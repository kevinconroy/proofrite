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
#include <stdio.h>

#include "ut_debugmsg.h"
#include "ut_assert.h"
#include "ut_types.h"
#include "ut_string.h"

#include "xap_App.h"
#include "xap_Preview.h"

#include "ap_Preview_Paragraph.h"
#include "ap_Strings.h"
#include "ap_Dialog_Lists.h"

#include <fribidi/fribidi.h>

/************************************************************************/

// all of these are measured in pixels

#define DEFAULT_TOP_MARGIN _UL(5)

#define DEFAULT_LEFT_STOP _UL(20)
#define DEFAULT_RIGHT_STOP _UL(20)

#define DEFAULT_BEFORE_SPACING 0
#define DEFAULT_AFTER_SPACING 0
#define DEFAULT_LINE_SPACING 0

AP_Preview_Paragraph_Block::AP_Preview_Paragraph_Block(UT_RGBColor & clr,
													   GR_Graphics * gc,
													   AP_Dialog_Paragraph::tAlignState m_align,
													   UT_uint32 fontHeight)
{
	UT_ASSERT(gc);

	m_clr.m_red = clr.m_red;
	m_clr.m_grn = clr.m_grn;
	m_clr.m_blu = clr.m_blu;

	m_gc = gc;

	m_firstLineLeftStop = DEFAULT_LEFT_STOP;
	m_leftStop = DEFAULT_LEFT_STOP;
	m_rightStop = DEFAULT_RIGHT_STOP;

	m_beforeSpacing = DEFAULT_BEFORE_SPACING;
	m_afterSpacing = DEFAULT_AFTER_SPACING;
	m_lineSpacing = DEFAULT_LINE_SPACING;

	m_align = AP_Dialog_Paragraph::align_LEFT;
	m_indent = AP_Dialog_Paragraph::indent_NONE;
	m_spacing = AP_Dialog_Paragraph::spacing_SINGLE;

	m_fontHeight = fontHeight;
}

AP_Preview_Paragraph_Block::~AP_Preview_Paragraph_Block()
{
	// clear out our vector by freeing ONLY the first
	// word.  All the pointers in the vector point
	// to different offsets of one piece of memory allocated
	// all at once.
	if (m_words.getItemCount() > 0)
	{
		UT_UCSChar * word = (UT_UCSChar *) m_words.getNthItem(0);
		FREEP(word);
	}
}

void AP_Preview_Paragraph_Block::setText(const UT_UCSChar * text)
{
	UT_ASSERT(text);

	// clear the words vector by freeing ONLY the first
	// word (see the destructor for notes)
	if (m_words.getItemCount() > 0)
	{
		UT_UCSChar * word = (UT_UCSChar *) m_words.getNthItem(0);
		FREEP(word);
		m_words.clear();
	}

	// clear the widths vector (has no memory at each item)
	m_widths.clear();

	// dup the string for harmful chunkification
	UT_UCSChar * clone = NULL;
	UT_UCS4_cloneString(&clone, text);

	UT_UCSChar * i = clone;

	while (*i != 0)
	{
		// for each space
		if (*i == ' ')
		{
			// terminate this word
			*i = 0;

			// add clone item
			m_words.addItem(clone);

			// measure clone item
			m_widths.addItem((void *) m_gc->measureString(clone, 0, UT_UCS4_strlen(clone), NULL));

			// advance clone pointer for new word
			clone = i + 1;
		}
		i++;
	}

	// add last word
	m_words.addItem(clone);
	// measure last word
	m_widths.addItem((void *) m_gc->measureString(clone, 0, UT_UCS4_strlen(clone), NULL));
}

// ignores NULL parameters, otherwise scales dimensioned strings into
// pixel constants for drawing this block.  It's 72/2, since we'll
// be converting all units to inches, then to points (72 dpi),
// and cutting in half (/2) for mini-view

#define DIMENSION_INCH_SCALE_FACTOR	36

#define STORE_CONVERTED(m, v) \
            if (v) m = (UT_uint32) (UT_convertToInches(v) * (double) DIMENSION_INCH_SCALE_FACTOR);

#define SCALE_TO_PIXELS(s) ((UT_uint32) (UT_convertToInches(s) * (double) DIMENSION_INCH_SCALE_FACTOR))

void AP_Preview_Paragraph_Block::setFormat(const XML_Char * pageLeftMargin,
										   const XML_Char * pageRightMargin,
										   AP_Dialog_Paragraph::tAlignState align,
										   const XML_Char * firstLineIndent,
										   AP_Dialog_Paragraph::tIndentState indent,
										   const XML_Char * leftIndent,
										   const XML_Char * rightIndent,
										   const XML_Char * beforeSpacing,
										   const XML_Char * afterSpacing,
										   const XML_Char * lineSpacing,
										   AP_Dialog_Paragraph::tSpacingState spacing)
{
	// align is always set
	m_align = align;

	if(pageLeftMargin)
	{
		m_leftStop = _UL(SCALE_TO_PIXELS(pageLeftMargin));
	}
	else
	{
		m_leftStop = DEFAULT_LEFT_STOP;
	}

	// left margins are in or out from the default stop
	if (leftIndent)
	{
		m_leftStop += _UL(SCALE_TO_PIXELS(leftIndent));
		// NOTE : if we recomputed the leftIndent, we have to recompute
		// NOTE : the firstLineLeftStop below
	}

	if(pageRightMargin)
	{
		m_rightStop = _UL(SCALE_TO_PIXELS(pageRightMargin));
	}
	else
	{
		m_rightStop = DEFAULT_RIGHT_STOP;
	}

	// right margins are in or out from the default stop
	if (rightIndent)
		m_rightStop += _UL(SCALE_TO_PIXELS(rightIndent));

	STORE_CONVERTED(m_beforeSpacing, beforeSpacing);
	STORE_CONVERTED(m_afterSpacing, afterSpacing);
	_UUL(m_beforeSpacing);
	_UUL(m_afterSpacing);

	m_indent = indent;
	switch (m_indent)
	{
		// the signage for these two is handled in the conversion through
		// UT_convertToInches()
	case AP_Dialog_Paragraph::indent_FIRSTLINE:
		m_firstLineLeftStop = m_leftStop + _UL(SCALE_TO_PIXELS(firstLineIndent));
		break;
	case AP_Dialog_Paragraph::indent_HANGING:
		m_firstLineLeftStop = m_leftStop - _UL(SCALE_TO_PIXELS(firstLineIndent));
		break;
	case AP_Dialog_Paragraph::indent_NONE:
		m_firstLineLeftStop = m_leftStop;
		break;
	default:
		UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
	}

	if (lineSpacing)
	{
		m_spacing = spacing;
		switch (m_spacing)
		{
		case AP_Dialog_Paragraph::spacing_SINGLE:
			m_lineSpacing = 0;
			break;
		case AP_Dialog_Paragraph::spacing_ONEANDHALF:
			m_lineSpacing = (UT_uint32) ((double) m_fontHeight * (double) 0.5);
			break;
		case AP_Dialog_Paragraph::spacing_DOUBLE:
			m_lineSpacing = m_fontHeight;
			break;
		case AP_Dialog_Paragraph::spacing_ATLEAST:
			// TODO : THIS IS BROKEN SOMEHOW.  m_lineSpacing should be the number
			// TODO : of pixels needed to place before the line (of height
			// TODO : m_fontHeight pixels).

			// we measure from top to top here, and use a minimum of the current
			// line height
			if (_UL(SCALE_TO_PIXELS(lineSpacing)) > m_fontHeight)
				m_lineSpacing = _UL(SCALE_TO_PIXELS(lineSpacing)) - m_fontHeight;
			else
				m_lineSpacing = 0;
			break;
		case AP_Dialog_Paragraph::spacing_EXACTLY:
			// for exact, we always give them exactly what they asked for,
			// overlapping and all
			m_lineSpacing = _UL(SCALE_TO_PIXELS(lineSpacing));
			break;
		case AP_Dialog_Paragraph::spacing_MULTIPLE:
			m_lineSpacing = (UT_uint32) ((double) m_fontHeight
										 * (UT_convertDimensionless(lineSpacing) - (double) 1));
			break;
		}
	}

}


/************************************************************************/

AP_Preview_Paragraph::AP_Preview_Paragraph(GR_Graphics * gc,
										   const UT_UCSChar * text,
										   AP_Dialog_Lists * dlg)
  : XAP_Preview(gc), m_dir(FRIBIDI_TYPE_LTR)
{
	UT_ASSERT(text && dlg);

	m_font = NULL;
	m_fontHeight = 0;

	m_y = DEFAULT_TOP_MARGIN;

	m_clrWhite = new UT_RGBColor(255,255,255);
	m_clrBlack = new UT_RGBColor(0,0,0);
	m_clrGray = new UT_RGBColor(192,192,192);

	// initialize font to start measuring with for following setText calls
	_loadDrawFont();

	{
		// this block is a dummy block
		m_previousBlock = new AP_Preview_Paragraph_Block(*m_clrGray,
														 m_gc,
														 AP_Dialog_Paragraph::align_LEFT,
														 m_fontHeight);
		m_previousBlock->setFormat(NULL,
									NULL,
									AP_Dialog_Paragraph::align_LEFT,
									NULL,
									AP_Dialog_Paragraph::indent_NONE,
									NULL,NULL,NULL,NULL,NULL,
									AP_Dialog_Paragraph::spacing_SINGLE);
	}

	{
		// this block is our ACTIVE block
		m_activeBlock = new AP_Preview_Paragraph_Block(*m_clrBlack,
													   m_gc,
													   AP_Dialog_Paragraph::align_LEFT,
													   m_fontHeight);
		// read these from the dialog's members
#if 0
		m_activeBlock->setFormat(NULL,
									NULL,
									(AP_Dialog_Paragraph::tAlignState) dlg->_getMenuItemValue(AP_Dialog_Paragraph::id_MENU_ALIGNMENT),
									dlg->_getSpinItemValue(AP_Dialog_Paragraph::id_SPIN_SPECIAL_INDENT),
									(AP_Dialog_Paragraph::tIndentState) dlg->_getMenuItemValue(AP_Dialog_Paragraph::id_MENU_SPECIAL_INDENT),
									dlg->_getSpinItemValue(AP_Dialog_Paragraph::id_SPIN_LEFT_INDENT),
									dlg->_getSpinItemValue(AP_Dialog_Paragraph::id_SPIN_RIGHT_INDENT),
									dlg->_getSpinItemValue(AP_Dialog_Paragraph::id_SPIN_BEFORE_SPACING),
									dlg->_getSpinItemValue(AP_Dialog_Paragraph::id_SPIN_AFTER_SPACING),
									dlg->_getSpinItemValue(AP_Dialog_Paragraph::id_SPIN_SPECIAL_SPACING),
									(AP_Dialog_Paragraph::tSpacingState) dlg->_getMenuItemValue(AP_Dialog_Paragraph::id_MENU_SPECIAL_SPACING));
#endif
	}

	{
		// another dummy block
		m_followingBlock = new AP_Preview_Paragraph_Block(*m_clrGray,
														  m_gc,
														  AP_Dialog_Paragraph::align_LEFT,
														  m_fontHeight);
		m_followingBlock->setFormat(NULL,
									NULL,
									AP_Dialog_Paragraph::align_LEFT,
									NULL,
									AP_Dialog_Paragraph::indent_NONE,
									NULL,NULL,NULL,NULL,NULL,
									AP_Dialog_Paragraph::spacing_SINGLE);
	}

	const XAP_StringSet * pSS = dlg->getApp()->getStringSet();

	UT_UCSChar * tmp = NULL;

	UT_UCS4_cloneString_char(&tmp, pSS->getValue(AP_STRING_ID_DLG_Para_PreviewPrevParagraph));
	m_previousBlock->setText(tmp);
	FREEP(tmp);

	// this text came from the current document, passed in as arg
	m_activeBlock->setText(text);

	UT_UCS4_cloneString_char(&tmp, pSS->getValue(AP_STRING_ID_DLG_Para_PreviewFollowParagraph));
	m_followingBlock->setText(tmp);
	FREEP(tmp);
}

AP_Preview_Paragraph::AP_Preview_Paragraph(GR_Graphics * gc,
					   const UT_UCSChar * text,
										   XAP_Dialog * dlg) : XAP_Preview(gc), m_dir(FRIBIDI_TYPE_LTR)
{
  // this method heavily relies upon the parent dlg to call setFormat()
  // rather than auto-generating defaults
	UT_ASSERT(text && dlg);

	m_font = NULL;
	m_fontHeight = 0;

	m_y = DEFAULT_TOP_MARGIN;

	m_clrWhite = new UT_RGBColor(255,255,255);
	m_clrBlack = new UT_RGBColor(0,0,0);
	m_clrGray = new UT_RGBColor(192,192,192);

	// initialize font to start measuring with for following setText calls
	_loadDrawFont();

	{
	  // this block is a dummy block
	  m_previousBlock = new AP_Preview_Paragraph_Block(*m_clrGray,
							   m_gc,
							   AP_Dialog_Paragraph::align_LEFT,
							   m_fontHeight);
	}

	{
	  // this block is our ACTIVE block
	  m_activeBlock = new AP_Preview_Paragraph_Block(*m_clrBlack,
							 m_gc,
							 AP_Dialog_Paragraph::align_LEFT,
							 m_fontHeight);
	}

	{
	  // another dummy block
	  m_followingBlock = new AP_Preview_Paragraph_Block(*m_clrGray,
							    m_gc,
							    AP_Dialog_Paragraph::align_LEFT,
							    m_fontHeight);
	}

	const XAP_StringSet * pSS = dlg->getApp()->getStringSet();

	UT_UCSChar * tmp = NULL;

	UT_UCS4_cloneString_char(&tmp, pSS->getValue(AP_STRING_ID_DLG_Para_PreviewPrevParagraph));
	m_previousBlock->setText(tmp);
	FREEP(tmp);

	// this text came from the current document, passed in as arg
	m_activeBlock->setText(text);

	UT_UCS4_cloneString_char(&tmp, pSS->getValue(AP_STRING_ID_DLG_Para_PreviewFollowParagraph));
	m_followingBlock->setText(tmp);
	FREEP(tmp);

}

AP_Preview_Paragraph::AP_Preview_Paragraph(GR_Graphics * gc,
					   const UT_UCSChar * text,
					   AP_Dialog_Paragraph * dlg)
	: XAP_Preview(gc),m_dir(FRIBIDI_TYPE_LTR)
{
	UT_ASSERT(text && dlg);

	m_font = NULL;
	m_fontHeight = 0;

	m_y = DEFAULT_TOP_MARGIN;

	m_clrWhite = new UT_RGBColor(255,255,255);
	m_clrBlack = new UT_RGBColor(0,0,0);
	m_clrGray = new UT_RGBColor(192,192,192);

	// initialize font to start measuring with for following setText calls
	_loadDrawFont();

	{
		// this block is a dummy block
		m_previousBlock = new AP_Preview_Paragraph_Block(*m_clrGray,
														 m_gc,
														 AP_Dialog_Paragraph::align_LEFT,
														 m_fontHeight);
		m_previousBlock->setFormat(dlg->m_pageLeftMargin,
									dlg->m_pageRightMargin,
									(AP_Dialog_Paragraph::tAlignState) dlg->_getMenuItemValue(AP_Dialog_Paragraph::id_MENU_ALIGNMENT),
									NULL,
									AP_Dialog_Paragraph::indent_NONE,
									NULL,NULL,NULL,NULL,NULL,
									AP_Dialog_Paragraph::spacing_SINGLE);
	}

	{
		// this block is our ACTIVE block
		m_activeBlock = new AP_Preview_Paragraph_Block(*m_clrBlack,
													   m_gc,
													   AP_Dialog_Paragraph::align_LEFT,
													   m_fontHeight);
		// read these from the dialog's members
		m_activeBlock->setFormat(dlg->m_pageLeftMargin,
									dlg->m_pageRightMargin,
									(AP_Dialog_Paragraph::tAlignState) dlg->_getMenuItemValue(AP_Dialog_Paragraph::id_MENU_ALIGNMENT),
									dlg->_getSpinItemValue(AP_Dialog_Paragraph::id_SPIN_SPECIAL_INDENT),
									(AP_Dialog_Paragraph::tIndentState) dlg->_getMenuItemValue(AP_Dialog_Paragraph::id_MENU_SPECIAL_INDENT),
									dlg->_getSpinItemValue(AP_Dialog_Paragraph::id_SPIN_LEFT_INDENT),
									dlg->_getSpinItemValue(AP_Dialog_Paragraph::id_SPIN_RIGHT_INDENT),
									dlg->_getSpinItemValue(AP_Dialog_Paragraph::id_SPIN_BEFORE_SPACING),
									dlg->_getSpinItemValue(AP_Dialog_Paragraph::id_SPIN_AFTER_SPACING),
									dlg->_getSpinItemValue(AP_Dialog_Paragraph::id_SPIN_SPECIAL_SPACING),
									(AP_Dialog_Paragraph::tSpacingState) dlg->_getMenuItemValue(AP_Dialog_Paragraph::id_MENU_SPECIAL_SPACING));

		if(dlg->_getCheckItemValue(AP_Dialog_Paragraph::id_CHECK_DOMDIRECTION) == AP_Dialog_Paragraph::check_TRUE)
			m_dir = FRIBIDI_TYPE_RTL;
	}

	{
		// another dummy block
		m_followingBlock = new AP_Preview_Paragraph_Block(*m_clrGray,
														  m_gc,
														  AP_Dialog_Paragraph::align_LEFT,
														  m_fontHeight);
		m_followingBlock->setFormat(dlg->m_pageLeftMargin,
									dlg->m_pageRightMargin,
									(AP_Dialog_Paragraph::tAlignState) dlg->_getMenuItemValue(AP_Dialog_Paragraph::id_MENU_ALIGNMENT),
									NULL,
									AP_Dialog_Paragraph::indent_NONE,
									NULL,NULL,NULL,NULL,NULL,
									AP_Dialog_Paragraph::spacing_SINGLE);
	}

	const XAP_StringSet * pSS = dlg->m_pApp->getStringSet();


	UT_UCSChar * tmp = NULL;

	UT_UCS4_cloneString_char(&tmp, pSS->getValue(AP_STRING_ID_DLG_Para_PreviewPrevParagraph));
	m_previousBlock->setText(tmp);
	FREEP(tmp);

	// this text came from the current document, passed in as arg
	m_activeBlock->setText(text);

	UT_UCS4_cloneString_char(&tmp, pSS->getValue(AP_STRING_ID_DLG_Para_PreviewFollowParagraph));
	m_followingBlock->setText(tmp);
	FREEP(tmp);
}

AP_Preview_Paragraph::~AP_Preview_Paragraph()
{
	DELETEP(m_font);

	DELETEP(m_clrWhite);
	DELETEP(m_clrBlack);
	DELETEP(m_clrGray);

	DELETEP(m_previousBlock);
	DELETEP(m_activeBlock);
	DELETEP(m_followingBlock);
}

void AP_Preview_Paragraph::setFormat(const XML_Char * pageLeftMargin,
										const XML_Char * pageRightMargin,
										AP_Dialog_Paragraph::tAlignState align,
										const XML_Char * firstLineIndent,
										AP_Dialog_Paragraph::tIndentState indent,
										const XML_Char * leftIndent,
										const XML_Char * rightIndent,
										const XML_Char * beforeSpacing,
										const XML_Char * afterSpacing,
										const XML_Char * lineSpacing,
										AP_Dialog_Paragraph::tSpacingState spacing)
{
	UT_ASSERT(m_activeBlock);
	m_activeBlock->setFormat(pageLeftMargin, pageRightMargin,
								align, firstLineIndent, indent, leftIndent,
								rightIndent, beforeSpacing, afterSpacing,
								lineSpacing, spacing);
}

void AP_Preview_Paragraph::draw(void)
{
	UT_ASSERT(m_gc);

	// paint white background (Word 97's background is always white, the
	// text is always black, and the font is always the same size, regardless
	// of the current document's real block formatting).
	_drawPageBackground();

	// draw the three paragraphs
	_appendBlock(m_previousBlock);
	_appendBlock(m_activeBlock);
	_appendBlock(m_followingBlock);

	_drawPageBorder();

	m_y = DEFAULT_TOP_MARGIN;
}

bool AP_Preview_Paragraph::_loadDrawFont(void)
{
	// we draw at 7 points in this preview
	GR_Font * font = m_gc->findFont("Times New Roman", "normal", "", "normal", "", "7pt");

	if (font)
	{
		REPLACEP(m_font, font);
		m_gc->setFont(m_font);
		m_fontHeight = m_gc->getFontHeight();
		return true;
	}
	else
		return false;
}

void AP_Preview_Paragraph::_drawPageBackground(void)
{
	// clear area
	m_gc->fillRect(*m_clrWhite, 0, 0, _UL(getWindowWidth()), _UL(getWindowHeight()));
}

void AP_Preview_Paragraph::_drawPageBorder(void)
{
	// draw a black one pixel border
	m_gc->setColor(*m_clrBlack);
	m_gc->drawLine(0, 0, _UL(getWindowWidth()), 0);
	m_gc->drawLine(_UL(getWindowWidth()) - _UL(1), 0, _UL(getWindowWidth()) - _UL(1), _UL(getWindowHeight()));
	m_gc->drawLine(_UL(getWindowWidth()) - _UL(1), _UL(getWindowHeight()) - _UL(1), 0, _UL(getWindowHeight()) - _UL(1));
	m_gc->drawLine(0, _UL(getWindowHeight()) - _UL(1), 0, 0);
}


void AP_Preview_Paragraph::_appendBlock(AP_Preview_Paragraph_Block * block)
{
	UT_ASSERT(block);

	UT_uint32 ypre = 0;
	UT_uint32 ypost = 0;

	UT_uint32 wordCounter = 0;
	UT_uint32 wordCount = block->m_words.getItemCount();

	m_gc->setColor(block->m_clr);

	{
		// is there any "at least" or "exactly" spacing for this block?
		// we have to land the baseline in the right spot then
		switch (block->m_spacing)
		{
		case AP_Dialog_Paragraph::spacing_SINGLE:
		case AP_Dialog_Paragraph::spacing_ONEANDHALF:
		case AP_Dialog_Paragraph::spacing_DOUBLE:
		case AP_Dialog_Paragraph::spacing_MULTIPLE:
			ypost = block->m_lineSpacing;
			break;
		case AP_Dialog_Paragraph::spacing_ATLEAST:
		case AP_Dialog_Paragraph::spacing_EXACTLY:
			ypre = block->m_lineSpacing;
			break;
		default:
			UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
		}
	}

	// start y at m_y;
	UT_uint32 y = m_y;

	// do before block spacing
	y += block->m_beforeSpacing;

	// handle any spacing before first line
	y += ypre;
	// draw first line
	wordCounter += _appendLine(&block->m_words,
							   &block->m_widths,
							   0,
							   block->m_firstLineLeftStop,
							   block->m_rightStop,
							   block->m_align,
							   y);
	y += block->m_fontHeight;
	// handle any spacing after first line
	y += ypost;

	// handle all other lines until out of words
	UT_uint32 newWords = 1;
	while (wordCounter < wordCount && newWords > 0)
	{
		// handle any spacing before this line
		y += ypre;

		newWords = _appendLine(&block->m_words,
					      	   &block->m_widths,
							   wordCounter,
							   block->m_leftStop,
							   block->m_rightStop,
							   block->m_align,
							   y);

		wordCounter += newWords;

		y += block->m_fontHeight;
		// handle any spacing after this line
		y += ypost;
	}

	// do after block spacing
	y += block->m_afterSpacing;

	// record the changes
	m_y = y;
}

// returns number of words it plotted
UT_uint32 AP_Preview_Paragraph::_appendLine(UT_Vector * words,
											UT_Vector * widths,
											UT_uint32 startWithWord,
											UT_uint32 left,
											UT_uint32 right,
											AP_Dialog_Paragraph::tAlignState align,
											UT_uint32 y)
{

	UT_ASSERT(words && widths);

	// width of space character in pixels
	UT_sint32 spaceCharWidth = _UL(3);

	UT_uint32 i = 0;
	UT_uint32 totalWords = words->getItemCount();

	UT_sint32 pixelsForThisLine = 0;

	// max length of first line is the diff between the (special)
	// left stop and the (normal) right stop
	UT_sint32 maxPixelsForThisLine = _UL(getWindowWidth()) - left - right;

	// negative or zero makes no sense; bail in that case (callers can deal)
	if (maxPixelsForThisLine <= 0)
	  return 0;

	i = startWithWord;

	// while we're not out of words AND have space, try to pack more onto this line
	// NOTE : we don't evaluate space widths in the while() condition so we don't
	// NOTE : wrap on one (which would be silly)
	while ((i < totalWords) &&
		   (pixelsForThisLine + (UT_uint32) widths->getNthItem(i) <= (UT_uint32)maxPixelsForThisLine))
	{
		pixelsForThisLine += (UT_uint32) widths->getNthItem(i) + spaceCharWidth;
		i++;
	}

	if(i == startWithWord)
	{
		// HACK: Make sure we have at least one word. (no longer true, because of above)

		pixelsForThisLine += (UT_uint32) widths->getNthItem(i) + spaceCharWidth;
		i++;
	}

	// we have "i" words to plot on this line, and they will take pixelsForThisLine space

	// TODO : maybe rework following code to remove this variable for more speed

	UT_uint32 willDrawAt = left;

	if(m_dir == FRIBIDI_TYPE_RTL)
		willDrawAt += maxPixelsForThisLine;

 	spaceCharWidth <<= 8;	// Calculate spacing at 256 times the resolution

	// obey alignment requests
 	switch(align)
 	{
 	case AP_Dialog_Paragraph::align_RIGHT:
		if(m_dir == FRIBIDI_TYPE_LTR)

	    // for right, we just draw at the difference in spaces added onto the first line stop.
	    willDrawAt = left + (maxPixelsForThisLine - pixelsForThisLine);
		break;
	case AP_Dialog_Paragraph::align_CENTERED:
		// for centered, we split the difference
		willDrawAt = left + (maxPixelsForThisLine - pixelsForThisLine) / 2;
		break;
	case AP_Dialog_Paragraph::align_JUSTIFIED:
		if(i < totalWords)
		{
			spaceCharWidth += (UT_sint32)((double)(maxPixelsForThisLine - pixelsForThisLine) /
														(i - startWithWord) * 256);
		}
		break;
	default:
		// aligh_LEFT is caught here
		if(m_dir == FRIBIDI_TYPE_RTL)
			willDrawAt =  pixelsForThisLine + left;

		break;
	}

	willDrawAt <<= 8;

	UT_uint32 k;

	FriBidiChar fb1[100];
	FriBidiChar fb2[100];
	UT_UCSChar  str[100];
	UT_uint32 j, iLen;

	for (k = startWithWord; k < i; k++)
	{
		// this will not produce correct results in true bidi text, since the words that are inconsistend
		// with the overall pargraph direction will be in wrong order, but that is not a big deal
  	    iLen = UT_UCS4_strlen((UT_UCSChar *) words->getNthItem(k));
	    for(j = 0; j < iLen; j++)
		    fb1[j] = ((UT_UCSChar *) words->getNthItem(k))[j];

		fribidi_log2vis (		/* input */
						 &fb1[0],
						 iLen,
						 &m_dir,
						 /* output */
						 &fb2[0],
						 NULL,
						 NULL,
						 NULL);

		for(j = 0; j < iLen; j++)
		    str[j] = (UT_UCSChar)fb2[j];

		if(m_dir == FRIBIDI_TYPE_RTL)
		    willDrawAt -= (((UT_uint32) widths->getNthItem(k)) << 8) + spaceCharWidth;

		m_gc->drawChars(str, 0,	iLen, willDrawAt >> 8, y);

		if(m_dir == FRIBIDI_TYPE_LTR)
		    willDrawAt += (((UT_uint32) widths->getNthItem(k)) << 8) + spaceCharWidth;
	}

	// return number of words drawn
	return k - startWithWord;
}
