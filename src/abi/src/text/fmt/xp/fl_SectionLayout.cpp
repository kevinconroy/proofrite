/* AbiWord
 * Copyright (C) 1998 AbiSource, Inc.
 * Copyright (C) 2002 Martin Sevior (msevior@physics.unimelb.edu.au>
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

#include <string.h>
#include <stdlib.h>

#include "ut_types.h"
#include "ut_string.h"

#include "ap_Prefs.h"
#include "fl_SectionLayout.h"
#include "fl_FootnoteLayout.h"
#include "fl_Layout.h"
#include "fl_DocLayout.h"
#include "fl_BlockLayout.h"
#include "fl_TableLayout.h"
#include "fp_TableContainer.h"
#include "fb_LineBreaker.h"
#include "fb_ColumnBreaker.h"
#include "fp_Page.h"
#include "fp_Line.h"
#include "fp_Column.h"
#include "pd_Document.h"
#include "pp_AttrProp.h"
#include "gr_Graphics.h"
#include "pp_Property.h"
#include "px_ChangeRecord.h"
#include "px_CR_Object.h"
#include "px_CR_ObjectChange.h"
#include "px_CR_Span.h"
#include "px_CR_SpanChange.h"
#include "px_CR_Strux.h"
#include "px_CR_StruxChange.h"
#include "px_CR_Glob.h"
#include "fv_View.h"
#include "fp_Run.h"
#include "ut_debugmsg.h"
#include "ut_assert.h"
#include "ut_units.h"

#define SCALE_TO_SCREEN (double)getGraphics()->getResolution() / UT_LAYOUT_UNITS

/*
  TODO this file is now really too long.  divide it up
  into smaller ones.
*/

fl_SectionLayout::fl_SectionLayout(FL_DocLayout* pLayout, PL_StruxDocHandle sdh, PT_AttrPropIndex indexAP, SectionType iType, fl_ContainerType iCType, PTStruxType iStrux, fl_ContainerLayout * pMyContainerLayout)
	: fl_ContainerLayout(pMyContainerLayout, sdh, indexAP,iStrux, iCType),
	  m_iType(iType),
	  m_pLayout(pLayout),
	  m_bIsCollapsed(true),
	  m_bNeedsReformat(true),
	  m_bNeedsRedraw(true)
{
	UT_ASSERT(pLayout);
	m_pDoc = pLayout->getDocument();
}

fl_SectionLayout::~fl_SectionLayout()
{
}

FL_DocLayout* fl_SectionLayout::getDocLayout(void) const
{
	if(m_pLayout == NULL)
	{
		return fl_ContainerLayout::getDocLayout();
	}
	return m_pLayout;
}

bool fl_SectionLayout::recalculateFields(UT_uint32 iUpdateCount)
{
	bool bResult = false;

	fl_ContainerLayout*	pL = getFirstLayout();

	while (pL)
	{
		bResult = pL->recalculateFields(iUpdateCount) || bResult;

		pL = pL->getNext();
	}

	return bResult;
}


void fl_SectionLayout::markAllRunsDirty(void)
{
	fl_ContainerLayout*	pL = getFirstLayout();
	while (pL)
	{
		pL->markAllRunsDirty();
		pL = pL->getNext();
	}
}

void fl_SectionLayout::_purgeLayout()
{
	fl_ContainerLayout*	pL = getLastLayout();

	while (pL)
	{
		fl_ContainerLayout* pNuke = pL;

		pL = pL->getPrev();

		delete pNuke;
	}

	return;
}

void fl_SectionLayout::setNeedsReformat(UT_uint32 /*offset*/)
{
	m_bNeedsReformat = true;
	if(myContainingLayout() != NULL && static_cast<fl_SectionLayout *>(myContainingLayout()) != this)
	{
		static_cast<fl_SectionLayout *>(myContainingLayout())->setNeedsReformat();
	}
}


void fl_SectionLayout::setNeedsRedraw(void)
{
	m_bNeedsRedraw = true;
	if(myContainingLayout() != NULL  && static_cast<fl_SectionLayout *>(myContainingLayout()) != this)
	{
		static_cast<fl_SectionLayout *>(myContainingLayout())->setNeedsRedraw();
	}
}

bool fl_SectionLayout::bl_doclistener_populateSpan(fl_ContainerLayout* pBL, const PX_ChangeRecord_Span * pcrs, PT_BlockOffset blockOffset, UT_uint32 len)
{
	if(pBL->getPrev()!= NULL && pBL->getPrev()->getLastContainer()==NULL)
	{
		UT_DEBUGMSG(("In bl_doclistner_pop no LastLine \n"));
		UT_DEBUGMSG(("getPrev = %d this = %d \n",pBL->getPrev(),pBL));
		//  UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
	}

	return static_cast<fl_BlockLayout *>(pBL)->doclistener_populateSpan(pcrs, blockOffset, len);
}

bool fl_SectionLayout::bl_doclistener_populateObject(fl_ContainerLayout* pBL, PT_BlockOffset blockOffset, const PX_ChangeRecord_Object * pcro)
{
	return static_cast<fl_BlockLayout *>(pBL)->doclistener_populateObject(blockOffset, pcro);
}

bool fl_SectionLayout::bl_doclistener_insertSpan(fl_ContainerLayout* pBL, const PX_ChangeRecord_Span * pcrs)
{
	bool bres = static_cast<fl_BlockLayout *>(pBL)->doclistener_insertSpan(pcrs);
	checkAndAdjustCellSize();
	return bres;
}

bool fl_SectionLayout::bl_doclistener_deleteSpan(fl_ContainerLayout* pBL, const PX_ChangeRecord_Span * pcrs)
{
	bool bres = static_cast<fl_BlockLayout *>(pBL)->doclistener_deleteSpan(pcrs);
	checkAndAdjustCellSize();
	return bres;
}

bool fl_SectionLayout::bl_doclistener_changeSpan(fl_ContainerLayout* pBL, const PX_ChangeRecord_SpanChange * pcrsc)
{
	bool bres = static_cast<fl_BlockLayout *>(pBL)->doclistener_changeSpan(pcrsc);
	checkAndAdjustCellSize();
	return bres;
}

bool fl_SectionLayout::bl_doclistener_deleteStrux(fl_ContainerLayout* pBL, const PX_ChangeRecord_Strux * pcrx)
{
	bool bres = static_cast<fl_BlockLayout *>(pBL)->doclistener_deleteStrux(pcrx);
	checkAndAdjustCellSize();
	return bres;
}

bool fl_SectionLayout::bl_doclistener_changeStrux(fl_ContainerLayout* pBL, const PX_ChangeRecord_StruxChange * pcrxc)
{
	bool bres = static_cast<fl_BlockLayout *>(pBL)->doclistener_changeStrux(pcrxc);
	checkAndAdjustCellSize();
	return bres;
}

bool fl_SectionLayout::bl_doclistener_insertBlock(fl_ContainerLayout* pBL, const PX_ChangeRecord_Strux * pcrx,
												  PL_StruxDocHandle sdh,
												  PL_ListenerId lid,
												  void (* pfnBindHandles)(PL_StruxDocHandle sdhNew,
																		  PL_ListenerId lid,
																		  PL_StruxFmtHandle sfhNew))
{
	if (pBL)
		return static_cast<fl_BlockLayout *>(pBL)->doclistener_insertBlock(pcrx, sdh, lid, pfnBindHandles);
	else
	{
		// Insert the block at the beginning of the section
		fl_BlockLayout*	pNewBL = (fl_BlockLayout *) insert(sdh, NULL, pcrx->getIndexAP(),FL_CONTAINER_BLOCK);
		if (!pNewBL)
		{
			UT_DEBUGMSG(("no memory for BlockLayout\n"));
			return false;
		}

		return pNewBL->doclistener_insertFirstBlock(pcrx, sdh,
													lid, pfnBindHandles);
	}
}

void fl_SectionLayout::checkAndAdjustCellSize(void)
{
	if(getContainerType() != FL_CONTAINER_CELL)
	{
		return;
	}
	fl_CellLayout * pCell = (fl_CellLayout *) this;
	pCell->checkAndAdjustCellSize();
}

bool fl_SectionLayout::bl_doclistener_insertSection(fl_ContainerLayout* pBL,
													SectionType iType,
													const PX_ChangeRecord_Strux * pcrx,
													PL_StruxDocHandle sdh,
													PL_ListenerId lid,
													void (* pfnBindHandles)(PL_StruxDocHandle sdhNew,
																			PL_ListenerId lid,
																			PL_StruxFmtHandle sfhNew))
{
	bool bres = static_cast<fl_BlockLayout *>(pBL)->doclistener_insertSection(pcrx, iType, sdh, lid, pfnBindHandles);
	return bres;
}


fl_SectionLayout * fl_SectionLayout::bl_doclistener_insertTable(fl_ContainerLayout* pBL,
													SectionType iType,
													const PX_ChangeRecord_Strux * pcrx,
													PL_StruxDocHandle sdh,
													PL_ListenerId lid,
													void (* pfnBindHandles)(PL_StruxDocHandle sdhNew,
																			PL_ListenerId lid,
																			PL_StruxFmtHandle sfhNew))
{
	fl_SectionLayout * pSL = static_cast<fl_BlockLayout *>(pBL)->doclistener_insertTable(pcrx, iType, sdh, lid, pfnBindHandles);
	checkAndAdjustCellSize();
	return pSL;
}

bool fl_SectionLayout::bl_doclistener_insertObject(fl_ContainerLayout* pBL, const PX_ChangeRecord_Object * pcro)
{
	bool bres = static_cast<fl_BlockLayout *>(pBL)->doclistener_insertObject(pcro);
	checkAndAdjustCellSize();
	return bres;
}

bool fl_SectionLayout::bl_doclistener_deleteObject(fl_ContainerLayout* pBL, const PX_ChangeRecord_Object * pcro)
{
	bool bres = static_cast<fl_BlockLayout *>(pBL)->doclistener_deleteObject(pcro);
	checkAndAdjustCellSize();
	return bres;
}

bool fl_SectionLayout::bl_doclistener_changeObject(fl_ContainerLayout* pBL, const PX_ChangeRecord_ObjectChange * pcroc)
{
	bool bres = static_cast<fl_BlockLayout *>(pBL)->doclistener_changeObject(pcroc);
	checkAndAdjustCellSize();
	return bres;
}

bool fl_SectionLayout::bl_doclistener_insertFmtMark(fl_ContainerLayout* pBL, const PX_ChangeRecord_FmtMark * pcrfm)
{
	bool bres = static_cast<fl_BlockLayout *>(pBL)->doclistener_insertFmtMark(pcrfm);
	checkAndAdjustCellSize();
	return bres;
}

bool fl_SectionLayout::bl_doclistener_deleteFmtMark(fl_ContainerLayout* pBL, const PX_ChangeRecord_FmtMark * pcrfm)
{
	bool bres = static_cast<fl_BlockLayout *>(pBL)->doclistener_deleteFmtMark(pcrfm);
	checkAndAdjustCellSize();
	return bres;
}

bool fl_SectionLayout::bl_doclistener_changeFmtMark(fl_ContainerLayout* pBL, const PX_ChangeRecord_FmtMarkChange * pcrfmc)
{
	bool bres = static_cast<fl_BlockLayout *>(pBL)->doclistener_changeFmtMark(pcrfmc);
	checkAndAdjustCellSize();
	return bres;
}

/*!
 * This method updates the Background color in all the runs from the Page color
 * in the DocSectionLayout.
 */
void fl_SectionLayout::updateBackgroundColor(void)
{
	fl_ContainerLayout*	pL = getFirstLayout();
	while (pL)
	{
		pL->updateBackgroundColor();
		pL = pL->getNext();
	}
	if(getType() != FL_SECTION_DOC)
		return;
	fl_DocSectionLayout * pDSL = static_cast<fl_DocSectionLayout *>(this);
	UT_Vector vecHdrFtr;
	pDSL->getVecOfHdrFtrs( &vecHdrFtr);
	UT_uint32 i = 0;
	for(i = 0; i < vecHdrFtr.getItemCount(); i++)
	{
		fl_HdrFtrSectionLayout * pHdrFtr = (fl_HdrFtrSectionLayout *) vecHdrFtr.getNthItem(i);
		pHdrFtr->updateBackgroundColor();
	}
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
#ifdef _MSC_VER	// MSVC++ warns about using 'this' in initializer list.
#pragma warning(disable: 4355)
#endif
fl_DocSectionLayout::fl_DocSectionLayout(FL_DocLayout* pLayout, PL_StruxDocHandle sdh, PT_AttrPropIndex indexAP, SectionType iType)
	: fl_SectionLayout(pLayout, sdh, indexAP, iType, FL_CONTAINER_DOCSECTION,PTX_Section, this)
{
	UT_ASSERT((iType == FL_SECTION_DOC || iType == FL_SECTION_ENDNOTE));
	m_pFirstColumn = NULL;
	m_pLastColumn = NULL;

	m_pHeaderSL = NULL;
	m_pFooterSL = NULL;
	m_pHeaderEvenSL = NULL;
	m_pFooterEvenSL = NULL;
	m_pHeaderFirstSL = NULL;
	m_pFooterFirstSL = NULL;
	m_pHeaderLastSL = NULL;
	m_pFooterLastSL = NULL;
	m_pEndnoteSL = NULL;
	m_pEndnoteOwnerSL = NULL;
	m_pFirstOwnedPage = NULL;
	m_bNeedsFormat = false;
	m_bNeedsRebuild = false;
	m_bNeedsSectionBreak = true;
	m_pDoc = pLayout->getDocument();
	_lookupProperties();
}

fl_DocSectionLayout::~fl_DocSectionLayout()
{
	// NB: be careful about the order of these
	_purgeLayout();

	UT_Vector vecHdrFtr;
	getVecOfHdrFtrs( &vecHdrFtr);
	UT_uint32 i = 0;
	fl_HdrFtrSectionLayout * pHdrFtr = NULL;
	for(i = 0; i < vecHdrFtr.getItemCount(); i++)
	{
		pHdrFtr = (fl_HdrFtrSectionLayout *) vecHdrFtr.getNthItem(i);
		delete pHdrFtr;
	}

	fp_Column* pCol = m_pFirstColumn;
	while (pCol)
	{
		fp_Column* pNext = (fp_Column *) pCol->getNext();

		delete pCol;

		pCol = pNext;
	}
}

FootnoteType fl_DocSectionLayout::getFootnoteType(void) const
{
	return m_FootnoteType;
}

fl_FootnoteLayout * fl_DocSectionLayout::getFootnoteLayout(UT_uint32 pid)
{
	fl_ContainerLayout * pCL = getFirstLayout();
	fl_FootnoteLayout * pFL = NULL;
	bool bFound = false;
	while(pCL && !bFound)
	{
		if(pCL->getContainerType() == FL_CONTAINER_FOOTNOTE)
		{
			pFL = (fl_FootnoteLayout *) pCL;
			if(pFL->getFootnotePID() == pid)
			{
				bFound = true;
				break;
			}
		}
		pCL = pCL->getNext();
	}
	if(bFound)
	{
		return pFL;
	}
	return NULL;
}
			
void fl_DocSectionLayout::setHdrFtr(HdrFtrType iType, fl_HdrFtrSectionLayout* pHFSL)
{
	if(pHFSL == NULL)
	{
		switch (iType)
		{
		case FL_HDRFTR_HEADER:
			m_pHeaderSL = pHFSL; break;
		case FL_HDRFTR_HEADER_EVEN:
			m_pHeaderEvenSL = pHFSL; break;
		case FL_HDRFTR_HEADER_FIRST:
			m_pHeaderFirstSL = pHFSL; break;
		case FL_HDRFTR_HEADER_LAST:
			m_pHeaderLastSL = pHFSL; break;
		case FL_HDRFTR_FOOTER:
			m_pFooterSL = pHFSL; break;
		case FL_HDRFTR_FOOTER_EVEN:
			m_pFooterEvenSL = pHFSL; break;
		case FL_HDRFTR_FOOTER_FIRST:
			m_pFooterFirstSL = pHFSL; break;
		case FL_HDRFTR_FOOTER_LAST:
			m_pFooterLastSL = pHFSL; break;
		case FL_HDRFTR_NONE:
			UT_ASSERT(UT_SHOULD_NOT_HAPPEN); break;
		}
		checkAndRemovePages();
		return;
	}
	const char* pszID = pHFSL->getAttribute("id");

	const char* pszAtt = NULL;

	pszAtt = getAttribute("header");
	if (pszAtt && (0 == UT_stricmp(pszAtt, pszID)) )
	{
		m_pHeaderSL = pHFSL;
		checkAndRemovePages();
		return;
	}

	pszAtt = getAttribute("header-even");
	if (pszAtt && (0 == UT_stricmp(pszAtt, pszID)) )
	{
		m_pHeaderEvenSL = pHFSL;
		checkAndRemovePages();
		return;
	}

	pszAtt = getAttribute("header-first");
	if (pszAtt && (0 == UT_stricmp(pszAtt, pszID)) )
	{
		m_pHeaderFirstSL = pHFSL;
		checkAndRemovePages();
		return;
	}

	pszAtt = getAttribute("header-last");
	if (pszAtt && (0 == UT_stricmp(pszAtt, pszID)) )
	{
		m_pHeaderLastSL = pHFSL;
		checkAndRemovePages();
		return;
	}

	pszAtt = getAttribute("footer");
	if (pszAtt && (0 == UT_stricmp(pszAtt, pszID))	)
	{
		m_pFooterSL = pHFSL;
		checkAndRemovePages();
		return;
	}

	pszAtt = getAttribute("footer-even");
	if (pszAtt && (0 == UT_stricmp(pszAtt, pszID))	)
	{
		m_pFooterEvenSL = pHFSL;
		checkAndRemovePages();
		return;
	}

	pszAtt = getAttribute("footer-first");
	if (pszAtt && (0 == UT_stricmp(pszAtt, pszID))	)
	{
		m_pFooterFirstSL = pHFSL;
		checkAndRemovePages();
		return;
	}

	pszAtt = getAttribute("footer-last");
	if (pszAtt && (0 == UT_stricmp(pszAtt, pszID))	)
	{
		m_pFooterLastSL = pHFSL;
		checkAndRemovePages();
		return;
	}

	UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
}

fl_HdrFtrSectionLayout*   fl_DocSectionLayout::getHeader(void)
{
	return m_pHeaderSL;
}

fl_HdrFtrSectionLayout*   fl_DocSectionLayout::getFooter(void)
{
	return m_pFooterSL;
}


fl_HdrFtrSectionLayout*   fl_DocSectionLayout::getHeaderEven(void)
{
	return m_pHeaderEvenSL;
}

fl_HdrFtrSectionLayout*   fl_DocSectionLayout::getFooterEven(void)
{
	return m_pFooterEvenSL;
}


fl_HdrFtrSectionLayout*   fl_DocSectionLayout::getHeaderFirst(void)
{
	return m_pHeaderFirstSL;
}

fl_HdrFtrSectionLayout*   fl_DocSectionLayout::getFooterFirst(void)
{
	return m_pFooterFirstSL;
}


fl_HdrFtrSectionLayout*   fl_DocSectionLayout::getHeaderLast(void)
{
	return m_pHeaderLastSL;
}

fl_HdrFtrSectionLayout*   fl_DocSectionLayout::getFooterLast(void)
{
	return m_pFooterLastSL;
}

void fl_DocSectionLayout::setEndnote(fl_DocSectionLayout* pEndnoteSL)
{
	UT_ASSERT(getType() == FL_SECTION_DOC);
	m_pEndnoteSL = pEndnoteSL;
}

fl_DocSectionLayout* fl_DocSectionLayout::getEndnote(void)
{
	UT_ASSERT(getType() == FL_SECTION_DOC);
	return m_pEndnoteSL;
}

void fl_DocSectionLayout::setEndnoteOwner(fl_DocSectionLayout* pDSL)
{
	UT_ASSERT(getType() == FL_SECTION_ENDNOTE);
	m_pEndnoteOwnerSL = pDSL;
}

fl_DocSectionLayout* fl_DocSectionLayout::getEndnoteOwner(void)
{
	UT_ASSERT(getType() == FL_SECTION_ENDNOTE);
	return m_pEndnoteOwnerSL;
}

fp_Container* fl_DocSectionLayout::getFirstContainer() const
{
	return m_pFirstColumn;
}

fp_Container* fl_DocSectionLayout::getLastContainer() const
{
	return m_pLastColumn;
}

void fl_DocSectionLayout::setFirstContainer(fp_Container * pCon)
{
	UT_DEBUGMSG(("docSectionLayout: DocSec %x First container set to %x \n",this,pCon));
	m_pFirstColumn = (fp_Column *) pCon;
}


void fl_DocSectionLayout::setLastContainer(fp_Container * pCon)
{
	m_pLastColumn = (fp_Column *) pCon;
}

/*!
  Create new container
  \return The newly created container

  This creates a new column or row of same.

*/
fp_Container* fl_DocSectionLayout::getNewContainer(fp_Container * pFirstContainer)
{
	fp_Page* pPage = NULL;
	fp_Column* pLastColumn = (fp_Column*) getLastContainer();
	fp_Column* pAfterColumn = NULL;
	UT_sint32 iNextCtrHeight = 0;

	if (pLastColumn)
	{
		fp_Container * prevContainer = NULL;
		fp_Page* pTmpPage = NULL;
		UT_sint32 pageHeight = 0;
		pTmpPage = pLastColumn->getPage();
		iNextCtrHeight = 0;
		if(pFirstContainer != NULL)
		{
			prevContainer = (fp_Container *) pFirstContainer->getPrevContainerInSection();
		}
//
// Calculate from the page height up to prevContainer
//
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
		pageHeight = pTmpPage->getFilledHeightInLayoutUnits(prevContainer);
#else
		pageHeight = pTmpPage->getFilledHeight(prevContainer);
#endif

		if(pFirstContainer != NULL)
		{
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
			iNextCtrHeight = pFirstContainer->getHeightInLayoutUnits();
#else
			iNextCtrHeight = pFirstContainer->getHeight();
#endif
		}
		else if( pLastColumn->getLastContainer())
		{
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
			iNextCtrHeight = pLastColumn->getLastContainer()->getHeightInLayoutUnits();
#else
			iNextCtrHeight = pLastColumn->getLastContainer()->getHeight();
#endif
		}
		else
		{
			iNextCtrHeight =12*14; // approximately one average line
		}
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
		UT_sint32 avail =  pTmpPage->getAvailableHeightInLayoutUnits();
#else
		UT_sint32 avail =  pTmpPage->getAvailableHeight();
#endif

		UT_sint32 newHeight = pageHeight+ 3*iNextCtrHeight;
		xxx_UT_DEBUGMSG(("SEVIOR: Pageheight =%d nextlineheight =%d newheight = %d availableheight =%d linepos %d \n",pageHeight,iNextCtrHeight,newHeight,avail));
		if( newHeight  >= avail || pFirstContainer == NULL)
		{
			xxx_UT_DEBUGMSG(("SEVIOR: Container on new page \n"));
			if (pTmpPage->getNext())
			{
				pPage = pTmpPage->getNext();
			}
			else
			{
				pPage = m_pLayout->addNewPage(this);
			}
		}
		else
		{
			xxx_UT_DEBUGMSG(("SEVIOR: Container on current page \n"));
			pPage = pTmpPage;
			if(prevContainer == NULL)
			{
				pAfterColumn = pPage->getNthColumnLeader(pPage->countColumnLeaders()-1);
			}
			else
			{
				pAfterColumn = static_cast<fp_Column *>(prevContainer->getContainer())->getLeader();
			}

		}
	}
	else
	{
		// We currently have no columns in this section.  Time to
		// create some.  If there is a previous section, then we need
		// to start our section right after that one.  If not, then we
		// start our section on the first page.  If there is no first
		// page, then we need to create one.
		fl_DocSectionLayout* pPrevSL = getPrevDocSection();
		if (pPrevSL)
		{
//
// This should make sure the last column in the previous section  has it's last container
// on a sane page.
//

#if 0
			//
			// Sevior this code should not be needed!
			//
			UT_DEBUGMSG(("code sez: this code should not be needed!\n"));
			UT_ASSERT(0);

			// says not needed, but clearly still is
#endif
			fp_Column * pPrevCol = (fp_Column *) pPrevSL->getLastContainer();
			while(pPrevCol == NULL)
			{
				UT_DEBUGMSG(("BUG! BUG! Prev section has no last container! Attempting to fix this \n"));
				pPrevSL->format();
			    pPrevCol = (fp_Column *) pPrevSL->getLastContainer();
			}
			fp_Page* pTmpPage = pPrevSL->getLastContainer()->getPage();
			fp_Container * prevContainer = NULL;
			if(pFirstContainer != NULL)
			{
				prevContainer = (fp_Container *) pFirstContainer->getPrevContainerInSection();
			}

#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
			UT_sint32 pageHeight = pTmpPage->getFilledHeightInLayoutUnits(prevContainer);
#else
			UT_sint32 pageHeight = pTmpPage->getFilledHeight(prevContainer);
#endif
			if(pFirstContainer != NULL)
			{
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
				iNextCtrHeight = pFirstContainer->getHeightInLayoutUnits();
#else
				iNextCtrHeight = pFirstContainer->getHeight();
#endif
			}
			else if(pPrevCol->getLastContainer())
			{
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
				iNextCtrHeight = pPrevCol->getLastContainer()->getHeightInLayoutUnits();
#else
				iNextCtrHeight = pPrevCol->getLastContainer()->getHeight();
#endif
			}
			else
			{
				iNextCtrHeight = 12*14; //average height!
			}
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
			bool bForce = (pageHeight + 2*iNextCtrHeight) >= pTmpPage->getAvailableHeightInLayoutUnits();
#else
			bool bForce = (pageHeight + 2*iNextCtrHeight) >= pTmpPage->getAvailableHeight();
#endif
			if (m_bForceNewPage || bForce)
			{
				if (pTmpPage->getNext())
				{
					pPage = pTmpPage->getNext();
				}
				else
				{
					pPage = m_pLayout->addNewPage(this);
				}
			}
			else
			{
				pPage = pTmpPage;
#if 0 // This fixes bug 966 but introduces new problems - jskov 2001.06.10
				pAfterColumn = pPrevCol;
#else
				if(prevContainer == NULL)
				{
					pAfterColumn = pPage->getNthColumnLeader(pPage->countColumnLeaders()-1);
				}
				else
				{
					pAfterColumn = static_cast<fp_Column *>(prevContainer->getContainer())->getLeader();
				}
#endif
			}
		}
		else
		{
			if (m_pLayout->countPages() > 0)
			{
				pPage = m_pLayout->getFirstPage();
			}
			else
			{
				pPage = m_pLayout->addNewPage(this,true);
			}
		}
	}

	UT_ASSERT(pPage);

	// Create row of columns
	fp_Column* pLeaderColumn = NULL;
	fp_Column* pTail = NULL;
	UT_uint32 i = 0;
	for (i=0; i<m_iNumColumns; i++)
	{
		fp_Column* pCol = new fp_Column(this);
		if (pTail)
		{
			pCol->setLeader(pLeaderColumn);
			pTail->setFollower(pCol);
			pTail->setNext(pCol);
			pCol->setPrev(pTail);

			pTail = pCol;
		}
		else
		{
			pLeaderColumn = pTail = pCol;
			pLeaderColumn->setLeader(pLeaderColumn);
		}
	}

	// Append added columns to any previous columns in this section.
	if (m_pLastColumn)
	{
		UT_ASSERT(m_pFirstColumn);

		m_pLastColumn->setNext(pLeaderColumn);
		pLeaderColumn->setPrev(m_pLastColumn);
	}
	else
	{
		UT_ASSERT(!m_pFirstColumn);
		UT_ASSERT(pLeaderColumn);
		m_pFirstColumn = pLeaderColumn;
	}

	// Find last added column and set that as the last in the section.
	fp_Column* pLastNewCol = pLeaderColumn;
	while (pLastNewCol->getFollower())
	{
		pLastNewCol = pLastNewCol->getFollower();
	}
	m_pLastColumn = pLastNewCol;
	UT_ASSERT(!(m_pLastColumn->getNext()));
	UT_ASSERT(!(m_pLastColumn->getFollower()));

	pPage->insertColumnLeader(pLeaderColumn, pAfterColumn);

	fp_Column* pTmpCol = pLeaderColumn;
	i = 0;
 	while (pTmpCol)
	{
		UT_ASSERT(pTmpCol->getPage());

		pTmpCol = pTmpCol->getFollower();
		i++;
	}

	return pLeaderColumn;
}

void fl_DocSectionLayout::format(void)
{
	fl_ContainerLayout*	pBL = getFirstLayout();
	FV_View * pView = m_pLayout->getView();

	bool bShowHidden = pView && pView->getShowPara();
	FPVisibility eHidden;
	bool bHidden;

	while (pBL)
	{
		eHidden  = pBL->isHidden();
		bHidden = ((eHidden == FP_HIDDEN_TEXT && !bShowHidden)
		              || eHidden == FP_HIDDEN_REVISION
		              || eHidden == FP_HIDDEN_REVISION_AND_TEXT);

		if(!bHidden)
		{
			pBL->format();
			UT_sint32 count = 0;
			while(pBL->getLastContainer() == NULL || pBL->getFirstContainer()==NULL)
			{
				UT_DEBUGMSG(("Error formatting a block try again \n"));
				count = count + 1;
				pBL->format();
				if(count > 3)
				{
					UT_DEBUGMSG(("Give up trying to format. Hope for the best :-( \n"));
					break;
				}
			}
		}

		pBL = pBL->getNext();
	}

	m_ColumnBreaker.breakSection(this);
	m_bNeedsFormat = false;
}

void fl_DocSectionLayout::markAllRunsDirty(void)
{
	fl_ContainerLayout*	pBL = getFirstLayout();
	while (pBL)
	{
		pBL->markAllRunsDirty();
		pBL = pBL->getNext();
	}
	if(m_pHeaderSL)
	{
		m_pHeaderSL->markAllRunsDirty();
	}
	if(m_pHeaderEvenSL)
	{
		m_pHeaderEvenSL->markAllRunsDirty();
	}
	if(m_pHeaderFirstSL)
	{
		m_pHeaderFirstSL->markAllRunsDirty();
	}
	if(m_pHeaderLastSL)
	{
		m_pHeaderLastSL->markAllRunsDirty();
	}
	if(m_pFooterSL)
	{
		m_pFooterSL->markAllRunsDirty();
	}
	if(m_pFooterEvenSL)
	{
		m_pFooterEvenSL->markAllRunsDirty();
	}
	if(m_pFooterFirstSL)
	{
		m_pFooterFirstSL->markAllRunsDirty();
	}
	if(m_pFooterLastSL)
	{
		m_pFooterLastSL->markAllRunsDirty();
	}
}

void fl_DocSectionLayout::updateLayout(void)
{
	fl_ContainerLayout*	pBL = getFirstLayout();
	FV_View * pView = m_pLayout->getView();

	bool bShowHidden = pView && pView->getShowPara();
	FPVisibility eHidden;
	bool bHidden;
	while (pBL)
	{
		eHidden  = pBL->isHidden();
		bHidden = ((eHidden == FP_HIDDEN_TEXT && !bShowHidden)
		              || eHidden == FP_HIDDEN_REVISION
		              || eHidden == FP_HIDDEN_REVISION_AND_TEXT);

 		if(!bHidden)
 		{
 			if (pBL->needsReformat())
			{
				pBL->format();
			}
			if (pBL->getContainerType() != FL_CONTAINER_BLOCK && !getDocument()->isDontImmediateLayout())
			{
				xxx_UT_DEBUGMSG(("updateDocSecLayout calling table update \n"));
				pBL->updateLayout();
			}
		}

		pBL = pBL->getNext();
	}
	if(needsSectionBreak())
	{
		m_ColumnBreaker.breakSection(this);
//		UT_ASSERT(!needsSectionBreak());
	}
	if(needsRebuild())
	{
//		UT_ASSERT(0);
		checkAndRemovePages();
		addValidPages();
	}
}

void fl_DocSectionLayout::setNeedsSectionBreak(bool bSet, fp_Page * pPage)
{
	m_bNeedsSectionBreak = bSet;
	fp_Page * pOldP = m_ColumnBreaker.getStartPage();
    UT_sint32 iOldP = 999999999;
	if(pPage == NULL)
	{
		m_ColumnBreaker.setStartPage(pPage);
		return;
	}	
	if(pPage->getOwningSection() != this)
	{
		m_ColumnBreaker.setStartPage(NULL);
		return;
	}	
	if(pOldP)
	{
		iOldP = getDocLayout()->findPage(pOldP);
	}
	UT_sint32 iNewP = getDocLayout()->findPage(pPage);
	xxx_UT_DEBUGMSG(("setNeedsSectionBreak: new Page %d OldPage %d \n",iNewP,iOldP));	
	if( (iNewP > -1) && (iNewP < iOldP))
	{
		xxx_UT_DEBUGMSG(("setNeedsSectionBreak: Rebuild from Page %x \n",pPage));	
		m_ColumnBreaker.setStartPage(pPage);
	}
}

void fl_DocSectionLayout::completeBreakSection(void)
{
	m_bNeedsSectionBreak = true;
	m_ColumnBreaker.setStartPage(NULL);
	m_ColumnBreaker.breakSection(this);
	m_bNeedsSectionBreak = false;
}

void fl_DocSectionLayout::redrawUpdate(void)
{
	fl_ContainerLayout*	pBL = getFirstLayout();

	// we only need to break and redo this section if its contents
	// have changed, i.e., if the field values changed
	
	while (pBL)
	{
		if(pBL->getContainerType() == FL_CONTAINER_BLOCK && static_cast<fl_BlockLayout *>(pBL)->hasUpdatableField())
		{
			bool bReformat = pBL->recalculateFields(getDocLayout()->getRedrawCount());
			if(bReformat)
			{
				pBL->format();
			}
		}
		if (pBL->needsRedraw())
		{
			pBL->redrawUpdate();
		}

		pBL = pBL->getNext();
	}

	if(needsSectionBreak() || needsRebuild())
	{
		m_ColumnBreaker.breakSection(this);
	
		if(needsRebuild())
		{
//			UT_ASSERT(0);
			checkAndRemovePages();
			addValidPages();
		}
	}
}

bool fl_DocSectionLayout::doclistener_changeStrux(const PX_ChangeRecord_StruxChange * pcrxc)
{
	UT_ASSERT(pcrxc->getType()==PX_ChangeRecord::PXT_ChangeStrux);


	setAttrPropIndex(pcrxc->getIndexAP());
	return true;
}

void fl_DocSectionLayout::updateDocSection(void)
{

	const PP_AttrProp* pAP = NULL;
	bool bres = m_pDoc->getAttrProp(m_apIndex, &pAP);
	UT_ASSERT(bres);


	const XML_Char* pszSectionType = NULL;
	pAP->getAttribute("type", pszSectionType);

	_lookupProperties();

	// clear all the columns
    // Assume that all columns and formatting have already been removed via a collapseDocSection()
    //

	/*
	  TODO to more closely mirror the architecture we're using for BlockLayout, this code
	  should probably just set a flag, indicating the need to reformat this section.  Then,
	  when it's time to update everything, we'll actually do the format.
	*/

	FV_View * pView = m_pLayout->getView();
	if(pView)
	{
		pView->setScreenUpdateOnGeneralUpdate(false);
	}

	format();
	updateBackgroundColor();
	checkAndRemovePages();
	formatAllHdrFtr();
	if (m_pEndnoteSL)
	{
		m_pEndnoteSL->format();
	}
	markAllRunsDirty();

	if(pView)
	{
		pView->setScreenUpdateOnGeneralUpdate(true);
	}

//	if (pView)
//	{
//		pView->updateScreen(false);
//		pView->notifyListeners(AV_CHG_TYPING | AV_CHG_FMTSECTION);
//	}

	return;
}

void fl_DocSectionLayout::_lookupProperties(void)
{
	const PP_AttrProp* pSectionAP = NULL;

	m_pLayout->getDocument()->getAttrProp(m_apIndex, &pSectionAP);

	/*
	  TODO shouldn't we be using PP_evalProperty like
	  the blockLayout does?

	  Yes, since PP_evalProperty does a fallback to the
	  last-chance defaults, whereas the code below is
	  hard-coding its own defaults.  Bad idea.
	*/

	const char* pszNumColumns = NULL;
	pSectionAP->getProperty("columns", (const XML_Char *&)pszNumColumns);
	if (pszNumColumns && pszNumColumns[0])
	{
		m_iNumColumns = atoi(pszNumColumns);
	}
	else
	{
		m_iNumColumns = 1;
	}

	const char* pszColumnGap = NULL;
	pSectionAP->getProperty("column-gap", (const XML_Char *&)pszColumnGap);
	if (pszColumnGap && pszColumnGap[0])
	{
		m_iColumnGap = m_pLayout->getGraphics()->convertDimension(pszColumnGap);
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
		m_iColumnGapLayoutUnits = UT_convertToLayoutUnits(pszColumnGap);
#endif
	}
	else
	{
		m_iColumnGap = m_pLayout->getGraphics()->convertDimension("0.25in");
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
		m_iColumnGapLayoutUnits = UT_convertToLayoutUnits("0.25in");
#endif
	}

	const char* pszColumnLineBetween = NULL;
	pSectionAP->getProperty("column-line", (const XML_Char *&)pszColumnLineBetween);
	if (pszColumnLineBetween && pszColumnLineBetween[0])
	{
		m_bColumnLineBetween = (strcmp(pszColumnLineBetween, "on") == 0) ? true : false;
	}
	else
	{
		m_bColumnLineBetween = false;
	}

	/* column-order */
	//we use the mechanism used by BlockLayout, since otherwise we
	//cannot recode the default value
	const PP_AttrProp * pSpanAP = NULL;
	const PP_AttrProp * pBlockAP = NULL;

	const char * pszColumnOrder = PP_evalProperty("dom-dir",pSpanAP,pBlockAP,pSectionAP,m_pDoc,false);
    UT_DEBUGMSG(("column order: %s\n", pszColumnOrder));
	if (pszColumnOrder && pszColumnOrder[0])
	{
		m_iColumnOrder = strcmp(pszColumnOrder, "ltr")	? 1 : 0;
	}
	else
	{
		m_iColumnOrder = 0;
	}

	const char* pszSpaceAfter = NULL;
	pSectionAP->getProperty("section-space-after", (const XML_Char *&)pszSpaceAfter);
	if (pszSpaceAfter && pszSpaceAfter[0])
	{
		m_iSpaceAfter = m_pLayout->getGraphics()->convertDimension(pszSpaceAfter);
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
		m_iSpaceAfterLayoutUnits = UT_convertToLayoutUnits(pszSpaceAfter);
#endif
	}
	else
	{
		m_iSpaceAfter = m_pLayout->getGraphics()->convertDimension("0in");
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
		m_iSpaceAfterLayoutUnits = UT_convertToLayoutUnits("0in");
#endif
	}

	const char* pszRestart = NULL;
	pSectionAP->getProperty("section-restart", (const XML_Char *&)pszRestart);
	if (pszRestart && pszRestart[0])
	{
		m_bRestart = (UT_strcmp(pszRestart,"1")==0);
	}
	else
	{
		m_bRestart = false;
	}

	const char* pszRestartValue = NULL;
	pSectionAP->getProperty("section-restart-value", (const XML_Char *&)pszRestartValue);
	if (pszRestartValue && pszRestartValue[0])
	{
		m_iRestartValue = atoi(pszRestartValue);
	}
	else
	{
		m_iRestartValue = 1;
	}

	const char* pszLeftMargin = NULL;
	const char* pszTopMargin = NULL;
	const char* pszRightMargin = NULL;
	const char* pszBottomMargin = NULL;
	const char* pszFooterMargin = NULL;
	const char* pszHeaderMargin = NULL;
	const char* pszMaxColumnHeight = NULL;
	pSectionAP->getProperty("page-margin-left", (const XML_Char *&)pszLeftMargin);
	pSectionAP->getProperty("page-margin-top", (const XML_Char *&)pszTopMargin);
	pSectionAP->getProperty("page-margin-right", (const XML_Char *&)pszRightMargin);
	pSectionAP->getProperty("page-margin-bottom", (const XML_Char *&)pszBottomMargin);
	pSectionAP->getProperty("page-margin-footer", (const XML_Char *&)pszFooterMargin);
	pSectionAP->getProperty("page-margin-header", (const XML_Char *&)pszHeaderMargin);


	const XML_Char * szRulerUnits;
	UT_Dimension dim;
	if (XAP_App::getApp()->getPrefsValue(AP_PREF_KEY_RulerUnits,&szRulerUnits))
		dim = UT_determineDimension(szRulerUnits);
	else
		dim = DIM_IN;

	UT_String defaultMargin;
	switch(dim)
	{
	case DIM_IN:
		defaultMargin = "1.0in";
		break;

	case DIM_CM:
		defaultMargin = "2.54cm";
		break;

	case DIM_PI:
		defaultMargin = "6.0pi";
		break;

	case DIM_PT:
		defaultMargin= "72.0pt";
		break;

	case DIM_MM:
		defaultMargin= "25.4mm";
		break;

		// TODO: PX, and PERCENT
		// let them fall through to the default now
		// and we don't use them anyway
#if 0
	case DIM_PX:
	case DIM_PERCENT:
#endif
	case DIM_none:
	default:
		defaultMargin = "1.0in";	// TODO: what to do with this.
		break;

	}

	if(pszLeftMargin && pszLeftMargin[0])
	{
		m_iLeftMargin = m_pLayout->getGraphics()->convertDimension(pszLeftMargin);
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
		m_iLeftMarginLayoutUnits = UT_convertToLayoutUnits(pszLeftMargin);
#endif
		m_dLeftMarginUserUnits = UT_convertDimensionless(pszLeftMargin);
	}
	else
	{
		m_iLeftMargin = m_pLayout->getGraphics()->convertDimension(defaultMargin.c_str());
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
		m_iLeftMarginLayoutUnits = UT_convertToLayoutUnits(defaultMargin.c_str());
#endif
		m_dLeftMarginUserUnits = UT_convertDimensionless(defaultMargin.c_str());
	}

	if(pszTopMargin && pszTopMargin[0])
	{
		m_iTopMargin = m_pLayout->getGraphics()->convertDimension(pszTopMargin);
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
		m_iTopMarginLayoutUnits = UT_convertToLayoutUnits(pszTopMargin);
#endif
		m_dTopMarginUserUnits = UT_convertDimensionless(pszTopMargin);
	}
	else
	{
		m_iTopMargin = m_pLayout->getGraphics()->convertDimension(defaultMargin.c_str());
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
		m_iTopMarginLayoutUnits = UT_convertToLayoutUnits(defaultMargin.c_str());
#endif
		m_dTopMarginUserUnits = UT_convertDimensionless(defaultMargin.c_str());
	}

	if(pszRightMargin && pszRightMargin[0])
	{
		m_iRightMargin = m_pLayout->getGraphics()->convertDimension(pszRightMargin);
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
		m_iRightMarginLayoutUnits = UT_convertToLayoutUnits(pszRightMargin);
#endif
		m_dRightMarginUserUnits = UT_convertDimensionless(pszRightMargin);
	}
	else
	{
		m_iRightMargin = m_pLayout->getGraphics()->convertDimension(defaultMargin.c_str());
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
		m_iRightMarginLayoutUnits = UT_convertToLayoutUnits(defaultMargin.c_str());
#endif
		m_dRightMarginUserUnits = UT_convertDimensionless(defaultMargin.c_str());
	}

	if(pszBottomMargin && pszBottomMargin[0])
	{
		m_iBottomMargin = m_pLayout->getGraphics()->convertDimension(pszBottomMargin);
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
		m_iBottomMarginLayoutUnits = UT_convertToLayoutUnits(pszBottomMargin);
#endif
		m_dBottomMarginUserUnits = UT_convertDimensionless(pszBottomMargin);
	}
	else
	{
		m_iBottomMargin = m_pLayout->getGraphics()->convertDimension(defaultMargin.c_str());
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
		m_iBottomMarginLayoutUnits = UT_convertToLayoutUnits(defaultMargin.c_str());
#endif
		m_dBottomMarginUserUnits = UT_convertDimensionless(defaultMargin.c_str());
	}

	if(pszFooterMargin && pszFooterMargin[0])
	{
		m_iFooterMargin = m_pLayout->getGraphics()->convertDimension(pszFooterMargin);
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
		m_iFooterMarginLayoutUnits = UT_convertToLayoutUnits(pszFooterMargin);
#endif
		m_dFooterMarginUserUnits = UT_convertDimensionless(pszFooterMargin);
	}
	else
	{
		m_iFooterMargin = m_pLayout->getGraphics()->convertDimension("0.0in");
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
		m_iFooterMarginLayoutUnits = UT_convertToLayoutUnits("0.0in");
#endif
		m_dFooterMarginUserUnits = UT_convertDimensionless("0.0in");
	}

	if(pszHeaderMargin && pszHeaderMargin[0])
	{
		m_iHeaderMargin = m_pLayout->getGraphics()->convertDimension(pszHeaderMargin);
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
		m_iHeaderMarginLayoutUnits = UT_convertToLayoutUnits(pszHeaderMargin);
#endif
		m_dHeaderMarginUserUnits = UT_convertDimensionless(pszHeaderMargin);
	}
	else
	{
		m_iHeaderMargin = m_pLayout->getGraphics()->convertDimension("0.0in");
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
		m_iHeaderMarginLayoutUnits = UT_convertToLayoutUnits("0.0in");
#endif
		m_dHeaderMarginUserUnits = UT_convertDimensionless("0.0in");
	}

	pSectionAP->getProperty("section-max-column-height", (const XML_Char *&)pszMaxColumnHeight);
	if (pszMaxColumnHeight && pszMaxColumnHeight[0])
	{
		m_iMaxSectionColumnHeight = m_pLayout->getGraphics()->convertDimension(pszMaxColumnHeight);
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
		m_iMaxSectionColumnHeightInLayoutUnits = UT_convertToLayoutUnits(pszMaxColumnHeight);
#endif
	}
	else
	{
		m_iMaxSectionColumnHeight = m_pLayout->getGraphics()->convertDimension("0in");
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
		m_iMaxSectionColumnHeightInLayoutUnits = UT_convertToLayoutUnits("0in");
#endif
	}

	const XML_Char * pszFootnoteLine = NULL;
	pSectionAP->getProperty("section-footnote-line-thickness", (const XML_Char *&)pszFootnoteLine);
	if (pszFootnoteLine && pszFootnoteLine[0])
	{
		m_iFootnoteLineThickness = m_pLayout->getGraphics()->convertDimension(pszFootnoteLine);
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
		m_iFootnoteLineThicknessLayoutUnits = UT_convertToLayoutUnits(pszFootnoteLine);
#endif
	}
	else
	{
		m_iFootnoteLineThickness = m_pLayout->getGraphics()->convertDimension("0.005in");
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
		m_iFootnoteLineThicknessLayoutUnits = UT_convertToLayoutUnits("0.005in");
#endif
	}

	const XML_Char * pszFootnoteType = NULL;
	pSectionAP->getProperty("section-footnote-type", (const XML_Char *&)pszFootnoteType);
	if (pszFootnoteType == NULL)
	{
		m_FootnoteType = FOOTNOTE_TYPE_NUMERIC_SQUARE_BRACKETS;
	}
	else if(pszFootnoteType[0] == 0)
	{
		m_FootnoteType = FOOTNOTE_TYPE_NUMERIC_SQUARE_BRACKETS;
	}
	else if(UT_XML_strcmp(pszFootnoteType,"numeric") == 0)
	{
		m_FootnoteType = FOOTNOTE_TYPE_NUMERIC;
	}
	else if(UT_XML_strcmp(pszFootnoteType,"numeric-square-brackets") == 0)
	{
		m_FootnoteType = FOOTNOTE_TYPE_NUMERIC_SQUARE_BRACKETS;
	}
	else if(UT_XML_strcmp(pszFootnoteType,"numeric-paren") == 0)
	{
		m_FootnoteType = FOOTNOTE_TYPE_NUMERIC_PAREN;
	}
	else if(UT_XML_strcmp(pszFootnoteType,"numeric-open-paren") == 0)
	{
		m_FootnoteType = FOOTNOTE_TYPE_NUMERIC_OPEN_PAREN;
	}
	else if(UT_XML_strcmp(pszFootnoteType,"upper") == 0)
	{
		m_FootnoteType = FOOTNOTE_TYPE_UPPER;
	}
	else if(UT_XML_strcmp(pszFootnoteType,"upper-paren") == 0)
	{
		m_FootnoteType = FOOTNOTE_TYPE_UPPER_PAREN;
	}
	else if(UT_XML_strcmp(pszFootnoteType,"upper-paren-open") == 0)
	{
		m_FootnoteType = FOOTNOTE_TYPE_UPPER_OPEN_PAREN;
	}
	else if(UT_XML_strcmp(pszFootnoteType,"lower") == 0)
	{
		m_FootnoteType = FOOTNOTE_TYPE_LOWER;
	}
	else if(UT_XML_strcmp(pszFootnoteType,"lower-paren") == 0)
	{
		m_FootnoteType = FOOTNOTE_TYPE_LOWER_PAREN;
	}
	else if(UT_XML_strcmp(pszFootnoteType,"lower-paren-open") == 0)
	{
		m_FootnoteType = FOOTNOTE_TYPE_LOWER_OPEN_PAREN;
	}
	else if(UT_XML_strcmp(pszFootnoteType,"lower-roman") == 0)
	{
		m_FootnoteType = FOOTNOTE_TYPE_LOWER_ROMAN;
	}
	else if(UT_XML_strcmp(pszFootnoteType,"lower-roman-paren") == 0)
	{
		m_FootnoteType = FOOTNOTE_TYPE_LOWER_ROMAN_PAREN;
	}
	else if(UT_XML_strcmp(pszFootnoteType,"upper-roman") == 0)
	{
		m_FootnoteType = FOOTNOTE_TYPE_UPPER_ROMAN;
	}
	else if(UT_XML_strcmp(pszFootnoteType,"upper-roman-paren") == 0)
	{
		m_FootnoteType = FOOTNOTE_TYPE_UPPER_ROMAN_PAREN;
	}
	else
	{
		m_FootnoteType = FOOTNOTE_TYPE_NUMERIC_SQUARE_BRACKETS;
	}

	setPaperColor();
	m_bForceNewPage = false;
}

UT_sint32 fl_DocSectionLayout::getTopMargin(void) const
{
	return m_iTopMargin;
}

#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
UT_sint32 fl_DocSectionLayout::getTopMarginInLayoutUnits(void) const
{
	return m_iTopMarginLayoutUnits;
}
#endif

UT_sint32 fl_DocSectionLayout::getBottomMargin(void) const
{
	return m_iBottomMargin;
}

#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
UT_sint32 fl_DocSectionLayout::getBottomMarginInLayoutUnits(void) const
{
	return m_iBottomMarginLayoutUnits;
}
#endif

/*!
 * Set the color of the background paper in the following order of precedence
 * 1. If The section level proper "background-color" is present and is
 *    not transparent use that.
 * 2. If this section is being displayed to the screen use the
 *     ColorForTransparency preference item color.
 * 3. Otherwise use white
 */
void fl_DocSectionLayout::setPaperColor(void)
{
	const PP_AttrProp* pSectionAP = NULL;
	m_pLayout->getDocument()->getAttrProp(m_apIndex, &pSectionAP);

	const char* pszClrPaper = NULL;
	pSectionAP->getProperty("background-color", (const XML_Char *&)pszClrPaper);
	FV_View * pView = m_pLayout->getView();
	if(pszClrPaper && UT_strcmp(pszClrPaper,"transparent") != 0)
		UT_parseColor(pszClrPaper,m_clrPaper);
	else if( pView ) /* && pView->getGraphics()->queryProperties(GR_Graphics::DGP_SCREEN) ) */
	{
		XAP_App * pApp = pView->getApp();
		XAP_Prefs * pPrefs = pApp->getPrefs();
		const XML_Char * pszTransparentColor = NULL;
		pPrefs->getPrefsValue((const XML_Char * ) XAP_PREF_KEY_ColorForTransparent,&pszTransparentColor);
		UT_parseColor(pszTransparentColor,m_clrPaper);
	}
	else
	{
		UT_parseColor("ffffff",m_clrPaper);
	}
}

/*!
 * Return a pointer the current background color.
 */
UT_RGBColor * fl_DocSectionLayout::getPaperColor(void)
{
	return &m_clrPaper;
}

/*!
 * Delete Empty Column containers in this section.
 */
void fl_DocSectionLayout::deleteEmptyColumns(void)
{
	fp_Column* pCol = m_pFirstColumn;
	while (pCol)
	{
		if (pCol->getLeader() == pCol)
		{
			fp_Column* pCol2 = pCol;
			bool bAllEmpty = true;
			fp_Column* pLastInGroup = NULL;

			while (pCol2)
			{
				if (!pCol2->isEmpty())
				{
					bAllEmpty = false;
				}

				if (!(pCol2->getFollower()))
				{
					pLastInGroup = pCol2;
				}

				pCol2 = pCol2->getFollower();
			}

			if (bAllEmpty)
			{
				UT_ASSERT(pLastInGroup);
				if(pCol->getPage() != NULL)
				{
					pCol->getPage()->removeColumnLeader(pCol);
				}
				if (pCol == m_pFirstColumn)
				{
					m_pFirstColumn = (fp_Column *) pLastInGroup->getNext();
					UT_ASSERT(m_pFirstColumn);
				}

				if (pLastInGroup == m_pLastColumn)
				{
					m_pLastColumn = (fp_Column *) pCol->getPrev();
				}

				if (pCol->getPrev())
				{
					pCol->getPrev()->setNext(pLastInGroup->getNext());
				}

				if (pLastInGroup->getNext())
				{
					pLastInGroup->getNext()->setPrev(pCol->getPrev());
				}

				fp_Column* pCol3 = pCol;
				pCol = (fp_Column *) pLastInGroup->getNext();
				while (pCol3)
				{
					fp_Column* pNext = pCol3->getFollower();

					delete pCol3;

					pCol3 = pNext;
				}
			}
			else
			{
				pCol = (fp_Column *) pLastInGroup->getNext();
			}
		}
		else
		{
			pCol = (fp_Column *) pCol->getNext();
		}
	}
}

UT_uint32 fl_DocSectionLayout::getNumColumns(void) const
{
	return m_iNumColumns;
}

UT_uint32 fl_DocSectionLayout::getColumnGap(void) const
{
	return m_iColumnGap;
}

#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
UT_uint32 fl_DocSectionLayout::getColumnGapInLayoutUnits(void) const
{
	return m_iColumnGapLayoutUnits;
}
#endif

UT_uint32 fl_DocSectionLayout::getColumnOrder(void) const
{
	return m_iColumnOrder;
}


fl_DocSectionLayout* fl_DocSectionLayout::getNextDocSection(void) const
{
	fl_DocSectionLayout * pSL = (fl_DocSectionLayout *) getNext();
	if(pSL != NULL && pSL->getType()== FL_SECTION_DOC)
		return pSL;
	return NULL;
}

fl_DocSectionLayout* fl_DocSectionLayout::getPrevDocSection(void) const
{
	fl_DocSectionLayout * pSL = (fl_DocSectionLayout *) getPrev();
	while(pSL != NULL && pSL->getType()!= FL_SECTION_DOC)
	{
		pSL = (fl_DocSectionLayout *) pSL->getPrev();
	}
	return pSL;
}

void fl_DocSectionLayout::collapse(void)
{
	UT_DEBUGMSG(("DocSectionLayout: Collapsing all content in %x \n",this));
	fp_Column* pCol = m_pFirstColumn;
	while (pCol)
	{
		pCol->clearScreen();

		pCol = (fp_Column *) pCol->getNext();
	}
	//
	// Clear the header/footers too
	//
	UT_Vector vecHdrFtr;
	getVecOfHdrFtrs( &vecHdrFtr);
	UT_uint32 i = 0;
	fl_HdrFtrSectionLayout * pHdrFtr = NULL;
	for(i = 0; i < vecHdrFtr.getItemCount(); i++)
	{
		pHdrFtr = (fl_HdrFtrSectionLayout *) vecHdrFtr.getNthItem(i);
		pHdrFtr->clearScreen();
	}
	//
	// Collapse the header/footers now
	//
	for(i = 0; i < vecHdrFtr.getItemCount(); i++)
	{
		pHdrFtr = (fl_HdrFtrSectionLayout *) vecHdrFtr.getNthItem(i);
		pHdrFtr->collapse();
	}
	// remove all the columns from their pages
	pCol = m_pFirstColumn;
	while (pCol)
	{
		if (pCol->getLeader() == pCol)
		{
			pCol->getPage()->removeColumnLeader(pCol);
		}

		pCol = (fp_Column *) pCol->getNext();
	}

	// get rid of all the layout information for every block
	fl_ContainerLayout*	pBL = getFirstLayout();
	while (pBL)
	{
		pBL->collapse();
		pBL = pBL->getNext();
	}

	// delete all our columns
	pCol = m_pFirstColumn;
	while (pCol)
	{
		fp_Column* pNext = (fp_Column *) pCol->getNext();
		delete pCol;
		pCol = pNext;
	}
	m_pFirstColumn = NULL;
	m_pLastColumn = NULL;

//
// Remove all the empty pages thus created. Don't notify of the deletion though.
//
	getDocLayout()->deleteEmptyPages(true);
//
// This Doc Section No longer owns pages so this becomes NULL
//
	m_pFirstOwnedPage = NULL;
}

bool fl_DocSectionLayout::doclistener_deleteStrux(const PX_ChangeRecord_Strux * pcrx)
{
	UT_ASSERT(pcrx->getType()==PX_ChangeRecord::PXT_DeleteStrux);
	UT_ASSERT(pcrx->getStruxType()==PTX_Section || pcrx->getStruxType()==PTX_SectionEndnote);
	UT_DEBUGMSG(("Doing Section delete \n"));
	fl_DocSectionLayout* pPrevSL = getPrevDocSection();
	if (!pPrevSL)
	{
		// TODO shouldn't this just assert?
		UT_DEBUGMSG(("no prior SectionLayout"));
		return false;
	}

	if(m_pEndnoteOwnerSL)
	{
		m_pEndnoteOwnerSL->setEndnote(0);
	}

//
// Collapse previous section too. We need this so it can be rebuilt properly.
//
	pPrevSL->collapse();

	// clear all the columns
	collapse();

	DELETEP(m_pHeaderSL);
	DELETEP(m_pHeaderEvenSL);
	DELETEP(m_pHeaderFirstSL);
	DELETEP(m_pHeaderLastSL);
	DELETEP(m_pFooterSL);
	DELETEP(m_pFooterEvenSL);
	DELETEP(m_pFooterFirstSL);
	DELETEP(m_pFooterLastSL);

//
// Collapse the subsequent sections too. These will be reformatted in a few lines.
//
	fl_DocSectionLayout * pDSL = getNextDocSection();
	while(pDSL != NULL)
	{
		pDSL->collapse();
		pDSL = pDSL->getNextDocSection();
	}
//
// OK set the links and move all blocks in this section into the previous section.
// I know that getFirstLayout isn't set for Endnotes.  Maybe this should be
// fixed. -PL
//
	if (pcrx->getStruxType() != PTX_SectionEndnote)
	{
		fl_ContainerLayout * pBCur = getFirstLayout();
		fl_ContainerLayout * pBPrev = pPrevSL->getLastLayout();
		UT_ASSERT(pBCur && pBPrev);

		pBCur->setPrev(pBPrev);
		pBPrev->setNext(pBCur);
		while(pBCur != NULL)
		{
			xxx_UT_DEBUGMSG(("updating block %x \n",pBCur));
			pBCur->setContainingLayout(pBPrev->myContainingLayout());
			if(pBCur->getContainerType() == FL_CONTAINER_BLOCK)
			{
				static_cast<fl_BlockLayout *>(pBCur)->
					setSectionLayout(pPrevSL);
			}
			pBCur = pBCur->getNext();
		}
		setFirstLayout(NULL);
		setLastLayout(NULL);
	}
//
// Get this before we remove this section from the run list!
//
    pDSL = getNextDocSection();
	m_pLayout->removeSection(this);
	pPrevSL->format();

	FV_View* pView = m_pLayout->getView();
	if (pView)
  	{
  		pView->_setPoint(pcrx->getPosition());
  	}
//
// Update the following sections.
//
	while(pDSL != NULL)
	{
		pDSL->updateDocSection();
		pDSL = pDSL->getNextDocSection();
	}
	delete this;			// TODO whoa!  this construct is VERY dangerous.

	return true;
}

void fl_DocSectionLayout::addOwnedPage(fp_Page* pPage)
{
	// TODO do we really need the vecOwnedPages member? YES!!!

	if(m_pFirstOwnedPage == NULL)
		m_pFirstOwnedPage = pPage;
	fp_Page * pPrev = m_pFirstOwnedPage;

//
// The addPage methods will add the page to the correct HdrFtrSL.
//
	UT_Vector vecHdrFtr;
	getVecOfHdrFtrs( &vecHdrFtr);
	UT_uint32 i = 0;
	for(i = 0; i < vecHdrFtr.getItemCount(); i++)
	{
		fl_HdrFtrSectionLayout * pHdrFtr = (fl_HdrFtrSectionLayout *) vecHdrFtr.getNthItem(i);
		if(pHdrFtr->getHFType() < FL_HDRFTR_FOOTER)
		{
			if(pPrev && pPrev->getOwningSection() == this && pPrev->getHdrFtrP(FL_HDRFTR_HEADER) == NULL )
				prependOwnedHeaderPage(pPrev);

			pHdrFtr->addPage(pPage);
		}
		else
		{
			if(pPrev && pPrev->getOwningSection() == this && pPrev->getHdrFtrP(FL_HDRFTR_FOOTER) == NULL)
			{
				prependOwnedFooterPage(pPrev);
			}
			pHdrFtr->addPage(pPage);
		}
	}
	fl_DocSectionLayout * pDSL = this;
	while(pDSL != NULL)
	{
		pDSL->checkAndRemovePages();
		pDSL->addValidPages();
		pDSL = pDSL->getNextDocSection();
	}
}

void fl_DocSectionLayout::prependOwnedHeaderPage(fp_Page* pPage)
{
	//
	// Skip back through the pages until the first owned page of this section
	//
	fp_Page * pPrev = pPage->getPrev();
	if(pPrev && pPrev->getOwningSection() == this && pPrev->getHdrFtrP(FL_HDRFTR_HEADER) == NULL)
	{
		prependOwnedHeaderPage(pPrev);
	}
//
// The addPage methods will add the page to the correct HdrFtrSL.
//
	UT_Vector vecHdrFtr;
	getVecOfHdrFtrs( &vecHdrFtr);
	UT_uint32 i = 0;
	for(i = 0; i < vecHdrFtr.getItemCount(); i++)
	{
		fl_HdrFtrSectionLayout * pHdrFtr = (fl_HdrFtrSectionLayout *) vecHdrFtr.getNthItem(i);
		if(pHdrFtr->getHFType() < FL_HDRFTR_FOOTER)
		{
			xxx_UT_DEBUGMSG(("SEVIOR: prepending page %x \n",pPage));
			pHdrFtr->addPage(pPage);
		}
	}
}


void fl_DocSectionLayout::prependOwnedFooterPage(fp_Page* pPage)
{
	//
	// Skip back through the pages until the first owned page of this section
	//
	fp_Page * pPrev = pPage->getPrev();
	if(pPrev && pPrev->getOwningSection() == this && pPrev->getHdrFtrP(FL_HDRFTR_FOOTER) == NULL)
	{
		prependOwnedFooterPage(pPrev);
	}
//
// The addPage methods will add the page to the correct HdrFtrSL.
//
	UT_Vector vecHdrFtr;
	getVecOfHdrFtrs( &vecHdrFtr);
	UT_uint32 i = 0;
	for(i = 0; i < vecHdrFtr.getItemCount(); i++)
	{
		fl_HdrFtrSectionLayout * pHdrFtr = (fl_HdrFtrSectionLayout *) vecHdrFtr.getNthItem(i);
		if(pHdrFtr->getHFType() >= FL_HDRFTR_FOOTER)
		{
			pHdrFtr->addPage(pPage);
		}
	}
}


/*!
 * This fills a vector with all the valid header/footers.
 */
void fl_DocSectionLayout::getVecOfHdrFtrs(UT_Vector * vecHdrFtr)
{
	vecHdrFtr->clear();
	if (m_pHeaderFirstSL != NULL)
	{
		vecHdrFtr->addItem((void *) m_pHeaderFirstSL);
	}
	if (m_pHeaderLastSL  != NULL)
	{
		vecHdrFtr->addItem((void *) m_pHeaderLastSL);
	}
	if (m_pHeaderEvenSL  != NULL)
	{
		vecHdrFtr->addItem((void *) m_pHeaderEvenSL);
	}
	if (m_pHeaderSL  != NULL)
	{
		vecHdrFtr->addItem((void *) m_pHeaderSL);
	}
	if (m_pFooterFirstSL != NULL)
	{
		vecHdrFtr->addItem((void *) m_pFooterFirstSL);
	}
	if (m_pFooterLastSL != NULL)
	{
		vecHdrFtr->addItem((void *) m_pFooterLastSL);
	}
	if (m_pFooterEvenSL != NULL)
	{
		vecHdrFtr->addItem((void *) m_pFooterEvenSL);
	}
	if (m_pFooterSL != NULL)
	{
		vecHdrFtr->addItem((void *) m_pFooterSL);
	}
}

/*!
 * This method formats all the header/footers
 */
void fl_DocSectionLayout::formatAllHdrFtr(void)
{
	xxx_UT_DEBUGMSG(("SEVIOR: Doing formatAllHdrFtr \n"));
	UT_Vector vecHdrFtr;
	getVecOfHdrFtrs( &vecHdrFtr);
	UT_uint32 i = 0;
	for(i = 0; i < vecHdrFtr.getItemCount(); i++)
	{
		fl_HdrFtrSectionLayout * pHdrFtr = (fl_HdrFtrSectionLayout *) vecHdrFtr.getNthItem(i);
		xxx_UT_DEBUGMSG(("SEVIOR: Doing formatting %x in formatAllHdrFtr \n",pHdrFtr));
		pHdrFtr->format();
	}
}

/*!
 * This method checks each header for valid pages and removes the page if it's not
 * valid. ie it remove odd pages from even headers etc.
 */
void fl_DocSectionLayout::checkAndRemovePages(void)
{
	UT_Vector vecHdrFtr;
	getVecOfHdrFtrs( &vecHdrFtr);
	UT_uint32 i = 0;
	for(i = 0; i < vecHdrFtr.getItemCount(); i++)
	{
		fl_HdrFtrSectionLayout * pHdrFtr = (fl_HdrFtrSectionLayout *) vecHdrFtr.getNthItem(i);
		pHdrFtr->checkAndRemovePages();
	}
}


/*!
 * This method adds valid pages to every valid header/footer in the docsection if
 * they're not there already.
 */
void fl_DocSectionLayout::addValidPages(void)
{
	UT_Vector vecHdrFtr;
	getVecOfHdrFtrs( &vecHdrFtr);
	UT_uint32 i = 0;
	for(i = 0; i < vecHdrFtr.getItemCount(); i++)
	{
		fl_HdrFtrSectionLayout * pHdrFtr = (fl_HdrFtrSectionLayout *) vecHdrFtr.getNthItem(i);
		pHdrFtr->addValidPages();
	}
}

/*!
 * This method deletes the owned page from the DocSectionLayout and all
 * the header files.
 */
void fl_DocSectionLayout::deleteOwnedPage(fp_Page* pPage, bool bReallyDeleteIt)
{
	UT_Vector vecHdrFtr;
	getVecOfHdrFtrs( &vecHdrFtr);
	UT_uint32 i = 0;
	for(i = 0; i < vecHdrFtr.getItemCount(); i++)
	{
		fl_HdrFtrSectionLayout * pHdrFtr = (fl_HdrFtrSectionLayout *) vecHdrFtr.getNthItem(i);
		if(pHdrFtr->isPageHere(pPage))
		{
			pHdrFtr->deletePage(pPage);
		}
	}
//
// Remove this page from the list of owned pages
//
	if(m_pFirstOwnedPage == pPage)
	{
		fp_Page * pNext = pPage->getNext();
		if(pNext && pNext->getOwningSection() == this)
		{
			m_pFirstOwnedPage = pNext;
		}
		else
		{
			m_pFirstOwnedPage = NULL;
		}
	}
	fl_DocSectionLayout * pDSL = this;
	if(!getDocLayout()->isLayoutDeleting() && bReallyDeleteIt)
	{
		UT_sint32 i = m_pLayout->findPage(pPage);
		if(i>0)
		{
			UT_DEBUGMSG(("fl_DocSec: deleting page %x ReallyDeleteIt %d \n",pPage,bReallyDeleteIt));
			m_pLayout->deletePage(pPage,true);
		}
		while(pDSL != NULL)
		{
			pDSL->checkAndRemovePages();
			pDSL->addValidPages();
			pDSL = pDSL->getNextDocSection();
		}
	}
}

/*!
 * This method returns true if the pPage pointer matches the header/footer type
 * given.
\param hfType The type of the header/Footer
\param fp_Page * pThisPage pointer to the page queried.
 */
bool fl_DocSectionLayout::isThisPageValid(HdrFtrType hfType, fp_Page * pThisPage)
{
	if (!m_pFirstOwnedPage)
		return false;

    // No header/footerness assigned yet. Page is invalid.
	if(hfType == FL_HDRFTR_NONE)
		return false;

	if(hfType == FL_HDRFTR_HEADER_FIRST ||
	   hfType == FL_HDRFTR_FOOTER_FIRST)
		return (pThisPage == m_pFirstOwnedPage);

//
// If there is a header page defined and this is a header page bail now!
//
	if ((pThisPage == m_pFirstOwnedPage) &&
		 ((m_pHeaderFirstSL && hfType < FL_HDRFTR_FOOTER) ||
		  (m_pFooterFirstSL && hfType >= FL_HDRFTR_FOOTER)))
		return false;

	fp_Page * pPage = m_pFirstOwnedPage;
	fp_Page * pNext = pPage->getNext();
	while(pNext && (pNext->getOwningSection() == this))
	{
		pPage = pNext;
		pNext = pNext->getNext();
	}

	if(hfType == FL_HDRFTR_HEADER_LAST ||
	   hfType == FL_HDRFTR_FOOTER_LAST)
	{
		return (pPage == pThisPage);
	}
//
// If there is a Last SL defined and this is the last page in the SLpage bail now!
//
	if ((pThisPage == pPage) &&
		 ((m_pHeaderLastSL && hfType < FL_HDRFTR_FOOTER) ||
		  (m_pFooterLastSL && hfType >= FL_HDRFTR_FOOTER)))
		return false;

	UT_uint32 i = 0;
	for(i=0; i < getDocLayout()->countPages(); i++)
	{
		if (getDocLayout()->getNthPage(i) == pThisPage)
			break;
	}

	UT_ASSERT(i < getDocLayout()->countPages());

	if((hfType == FL_HDRFTR_HEADER_EVEN) ||
	   (hfType == FL_HDRFTR_FOOTER_EVEN))
	{
		if(i % 2 == 0)
			return true;
		else
			return false;
	}
//
// If there is an Even SL defined and this is an even page in the SL page bail now!
//
	if ((i % 2 == 0) &&
		((m_pHeaderEvenSL && hfType < FL_HDRFTR_FOOTER) ||
		 (m_pFooterEvenSL && hfType >= FL_HDRFTR_FOOTER)))
		return false;

	return true; //if we're here all pages are valid.
}

void fl_DocSectionLayout::checkAndAdjustColumnGap(UT_sint32 iLayoutWidth)
{
	// Check to make sure column gap is not to wide to fit on the page with the
	// given number of columns.

	if(m_iNumColumns > 1)
	{
		UT_sint32 minColumnWidth = m_pLayout->getGraphics()->convertDimension("0.5in");	//TODO should this dimension be hard coded.
		UT_sint32 iColWidth = (iLayoutWidth - (UT_sint32)(((m_iNumColumns - 1) * m_iColumnGap))) / (UT_sint32)m_iNumColumns;

		if(iColWidth < minColumnWidth)
		{
			m_iColumnGap = (iLayoutWidth - minColumnWidth * m_iNumColumns) / (m_iNumColumns - 1);
		}

	}

}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

class ABI_EXPORT _PageHdrFtrShadowPair
{
public:
	_PageHdrFtrShadowPair(void)
	   {
			m_pPage = NULL;
			m_pShadow = NULL;
		}
	virtual ~_PageHdrFtrShadowPair(void)
		{
			m_pPage = NULL;
			m_pShadow = NULL;
		}
	void setPage (fp_Page * pPage) { m_pPage = pPage;}
	void setShadow (fl_HdrFtrShadow * pShadow) { m_pShadow = pShadow;}
	fp_Page * getPage(void) const {return m_pPage;}
	fl_HdrFtrShadow * getShadow(void) const {return m_pShadow;}
private:
	fp_Page*			m_pPage;
	fl_HdrFtrShadow*	m_pShadow;
};


fl_HdrFtrSectionLayout::fl_HdrFtrSectionLayout(HdrFtrType iHFType, FL_DocLayout* pLayout, fl_DocSectionLayout* pDocSL, PL_StruxDocHandle sdh, PT_AttrPropIndex indexAP)
	: fl_SectionLayout(pLayout, sdh, indexAP, FL_SECTION_HDRFTR,FL_CONTAINER_HDRFTR,PTX_SectionHdrFtr,pDocSL),
	  m_pDocSL(pDocSL),
	  m_iHFType(iHFType),
	  m_pHdrFtrContainer(NULL)
{
	fl_Layout::setType(PTX_SectionHdrFtr); // Set the type of this strux
	UT_DEBUGMSG(("SEVIOR: Creating HFType =%d \n",m_iHFType));
//
// Since we're almost certainly removing blocks at the end of the doc, tell the
// view to remember the current position on the active view.
//
// 	FV_View * pView = m_pLayout->getView();
// 	if(pView && pView->isActive())
// 	{
// 		pView->markSavedPositionAsNeeded();
// 	}
}

fl_HdrFtrSectionLayout::~fl_HdrFtrSectionLayout()
{
	xxx_UT_DEBUGMSG(("SEVIOR: Deleting HFType =%d \n",m_iHFType));
	UT_uint32 iCount = m_vecPages.getItemCount();
	for (UT_uint32 i=0; i<iCount; i++)
	{
		_PageHdrFtrShadowPair* pPair = (_PageHdrFtrShadowPair*) m_vecPages.getNthItem(i);

		delete pPair->getShadow();
	}
	_purgeLayout();
	DELETEP(m_pHdrFtrContainer);
//
// Take this section layout out of the linked list
//
	m_pLayout->removeHdrFtrSection((fl_SectionLayout *) this);
//
// Null out pointer to this HdrFtrSection in the attached DocLayoutSection
//
	m_pDocSL->setHdrFtr(m_iHFType, NULL);
//
// Since we're almost certainly removing blocks at the end of the doc, tell the
// view to remember the current position on the active view.
//
// 	FV_View * pView = m_pLayout->getView();
// 	if(pView && pView->isActive())
// 	{
// 		pView->markSavedPositionAsNeeded();
// 	}
//
	UT_VECTOR_PURGEALL(_PageHdrFtrShadowPair*, m_vecPages);
}

/*!
 * This method removes all the lines and containers associated with the shadows
 * and the lines associated with this HdrFtrSectionLayout.
 *
 */
void fl_HdrFtrSectionLayout::collapse(void)
{
//
// If a view exists and we're editting a header footer take the pointer out of
// the header/footer. This will also clear the box around the header/footer
//
	FV_View * pView = m_pLayout->getView();
	if(pView && pView->isHdrFtrEdit())
	{
		pView->clearHdrFtrEdit();
		pView->warpInsPtToXY(0,0,false);
		pView->rememberCurrentPosition();
	}

	_localCollapse();
	UT_uint32 iCount = m_vecPages.getItemCount();
	UT_uint32 i;
	for (i=0; i<iCount; i++)
	{
		_PageHdrFtrShadowPair* pPair = (_PageHdrFtrShadowPair*) m_vecPages.getNthItem(i);
		fp_Page * ppPage = pPair->getPage();
		delete pPair->getShadow();
		ppPage->removeHdrFtr(getHFType());
		delete pPair;
	}
	m_vecPages.clear();
	DELETEP(m_pHdrFtrContainer);
}

/*!
 * This method removes the block pBlock from all the shadowLayouts.
 */
void fl_HdrFtrSectionLayout::collapseBlock(fl_ContainerLayout *pBlock)
{
	UT_uint32 iCount = m_vecPages.getItemCount();
	UT_uint32 i;
	for (i=0; i<iCount; i++)
	{
		_PageHdrFtrShadowPair* pPair = (_PageHdrFtrShadowPair*) m_vecPages.getNthItem(i);
		fl_ContainerLayout * pShadowBL = pPair->getShadow()->findMatchingContainer(pBlock);
		UT_ASSERT(pShadowBL);
		if(pShadowBL)
		{
			// In case we've never checked this one
			if(pShadowBL->getContainerType() == FL_CONTAINER_BLOCK)
			{
				m_pLayout->dequeueBlockForBackgroundCheck((fl_BlockLayout *) pShadowBL);
			}
			pPair->getShadow()->remove( pShadowBL);
			delete pShadowBL;
			pPair->getShadow()->format();
		}
	}
}

bool fl_HdrFtrSectionLayout::recalculateFields(UT_uint32 iUpdateCount)
{
	bool bResult = false;

	UT_uint32 iCount = m_vecPages.getItemCount();
	for (UT_uint32 i=0; i<iCount; i++)
	{
		_PageHdrFtrShadowPair* pPair = (_PageHdrFtrShadowPair*) m_vecPages.getNthItem(i);
		UT_ASSERT(pPair->getShadow());
		bResult = pPair->getShadow()->recalculateFields(iUpdateCount) || bResult;
	}
	return bResult;
}


fl_HdrFtrShadow * fl_HdrFtrSectionLayout::getFirstShadow(void)
{
	UT_uint32 iCount = m_vecPages.getItemCount();
	if(iCount != 0)
	{
		_PageHdrFtrShadowPair* pPair = (_PageHdrFtrShadowPair*) m_vecPages.getNthItem(0);
		return pPair->getShadow();
	}
	return NULL;
}

fp_Container* fl_HdrFtrSectionLayout::getFirstContainer() const
{
	return m_pHdrFtrContainer;
}


fp_Container* fl_HdrFtrSectionLayout::getLastContainer() const
{
	return m_pHdrFtrContainer;
}

fp_Container* fl_HdrFtrSectionLayout::getNewContainer(fp_Container * pFirstContainer)
{
	DELETEP(m_pHdrFtrContainer);
	UT_sint32 iWidth = m_pDocSL->getFirstContainer()->getPage()->getWidth(); // why is this different than the next one ?
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
	UT_sint32 iWidthLayout = m_pDocSL->getFirstContainer()->getPage()->getWidthInLayoutUnits() - m_pDocSL->getLeftMarginInLayoutUnits() - m_pDocSL->getRightMarginInLayoutUnits();
	m_pHdrFtrContainer = (fp_Container *) new fp_HdrFtrContainer(iWidth,iWidthLayout, (fl_SectionLayout *) this);
#else
	m_pHdrFtrContainer = (fp_Container *) new fp_HdrFtrContainer(iWidth,0, (fl_SectionLayout *) this);
#endif
	return m_pHdrFtrContainer;
}

bool fl_HdrFtrSectionLayout::isPageHere(fp_Page * pPage)
{
	return (_findShadow(pPage) >=0 );
}

fl_HdrFtrShadow *  fl_HdrFtrSectionLayout::findShadow(fp_Page* pPage)
{
       UT_sint32 iPage = _findShadow(pPage);
       if(iPage < 0)
	        return NULL;
       _PageHdrFtrShadowPair* pPair = (_PageHdrFtrShadowPair*) m_vecPages.getNthItem(iPage);
       return pPair->getShadow();
}

UT_sint32 fl_HdrFtrSectionLayout::_findShadow(fp_Page* pPage)
{
	UT_uint32 iCount = m_vecPages.getItemCount();
	for (UT_uint32 i=0; i<iCount; i++)
	{
		_PageHdrFtrShadowPair* pPair = (_PageHdrFtrShadowPair*) m_vecPages.getNthItem(i);

		if (pPair->getPage() == pPage)
		{
			return i;
		}
	}

	return -1;
}
/*!
 * This method converts a previously existing section to this header/footer.
 * Code liberally stolen from fl_DocSectionLayout::doclistener_deleteStrux
 \param fl_DocSectionLayout * pSL sectionlayout to be converted to a
 *     HdrFtrSectionLayout
*/
void fl_HdrFtrSectionLayout::changeIntoHdrFtrSection( fl_DocSectionLayout * pSL)
{
	fl_DocSectionLayout* pPrevSL = pSL->getPrevDocSection();
	UT_ASSERT(pPrevSL);
	// clear all the columns
	fp_Column* pCol =NULL;

	pCol = (fp_Column *) pSL->getFirstContainer();
	while (pCol)
	{
		pCol->clearScreen();

		pCol = (fp_Column *) pCol->getNext();
	}

	// remove all the columns from their pages
	pCol = (fp_Column *) pSL->getFirstContainer();
	while (pCol)
	{
		if (pCol->getLeader() == pCol)
		{
			pCol->getPage()->removeColumnLeader(pCol);
		}

		pCol = (fp_Column *) pCol->getNext();
	}


	// get rid of all the layout information for every block
	fl_ContainerLayout*	pBL = pSL->getFirstLayout();
	while (pBL)
	{
		pBL->collapse();

		pBL = pBL->getNext();
	}

	//
	// Change the section type
	//

	// transfer the Sections' blocks into this header/footer

	while (pSL->getFirstLayout())
	{
		pBL = pSL->getFirstLayout();
		pSL->remove(pBL);
		add(pBL);
		static_cast<fl_BlockLayout *>(pBL)->setSectionLayout(this);
		static_cast<fl_BlockLayout *>(pBL)->setHdrFtr();
	}
	//
	// Remove old section from the section linked list!!
	//
	m_pLayout->removeSection(pSL);
//
	DELETEP(pSL); // Old Section layout is totally gone
	//
	// Create and Format the shadows
	//
	format();

	// Finished! we now have a header/footer
}

/*!
 * Remove the strux identifing this as a seperate section has been deleted so
 * we have to remove this HdrFtrSectionLayout class and all the shadow sections
 * attached to it. The blocks in this class are moved to the DocSectionLayout
 * associated with this class.
 * I do this because I expect that this will be called as part
 * on an undo "Insert Header" command. The rest of the undo needs blocks to
 * delete so I'm putting them there to keep the rest of the undo code happy
\param pcrx the changerecord identifying this action as necesary.
\returns true
*/
bool fl_HdrFtrSectionLayout::doclistener_deleteStrux(const PX_ChangeRecord_Strux * pcrx)
{
	UT_ASSERT(pcrx->getType()==PX_ChangeRecord::PXT_DeleteStrux);
	UT_ASSERT(pcrx->getStruxType()==PTX_SectionHdrFtr);
//
// Get last doc section. Move all the blocks from here to there after deleting
// this strux.
//
	fl_DocSectionLayout* pPrevSL = m_pDocSL;
	if (!pPrevSL)
	{
		UT_DEBUGMSG(("no prior SectionLayout"));
		UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
	}
//
// Get rid of all the shadows, all the containers, and all the layout
// information for all the blocks.
//
	collapse();
//
// Now copy these line-less blocks into the previous docSectionLayout.
// Note: I expect that these blocks will be deleted by a later delete strux
// on these blocks.
//
	fl_ContainerLayout * pBL = NULL;
	while (getFirstLayout())
	{
		pBL = getFirstLayout();
		remove(pBL);
		pPrevSL->add(pBL);
	}
//
// Format the new section containing the blocks.
//
	pPrevSL->format();
//
// Finally delete this HdrFtrSectionLayout. This could be done the docListener
// class but here I'm following the convention for the DocSectionLayout. It
// works there so I hope it works here. The HdrFtrSection destructor takes care
// of the details of unlinking the section etc.
//
	delete this;
	return true;
}

void fl_HdrFtrSectionLayout::addPage(fp_Page* pPage)
{
//
//  Sevior:
//  This triggers if we're rebuilding a section before page is defined like in a section change
//  strux. Reinstate if needed to find other bugs.
//	UT_ASSERT(0 > _findShadow(pPage));
//
//
// This might actually be called before we have any content to put in it. If so
// return and hope we get called later.
//
	if(getFirstLayout() == NULL)
	{
		UT_DEBUGMSG(("HdrFtr BUG. No content but we're asking to create a shadow !! \n"));
		UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
		return;
	}

	if(_findShadow(pPage) > -1)
		return;
//
// Check this page is valid for this type of hdrftr
//
	if(!getDocSectionLayout()->isThisPageValid(m_iHFType, pPage))
	{
		return;
	}
	//
	// see if this page has a shadow attached already. This can happen
    // is a page goes from being odd to even.
	//
	fp_ShadowContainer* pOldShadow = pPage->getHdrFtrP(m_iHFType);
	//
	// If so remove it.
	//
	if(pOldShadow != NULL)
	{
		pOldShadow->getHdrFtrSectionLayout()->deletePage(pPage);
	}

	_PageHdrFtrShadowPair* pPair = new _PageHdrFtrShadowPair();
	// TODO outofmem
	xxx_UT_DEBUGMSG(("SEVIOR: Add page %x to pair %x \n",pPage,pPair));
	pPair->setPage(pPage);
	pPair->setShadow(new fl_HdrFtrShadow(m_pLayout, pPage, this, m_sdh, m_apIndex));
	//
	// Make sure we register the shadow before populating it.
	//
	m_vecPages.addItem(pPair);
	//
	// Populate the shadow
	//

	fl_ShadowListener* pShadowListener = new fl_ShadowListener(this, pPair->getShadow());
//
// Populate with just this section so find the start and end of it
//
	PT_DocPosition posStart,posEnd,posDocEnd;
	posStart = getFirstLayout()->getPosition(true) - 1;
	posEnd = getLastLayout()->getPosition(false);
	fp_Run * pRun = getLastLayout()->getFirstRun();
	while(pRun->getNext() != NULL)
	{
		pRun = pRun->getNext();
	}
	posEnd += pRun->getBlockOffset();
	PL_StruxDocHandle sdh=NULL;
	bool bres;
	bres = m_pDoc->getStruxOfTypeFromPosition(posEnd, PTX_Block, &sdh);
	m_pDoc->getBounds(true,posDocEnd);
	while(bres && sdh == getLastLayout()->getStruxDocHandle()
		  && posEnd <= posDocEnd)
	{
		posEnd++;
		bres = m_pDoc->getStruxOfTypeFromPosition(posEnd, PTX_Block, &sdh);
	}
	posEnd--;
	UT_ASSERT(posEnd > posStart);
	PD_DocumentRange * docRange = new PD_DocumentRange(m_pDoc,posStart,posEnd);
	m_pDoc->tellListenerSubset(pShadowListener, docRange);
	delete docRange;
	delete pShadowListener;
	markAllRunsDirty();
}

bool fl_HdrFtrSectionLayout::isPointInHere(PT_DocPosition pos)
{
//
// Skip through the Containers in this shadow to find the one containing this
// point.
//
    fl_ContainerLayout*	pBL = getFirstLayout();
	if(pBL == NULL)
		return false;
	if(pos < pBL->getPosition())
	{
//
// This corner case is that pos == position of the HdrFtr strux
//
		if(pos == (pBL->getPosition() - 1))
		{
			return true;
		}
		return false;
	}
//
// OK see if the next hdrftr is ahead of the pos
//
	fl_HdrFtrSectionLayout * pHF = (fl_HdrFtrSectionLayout *) getNext();
	if(pHF == NULL)
	{
		PT_DocPosition posEOD;
		m_pDoc->getBounds(true,posEOD);
		if(pos <= posEOD)
		{
			return true;
		}
		// This happens when you're erasing the last character in the document.
		// Not sure if assert should stay or not.
		UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
		return false;
	}
	fl_ContainerLayout * ppBL = pHF->getFirstLayout();
	if(ppBL != NULL)
	{
		if(pos < (ppBL->getPosition()-1))
		{
			return true;
		}
		return false;
	}

	fl_ContainerLayout* pNext = pBL->getNext();
	while(pNext != NULL && pNext->getPosition( true) < pos)
	{
		pBL = pNext;
		pNext = pNext->getNext();
	}
	if(pNext != NULL)
	{
		return true;
	}
	else if(pBL && pBL->getPosition() == pos)
	{
		return true;
	}
//
// Now the point MIGHT be in this last block. Use code from pd_Document
// to find out. Have to check whether we're out of docrange first
//
	PL_StruxDocHandle sdh=NULL;
	bool bres;
	bres = m_pDoc->getStruxOfTypeFromPosition(pos, PTX_Block, &sdh);
	if(bres && sdh == pBL->getStruxDocHandle())
	{
		return true;
	}
	return false;
}

/*!
 * Removes the shadow and the corresponding element pointing to the shadow for this
 * Page.
 */
void fl_HdrFtrSectionLayout::deletePage(fp_Page* pPage)
{
	UT_sint32 iShadow = _findShadow(pPage);
//
// This shadow might have already been deleted via the collapse method
//
	if(iShadow <  0)
		return;
	_PageHdrFtrShadowPair* pPair = (_PageHdrFtrShadowPair*) m_vecPages.getNthItem(iShadow);
	UT_ASSERT(pPair);

	UT_ASSERT(pPair->getShadow());


	fp_Page * ppPage = pPair->getPage();
	UT_ASSERT(pPage == ppPage);
	delete pPair->getShadow();
	if(getDocLayout()->findPage(ppPage) >= 0)
	{
			ppPage->removeHdrFtr(getHFType());
	}
	delete pPair;
	m_vecPages.deleteNthItem(iShadow);
}


/*!
 *  Just format the HdrFtrSectionLayout blocks for an insertBlock method.
 *  these blocks will be collapsed afterwards.
 */
void fl_HdrFtrSectionLayout::localFormat(void)
{
	xxx_UT_DEBUGMSG(("Doing a Local Format of the hdrftr section \n"));
	if(!getDocSectionLayout())
		return;
	fl_ContainerLayout*	pBL = getFirstLayout();

	while (pBL)
	{
		if(pBL->getContainerType() == FL_CONTAINER_BLOCK)
		{
			static_cast<fl_BlockLayout *>(pBL)->setHdrFtr();
		}
		pBL->format();
		pBL = pBL->getNext();
	}
}

/*!
 *  Just collapse the HdrFtrSectionLayout blocks for an insertBlock method.
 *  This removes all lines and references to containers but leaves the blocks
 *  and runs intact.
 */
void fl_HdrFtrSectionLayout::_localCollapse(void)
{
	fl_ContainerLayout*	pBL = getFirstLayout();
	while (pBL)
	{
		pBL->collapse();
		pBL = pBL->getNext();
	}
}

/*!
 * This routine returns the matching block within this HdrFtrSectionLayout of the
 * shadow.
 \param fl_ContainerLayout * Pointer to block in shadow
 \returns the pinter to the matching block in the HdrFtr
 */
fl_ContainerLayout* fl_HdrFtrSectionLayout::findMatchingContainer(fl_ContainerLayout* pBL)
{
	fl_ContainerLayout* ppBL = getFirstLayout();
	while(ppBL && (ppBL->getStruxDocHandle() != pBL->getStruxDocHandle()))
	{
		ppBL = ppBL->getNext();
	}
	UT_ASSERT(ppBL);
	//xxx_UT_DEBUGMSG(("This header/footer is %x in findmatchingBlock \n",this));
	return ppBL;
}

/*!
 * This method checks that the pages in this header are valid and removes them if
 * they're not.
 */
void fl_HdrFtrSectionLayout::checkAndRemovePages(void)
{
	UT_sint32 iCount = (UT_sint32) m_vecPages.getItemCount();
//
// Check that the pages we have are still valid. Delete them if they're not.
//
	UT_sint32 i = 0;
	UT_Vector pageForDelete;
	for(i =0; i< iCount; i++)
	{
		_PageHdrFtrShadowPair* pPair = (_PageHdrFtrShadowPair*) m_vecPages.getNthItem(i);
		UT_ASSERT(pPair);
		UT_ASSERT(pPair->getShadow());

		fp_Page * ppPage = pPair->getPage();
		if(getDocLayout()->findPage(ppPage) >= 0)
		{
			if(!getDocSectionLayout()->isThisPageValid(getHFType(),ppPage))
			{
				pageForDelete.addItem((void *) ppPage);
			}
		}
		else
		{
			pageForDelete.addItem((void *) ppPage);
		}
	}
	for(i=0; i< (UT_sint32) pageForDelete.getItemCount(); i++)
	{
		fp_Page * pPage = (fp_Page *) pageForDelete.getNthItem(i);
		deletePage(pPage);
	}
	if( pageForDelete.getItemCount() > 0)
	{
		markAllRunsDirty();
	}
}

/*!
 * This method adds valid pages to the collection of shadows.
 */
void fl_HdrFtrSectionLayout::addValidPages(void)
{
	//
	// Check that all the pages this header/footer should have are
    // in place.
	// We have to extract this information from m_pDocSL
	// Loop through all the columns in m_pDocSl and find the pages owned
	// by m_pDocSL
	//
	fp_Column * pCol = (fp_Column *) m_pDocSL->getFirstContainer();
	fp_Page * pOldPage = NULL;
	fp_Page * pNewPage = NULL;
	while(pCol)
	{
		pNewPage = pCol->getPage();
		if((pNewPage != NULL) && (pNewPage != pOldPage) && (getDocLayout()->findPage(pNewPage) >=0))
		{
			fl_DocSectionLayout* pDocSec = pNewPage->getOwningSection();
			if(pDocSec == m_pDocSL && _findShadow(pNewPage) < 0)
			{
//
// The addPage Method checks that only valid pages are added to this HdrFtr based on
// the HFType
//
				addPage(pNewPage);
			}
		}
		pCol = (fp_Column *) pCol->getNext();
	}
}

/*!
 * Format the overall HdrFtrSectionLayout in it's virtual container.
 * Also check that all the correct pages have been found for this HdrFtr. Then
 * format the Shadows.
 */
void fl_HdrFtrSectionLayout::format(void)
{
	if(getFirstLayout() == NULL)
	{
		return;
	}
	UT_sint32 iCount =0;
	UT_sint32 i = 0;
	localFormat();
	//
	// Fail safe code to add pages if we don't have them.
	//
	addValidPages();

	iCount = m_vecPages.getItemCount();

	for (i=0; i<iCount; i++)
	{
		_PageHdrFtrShadowPair* pPair = (_PageHdrFtrShadowPair*) m_vecPages.getNthItem(i);
		pPair->getShadow()->format();
	}
	layout();
}

void fl_HdrFtrSectionLayout::updateLayout(void)
{
	bool bredraw = false;
	fl_ContainerLayout*	pBL = getFirstLayout();
	while (pBL)
	{
		if (pBL->needsReformat())
		{
			bredraw = true;
			pBL->format();
		}

		pBL = pBL->getNext();
	}
	if(bredraw == true)
	{
		if(m_pHdrFtrContainer)
			static_cast<fp_HdrFtrContainer *>(m_pHdrFtrContainer)->layout();
 	}

	//
	// update Just the  blocks in the shadowlayouts
	//
  	UT_uint32 iCount = m_vecPages.getItemCount();
	for (UT_uint32 i=0; i<iCount; i++)
	{
		_PageHdrFtrShadowPair* pPair = (_PageHdrFtrShadowPair*) m_vecPages.getNthItem(i);

		pPair->getShadow()->updateLayout();
	}
}

/*!
 * Mark all runs and lines in the all shadows for redraw.
 */
void fl_HdrFtrSectionLayout::markAllRunsDirty(void)
{
  	UT_uint32 iCount = m_vecPages.getItemCount();
	for (UT_uint32 i=0; i<iCount; i++)
	{
		_PageHdrFtrShadowPair* pPair = (_PageHdrFtrShadowPair*) m_vecPages.getNthItem(i);

		pPair->getShadow()->markAllRunsDirty();
	}
}

/*!
 * Layout the overall HdrFtr and everything underneath it.
 */
void fl_HdrFtrSectionLayout::layout(void)
{
    if(m_pHdrFtrContainer)
	static_cast<fp_HdrFtrContainer *>(m_pHdrFtrContainer)->layout();
	//
	// update the shadowlayouts
	//
  	UT_uint32 iCount = m_vecPages.getItemCount();
	for (UT_uint32 i=0; i<iCount; i++)
	{
		_PageHdrFtrShadowPair* pPair = (_PageHdrFtrShadowPair*) m_vecPages.getNthItem(i);

		pPair->getShadow()->layout();
	}
}

/*!
 * This method updates the background color in the header/footer section and
 * all the shadows associated with it.
 */
void fl_HdrFtrSectionLayout::updateBackgroundColor(void)
{
	fl_ContainerLayout*	pBL = getFirstLayout();
	while (pBL)
	{
		pBL->updateBackgroundColor();
		pBL = pBL->getNext();
	}
	//
	// update Just the  blocks in the shadowlayouts
	//
  	UT_uint32 iCount = m_vecPages.getItemCount();
	for (UT_uint32 i=0; i<iCount; i++)
	{
		_PageHdrFtrShadowPair* pPair = (_PageHdrFtrShadowPair*) m_vecPages.getNthItem(i);

		pPair->getShadow()->updateBackgroundColor();
	}
}


void fl_HdrFtrSectionLayout::clearScreen(void)
{
	//
	// update Just the  blocks in the shadowlayouts
	//
  	UT_uint32 iCount = m_vecPages.getItemCount();
	for (UT_uint32 i=0; i<iCount; i++)
	{
		_PageHdrFtrShadowPair* pPair = (_PageHdrFtrShadowPair*) m_vecPages.getNthItem(i);

		pPair->getShadow()->clearScreen();
	}
}

void fl_HdrFtrSectionLayout::redrawUpdate(void)
{
//
// Do another layout but don't redraw.
//
	if(m_pHdrFtrContainer)
		static_cast<fp_HdrFtrContainer *>(m_pHdrFtrContainer)->layout();
	//
	// Don't need to draw here since this is never displayed on the screen?
	//
	UT_uint32 iCount = m_vecPages.getItemCount();
	for (UT_uint32 i=0; i<iCount; i++)
	{
		_PageHdrFtrShadowPair* pPair = (_PageHdrFtrShadowPair*) m_vecPages.getNthItem(i);

		pPair->getShadow()->redrawUpdate();
	}

}

bool fl_HdrFtrSectionLayout::doclistener_changeStrux(const PX_ChangeRecord_StruxChange * pcrxc)
{
	UT_ASSERT(pcrxc->getType()==PX_ChangeRecord::PXT_ChangeStrux);

	setAttrPropIndex(pcrxc->getIndexAP());

	// TODO what happens here?

	UT_ASSERT(UT_SHOULD_NOT_HAPPEN);

	return false;
}

void fl_HdrFtrSectionLayout::_lookupProperties(void)
{
}

bool fl_HdrFtrSectionLayout::bl_doclistener_populateSpan(fl_ContainerLayout* pBL, const PX_ChangeRecord_Span * pcrs, PT_BlockOffset blockOffset, UT_uint32 len)
{
//
// We need to populate block in the header/footer but to do that we need the
// header/footer to be fomatted. So do it then unformat after.
//
	bool bResult = true;
	fl_ContainerLayout * pShadowBL = NULL;
	UT_uint32 iCount = m_vecPages.getItemCount();
	m_pDoc->setDontChangeInsPoint();

	for (UT_uint32 i=0; i<iCount; i++)
	{
		_PageHdrFtrShadowPair* pPair = (_PageHdrFtrShadowPair*) m_vecPages.getNthItem(i);
		// Find matching block in this shadow.
		pShadowBL = pPair->getShadow()->findMatchingContainer(pBL);
		bResult = static_cast<fl_BlockLayout *>(pShadowBL)->doclistener_populateSpan(pcrs,blockOffset,len)
			&& bResult;
	}
	m_pDoc->allowChangeInsPoint();
	pBL = findMatchingContainer(pBL);
	bResult = static_cast<fl_BlockLayout *>(pBL)->doclistener_populateSpan(pcrs,blockOffset,len)
			&& bResult;
	return bResult;
}

/*!
 * Now for all these methods which manipulate the shadow sections, turn off
 * Insertion Point changes while the shadows are manipulated.
 * Re Enabled insertion point changes for the overall hdrftrsection so it
 * is changed just once.
 */

bool fl_HdrFtrSectionLayout::bl_doclistener_populateObject(fl_ContainerLayout* pBL, PT_BlockOffset blockOffset, const PX_ChangeRecord_Object * pcro)
{
//
// We need to populate block in the header/footer but to do that we need the
// header/footer to be fomatted. So do it then unformat after.
//
  	bool bResult = true;
	fl_ContainerLayout * pShadowBL = NULL;
	UT_uint32 iCount = m_vecPages.getItemCount();
	m_pDoc->setDontChangeInsPoint();
	for (UT_uint32 i=0; i<iCount; i++)
	{
		_PageHdrFtrShadowPair* pPair = (_PageHdrFtrShadowPair*) m_vecPages.getNthItem(i);
		// Find matching block in this shadow.
		pShadowBL = pPair->getShadow()->findMatchingContainer(pBL);
		bResult = static_cast<fl_BlockLayout *>(pShadowBL)->doclistener_populateObject(blockOffset,pcro)
			&& bResult;
	}
	m_pDoc->allowChangeInsPoint();
	pBL = findMatchingContainer(pBL);
  	bResult = static_cast<fl_BlockLayout *>(pBL)->doclistener_populateObject(blockOffset,pcro)
  		&& bResult;
	return bResult;
}

bool fl_HdrFtrSectionLayout::bl_doclistener_insertSpan(fl_ContainerLayout* pBL, const PX_ChangeRecord_Span * pcrs)
{
	bool bResult = true;
	fl_ContainerLayout * pShadowBL = NULL;
	UT_uint32 iCount = m_vecPages.getItemCount();
	m_pDoc->setDontChangeInsPoint();
	for (UT_uint32 i=0; i<iCount; i++)
	{
		_PageHdrFtrShadowPair* pPair = (_PageHdrFtrShadowPair*) m_vecPages.getNthItem(i);

		// Find matching block in this shadow.

		pShadowBL = pPair->getShadow()->findMatchingContainer(pBL);
		bResult = static_cast<fl_BlockLayout *>(pShadowBL)->doclistener_insertSpan(pcrs)
			&& bResult;
	}
	m_pDoc->allowChangeInsPoint();
	// Update the overall block too.
	pBL = findMatchingContainer(pBL);
	bResult = static_cast<fl_BlockLayout *>(pBL)->doclistener_insertSpan(pcrs)
	&& bResult;
	return bResult;
}

bool fl_HdrFtrSectionLayout::bl_doclistener_deleteSpan(fl_ContainerLayout* pBL, const PX_ChangeRecord_Span * pcrs)
{
	bool bResult = true;
	fl_ContainerLayout * pShadowBL = NULL;
	UT_uint32 iCount = m_vecPages.getItemCount();
	m_pDoc->setDontChangeInsPoint();
	for (UT_uint32 i=0; i<iCount; i++)
	{
		_PageHdrFtrShadowPair* pPair = (_PageHdrFtrShadowPair*) m_vecPages.getNthItem(i);

		// Find matching block in this shadow.

		pShadowBL = pPair->getShadow()->findMatchingContainer(pBL);
		bResult = static_cast<fl_BlockLayout *>(pShadowBL)->doclistener_deleteSpan(pcrs)
			&& bResult;
	}
	// Update the overall block too.

	m_pDoc->allowChangeInsPoint();
	pBL = findMatchingContainer(pBL);
	bResult = static_cast<fl_BlockLayout *>(pBL)->doclistener_deleteSpan(pcrs)
		&& bResult;
	return bResult;
}

bool fl_HdrFtrSectionLayout::bl_doclistener_changeSpan(fl_ContainerLayout* pBL, const PX_ChangeRecord_SpanChange * pcrsc)
{
	bool bResult = true;
	fl_ContainerLayout * pShadowBL = NULL;
	UT_uint32 iCount = m_vecPages.getItemCount();
	m_pDoc->setDontChangeInsPoint();
	for (UT_uint32 i=0; i<iCount; i++)
	{
		_PageHdrFtrShadowPair* pPair = (_PageHdrFtrShadowPair*) m_vecPages.getNthItem(i);

		// Find matching block in this shadow.

		pShadowBL = pPair->getShadow()->findMatchingContainer(pBL);
		bResult = static_cast<fl_BlockLayout *>(pShadowBL)->doclistener_changeSpan(pcrsc)
			&& bResult;
	}
	// Update the overall block too.

	m_pDoc->allowChangeInsPoint();
	pBL = findMatchingContainer(pBL);
   	bResult = static_cast<fl_BlockLayout *>(pBL)->doclistener_changeSpan(pcrsc)
		&& bResult;
	return bResult;
}

bool fl_HdrFtrSectionLayout::bl_doclistener_deleteStrux(fl_ContainerLayout* pBL, const PX_ChangeRecord_Strux * pcrx)
{
	bool bResult = true;
	fl_ContainerLayout * pShadowBL = NULL;
	UT_uint32 iCount = m_vecPages.getItemCount();
	m_pDoc->setDontChangeInsPoint();
	for (UT_uint32 i=0; i<iCount; i++)
	{
		_PageHdrFtrShadowPair* pPair = (_PageHdrFtrShadowPair*) m_vecPages.getNthItem(i);

		// Find matching block in this shadow.

		pShadowBL = pPair->getShadow()->findMatchingContainer(pBL);
		bResult = static_cast<fl_BlockLayout *>(pShadowBL)->doclistener_deleteStrux(pcrx)
			&& bResult;
	}
	// Update the overall block too.

	m_pDoc->allowChangeInsPoint();
	pBL = findMatchingContainer(pBL);
   	bResult = static_cast<fl_BlockLayout *>(pBL)->doclistener_deleteStrux(pcrx) && bResult;
	return bResult;
}

bool fl_HdrFtrSectionLayout::bl_doclistener_changeStrux(fl_ContainerLayout* pBL, const PX_ChangeRecord_StruxChange * pcrxc)
{
	bool bResult = true;
	fl_ContainerLayout * pShadowBL = NULL;
	UT_uint32 iCount = m_vecPages.getItemCount();
	m_pDoc->setDontChangeInsPoint();
	for (UT_uint32 i=0; i<iCount; i++)
	{
		_PageHdrFtrShadowPair* pPair = (_PageHdrFtrShadowPair*) m_vecPages.getNthItem(i);

		// Find matching block in this shadow.

		pShadowBL = pPair->getShadow()->findMatchingContainer(pBL);
		bResult = static_cast<fl_BlockLayout *>(pShadowBL)->doclistener_changeStrux(pcrxc)
			&& bResult;
	}
	// Update the overall block too.

	m_pDoc->allowChangeInsPoint();
	pBL = findMatchingContainer(pBL);
    bResult = static_cast<fl_BlockLayout *>(pBL)->doclistener_changeStrux(pcrxc)
		&& bResult;
	return bResult;
}

bool fl_HdrFtrSectionLayout::bl_doclistener_insertBlock(fl_ContainerLayout* pBL, const PX_ChangeRecord_Strux * pcrx,PL_StruxDocHandle sdh,PL_ListenerId lid,void (* pfnBindHandles)(PL_StruxDocHandle sdhNew,	PL_ListenerId lid, PL_StruxFmtHandle sfhNew))
{
	bool bResult = true;
//
// Now insert it into all the shadows.
//
	UT_uint32 iCount = m_vecPages.getItemCount();
	fl_ContainerLayout * pShadowBL = NULL;
	m_pDoc->setDontChangeInsPoint();
	for (UT_uint32 i=0; i<iCount; i++)
	{
		_PageHdrFtrShadowPair* pPair = (_PageHdrFtrShadowPair*) m_vecPages.getNthItem(i);

		// Find matching block in this shadow.
		if(pBL)
		{
			pShadowBL = pPair->getShadow()->findMatchingContainer(pBL);
			bResult = static_cast<fl_BlockLayout *>(pShadowBL)->doclistener_insertBlock(pcrx,sdh,lid,pfnBindHandles)
				&& bResult;
		}
		else
//
// This is the first block in the shadow
//
		{
			fl_ContainerLayout*	pNewBL = pPair->getShadow()->insert(sdh, NULL, pcrx->getIndexAP(),FL_CONTAINER_BLOCK);
			if (!pNewBL)
			{
				UT_DEBUGMSG(("no memory for BlockLayout\n"));
				return false;
			}
			bResult = bResult && static_cast<fl_BlockLayout *>(pNewBL)->doclistener_insertFirstBlock(pcrx, sdh,
													lid, pfnBindHandles);
		}
	}
//
// Find Matching Block in this HdrFtrSectionLayout!!
//
	if(pBL)
	{
		fl_ContainerLayout * ppBL = findMatchingContainer(pBL);
		m_pDoc->allowChangeInsPoint();

		static_cast<fl_BlockLayout *>(ppBL)->setHdrFtr();
		bResult = static_cast<fl_BlockLayout *>(ppBL)->doclistener_insertBlock(pcrx,sdh,lid,pfnBindHandles)
			&& bResult;
//
// Mark the Block as HdrFtr
//
		static_cast<fl_BlockLayout *>(ppBL->getNext())->setHdrFtr();
	}
	else
//
// First block in the section
//
	{
		fl_ContainerLayout*	pNewBL = insert(sdh, NULL, pcrx->getIndexAP(),FL_CONTAINER_BLOCK);
		if (!pNewBL)
		{
			UT_DEBUGMSG(("no memory for BlockLayout\n"));
			return false;
		}
		bResult = bResult && static_cast<fl_BlockLayout *>(pNewBL)->doclistener_insertFirstBlock(pcrx, sdh,
													lid, pfnBindHandles);
		m_pDoc->allowChangeInsPoint();
		static_cast<fl_BlockLayout *>(pNewBL)->setHdrFtr();
	}
	return bResult;
}

bool fl_HdrFtrSectionLayout::bl_doclistener_insertSection(fl_ContainerLayout* pBL, const PX_ChangeRecord_Strux * pcrx,
														  PL_StruxDocHandle sdh,
														  PL_ListenerId lid,
														  void (* pfnBindHandles)(PL_StruxDocHandle sdhNew,
																				  PL_ListenerId lid,
																				  PL_StruxFmtHandle sfhNew))
{
	// TODO this should NEVER happen, right?
	UT_DEBUGMSG(("Insert Section is header/footer!!! \n"));
	UT_ASSERT(0);
	bool bResult = true;
	UT_uint32 iCount = m_vecPages.getItemCount();
	for (UT_uint32 i=0; i<iCount; i++)
	{
		_PageHdrFtrShadowPair* pPair = (_PageHdrFtrShadowPair*) m_vecPages.getNthItem(i);

		bResult = pPair->getShadow()->bl_doclistener_insertSection(pBL, FL_SECTION_DOC, pcrx, sdh, lid, pfnBindHandles)
			&& bResult;
	}

	return bResult;
}

bool fl_HdrFtrSectionLayout::bl_doclistener_insertObject(fl_ContainerLayout* pBL, const PX_ChangeRecord_Object * pcro)
{
	bool bResult = true;
	fl_ContainerLayout * pShadowBL = NULL;
	UT_uint32 iCount = m_vecPages.getItemCount();
	m_pDoc->setDontChangeInsPoint();
	for (UT_uint32 i=0; i<iCount; i++)
	{
		_PageHdrFtrShadowPair* pPair = (_PageHdrFtrShadowPair*) m_vecPages.getNthItem(i);
		// Find matching block in this shadow.
		pShadowBL = pPair->getShadow()->findMatchingContainer(pBL);
		bResult = static_cast<fl_BlockLayout *>(pShadowBL)->doclistener_insertObject(pcro)
			&& bResult;
	}
	// Update the overall block too.
	m_pDoc->allowChangeInsPoint();
	pBL = findMatchingContainer(pBL);
   	bResult = static_cast<fl_BlockLayout *>(pBL)->doclistener_insertObject(pcro) && bResult;
	return bResult;
}

bool fl_HdrFtrSectionLayout::bl_doclistener_deleteObject(fl_ContainerLayout* pBL, const PX_ChangeRecord_Object * pcro)
{
	bool bResult = true;
	fl_ContainerLayout * pShadowBL = NULL;
	UT_uint32 iCount = m_vecPages.getItemCount();
	m_pDoc->setDontChangeInsPoint();
	for (UT_uint32 i=0; i<iCount; i++)
	{
		_PageHdrFtrShadowPair* pPair = (_PageHdrFtrShadowPair*) m_vecPages.getNthItem(i);
		// Find matching block in this shadow.
		pShadowBL = pPair->getShadow()->findMatchingContainer(pBL);
		bResult = static_cast<fl_BlockLayout *>(pShadowBL)->doclistener_deleteObject(pcro)
			&& bResult;
	}
	// Update the overall block too.
	m_pDoc->allowChangeInsPoint();
	pBL = findMatchingContainer(pBL);
	bResult = static_cast<fl_BlockLayout *>(pBL)->doclistener_deleteObject(pcro) && bResult;

	return bResult;
}

bool fl_HdrFtrSectionLayout::bl_doclistener_changeObject(fl_ContainerLayout* pBL, const PX_ChangeRecord_ObjectChange * pcroc)
{
	bool bResult = true;
	fl_ContainerLayout * pShadowBL = NULL;
	UT_uint32 iCount = m_vecPages.getItemCount();
	m_pDoc->setDontChangeInsPoint();
	for (UT_uint32 i=0; i<iCount; i++)
	{
		_PageHdrFtrShadowPair* pPair = (_PageHdrFtrShadowPair*) m_vecPages.getNthItem(i);
		// Find matching block in this shadow.
		pShadowBL = pPair->getShadow()->findMatchingContainer(pBL);
		bResult = static_cast<fl_BlockLayout *>(pShadowBL)->doclistener_changeObject(pcroc)
			&& bResult;
	}
	// Update the overall block too.
	m_pDoc->allowChangeInsPoint();
	pBL = findMatchingContainer(pBL);
   	bResult = static_cast<fl_BlockLayout *>(pBL)->doclistener_changeObject(pcroc) && bResult;

	return bResult;
}

bool fl_HdrFtrSectionLayout::bl_doclistener_insertFmtMark(fl_ContainerLayout* pBL, const PX_ChangeRecord_FmtMark * pcrfm)
{
	bool bResult = true;
	fl_ContainerLayout * pShadowBL = NULL;
	UT_uint32 iCount = m_vecPages.getItemCount();
	m_pDoc->setDontChangeInsPoint();
	for (UT_uint32 i=0; i<iCount; i++)
	{
		_PageHdrFtrShadowPair* pPair = (_PageHdrFtrShadowPair*) m_vecPages.getNthItem(i);
		// Find matching block in this shadow.
		pShadowBL = pPair->getShadow()->findMatchingContainer(pBL);
		bResult = static_cast<fl_BlockLayout *>(pShadowBL)->doclistener_insertFmtMark(pcrfm)
			&& bResult;
	}
	// Update the overall block too.
	m_pDoc->allowChangeInsPoint();
	pBL = findMatchingContainer(pBL);
	bResult = static_cast<fl_BlockLayout *>(pBL)->doclistener_insertFmtMark(pcrfm) && bResult;
	return bResult;
}

bool fl_HdrFtrSectionLayout::bl_doclistener_deleteFmtMark(fl_ContainerLayout* pBL, const PX_ChangeRecord_FmtMark * pcrfm)
{
	bool bResult = true;
	fl_ContainerLayout * pShadowBL = NULL;
	UT_uint32 iCount = m_vecPages.getItemCount();
	m_pDoc->setDontChangeInsPoint();
	for (UT_uint32 i=0; i<iCount; i++)
	{
		_PageHdrFtrShadowPair* pPair = (_PageHdrFtrShadowPair*) m_vecPages.getNthItem(i);
		// Find matching block in this shadow.
		pShadowBL = pPair->getShadow()->findMatchingContainer(pBL);
		bResult = static_cast<fl_BlockLayout *>(pShadowBL)->doclistener_deleteFmtMark(pcrfm)
			&& bResult;
	}
	// Update the overall block too.
	m_pDoc->allowChangeInsPoint();
	pBL = findMatchingContainer(pBL);
	bResult = static_cast<fl_BlockLayout *>(pBL)->doclistener_deleteFmtMark(pcrfm)	&& bResult;
	return bResult;
}

bool fl_HdrFtrSectionLayout::bl_doclistener_changeFmtMark(fl_ContainerLayout* pBL, const PX_ChangeRecord_FmtMarkChange * pcrfmc)
{
	bool bResult = true;
	fl_ContainerLayout * pShadowBL = NULL;
	UT_uint32 iCount = m_vecPages.getItemCount();
	m_pDoc->setDontChangeInsPoint();
	for (UT_uint32 i=0; i<iCount; i++)
	{
		_PageHdrFtrShadowPair* pPair = (_PageHdrFtrShadowPair*) m_vecPages.getNthItem(i);
		// Find matching block in this shadow.
		pShadowBL = pPair->getShadow()->findMatchingContainer(pBL);
		bResult = static_cast<fl_BlockLayout *>(pShadowBL)->doclistener_changeFmtMark(pcrfmc)
			&& bResult;
	}
	// Update the overall block too.
	m_pDoc->allowChangeInsPoint();
	pBL = findMatchingContainer(pBL);
   	bResult = static_cast<fl_BlockLayout *>(pBL)->doclistener_changeFmtMark(pcrfmc) && bResult;
	return bResult;
}

bool fl_DocSectionLayout::bl_doclistener_insertFootnote(fl_ContainerLayout* pFootnote,
											  const PX_ChangeRecord_Strux * pcrx,
											  PL_StruxDocHandle sdh,
											  PL_ListenerId lid,
											  void (* pfnBindHandles)(PL_StruxDocHandle sdhNew,
																	  PL_ListenerId lid,
																	  PL_StruxFmtHandle sfhNew))
{
	fl_ContainerLayout * pNewCL = NULL;
	fl_DocSectionLayout * pCol = (fl_DocSectionLayout *) myContainingLayout();
	pNewCL = pCol->insert(sdh,pFootnote,pcrx->getIndexAP(), FL_CONTAINER_FOOTNOTE);
	
		// Must call the bind function to complete the exchange of handles
		// with the document (piece table) *** before *** anything tries
		// to call down into the document (like all of the view
		// listeners).
		
	PL_StruxFmtHandle sfhNew = (PL_StruxFmtHandle)pNewCL;
	pfnBindHandles(sdh,lid,sfhNew);


//
// increment the insertion point in the view.
//
	FV_View* pView = m_pLayout->getView();
	if (pView && (pView->isActive() || pView->isPreview()))
	{
		pView->setPoint(pcrx->getPosition() +  fl_BLOCK_STRUX_OFFSET);
	}
	else if(pView && pView->getPoint() > pcrx->getPosition())
	{
		pView->setPoint(pView->getPoint() +  fl_BLOCK_STRUX_OFFSET);
	}
	return true;
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

fl_HdrFtrShadow::fl_HdrFtrShadow(FL_DocLayout* pLayout, fp_Page* pPage, fl_HdrFtrSectionLayout* pHdrFtrSL, PL_StruxDocHandle sdh, PT_AttrPropIndex indexAP)
	: fl_SectionLayout(pLayout, sdh, indexAP, FL_SECTION_SHADOW,FL_CONTAINER_SHADOW,PTX_Section,pHdrFtrSL->getDocSectionLayout()),
	  m_pPage(pPage),
	  m_pHdrFtrSL(pHdrFtrSL)
{
	// Force creation of the appropriate container object;
	// throw away return value.
	m_pPage->getHdrFtrContainer(m_pHdrFtrSL);
	UT_DEBUGMSG(("check that m_iType is indeed FL_SECTION_SHADOW"));
	UT_ASSERT(m_iType == FL_SECTION_SHADOW);
//	UT_ASSERT(0);
	fl_Layout::setType(PTX_Section); // Set the type of this strux
}

fl_HdrFtrShadow::~fl_HdrFtrShadow()
{
	_purgeLayout();
}

fp_Container* fl_HdrFtrShadow::getFirstContainer() const
{
	return m_pPage->getHdrFtrContainer(m_pHdrFtrSL);
}

fp_Container* fl_HdrFtrShadow::getLastContainer() const
{
	UT_ASSERT(UT_TODO);

	return NULL;
}

fp_Container* fl_HdrFtrShadow::getNewContainer(fp_Container * pFirstContainer)
{
	UT_ASSERT(UT_SHOULD_NOT_HAPPEN);

	return NULL;
}

fl_ContainerLayout* fl_HdrFtrShadow::findMatchingContainer(fl_ContainerLayout* pBL)
{
	// This routine returns the matching block within this shadow of the
	// hdrftrSectionlayout.
	//
	fl_ContainerLayout* ppBL = getFirstLayout();
	while(ppBL && (ppBL->getStruxDocHandle() != pBL->getStruxDocHandle()))
	{
		ppBL = ppBL->getNext();
	}
	UT_ASSERT(ppBL);
	xxx_UT_DEBUGMSG(("Search for block in shadow %x \n",this));
	return ppBL;
}

void fl_HdrFtrShadow::format(void)
{
	fl_ContainerLayout*	pBL = getFirstLayout();
	while (pBL)
	{
		pBL->format();
		pBL = pBL->getNext();
	}
}

/*!
 * Scans through the shadow looking for the block at the specified Document
 * Position.
 \param pos the Document position
 \return A pointer to the block containing the point. Returns NULL if no block
         is found
 */
fl_ContainerLayout * fl_HdrFtrShadow::findBlockAtPosition(PT_DocPosition pos)
{
//
// Skip through the blocks in this shadow to find the one containing this
// point.
//
    fl_ContainerLayout*	pBL = getFirstLayout();
	if(pBL == NULL)
		return NULL;
	if(pos < pBL->getPosition())
	{
//
// This corner case is that pos == position of the HdrFtr strux
//
		if(pos == (pBL->getPosition() - 1))
		{
			return pBL;
		}
		return NULL;
	}
	fl_ContainerLayout* pNext = pBL->getNext();
	while(pNext != NULL && pNext->getPosition( true) < pos)
	{
		pBL = pNext;
		pNext = pNext->getNext();
	}
	if(pNext != NULL)
	{
		return pBL;
	}
	else if(pBL && pBL->getPosition() == pos)
	{
		return pBL;
	}
//
// Next corner case. See if position is inside the edittableBounds of this
// section
//
	PT_DocPosition posEnd;
	FV_View * pView = m_pLayout->getView();
	if(pView)
	{
		pView->getEditableBounds(true,posEnd);
		if(pos <= posEnd)
			return pBL;
	}
//
// Now the point MIGHT be in this last block. Use code from pd_Document
// to find out. Have to check whether we're out of docrange first
//
	m_pDoc->getBounds(true,posEnd);
	if(pos > posEnd)
		return NULL;
	PL_StruxDocHandle sdh=NULL;
	bool bres;
	bres = m_pDoc->getStruxOfTypeFromPosition(pos, PTX_Block, &sdh);
	if(bres && sdh == pBL->getStruxDocHandle())
		return pBL;
//
// Not here!!
//
	return NULL;
}

void fl_HdrFtrShadow::updateLayout(void)
{
	bool bredraw = false;
	fl_ContainerLayout*	pBL = getFirstLayout();
	while (pBL)
	{
		if (pBL->needsReformat())
		{
			bredraw = true;
			pBL->format();
		}

		pBL = pBL->getNext();
	}
	if(bredraw)
	{
		//    clearScreen();
		static_cast<fp_ShadowContainer *>(getFirstContainer())->layout();
 	}
}

void fl_HdrFtrShadow::layout(void)
{
	static_cast<fp_ShadowContainer *>(getFirstContainer())->layout();
}

void fl_HdrFtrShadow::clearScreen(void)
{
	UT_ASSERT(getFirstContainer());
	if(getFirstContainer())
		static_cast<fp_ShadowContainer *>(getFirstContainer())->clearScreen();
}

void fl_HdrFtrShadow::redrawUpdate(void)
{
	FV_View * pView = m_pLayout->getView();
	fl_ContainerLayout*	pBL = getFirstLayout();
	while (pBL && (pView != NULL))
	{
		if(pBL->getContainerType() == FL_CONTAINER_BLOCK && static_cast<fl_BlockLayout *>(pBL)->hasUpdatableField())
		{
			bool bReformat = pBL->recalculateFields(getDocLayout()->getRedrawCount());
			if(bReformat)
			{
				pBL->format();
			}
		}
		if(pView && pBL->needsRedraw())
		{
			pBL->redrawUpdate();
		}
		pBL = pBL->getNext();
	}
	static_cast<fp_ShadowContainer *>(getFirstContainer())->layout();
}
bool fl_HdrFtrShadow::doclistener_changeStrux(const PX_ChangeRecord_StruxChange * pcrxc)
{
	UT_ASSERT(pcrxc->getType()==PX_ChangeRecord::PXT_ChangeStrux);

	setAttrPropIndex(pcrxc->getIndexAP());

	// TODO

	UT_ASSERT(UT_SHOULD_NOT_HAPPEN);

	return false;
}


void fl_HdrFtrShadow::_lookupProperties(void)
{
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

fl_ShadowListener::fl_ShadowListener(fl_HdrFtrSectionLayout* pHFSL, fl_HdrFtrShadow* pShadow)
{
	UT_ASSERT(pHFSL);
	UT_ASSERT(pShadow);

	m_pDoc = pHFSL->getDocLayout()->getDocument();
	m_pHFSL = pHFSL;
	m_pShadow = pShadow;
	m_bListening = false;
	m_pCurrentBL = NULL;
}

fl_ShadowListener::~fl_ShadowListener()
{
}

bool fl_ShadowListener::populate(PL_StruxFmtHandle sfh,
								 const PX_ChangeRecord * pcr)
{
	if (!m_bListening)
	{
		return true;
	}

	UT_ASSERT(m_pShadow);
//	UT_DEBUGMSG(("fl_ShadowListener::populate shadow %x \n",m_pShadow));

	bool bResult = false;
	FV_View* pView = m_pHFSL->getDocLayout()->getView();
	PT_DocPosition oldPos = 0;
	//
	// We're not printing
	//
	if(pView != NULL)
	{
		oldPos = pView->getPoint();
	}
	switch (pcr->getType())
	{
	case PX_ChangeRecord::PXT_InsertSpan:
	{
		const PX_ChangeRecord_Span * pcrs = static_cast<const PX_ChangeRecord_Span *> (pcr);

		{
			fl_Layout * pL = (fl_Layout *)sfh;
			UT_ASSERT(pL->getType() == PTX_Block);
			UT_ASSERT(m_pCurrentBL == (static_cast<fl_ContainerLayout *>(pL)));
		}
		PT_BlockOffset blockOffset = pcrs->getBlockOffset();
		UT_uint32 len = pcrs->getLength();


		bResult = static_cast<fl_BlockLayout *>(m_pCurrentBL)->doclistener_populateSpan(pcrs, blockOffset, len);
		goto finish_up;
	}

	case PX_ChangeRecord::PXT_InsertObject:
	{
		const PX_ChangeRecord_Object * pcro = static_cast<const PX_ChangeRecord_Object *>(pcr);

		{
			fl_Layout * pL = (fl_Layout *)sfh;
			UT_ASSERT(pL->getType() == PTX_Block);
			UT_ASSERT(m_pCurrentBL == (static_cast<fl_ContainerLayout *>(pL)));
		}
		PT_BlockOffset blockOffset = pcro->getBlockOffset();

// sterwill -- is this call to getSectionLayout() needed?  pBLSL is not used.

//			fl_SectionLayout* pBLSL = m_pCurrentBL->getSectionLayout();
		bResult = static_cast<fl_BlockLayout *>(m_pCurrentBL)->doclistener_populateObject(blockOffset,pcro);
		goto finish_up;
	}

	case PX_ChangeRecord::PXT_InsertFmtMark:
	{
		//	const PX_ChangeRecord_FmtMark * pcrfm = static_cast<const PX_ChangeRecord_FmtMark *>(pcr);

		{
			fl_Layout * pL = (fl_Layout *)sfh;
			UT_ASSERT(pL->getType() == PTX_Block);
			UT_ASSERT(m_pCurrentBL == (static_cast<fl_ContainerLayout *>(pL)));
		}
		bResult = static_cast<fl_BlockLayout *>(m_pCurrentBL)->doclistener_insertFmtMark( (const PX_ChangeRecord_FmtMark *) pcr);
		goto finish_up;
	}

	default:
		UT_DEBUGMSG(("Unknown Change record = %d \n",pcr->getType()));
		UT_ASSERT(0);
		//
		// We're not printing
		//
		if(pView != NULL)
		{
			pView->setPoint(oldPos);
		}
		return false;
	}

 finish_up:
	//
	// We're not printing
	//
	if(pView != NULL)
	{
		pView->setPoint(oldPos);
	}
	return bResult;
}

bool fl_ShadowListener::populateStrux(PL_StruxDocHandle sdh,
									  const PX_ChangeRecord * pcr,
									  PL_StruxFmtHandle * psfh)
{
	UT_ASSERT(m_pShadow);
	UT_DEBUGMSG(("fl_ShadowListener::populateStrux\n"));

	UT_ASSERT(pcr->getType() == PX_ChangeRecord::PXT_InsertStrux);
	const PX_ChangeRecord_Strux * pcrx = static_cast<const PX_ChangeRecord_Strux *> (pcr);

	switch (pcrx->getStruxType())
	{
	case PTX_Section:
	{
		PT_AttrPropIndex indexAP = pcr->getIndexAP();
		const PP_AttrProp* pAP = NULL;
		if (m_pDoc->getAttrProp(indexAP, &pAP) && pAP)
		{
			const XML_Char* pszSectionType = NULL;
			pAP->getAttribute("type", pszSectionType);
			if (
				!pszSectionType
				|| (0 == UT_strcmp(pszSectionType, "doc"))
				)
			{
				m_bListening = false;
			}
			else
			{
				if ( (0 == UT_strcmp(pszSectionType, "header"))
					|| (0 == UT_strcmp(pszSectionType, "footer"))
					 || (0 == UT_strcmp(pszSectionType, "header-first"))
					|| (0 == UT_strcmp(pszSectionType, "footer-first"))
					 || (0 == UT_strcmp(pszSectionType, "header-even"))
					|| (0 == UT_strcmp(pszSectionType, "footer-even"))
					 || (0 == UT_strcmp(pszSectionType, "header-last"))
					|| (0 == UT_strcmp(pszSectionType, "footer-last"))
					)
				{
					// TODO verify id match

					m_bListening = true;
				}
				else
				{
					return false;
				}
			}
		}
		else
		{
			// TODO fail?
			return false;
		}
	}
	break;

	case PTX_SectionHdrFtr:
	{
		PT_AttrPropIndex indexAP = pcr->getIndexAP();
		const PP_AttrProp* pAP = NULL;
		if (m_pDoc->getAttrProp(indexAP, &pAP) && pAP)
		{
			const XML_Char* pszSectionType = NULL;
			pAP->getAttribute("type", pszSectionType);
			if (
				!pszSectionType
				|| (0 == UT_strcmp(pszSectionType, "doc"))
				)
			{
				m_bListening = false;
			}
			else
			{
				if ( (0 == UT_strcmp(pszSectionType, "header"))
					|| (0 == UT_strcmp(pszSectionType, "footer"))
					 || (0 == UT_strcmp(pszSectionType, "header-first"))
					|| (0 == UT_strcmp(pszSectionType, "footer-first"))
					 || (0 == UT_strcmp(pszSectionType, "header-even"))
					|| (0 == UT_strcmp(pszSectionType, "footer-even"))
					 || (0 == UT_strcmp(pszSectionType, "header-last"))
					|| (0 == UT_strcmp(pszSectionType, "footer-last"))
					)
				{
					// TODO verify id match

					m_bListening = true;
				}
				else
				{
					return false;
				}
			}
		}
		else
		{
			// TODO fail?
			return false;
		}
	}
	break;

	case PTX_Block:
	{
		if (m_bListening)
		{
			// append a new BlockLayout to that SectionLayout
			fl_ContainerLayout*	pBL = m_pShadow->append(sdh, pcr->getIndexAP(),FL_CONTAINER_BLOCK);
			if (!pBL)
			{
				UT_DEBUGMSG(("no memory for BlockLayout"));
				return false;
			}
			m_pCurrentBL = pBL;
			*psfh = (PL_StruxFmtHandle)pBL;
		}

	}
	break;

	default:
		UT_ASSERT(0);
		return false;
	}
	//
	// We're not printing
	//
	return true;
}

bool fl_ShadowListener::change(PL_StruxFmtHandle /*sfh*/,
							   const PX_ChangeRecord * /*pcr*/)
{
	UT_ASSERT(UT_SHOULD_NOT_HAPPEN);

	return false;
}

bool fl_ShadowListener::insertStrux(PL_StruxFmtHandle /*sfh*/,
									const PX_ChangeRecord * /*pcr*/,
									PL_StruxDocHandle /*sdh*/,
									PL_ListenerId /*lid*/,
									void (* /*pfnBindHandles*/)(PL_StruxDocHandle sdhNew,
																PL_ListenerId lid,
																PL_StruxFmtHandle sfhNew))
{
	UT_ASSERT(UT_SHOULD_NOT_HAPPEN);

	return false;
}

bool fl_ShadowListener::signal(UT_uint32 /*iSignal*/)
{
	UT_ASSERT(UT_SHOULD_NOT_HAPPEN);

	return false;
}


