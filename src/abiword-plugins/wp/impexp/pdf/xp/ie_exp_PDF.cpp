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
#include "xap_Module.h"
#include "ie_exp_PDF.h"


/*****************************************************************/
/*****************************************************************/

// we use a reference-counted sniffer
static IE_Exp_PDF_Sniffer * m_expSniffer = 0;

ABI_FAR_CALL
int abi_plugin_register (XAP_ModuleInfo *mi)
{
  if (!m_expSniffer)
    {
      m_expSniffer = new IE_Exp_PDF_Sniffer ();
    }
  else
    {
      m_expSniffer->ref();
    }

  mi->name = "PDF Exporter";
  mi->desc = "Exports PDF Documents";
  mi->version = ABI_VERSION_STRING;
  mi->author = "John Wyrwas and Abi the Ant";
  mi->usage = "No Usage";

  IE_Exp::registerExporter(m_expSniffer);
  return 1;
}

ABI_FAR_CALL
int abi_plugin_unregister(XAP_ModuleInfo *mi)
{
  mi->name = 0;
  mi->desc = 0;
  mi->version = 0;
  mi->author = 0;
  mi->usage = 0;

  UT_ASSERT(m_expSniffer);

  IE_Exp::unregisterExporter(m_expSniffer);
  if (!m_expSniffer->unref())
    {
      m_expSniffer = 0;
    }

  return 1;
}

ABI_FAR_CALL
int abi_plugin_supports_version(UT_uint32 major, UT_uint32 minor, UT_uint32 release)
{
  return 1;
}


/*****************************************************************/
/*****************************************************************/


IE_Exp_PDF::IE_Exp_PDF(PD_Document * pDocument)
    : IE_Exp(pDocument), m_pListener(0),
    pdf_stream_length(0),
    pdf_stream_start(0),
    pdf_object_type(0),
    m_num_objects(0),
    m_num_pages(0),
    m_info_object(0),
    m_pages_object(0),
    m_root_object(0),
    compressor_active(0)

{
  m_error = UT_OK;
}

IE_Exp_PDF::~IE_Exp_PDF()
{}

void IE_Exp_PDF::write_document(UT_Vector document)
{
  int i;
  m_pages = document;

  //get the object counts
  m_num_pages = document.getItemCount();
  m_num_objects =0;
  for(i = 0; i < m_num_pages; i++)
    {
      m_num_objects += ((page_t *)m_pages[i])->renders.getItemCount();
    }

  //writing the document
  write_prolog();

  pdf_start_object();
  add_to_buffer("/Type/Pages");
  doc_printf("/Count %d", m_num_pages);
  add_to_buffer("/Kids[");

  for (int page = 1; page <= m_num_pages; page ++)
    doc_printf("%d 0 R\n", (m_num_objects + 1) + 2 * page + 1);
  add_to_buffer("]");
  pdf_end_object();

  for(i = 0; i < (int)(m_pages.getItemCount()); i++)
    write_page(i);

  write_trailer();
  write((const char *)(m_file_buffer.getPointer(0)), m_file_buffer.getLength());
}


int IE_Exp_PDF::current_file_size()
{
  return (m_file_buffer.getLength());
}


void IE_Exp_PDF::write_prolog()
{
  time_t	doc_time;	// Current time
  struct tm *doc_date;	// Current date

  doc_time = time(NULL);
  doc_date = localtime(&doc_time);

  int		i;
  char		temp[1024];	// Temporary string
  md5_state_t	md5;		// MD5 state


  // Write PDF prolog
  doc_printf("%%PDF-%.1f\n", 1.3);  //outputs version, 1.3
  add_to_buffer("%\342\343\317\323\n");
  m_num_objects = 0;

  // Compute the file ID...
  md5_init(&md5);
  md5_append(&md5, (md5_byte_t *)(getFileName()), sizeof(getFileName()));
  md5_append(&md5, (md5_byte_t *)&doc_time, sizeof(doc_time));
  md5_finish(&md5, m_file_id);

  // Write info object...
  m_info_object = pdf_start_object();
  add_to_buffer("/Producer");
  write_string((UT_Byte *)"AbiWord.", 0);
  add_to_buffer("/CreationDate");

  //TODO replace this with byte buffer
  sprintf(temp, "D:%04d%02d%02d%02d%02d%02d%+03d%02d",
          doc_date->tm_year + 1900, doc_date->tm_mon + 1, doc_date->tm_mday,
          doc_date->tm_hour, doc_date->tm_min, doc_date->tm_sec,
          (int)(-timezone / 3600),
          (int)(((timezone < 0 ? -timezone : timezone) / 60) % 60));
  write_string((UT_Byte *)temp, 0);

  // TODO optional keywords

  //add_to_buffer("/Title");
  //write_string(**TITLE**, 0);
  //add_to_buffer("/Author");
  //write_string(** AUTHOR **, 0);
  add_to_buffer("/Creator");
  write_string((UT_Byte *)"AbiWord", 0);
  //add_to_buffer("/Keywords");
  //write_string(** KEYWORDS **, 0);

  pdf_end_object();

  for (i = 0; i < (int)(m_fonts.getItemCount()); i ++)
    {
      int * temp_int = new int;
      *temp_int = pdf_start_object();
      m_font_objects.addItem((void *)temp_int);
      add_to_buffer("/Type/Font");
      // Use Type1 font...
      add_to_buffer("/Subtype/Type1");
      doc_printf("/BaseFont/%s", ((UT_String *)m_fonts[i])->c_str());
      add_to_buffer("/Encoding/WinAnsiEncoding"); //TODO should use native encoding!
      pdf_end_object();
    }
}

// 'write_trailer()' - Write the file trailer.
void IE_Exp_PDF::write_trailer()
{
  int		i,	offset;		//  Offset to xref table in PDF file

  m_root_object = pdf_start_object();

  add_to_buffer("/Type/Catalog");
  doc_printf("/Pages %d 0 R", m_pages_object);
  doc_printf("/PageLayout/%s", "SinglePage"); //let layout code handle columns
  doc_printf("/PageMode/%s", "UseNone");
  pdf_end_object();

  offset = current_file_size();

  add_to_buffer("xref\n");
  doc_printf("0 %d \n", m_num_objects + 1);
  add_to_buffer("0000000000 65535 f \n");
  for (i = 0; i < (int)(m_objects.getItemCount()); i ++)
    doc_printf("%010d 00000 n \n", (int *)m_objects[i]);

  add_to_buffer("trailer\n");
  add_to_buffer("<<");
  doc_printf("/Size %d", m_num_objects + 1);
  doc_printf("/Root %d 0 R", m_root_object);
  doc_printf("/Info %d 0 R", m_info_object);
  add_to_buffer("/ID[<");
  for (i = 0; i < 16; i ++)
    doc_printf("%02x", m_file_id[i]);
  add_to_buffer("><");
  for (i = 0; i < 16; i ++)
    doc_printf("%02x", m_file_id[i]);
  add_to_buffer(">]");

  add_to_buffer(">>\n");
  add_to_buffer("startxref\n");
  doc_printf("%d\n", offset);
  add_to_buffer("%%EOF\n");
}


int IE_Exp_PDF::addfont(UT_String name, UT_String style)
{
  UT_String * temp = new UT_String;
  int item;

  if(!(style == ""))
    *temp = name + "-" + style;
  else
    *temp = name;
  item = m_fonts.findItem(temp);
  if (item == -1)
    m_fonts.addItem(temp);
  return (m_fonts.findItem(temp));
}

UT_Vector IE_Exp_PDF::getfonts()
{
  return m_fonts;
}


void IE_Exp_PDF::write_page(int page)
{

  page_t	*p;		// Current page
  render_t	*r;		// Render pointer
  float		box[3];		// RGB color for boxes

  p = (page_t *)(m_pages[page]);

  // Clear the render cache...
  render_rgb[0]   = 0.0f;
  render_rgb[1]   = 0.0f;
  render_rgb[2]   = 0.0f;
  render_x        = -1.0f;
  render_y        = -1.0f;
  box[0]          = -1.0f;
  box[1]          = -1.0f;
  box[2]          = -1.0f;

  pdf_start_object();
  add_to_buffer("/Type/Page");
  doc_printf("/Parent %d 0 R", m_pages_object);
  doc_printf("/Contents %d 0 R", m_num_objects + 1);
  doc_printf("/MediaBox[0 0 %d ", p->width);
  doc_printf("%d]",p->length);
  write_resources(page);
  pdf_end_object();

  pdf_start_object();
  add_to_buffer("/Filter/FlateDecode");

  pdf_start_stream();
  flate_open_stream();

  flate_puts("q\n");

  flate_printf("1 0 0 1 %d ", p->left);
  flate_printf("%d cm\n", p->bottom);

  // Render all graphics elements...

  for (int i = 0; i < (int)(p->renders.getItemCount()); i++)
    {
      r = (render_t *)(p->renders[i]);
      switch (r->type)
        {
        case RENDER_IMAGE :
          if (r->width > 0.01f && r->height > 0.01f)
            //TODO          write_image(r); //need to implement this funct.
            break;

        case RENDER_BOX :  //RENDER_BOX's are underlines, overlines, etc.
          if (r->height == 0.0)
            {
              if (box[0] != r->box[0] ||
                  box[1] != r->box[1] ||
                  box[2] != r->box[2])
                {
                  flate_printf("%.2f ", box[0] = r->box[0]);

                  flate_printf("%.2f ",box[1] = r->box[1]);
                  flate_printf("%.2f RG\n",box[2] = r->box[2]);
                }
              flate_printf("%.1f ",r->x);
              flate_printf("%.1f ", r->y);
              flate_printf("m %.1f ", r->x + r->width);
              flate_printf("%.1f l S\n", r->y);
            }
          else
            {
              set_color(r->box);
              flate_printf("%.1f ",r->x);
              flate_printf("%.1f ", r->y);
              flate_printf("%.1f ", r->width);
              flate_printf("%.1f re f\n", r->height);
            }
          break;
        }
    }


  // Render all text elements
  flate_puts("BT\n");

  render_typeface = -1;
  render_size     = -1;
  render_x        = -1.0f;
  render_y        = -1.0f;
  render_spacing  = -1.0f;

  for (int x = 0; x < (int)(p->renders.getItemCount()); x++)
    {
      r = (render_t *)(p->renders[x]);
      if (r->type == RENDER_TEXT)
        write_text(r);
    }

  flate_puts("ET\n");


  flate_puts("Q\n");
  flate_close_stream();

  pdf_end_object();
}


// 'write_text()' - Write a text entity.
void IE_Exp_PDF::write_text(render_t *r)
{

  if ( r->text.rgb[0] == render_rgb[0] &&
       r->text.rgb[1] == render_rgb[1] &&
       r->text.rgb[2] == render_rgb[2])
  {}
  else
    {
      render_rgb[0] = r->text.rgb[0];
      render_rgb[1] = r->text.rgb[1];
      render_rgb[2] = r->text.rgb[2];
      flate_printf("%.2f ", r->text.rgb[0]);
      flate_printf("%.2f ", r->text.rgb[1]);
      flate_printf("%.2f rg ", r->text.rgb[2]);
    }


  set_font(r->text.typeface, r->text.size);
  set_pos(r->x, r->y);

  if (r->text.spacing != render_spacing)
    {
      flate_printf(" %.3f Tc", render_spacing = r->text.spacing);
    }
  write_string((UT_Byte *)(r->text.buffer.c_str()), 1);
  flate_puts("Tj\n");
  render_x += r->width;
}




//'write_resources()' - Write the resources dictionary for a page.

void IE_Exp_PDF::write_resources(int  page)
{
  int		i;
  render_t	*r;		// Render pointer
  page_t	*p;
  int		images_used;	// Non-zero if the page uses an image
  int		text_used;	// Non-zero if the page uses text

  images_used = 0;
  text_used   = 0;
  p = (page_t *)(m_pages[page]);

  for (i = 0; i < (int)(p->renders.getItemCount()); i++)
    {
      r = (render_t *)(p->renders[i]);
      if (r->type == RENDER_IMAGE)
        images_used = 1;
      else if (r->type == RENDER_TEXT)
        {
          text_used = 1;
        }
    }
  add_to_buffer("/Resources<<");

  if (!images_used)
    add_to_buffer("/ProcSet[/PDF/Text]");
  else
    {
      add_to_buffer("/ProcSet[/PDF/Text/ImageB/ImageC/ImageI]");
    }

  if (text_used) //output the fonts, TODO change to only ones used on page
    {
      add_to_buffer("/Font<<");
      for (i = 0; i < (int)(m_font_objects.getItemCount()); i ++)
        {
          doc_printf("/F%1x ", i);
          doc_printf("%d 0 R", (const char *)m_font_objects[i]);
        }
      add_to_buffer(">>");
    }

  add_to_buffer("/XObject<<");

  for(i = 0; i < (int)(p->renders.getItemCount()); i++)
    {
      r = (render_t *)(p->renders[i]);
      if (r->type == RENDER_IMAGE && r->image->obj)
        {
          doc_printf("/I%d ",r->image->obj);
          doc_printf("%d 0 R",r->image->obj);
        }
    }
  add_to_buffer(">>");
  add_to_buffer(">>");
}


//end file