/*
 * 
 * Copyright (C) 2002 by Dom Lachowicz
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

#ifndef MAGICK_GRAPHICS_H
#define MAGICK_GRAPHICS_H

#include <Magick++.h>
#include <string>
#include <list>

#include "gr_Graphics.h"
#include "gr_Image.h"
#include "ut_misc.h"
#include "ut_bytebuf.h"

class GR_MagickFont ;

/**
 * Interface whose sole purpose is to receive imageEvents
 * from the MagickGraphics class and deal with them appropriately
 */
class GR_MagickImageEventListener
{
    public:
    
        /**
         * Dummy c'tor
         */
        GR_MagickImageEventListener () ;
    
        /**
         * Dummy virtual d'tor
         */
        virtual ~GR_MagickImageEventListener () ;
        
        /**
         * Called with a non-null bytebuf \param pBytes containing image data in the format
         * \param szFormat
         */
        virtual void imageEvent ( const UT_ByteBuf * pBytes, const std::string & szFormat, bool isMultiFrame ) = 0 ;
} ;

// ------

class GR_MagickImage : public GR_Image
{
    public:
    
  GR_MagickImage(const char * szName);
    
        virtual ~GR_MagickImage () ;

        virtual GR_Image::GRType getType(void) const ;

	virtual UT_sint32	getDisplayWidth(void) const;
	virtual UT_sint32	getDisplayHeight(void) const;

	virtual bool convertToBuffer(UT_ByteBuf** ppBB) const ;                
	virtual bool convertFromBuffer(const UT_ByteBuf* pBB, UT_sint32 iDisplayWidth, UT_sint32 iDisplayHeight) ;    
        
        Magick::Image & getImage () ;
    
    private:
    
        Magick::Image mImage ;	
} ;

// ------

class GR_MagickGraphics : public GR_Graphics
{
    public:

        GR_MagickGraphics ( const std::string & inSaveFormat = "png" , bool bUseMultiFrameIfAppropriate = true) ;
        virtual ~GR_MagickGraphics () ;

        void setSaveFormat ( const std::string & inSaveFormat, bool bUseMultiFrameIfAppropriate = true ) ;
        std::string getSaveFormat () const ;
        inline bool isMutliFrame () const { return mBMultiFrame ; }

        void addListener ( GR_MagickImageEventListener * listener ) ;
        bool removeListener ( GR_MagickImageEventListener * listener ) ;

        virtual UT_uint32 measureUnRemappedChar (unsigned int ch);
        virtual void getCoverage (UT_Vector &) ;

	virtual void getColor(UT_RGBColor&)
	  {
	    //UT_ASSERT_NOT_REACHED();
	  }

	virtual bool startPrint () ;
	virtual bool endPrint () ;
	virtual bool startPage (const char *szPageLabel, 
				UT_uint32 pageNumber, bool isPortrait, 
				UT_uint32 iWidth, UT_uint32 iHeight) ;

	virtual void setFont(GR_Font* pFont) ;
	virtual UT_uint32 getFontAscent() ;
	virtual UT_uint32 getFontDescent() ;
	virtual UT_uint32 getFontHeight() ;
	virtual UT_uint32 getFontAscent(GR_Font * pFont) ;
	virtual UT_uint32 getFontDescent(GR_Font * pFont) ;
	virtual UT_uint32 getFontHeight(GR_Font * pFont) ;
	virtual GR_Font* getGUIFont() ;
	virtual GR_Font*  findFont(const char* pszFontFamily,
				   const char* pszFontStyle,
				   const char* pszFontVariant,
				   const char* pszFontWeight,
				   const char* pszFontStretch,
				   const char* pszFontSize) ;
        virtual void setColor (const UT_RGBColor& clr) ;       
        virtual void setLineWidth(UT_sint32 width) ;
        
	virtual void drawGlyph (UT_uint32 glyph_idx, UT_sint32 xoff, UT_sint32 yoff) ;
	virtual void drawChars(const UT_UCSChar* pChars,
                                int iCharOffset,
				int iLength,
				UT_sint32 xoff,
				UT_sint32 yoff,
				int* pCharWidths = NULL) ;
                                       
        virtual void drawImage(GR_Image* pImg, UT_sint32 xDest, UT_sint32 yDest) ;
	virtual void drawLine(UT_sint32 x1, UT_sint32 y1, UT_sint32 x2, UT_sint32 y2) ;
	virtual void fillRect(const UT_RGBColor& c,
                              UT_sint32 x,
                              UT_sint32 y,
                              UT_sint32 w,
                              UT_sint32 h) ;
	virtual bool queryProperties(GR_Graphics::Properties gp) const ;
        virtual GR_Image* createNewImage(const char* pszName, 
                                         const UT_ByteBuf* pBB, 
					 UT_sint32 iDisplayWidth,
					 UT_sint32 iDisplayHeight, 
					 GR_Image::GRType iType) ;
	virtual void polyLine(UT_Point * pts, UT_uint32 nPoints) ;
	virtual void xorLine(UT_sint32, UT_sint32, UT_sint32, UT_sint32) ;
	virtual void invertRect(const UT_Rect* pRect) ;
	virtual void setClipRect(const UT_Rect* pRect) ;
	virtual void scroll(UT_sint32, UT_sint32) ;
	virtual void scroll(UT_sint32 x_dest,
                            UT_sint32 y_dest,
                            UT_sint32 x_src,
                            UT_sint32 y_src,
                            UT_sint32 width,
                            UT_sint32 height) ;
	virtual void clearArea(UT_sint32, UT_sint32, UT_sint32, UT_sint32) ;
	virtual void setColorSpace(GR_Graphics::ColorSpace c) ;
	virtual GR_Graphics::ColorSpace getColorSpace(void) const ;
	virtual void setCursor(GR_Graphics::Cursor c) ;
	virtual GR_Graphics::Cursor getCursor(void) const ;
	virtual void setColor3D(GR_Color3D c) ;        
	virtual void fillRect(GR_Color3D c,
			      UT_sint32 x,
			      UT_sint32 y,
			      UT_sint32 w,
			      UT_sint32 h) ;
	virtual void fillRect(GR_Color3D c, UT_Rect &r) ;
	
	virtual void	  saveRectangle(UT_Rect & r) {}
	virtual void	  restoreRectangle() {}

protected:

        virtual UT_uint32 _getResolution(void) const ;
private:

        void notifyListeners ( const UT_ByteBuf & bytes ) ;
        void cleanupListeners () ;
        void endPage () ;
        void newCanvas ( UT_uint32 iWidth, UT_uint32 iHeight ) ;
        void pushDrawable ( const Magick::Drawable & drawable ) ;
        void paintCanvas () ;
        void clearCanvas () ;
        Magick::ColorRGB toMagickRGB (const UT_RGBColor & clr) ;
        
        UT_uint32 scaleXCoord ( UT_uint32 inX ) const ;
        UT_uint32 scaleYCoord ( UT_uint32 inY ) const ;

   private:
   
        GR_MagickGraphics ( const GR_MagickGraphics & other ) ;
        GR_MagickGraphics& operator= ( const GR_MagickGraphics & other ) ;

        Magick::Image * mCanvas ;
        std::list< Magick::Image > mFrames ;
        Magick::DrawableList mCommandStack  ;

        std::list<GR_MagickImageEventListener *> mEventListeners ;

        std::string mSaveFormat ;
        bool mStartedPrint ;
        bool mStartedPage ;
        
        GR_MagickFont * mFont ;
        
        bool mBMultiFrame ;
} ;

#endif // MAGIC_GRAPHICS_H
