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

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "fp_Run.h"
#include "fl_DocLayout.h"
#include "fl_BlockLayout.h"
#include "fp_Line.h"
#include "fp_Column.h"
#include "fp_Page.h"
#include "pp_Property.h"
#include "gr_Graphics.h"
#include "pd_Document.h"
#include "gr_DrawArgs.h"
#include "fv_View.h"
#include "pp_AttrProp.h"

#include "ut_debugmsg.h"
#include "ut_assert.h"
#include "ut_string.h"
#include "ut_growbuf.h"

#include "ap_Prefs.h"

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

fp_FmtMarkRun::fp_FmtMarkRun(fl_BlockLayout* pBL, GR_Graphics* pG,
							 UT_uint32 iOffsetFirst)
	: fp_Run(pBL, pG, iOffsetFirst, 0, FPRUN_FMTMARK)
{
	lookupProperties();
}

void fp_FmtMarkRun::_lookupProperties(const PP_AttrProp * pSpanAP,
									  const PP_AttrProp * pBlockAP,
									  const PP_AttrProp * pSectionAP)
{
	// look for fonts in this DocLayout's font cache
	FL_DocLayout * pLayout = getBlock()->getDocLayout();

	GR_Font* pFont = pLayout->findFont(pSpanAP,
									   pBlockAP,
									   pSectionAP,
									   FL_DocLayout::FIND_FONT_AT_SCREEN_RESOLUTION);

	_setAscent(getGR()->getFontAscent(pFont));
	_setDescent(getGR()->getFontDescent(pFont));
	_setHeight(getGR()->getFontHeight(pFont));

#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
	pFont = pLayout->findFont(pSpanAP,
							  pBlockAP,
							  pSectionAP,
							  FL_DocLayout::FIND_FONT_AT_LAYOUT_RESOLUTION);

	_setAscentLayoutUnits(getGR()->getFontAscent(pFont));
	_setDescentLayoutUnits(getGR()->getFontDescent(pFont));
	_setHeightLayoutUnits(getGR()->getFontHeight(pFont));
#endif

	PD_Document * pDoc = getBlock()->getDocument();

	_setDirection(FRIBIDI_TYPE_WS);

	const XML_Char * pszPosition = PP_evalProperty("text-position",
												   pSpanAP,
												   pBlockAP,
												   pSectionAP,
												   pDoc,
												   true);

	if (0 == UT_strcmp(pszPosition, "superscript"))
	{
		m_fPosition = TEXT_POSITION_SUPERSCRIPT;
	}
	else if (0 == UT_strcmp(pszPosition, "subscript"))
	{
		m_fPosition = TEXT_POSITION_SUBSCRIPT;
	}
	else m_fPosition = TEXT_POSITION_NORMAL;

}

bool fp_FmtMarkRun::canBreakAfter(void) const
{
	return true;
}

bool fp_FmtMarkRun::canBreakBefore(void) const
{
	return true;
}

bool fp_FmtMarkRun::letPointPass(void) const
{
	return false;
}

void fp_FmtMarkRun::mapXYToPosition(UT_sint32 /* x */, UT_sint32 /*y*/, PT_DocPosition& pos, bool& bBOL, bool& bEOL)
{
	pos = getBlock()->getPosition() + getBlockOffset();
	bBOL = false;
	bEOL = false;
}

void fp_FmtMarkRun::findPointCoords(UT_uint32 /*iOffset*/, UT_sint32& x, UT_sint32& y,  UT_sint32& x2, UT_sint32& y2, UT_sint32& height, bool& bDirection)
{
	UT_sint32 xoff;
	UT_sint32 yoff;

	UT_ASSERT(getLine());

	getLine()->getOffsets(this, xoff, yoff);
	if (m_fPosition == TEXT_POSITION_SUPERSCRIPT)
	{
		yoff -= getAscent() * 1/2;
	}
	else if (m_fPosition == TEXT_POSITION_SUBSCRIPT)
	{
		yoff += getDescent() /* * 3/2 */;
	}
	x = xoff;
	y = yoff;
	height = getHeight();
	x2 = x;
	y2 = y;
	bDirection = (getVisDirection() != 0);
}

void fp_FmtMarkRun::_clearScreen(bool /* bFullLineHeightRect */)
{
#if 0
#ifdef DEBUG
	UT_sint32 xoff = 0, yoff = 0;
	getLine()->getScreenOffsets(this, xoff, yoff);

	getGR()->fillRect(m_ColorBG,xoff,yoff, 1,m_iHeight);
#endif
#endif
}

void fp_FmtMarkRun::_draw(dg_DrawArgs* /*pDA */)
{
#if 0
#ifdef DEBUG
	UT_sint32 yTopOfRun = pDA->yoff - getAscent();
	UT_sint32 xOrigin = pDA->xoff;

	UT_RGBColor clrBlue(0,0,255); // debug color only
	getGR()->setColor(clrBlue);
	getGR()->drawLine(xOrigin,yTopOfRun, xOrigin,yTopOfRun+getHeight());
#endif
#endif
}

const PP_AttrProp* fp_FmtMarkRun::getAP(void) const
{
	const PP_AttrProp * pSpanAP = NULL;

	getBlock()->getSpanAttrProp(getBlockOffset(),true,&pSpanAP);

	return pSpanAP;
}
