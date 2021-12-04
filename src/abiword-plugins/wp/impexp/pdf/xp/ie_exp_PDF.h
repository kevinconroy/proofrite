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


#ifndef IE_EXP_PDF_H
#define IE_EXP_PDF_H

#include <zlib.h>
#include "ie_exp.h"
#include "pl_Listener.h"
#include "ie_exp_PDF_render.h"
#include "ut_bytebuf.h"

/*****************************************************************/
/*****************************************************************/

#define doc_printf(format,p){ char temp_buffer[10240]; int length; length = snprintf(temp_buffer,sizeof(temp_buffer), format, p); add_to_buffer((const char *)temp_buffer, length);}
#define flate_printf(format,p){ char temp_buffer[10240]; int length; length = snprintf(temp_buffer,sizeof(temp_buffer), format, p); flate_write((UT_Byte *)temp_buffer, length);}

class PD_Document;
class s_PDF_Listener;

// The exporter/writer

class ABI_EXPORT IE_Exp_PDF_Sniffer : public IE_ExpSniffer
  {
    friend class IE_Exp;

  public:
    IE_Exp_PDF_Sniffer ();

    virtual ~IE_Exp_PDF_Sniffer ()
    {}

    virtual bool recognizeSuffix (const char * szSuffix);
    virtual bool getDlgLabels (const char ** szDesc,
                               const char ** szSuffixList,
                               IEFileType * ft);
    virtual UT_Error constructExporter (PD_Document * pDocument,
                                        IE_Exp ** ppie);

  };

class ABI_EXPORT IE_Exp_PDF : public IE_Exp
  {
  public:
    IE_Exp_PDF(PD_Document * pDocument);
    virtual ~IE_Exp_PDF();

    int current_file_size();

    void write_document(UT_Vector document);
    void write_prolog();
    void write_trailer();
    int addfont(UT_String name, UT_String style);

    void add_to_buffer(const char * sz, UT_uint32 length);
    void add_to_buffer(const char * sz);

  protected:
    virtual UT_Error	_writeDocument(void);

    int pdf_start_object();
    void pdf_end_object();
    void flate_open_stream();
    void flate_close_stream();
    UT_Vector getfonts();

    void write_page(int page);
    void pdf_start_stream();
    void set_font(int typeface, float size);
    void set_color(float *rgb);
    void write_text(render_t *r);
    void set_pos(float x,float y);
    void write_resources(int  page);

    void write_string(UT_Byte *s, int compress);
    void flate_puts(const char *s);
    void flate_write(UT_Byte *buf,int length);

  private:

    s_PDF_Listener *	m_pListener;

    int	pdf_stream_length;
    int	pdf_stream_start;
    int	pdf_object_type;
    int	m_num_objects;
    int   m_alloc_objects;

    UT_Vector m_fonts;
    UT_Vector m_font_objects;
    UT_Vector m_objects;

    int   m_num_pages;
    int   m_info_object;
    int   m_pages_object;
    int   m_root_object;
    int compressor_active;

    UT_ByteBuf m_file_buffer;

    z_stream		compressor;
    UT_Byte		comp_buffer[8192];

    md5_byte_t	m_file_id[16];

    int	render_typeface;
    float	render_size,
    render_rgb[3],
    render_x,
    render_y,
    render_startx,
    render_spacing;

    UT_Vector m_pages;	 //(of page_t 's)

  }
;



#endif /* IE_EXP_PDF_H */
