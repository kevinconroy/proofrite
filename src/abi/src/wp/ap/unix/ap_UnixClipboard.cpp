/* AbiWord
 * Copyright (C) 1998-2002 AbiSource, Inc.
 * Copyright (C) 2002 Dom Lachowicz 
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

/*****************************************************************
** Only one of these is created by the application.
*****************************************************************/

#include <gdk/gdk.h>

#include "ut_types.h"
#include "ut_string.h"
#include "ut_vector.h"
#include "ap_UnixClipboard.h"
#include "ap_UnixApp.h"

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// RichText: cut and paste
#define AP_CLIPBOARD_TXT_RTF 			"text/rtf"
#define AP_CLIPBOARD_APPLICATION_RTF            "application/rtf"

// HTML: cut only
#define AP_CLIPBOARD_TXT_HTML                   "text/html"
#define AP_CLIPBOARD_APPLICATION_XHTML          "application/xhtml+xml"

// Images: cut and paste
#define AP_CLIPBOARD_IMAGE_PNG                  "image/png"

// Images: paste only
#define AP_CLIPBOARD_IMAGE_JPEG                 "image/jpeg"
#define AP_CLIPBOARD_IMAGE_GIF                  "image/gif"
#define AP_CLIPBOARD_IMAGE_BMP                  "image/bmp"
#define AP_CLIPBOARD_IMAGE_TIFF                 "image/tiff"
#define AP_CLIPBOARD_IMAGE_WBMP                 "image/vnd.wap.wbmp"
#define AP_CLIPBOARD_IMAGE_XBM                  "image/x-xbitmap"
#define AP_CLIPBOARD_IMAGE_XPM                  "image/x-xpixmap"
#define AP_CLIPBOARD_IMAGE_PNM                  "image/x-portable-anymap"
#define AP_CLIPBOARD_IMAGE_PGM                  "image/x-portable-graymap"
#define AP_CLIPBOARD_IMAGE_PPM                  "image/x-portable-pixmap"
#define AP_CLIPBOARD_IMAGE_RAS                  "image/x-cmu-raster"
#define AP_CLIPBOARD_IMAGE_WMF                  "image/x-wmf"
#define AP_CLIPBOARD_IMAGE_SVG                  "image/svg"
#define AP_CLIPBOARD_IMAGE_SVG_XML              "image/svg+xml"

// Text: cut and paste
#define AP_CLIPBOARD_TEXT_UTF8_STRING           "UTF8_STRING"
#define AP_CLIPBOARD_TEXT                       "TEXT"
#define AP_CLIPBOARD_TEXT_STRING                "STRING"
#define AP_CLIPBOARD_TEXT_PLAIN                 "text/plain"
#define AP_CLIPBOARD_TEXT_COMPOUND              "COMPOUND_TEXT"

static const char * rtfszFormatsAccepted[] = {
  AP_CLIPBOARD_TXT_RTF,
  AP_CLIPBOARD_APPLICATION_RTF,
  0 } ;

static const char * imgszFormatsAccepted[] = {
  AP_CLIPBOARD_IMAGE_PNG,
  AP_CLIPBOARD_IMAGE_JPEG,
  AP_CLIPBOARD_IMAGE_TIFF,
  AP_CLIPBOARD_IMAGE_GIF,
  AP_CLIPBOARD_IMAGE_BMP,
  AP_CLIPBOARD_IMAGE_XBM,
  AP_CLIPBOARD_IMAGE_XPM,
  AP_CLIPBOARD_IMAGE_PNM,
  AP_CLIPBOARD_IMAGE_PPM,
  AP_CLIPBOARD_IMAGE_PGM,
  AP_CLIPBOARD_IMAGE_WBMP,
  AP_CLIPBOARD_IMAGE_RAS,
  AP_CLIPBOARD_IMAGE_WMF,
  AP_CLIPBOARD_IMAGE_SVG,
  AP_CLIPBOARD_IMAGE_SVG_XML,
  0 } ;

static const char * txtszFormatsAccepted[] = {
  AP_CLIPBOARD_TEXT_UTF8_STRING,
  AP_CLIPBOARD_TEXT,
  AP_CLIPBOARD_TEXT_STRING,
  AP_CLIPBOARD_TEXT_PLAIN,
  AP_CLIPBOARD_TEXT_COMPOUND,
  0 } ;

AP_UnixClipboard::AP_UnixClipboard(AP_UnixApp * pApp)
  : XAP_UnixClipboard(pApp)
{
  // DECLARE IN ORDER OF PREFERENCE RECEIVING

  // rich text types
  AddFmt(AP_CLIPBOARD_TXT_RTF);
  AddFmt(AP_CLIPBOARD_APPLICATION_RTF);
  
  // plain text types
  AddFmt(AP_CLIPBOARD_TEXT_UTF8_STRING);
  AddFmt(AP_CLIPBOARD_TEXT);
  AddFmt(AP_CLIPBOARD_TEXT_STRING);
  AddFmt(AP_CLIPBOARD_TEXT_PLAIN);
  AddFmt(AP_CLIPBOARD_TEXT_COMPOUND);
  
  // hypertext types
  AddFmt ( AP_CLIPBOARD_TXT_HTML ) ; // actually XHTML, but who's counting?
  AddFmt ( AP_CLIPBOARD_APPLICATION_XHTML ) ;
  
  // image types
  AddFmt ( AP_CLIPBOARD_IMAGE_PNG ) ;
  AddFmt ( AP_CLIPBOARD_IMAGE_JPEG ) ;
  AddFmt ( AP_CLIPBOARD_IMAGE_TIFF ) ;
  AddFmt ( AP_CLIPBOARD_IMAGE_GIF ) ;
  AddFmt ( AP_CLIPBOARD_IMAGE_BMP ) ;
  AddFmt ( AP_CLIPBOARD_IMAGE_XBM ) ;
  AddFmt ( AP_CLIPBOARD_IMAGE_XPM ) ;
  AddFmt ( AP_CLIPBOARD_IMAGE_PNM ) ;
  AddFmt ( AP_CLIPBOARD_IMAGE_PPM ) ;
  AddFmt ( AP_CLIPBOARD_IMAGE_PGM ) ;
  AddFmt ( AP_CLIPBOARD_IMAGE_WBMP ) ;
  AddFmt ( AP_CLIPBOARD_IMAGE_RAS ) ;
  AddFmt ( AP_CLIPBOARD_IMAGE_WMF ) ;
  AddFmt ( AP_CLIPBOARD_IMAGE_SVG ) ;
  AddFmt ( AP_CLIPBOARD_IMAGE_SVG_XML ) ;
}

bool AP_UnixClipboard::addTextData(T_AllowGet tTo, void* pData, UT_sint32 iNumBytes)
{
  if ( addData(tTo, AP_CLIPBOARD_TEXT_UTF8_STRING, pData, iNumBytes) &&
       addData(tTo, AP_CLIPBOARD_TEXT, pData, iNumBytes) &&
       addData(tTo, AP_CLIPBOARD_TEXT_STRING, pData, iNumBytes) &&
       addData(tTo, AP_CLIPBOARD_TEXT_PLAIN, pData, iNumBytes) &&
       addData(tTo, AP_CLIPBOARD_TEXT_COMPOUND,  pData, iNumBytes) )
    return true;
  return false;
}

bool AP_UnixClipboard::addRichTextData(T_AllowGet tTo, void* pData, UT_sint32 iNumBytes)
{
  if ( addData ( tTo, AP_CLIPBOARD_TXT_RTF, pData, iNumBytes ) && 
       addData ( tTo, AP_CLIPBOARD_APPLICATION_RTF, pData, iNumBytes ) )
    return true ;
  return false ;
}

bool AP_UnixClipboard::addHtmlData(T_AllowGet tTo, void* pData, UT_sint32 iNumBytes)
{
  if ( addData ( tTo, AP_CLIPBOARD_TXT_HTML, pData, iNumBytes ) &&
       addData ( tTo, AP_CLIPBOARD_APPLICATION_XHTML, pData, iNumBytes ) )
    return true ;
  return false ;
}

bool AP_UnixClipboard::addPNGData(T_AllowGet tTo, void* pData, UT_sint32 iNumBytes)
{
  return addData ( tTo, AP_CLIPBOARD_IMAGE_PNG, pData, iNumBytes );
}

bool  AP_UnixClipboard::getSupportedData(T_AllowGet tFrom,
					 void ** ppData, UT_uint32 * pLen,
					 const char **pszFormatFound)
{
  // give priority to rich text, then images, then text
  if (getData(tFrom, rtfszFormatsAccepted, ppData, pLen, pszFormatFound))
    return true;
  else if (getData(tFrom, imgszFormatsAccepted, ppData, pLen, pszFormatFound))
    return true;
  else if (getTextData (tFrom, ppData, pLen, pszFormatFound))
    return true;

  return false;
}

bool  AP_UnixClipboard::getTextData(T_AllowGet tFrom,
				    void ** ppData, UT_uint32 * pLen,
				    const char **pszFormatFound)
{
  return getData(tFrom, txtszFormatsAccepted, ppData,pLen, pszFormatFound);
}

bool  AP_UnixClipboard::getRichTextData(T_AllowGet tFrom,
					void ** ppData, UT_uint32 * pLen,
					const char **pszFormatFound)
{
  return getData( tFrom, rtfszFormatsAccepted, ppData, pLen, pszFormatFound ) ;
}

bool AP_UnixClipboard::getImageData(T_AllowGet tFrom,
				    void ** ppData, UT_uint32 * pLen,
				    const char **pszFormatFound)
{
  return getData ( tFrom, imgszFormatsAccepted, ppData, pLen, pszFormatFound );
}

bool AP_UnixClipboard::isTextTag ( const char * tag )
{
  if ( !tag || !strlen(tag) )
    return false ;

  // getTextData will only return this because it's sort-of a hack
  if ( !UT_stricmp( tag, AP_CLIPBOARD_TEXT_UTF8_STRING ) ||
       !UT_stricmp( tag, AP_CLIPBOARD_TEXT ) ||
       !UT_stricmp( tag, AP_CLIPBOARD_TEXT_STRING ) ||
       !UT_stricmp( tag, AP_CLIPBOARD_TEXT_PLAIN ) ||
       !UT_stricmp( tag, AP_CLIPBOARD_TEXT_COMPOUND ) )
    return true ;
  return false ;
}

bool AP_UnixClipboard::isRichTextTag ( const char * tag )
{
  if ( !tag || !strlen(tag) )
    return false ;

  if ( !UT_stricmp ( tag, AP_CLIPBOARD_TXT_RTF ) ||
       !UT_stricmp ( tag, AP_CLIPBOARD_APPLICATION_RTF ) )
    return true ;
  return false ;
}

bool AP_UnixClipboard::isHTMLTag ( const char * tag )
{
  if ( !tag || !strlen(tag) )
    return false ;

  if ( !UT_stricmp ( tag, AP_CLIPBOARD_TXT_HTML ) ||
       !UT_stricmp ( tag, AP_CLIPBOARD_APPLICATION_XHTML ) )
    return true ;
  return false ;
}

bool AP_UnixClipboard::isImageTag ( const char * tag )
{
  if ( !tag || !strlen(tag) )
    return false ;

  if ( !strncmp ( tag, "image/", 6 ) )
    return true ;
  return false ;
}
