/* -*- mode: C++; tab-width: 4; c-basic-offset: 4; -*- */

/* Abiword
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

#ifndef GR_UNIXGRAPHICS_H
#define GR_UNIXGRAPHICS_H

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include "xap_UnixApp.h"
#include "xap_UnixFont.h"
#include "xap_Frame.h"
#include "gr_Graphics.h"
#include "ut_vector.h"

#ifdef USE_XFT
#include <X11/Xft/Xft.h>
#endif

class UT_ByteBuf;
class UT_String;
class UT_Wctomb;

class GR_UnixGraphics : public GR_Graphics
{
 public:
#ifndef WITH_PANGO
 	GR_UnixGraphics(GdkWindow * win, XAP_UnixFontManager * fontManager, XAP_App *app);
#else
 	GR_UnixGraphics(GdkWindow * win, XAP_App *app);
#endif
	virtual ~GR_UnixGraphics();

#ifndef WITH_PANGO 
	virtual void        drawGlyph(UT_uint32 glyph_idx, UT_sint32 xoff, UT_sint32 yoff);
	virtual void		drawChars(const UT_UCSChar* pChars, int iCharOffset,
								  int iLength, UT_sint32 xoff, UT_sint32 yoff,
								  int * pCharWidths = NULL);
	virtual void		setFont(GR_Font* pFont);
	virtual UT_uint32	getFontHeight();
	// virtual UT_uint32	measureString(const UT_UCSChar*s, int iOffset, int num, unsigned short* pWidths);
	virtual UT_uint32 measureUnRemappedChar(const UT_UCSChar c);
#endif	
	virtual void		setColor(const UT_RGBColor& clr);
	virtual void        getColor(UT_RGBColor &clr);

	virtual GR_Font*	getGUIFont();

#ifndef WITH_PANGO 	
	virtual GR_Font*	findFont(const char* pszFontFamily, 
								 const char* pszFontStyle, 
								 const char* pszFontVariant, 
								 const char* pszFontWeight, 
								 const char* pszFontStretch, 
								 const char* pszFontSize);
	virtual GR_Font*	getDefaultFont(UT_String& fontFamily);

	virtual UT_uint32	getFontAscent();
	virtual UT_uint32	getFontDescent();

	virtual void		getCoverage(UT_Vector& coverage);
#endif	
	virtual void		drawLine(UT_sint32, UT_sint32, UT_sint32, UT_sint32);
	virtual void		setLineWidth(UT_sint32);
	virtual void		xorLine(UT_sint32, UT_sint32, UT_sint32, UT_sint32);
	virtual void		polyLine(UT_Point * pts, UT_uint32 nPoints);
	virtual void		fillRect(const UT_RGBColor& c,
								 UT_sint32 x, UT_sint32 y,
								 UT_sint32 w, UT_sint32 h);
	virtual void		invertRect(const UT_Rect* pRect);
	virtual void		setClipRect(const UT_Rect* pRect);
	virtual void		scroll(UT_sint32, UT_sint32);
	virtual void		scroll(UT_sint32 x_dest, UT_sint32 y_dest,
							   UT_sint32 x_src, UT_sint32 y_src,
							   UT_sint32 width, UT_sint32 height);
	virtual void		clearArea(UT_sint32, UT_sint32, UT_sint32, UT_sint32);
  
	virtual void		drawImage(GR_Image* pImg, UT_sint32 xDest, UT_sint32 yDest);
	virtual GR_Image*	createNewImage(const char* pszName, const UT_ByteBuf* pBB,
					       UT_sint32 iDisplayWidth, UT_sint32 iDisplayHeight,
					       GR_Image::GRType = GR_Image::GRT_Raster);
  
	virtual bool		queryProperties(GR_Graphics::Properties gp) const;
	virtual bool		startPrint(void);
	virtual bool		startPage(const char * szPageLabel, UT_uint32 pageNumber,
								  bool bPortrait, UT_uint32 iWidth, UT_uint32 iHeight);
	virtual bool		endPrint(void);

	virtual void		flush(void);

	virtual void		setColorSpace(GR_Graphics::ColorSpace c);
	virtual GR_Graphics::ColorSpace getColorSpace(void) const;
	
	virtual void		setCursor(GR_Graphics::Cursor c);
	virtual GR_Graphics::Cursor getCursor(void) const;

	virtual void		setColor3D(GR_Color3D c);
	void				init3dColors(GtkStyle * pStyle);
	virtual void		fillRect(GR_Color3D c,
								 UT_sint32 x, UT_sint32 y,
								 UT_sint32 w, UT_sint32 h);
	virtual void		fillRect(GR_Color3D c, UT_Rect &r);
	
	virtual void		polygon(UT_RGBColor& c,UT_Point *pts,UT_uint32 nPoints);

	void                createPixmapFromXPM( char ** pXPM,GdkPixmap *source,
											 GdkBitmap * mask);

	virtual void setLineProperties ( double inWidthPixels, 
					 GR_Graphics::JoinStyle inJoinStyle = JOIN_MITER,
					 GR_Graphics::CapStyle inCapStyle   = CAP_BUTT,
					 GR_Graphics::LineStyle inLineStyle = LINE_SOLID ) ;

#ifndef WITH_PANGO 	
	/* GR_Font versions of the above -- TODO: should I add drawChar* methods too? */
	virtual UT_uint32 getFontAscent(GR_Font *);
	virtual UT_uint32 getFontDescent(GR_Font *);
	virtual UT_uint32 getFontHeight(GR_Font *);
#else
 private:
	virtual void _drawFT2Bitmap(UT_sint32 x, UT_sint32 y, FT_Bitmap * pBitmap) const;
#endif
	virtual void	  saveRectangle(UT_Rect & r, UT_uint32 iIndx);
	virtual void	  restoreRectangle(UT_uint32 iIndx);
	
 protected:
	virtual UT_uint32 	_getResolution(void) const;
	void				_setColor(GdkColor & c);
#ifndef WITH_PANGO
	XAP_UnixFontManager * 	m_pFontManager;
#endif	

#if (!defined(WITH_PANGO) || !defined(USE_XFT))
	/* variables used by WCTOMB_DECLS and CONVERT_TO_MBS(c)
	 */
	UT_Wctomb *				m_wctomb;
	char					m_text[1];
	int						m_text_length;
	int						m_fallback_used;
#endif	

	GdkGC*       			m_pGC;
	GdkGC*  	      		m_pXORGC;
	GdkWindow*  	  		m_pWin;

#ifndef WITH_PANGO	
	// our currently requested font by handle
	XAP_UnixFontHandle *	m_pFont;
#endif
	// Current GDK fonts corresponding to this. Calling m_pFont->explodeGdkFont
	// causes gdk_font_load to be called and memory to be allocated. This should
	// not happen on every draw
	GdkFont * m_pSingleByteFont, * m_pMultiByteFont;

	// our "OEM" system font, like a 10 point Helvetica for GUI items
	static XAP_UnixFontHandle *	s_pFontGUI;
	static UT_uint32		s_iInstanceCount;
  
	GdkColormap* 	 		m_pColormap;
	int          			m_iWindowHeight, m_iWindowWidth;
	UT_sint32				m_iLineWidth;
	GR_Graphics::Cursor		m_cursor;

	GR_Graphics::ColorSpace	m_cs;
	
	GdkColor				m_3dColors[COUNT_3D_COLORS];
private:
#ifndef WITH_PANGO 	
	XAP_UnixFontHandle *	m_pFallBackFontHandle;
#endif

#ifdef USE_XFT
	XftDraw*				m_pXftDraw;
	XftColor				m_XftColor;
	XftFont*				m_pXftFont;
	XftFaceLocker			m_XftFaceLocker;
	
	Drawable				m_Drawable;
	Visual*					m_pVisual;
	Colormap				m_Colormap;

	FcChar32				m_aMap[FC_CHARSET_MAP_SIZE];
	// hack
	bool					m_bLayoutUnits;
	UT_sint32               m_iXoff;
	UT_sint32               m_iYoff;
#endif
	UT_RGBColor				m_curColor;

	UT_Vector				m_vSaveRect;
	UT_Vector 				m_vSaveRectBuf;

	bool                    m_bIsSymbol;       
	bool                    m_bIsDingbat;       
};

#endif /* GR_UNIXGRAPHICS_H */
