/* Experimental canvas masquerading as SVG plugin for AbiWord-1.0
 * Copyright (C) 2002 Francis James Franklin
 * Copyright (C) 2002 AbiSource, Inc.
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
#include "xap_Module.h"
#include "ie_impGraphic.h"

#include "ut_canvas.h"

class ABI_EXPORT IE_CanvasGraphic : public IE_ImpGraphic
{
public:
  IE_CanvasGraphic () { }
  virtual ~IE_CanvasGraphic () { }

  /*!
   * Convert an image data buffer into PNG image buffer.
   */
  virtual UT_Error importGraphic (UT_ByteBuf * pBB, FG_Graphic ** ppfg)
  {
    UT_Canvas canvas;
    UT_ByteBuf * pPngBB = 0;

    UT_Error err = convertGraphic (pBB, &pPngBB);
    if (err != UT_OK) return err;

    FG_GraphicRaster * pFGR = new FG_GraphicRaster ();
    if(!pFGR->setRaster_PNG (pPngBB)) 
      {
	DELETEP (pFGR);
	DELETEP (pPngBB);
	return UT_IE_FAKETYPE;
      }

    *ppfg = (FG_Graphic *) pFGR;

    DELETEP (pPngBB);
    return UT_OK;
  }

  /*!
   * Convert an image byte buffer into a PNG byte buffer
   */
  UT_Error convertGraphic (UT_ByteBuf * pBB, UT_ByteBuf ** ppBB)
  {
    UT_Canvas canvas;
    if (!canvas.test (pBB, ppBB))
      {
	// ?? DELETEP (pBB);
	return UT_IE_FAKETYPE;
      }

    // ?? DELETEP (pBB);
    return UT_OK;
  }
};

// ---------------------------------------------------------------------------

class ABI_EXPORT IE_CanvasGraphic_Sniffer : public IE_ImpGraphicSniffer
{
public:
  IE_CanvasGraphic_Sniffer () { }
  ~IE_CanvasGraphic_Sniffer () { }

  /*!
   * Sniff the byte buffer to see if it contains vaild image data recognized
   * by gdk-pixbuf
   */
  virtual bool recognizeContents (const char * szBuf, UT_uint32 iNum) { return true; }
  virtual bool recognizeSuffix (const char * szSuffix) { return false; }

  bool getDlgLabels (const char ** pszDesc, const char ** pszSuffixList, IEGraphicFileType * ft)
  {
    *pszDesc = "Experimental Canvas Test";
    *pszSuffixList = "*.png";
    *ft = getType ();
    return true;
  }

  UT_Error constructImporter (IE_ImpGraphic ** ppieg)
  {
    *ppieg = new IE_CanvasGraphic ();
    return UT_OK;
  }
};

// -----------------------------------------------------------------------

ABI_PLUGIN_DECLARE ("CanvasTest")

IE_CanvasGraphic_Sniffer * m_sniffer = 0;

ABI_FAR_CALL extern "C"
int abi_plugin_register (XAP_ModuleInfo * mi)
{
  mi->name = "Experimental Canvas Test";
  mi->desc = "This is exploring canvas functionality required for SVG support and AbiDraw/Show";
  mi->version = ABI_PLUGIN_VERSION;
  mi->author = "Abi, the Ant, & fjf, her friend.";
  mi->usage = "See back of Prayer Wheel for instructions.";

  if (!m_sniffer)
    {
      // create a new sniffer
      m_sniffer = new IE_CanvasGraphic_Sniffer ();
    }
  else
    {
      // else just reference the one we've got
      m_sniffer->ref ();
    }

  IE_ImpGraphic::registerImporter (m_sniffer);

  return 1;
};

ABI_FAR_CALL extern "C" 
int abi_plugin_unregister (XAP_ModuleInfo * mi)
{
  mi->name = 0;
  mi->desc = 0;
  mi->version = 0;
  mi->author = 0;
  mi->usage = 0;

  if (m_sniffer)
    {
      IE_ImpGraphic::unregisterImporter (m_sniffer);
    }
  if (!m_sniffer->unref ())
    {
      m_sniffer = 0;
    }

  return 1;
};

ABI_FAR_CALL extern "C"
int abi_plugin_supports_version (UT_uint32 major, UT_uint32 minor, UT_uint32 release)
{
  return 1;
};






