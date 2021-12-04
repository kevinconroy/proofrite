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

#include <algorithm>
#include "MagickGraphics.h"
#include "ut_string_class.h"
#include "xap_App.h"

#include "ut_assert.h"
#include "ut_debugmsg.h"

/******************************************************************/
/* GR_MagickFont */
/******************************************************************/

enum
  {
    LIGHT_WEIGHT   = 100,
    DEFAULT_WEIGHT = 100,
    BOLD_WEIGHT    = 500,
    HEAVY_WEIGHT   = 700
  } ;

static std::string abiToMagicFont( const std::string & inAbiFont )
{
#if 0

#if !defined(DONT_REMAP_FONTS)
#define NO_MAPPED_FONT_CLOSEST(f,r) r
#else
#define NO_MAPPED_FONT_CLOSEST(f,r) f
#endif

#define NO_MAPPED_FONT(f) NO_MAPPED_FONT_CLOSEST(f, "Times-Roman")

  if ( "Arial" == inAbiFont )
    return "" ;
  if ( "AvantGarde" == inAbiFont )
    return "AvantGarde" ;
  if ( "Bitstream" == inAbiFont || "Bitream Charter" == inAbiFont )
    return NO_MAPPED_FONT_CLOSEST(inAbiFont, "Palatino") ;
  if ( "Bookman" == inAbiFont )
    return "Bookman" ;
  if ( "Century Schoolbook" == inAbiFont )
    return "NewCenturySchlbk" ;
  if ( "Courier" == inAbiFont )
    return "Courier" ;
  if ( "Courier New" == inAbiFont )
    return NO_MAPPED_FONT_CLOSEST(inAbiFont, "Courier") ; // not really...
  if ( "Dingbats" == inAbiFont )
    return NO_MAPPED_FONT_CLOSEST(inAbiFont, "Symbol") ;
  if ( "Gothic" == inAbiFont )
    return NO_MAPPED_FONT_CLOSEST(inAbiFont, "Palatino");
  if ( "Helvetic" == inAbiFont || "Helvetica" == inAbiFont )
    return "Helvetica" ;
  if ( "Symbol" == inAbiFont )
    return "Symbol" ;
  if ( "Times" == inAbiFont || "Times Roman" == inAbiFont
       || "Times New Roman" == inAbiFont )
    return "Times-Roman";
  return NO_MAPPED_FONT(inAbiFont) ;

#else

  // work around bug in ImageMagick for the time being until 5.4.9 comes out
  return UT_String_sprintf ( "'%s'", inAbiFont.c_str() ).c_str() ;

#endif
}

class GR_MagickFont : public GR_Font
{
public:
  
  GR_MagickFont ( const char* pszFontFamily,
                  const char* pszFontStyle,
                  const char* pszFontVariant,
                  const char* pszFontWeight,
                  const char* pszFontStretch,
                  const char* pszFontSize )
    : GR_Font (), mFont ( "Times-Roman", Magick::NormalStyle, DEFAULT_WEIGHT, Magick::NormalStretch ), mSize ( 12 ) 
  {
    try
      {
        Magick::StyleType theStyle      = Magick::NormalStyle ;
        unsigned long theWeight = DEFAULT_WEIGHT ;
        Magick::StretchType theStretch  = Magick::NormalStretch ;
        
        if ( pszFontWeight && !UT_strcmp(pszFontWeight, "bold") )
          theWeight = BOLD_WEIGHT ;
        
        if ( pszFontStyle && !UT_strcmp(pszFontStyle, "italic") )
          theStyle = Magick::ItalicStyle ;
        else if ( pszFontStyle && !UT_strcmp(pszFontStyle, "oblique") )
          theStyle = Magick::ObliqueStyle ;
        
        if ( pszFontSize )
          {
#if 0
            // TODO - proper layout units stuff
            mSize = getAppropriateFontSizeFromString( pszFontSize ) ;
#else
            mSize = atoi ( pszFontSize ) ;
#endif
          }
        
        // create a new drawable font
        mFont = Magick::DrawableFont ( abiToMagicFont ( pszFontFamily ), theStyle, theWeight, theStretch ) ; 
        
        // inject these metrics into our offscreen image
        mOffscreen.textEncoding ( "UTF-8" ) ;
        mOffscreen.font ( mFont.font () ) ;
        mOffscreen.fontPointsize ( mSize ) ;
        
        // TODO: better way of doing something similar to this. we can ensure that unicode glyphs get handled
        // TODO: correctly iff we can ensure that a measureString call happens before any 'getXXX' call

        // setup the font metrics so that the getAscent, getDescent, getHeight calls work
        mOffscreen.fontTypeMetrics ( "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-=[]\\;',./ !@#$%^&*()_+{}|:\"<>?`~", 
                                     &mMetric ) ;
      }
    catch ( Magick::Exception e )
      {
        UT_DEBUGMSG(("Caught exception in font constructor(): %s\n", e.what()));
      }
  }
  
  virtual ~GR_MagickFont ()
  {
  }
  
  UT_uint32 getFontAscent ()
  {
    return (UT_uint32)mMetric.ascent();
  }
  
  UT_uint32 getFontDescent ()
  {
    return (UT_uint32)(mMetric.descent() * -1);
  }
  
  UT_uint32 getFontHeight ()
  {
    return (UT_uint32)mMetric.textHeight () ;
  }
  
  UT_uint32 measureString ( const std::string & inString )
  {
    try 
      {
        // ALWAYS UTF-8!!!
        Magick::TypeMetric local ;
        mOffscreen.fontTypeMetrics ( inString, &local ) ;        
        return (UT_uint32) local.textWidth () ;
      }
    catch (Magick::Exception e)
      {
        UT_DEBUGMSG(("Caught exception in measureString(): %s\n", e.what()));
      }

    return 0 ;
  }
  
  Magick::DrawableFont & getFont()
  {
    return mFont ;
  }
  
  UT_uint32 getSize () const
  {
    return mSize ;
  }
  
private:
  
  Magick::DrawableFont  mFont ;
  UT_uint32     mSize ;
  Magick::TypeMetric    mMetric ;
  Magick::Image mOffscreen ;
} ;

/******************************************************************/
/* GR_MagickImageEventListener */
/******************************************************************/

GR_MagickImageEventListener::GR_MagickImageEventListener ()
{
}

GR_MagickImageEventListener::~GR_MagickImageEventListener()
{
}

/******************************************************************/
/* GR_MagickImage */
/******************************************************************/

GR_MagickImage::GR_MagickImage(const char * szName)
  : GR_Image ()
{
  if (szName)
    {
      setName ( szName );
    }
  else
    {
      setName ( "GR_MagickImage" );
    }        
}

GR_MagickImage::~GR_MagickImage ()
{        
}

bool GR_MagickImage::convertToBuffer(UT_ByteBuf** ppBB) const
{
  UT_ASSERT_NOT_REACHED () ;
  return false ;
}

bool GR_MagickImage::convertFromBuffer(const UT_ByteBuf* pBB, UT_sint32 iDisplayWidth, UT_sint32 iDisplayHeight)
{
  try
    {
      Magick::Blob inBlob ( pBB->getPointer(0), pBB->getLength () );
      Magick::Geometry geom ( iDisplayWidth, iDisplayHeight ) ;
      
      try 
        {
          mImage.read ( inBlob, geom ) ;
        } 
      catch (...)
        {
          mImage.read ( inBlob, geom ) ; // work around for bug 2637
        }

      return true ;
    }
  catch( Magick::Exception e )
    {
      UT_DEBUGMSG(("Caught exception in convertFromBuffer(): %s\n", e.what()));
      return false;
    }
}

GR_Image::GRType GR_MagickImage::getType(void) const
{
  return GR_Image::GRT_Raster;
}

Magick::Image & GR_MagickImage::getImage ()
{
    return mImage ;
}

UT_sint32 GR_MagickImage::getDisplayWidth(void) const
{
  return mImage.columns() ;
}

UT_sint32 GR_MagickImage::getDisplayHeight(void) const
{
  return mImage.rows () ;
}

/******************************************************************/
/* GR_MagickGraphics */
/******************************************************************/
          
/******************************************************************/
/* Class Constructors and destructors */
/******************************************************************/

/**
 * Create a new ImageMagick based graphics canvas. The default save
 * format is "png". Please see also the setSaveFormat method.
 */
GR_MagickGraphics::GR_MagickGraphics ( const std::string & inSaveFormat, bool bUseMultiFrameIfAppropriate )
  : GR_Graphics (), mCanvas ( 0 ), mSaveFormat ( "PNG" ),
    mStartedPrint ( false ), mStartedPage ( false ), mFont ( 0 ),
    mBMultiFrame ( false )
{
  // stupid...
  m_pApp = XAP_App::getApp();
  
  setSaveFormat ( inSaveFormat, bUseMultiFrameIfAppropriate ) ;
}

/**
 * D'tor
 */
GR_MagickGraphics::~GR_MagickGraphics ()
{
  if ( mStartedPrint )
    endPrint () ;
  
  // cleanup anything listening to our image events
  cleanupListeners () ;
}

/******************************************************************/
/* Accessor methods */
/******************************************************************/

/**
 * Set the save as format. Currently known supported values are:
 * "png" "jpeg" "bmp" "svg" "mvg" "tiff" "gif". If you try to set
 * inSaveFormat to something that isn't supported, it will not change
 * your save format, thus leaving you with the previous format 
 * (which could possibly be the default - PNG). If you want to use
 * a multi-frame version of a supported format (TIFF, PS, PDF, GIF),
 * set bUseMultiFrameIfAppropriate to true.
 */
void GR_MagickGraphics::setSaveFormat ( const std::string & inSaveFormat, bool bUseMultiFrameIfAppropriate )        
{
    try
    {
        Magick::CoderInfo info ( inSaveFormat ) ;  

        // assert that this format is valid and is writable
        UT_return_if_fail(info.isWritable()) ;

        mSaveFormat = inSaveFormat ;
        mBMultiFrame == ( bUseMultiFrameIfAppropriate && info.isMultiFrame() ) ; 
    }
    catch ( Magick::Exception e )
    {
        UT_DEBUGMSG(("Coder info error: %s\n", e.what()));
    }
}

/**
 * Get the save as format
 */
std::string GR_MagickGraphics::getSaveFormat () const
{
  return mSaveFormat ;
}

/**
 * Add a non-null ImageEventListener that gets triggered whenever a new image
 * is ready for consumption (i.e. on each new page finish for single frame formats, or
 * when the whole multi-frame image is done drawing). Unless you call removeListener 
 * explicitly, this class assumes ownership of \param listener and will delete it when appropriate
 */
void GR_MagickGraphics::addListener ( GR_MagickImageEventListener * listener )
{
  UT_return_if_fail ( listener ) ;
  mEventListeners.push_back ( listener ) ;
}

/**
 * Remove this listener \param listener from the event queue iff
 * listener is found. Does *not* delete listener. Returns success
 */
bool GR_MagickGraphics::removeListener ( GR_MagickImageEventListener * listener )
{
  UT_return_val_if_fail ( listener, false ) ;
  std::list<GR_MagickImageEventListener *>::iterator iter ;
  
  iter = std::find ( mEventListeners.begin (), mEventListeners.end (), listener ) ;
  
  if ( iter != mEventListeners.end () )
    {
      // found, so remove and return the listener
      mEventListeners.erase ( iter ) ;
      return true ;
    }
  else
    {
      // not found
      return false ;
    }
}

/******************************************************************/
/* Printing administrata */
/******************************************************************/

/**
 * Start printing
 */
bool GR_MagickGraphics::startPrint ()
{
  mStartedPrint = true ;
  return true ;
}

/**
 * End printing
 */
bool GR_MagickGraphics::endPrint ()
{
  if ( mStartedPage )
    endPage () ;
  mStartedPrint = false ;
  
  // print out a multi-frame image
  if ( mBMultiFrame )
  {
        Magick::Image composite ;
        
        Magick::appendImages ( &composite, mFrames.begin(), mFrames.end() ) ;
        
        Magick::Blob outBlob ;
        composite.write ( &outBlob, mSaveFormat ) ;

        // write out the IM::Blob to our Byte-Buffer
        UT_ByteBuf buf ( outBlob.length () ) ;      
        buf.append ( (const UT_Byte*)outBlob.data (), outBlob.length () ) ;

        notifyListeners ( buf ) ;
  }
  
  return true ;
}

/**
 * Start printing a page with the title \param szPageLabel
 */
bool GR_MagickGraphics::startPage (const char *szPageLabel, 
				   UT_uint32 pageNumber, bool isPortrait, 
				   UT_uint32 iWidth, UT_uint32 iHeight)
{
  if ( mStartedPage )
    endPage () ;
  mStartedPage = true ;
  
  // create a new canvas of this size
  newCanvas ( iWidth, iHeight ) ;
  
  UT_return_val_if_fail(mCanvas, false);

  if ( szPageLabel )
    mCanvas->label ( szPageLabel ) ;
  
  return true ;
}

/******************************************************************/
/* Drawing routines */
/******************************************************************/

UT_uint32 GR_MagickGraphics::measureUnRemappedChar (unsigned int ch)
{
  UT_return_val_if_fail(mFont, 0);

  UT_UTF8String utf_str ( (UT_UCS4Char *)(&ch), 1 ) ;
  std::string utf8 ( utf_str.utf8_str(), utf_str.size() ) ;
  return mFont->measureString ( utf8 ) ;
}

void GR_MagickGraphics::getCoverage (UT_Vector & vec)
{
  return ;
}

void GR_MagickGraphics::setFont(GR_Font* pFont)
{
  mFont = static_cast<GR_MagickFont *>(pFont) ; 
  
  pushDrawable ( mFont->getFont () ) ;
  pushDrawable ( Magick::DrawablePointSize ( mFont->getSize () ) ) ;
}

UT_uint32 GR_MagickGraphics::getFontAscent()
{
  UT_return_val_if_fail(mFont, 0);
  return scaleYCoord ( mFont->getFontAscent () ) ;
}

UT_uint32 GR_MagickGraphics::getFontDescent()
{
  UT_return_val_if_fail(mFont, 0);
  return scaleYCoord ( mFont->getFontDescent () ) ;
}

UT_uint32 GR_MagickGraphics::getFontHeight()
{
  UT_return_val_if_fail(mFont, 0);
  return scaleYCoord ( mFont->getFontHeight () ) ;
}

UT_uint32 GR_MagickGraphics::getFontAscent(GR_Font * pFont)
{
  GR_MagickFont * mf = static_cast<GR_MagickFont *>(pFont) ;    
  return scaleYCoord ( mf->getFontAscent () ) ;
}

UT_uint32 GR_MagickGraphics::getFontDescent(GR_Font * pFont)
{
  GR_MagickFont * mf = static_cast<GR_MagickFont *>(pFont) ;    
  return scaleYCoord ( mf->getFontDescent () ) ;
}

UT_uint32 GR_MagickGraphics::getFontHeight(GR_Font * pFont)
{
  GR_MagickFont * mf = static_cast<GR_MagickFont *>(pFont) ;    
  return scaleYCoord ( mf->getFontHeight () ) ;
}

GR_Font* GR_MagickGraphics::getGUIFont()
{
  UT_ASSERT_NOT_REACHED();  
  return 0 ;
}

GR_Font* GR_MagickGraphics::findFont(const char* pszFontFamily,
                                     const char* pszFontStyle,
                                     const char* pszFontVariant,
                                     const char* pszFontWeight,
                                     const char* pszFontStretch,
                                     const char* pszFontSize)
{
  return new GR_MagickFont ( pszFontFamily, pszFontStyle, 
                             pszFontVariant, pszFontWeight, 
                             pszFontStretch, pszFontSize) ;
}

void GR_MagickGraphics::setColor (const UT_RGBColor& clr)
{
  Magick::Color mc ( toMagickRGB( clr ) ) ;
  pushDrawable ( Magick::DrawableFillColor ( mc ) ) ;
  pushDrawable ( Magick::DrawableStrokeColor ( mc ) ) ;
}

void GR_MagickGraphics::setLineWidth(UT_sint32 width)
{
  pushDrawable ( Magick::DrawableStrokeWidth ( ( double ) width ) ) ;
}

void GR_MagickGraphics::drawGlyph (UT_uint32 glyph_idx, UT_sint32 xoff, UT_sint32 yoff)
{
  // DOM: THIS SO TOTALLY ISN'T CORRECT!!!
  UT_DEBUGMSG(("DOM: drawGlyph\n"));

  std::string theStr ;
  
  theStr += (char) glyph_idx ;
  
  pushDrawable ( Magick::DrawableText ( xoff, yoff, theStr, "UTF-8" ) ) ;
}

void GR_MagickGraphics::drawChars(const UT_UCSChar* pChars,
                                  int iCharOffset,
                                  int iLength,
                                  UT_sint32 xoff,
                                  UT_sint32 yoff,
                                  int* pCharWidths)
{
  UT_UTF8String utf_str ( pChars + iCharOffset, iLength ) ;
  
  std::string utf8 ( utf_str.utf8_str(), utf_str.size () ) ;  
  pushDrawable ( Magick::DrawableText ( xoff, yoff, utf8, "UTF-8" ) ) ;
}

void GR_MagickGraphics::drawImage(GR_Image* pImg, UT_sint32 xDest, UT_sint32 yDest)
{
  if (pImg->getType() != GR_Image::GRT_Raster) 
    {
      pImg->render(this, xDest, yDest);
      return;
    }
  
  GR_MagickImage * magImg = static_cast<GR_MagickImage *>(pImg) ;
  pushDrawable ( Magick::DrawableCompositeImage ( (double)xDest, (double)yDest, magImg->getImage() ) ) ;            
}

void GR_MagickGraphics::drawLine(UT_sint32 x1, UT_sint32 y1, UT_sint32 x2, UT_sint32 y2)
{
  pushDrawable ( Magick::DrawableLine ( x1, y1, x2, y2 ) ) ;
}

void GR_MagickGraphics::fillRect(const UT_RGBColor& c,
                                 UT_sint32 x,
                                 UT_sint32 y,
                                 UT_sint32 w,
                                 UT_sint32 h)
{
  pushDrawable ( Magick::DrawablePushGraphicContext () );
  pushDrawable ( Magick::DrawableStrokeWidth ( 0.0 ) ) ;
  pushDrawable ( Magick::DrawableStrokeColor ( Magick::Color ( "transparent" ) ) ) ;
  pushDrawable ( Magick::DrawableFillColor ( toMagickRGB( c ) ) ) ;
  pushDrawable ( Magick::DrawableRectangle ( x+w, y-h, x, y ) ) ;
  pushDrawable ( Magick::DrawablePopGraphicContext () ) ;
}

bool GR_MagickGraphics::queryProperties(GR_Graphics::Properties gp) const
{
  if ( gp == DGP_PAPER )
    return true ;
  return false ;
}

GR_Image* GR_MagickGraphics::createNewImage(const char* pszName, 
                                            const UT_ByteBuf* pBB, 
                                            UT_sint32 iDisplayWidth,
                                            UT_sint32 iDisplayHeight, 
                                            GR_Image::GRType iType)
{
  GR_Image* pImg = NULL;
  
  if (iType == GR_Image::GRT_Raster)
    pImg = new GR_MagickImage(pszName);
  else if (iType == GR_Image::GRT_Vector)
    pImg = new GR_VectorImage(pszName);
  
  pImg->convertFromBuffer(pBB, iDisplayWidth, iDisplayHeight);
  
  return pImg;
}

/******************************************************************/
/* Unused routines */
/******************************************************************/

void GR_MagickGraphics::polyLine(UT_Point * pts, UT_uint32 nPoints)
{
  UT_ASSERT_NOT_REACHED() ;
}

void GR_MagickGraphics::xorLine(UT_sint32, UT_sint32, UT_sint32, UT_sint32)
{
  UT_ASSERT_NOT_REACHED() ;
}

void GR_MagickGraphics::invertRect(const UT_Rect* pRect)
{
  UT_ASSERT_NOT_REACHED();
}

void GR_MagickGraphics::setClipRect(const UT_Rect* pRect)
{
  UT_ASSERT_NOT_REACHED() ;
}

void GR_MagickGraphics::scroll(UT_sint32, UT_sint32)
{
  UT_ASSERT_NOT_REACHED() ;
}

void GR_MagickGraphics::scroll(UT_sint32 x_dest,
                               UT_sint32 y_dest,
                               UT_sint32 x_src,
                               UT_sint32 y_src,
                               UT_sint32 width,
                               UT_sint32 height)
{
  UT_ASSERT_NOT_REACHED();
}

void GR_MagickGraphics::clearArea(UT_sint32, UT_sint32, UT_sint32, UT_sint32)
{
  UT_ASSERT_NOT_REACHED() ;
}

void GR_MagickGraphics::setColorSpace(GR_Graphics::ColorSpace c)
{
  UT_ASSERT_NOT_REACHED();
}

GR_Graphics::ColorSpace GR_MagickGraphics::getColorSpace(void) const
{
  UT_ASSERT_NOT_REACHED();
  return GR_Graphics::GR_COLORSPACE_COLOR ;
}

void GR_MagickGraphics::setCursor(GR_Graphics::Cursor c)
{
  UT_ASSERT_NOT_REACHED();
}

GR_Graphics::Cursor GR_MagickGraphics::getCursor(void) const
{
  UT_ASSERT_NOT_REACHED();
  return GR_Graphics::GR_CURSOR_DEFAULT ;
}

void GR_MagickGraphics::setColor3D(GR_Color3D c)
{
  UT_ASSERT_NOT_REACHED ();
}

void GR_MagickGraphics::fillRect(GR_Color3D c,
                                 UT_sint32 x,
                                 UT_sint32 y,
                                 UT_sint32 w,
                                 UT_sint32 h)
{
  UT_ASSERT_NOT_REACHED();
}

void GR_MagickGraphics::fillRect(GR_Color3D c, UT_Rect &r)
{
  UT_ASSERT_NOT_REACHED();
}

/******************************************************************/
/* Internal private routines */
/******************************************************************/

UT_uint32 GR_MagickGraphics::_getResolution(void) const
{
  return 72 ;
}

/**
 * Notify all of the listeners that we've just gotten
 * a raster image byte buffer ready for consumption
 */
void GR_MagickGraphics::notifyListeners ( const UT_ByteBuf & bytes )
{
  std::list<GR_MagickImageEventListener *>::const_iterator iter, end ;            
  end = mEventListeners.end () ;
  
  const UT_ByteBuf * pBytes = (const UT_ByteBuf *)( &bytes ) ;
  
  for ( iter = mEventListeners.begin () ; iter != end ; iter++ )
    (*iter)->imageEvent ( pBytes, getSaveFormat (), mBMultiFrame ) ;
}

/**
 * Clean up all of our listeners
 */
void GR_MagickGraphics::cleanupListeners ()
{
  std::list<GR_MagickImageEventListener *>::iterator iter, end ;            
  end = mEventListeners.end () ;
  
  for ( iter = mEventListeners.begin () ; iter != end ; iter++ )
    delete (*iter) ;
}

/**
 * End a page being drawn, dispatch byte buffer to listeners
 */
void GR_MagickGraphics::endPage ()
{
  mStartedPage = false ;

  UT_return_if_fail ( mCanvas ) ;

  try
    {      
      // append a pop graphics canvas - MVG and SVG need this
      pushDrawable ( Magick::DrawablePopGraphicContext () ) ;
      
      // draw the queued commands
      paintCanvas () ;
            
      if ( !mBMultiFrame )
      {
        // single frame format. save and notify listeners        
        Magick::Blob outBlob ;
        mCanvas->write ( &outBlob, mSaveFormat ) ;

        // write out the IM::Blob to our Byte-Buffer
        UT_ByteBuf buf ( outBlob.length () ) ;      
        buf.append ( (const UT_Byte*)outBlob.data (), outBlob.length () ) ;

        notifyListeners ( buf ) ;
      }
      else
      {
        // multi-frame format. add to our number of frames and continue
        mFrames.push_back ( *mCanvas ) ;
      }
       
      // clear the canvas of any pending draws
      clearCanvas () ;
    }
  catch ( Magick::Exception e )
    {
      UT_DEBUGMSG(("Caught exception in endPage(): %s\n", e.what()));
    }

  DELETEP( mCanvas ) ;
}                
        
/**
 * Create and return a new canvas whose with width and height (\param iWidth, \param iHeight)
 */
void GR_MagickGraphics::newCanvas ( UT_uint32 iWidth, UT_uint32 iHeight )
{
  UT_ASSERT( !mCanvas ) ;

  UT_DEBUGMSG(("DOM: newCanvas(%d, %d)\n", iWidth, iHeight));

  try
    {
      mCanvas = new Magick::Image ( Magick::Geometry(iWidth, iHeight),  Magick::Color ( "white" ) ) ;
      
      // MVG and SVG need these
      // DrawableViewbox was added sometime in the 5.4.x series where x > 3. I know that 5.4.8+ has it
      pushDrawable ( Magick::DrawablePushGraphicContext () ) ;  
      pushDrawable ( Magick::DrawableViewbox ( 0, 0, iWidth, iHeight ) ) ;
      
      // set up our canvas' defaults
      pushDrawable ( Magick::DrawableTextDecoration ( Magick::NoDecoration ) ) ;
      pushDrawable ( Magick::DrawableFillRule (  Magick::UndefinedRule ) ) ;
      pushDrawable ( Magick::DrawableFillColor (  Magick::Color ( "black" ) ) ) ;
      pushDrawable ( Magick::DrawableFont ( "Times-Roman",  Magick::NormalStyle, DEFAULT_WEIGHT,  Magick::NormalStretch ) ) ;
      pushDrawable ( Magick::DrawableStrokeColor (  Magick::Color ( "black" ) ) ) ;
      pushDrawable ( Magick::DrawableStrokeLineCap (  Magick::RoundCap ) ) ;
      pushDrawable ( Magick::DrawableStrokeLineJoin (  Magick::RoundJoin ) ) ;
      pushDrawable ( Magick::DrawableStrokeWidth ( 1.0 ) ) ;
    }
  catch( Magick::Exception e )
    {
      UT_DEBUGMSG(("Caught exception in newCanvas(): %s\n", e.what()));
      DELETEP(mCanvas); // eat exception, ensure canvas is null
    }
}

/**
 * Causes the drawable \param drawable to be drawn
 */
void GR_MagickGraphics::pushDrawable ( const Magick::Drawable & drawable )
{
  mCommandStack.push_back ( drawable ) ;
}

/**
 * Causes the canvas to be painted
 */
void GR_MagickGraphics::paintCanvas ()
{
  UT_return_if_fail ( mCanvas ) ;

  // let exceptions propegate upward
  mCanvas->draw ( mCommandStack ) ;
}

UT_uint32 GR_MagickGraphics::scaleXCoord ( UT_uint32 inX ) const
{
  return inX ;
}

UT_uint32 GR_MagickGraphics::scaleYCoord ( UT_uint32 inY ) const
{
  return inY ;
}

/**
 * Will clean up the canvas
 */
void GR_MagickGraphics::clearCanvas ()
{
  mCommandStack.erase ( mCommandStack.begin(), mCommandStack.end() ) ;
}

/**
 * Convert a UT_RGBColor to a Magick::ColorRGB
 */
Magick::ColorRGB GR_MagickGraphics::toMagickRGB (const UT_RGBColor & clr)
{
  return Magick::ColorRGB ( (double)clr.m_red/255., (double)clr.m_grn/255., (double)clr.m_blu/255. ) ;
}
