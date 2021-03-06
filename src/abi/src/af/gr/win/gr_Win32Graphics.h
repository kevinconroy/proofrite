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



#ifndef GR_WIN32GRAPHICS_H
#define GR_WIN32GRAPHICS_H

#include <windows.h>
#include "ut_misc.h"
#include "gr_Graphics.h"
#include "gr_Win32CharWidths.h"
#include "gr_Win32InkOverlay.h"

class UT_ByteBuf;

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

class GR_Win32Font : public GR_Font
{
public:
	GR_Win32Font(HFONT hFont);
	~GR_Win32Font();


	// make GR_Win32Graphics an "aquaintance" of GR_Win32Font
	class Acq
	{
		friend class GR_Win32Graphics;
	private:

		static inline HFONT		getHFONT(GR_Win32Font& font)
		{ return font.m_hFont; };
#if 0
		static UT_uint32	measureString(	GR_Win32Font& font,
			const UT_UCSChar* s,
			int iOffset,
			int num,
			unsigned short* pWidths);
#endif
		static UT_uint32	measureUnRemappedChar(	GR_Win32Font& font,
			UT_UCSChar c);
		static const GR_Win32CharWidths&
			getCharWidths(const GR_Win32Font& font)
		{ return font.m_cw; };
		static UT_uint32	getAscent(const GR_Win32Font& font)
		{ return font.m_tm.tmAscent; };
		static UT_uint32	getDescent(const GR_Win32Font& font)
		{ return font.m_tm.tmDescent; };
		static UT_uint32	getFontHeight(const GR_Win32Font& font)
		{ return font.m_tm.tmHeight; };

		static void				selectFontIntoDC(GR_Win32Font& font, HDC hdc);
	};
	friend class Acq;

private:
	void					setupFontInfo();
	HDC						m_oldHDC;
	HFONT					m_hFont;
	UT_uint32				m_defaultCharWidth;
	TEXTMETRIC				m_tm;
	GR_Win32CharWidths		m_cw;
};

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

class GR_Win32Graphics : public GR_Graphics
{
public:
	GR_Win32Graphics(HDC, HWND, XAP_App *, GR_Win32InkOverlay *);					/* for screen */
	GR_Win32Graphics(HDC, const DOCINFO *, XAP_App *, GR_Win32InkOverlay *);		/* for printing */
	~GR_Win32Graphics();

	virtual void			drawGlyph(UT_uint32 glyph_idx, UT_sint32 xoff, UT_sint32 yoff);
	virtual void			drawChar(UT_UCSChar Char, UT_sint32 xoff, UT_sint32 yoff);
	virtual void			drawChars(const UT_UCSChar* pChars,
		int iCharOffset, int iLength,
		UT_sint32 xoff, UT_sint32 yoff,
		int * pCharWidth);
	virtual void			setFont(GR_Font* pFont);
	virtual UT_uint32		getFontHeight();
	//virtual UT_uint32		measureString(const UT_UCSChar*s, int iOffset, int num, unsigned short* pWidths);
	virtual UT_uint32		measureUnRemappedChar(const UT_UCSChar c);
	virtual void			setColor(const UT_RGBColor& clr);
	virtual void            getColor(UT_RGBColor& clr);
	virtual GR_Font*		getGUIFont();
	virtual GR_Font*		findFont(const char* pszFontFamily,
		const char* pszFontStyle,
		const char* pszFontVariant,
		const char* pszFontWeight,
		const char* pszFontStretch,
		const char* pszFontSize);
	virtual UT_uint32		getFontAscent();
	virtual UT_uint32		getFontDescent();
	virtual void			getCoverage(UT_Vector& coverage);
	virtual void			drawLine(UT_sint32, UT_sint32, UT_sint32, UT_sint32);
	virtual void			xorLine(UT_sint32, UT_sint32, UT_sint32, UT_sint32);
	virtual void			setLineWidth(UT_sint32);

	virtual void            setLineProperties ( double inWidthPixels,
		JoinStyle inJoinStyle = JOIN_MITER,
		CapStyle inCapStyle   = CAP_BUTT,
		LineStyle inLineStyle = LINE_SOLID );

	virtual void			polyLine(UT_Point * pts, UT_uint32 nPoints);
	virtual void			fillRect(const UT_RGBColor& c,
		UT_sint32 x, UT_sint32 y,
		UT_sint32 w, UT_sint32 h);
	virtual void			invertRect(const UT_Rect* pRect);
	virtual void			setClipRect(const UT_Rect* pRect);
	virtual void			scroll(UT_sint32 dx, UT_sint32 dy);
	virtual void			scroll(UT_sint32 x_dest, UT_sint32 y_dest,
		UT_sint32 x_src, UT_sint32 y_src,
		UT_sint32 width, UT_sint32 height);
	virtual void			clearArea(UT_sint32, UT_sint32, UT_sint32, UT_sint32);

	virtual void			drawImage(GR_Image* pImg, UT_sint32 xDest, UT_sint32 yDest);
	virtual GR_Image*		createNewImage(const char* pszName, const UT_ByteBuf* pBB,
		UT_sint32 iDisplayWidth, UT_sint32 iDisplayHeight, GR_Image::GRType iType = GR_Image::GRT_Raster);

	virtual bool			queryProperties(GR_Graphics::Properties gp) const;

	virtual bool			startPrint(void);
	virtual bool			startPage(const char * szPageLabel, UT_uint32 pageNumber,
		bool bPortrait, UT_uint32 iWidth, UT_uint32 iHeight);
	virtual bool			endPrint(void);

	virtual HWND			getHwnd(void) const;

	virtual void			setColorSpace(GR_Graphics::ColorSpace c);
	virtual GR_Graphics::ColorSpace		getColorSpace(void) const;

	virtual void			setCursor(GR_Graphics::Cursor c);
	virtual GR_Graphics::Cursor			getCursor(void) const;
	virtual void			handleSetCursorMessage(void);

	virtual void			setColor3D(GR_Color3D c);
	void					init3dColors(void);
	virtual void			fillRect(GR_Color3D c,
		UT_sint32 x, UT_sint32 y,
		UT_sint32 w, UT_sint32 h);
	virtual void			fillRect(GR_Color3D c, UT_Rect &r);
	virtual void            polygon(UT_RGBColor& c,UT_Point *pts,UT_uint32 nPoints);
	virtual UT_uint32		getFontAscent(GR_Font *);
	virtual UT_uint32		getFontDescent(GR_Font *);
	virtual UT_uint32		getFontHeight(GR_Font *);
	virtual UT_sint32       getScreenResolution(void){return s_iScreenResolution;};
	virtual void		  saveRectangle(UT_Rect & r, UT_uint32 iIndx);
	virtual void		  restoreRectangle(UT_uint32 iIndx);

	void setBrush(HBRUSH hBrush){ m_hClearBrush = hBrush;};
	virtual HDC getHDC() { return m_hdc; };

	// KMC: ink
	virtual bool hasInkOverlay();
	virtual GR_Win32InkOverlay * getInkOverlay(); 
	void		refreshScreen();

protected:
	// KMC: ink
	GR_Win32InkOverlay * m_pInkOverlay;

	virtual UT_uint32 		_getResolution(void) const;
	void					_setColor(DWORD clrRef);

	HDC						m_hdc;
	HDC           m_printerDC;
	HWND 					m_hwnd;
	const DOCINFO *			m_pDocInfo;
	bool					m_bPrint;
	bool					m_bStartPrint;
	bool					m_bStartPage;
	GR_Win32Font*			m_pFont;
	GR_Win32Font*			m_pFontGUI;
	UT_sint32				m_iLineWidth;
	JoinStyle               m_eJoinStyle;
	CapStyle                m_eCapStyle;
	LineStyle               m_eLineStyle;

	GR_Graphics::ColorSpace m_cs;
	GR_Graphics::Cursor		m_cursor;

	DWORD					m_clrCurrent;
	DWORD					m_3dColors[COUNT_3D_COLORS];

private:
	void 					_constructorCommonCode(HDC);
	UT_uint16*				_remapGlyphs(const UT_UCSChar* pChars, int iCharOffset, int &iLength, int * pCharWidths);
	virtual bool            _setTransform(const GR_Transform & tr);

	DWORD					m_clrXorPen;
	HPEN					m_hXorPen;

	UT_UCS2Char*			m_remapBuffer;
	UT_uint32				m_remapBufferSize;
	// we will make this static, so that it gets initialized by the first instance of the class
	// since we have to construct a screen graphics before we can print, this should guarantee
	// us the correct hdc
	static UT_sint32        s_iScreenResolution;
	UT_UCS2Char*				m_remapIndices;

#ifndef USE_LAYOUT_UNITS
	static UT_sint32*       s_pCharAdvances;
	static UT_uint32        s_iCharAdvancesSize;
	static UT_uint32        s_iInstanceCount;
#endif

	UT_RGBColor				m_curColor;
	UT_Vector				m_vSaveRect;
	UT_Vector 				m_vSaveRectBuf;
	HBRUSH					m_hClearBrush;
};

#endif /* GR_WIN32GRAPHICS_H */
