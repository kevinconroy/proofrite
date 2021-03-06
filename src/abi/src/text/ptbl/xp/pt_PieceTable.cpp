/* AbiWord
 * Copyright (C) 1998 AbiSource, Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */


#include "ut_types.h"
#include "ut_misc.h"
#include "ut_assert.h"
#include "ut_debugmsg.h"
#include "ut_growbuf.h"
#include "pt_PieceTable.h"
#include "pf_Frag.h"
#include "pf_Frag_FmtMark.h"
#include "pf_Frag_Strux.h"
#include "pf_Frag_Strux_Block.h"
#include "pf_Frag_Strux_Section.h"
#include "pf_Frag_Text.h"
#include "pf_Frag_Object.h"
#include "pf_Fragments.h"
#include "px_ChangeRecord.h"
#include "px_CR_Span.h"
#include "px_CR_SpanChange.h"
#include "px_CR_Strux.h"
#include "pd_Style.h"


// TODO: calculate this from pf_FRAG_STRUX_*_LENGTH instead?
#define pt_BOD_POSITION 2

/*****************************************************************/
/*****************************************************************/

pt_PieceTable::pt_PieceTable(PD_Document * pDocument)
  : m_pts(PTS_Create), m_hashStyles(11), m_pDocument(pDocument),
    m_atomicGlobCount(0)
{

	setPieceTableState(PTS_Create);
	loading.m_indexCurrentInlineAP = 0;
}

pt_PieceTable::~pt_PieceTable()
{
	UT_HASH_PURGEDATA(PD_Style *, &m_hashStyles, delete);
}

void pt_PieceTable::setPieceTableState(PTState pts)
{
	UT_ASSERT(pts >= m_pts);

	if ((m_pts==PTS_Create) && (pts==PTS_Loading))
	{
		// transition from create to loading.
		// populate the builtin styles
		_loadBuiltinStyles();
	}

	if ((m_pts==PTS_Loading) && (pts==PTS_Editing))
	{
		// transition from loading to editing.
		// tack on an EOD fragment to the fragment list.
		// this allows us to safely go to the end of the document.
		pf_Frag * pfEOD = new pf_Frag(this,pf_Frag::PFT_EndOfDoc,0);
		m_fragments.appendFrag(pfEOD);
	}

	m_pts = pts;
	m_varset.setPieceTableState(pts);
}

/*!
 * Use this for deleting unneeded strux during doc import. Particularly useful for importing
 * RTF.
 */
bool pt_PieceTable::deleteStruxNoUpdate(PL_StruxDocHandle sdh)
{
	pf_Frag_Strux * pfs = (pf_Frag_Strux *) sdh;
	UT_DEBUGMSG(("SEVIOR: deleting strux %x \n",sdh));
	getFragments().unlinkFrag((pf_Frag *) pfs);
	delete pfs;
	return true;
}

/*!
 * This method inserts a strux of type pts immediately before the sdh given.
 * Attributes of the strux can be optionally passed. This method does not throw
 * a change record and should only be used under exceptional circumstances to 
 * repair the piecetable during loading. It was necessary to import RTF tables.
 */
bool pt_PieceTable::insertStruxNoUpdateBefore(PL_StruxDocHandle sdh, PTStruxType pts,const XML_Char ** attributes )
{
	pf_Frag_Strux * pfs = (pf_Frag_Strux *) sdh;
	UT_DEBUGMSG(("SEVIOR: Inserting strux of type %d no update %x \n",pts,sdh));
//
// Create an indexAP
//
	PT_AttrPropIndex indexAP = pfs->getIndexAP();
	if(attributes)
	{		
		PT_AttrPropIndex pAPIold = indexAP;
		bool bMerged = m_varset.mergeAP(PTC_AddFmt,pAPIold,attributes,NULL,&indexAP,getDocument());
		UT_ASSERT(bMerged);
	}
//
// create a strux
//
	pf_Frag_Strux * pNewStrux = NULL;
	_createStrux(pts,indexAP,&pNewStrux);
//
// Insert it.
//
	pf_Frag * pfPrev = pfs->getPrev();
	UT_ASSERT(pfPrev);
	if(!pfPrev)
	{
		return false;
	}
	m_fragments.insertFrag(pfPrev,(pf_Frag *) pNewStrux);
#if 0
	m_pDocument->miniDump(sdh,8);
#endif
	return true;
}

void pt_PieceTable::_unlinkFrag(pf_Frag * pf,
								pf_Frag ** ppfEnd, UT_uint32 * pfragOffsetEnd)
{
	// unlink the given fragment from the fragment list.
	// also, see if the adjacent fragments can be coalesced.
	// in (ppfEnd,pfragOffsetEnd) we return the position
	// immediately past the frag we're deleting.
	// the caller is responsible for deleting pf.

	if (ppfEnd)
		*ppfEnd = pf->getNext();
	if (pfragOffsetEnd)
		*pfragOffsetEnd = 0;

	pf_Frag * pp = pf->getPrev();

	m_fragments.unlinkFrag(pf);

	if (   pp
		&& pp->getType()==pf_Frag::PFT_Text
		&& pp->getNext()
		&& pp->getNext()->getType()==pf_Frag::PFT_Text)
	{
		pf_Frag_Text * ppt = static_cast<pf_Frag_Text *> (pp);
		pf_Frag_Text * pnt = static_cast<pf_Frag_Text *> (pp->getNext());
		UT_uint32 prevLength = ppt->getLength();
		if (   ppt->getIndexAP() == pnt->getIndexAP()
			&& m_varset.isContiguous(ppt->getBufIndex(),prevLength,pnt->getBufIndex()))
		{
			if (ppfEnd)
				*ppfEnd = pp;
			if (pfragOffsetEnd)
				*pfragOffsetEnd = prevLength;

			ppt->changeLength(prevLength+pnt->getLength());
			m_fragments.unlinkFrag(pnt);
			delete pnt;
		}
	}
}

bool pt_PieceTable::_struxHasContent(pf_Frag_Strux * pfs) const
{
	// return true iff the paragraph has content (text).

	return (pfs->getNext() && (pfs->getNext()->getType() == pf_Frag::PFT_Text));
}

bool pt_PieceTable::getAttrProp(PT_AttrPropIndex indexAP, const PP_AttrProp ** ppAP) const
{
	UT_ASSERT(ppAP);

	const PP_AttrProp * pAP = m_varset.getAP(indexAP);
	if (!pAP)
		return false;

	*ppAP = pAP;
	return true;
}

bool pt_PieceTable::_getSpanAttrPropHelper(pf_Frag * pf, const PP_AttrProp ** ppAP) const
{
#define ReturnThis(type,pf)													\
	do {	type * _pf_ = static_cast< type *>((pf));						\
			const PP_AttrProp * pAP = m_varset.getAP(_pf_->getIndexAP());	\
			*ppAP = pAP;													\
			return (pAP != NULL);											\
	} while (0)

	switch (pf->getType())
	{
	case pf_Frag::PFT_FmtMark:
		ReturnThis( pf_Frag_FmtMark, pf );

	case pf_Frag::PFT_Text:
		ReturnThis( pf_Frag_Text, pf );

	case pf_Frag::PFT_Object:
		ReturnThis( pf_Frag_Object, pf );

	case pf_Frag::PFT_Strux:
	case pf_Frag::PFT_EndOfDoc:
	default:
		*ppAP = NULL;
		return false;
	}
#undef ReturnThis
}


bool pt_PieceTable::getSpanAttrProp(PL_StruxDocHandle sdh, UT_uint32 offset, bool bLeftSide,
									   const PP_AttrProp ** ppAP) const
{
	// return the AP for the text at the given offset from the given strux.
	// offset zero now refers to the first character in the block, so adding
	// fl_BLOCK_STRUX_OFFSET to the offset in the call is no longer necessary.

	UT_ASSERT(sdh);
	UT_ASSERT(ppAP);

	pf_Frag * pf = (pf_Frag *)sdh;
	UT_ASSERT(pf->getType() == pf_Frag::PFT_Strux);
	pf_Frag_Strux * pfsBlock = static_cast<pf_Frag_Strux *> (pf);
	UT_ASSERT(pfsBlock->getStruxType() == PTX_Block);

	UT_uint32 cumOffset = 0;
	UT_uint32 cumEndOffset = 0;
	pf_Frag * pfTemp = NULL;
	for (pfTemp=pfsBlock->getNext(); (pfTemp); cumOffset=cumEndOffset, pfTemp=pfTemp->getNext())
	{
		cumEndOffset = cumOffset+pfTemp->getLength();

		if (offset > cumEndOffset)		// the place we want is way past the end of pfTemp,
			continue;					// so keep searching.

		if (offset == cumOffset)		// there's a frag boundary exactly where we want. pfTemp is to our right.
		{
			// FmtMarks have length zero, so we have to see what side of the position the caller wants.
			if ((pfTemp->getType()==pf_Frag::PFT_FmtMark) && (!bLeftSide))
				continue;				// go round again and get thing to the right

			return _getSpanAttrPropHelper(pfTemp,ppAP);
		}

		UT_ASSERT(offset > cumOffset);

		if (offset == cumEndOffset)		// there's a frag boundary exactly where we want. pfTemp is to our left.
		{
			if (!bLeftSide)
				continue;				// return the next one on the next loop iteration

			// FmtMarks have length zero, so we advance to put it to our left and then decide what to do
			if (pfTemp->getNext() && (pfTemp->getNext()->getType()==pf_Frag::PFT_FmtMark))
				continue;				// we'll return this one on the next loop iteration

			// otherwise, we want the thing that we are at the end of (ie that is to the left)
			return _getSpanAttrPropHelper(pfTemp,ppAP);
		}

		UT_ASSERT(offset < cumEndOffset);

		// the place we want is inside of a fragment, so just use it.
		return _getSpanAttrPropHelper(pfTemp,ppAP);
	}

	*ppAP = NULL;
	return false;
}


bool pt_PieceTable::getSpanPtr(PL_StruxDocHandle sdh, UT_uint32 offset,
								  const UT_UCSChar ** ppSpan, UT_uint32 * pLength) const
{
	// note: offset zero refers to the strux.  the first character is at
	// note: (0 + pfsBlock->getLength()).

	*ppSpan = NULL;
	*pLength = 0;

	pf_Frag * pf = (pf_Frag *)sdh;
	UT_ASSERT(pf->getType() == pf_Frag::PFT_Strux);
	pf_Frag_Strux * pfsBlock = static_cast<pf_Frag_Strux *> (pf);
	UT_ASSERT(pfsBlock->getStruxType() == PTX_Block);
	xxx_UT_DEBUGMSG(("getSpanPtr: Requested offset %d \n",offset));
	
	UT_uint32 cumOffset = pf->getLength();
	for (pf_Frag * pfTemp=pfsBlock->getNext(); (pfTemp); pfTemp=pfTemp->getNext())
	{
		xxx_UT_DEBUGMSG(("getSpanPtr: offset %d cumOffset %d \n",offset,cumOffset));
		if (offset == cumOffset)
		{
			if (pfTemp->getType() == pf_Frag::PFT_FmtMark)
				continue;
			if(isFootnote(pfTemp) || isEndFootnote(pfTemp))
			{
				cumOffset += pfTemp->getLength();
				continue;
			}
			if (pfTemp->getType() != pf_Frag::PFT_Text)
			{
				xxx_UT_DEBUGMSG(("getSpanPtr: Error 1 offset %d cumOffset %d \n",offset,cumOffset));
//				UT_ASSERT(0);
				return false;
			}

			pf_Frag_Text * pfText = static_cast<pf_Frag_Text *> (pfTemp);
			*ppSpan = getPointer(pfText->getBufIndex());
			*pLength = pfText->getLength();
			return true;
		}
		if (offset < cumOffset+pfTemp->getLength())
		{
			if(isFootnote(pfTemp) || isEndFootnote(pfTemp))
			{
				cumOffset += pfTemp->getLength();
				continue;
			}
			if (pfTemp->getType() != pf_Frag::PFT_Text)
			{
				xxx_UT_DEBUGMSG(("getSpanPtr: Error 2 offset %d cumOffset %d \n",offset,cumOffset));
				return false;
			}
			pf_Frag_Text * pfText = static_cast<pf_Frag_Text *> (pfTemp);
			const UT_UCSChar * p = getPointer(pfText->getBufIndex());
			UT_uint32 delta = offset - cumOffset;
			*ppSpan = p + delta;
			*pLength = pfText->getLength() - delta;
			return true;
		}

		cumOffset += pfTemp->getLength();
	}
	xxx_UT_DEBUGMSG(("getSpanPtr: Error 3 offset %d cumOffset %d \n",offset,cumOffset));
	return false;
}


PD_Document * pt_PieceTable::getDocument(void)
{
        return m_pDocument;
}

/*!
  Copy paragraph (block) into buffer
  \param sdh Paragraph to copy
  \retval pgb Buffer where text should be copied to
  \return Always returns true

  Copy the contents (unicode character data) of the paragraph (block)
  into the growbuf given.  We append the content onto the growbuf.
*/
bool pt_PieceTable::getBlockBuf(PL_StruxDocHandle sdh,
                                   UT_GrowBuf * pgb) const
{
    UT_ASSERT(pgb);

    pf_Frag * pf = (pf_Frag *)sdh;
    UT_return_val_if_fail(pf->getType() == pf_Frag::PFT_Strux, false);
    pf_Frag_Strux * pfsBlock = static_cast<pf_Frag_Strux *> (pf);
    UT_return_val_if_fail(pfsBlock->getStruxType() == PTX_Block, false);

    UT_uint32 bufferOffset = pgb->getLength();

    pf_Frag * pfTemp = pfsBlock->getNext();
	UT_sint32 countFoots = 0;
    while (pfTemp)
    {
        switch (pfTemp->getType())
        {
        default:
            UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
        case pf_Frag::PFT_Strux:
//
// Have to deal with embedded section struxes like Footnotes. We do this by
// filling the block buffer with the content contained until we find an
// end of embedded container. By placing zero's and content as expected in
// the block buffer we match the situation in fl_BlockLayout.
//
		{
			UT_GrowBufElement valz = 0;
            bool bAppended;
			if(isFootnote(pfTemp))
			{
				countFoots++;
				bAppended = pgb->ins(bufferOffset,&valz,1);
				UT_ASSERT(bAppended);
				bufferOffset++;
				pfTemp = pfTemp->getNext();
				break;
			}
			if(isEndFootnote(pfTemp))
			{
				countFoots--;
				if(countFoots < 0)
				{
					pfTemp = NULL;
					break;
				}
				bAppended = pgb->ins(bufferOffset,&valz,1);
				UT_ASSERT(bAppended);
				bufferOffset++;
				pfTemp = pfTemp->getNext();
				break;
			}
			if(countFoots>0)
			{
				bAppended = pgb->ins(bufferOffset,&valz,1);
				UT_ASSERT(bAppended);
				bufferOffset++;
				pfTemp = pfTemp->getNext();
				break;
			}
			pfTemp = NULL;
			break;
		}
        case pf_Frag::PFT_EndOfDoc:
            pfTemp = NULL;
            break;

        case pf_Frag::PFT_FmtMark:
            pfTemp = pfTemp->getNext();
            break;

        case pf_Frag::PFT_Text:
        {
            pf_Frag_Text * pft = static_cast<pf_Frag_Text *>(pfTemp);
            const UT_UCSChar * pSpan = getPointer(pft->getBufIndex());
            UT_uint32 length = pft->getLength();

            bool bAppended;
            bAppended = pgb->ins(bufferOffset,(UT_GrowBufElement*)pSpan,length);
            UT_ASSERT(bAppended);

            bufferOffset += length;
        }
        pfTemp = pfTemp->getNext();
        break;

        case pf_Frag::PFT_Object:
        {
            /*
              TODO investigate this....  Now *here* is a seriously
              questionable fragment of code.  :-) We can't let
              getBlockBuf halt on a block when it finds an inline
              object.  However, we can't very well sensibly store an
              inline object in a UNICODE character.  So, we dump
              USC_BLOCK in its place, to preserve the integrity of the
              buffer.  Obviously, those codes aren't useful, but at
              least the app doesn't crash, and the rest of the text in
              the block is safely stored in the buffer in the proper
              location.

              The UCS_ABI_OBJECT used to be defined as a space, but
              that caused selection code to fail for fields since the
              code would look for the beginning of a word, ignoring
              spaces. Now the UCS_ABI_OBJECT is instead defined as an
              alpha character. Doesn't really matter since it'll never
              be used for anything but limit checking anyway. See bug
              #223 for details.
			*/

            UT_uint32 length = pfTemp->getLength();

            // TODO investigate appending the SPACES directly to
            // TODO the pgb.  **or** investigate the cost of this
            // TODO malloc and what happens when it fails....

            UT_UCSChar* pSpaces = new UT_UCSChar[length];
            for (UT_uint32 i=0; i<length; i++)
            {
                pSpaces[i] = UCS_ABI_OBJECT;
            }
            bool bAppended;
            bAppended = pgb->ins(bufferOffset, (UT_GrowBufElement*)pSpaces, length);
            delete[] pSpaces;
            UT_ASSERT(bAppended);

            bufferOffset += length;
        }
        pfTemp = pfTemp->getNext();
        break;
        }
    }

    UT_ASSERT(bufferOffset == pgb->getLength());
    return true;
}

bool pt_PieceTable::getBounds(bool bEnd, PT_DocPosition & docPos) const
{
	// be optimistic
	bool res = true;

	if (!bEnd)
	{
		docPos = pt_BOD_POSITION;
	}
	else
	{
		// NOTE: this gets called for every cursor motion
		// TODO: be more efficient & cache the doc length
		// Sevior I did this 6/6/2001
		if(m_fragments.areFragsDirty())
		{
			m_fragments.cleanFrags();
		}
		docPos = m_fragments.getLast()->getPos()+m_fragments.getLast()->getLength();
	}
	return res;
}

PT_DocPosition pt_PieceTable::getStruxPosition(PL_StruxDocHandle sdh) const
{
	// return absolute document position of the given handle.

	pf_Frag * pfToFind = (pf_Frag *)sdh;

	return getFragPosition(pfToFind);
}

void pt_PieceTable::deleteHdrFtrStrux(pf_Frag_Strux * pfs)
{
	_realDeleteHdrFtrStrux(pfs);
}

void pt_PieceTable::_realDeleteHdrFtrStrux(pf_Frag_Strux * pfs)
{
	_deleteHdrFtrStruxWithNotify(pfs);
}

PT_DocPosition pt_PieceTable::getFragPosition(const pf_Frag * pfToFind) const
{
	if(m_fragments.areFragsDirty())
		m_fragments.cleanFrags();
	return  pfToFind->getPos();
}

bool pt_PieceTable::getFragFromPosition(PT_DocPosition docPos,
										   pf_Frag ** ppf,
										   PT_BlockOffset * pFragOffset) const
{
	// return the frag at the given doc position.
//
// Sevior do a binary search here now
//
	pf_Frag * pfLast = m_fragments.findFirstFragBeforePos(docPos);
	if(pfLast)
	{
		xxx_UT_DEBUGMSG(("_findFrag: docPos %d pfLast->getPos %d pfLast->getLength %d \n",docPos,pfLast->getPos(),pfLast->getLength()));
		while(pfLast->getNext() && docPos >= (pfLast->getPos() + pfLast->getLength()))
		{
			xxx_UT_DEBUGMSG(("_findFrag: docPos %d pfLast->getPos %d pfLast->getLength %d \n",docPos,pfLast->getPos(),pfLast->getLength()));
			pfLast = pfLast->getNext();
		}
		xxx_UT_DEBUGMSG(("_findFrag: docPos %d pfLast->getPos %d pfLast->getLength %d offset %d Frag Type %d \n",docPos,pfLast->getPos(),pfLast->getLength(),docPos - pfLast->getPos(),pfLast->getType()));
		if (pFragOffset)
			*pFragOffset = docPos - pfLast->getPos();
		*ppf = pfLast;       
		return true;
		xxx_UT_DEBUGMSG(("SEVIOR: I found frag %d \n",getFragNumber(pfLast)));
	}

	UT_ASSERT(pfLast);
	UT_ASSERT(pfLast->getType() == pf_Frag::PFT_EndOfDoc);

	return true;
}
	//  PT_DocPosition sum = 0;
//  	pfLast = NULL;
//  	pf_Frag * pf = NULL;
//  	for (pf = m_fragments.getFirst(); (pf); pf=pf->getNext())
//  	{
//  		if ((docPos >= sum) && (docPos < sum+pf->getLength()))
//  		{
//  			*ppf = pf;
//  			if (pFragOffset)
//  				*pFragOffset = docPos - sum;

//  			// a FmtMark has length zero.  we don't want to find it
//  			// in this loop -- rather we want the thing just past it.

//  			UT_ASSERT(pf->getType() != pf_Frag::PFT_FmtMark);
//  			UT_DEBUGMSG(("SEVIOR: Jeff finds frag %d at Pos %d \n",getFragNumber(pf),docPos));

//  			return true;
//  		}

//  		sum += pf->getLength();
//  		pfLast = pf;
//  	}

//  	// if we fall out of the loop, we didn't have a node
//  	// at or around the document position requested.
//  	// since we now have an EOD fragment, we should not
//  	// ever see this -- unless the caller sends a bogus
//  	// doc position.

//  	UT_ASSERT(pfLast);
//  	UT_ASSERT(pfLast->getType() == pf_Frag::PFT_EndOfDoc);

//  	// TODO if (docPos > sum) we should probably complain...

//  	*ppf = pfLast;
//  	if (pFragOffset)
//  		*pFragOffset = docPos - sum;
//  	UT_DEBUGMSG(("SEVIOR: Jeff finds Last frag Number %d at Pos %d \n",getFragNumber(pf),docPos));


//  	return true;
//  }

bool pt_PieceTable::getFragsFromPositions(PT_DocPosition dPos1, PT_DocPosition dPos2,
											 pf_Frag ** ppf1, PT_BlockOffset * pOffset1,
											 pf_Frag ** ppf2, PT_BlockOffset * pOffset2) const
{
	// compute the (fragment,offset) pairs for each position given.

	UT_ASSERT(dPos1 <= dPos2);
	UT_ASSERT(ppf1);
	UT_ASSERT(pOffset1);

	// the first set has to be done the hard way.

	if (!getFragFromPosition(dPos1,ppf1,pOffset1))
		return false;

	// now get the second set relative to the first.

	PT_DocPosition deltaPos = dPos2 - dPos1;
	PT_BlockOffset offset = *pOffset1;
	pf_Frag * pf = *ppf1;
	UT_uint32 length = pf->getLength();
	while (offset+deltaPos >= length)
	{
		deltaPos -= (length - offset);
		offset = 0;
		if (pf->getType() == pf_Frag::PFT_EndOfDoc)
			break;						// TODO if we haven't quite reached dPos2, we should probably complain...
		pf = pf->getNext();
		length = pf->getLength();
	}

	// a FmtMark has length zero.  we don't want to find it here.
	// rather we want the thing to the right of it.
	UT_ASSERT(pf->getType() != pf_Frag::PFT_FmtMark);

	if (ppf2)
		*ppf2 = pf;
	if (pOffset2)
		*pOffset2 = offset+deltaPos;
	return true;
}

bool pt_PieceTable::getStruxFromPosition(PL_ListenerId listenerId,
											PT_DocPosition docPos,
											PL_StruxFmtHandle * psfh) const
{
	// return the SFH of the last strux immediately prior to
	// the given absolute document position.

	pf_Frag_Strux * pfs = NULL;
	if (!_getStruxFromPosition(docPos,&pfs))
		return false;

	*psfh = pfs->getFmtHandle(listenerId);
	return true;
}

bool pt_PieceTable::getStruxOfTypeFromPosition(PL_ListenerId listenerId,
												  PT_DocPosition docPos,
												  PTStruxType pts,
												  PL_StruxFmtHandle * psfh) const
{
	// return the SFH of the last strux of the given type
	// immediately prior to the given absolute document position.

	pf_Frag_Strux * pfs = NULL;
	if (!_getStruxOfTypeFromPosition(docPos,pts,&pfs))
		return false;

	*psfh = pfs->getFmtHandle(listenerId);
	return true;
}
///
/// return the SDH of the last strux of the given type
/// immediately prior to the given absolute document position.
///
bool pt_PieceTable::getStruxOfTypeFromPosition( PT_DocPosition docPos,
						   PTStruxType pts,
						   PL_StruxDocHandle * sdh) const
{

	pf_Frag_Strux * pfs = NULL;
	if (!_getStruxOfTypeFromPosition(docPos,pts,&pfs))
			return false;
	*sdh = ( PL_StruxDocHandle ) pfs;
	return true;
}

bool pt_PieceTable::_getStruxFromPosition(PT_DocPosition docPos,
											 pf_Frag_Strux ** ppfs) const
{
	// return the strux fragment immediately prior (containing)
	// the given absolute document position.
	pf_Frag * pfFirst = m_fragments.findFirstFragBeforePos( docPos);
	while(pfFirst && pfFirst->getPrev() && pfFirst->getPos()  >= docPos)
	{
		pfFirst = pfFirst->getPrev();
	}
	while(pfFirst && pfFirst->getPrev() && pfFirst->getType() !=pf_Frag::PFT_Strux)
	{
		pfFirst = pfFirst->getPrev();
	}
//	UT_DEBUGMSG(("SEVIOR: I find strux frag number %d  sum = %d at pos %d \n",getFragNumber(pfFirst),pfFirst->getPos(),docPos));
  	pf_Frag_Strux * pfs = static_cast<pf_Frag_Strux *> (pfFirst);
  	*ppfs = pfs;
    return true;

	//  PT_DocPosition sum = pfFirst->getPos();
//  	pf_Frag * pfLastStrux = NULL;

//  	for (pf_Frag * pf = pfFirst; (pf); pf=pf->getNext())
//  	{
//  		if (pf->getType() == pf_Frag::PFT_Strux)
//  			pfLastStrux = pf;

//  		sum += pf->getLength();

//  		if (sum >= docPos)
//  			goto FoundIt;
//  	}

	// if we fall out of the loop, we didn't have a text node
	// at or around the document position requested.
	// return the last strux in the document.

//   FoundIt:

//  	pf_Frag_Strux * pfs = static_cast<pf_Frag_Strux *> (pfLastStrux);
//  	UT_DEBUGMSG(("SEVIOR: Jeff find strux frag number %d  sum = %d at pos %d \n",getFragNumber(pfLastStrux),sum,docPos));
//  	*ppfs = pfs;
//      return true;
}

bool pt_PieceTable::isEndFootnote(pf_Frag * pf) const
{
	if(pf->getType() == pf_Frag::PFT_Strux)
	{
		pf_Frag_Strux * pfs = (pf_Frag_Strux *) pf;
		if(pfs->getStruxType() == PTX_EndFootnote)
		{
			return true;
		}
	}
	return false;
}


bool pt_PieceTable::isFootnote(pf_Frag * pf) const
{
	if(pf->getType() == pf_Frag::PFT_Strux)
	{
		pf_Frag_Strux * pfs = (pf_Frag_Strux *) pf;
		if(pfs->getStruxType() == PTX_SectionFootnote)
		{
			return true;
		}
	}
	return false;
}

bool pt_PieceTable::_getStruxFromPositionSkip(PT_DocPosition docPos,
											 pf_Frag_Strux ** ppfs) const
{
	// return the strux fragment immediately prior (containing)
	// the given absolute document position. This version skips past
    // Footnote struxes.
	UT_sint32 countEndFootnotes = 0;
	pf_Frag * pfFirst = m_fragments.findFirstFragBeforePos( docPos);
	if(isEndFootnote(pfFirst))
	{
		countEndFootnotes++;
	}
	while(pfFirst && pfFirst->getPrev() && pfFirst->getPos()  >= docPos )
	{
		pfFirst = pfFirst->getPrev();
		if(isFootnote(pfFirst))
		{
			countEndFootnotes--;
		}
		else if(isEndFootnote(pfFirst))
		{
			countEndFootnotes++;
		}
		xxx_UT_DEBUGMSG(("countEndNotes 1 %d \n",countEndFootnotes));
	}
	while(pfFirst && pfFirst->getPrev() && pfFirst->getType() !=pf_Frag::PFT_Strux || (countEndFootnotes > 0) || isFootnote(pfFirst) || isEndFootnote(pfFirst))
	{
		pfFirst = pfFirst->getPrev();
		if(isFootnote(pfFirst))
		{
			countEndFootnotes--;
			pfFirst = pfFirst->getPrev();
		}
		else if(isEndFootnote(pfFirst))
		{
			countEndFootnotes++;
			pfFirst = pfFirst->getPrev();
		}
		xxx_UT_DEBUGMSG(("countEndNotes 2 %d \n",countEndFootnotes));
	}
	xxx_UT_DEBUGMSG(("countEndNotes final %d \n",countEndFootnotes));
  	pf_Frag_Strux * pfs = static_cast<pf_Frag_Strux *> (pfFirst);
  	*ppfs = pfs;
    return true;
}

bool pt_PieceTable::_getStruxOfTypeFromPosition(PT_DocPosition dpos,
												   PTStruxType pts,
												   pf_Frag_Strux ** ppfs) const
{
	// return the strux fragment of the given type containing
	// the given absolute document position.
	UT_ASSERT(ppfs);
	xxx_UT_DEBUGMSG(("_getStruxOfTypeFromPosition: looking for type %d \n",pts));
	*ppfs = NULL;

	pf_Frag_Strux * pfs = NULL;
	if(pts == PTX_EndFootnote || pts == PTX_SectionFootnote)
	{
		if (!_getStruxFromPosition(dpos,&pfs))
			return false;
	}
	else
	{
		if (!_getStruxFromPositionSkip(dpos,&pfs))
			return false;
	}

	if (pfs->getStruxType() == pts || (pts == PTX_Section && pfs->getStruxType() == PTX_SectionHdrFtr) || (pts == PTX_SectionFootnote && pfs->getStruxType() == PTX_SectionFootnote) || (pts == PTX_SectionTable && pfs->getStruxType() == PTX_SectionTable) || (pts == PTX_SectionCell && pfs->getStruxType() == PTX_SectionCell) || (pts == PTX_EndTable && pfs->getStruxType() == PTX_EndTable) || (pts == PTX_EndCell && pfs->getStruxType() == PTX_EndCell)  )		// is it of the type we want
	{
		*ppfs = pfs;
		return true;
	}

	// if not, we walk backwards thru the list and try to find it.
	UT_sint32 numEndTable = 0;
	for (pf_Frag * pf=pfs; (pf); pf=pf->getPrev())
		if (pf->getType() == pf_Frag::PFT_Strux)
		{
			pf_Frag_Strux * pfsTemp = static_cast<pf_Frag_Strux *>(pf);
			if(pfsTemp->getStruxType() == PTX_EndTable)
			{
				numEndTable++;
			}
			else if(pfsTemp->getStruxType() == PTX_SectionTable)
			{
				numEndTable--;
			}
			if (pfsTemp->getStruxType() == pts || (pts == PTX_Section && pfsTemp->getStruxType() == PTX_SectionHdrFtr) || (pts == PTX_SectionFootnote && pfsTemp->getStruxType() == PTX_SectionFootnote) || (pts == PTX_EndFootnote && pfsTemp->getStruxType() == PTX_EndFootnote))	// did we find it
			{
				if(((numEndTable < 0) && (pfsTemp->getStruxType()==PTX_SectionTable)) || (numEndTable == 0 && (pfsTemp->getStruxType()!=PTX_SectionTable)))
				{
					*ppfs = pfsTemp;
					return true;
				}
				else if(pfsTemp->getStruxType() != PTX_SectionTable &&
						pfsTemp->getStruxType() != PTX_SectionCell &&
						pfsTemp->getStruxType() != PTX_EndTable &&
						pfsTemp->getStruxType() != PTX_EndCell)
				{
					*ppfs = pfsTemp;
					return true;
				}
			}
		}

	// did not find it.

	return false;
}

bool pt_PieceTable::_getStruxFromFrag(pf_Frag * pfStart, pf_Frag_Strux ** ppfs) const
{
	// return the strux frag immediately prior to (containing)
	// the given fragment.

	*ppfs = NULL;

	pf_Frag * pf;

	for (pf=pfStart->getPrev(); (pf && (pf->getType() != pf_Frag::PFT_Strux)); pf=pf->getPrev())
		;
	if (!pf)
		return false;

	*ppfs = static_cast<pf_Frag_Strux *>(pf);
	return true;
}


bool pt_PieceTable::_getStruxFromFragSkip(pf_Frag * pfStart, pf_Frag_Strux ** ppfs) const
{
	// return the strux frag immediately prior to (containing)
	// the given fragment while skipping endFootnote/footnote stuff.

	*ppfs = NULL;

	pf_Frag * pf;
	UT_sint32 countFoots = 0;
	if(isEndFootnote(pfStart))
	{
		countFoots++;
	}
	pf = pfStart->getPrev();
	if(isEndFootnote(pf))
	{
		countFoots++;
	}
	xxx_UT_DEBUGMSG(("_getStruxFromFragStrux: 1 countFoots %d \n",countFoots));
	while(pf && ((pf->getType() != pf_Frag::PFT_Strux) || (countFoots > 0) 
				 || isFootnote(pf) || isEndFootnote(pf)))
	{
		pf=pf->getPrev();
		if(isFootnote(pf))
		{
			countFoots--;
		}
		else if(isEndFootnote(pf))
		{
			countFoots++;
		}
		xxx_UT_DEBUGMSG(("_getStruxFromFragStrux: 2 countFoots %d \n",countFoots));
	}
		;
	if (!pf)
		return false;

	*ppfs = static_cast<pf_Frag_Strux *>(pf);
	return true;
}

UT_uint32 pt_PieceTable::_computeBlockOffset(pf_Frag_Strux * pfs,pf_Frag * pfTarget) const
{
	// return the block offset of the beginning of pfTarget from the end of pfs.

	UT_uint32 sum;
	pf_Frag * pf;

	for (pf=pfs->getNext(), sum=0; (pf!=pfTarget); sum+=pf->getLength(), pf=pf->getNext())
		;

	return sum;
}


void pt_PieceTable::clearIfAtFmtMark(PT_DocPosition dpos)
{
	while (_lastUndoIsThisFmtMark(dpos))
	{
		UT_DEBUGMSG(("clearIfAtFmtMark doing something...\n"));
		undoCmd();
	}
}

bool pt_PieceTable::_changePointWithNotify(PT_DocPosition dpos)
{
	PX_ChangeRecord * pcr
		= new PX_ChangeRecord(PX_ChangeRecord::PXT_ChangePoint,
							  dpos, 0);
	UT_ASSERT(pcr);

	m_history.addChangeRecord(pcr);
	m_pDocument->notifyListeners(NULL, pcr);

	return true;
}



