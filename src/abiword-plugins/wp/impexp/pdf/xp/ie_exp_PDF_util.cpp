/* Some code Copyright (C) 2002 John Wyrwas
 *
 * Based on the KWord Exporter 
 *
 * AbiWord
 * Copyright (C) 2001 AbiSource, Inc.
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
 *
 *
 */

/* PDF code based loosely on HTMLDOC
 *
 *   Copyright 1997-2002 by Easy Software Products.
 *
 *   These coded instructions, statements, and computer programs are the
 *   property of Easy Software Products and are protected by Federal
 *   copyright law.  Distribution and use rights are outlined in the file
 *   "COPYING.txt" which should have been included with this file.  If this
 *   file is missing or damaged please contact Easy Software Products
 *   at:
 *
 *       Attn: ESP Licensing Information
 *       Easy Software Products
 *       44141 Airport View Drive, Suite 204
 *       Hollywood, Maryland 20636-3111 USA
 *
 *       Voice: (301) 373-9600
 *       EMail: info@easysw.com
 *         WWW: http://www.easysw.com
 *
 */


#include <locale.h>
#include <ctype.h>
#include <time.h>
#include <zlib.h>
#include <math.h>

#include "md5.c"
#include "ut_string.h"
#include "ut_types.h"
#include "ut_misc.h"
#include "ut_units.h"
#include "ut_bytebuf.h"
#include "ut_base64.h"
#include "ut_debugmsg.h"
#include "ut_vector.h"
#include "pt_Types.h"
#include "pd_Document.h"
#include "pp_AttrProp.h"
#include "px_ChangeRecord.h"
#include "px_CR_Object.h"
#include "px_CR_Span.h"
#include "px_CR_Strux.h"
#include "pp_Property.h"
#include "ap_Prefs.h"
#include "pd_Style.h"
#include "fd_Field.h"
#include "xap_EncodingManager.h"
#include "fl_AutoNum.h"
#include "fp_PageSize.h"
#include "ut_string_class.h"

#include "ie_exp_PDF.h"


void IE_Exp_PDF::add_to_buffer(const char * sz, UT_uint32 length)
{
  if (!sz || !length)
    return;

  m_file_buffer.append((UT_Byte *)sz,length);
  return;
}
void IE_Exp_PDF::add_to_buffer(const char * sz)
{
  if (!sz)
    return;
  m_file_buffer.append((UT_Byte *)sz,strlen(sz));
  return;
}

void IE_Exp_PDF::pdf_start_stream()
{
  // Write the "/Length " string, get the position, and then write 10
  // zeroes to cover the maximum size of a stream.
  add_to_buffer("/Length ");
  pdf_stream_length = current_file_size();
  add_to_buffer("0000000000>>stream\n");
  pdf_stream_start = current_file_size();
}

// 'flate_open_stream()' - Open a deflated output stream.
void IE_Exp_PDF::flate_open_stream()
{
  compressor_active = 1;
  compressor.zalloc = (alloc_func)0;
  compressor.zfree  = (free_func)0;
  compressor.opaque = (voidpf)0;
  deflateInit(&compressor, 1);

  compressor.next_out  = (Bytef *)comp_buffer;
  compressor.avail_out = sizeof(comp_buffer);
}


// 'flate_close_stream()' - Close a deflated output stream.
void IE_Exp_PDF::flate_close_stream()
{
  while (deflate(&compressor, Z_FINISH) != Z_STREAM_END)
    {
      add_to_buffer((const char *)comp_buffer, (UT_Byte *)compressor.next_out - (UT_Byte *)comp_buffer);
      compressor.next_out  = (Bytef *)comp_buffer;
      compressor.avail_out = sizeof(comp_buffer);
    }

  if ((UT_Byte *)compressor.next_out > (UT_Byte *)comp_buffer)
    add_to_buffer((const char *)(comp_buffer), (UT_Byte *)compressor.next_out - (UT_Byte *)comp_buffer);

  deflateEnd(&compressor);
  compressor_active = 0;
}

//flate_puts()' - Write a character string to a compressed stream.
void IE_Exp_PDF::flate_puts(const char *s)
{
  flate_write((UT_Byte *)s, strlen(s));
}


//'flate_write()' - Write data to a compressed stream.
void IE_Exp_PDF::flate_write(UT_Byte *buf,int length)
{
  int flush = 0;
  if (compressor_active)
    {
      compressor.next_in  = buf;
      compressor.avail_in = length;
      while (compressor.avail_in > 0)
        {
          if (compressor.avail_out < (int)(sizeof(comp_buffer) / 8))
            {
              add_to_buffer((const char *)comp_buffer,
                            (UT_Byte *)compressor.next_out - (UT_Byte *)comp_buffer);
              compressor.next_out  = (Bytef *)comp_buffer;
              compressor.avail_out = sizeof(comp_buffer);
            }
          deflate(&compressor, flush ? Z_FULL_FLUSH : Z_NO_FLUSH);
          flush = 0;
        }
    }
  else
    add_to_buffer((const char *)buf, length);
}


// Writes a text entry
void IE_Exp_PDF::write_string(UT_Byte *s,int compress)	/* I - Compress output? */
{
  if (compress)
    flate_write((UT_Byte *)"(", 1);
  else
    add_to_buffer("(");
  while (*s != '\0')
    {       // This section changes invalid characters
      if (*s == 160)
        { 	/* &nbsp; */
          if (compress)
            flate_write((UT_Byte *)" ", 1);
          else
            add_to_buffer(" ");
        }
      else if (*s < 32 || *s > 126)
        {
          if (compress)
            {
              flate_printf("\\%o", *s);
            }
          else
            {
              doc_printf("\\%o", *s);
            }
        }
      else if (compress)
        {
          if (*s == '(' || *s == ')' || *s == '\\')
            flate_write((UT_Byte *)"\\", 1);
          flate_write(s, 1);
        }
      else
        {
          if (*s == '(' || *s == ')' || *s == '\\')
            add_to_buffer("\\");

          add_to_buffer((const char *)(*s));
        }
      s ++;
    }
  if (compress)
    flate_write((UT_Byte *)")", 1);
  else
    add_to_buffer(")");
}


int IE_Exp_PDF::pdf_start_object()
{
  int * temp = new int;
  *temp = current_file_size();

  m_num_objects++;
  m_objects.addItem(temp);
  doc_printf( "%d 0 obj", m_num_objects);

  pdf_object_type = 0;
  add_to_buffer(pdf_object_type ? "[" : "<<");
  return (m_num_objects); //	 Object number
}

void IE_Exp_PDF::pdf_end_object()
{
  int	length;			// Total length of stream
  int	write_size;		/* Length of output string */
  char		buf[10240];	/* Output buffer */

  if (pdf_stream_start)
    {
      // For streams, go back and update the length field in the
      // object dictionary...
      length = current_file_size() - pdf_stream_start;
      write_size = snprintf(buf, sizeof(buf),"%-10d", length);
      m_file_buffer.overwrite(pdf_stream_length, (UT_Byte *)buf, write_size);

      pdf_stream_start = 0;
      add_to_buffer("endstream\n");
    }
  else
    add_to_buffer(pdf_object_type ? "]" : ">>");
  add_to_buffer("endobj\n");
}


void IE_Exp_PDF::set_font(int typeface,float size)
{
  char	sizes[255],	// Formatted string for size
  *s;		// Pointer to end of string

  if (typeface == render_typeface &&
      size == render_size)
    return;


  // Format size and strip trailing 0's and decimals...
  sprintf(sizes, "%.1f", size);

  for (s = sizes + strlen(sizes) - 1; s > sizes && *s == '0'; s --)
    *s = '\0';

  if (*s == '.')
    *s = '\0';

  // Set the new typeface, style, and size.

  flate_printf("/F%x ", typeface);
  flate_printf("%s Tf ", sizes);

  render_typeface = typeface;
  render_size     = size;
}


void IE_Exp_PDF::set_pos(float x,float y)
{
  char	xs[255],	// Formatted string for X...
  ys[255],	// Formatted string for Y.
  *s;		// Pointer to end of string


  if (fabs(render_x - x) < 0.1 && fabs(render_y - y) < 0.1)
    return;

  if (render_x == -1.0)
    {
      sprintf(xs, "%.3f", x);
      sprintf(ys, "%.3f", y);
    }
  else
    {
      sprintf(xs, "%.3f", x - render_startx);
      sprintf(ys, "%.3f", y - render_y);
    }

  //Strip trailing 0's and decimals...
  for (s = xs + strlen(xs) - 1; s > xs && *s == '0'; s --)
    *s = '\0';

  if (*s == '.')
    *s = '\0';

  for (s = ys + strlen(ys) - 1; s > ys && *s == '0'; s --)
    *s = '\0';

  if (*s == '.')
    *s = '\0';

  flate_printf("%s ", xs);
  flate_printf("%s Td", ys);

  render_x = render_startx = x;
  render_y = y;
}


//'set_color()' - Set the current text color...
void IE_Exp_PDF::set_color(float *rgb)	/* I - RGB color */
{
  if (rgb[0] == render_rgb[0] &&
      rgb[1] == render_rgb[1] &&
      rgb[2] == render_rgb[2])
    return;

  render_rgb[0] = rgb[0];
  render_rgb[1] = rgb[1];
  render_rgb[2] = rgb[2];

  flate_printf("%.2f ",rgb[0]);
  flate_printf("%.2f ",rgb[1]);
  flate_printf("%.2f rg ",rgb[2]);
}


/* end file */
