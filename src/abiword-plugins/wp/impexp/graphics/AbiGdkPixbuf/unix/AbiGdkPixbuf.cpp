/* -*- c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */
/* AbiWord Graphic importer employing GdkPixbuf
 * Copyright (C) 2001 Martin Sevior
 * Copyright (C) 2002 Dom Lachowicz
 *
 * Portions from GdkPixBuf Library 
 * Copyright (C) 1999 The Free Software Foundation
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
#include <glib.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gdk-pixbuf/gdk-pixbuf-loader.h>

#include "ut_debugmsg.h"
#include "ut_types.h"
#include "xap_Module.h"
#include "ie_impGraphic.h"
#include "fg_GraphicRaster.h"
#include <png.h>

//------------------------------------------------------------------------------------

/*! 
 * This class will import any graphic type supported by gdk-pixbuf
 * into a png buffer for abiword.
 */

static void _write_png( png_structp png_ptr, 
		        png_bytep data, 
		        png_size_t length )
{
	UT_ByteBuf* bb = (UT_ByteBuf*) png_get_io_ptr(png_ptr);
	bb->append(data, length);
}


static void _write_flush(png_structp png_ptr) { } // Empty Fuction.

//------------------------------------------------------------------------------------

class ABI_EXPORT IE_PixbufGraphic : public IE_ImpGraphic
{
public:

	IE_PixbufGraphic()
		: IE_ImpGraphic(), m_pPngBB(NULL)
	{
	}
	
	virtual ~IE_PixbufGraphic()
	{
		// we likely don't own the m_pPngBB, so don't free it
	}

	/*!
	 * Convert an image data buffer into PNG image buffer.
	 */
	virtual UT_Error importGraphic(UT_ByteBuf * pBB, FG_Graphic ** ppfg)
	{
		GdkPixbuf * pixbuf = pixbufForByteBuf ( pBB );

		if (!pixbuf)
		{
			UT_DEBUGMSG (("GdkPixbuf: couldn't get image from loader!\n"));
			return UT_ERROR;
		}

		// Initialize stuff to create our PNG.
		UT_Error err = Initialize_PNG();
		if (err)
		{
			g_object_unref(G_OBJECT(pixbuf));
			return err;
		}

		if (setjmp(m_pPNG->jmpbuf))
		{
			g_object_unref(G_OBJECT(pixbuf));
			png_destroy_write_struct(&m_pPNG, &m_pPNGInfo);
			return UT_ERROR;
		}

		//
		// Build the png member variables.
		//
	    _createPNGFromPixbuf(pixbuf);

		//
		// Get rid of these now that they are no longer needed
		//
		g_object_unref(G_OBJECT(pixbuf));
		png_destroy_write_struct(&m_pPNG, &m_pPNGInfo);

		FG_GraphicRaster * pFGR = new FG_GraphicRaster();
		if(pFGR == NULL)
		{
			return UT_IE_NOMEMORY;
		}

		if(!pFGR->setRaster_PNG(m_pPngBB)) 
		{
			DELETEP(pFGR);		
			return UT_IE_FAKETYPE;
		}

		*ppfg = (FG_Graphic *) pFGR;
		return UT_OK;
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
	 * Convert an image byte buffer into a PNG byte buffer
	 */
	virtual UT_Error convertGraphic(UT_ByteBuf* pBB,
									UT_ByteBuf** ppBB)
	{
		GdkPixbuf * pixbuf = pixbufForByteBuf (pBB);

		if (!pixbuf)
		{			
			return UT_ERROR;
		}

		// Initialize stuff to create our PNG.
		UT_Error err =Initialize_PNG();
		if (err)
		{
			g_object_unref(G_OBJECT(pixbuf));
			return err;
		}

		if (setjmp(m_pPNG->jmpbuf))
		{
			png_destroy_write_struct(&m_pPNG, &m_pPNGInfo);
			g_object_unref(G_OBJECT(pixbuf));
			return UT_ERROR;
		}

		//		
		// Build the png member variables.
		//
	    _createPNGFromPixbuf(pixbuf);

		// cleanup
		g_object_unref(G_OBJECT(pixbuf));
		png_destroy_write_struct(&m_pPNG, &m_pPNGInfo);

		*ppBB =  m_pPngBB;
		return UT_OK;
	}

private:

	void _createPNGFromPixbuf(GdkPixbuf * pixbuf)
	{
		int colorType = PNG_COLOR_TYPE_RGB;

		//
		// OK define the PNG header from the info in GdkPixbuf
		//

		UT_uint32 width =  gdk_pixbuf_get_width(pixbuf);
		UT_uint32 height = gdk_pixbuf_get_height(pixbuf);
		int rowstride = gdk_pixbuf_get_rowstride(pixbuf);
		guchar * pBuf = gdk_pixbuf_get_pixels(pixbuf);

		if(gdk_pixbuf_get_has_alpha(pixbuf))
		{
			colorType =  PNG_COLOR_TYPE_RGB_ALPHA;
		}
		//
		// Abi only has 8 bits per sample
		//
		static const int bitsPerSampleAbi = 8;
		png_set_IHDR ( m_pPNG,  m_pPNGInfo,
					   width,			       
					   height,			       
					   bitsPerSampleAbi,
					   colorType,
					   PNG_INTERLACE_NONE,
					   PNG_COMPRESSION_TYPE_DEFAULT,
					   PNG_FILTER_TYPE_DEFAULT );
		
		png_write_info(m_pPNG, m_pPNGInfo);
		UT_Byte* pngScanline = new UT_Byte[rowstride];

		for(UT_uint32 i =0; i < height; i++)
		{
			memmove(pngScanline,pBuf,rowstride);
			png_write_row(m_pPNG, pngScanline);
			pBuf += rowstride;
		}

		DELETEP (pngScanline);		
		png_write_end(m_pPNG, m_pPNGInfo);
	}

	/*!
	 * Massage the byte buffer into an array of strings that can be loaded by 
	 * gdk-pixbuf
	 */
	GdkPixbuf * _loadXPM(UT_ByteBuf * pBB)
	{
		GdkPixbuf * pixbuf = NULL;
		char * pBC = (char *) pBB->getPointer(0);

		UT_Vector vecStr;
		UT_sint32 k =0;
		UT_sint32 iBase =0;

		//
		// Find dimension line to start with.
		//
		UT_sint32 length = (UT_sint32) pBB->getLength();
		for(k =0; (*(pBC+k) != '"') &&( k < length); k++)
			;

		if(k >= length)
		{
			return NULL;
		}

		k++;
		iBase = k;
		for(k =k; (*(pBC+k) != '"') && (k < length); k++)
			;
		if(k >= length)
		{
			return NULL;
		}

		char * sz = NULL;
		UT_sint32 kLen = k-iBase+1;
		sz = (char *)UT_calloc(kLen,sizeof(char));
		UT_sint32 i =0;

		for(i=0; i< (kLen -1); i++)
		{
			*(sz+i) = *(pBC+iBase+i);
		}
		*(sz+i) = 0;
		vecStr.addItem((void *) sz);

		//
		// Now loop through all the lines until we get to "}" outside the
		// '"'
		while((*(pBC+k) != '}')  && (k < length) )
		{
			k++;

			//
			// Load a single string of data into our vector.
			// 
			if(*(pBC+k) =='"')
			{
				//
				// Start of a line
				//
				k++;
				iBase = k;
				for(k =k; (*(pBC+k) != '"') && (k < length); k++) {}
				if(k >= length)
				{
					return NULL;
				}
				sz = NULL;
				kLen = k-iBase+1;
				sz = (char *)UT_calloc(kLen,sizeof(char));
				for(i=0; i<(kLen -1); i++)
				{
					*(sz+i) = *(pBC+iBase+i);
				}
				*(sz +i) = 0;
				vecStr.addItem((void *) sz);
			}
		}

		if(k >= length)
		{
			for(i=0; i< (UT_sint32) vecStr.getItemCount(); i++)
			{
				char * psz = (char *) vecStr.getNthItem(i);
				FREEP(psz);
			}
			return NULL;
		}

		const char ** pszStr = (const char **)UT_calloc(vecStr.getItemCount(),sizeof(char *));
		for(i=0; i< (UT_sint32) vecStr.getItemCount(); i++)
		{
			pszStr[i] = (const char *) vecStr.getNthItem(i);
		}
		pixbuf = gdk_pixbuf_new_from_xpm_data(pszStr);
		DELETEP(pszStr);
		return pixbuf;
	}

	GdkPixbuf * pixbufForByteBuf (UT_ByteBuf * pBB)
	{
		if ( !pBB || !pBB->getLength() )
			return NULL;

		GdkPixbuf * pixbuf = NULL;

		bool bIsXPM = false;
		const char * szBuf = (const char *)pBB->getPointer(0);
		if((pBB->getLength() > 9) && (strncmp (szBuf, "/* XPM */", 9) == 0))
		{
			bIsXPM = true;
		}

		if(bIsXPM)
		{
			pixbuf = _loadXPM(pBB);
 		}
		else
		{
			GError * err = 0;
			GdkPixbufLoader * ldr = 0;

			ldr = gdk_pixbuf_loader_new ();
			if (!ldr)
				{
					UT_DEBUGMSG (("GdkPixbuf: couldn't create loader! WTF?\n"));
					UT_ASSERT (ldr);
					return NULL ;
				}

			if ( FALSE== gdk_pixbuf_loader_write (ldr, (const guchar *)pBB->getPointer (0),
												  (gsize)pBB->getLength (), &err) )
				{
					UT_DEBUGMSG(("DOM: couldn't write to loader: %s\n", err->message));
					g_error_free(err);
					gdk_pixbuf_loader_close (ldr, NULL);
					g_object_unref (G_OBJECT(ldr));
					return NULL ;
				}
			
			gdk_pixbuf_loader_close (ldr, NULL);
			pixbuf = gdk_pixbuf_loader_get_pixbuf (ldr);

			// ref before closing the loader
			if ( pixbuf )
				g_object_ref (G_OBJECT(pixbuf));

			g_object_unref (G_OBJECT(ldr));
		}

		return pixbuf;
	}
	
	UT_Error Initialize_PNG(void)
	{
		/* Set up png structures for writing */
		m_pPNG = png_create_write_struct( PNG_LIBPNG_VER_STRING, 
										  (void*) NULL,
										  NULL, 
										  NULL );
		if( m_pPNG == NULL )
			{
				return UT_ERROR;
			}
		
		m_pPNGInfo = png_create_info_struct(m_pPNG);
		if ( m_pPNGInfo == NULL )
			{
				png_destroy_write_struct(&m_pPNG, (png_infopp) NULL);
				return UT_ERROR;
		}
		
		/* Set error handling if you are using the setjmp/longjmp method (this is
		 * the normal method of doing things with libpng).  REQUIRED unless you
		 * set up your own error handlers in the png_create_read_struct() earlier.
		 */
		if (setjmp(m_pPNG->jmpbuf))
			{
				/* Free all of the memory associated with the png_ptr and info_ptr */
				png_destroy_write_struct(&m_pPNG, &m_pPNGInfo);
				
				/* If we get here, we had a problem reading the file */
				return UT_ERROR;
			}
		m_pPngBB = new UT_ByteBuf;  /* Byte Buffer for Converted Data */
		
		/* Setting up the Data Writing Function */
		png_set_write_fn(m_pPNG, (void *)m_pPngBB, (png_rw_ptr)_write_png, (png_flush_ptr)_write_flush);
		
		return UT_OK;
	}

	// PNG structures used
	png_structp m_pPNG;				// libpng structure for the PNG Object
	png_infop   m_pPNGInfo;			// libpng structure for info on the PNG Object
	UT_ByteBuf*  m_pPngBB;				// pBB Converted to PNG File
	bool m_bIsXPM;

};

// ---------------------------------------------------------------------------

class ABI_EXPORT IE_PixbufGraphic_Sniffer : public IE_ImpGraphicSniffer
{
public:
	IE_PixbufGraphic_Sniffer()
	  : IE_ImpGraphicSniffer()
	{
	}

	virtual ~IE_PixbufGraphic_Sniffer() 
	{
	}

	/*!
	 * Sniff the byte buffer to see if it contains vaild image data recognized
	 * by gdk-pixbuf
	 */
	virtual UT_Confidence_t recognizeContents(const char * szBuf, UT_uint32 iNum)
	{

		//
		//  Handle xpm differently coz the standard gdk-pixbuf loader scheme doesn't
		// work for these!
		//
		if((iNum > 9) && (strncmp (szBuf, "/* XPM */", 9) == 0))
		{
			return UT_CONFIDENCE_PERFECT;
		}

		GdkPixbufLoader * ldr = gdk_pixbuf_loader_new ();
		UT_return_val_if_fail (ldr, UT_CONFIDENCE_ZILCH);

		GError * err = NULL;
		if ( FALSE == gdk_pixbuf_loader_write (ldr, (const guchar *) szBuf,(gsize)iNum, &err) )
			{
				gdk_pixbuf_loader_close (ldr, NULL);
				return UT_CONFIDENCE_ZILCH;
			}

		gdk_pixbuf_loader_close (ldr, NULL);
		GdkPixbuf * pixbuf =  gdk_pixbuf_loader_get_pixbuf (ldr);

		if(pixbuf)
	  	{
			// never need to ref the pixbuf
			return UT_CONFIDENCE_PERFECT;
		}
		else
		{
			// never need to ref the pixbuf
			return UT_CONFIDENCE_ZILCH;
		}
	}

	virtual UT_Confidence_t recognizeSuffix(const char * szSuffix)
	{
		static const char * suffixes[] =  
		{
			".jpg",
			".jpeg",
			".png",
			".tif",
			".tiff",
			".gif",
			".xpm",
			".pnm",
			".ras",
			".ico",
			".bmp",
			".xbm"
		} ;

		for ( unsigned int i = 0; i < NrElements(suffixes); i++ )
			if ( UT_stricmp(szSuffix, suffixes[i] ) == 0 )
				return UT_CONFIDENCE_PERFECT;

		return UT_CONFIDENCE_ZILCH;
	}

	virtual bool getDlgLabels(const char ** pszDesc,
							  const char ** pszSuffixList,
							  IEGraphicFileType * ft)
	{
		// TODO add a more complete list of suffixes
		*pszDesc = "All GdkPixbuf images";
		*pszSuffixList = "*.jpg; *.jpeg; *.png; *.tiff; *.gif; *.xpm; *.pnm; *.ras; *.ico; *.bmp; *.xbm";
		*ft = getType ();
		return true;
	}
	
	virtual UT_Error constructImporter(IE_ImpGraphic **ppieg)
	{
		*ppieg = new IE_PixbufGraphic();
		if (*ppieg == NULL)
			return UT_IE_NOMEMORY;
		return UT_OK;
	}
};

// -----------------------------------------------------------------------

ABI_PLUGIN_DECLARE("AbiGdkPixbuf")

static IE_PixbufGraphic_Sniffer * m_sniffer = 0;

ABI_FAR_CALL  extern "C"
int abi_plugin_register (XAP_ModuleInfo * mi)
{
    mi->name = "GdkPixbuf Image loader Plugin";
    mi->desc = "This will enable AbiWord to read any graphic type that GdkPixbuf supports.";
    mi->version = ABI_VERSION_STRING;
    mi->author = "Martin Sevior and Dom Lachowicz";
    mi->usage = "No Usage";

    if (!m_sniffer)
    {
		// create a new sniffer
		m_sniffer = new IE_PixbufGraphic_Sniffer ();
	}
    else
	{
		// else just reference the one we've got
		m_sniffer->ref();
	}

    IE_ImpGraphic::registerImporter ( m_sniffer );

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

    if ( m_sniffer )
	{
		IE_ImpGraphic::unregisterImporter ( m_sniffer );
	}
    if (!m_sniffer->unref())
    {
		m_sniffer = 0;
	}

    return 1;
};

ABI_FAR_CALL  extern "C"
int abi_plugin_supports_version (UT_uint32 major, UT_uint32 minor, UT_uint32 release)
{
  if ( major >= 1 && minor >= 1 ) // >= 1.1 is true
    return 1;
  return 0;
};
