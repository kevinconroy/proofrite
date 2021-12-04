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

#include <Magick++.h>
#include <string>

#include "ut_types.h"
#include "xap_Module.h"
#include "ie_impGraphic.h"
#include "fg_GraphicRaster.h"

#include "xap_App.h"
#include "xap_Frame.h"
#include "fv_View.h"
#include "ap_Menu_Id.h"
#include "ev_Menu_Actions.h"
#include "ev_Menu.h"
#include "ev_Menu_Layouts.h"
#include "ev_Menu_Labels.h"
#include "ev_EditMethod.h"
#include "xap_Menu_Layouts.h"
#include "ut_string_class.h"
#include "ut_math.h"

#include "MagickGraphics.h"
#include "pd_Document.h"
#include "fl_BlockLayout.h"

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------

class FileSave_ImageEventListener : public GR_MagickImageEventListener
{
public:

  explicit FileSave_ImageEventListener ( const std::string & base_name )
    : GR_MagickImageEventListener (), mBaseName ( base_name ), mCount ( 0 )
  {
  }

  virtual ~FileSave_ImageEventListener ()
  {
  }

  virtual void imageEvent ( const UT_ByteBuf * pBytes, const std::string & szFormat, bool isMultiFrame )
  {
    mCount++;
    UT_String fileName ; 
    
    if ( !isMultiFrame )
        fileName = UT_String_sprintf ( "%s_%d.%s", mBaseName.c_str(),
                                        mCount, szFormat.c_str() ) ;
    else
        fileName = UT_String_sprintf ( "%s.%s", mBaseName.c_str(), szFormat.c_str() ) ;

    pBytes->writeToFile ( fileName.c_str() ) ;
  }

private:

  FileSave_ImageEventListener () ;
  FileSave_ImageEventListener ( const FileSave_ImageEventListener & other ) ;
  FileSave_ImageEventListener& operator= ( const FileSave_ImageEventListener & other ) ;

  std::string mBaseName ;
  UT_uint32 mCount ;
} ;

static void printPDDoc(PD_Document * pDoc, GR_Graphics * pGraphics,
                       const char * szTitle)
{
  // create a new layout and view object for the doc
  FL_DocLayout pDocLayout (pDoc,pGraphics);
  
  FV_View printView(XAP_App::getApp(),0,&pDocLayout);
  pDocLayout.fillLayouts();
  
  // get the width, height, orient
  UT_sint32 iWidth = pDocLayout.getWidth();
  UT_sint32 iHeight = pDocLayout.getHeight() / pDocLayout.countPages();
  
  bool orient = printView.getPageSize().isPortrait();
  pGraphics->setPortrait (orient);  
  
  // setup the drawing args
  dg_DrawArgs da;
  memset(&da, 0, sizeof(da));
  
  if(pGraphics->startPrint())
    {
      // iterate over the pages, printing each one
      for (UT_uint32 k = 1; (k <= pDocLayout.countPages()); k++)
	{
	  pGraphics->m_iRasterPosition = (k-1)*iHeight;
	  pGraphics->startPage(szTitle, k, orient, iWidth, iHeight);
	  printView.draw(k-1, &da);
	}
      pGraphics->endPrint();
    }  
}

static bool AbiMagick_printToImage (AV_View* v, EV_EditMethodCallData *d)
{
  FV_View * pView = static_cast<FV_View*>(v);

  const char * szTitle = "AbiWordImage" ;

  XAP_Frame * pFrame = XAP_App::getApp()->getLastFocussedFrame();
  if ( pFrame )
    if ( pFrame->getTitle ( 256 ) )
      szTitle = pFrame->getTitle ( 256 ) ;

  // TODO: grab base filename/directory via a dialog and also save format...

  FileSave_ImageEventListener * listener = new FileSave_ImageEventListener ( szTitle ) ;

  GR_MagickGraphics magickGr ( "png" ) ;
  magickGr.addListener ( listener ) ;

  printPDDoc ( pView->getDocument(), &magickGr, szTitle ) ;

  return true ;
}

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------

static Magick::Image ImageFromPNGByteBuf ( const UT_ByteBuf * pBB )
{
  Magick::Blob inBlob ( pBB->getPointer (0), pBB->getLength () );

  // not Magick::Image ( inBlob ) which doesn't work on win32 for some reason
  Magick::Image img ;
  try {
    img.read ( inBlob ) ;
  } catch (...) {
    img.read ( inBlob ) ; // work around for bug 2637 (1st img read in fails, so 1st insert or menu action fails)
  }

  return img ;
}

static UT_Error PNGByteBufFromImage ( Magick::Image & inImage,
				      UT_ByteBuf ** outByteBuf )
{
  Magick::Blob outBlob;

  try
    {
      inImage.write ( &outBlob, "png" );
    }
  catch(...)
    {
      return UT_ERROR ;
    }

  // write out the IM::Blob to our Byte-Buffer
  UT_ByteBuf * buf = new UT_ByteBuf (outBlob.length ());
  buf->append ( (const UT_Byte*)outBlob.data (), outBlob.length () );

  *outByteBuf = buf ;

  return UT_OK ;
}

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------

/*!
 * This class will import any graphic type supported
 * by ImageMagick into a PNG buffer for AbiWord's use
 */
class ABI_EXPORT IE_MagickGraphic : public IE_ImpGraphic
{

public:

  IE_MagickGraphic ()
    : IE_ImpGraphic ()
  {
  }

  virtual ~IE_MagickGraphic ()
  {
  } 
  
  /*!
   * Convert the incoming byte-buffer
   * into a PNG-based FG_Graphic type
   */
  virtual UT_Error importGraphic(UT_ByteBuf* pBB, 
				 FG_Graphic ** ppfg)
  {
    UT_Error err = UT_OK;
    UT_ByteBuf * pBBpng = 0;	
    FG_GraphicRaster * pFGR = 0;
    
    *ppfg = 0;
    
    err = convertGraphic(pBB,&pBBpng);
    if (err != UT_OK) {
      return err;
    }

    pFGR = new FG_GraphicRaster();
    if(pFGR == 0) {
      err = UT_IE_NOMEMORY;
    }
    else if(!pFGR->setRaster_PNG(pBBpng)) {
      DELETEP(pFGR);
      err = UT_IE_FAKETYPE;
    }
    else {
      *ppfg = (FG_Graphic *) pFGR;
    }

    return err;
  }

  /*!
   * Convert the data contained in the file to into a PNG-based 
   * FG_Graphic type
   */
  virtual UT_Error importGraphic(const char * szFilename, FG_Graphic ** ppfg)
  {
    UT_ByteBuf bb;
    
    if ( bb.insertFromFile(0, szFilename) )
      {
	return importGraphic ( &bb, ppfg ) ;
			}
    else
      {
	*ppfg = 0;
	return UT_ERROR;
      }
  }
  
  /*!
   * Convert the incoming byte-buffer into a PNG byte-buffer
   */
  virtual UT_Error convertGraphic(UT_ByteBuf* pBB, 
				  UT_ByteBuf** ppBB)
  {
    try
      {	
	Magick::Image img ( ImageFromPNGByteBuf ( pBB ) ) ;
	return PNGByteBufFromImage ( img, ppBB ) ;
      }
    catch (...)
      {
	return UT_ERROR;
      }
  }
  
};

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------

class ABI_EXPORT IE_MagickGraphic_Sniffer : public IE_ImpGraphicSniffer
{
public:
  IE_MagickGraphic_Sniffer () {}
  virtual ~IE_MagickGraphic_Sniffer () {}
  
  virtual UT_Confidence_t recognizeContents (const char * szBuf, 
					     UT_uint32 iNumbytes)
  {
    try
      {
        // todo: enable this bit of code once a new stable IM release is made
        Magick::Blob pingBlob ( (const void*)szBuf, (size_t)iNumbytes ) ;
        Magick::Image hopeful;
        
        // test to see if we support this image type
        hopeful.ping ( pingBlob ) ;
        
        if ( hopeful.rows () > 0 && hopeful.columns () > 0 )
          return UT_CONFIDENCE_PERFECT;
      }
    catch(...)
      {
      }
    return UT_CONFIDENCE_ZILCH;
  }
  
  virtual UT_Confidence_t recognizeSuffix (const char * szSuffix)
  {
    std::list<Magick::CoderInfo> coderList ;

    coderInfoList ( &coderList,
                    Magick::CoderInfo::TrueMatch,
                    Magick::CoderInfo::AnyMatch,
                    Magick::CoderInfo::AnyMatch ) ;
                    
    std::list<Magick::CoderInfo>::const_iterator iter ;
    
    for ( iter = coderList.begin () ; iter != coderList.end () ; iter++ )
    {
        if ( !UT_stricmp( iter->name ().c_str(), szSuffix ) )
            return UT_CONFIDENCE_PERFECT ;
    }

    // still a chance, but not a good one
    return UT_CONFIDENCE_POOR;
  }
  
  virtual bool getDlgLabels (const char ** szDesc,
			     const char ** szSuffixList,
			     IEGraphicFileType * ft)
  {
    *szDesc = "ImageMagick Images";
    *szSuffixList = "*.*";
    *ft = getType ();
    return true;
  }
  
  virtual UT_Error constructImporter (IE_ImpGraphic ** ppieg)
  {
    *ppieg = new IE_MagickGraphic ();
    if (*ppieg == 0)
      return UT_IE_NOMEMORY;
    return UT_OK;
  }  
};

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------

static bool GetCurrentlySelectedImage ( FV_View * pView,
					const UT_ByteBuf ** outByteBuf )
{
  *outByteBuf = 0 ;
  pView->saveSelectedImage ( outByteBuf ) ;
  return true ;
}

static void SetCurrentlySelectedImage ( FV_View * pView,
					UT_ByteBuf * inByteBuf )
{
  FG_Graphic* pFG = NULL ;
  IE_MagickGraphic graphic ;

  if ( graphic.importGraphic ( inByteBuf, &pFG ) == UT_OK )
    {
      // currently selected position
      PT_DocPosition pos = pView->getSelectionAnchor();

      pView->cmdUnselectSelection();
      pView->setPoint(pos);
      pView->extSelHorizontal(true, 1); // move point forward one

      UT_String temp_id = UT_String_sprintf ( "Magick_Image_%d", UT_newNumber () ) ;

      if ( UT_OK != pView->cmdInsertGraphic(pFG,temp_id.c_str()) )
	{
	  DELETEP(pFG);
	  return ;
	}

      //
      // Reselect the image
      //
      pView->setPoint(pos);
      pView->extSelHorizontal(true, 1); // move point forward one
    }

  return ;
}

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------

#define MAGICK_FILTER_METHOD(m) AbiMagick_Filter_##m

/*!
 * Macro to declare an imageMagick filter method
 */
#define DECLARE_MAGICK_FILTER_METHOD(m) \
static bool AbiMagick_Filter_##m (AV_View* v, EV_EditMethodCallData *d) \
{ \
  FV_View * pView = static_cast<FV_View*>(v) ; \
  const UT_ByteBuf * in = NULL; \
  UT_ByteBuf * out = NULL ; \
  if ( GetCurrentlySelectedImage ( pView, &in ) && in ) { \
    try \
    {	\
    Magick::Image img = ImageFromPNGByteBuf ( in ) ; \
    img. m () ; \
    PNGByteBufFromImage ( img, &out ) ; \
    } \
    catch (...) \
    { \
      if (out != NULL) DELETEP(out); \
      return false; \
    } \
    SetCurrentlySelectedImage ( pView, out ) ; \
    DELETEP(out); \
  } \
  return true ; \
}

// declare the methods we are going to employ as imagemagick filters

DECLARE_MAGICK_FILTER_METHOD(blur)
DECLARE_MAGICK_FILTER_METHOD(border)
DECLARE_MAGICK_FILTER_METHOD(charcoal)
DECLARE_MAGICK_FILTER_METHOD(despeckle)
DECLARE_MAGICK_FILTER_METHOD(edge)
DECLARE_MAGICK_FILTER_METHOD(emboss)
DECLARE_MAGICK_FILTER_METHOD(enhance)
DECLARE_MAGICK_FILTER_METHOD(equalize)
DECLARE_MAGICK_FILTER_METHOD(flip)
DECLARE_MAGICK_FILTER_METHOD(flop)
DECLARE_MAGICK_FILTER_METHOD(magnify)
DECLARE_MAGICK_FILTER_METHOD(medianFilter)
DECLARE_MAGICK_FILTER_METHOD(minify)
DECLARE_MAGICK_FILTER_METHOD(negate)
DECLARE_MAGICK_FILTER_METHOD(normalize)
DECLARE_MAGICK_FILTER_METHOD(oilPaint)
DECLARE_MAGICK_FILTER_METHOD(quantize)
DECLARE_MAGICK_FILTER_METHOD(raise)
DECLARE_MAGICK_FILTER_METHOD(reduceNoise)
DECLARE_MAGICK_FILTER_METHOD(segment)
DECLARE_MAGICK_FILTER_METHOD(shade)
DECLARE_MAGICK_FILTER_METHOD(sharpen)
DECLARE_MAGICK_FILTER_METHOD(solarize)
DECLARE_MAGICK_FILTER_METHOD(spread)
DECLARE_MAGICK_FILTER_METHOD(trim)
DECLARE_MAGICK_FILTER_METHOD(wave)

typedef struct
{
  const char    * methodName;
  EV_EditMethod_pFn method;
  const char    * label;
  const char    * description;
  EV_Menu_LayoutFlags flags;		// usually EV_MLF_Normal
} MagickFilterInfo ;

const static MagickFilterInfo mfi [] = 
{
  { "AbiMagick_submenu_start", NULL, "AbiMagick Effects", "Image manipulation via ImageMagick library.", EV_MLF_BeginSubMenu },
  { "AbiMagick_Filter_blur", /*AbiMagick_printToImage*/AbiMagick_Filter_blur, "Blur", "Blur image", EV_MLF_Normal },
  { "AbiMagick_Filter_border", AbiMagick_Filter_border, "Border", "Add border to image", EV_MLF_Normal },
  { "AbiMagick_Filter_charcoal", AbiMagick_Filter_charcoal, "Charcoal", "Charcoal effect image", EV_MLF_Normal },
  { "AbiMagick_Filter_despeckle", AbiMagick_Filter_despeckle, "Despeckle", "Despeckle image", EV_MLF_Normal },
  { "AbiMagick_Filter_edge", AbiMagick_Filter_edge, "Edge", "Edge image", EV_MLF_Normal },
  { "AbiMagick_Filter_emboss", AbiMagick_Filter_emboss, "Emboss", "Emboss image", EV_MLF_Normal },
  { "AbiMagick_Filter_enhance", AbiMagick_Filter_enhance, "Enhance", "Enhance image", EV_MLF_Normal },
  { "AbiMagick_Filter_flip", AbiMagick_Filter_flip, "Flip", "Flip image", EV_MLF_Normal },
  { "AbiMagick_Filter_flop", AbiMagick_Filter_flop, "Flop", "Flop image", EV_MLF_Normal },
  { "AbiMagick_Filter_magnify", AbiMagick_Filter_magnify, "Magnify", "Magnify image by integral size", EV_MLF_Normal },
  { "AbiMagick_Filter_medianFilter", AbiMagick_Filter_medianFilter, "Median Filter", "Median Filter", EV_MLF_Normal },
  { "AbiMagick_Filter_minify", AbiMagick_Filter_minify, "Minify", "Minify image by integral size", EV_MLF_Normal },
  { "AbiMagick_Filter_negate", AbiMagick_Filter_negate, "Negate", "Negate colors in image", EV_MLF_Normal },
  { "AbiMagick_Filter_normalize", AbiMagick_Filter_normalize, "Normalize", "Normalize image", EV_MLF_Normal },
  { "AbiMagick_Filter_oilPaint", AbiMagick_Filter_oilPaint, "Oil Paint", "Oil Paint image", EV_MLF_Normal },
  { "AbiMagick_Filter_quantize", AbiMagick_Filter_quantize, "Quanitze", "Quantize image", EV_MLF_Normal },
  { "AbiMagick_Filter_raise", AbiMagick_Filter_raise, "Raise", "Raise image", EV_MLF_Normal },
  { "AbiMagick_Filter_reduceNoise", AbiMagick_Filter_reduceNoise, "Reduce Noise", "Reduce Noise", EV_MLF_Normal },
  { "AbiMagick_Filter_segment", AbiMagick_Filter_segment, "Segment", "Segment image", EV_MLF_Normal },
  { "AbiMagick_Filter_shade", AbiMagick_Filter_shade, "Shade", "Shade image", EV_MLF_Normal },
  { "AbiMagick_Filter_sharpen", AbiMagick_Filter_sharpen, "Sharpen", "Sharpen image", EV_MLF_Normal },
  { "AbiMagick_Filter_solarize", AbiMagick_Filter_solarize, "Solarize", "Solarize image", EV_MLF_Normal },
  { "AbiMagick_Filter_spread", AbiMagick_Filter_spread, "Spread", "Spread pixels randomly", EV_MLF_Normal },
  { "AbiMagick_Filter_trim", AbiMagick_Filter_trim, "Trim", "Trim edges from image", EV_MLF_Normal },
  { "AbiMagick_Filter_wave", AbiMagick_Filter_wave, "Wave", "Map image pixels to a sine wave", EV_MLF_Normal },
  { "AbiMagick_submenu_end", NULL, "AbiMagick Submenu End", NULL, EV_MLF_EndSubMenu },
} ;

#define NUM_IM_FILTERS sizeof(mfi)/sizeof(mfi[0])

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------

static void InstallMenus ()
{
  // TODO: build ImageMagick's menus

  UT_uint32 i;  // MSVC and its old style for scoping...

  XAP_App *pApp = XAP_App::getApp();
  EV_EditMethodContainer* pEMC = pApp->getEditMethodContainer();

  int frameCount = pApp->getFrameCount();
  XAP_Menu_Factory * pFact = pApp->getMenuFactory();

  EV_Menu_ActionSet* pActionSet = pApp->getMenuActionSet();

  for ( i = 0 ; i < NUM_IM_FILTERS; i++ )
    {
      EV_EditMethod *myEditMethod = new EV_EditMethod(
						      mfi[i].methodName,
						      mfi[i].method,
						      0,
						      ""
						      );
      pEMC->addEditMethod(myEditMethod);

      const char * prev = "Resize &Image";
      if ( i != 0 )
	prev = mfi[i-1].label ;

      XAP_Menu_Id newID = pFact->addNewMenuAfter("ContextImageT",NULL,
						 prev, mfi[i].flags);
      pFact->addNewLabel(NULL,newID,mfi[i].label, mfi[i].description);

      // Create the Action that will be called.
      EV_Menu_Action* myAction = new EV_Menu_Action(
						    newID,
						    0,
						    0,
						    0,
						    mfi[i].methodName,
						    NULL,
						    NULL
						    );
      pActionSet->addAction(myAction);
    }
  {
    // TODO: clean me up
    EV_EditMethod *myEditMethod = new EV_EditMethod(
                                                    "AbiMagick_printToImage",
                                                    AbiMagick_printToImage,
                                                    0,
                                                    ""
                                                    );
    pEMC->addEditMethod(myEditMethod);

    const char * prev = "&Print";

    XAP_Menu_Id newID = pFact->addNewMenuAfter("Main",NULL,
                                               prev, EV_MLF_Normal);
    pFact->addNewLabel(NULL,newID,"Print To Image", "Prints the Document to an image");
    
    // Create the Action that will be called.
    EV_Menu_Action* myAction = new EV_Menu_Action(
                                                  newID,
                                                  0,
                                                  0,
                                                  0,
                                                  "AbiMagick_printToImage",
                                                  NULL,
                                                  NULL
                                                  );
    pActionSet->addAction(myAction);
  }

  // rebuild the menus
  for( i = 0;i < frameCount;++i)
    {
      // Get the current frame that we're iterating through.
      XAP_Frame* pFrame = pApp->getFrame(i);
      pFrame->rebuildMenus();
    }
}

static void UninstallMenus ()
{
  UT_uint32 i;  // MSVC and its old style for scoping...

  XAP_App *pApp = XAP_App::getApp();
  EV_EditMethodContainer* pEMC = pApp->getEditMethodContainer();

  int frameCount = pApp->getFrameCount();
  XAP_Menu_Factory * pFact = pApp->getMenuFactory();

  for ( i = 0 ; i < NUM_IM_FILTERS; i++ )
    {
      // remove the edit method
      EV_EditMethod * pEM = ev_EditMethod_lookup ( mfi[i].methodName ) ;
      pEMC->removeEditMethod ( pEM ) ;
      DELETEP( pEM ) ;

      // remove the contextual menu
      pFact->removeMenuItem( "ContextImageT",NULL, mfi[i].label ) ;
    }

  pFact->removeMenuItem( "Main", NULL, "Print To Image") ;

  // rebuild the menus
  for( i = 0;i < frameCount;++i)
    {
      // Get the current frame that we're iterating through.
      XAP_Frame* pFrame = pApp->getFrame(i);
      pFrame->rebuildMenus();
    }
}

// -----------------------------------------------------------------------
//
//      Abiword Plugin Interface 
//
// -----------------------------------------------------------------------

ABI_PLUGIN_DECLARE("ImageMagick")

static IE_MagickGraphic_Sniffer *m_sniffer = 0;

ABI_FAR_CALL
int abi_plugin_register (XAP_ModuleInfo * mi)
{
    mi->name = "ImageMagick Plugin";
    mi->desc = "Adds ImageMagick++ support for AbiWord. This enables AbiWord to read any graphic type that ImageMagick supports. ";
    mi->version = ABI_VERSION_STRING;
    mi->author = "Dom Lachowicz <cinamod@hotmail.com>";
    mi->usage = "No Usage";

    if (!m_sniffer)
      {
	// create a new sniffer
	m_sniffer = new IE_MagickGraphic_Sniffer ();
      }
    else
      {
	// else just reference the one we've got
	m_sniffer->ref();
      }

    // initialize ImageMagick and register ourself
    MagickLib::InitializeMagick(".");    
    IE_ImpGraphic::registerImporter ( m_sniffer );

    InstallMenus () ;

    return 1;
}


ABI_FAR_CALL
int abi_plugin_unregister (XAP_ModuleInfo * mi)
{
    mi->name = 0;
    mi->desc = 0;
    mi->version = 0;
    mi->author = 0;
    mi->usage = 0;

    if ( m_sniffer )
      IE_ImpGraphic::unregisterImporter ( m_sniffer );

    if (!m_sniffer->unref())
      {
	m_sniffer = 0;
      }

    UninstallMenus () ;

    return 1;
}


ABI_FAR_CALL
int abi_plugin_supports_version (UT_uint32 major, UT_uint32 minor, UT_uint32 release)
{
  return 1;
}

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------

#ifdef _WIN32  //Braindead LIBC library requires this
int main()
{
	return 0;
}
#endif
