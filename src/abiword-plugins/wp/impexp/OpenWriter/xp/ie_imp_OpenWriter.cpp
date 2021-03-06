/* AbiSource Program Utilities
 * Copyright (C) 2002 Dom Lachowicz <cinamod@hotmail.com>
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

#include <gsf/gsf-input-stdio.h>
#include <gsf/gsf-infile.h>
#include <gsf/gsf-infile-zip.h>

#include <locale.h>

#include "ie_impexp_OpenWriter.h"
#include "ie_impGraphic.h"
#include "fg_Graphic.h"
#include "fg_GraphicRaster.h"

#include "pd_Document.h"

// abiword stuff
#include "ut_xml.h"
#include "ut_misc.h"
#include "ut_string.h"
#include "ut_string_class.h"
#include "ut_bytebuf.h"
#include "ut_hash.h"
#include "ut_vector.h"
#include "ut_stack.h"

/*****************************************************************************/
/*****************************************************************************/

/*!
 * Class used to import OpenWriter documents
 */
class ABI_EXPORT IE_Imp_OpenWriter : public IE_Imp
{
public:
  IE_Imp_OpenWriter (PD_Document * pDocument);
  virtual ~IE_Imp_OpenWriter ();
  virtual UT_Error importFile(const char * szFilename);

  PD_Document * getDocument () const;

  GsfInfile * getOO () const { return m_oo; }

private:

  UT_Error _handleMetaStream ();
  UT_Error _handleSettingsStream ();
  UT_Error _handleStylesStream ();
  UT_Error _handleContentStream ();

  GsfInfile * m_oo;
};

/*****************************************************************************/
/*****************************************************************************/

IE_Imp_OpenWriter_Sniffer::IE_Imp_OpenWriter_Sniffer () :
  IE_ImpSniffer("OpenWriter::SXW")
{
}

IE_Imp_OpenWriter_Sniffer::~IE_Imp_OpenWriter_Sniffer ()
{
}

/*!
 * Recognize the well-known suffixes, if any
 */
UT_Confidence_t IE_Imp_OpenWriter_Sniffer::recognizeSuffix (const char * szSuffix)
{
  if (!UT_stricmp(szSuffix, ".sxw"))
    return UT_CONFIDENCE_PERFECT;
  return UT_CONFIDENCE_ZILCH;
}
  
/*!
 * Recognize the contents as best we can
 */
UT_Confidence_t IE_Imp_OpenWriter_Sniffer::recognizeContents (const char * szBuf, 
							      UT_uint32 iNumbytes)
{
  // BOGUS - will identify any zip file, also contains null characters
  static const char * magic = "PK     ";
  UT_uint32 magic_len = strlen ( magic );
  
  if (iNumbytes < magic_len)
    return UT_CONFIDENCE_ZILCH;
  
  if ( !strncmp (szBuf, magic, magic_len) )
    return UT_CONFIDENCE_SOSO;
  return UT_CONFIDENCE_ZILCH;
}

/*!
 * Construct an importer for ourselves
 */
UT_Error IE_Imp_OpenWriter_Sniffer::constructImporter (PD_Document * pDocument,
						       IE_Imp ** ppie)
{
  IE_Imp_OpenWriter * p = new IE_Imp_OpenWriter(pDocument);
  *ppie = p;
  return UT_OK;
}

/*!
 * Get the dialog labels
 */
bool IE_Imp_OpenWriter_Sniffer::getDlgLabels (const char ** szDesc,
					      const char ** szSuffixList,
					      IEFileType * ft)
{
  *szDesc = "OpenOffice Writer (.sxw)";
  *szSuffixList = "*.sxw";
  *ft = getFileType();
  return true;
}

/*****************************************************************************/
/*****************************************************************************/

/*!
 * Create a new OpenWriter importer object
 */
IE_Imp_OpenWriter::IE_Imp_OpenWriter (PD_Document * pDocument)
  : IE_Imp (pDocument), m_oo (0)
{
}

/*!
 * Destroy an OpenWriter importer object
 */
IE_Imp_OpenWriter::~IE_Imp_OpenWriter ()
{
  if (m_oo)
    g_object_unref (G_OBJECT(m_oo));
}

/*!
 * Import the given file
 */
UT_Error IE_Imp_OpenWriter::importFile(const char * szFilename)
{
  GsfInput * oo_src = gsf_input_stdio_new (szFilename, NULL);
  
  if (oo_src == NULL)
    return UT_ERROR;
  
  m_oo = gsf_infile_zip_new (oo_src, NULL);
  g_object_unref (G_OBJECT (oo_src));

  if (m_oo == NULL)
    return UT_ERROR;
  
  UT_Error err = UT_OK;

  if ( UT_OK != (err = _handleMetaStream ()))
    return err;
  if ( UT_OK != (err = _handleStylesStream ()))
    return err;
  if ( UT_OK != (err = _handleStylesStream ()))
    return err;
  if ( UT_OK != (err = _handleContentStream ()))
    return err;
    
  return UT_OK;
}

/*!
 *
 */
PD_Document * IE_Imp_OpenWriter::getDocument () const
{
  return getDoc ();
}

/*****************************************************************************/
/*****************************************************************************/

/*!
 * Baseclass for all OpenWriter listeners, basically a shim class
 * to expose a GetDocument() and a GetImporter() method
 */
class ABI_EXPORT OpenWriter_Stream_Listener : public virtual UT_XML::Listener
{
private:
  IE_Imp_OpenWriter * m_pImporter;
  
protected:
  OpenWriter_Stream_Listener ( IE_Imp_OpenWriter * importer )
    : m_pImporter ( importer )
  {
  }

  inline IE_Imp_OpenWriter * getImporter () const { return m_pImporter; }
  inline PD_Document * getDocument() const { return m_pImporter->getDocument(); }
  
public:
  
  virtual ~OpenWriter_Stream_Listener ()
  {
  }
};

/*****************************************************************************/
/*****************************************************************************/

static UT_Error loadStream ( GsfInfile * oo,
			     const char * stream,
			     UT_ByteBuf & buf )
{
  guint8 const *data = NULL;
  size_t len = 0;

  buf.truncate (0);
  GsfInput * input = gsf_infile_child_by_name(oo, stream);

  if (!input)
    return UT_ERROR;

  if (gsf_input_size (input) > 0) {
    while ((len = gsf_input_remaining (input)) > 0) {
      if (NULL == (data = gsf_input_read (input, len, NULL))) {
	return UT_ERROR;
      }
       buf.append ((const UT_Byte *)data, len);
    }
  }
    
  return UT_OK;
}

/*!
 * Static utility method to read a file/stream embedded inside of the
 * zipfile into an xml parser
 */
static UT_Error parseStream ( GsfInfile * oo, 
			      const char * stream,
			      UT_XML & parser )
{
  guint8 const *data = NULL;
  size_t len = 0;

  GsfInput * input = gsf_infile_child_by_name(oo, stream);

  if (!input)
    return UT_ERROR;

  if (gsf_input_size (input) > 0) {
    while ((len = gsf_input_remaining (input)) > 0) {
      if (NULL == (data = gsf_input_read (input, len, NULL))) {
	return UT_ERROR;
      }
      parser.parse ((const char *)data, len);
    }
  }
    
  return UT_OK;
}

/*!
 * Handle the stream @stream using the listener @listener.
 * Tries to abstract away how we're actually going to handle
 * how we read the stream, so that the underlying implementation
 * can easily adapt or change
 */
static UT_Error handleStream ( GsfInfile * oo,
			       const char * stream,
			       OpenWriter_Stream_Listener & listener )
{
  UT_XML reader;
  reader.setListener ( &listener );
  return parseStream (oo, stream, reader);
}

/*****************************************************************************/
/*****************************************************************************/

/*!
 * Class to handle meta-streams
 */
class ABI_EXPORT OpenWriter_MetaStream_Listener : public OpenWriter_Stream_Listener
{
public:
  OpenWriter_MetaStream_Listener ( IE_Imp_OpenWriter * importer )
    : OpenWriter_Stream_Listener ( importer )
  {
    UT_UTF8String prop_str ("OpenWriter::SXW");
    getDocument()->setMetaDataProp(PD_META_KEY_FORMAT, prop_str);
  }
  
  virtual ~OpenWriter_MetaStream_Listener ()
  {
  }
  
  virtual void startElement (const XML_Char * name, const XML_Char ** atts) 
  {
    mCharData.clear ();
    mAttrib.clear ();
    
    if (!UT_strcmp (name, "meta:user-defined"))
	{
	  const XML_Char * attrib = UT_getAttribute ("meta:name", atts);
	  if (attrib != NULL)
	    mAttrib = attrib;
	}
  }
  
  virtual void endElement (const XML_Char * name)
  {
    if (mCharData.size()) {
      if (!UT_strcmp (name, "dc:language"))
	{
	  getDocument()->setMetaDataProp (PD_META_KEY_LANGUAGE, 
					  mCharData);
	}
      else if (!UT_strcmp (name, "dc:date"))
	{
	  getDocument()->setMetaDataProp (PD_META_KEY_DATE, 
					  mCharData);
	}
      else if (!UT_strcmp (name, "meta:user-defined"))
	{
	  if (mAttrib.size())
	    getDocument()->setMetaDataProp (mAttrib.utf8_str(), 
					    mCharData);
	}
    }
    mCharData.clear ();
    mAttrib.clear ();
  }
  
  virtual void charData (const XML_Char * buffer, int length)
  {
    if (buffer && length) {
      UT_String buf(buffer, length);
      mCharData += buf.c_str();
    }
  }
  
private:

  UT_UTF8String mCharData;
  UT_UTF8String mAttrib;
};

/*!
 * Handle the meta-stream
 */
UT_Error IE_Imp_OpenWriter::_handleMetaStream ()
{
  OpenWriter_MetaStream_Listener listener ( this );
  return handleStream (m_oo, "meta.xml", listener);
}

/*****************************************************************************/
/*****************************************************************************/

/*!
 * Class to handle the settings stream
 */
class ABI_EXPORT OpenWriter_SettingsStream_Listener : public OpenWriter_Stream_Listener
{
public:
  OpenWriter_SettingsStream_Listener ( IE_Imp_OpenWriter * importer )
    : OpenWriter_Stream_Listener ( importer )
  {
  }

  virtual ~OpenWriter_SettingsStream_Listener ()
  {
  }

  virtual void startElement (const XML_Char * name, const XML_Char ** atts) 
  {
  }

  virtual void endElement (const XML_Char * name)
  {
  }

  virtual void charData (const XML_Char * buffer, int length)
  {
  }

private:
};

/*!
 * Handle the setting-stream
 */
UT_Error IE_Imp_OpenWriter::_handleSettingsStream ()
{
  OpenWriter_SettingsStream_Listener listener ( this );
  return handleStream (m_oo, "settings.xml", listener);
}

/*****************************************************************************/
/*****************************************************************************/

/*!
 * Class to handle the styles stream
 */
class ABI_EXPORT OpenWriter_StylesStream_Listener : public OpenWriter_Stream_Listener
{
public:
  OpenWriter_StylesStream_Listener ( IE_Imp_OpenWriter * importer )
    : OpenWriter_Stream_Listener ( importer )
  {
  }
  
  virtual ~OpenWriter_StylesStream_Listener ()
  {
  }
  
  virtual void startElement (const XML_Char * name, const XML_Char ** atts) 
  {
  }
  
  virtual void endElement (const XML_Char * name)
  {
  }
  
  virtual void charData (const XML_Char * buffer, int length)
  {
  }

private:
};

/*!
 * Handle the styles-stream
 */
UT_Error IE_Imp_OpenWriter::_handleStylesStream ()
{
  OpenWriter_StylesStream_Listener listener ( this );
  return handleStream (m_oo, "styles.xml", listener);
}

/*****************************************************************************/
/*****************************************************************************/

/*!
 * Class to handle the content stream
 */
class ABI_EXPORT OpenWriter_ContentStream_Listener : public OpenWriter_Stream_Listener
{
private:
  UT_UCS4String m_charData;
  bool m_bAcceptingText;
  UT_StringPtrMap m_styleBucket;

  UT_UTF8String m_curStyleName;

  UT_Vector		m_vecInlineFmt;
  UT_Stack		m_stackFmtStartIndex;

  UT_uint32 m_imgCnt;

  int m_row;
  int m_col;
  int m_cel;

public:
  OpenWriter_ContentStream_Listener ( IE_Imp_OpenWriter * importer )
    : OpenWriter_Stream_Listener ( importer ), m_bAcceptingText(false), m_imgCnt(0)
  {
    m_row = 0;
    m_col = 0;
    m_cel = 0;
  }

  virtual ~OpenWriter_ContentStream_Listener ()
  {
    UT_HASH_PURGEDATA(XML_Char *, &m_styleBucket, free);
  }

  virtual void startElement (const XML_Char * name, const XML_Char ** atts) 
  {
    if (!UT_strcmp(name, "office:body"))
      {
	getDocument()->appendStrux(PTX_Section, NULL);
      }
    else if (!UT_strcmp(name, "text:p" ))
      {
	const XML_Char * oo_sty = UT_getAttribute ("text:style-name", atts);
	const XML_Char * abi_sty = _mapStyle(oo_sty);

	const XML_Char * props[3];
	props[0] = "props";
	props[1] = abi_sty;
	props[2] = 0;

        getDocument()->appendStrux(PTX_Block, (const XML_Char **)props);
	m_bAcceptingText = true;
      }
    else if (!UT_strcmp(name, "text:span"))
      {
	_flush ();

	const XML_Char * oo_sty = UT_getAttribute ("text:style-name", atts);
	const XML_Char * abi_sty = _mapStyle(oo_sty);

	const XML_Char * props[3];
	props[0] = "props";
	props[1] = abi_sty;
	props[2] = 0;
	
	_pushInlineFmt(props);
	getDocument()->appendFmt(&m_vecInlineFmt);
      }
    else if (!UT_strcmp(name, "text:line-break"))
      {
	m_charData += UCS_LF;
	_flush ();
      }
    else if (!UT_strcmp(name, "style:style"))
      {
	m_curStyleName.clear ();
	m_curStyleName = UT_getAttribute ("style:name", atts);
      }
    else if (!UT_strcmp(name, "style:properties"))
      {
	_defineSimpleStyle (atts);
      }
    else if (!UT_strcmp(name, "text:a"))
      {
	const XML_Char * xlink_atts[3];
	xlink_atts[0] = "xlink:href";
	xlink_atts[1] = UT_getAttribute("xlink:href", atts);
	xlink_atts[2] = 0;
	getDocument()->appendObject(PTO_Hyperlink, xlink_atts);
      }
    else if (!UT_strcmp(name, "text:bookmark"))
    {
      _flush ();
      const XML_Char * name = UT_getAttribute ("text:name", atts);
      _insertBookmark (name, "start");
      _insertBookmark (name, "end");
    }
    else if (!UT_strcmp(name, "draw:image"))
      {
	_flush ();
	_insertImage (atts);
      }
    else if (!UT_strcmp(name, "table:table"))
      {
	_openTable (atts);
      }
    else if (!UT_strcmp(name, "table:table-column"))
      {
	_openColumn (atts);
      }
    else if (!UT_strcmp(name, "table:table-row"))
      {
	_openRow (atts);
      }
    else if (!UT_strcmp(name, "table:table-cell"))
      {
	_openCell (atts);
      }
    else if (!UT_strcmp(name, "text:date") ||
	     !UT_strcmp(name, "text:time") || 
	     !UT_strcmp(name, "text:page-number") ||
	     !UT_strcmp(name, "text:page-count") || 
	     !UT_strcmp(name, "text:file-name") ||
	     !UT_strcmp(name, "text:paragraph-count") ||
	     !UT_strcmp(name, "text:word-count") ||
	     !UT_strcmp(name, "text:character-count") ||
	     !UT_strcmp(name, "text:initial-creator") ||
	     !UT_strcmp(name, "text:author-name") ||
	     !UT_strcmp(name, "text:description") ||
	     !UT_strcmp(name, "text:keywords") ||
	     !UT_strcmp(name, "text:subject") ||
	     !UT_strcmp(name, "text:title"))
    {
      _flush ();

      const XML_Char * type = "";
      if(!UT_strcmp(name, "text:date"))
	type = "date_ddmmyy";
      else if(!UT_strcmp(name, "text:time"))
	type = "time";
      else if(!UT_strcmp(name, "text:page-number"))
	type = "page_number";
      else if(!UT_strcmp(name, "text:page-count"))
	type = "page_count";
      else if(!UT_strcmp(name, "text:file-name"))
	type = "file_name";
      else if(!UT_strcmp(name, "text:paragraph-count"))
	type = "para_count";
      else if(!UT_strcmp(name, "text:word-count"))
	type = "word_count";
      else if(!UT_strcmp(name, "text:character-count"))
	type = "char_count";
      else if(!UT_strcmp(name, "text:initial-creator") || !UT_strcmp(name, "text:author-name"))
	type = "meta_creator";
      else if(!UT_strcmp(name, "text:description"))
	type = "meta_description";
      else if(!UT_strcmp(name, "text:keywords"))
	type = "meta_keywords";
      else if(!UT_strcmp(name, "text:subject"))
	type = "meta_subject";
      else if(!UT_strcmp(name, "text:title"))
	type = "meta_title";

      const XML_Char *field_fmt[3];
      field_fmt[0] = "type";
      field_fmt[1] = type;
      field_fmt[2] = 0;
      getDocument()->appendObject(PTO_Field, (const XML_Char**)field_fmt);
      m_bAcceptingText = false;
    }
  }

  virtual void endElement (const XML_Char * name)
  {
    if (!UT_strcmp(name, "text:p" ))
      {
	_flush ();
	m_bAcceptingText= false;
      }
    else if (!UT_strcmp(name, "text:span"))
      {
	_flush ();
	_popInlineFmt();
	getDocument()->appendFmt(&m_vecInlineFmt);
      }
    else if (!UT_strcmp(name, "text:a"))
      {
	_flush ();
	getDocument()->appendObject(PTO_Hyperlink, NULL);
      }
    else if (!UT_strcmp(name, "table:table"))
      {
	_closeTable ();
      }
    else if (!UT_strcmp(name, "table:table-column"))
      {
	_closeColumn ();
      }
    else if (!UT_strcmp(name, "table:table-row"))
      {
	_closeRow ();
      }
    else if (!UT_strcmp(name, "table:table-cell"))
      {
	_closeCell ();
      }
    else if (!UT_strcmp(name, "text:date") ||
	     !UT_strcmp(name, "text:time") || 
	     !UT_strcmp(name, "text:page-number") ||
	     !UT_strcmp(name, "text:page-count") || 
	     !UT_strcmp(name, "text:file-name") ||
	     !UT_strcmp(name, "text:paragraph-count") ||
	     !UT_strcmp(name, "text:word-count") ||
	     !UT_strcmp(name, "text:character-count") ||
	     !UT_strcmp(name, "text:initial-creator") ||
	     !UT_strcmp(name, "text:author-name") ||
	     !UT_strcmp(name, "text:description") ||
	     !UT_strcmp(name, "text:keywords") ||
	     !UT_strcmp(name, "text:subject") ||
	     !UT_strcmp(name, "text:title"))
    {
      m_bAcceptingText = true;
    }
  }

  virtual void charData (const XML_Char * buffer, int length)
  {
    if (buffer && length && m_bAcceptingText)
      {
	UT_UCS4String ucs4 (buffer, length, true);
	m_charData += ucs4;
      }
  }

private:

  void _insertImage (const XML_Char ** atts)
  {
    UT_Error error		= UT_OK;
    const XML_Char * width  = UT_getAttribute ("svg:width", atts);
    const XML_Char * height = UT_getAttribute ("svg:height", atts);
    const XML_Char * href   = UT_getAttribute ("xlink:href", atts);

    m_imgCnt++;

    UT_ByteBuf img_buf;

    GsfInfile * pictures_dir = GSF_INFILE(gsf_infile_child_by_name(getImporter()->getOO(), "Pictures"));
    printf("DOM: w: %s; h: %s; href: %s\n", width, height, href+1);

    // 10 == strlen("#Pictures/");
    error = loadStream(pictures_dir, href+10, img_buf);
    g_object_unref (G_OBJECT (pictures_dir));

    if (error != UT_OK) {
      printf ("DOM: could not load image from stream\n");
      return;
    }

    const char * mimetype 	= UT_strdup ("image/png");
    IE_ImpGraphic * importer	= 0;
    FG_Graphic* pFG		= 0;
    UT_ByteBuf * pictData = 0;
    
    UT_String propBuffer;
    UT_String propsName;
    
    error = IE_ImpGraphic::constructImporter (&img_buf, IEGFT_Unknown, &importer);
    
    if ((error != UT_OK) || !importer)
      {
	printf ("DOM: could not create importer\n");
	FREEP(mimetype);
	goto Cleanup;
      }

    error = importer->importGraphic(&img_buf, &pFG);
    if ((error != UT_OK) || !pFG)
      {
	// pictData is already freed in ~FG_Graphic
	printf ("DOM: could not import graphic\n");
	FREEP(mimetype);
	goto Cleanup;
      }

    // TODO: can we get back a vector graphic?
    pictData = static_cast<FG_GraphicRaster *>(pFG)->getRaster_PNG();
    
    if (!pictData)
      {
	// i don't think that this could ever happen, but...
	printf ("DOM: could not convert to PNG\n");
	FREEP(mimetype);
	error = UT_ERROR;
	goto Cleanup;
      }

    //
    // This next bit of code will set up our properties based on the image attributes
    //
    
    UT_String_sprintf(propBuffer, "width:%s; height:%s", width, height);    
    UT_String_sprintf(propsName, "image%d", m_imgCnt);

    const XML_Char* propsArray[5];
    propsArray[0] = (XML_Char *)"props";
    propsArray[1] = (XML_Char *)propBuffer.c_str();
    propsArray[2] = (XML_Char *)"dataid";
    propsArray[3] = (XML_Char *)propsName.c_str();
    propsArray[4] = 0;
    
    if (!getDocument()->appendObject (PTO_Image, propsArray))
      {
	printf ("DOM: could not append object\n");
	FREEP(mimetype);
	goto Cleanup;
      }
    
    if (!getDocument()->createDataItem(propsName.c_str(), false,
				       pictData, (void*)mimetype, NULL))
      {
	printf ("DOM: could not create data item\n");
	goto Cleanup;
      }
    
  Cleanup:
    DELETEP(importer);
  }

  void _insertBookmark (const XML_Char * name, const XML_Char * type)
    {
	const XML_Char* propsArray[5];
	propsArray[0] = (XML_Char *)"name";
	propsArray[1] = name;
	propsArray[2] = (XML_Char *)"type";
	propsArray[3] = type;
	propsArray[4] = 0;
	getDocument()->appendObject (PTO_Bookmark, propsArray);
    }

  void _flush ()
  {
    if (m_charData.size () > 0)
      {
	getDocument()->appendSpan (m_charData.ucs4_str(), m_charData.size ());
	m_charData.clear ();
      }	
  }

  void _openTable (const XML_Char ** props)
  {
    getDocument()->appendStrux(PTX_SectionTable,NULL);
  }

  void _openColumn (const XML_Char ** props)
  {
    m_col++;
  }

  void _openRow (const XML_Char ** props)
  {
    m_row++; m_cel = 0;
  }

  void _openCell (const XML_Char ** props)
  {
    UT_String attach;

    attach = UT_String_sprintf("left-attach: %d; top-attach: %d; right-attach: %d; bot-attach: %d", m_cel, m_row-1, m_cel+1, m_row);

    m_cel++;

    const XML_Char *cell_props[3];
    cell_props[0] = "props";
    cell_props[1] = attach.c_str();
    cell_props[2] = 0;
    
    getDocument()->appendStrux(PTX_SectionCell,cell_props);
  }

  void _closeTable ()
  {
    getDocument()->appendStrux(PTX_EndTable, NULL);
  }

  void _closeColumn ()
  {
    m_col--;
  }

  void _closeRow ()
  {
    m_col--;
  }

  void _closeCell ()
  {
    getDocument()->appendStrux(PTX_EndCell,NULL);
  }

  void _defineStyle (const XML_Char * name, const XML_Char * props)
  {
    m_styleBucket.insert ((const char *)name, UT_strdup((const char *)props));
  }
  
  void _defineSimpleStyle (const XML_Char **props)
  {
    if (!m_curStyleName.size() || !props)
      return;

    UT_String style_def;
    const XML_Char** p = props;   

    const XML_Char * val = NULL;

    val = UT_getAttribute ("fo:text-align", props);
    if (val) {
      if (!UT_strcmp(val, "end"))
	style_def += "text-align: right;";
      else if (!UT_strcmp(val, "center"))
	style_def += "text-align: center;";
      else if (!UT_strcmp(val, "justify"))
	style_def += "text-align: justify;";
      else
	style_def += "text-align: left;";
    }

    val = UT_getAttribute ("fo:font-weight", props);
    if(val) {
      if (!UT_strcmp(val, "bold"))
	style_def += "font-weight: bold;";
      else
	style_def += "font-weight: normal;";
    }
    
    val = UT_getAttribute("fo:font-style", props);
    if (val) {
      if (!UT_strcmp(val, "italic"))
	style_def += "font-style: italic;";
    }
    
    val = UT_getAttribute("fo:color", props);
    if (val) {
      style_def += UT_String_sprintf ("color: %s;", val);
    }

    val = UT_getAttribute ("style:text-background-color", props);
    if(val){
      style_def += UT_String_sprintf ("bgcolor: %s;", val);
    }
    
    val = UT_getAttribute("style:font-name", props);
    if(val){
	style_def += UT_String_sprintf ("font-face: %s;", val);
      }

    val = UT_getAttribute("fo:font-size", props);
    if(val){
      style_def += UT_String_sprintf ("font-size: %s;", val);
    }
    
    if (UT_getAttribute("fo:language", props) && UT_getAttribute("fo:country", props))
      {
	style_def += UT_String_sprintf ("lang: %s-%s;", UT_getAttribute("fo:language", props),
					UT_getAttribute("fo:country", props));
      }

    val = UT_getAttribute("style:text-position", props);
    if(val){
      style_def += "text-position: ";
      if (strstr(val, "sup"))
	style_def += "superscript;";
      else if (strstr(val, "sub"))
	style_def += "subscript;";
      else
	style_def += "normal;";
    }

    if (UT_getAttribute("style:text-underline", props) || UT_getAttribute("style:text-crossing-out", props))
      {
	const XML_Char * undr = UT_getAttribute("style:text-underline", props);
	const XML_Char * strk = UT_getAttribute("style:text-crossing-out", props);

	style_def += "text-decoration: ";

	if(undr) {
	  if (UT_strcmp(undr, "none") != 0)
	    style_def += "underline";
	}

	if (undr && strk)
	  style_def += ",";

	if(strk) {
	  if (UT_strcmp(strk, "none") != 0)
	    style_def += "line-through";
	}

	style_def += ";";
      }

    val = UT_getAttribute ("fo:margin-left", props);
    if(val) {
      style_def += UT_String_sprintf ("margin-left: %s;", val);
    }

    val = UT_getAttribute ("fo:margin-right", props);
    if(val) {
      style_def += UT_String_sprintf ("margin-right: %s;", val);
    }

    val = UT_getAttribute ("style:line-height-at-least", props);
    if (val) {
      style_def += UT_String_sprintf ("line-height: %s+;", val);
    }

    val = UT_getAttribute ("fo:line-height", props);
    if (val) {
      if (strstr(val, "%") != NULL) {
	int spacing;

	sscanf (val, "%d%%", &spacing);	
	const char * old_loc = setlocale(LC_NUMERIC, "C");
	style_def += UT_String_sprintf ("line-height: %f;", (double)spacing/100.);
	setlocale (LC_NUMERIC, old_loc);
      }
      else
	style_def += UT_String_sprintf ("line-height: %s;", val);
    }

    val = UT_getAttribute("fo:keep-with-next", props);
    if (val) {
      style_def += UT_String_sprintf ("keep-with-next: %s;", !UT_strcmp(val, "true") ? "yes" : "no");
    }

    val = UT_getAttribute("style:break-inside", props);
    if (val) {
      style_def += UT_String_sprintf ("keep-together: %s;", !UT_strcmp(val, "avoid") ? "yes" : "no" );
    }

    val = UT_getAttribute("fo:widows", props);
    if (val) {
      int widows = 0;
      sscanf(val, "%d", &widows);
      style_def += UT_String_sprintf ("widows: %d", widows);
    }

    val = UT_getAttribute("fo:orphans", props);
    if (val) {
      int orphans = 0;
      sscanf (val, "%d", &orphans);
      style_def += UT_String_sprintf ("orphans: %d", orphans);
    }

    if (style_def.size()) {
      style_def [style_def.size()-1] = 0; 
      _defineStyle (m_curStyleName.utf8_str(), style_def.c_str());
    }
  }

  const XML_Char* _mapStyle(const XML_Char * name) const
  {
    const XML_Char * sty = (const XML_Char*)m_styleBucket.pick((const char *)name);
    if (NULL == sty)
      return "";
    return sty;
  }

  bool _pushInlineFmt(const XML_Char ** atts)
  {
    UT_uint32 start = m_vecInlineFmt.getItemCount()+1;
    UT_uint32 k;
    
    for (k=0; (atts[k]); k++)
      {
	XML_Char * p;
	if (!UT_XML_cloneString(p,atts[k]))
	  return false;
	if (m_vecInlineFmt.addItem(p)!=0)
	  return false;
      }
    if (!m_stackFmtStartIndex.push((void*)start))
      return false;
    return true;
  }
  
  void _popInlineFmt(void)
  {
    UT_uint32 start;
    if (!m_stackFmtStartIndex.pop((void **)&start))
      return;
    UT_uint32 k;
    UT_uint32 end = m_vecInlineFmt.getItemCount();
    for (k=end; k>=start; k--)
      {
	const XML_Char * p = (const XML_Char *)m_vecInlineFmt.getNthItem(k-1);
	m_vecInlineFmt.deleteNthItem(k-1);
	if (p)
	  free((void *)p);
      }
  }
  
};

/*!
 * Handle the content-stream
 */
UT_Error IE_Imp_OpenWriter::_handleContentStream ()
{
  OpenWriter_ContentStream_Listener listener ( this );
  return handleStream (m_oo, "content.xml", listener);
}
