/* AbiSource Program Utilities
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


#include <stdlib.h>
#include <string.h>
#include <setjmp.h>

#include <png.h>

/* PNG-write stuff adapted from AbiGdkPixbuf plugin (Martin Sevior)
 * presumably originally from gr_UnixImage?
 */
static void _write_png (png_structp png_ptr, png_bytep data, png_size_t length)
{
  UT_ByteBuf * bb = (UT_ByteBuf *) png_get_io_ptr (png_ptr);
  bb->append (data, length);
}

static void _write_flush (png_structp png_ptr)
{
  // Empty Fuction.
}

bool UT_Canvas::savePNG (UT_ByteBuf ** ppBB, UT_sint32 offset_x, UT_sint32 offset_y, UT_uint32 width, UT_uint32 height)
{
  if ((pBB == 0) || (width == 0) || (height == 0)) return false; // erk!

  *ppBB = 0;

  unsigned char * pBuf = malloc (4 * width * sizeof (unsigned char));
  if (pBuf == 0) return false;

  png_structp pPNG = png_create_write_struct (PNG_LIBPNG_VER_STRING, 0, 0, 0);
  if (pPNG == 0)
    {
      FREEP (pBuf);
      return false;
    }

  png_infop pPNGInfo = png_create_info_struct (pPNG);
  if (pPNGInfo == 0)
    {
      png_destroy_write_struct (&pPNG, 0);
      FREEP (pBuf);
      return false;
    }

  /* Set error handling if you are using the setjmp/longjmp method (this is
   * the normal method of doing things with libpng).  REQUIRED unless you
   * set up your own error handlers in the png_create_read_struct() earlier.
   */
  if (setjmp (pPNG->jmpbuf))
    {
      png_destroy_write_struct (&pPNG, &pPNGInfo);
      FREEP (pBuf);
      return false; // PNG-write failed
    }

  UT_ByteBuf * pPngBB = new UT_ByteBuf; // Byte Buffer for Converted Data

  // Setting up the Data Writing Function
  png_set_write_fn (pPNG, (void *) pPngBB, (png_rw_ptr) _write_png, (png_flush_ptr) _write_flush);

  png_set_IHDR (pPNG, pPNGInfo, width, height, 8,
		PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

  png_write_info (pPNG, pPNGInfo);

  bool success = true;
  for (UT_uint32 y = offset_y; y < offset_y + height; y++)
    {
      memset (pBuf, 0, 4 * width * sizeof (unsigned char));
      CanvasHSet * hset = getHSet (y);
      if (hset)
	{
	  if (!hset->copyColor (pBuf, offset_x, width)) success = false;
	}
      if (!success) break;
      png_write_row (pPNG, pBuf);
    }

  png_write_end (pPNG, pPNGInfo);

  if (success)
    *ppBB = pPngBB;
  else
    DELETEP (pPngBB);

  FREEP (pBuf);
  return success;
}

/* PNG-read stuff adapted gr_UnixImage
 */
struct _bb
{
  const UT_ByteBuf * pBB;
  UT_uint32 iCurPos;
};

static void _png_read (png_structp png_ptr, png_bytep data, png_size_t length)
{
  struct _bb * p = (struct _bb *) png_get_io_ptr (png_ptr);
  const UT_Byte * pBytes = p->pBB->getPointer (0);

  memcpy (data, pBytes + p->iCurPos, length);
  p->iCurPos += length;
}


bool UT_Canvas::CanvasImage::loadPNG (UT_ByteBuf * pBB)
{
  if (pBB == 0) return false;

  png_structp png_ptr = png_create_read_struct (PNG_LIBPNG_VER_STRING, 0, 0, 0);
  if (png_ptr == 0)
    {
      return false;
    }

  png_infop info_ptr = png_create_info_struct (png_ptr);
  if (info_ptr == 0)
    {
      png_destroy_read_struct (&png_ptr, 0, 0);
      return false;
    }

  /* Set error handling if you are using the setjmp/longjmp method (this is
   * the normal method of doing things with libpng).  REQUIRED unless you
   * set up your own error handlers in the png_create_read_struct() earlier.
   */
  if (setjmp (png_ptr->jmpbuf))
    {
      png_destroy_read_struct (&png_ptr, &info_ptr, 0);
      return false; // If we get here, we had a problem reading the file
    }

  struct _bb myBB;
  myBB.pBB = pBB;
  myBB.iCurPos = 0;
  png_set_read_fn (png_ptr, (void *) &myBB, _png_read);

  png_read_info (png_ptr, info_ptr);
      
  png_uint_32 width;
  png_uint_32 height;
  int bit_depth;
  int color_type;
  int interlace_type;
  png_get_IHDR (png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, 0, 0);

  bool have_alpha = (color_type & PNG_COLOR_MASK_ALPHA);
  bool have_color = (color_type & PNG_COLOR_MASK_COLOR);

  /* Create the image buffer(s) and canvas before continuing
   */
  // int channels = png_get_channels (png_ptr, info_ptr);
  int channels = (have_alpha ? 1 : 0) + (have_color ? 3 : 1);

  unsigned char * buffer = (unsigned char *) malloc (channels * width * height * sizeof (unsigned char));
  if (buffer == 0)
    {
      png_destroy_read_struct (&png_ptr, &info_ptr, 0);
      return false;
    }
  unsigned char ** rowbuf = (unsigned char **) malloc (height * sizeof (unsigned char *));
  if (rowbuf == 0)
    {
      FREEP (buffer);
      png_destroy_read_struct (&png_ptr, &info_ptr, 0);
      return false;
    }
  for (png_uint_32 y = 0; y < height; y++) rowbuf[y] = buffer + y * channels * width * sizeof (unsigned char);

  UT_RGBAColor blank;
  if (!resetCanvas (blank, static_cast<UT_uint32>width, static_cast<UT_uint32>height))
    {
      FREEP (rowbuf);
      FREEP (buffer);
      png_destroy_read_struct (&png_ptr, &info_ptr, 0);
      return false;
    }

  /* Extract multiple pixels with bit depths of 1, 2, and 4 from a single
   * byte into separate bytes (useful for paletted and grayscale images).
   */
  png_set_packing (png_ptr);

  /* Expand paletted colors into true RGB triplets
   */
  png_set_expand (png_ptr);

  /* If we've got images with 16 bits per channel, we don't need that
   * much precision.  We'll do fine with 8 bits per channel
   */
  png_set_strip_16 (png_ptr);

  /* We want libpng to deinterlace the image for us
   */
  UT_uint32 iInterlacePasses = png_set_interlace_handling (png_ptr);

  while (iInterlacePasses)
    {
      png_read_rows (png_ptr, rowbuf, 0, height);
      iInterlacePasses--;
    }

  /* read rest of file, and get additional chunks in info_ptr - REQUIRED
   */
  png_read_end (png_ptr, info_ptr);

  /* clean up after the read, and free any memory allocated - REQUIRED
   */
  png_destroy_read_struct (&png_ptr, &info_ptr, 0);

  bool success = true;
  unsigned char * pixel = buffer;
  for (UT_uint32 y = 0; y < height; y++)
    for (UT_uint32 x = 0; x < width; x++)
      {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
	if (have_color)
	  {
	    r = *pixel; pixel++;
	    g = *pixel; pixel++;
	    b = *pixel; pixel++;
	  }
	else
	  {
	    r = *pixel;
	    g = *pixel;
	    b = *pixel; pixel++;
	  }
	if (have_alpha)
	  {
	    a = *pixel; pixel++;
	  }
	else
	  {
	    a = 0xff;
	  }
	UT_RGBAColor color(r, g, b, a);
	if (!m_Image[y]->setColor (x, color)) success = false;
      }

  FREEP (rowbuf);
  FREEP (buffer);

  return success;
}
