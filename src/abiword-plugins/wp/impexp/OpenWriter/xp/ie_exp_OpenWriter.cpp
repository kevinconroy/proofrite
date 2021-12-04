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

#include <locale.h>
#include <gsf/gsf-output-stdio.h>
#include <gsf/gsf-outfile.h>
#include <gsf/gsf-outfile-zip.h>

#include "ie_impexp_OpenWriter.h"

#include "fd_Field.h"
#include "fl_AutoNum.h"
#include "fp_PageSize.h"

#include "px_ChangeRecord.h"
#include "px_CR_Object.h"
#include "px_CR_Span.h"
#include "px_CR_Strux.h"
#include "pd_Document.h"

// abiword stuff
#include "ut_misc.h"
#include "ut_string.h"
#include "ut_string_class.h"
#include "ut_bytebuf.h"
#include "ut_hash.h"
#include "ut_vector.h"
#include "ut_stack.h"
#include "ut_assert.h"

/*****************************************************************************/
/*****************************************************************************/

class ABI_EXPORT IE_Exp_OpenWriter : public IE_Exp
{
public:
  IE_Exp_OpenWriter(PD_Document * pDocument);
  virtual ~IE_Exp_OpenWriter();

protected:
  virtual UT_Error	_writeDocument(void);
  virtual bool		_openFile(const char * szFilename);
  virtual bool		_closeFile(void);
  
private:
  GsfOutfile * m_oo;	
};

/*****************************************************************************/
/*****************************************************************************/

IE_Exp_OpenWriter_Sniffer::IE_Exp_OpenWriter_Sniffer()
  : IE_ExpSniffer ("OpenWriter::SXW")
{
}

IE_Exp_OpenWriter_Sniffer::~IE_Exp_OpenWriter_Sniffer()
{
}

/*!
 * Recognize this suffix
 */
bool IE_Exp_OpenWriter_Sniffer::recognizeSuffix(const char * szSuffix)
{
  return (!UT_stricmp(szSuffix,".sxw"));
}

/*!
 * Construct an importer for us
 */
UT_Error IE_Exp_OpenWriter_Sniffer::constructExporter(PD_Document * pDocument,
						      IE_Exp ** ppie)
{
  *ppie = new IE_Exp_OpenWriter (pDocument);
  return UT_OK;
}

/*!
 * Get the dialog labels
 */
bool IE_Exp_OpenWriter_Sniffer::getDlgLabels(const char ** pszDesc,
					     const char ** pszSuffixList,
					     IEFileType * ft)
{
  *pszDesc = "OpenOffice Writer (.sxw)";
  *pszSuffixList = "*.sxw";
  *ft = getFileType();
  return true;
}

/*****************************************************************************/
/*****************************************************************************/

/*!
 * Write out a message to the stream. Message is an array of content
 */
static void writeToStream (GsfOutput * stream, const char * const message [], size_t nElements)
{
    for(UT_uint32 k = 0; k < nElements; k++)
      gsf_output_write(stream, strlen(message[k]), (const guint8*)message[k]);
}


static void writeUTF8String (GsfOutput * output, const UT_UTF8String & str)
{
  gsf_output_write (output, str.byteLength(), (const guint8*)str.utf8_str());
}

/*****************************************************************************/
/*****************************************************************************/

/*!
 * This class will iterate through the AbiWord document and capture
 * any style-related information and turn it into OOo styles.
 *
 * This includes: named styles (<style><s></s></style>
 *                indirect styles (props="foo:bar;")
 *
 * This class will then write out the OOo styles.xml file. Later on,
 * you can query for an indirect style name based on abiword props.
 * You can also ask it to write out the style section inside of content.xml
 */
class OO_StyleAccumulator : public PL_Listener
{
public:

  OO_StyleAccumulator (PD_Document * pDocument,
		  IE_Exp_OpenWriter * pie)
    : PL_Listener (), m_doc(pDocument), m_pie(pie)
  {
  }

  virtual ~OO_StyleAccumulator()
  {
  }
  
  virtual bool	populate(PL_StruxFmtHandle sfh,
			 const PX_ChangeRecord * pcr)
  {
    UT_ASSERT_NOT_REACHED();
    return true;
  }
  
  virtual bool	populateStrux(PL_StruxDocHandle sdh,
			      const PX_ChangeRecord * pcr,
			      PL_StruxFmtHandle * psfh)
  {
    UT_ASSERT_NOT_REACHED();
    return true;
  }

  virtual bool	change(PL_StruxFmtHandle sfh,
		       const PX_ChangeRecord * pcr)
  {
    UT_ASSERT_NOT_REACHED();
    return true;
  }
  
  virtual bool	insertStrux(PL_StruxFmtHandle sfh,
			    const PX_ChangeRecord * pcr,
			    PL_StruxDocHandle sdh,
			    PL_ListenerId lid,
			    void (* pfnBindHandles)(PL_StruxDocHandle sdhNew,
						    PL_ListenerId lid,
						    PL_StruxFmtHandle sfhNew))
  {
    UT_ASSERT_NOT_REACHED();
    return true;
  }
  
  virtual bool	signal(UT_uint32 iSignal)
  {
    UT_ASSERT_NOT_REACHED();
    return true;
  }

  bool writeStyles(GsfOutfile * oo)
  {
    GsfOutput * styleStream = gsf_outfile_new_child (oo, "styles.xml", FALSE);

    static const char * const preamble [] = 
      {
	// TODO!

	"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n",
	"<!DOCTYPE office:document-styles PUBLIC \"-//OpenOffice.org//DTD OfficeDocument 1.0//EN\" \"office.dtd\">\n",
	"<office:document-styles xmlns:office=\"http://openoffice.org/2000/office\" xmlns:style=\"http://openoffice.org/2000/style\" xmlns:text=\"http://openoffice.org/2000/text\" xmlns:table=\"http://openoffice.org/2000/table\" xmlns:draw=\"http://openoffice.org/2000/drawing\" xmlns:fo=\"http://www.w3.org/1999/XSL/Format\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns:number=\"http://openoffice.org/2000/datastyle\" xmlns:svg=\"http://www.w3.org/2000/svg\" xmlns:chart=\"http://openoffice.org/2000/chart\" xmlns:dr3d=\"http://openoffice.org/2000/dr3d\" xmlns:math=\"http://www.w3.org/1998/Math/MathML\" xmlns:form=\"http://openoffice.org/2000/form\" xmlns:script=\"http://openoffice.org/2000/script\" office:version=\"1.0\">\n",
	"<office:font-decls>\n",
	"<style:font-decl style:name=\"Arial Unicode MS\" fo:font-family=\"'Arial Unicode MS'\" style:font-pitch=\"variable\"/>\n",
	"<style:font-decl style:name=\"HG Mincho Light J\" fo:font-family=\"'HG Mincho Light J'\" style:font-pitch=\"variable\"/>\n",
	"<style:font-decl style:name=\"Nimbus Roman No9 L\" fo:font-family=\"'Nimbus Roman No9 L'\" style:font-family-generic=\"roman\" style:font-pitch=\"variable\"/>\n",
	"</office:font-decls>\n",
	"<office:styles>\n",
	"<style:default-style style:family=\"graphics\">\n",
	"<style:properties draw:start-line-spacing-horizontal=\"0.283cm\" draw:start-line-spacing-vertical=\"0.283cm\" draw:end-line-spacing-horizontal=\"0.283cm\" draw:end-line-spacing-vertical=\"0.283cm\" fo:color=\"#000000\" style:font-name=\"Nimbus Roman No9 L\" fo:font-size=\"12pt\" fo:language=\"en\" fo:country=\"US\" style:font-name-asian=\"HG Mincho Light J\" style:font-size-asian=\"12pt\" style:language-asian=\"none\" style:country-asian=\"none\" style:font-name-complex=\"Arial Unicode MS\" style:font-size-complex=\"12pt\" style:language-complex=\"none\" style:country-complex=\"none\" style:text-autospace=\"ideograph-alpha\" style:punctuation-wrap=\"simple\" style:line-break=\"strict\">\n",
        "<style:tab-stops/>\n",
	"</style:properties>\n",
	"</style:default-style>\n",
	"<style:default-style style:family=\"paragraph\">\n",
	"<style:properties fo:color=\"#000000\" style:font-name=\"Nimbus Roman No9 L\" fo:font-size=\"12pt\" fo:language=\"en\" fo:country=\"US\" style:font-name-asian=\"HG Mincho Light J\" style:font-size-asian=\"12pt\" style:language-asian=\"none\" style:country-asian=\"none\" style:font-name-complex=\"Arial Unicode MS\" style:font-size-complex=\"12pt\" style:language-complex=\"none\" style:country-complex=\"none\" fo:hyphenate=\"false\" fo:hyphenation-remain-char-count=\"2\" fo:hyphenation-push-char-count=\"2\" fo:hyphenation-ladder-count=\"no-limit\" style:text-autospace=\"ideograph-alpha\" style:punctuation-wrap=\"hanging\" style:line-break=\"strict\" style:tab-stop-distance=\"2.205cm\"/>\n",
	"</style:default-style>\n",
	"<style:style style:name=\"Standard\" style:family=\"paragraph\" style:class=\"text\"/>\n",
	"<text:outline-style>\n",
	"<text:outline-level-style text:level=\"1\" style:num-format=\"\"/>\n",
	"<text:outline-level-style text:level=\"2\" style:num-format=\"\"/>\n",
	"<text:outline-level-style text:level=\"3\" style:num-format=\"\"/>\n",
	"<text:outline-level-style text:level=\"4\" style:num-format=\"\"/>\n",
	"<text:outline-level-style text:level=\"5\" style:num-format=\"\"/>\n",
	"<text:outline-level-style text:level=\"6\" style:num-format=\"\"/>\n",
	"<text:outline-level-style text:level=\"7\" style:num-format=\"\"/>\n",
	"<text:outline-level-style text:level=\"8\" style:num-format=\"\"/>\n",
	"<text:outline-level-style text:level=\"9\" style:num-format=\"\"/>\n",
	"<text:outline-level-style text:level=\"10\" style:num-format=\"\"/>\n",
	"</text:outline-style>\n",
	"<text:footnotes-configuration style:num-format=\"1\" text:start-value=\"0\" text:footnotes-position=\"page\" text:start-numbering-at=\"document\"/>\n",
	"<text:endnotes-configuration style:num-format=\"i\" text:start-value=\"0\"/>\n",
	"<text:linenumbering-configuration text:number-lines=\"false\" text:offset=\"0.499cm\" style:num-format=\"1\" text:number-position=\"left\" text:increment=\"5\"/>\n",
	"</office:styles>\n",
	"<office:automatic-styles>\n",
	"<style:page-master style:name=\"pm1\">\n",
	"<style:properties fo:page-width=\"21.59cm\" fo:page-height=\"27.94cm\" style:num-format=\"1\" style:print-orientation=\"portrait\" fo:margin-top=\"2.54cm\" fo:margin-bottom=\"2.54cm\" fo:margin-left=\"3.175cm\" fo:margin-right=\"3.175cm\" style:footnote-max-height=\"0cm\">\n",
        "<style:footnote-sep style:width=\"0.018cm\" style:distance-before-sep=\"0.101cm\" style:distance-after-sep=\"0.101cm\" style:adjustment=\"left\" style:rel-width=\"25%\" style:color=\"#000000\"/>\n",
	"</style:properties>\n",
	"<style:header-style/>\n",
	"<style:footer-style/>\n",
	"</style:page-master>\n",
	"</office:automatic-styles>\n",
	"<office:master-styles>\n",
	"<style:master-page style:name=\"Standard\" style:page-master-name=\"pm1\"/>\n",
	"</office:master-styles>\n",
	"</office:document-styles>\n"
      };

    writeToStream(styleStream, preamble, NrElements(preamble));

    gsf_output_close(styleStream);
    g_object_unref(G_OBJECT(styleStream));

    return true;
  }

  void writeStylePreamble (GsfOutput * contents)
  {
    // TODO!

    static const char * const preamble [] = 
      {
	"<office:font-decls>\n",
	"<style:font-decl style:name=\"Arial Unicode MS\" fo:font-family=\"'Arial Unicode MS'\" style:font-pitch=\"variable\"/>\n",
	"<style:font-decl style:name=\"HG Mincho Light J\" fo:font-family=\"'HG Mincho Light J'\" style:font-pitch=\"variable\"/>\n",
	"<style:font-decl style:name=\"Nimbus Roman No9 L\" fo:font-family=\"'Nimbus Roman No9 L'\" style:font-family-generic=\"roman\" style:font-pitch=\"variable\"/>\n",
	"</office:font-decls>\n",
	"<office:automatic-styles/>\n"
      };

    writeToStream(contents, preamble, NrElements(preamble));
  }

  UT_String getParagraphStyle(PT_AttrPropIndex api)
  {
    // TODO!
    
    return "Standard";
  }

  UT_String getCharacterStyle(PT_AttrPropIndex api)
  {
    // TODO!

    return "Standard";
  }

private:
  PD_Document * m_doc;
  IE_Exp_OpenWriter * m_pie;
};

/*****************************************************************************/
/*****************************************************************************/

class OO_ContentWriter : public PL_Listener
{
public:

  OO_ContentWriter (PD_Document * pDocument,
		    IE_Exp_OpenWriter * pie,
		    OO_StyleAccumulator & acc,
		    GsfOutfile * oo)
    : PL_Listener (), m_doc(pDocument), m_pie(pie), m_acc(acc), m_contentStream(0), m_bInSpan(false), m_bInBlock(false)
  {
    m_contentStream = gsf_outfile_new_child (oo, "content.xml", FALSE);

    static const char * const preamble [] = 
      {
	"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n",
	"<!DOCTYPE office:document-content PUBLIC \"-//OpenOffice.org//DTD OfficeDocument 1.0//EN\" \"office.dtd\">\n",
	"<office:document-content xmlns:office=\"http://openoffice.org/2000/office\" xmlns:style=\"http://openoffice.org/2000/style\" xmlns:text=\"http://openoffice.org/2000/text\" xmlns:table=\"http://openoffice.org/2000/table\" xmlns:draw=\"http://openoffice.org/2000/drawing\" xmlns:fo=\"http://www.w3.org/1999/XSL/Format\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns:number=\"http://openoffice.org/2000/datastyle\" xmlns:svg=\"http://www.w3.org/2000/svg\" xmlns:chart=\"http://openoffice.org/2000/chart\" xmlns:dr3d=\"http://openoffice.org/2000/dr3d\" xmlns:math=\"http://www.w3.org/1998/Math/MathML\" xmlns:form=\"http://openoffice.org/2000/form\" xmlns:script=\"http://openoffice.org/2000/script\" office:class=\"text\" office:version=\"1.0\">\n",
	"<office:script/>\n"
      };

    writeToStream(m_contentStream, preamble, NrElements(preamble));

    m_acc.writeStylePreamble(m_contentStream);

    static const char * const midsection [] = 
      {
	"<office:body>\n",
	"<text:sequence-decls>\n",
	"<text:sequence-decl text:display-outline-level=\"0\" text:name=\"Illustration\"/>\n",
	"<text:sequence-decl text:display-outline-level=\"0\" text:name=\"Table\"/>\n",
	"<text:sequence-decl text:display-outline-level=\"0\" text:name=\"Text\"/>\n",
	"<text:sequence-decl text:display-outline-level=\"0\" text:name=\"Drawing\"/>\n",
	"</text:sequence-decls>\n"
      };

    writeToStream(m_contentStream, midsection, NrElements(midsection));
  }

  virtual ~OO_ContentWriter()
  {
    _closeBlock ();

    static const char * const postamble [] = 
      {
	  "</office:body>\n",
	  "</office:document-content>\n"
      };
    writeToStream(m_contentStream, postamble, NrElements(postamble));

    gsf_output_close(m_contentStream);
    g_object_unref(G_OBJECT(m_contentStream));
  }
  
  virtual bool populate(PL_StruxFmtHandle sfh,
			const PX_ChangeRecord * pcr)
  {
    switch (pcr->getType())
      {
      case PX_ChangeRecord::PXT_InsertSpan:
	{
	  const PX_ChangeRecord_Span * pcrs = static_cast<const PX_ChangeRecord_Span *> (pcr);
	  _openSpan(pcr->getIndexAP());
	  _outputData(m_doc->getPointer(pcrs->getBufIndex()),pcrs->getLength());
	}
      }

    return true;
  }
  
  virtual bool	populateStrux(PL_StruxDocHandle sdh,
			      const PX_ChangeRecord * pcr,
			      PL_StruxFmtHandle * psfh)
  {
    const PX_ChangeRecord_Strux * pcrx = static_cast<const PX_ChangeRecord_Strux *> (pcr);
    *psfh = 0;							// we don't need it.
    
    switch (pcrx->getStruxType())
      {
	case PTX_Block:
	  {
	    _closeSpan ();
	    _openBlock(pcr->getIndexAP());
	  }
      }

    return true;
  }

  virtual bool	change(PL_StruxFmtHandle sfh,
		       const PX_ChangeRecord * pcr)
  {
    UT_ASSERT_NOT_REACHED();
    return true;
  }
  
  virtual bool	insertStrux(PL_StruxFmtHandle sfh,
			    const PX_ChangeRecord * pcr,
			    PL_StruxDocHandle sdh,
			    PL_ListenerId lid,
			    void (* pfnBindHandles)(PL_StruxDocHandle sdhNew,
						    PL_ListenerId lid,
						    PL_StruxFmtHandle sfhNew))
  {
    UT_ASSERT_NOT_REACHED();
    return true;
  }
  
  virtual bool	signal(UT_uint32 iSignal)
  {
    UT_ASSERT_NOT_REACHED();
    return true;
  }

private:

  void _outputData(const UT_UCSChar * data, UT_uint32 length)
  {
    UT_UTF8String sBuf;
    const UT_UCSChar * pData;
    
    UT_ASSERT(sizeof(UT_Byte) == sizeof(char));
    
    for (pData=data; (pData<data+length); /**/)
      {
	switch (*pData)
	  {
	  case '<':
	    sBuf += "&lt;";
	    pData++;
	    break;
	    
	  case '>':
	    sBuf += "&gt;";
	    pData++;
	    break;
	    
	  case '&':
	    sBuf += "&amp;";
	    pData++;
	    break;
	    
	  case UCS_TAB:
	    sBuf += "\t";
	    pData++;
	    break;

	  default:
	    if (*pData < 0x20)         // Silently eat these characters.
	      pData++;
	    else
	      {
		sBuf.appendUCS4 (pData, 1);
		pData++;
	      }
	  }
      }
    
    writeUTF8String (m_contentStream, sBuf);
  }

  void _openSpan (PT_AttrPropIndex apiSpan)
  {
    if (m_bInSpan)
      _closeSpan();

    if (!apiSpan) // don't write tag for empty A/P
      return;

    UT_UTF8String begC ("<text:span>");
    writeUTF8String (m_contentStream, begC);

    m_bInSpan = true;
  }

  void _closeSpan()
  {
    if (!m_bInSpan)
      return;

    UT_UTF8String endC ("</text:span>\n");
    writeUTF8String (m_contentStream, endC);
    m_bInSpan = false;
  }

  void _openBlock (PT_AttrPropIndex apiSpan)
  {
    if (m_bInBlock)
      _closeBlock();

    UT_UTF8String begP ("<text:p text:style-name=\"Standard\">");
    writeUTF8String (m_contentStream, begP);
    m_bInBlock = true;
  }

  void _closeBlock ()
  {
    if (!m_bInBlock)
      return;

    UT_UTF8String endP ("</text:p>\n");
    writeUTF8String (m_contentStream, endP);
    m_bInBlock = false;
  }

  PD_Document * m_doc;
  IE_Exp_OpenWriter * m_pie;
  OO_StyleAccumulator & m_acc;
  GsfOutput * m_contentStream;

  bool m_bInSpan;
  bool m_bInBlock;
};

/*****************************************************************************/
/*****************************************************************************/

/*!
 * Class holding 1 static member. Its sole duty is to write
 * out a OOo meta.xml file based on Abi's metadata.
 */
class OO_MetaDataWriter
{
public:
  
  static bool writeMetaData(PD_Document * pDoc, GsfOutfile * oo)
  {
    UT_ASSERT_NOT_REACHED();
    GsfOutput * meta = gsf_outfile_new_child (oo, "meta.xml", FALSE);

    static const char * const preamble [] = 
      {
	"<?xml version='1.0' encoding='UTF-8'?>\n",
	"<!DOCTYPE office:document-meta PUBLIC '-//OpenOffice.org//DTD OfficeDocument 1.0//EN' 'office.dtd'>\n",
	"<office:document-meta xmlns:office='http://openoffice.org/2000/office' xmlns:xlink='http://www.w3.org/1999/xlink' xmlns:dc='http://purl.org/dc/elements/1.1/' xmlns:meta='http://openoffice.org/2000/meta' office:version='1.0'>\n",
	"<office:meta>\n",
	"<meta:generator>AbiWord</meta:generator>\n"
      };

    static const char * const postamble [] =
      {
	"</office:meta>\n",
	"</office:document-meta>\n"
      };

    writeToStream(meta, preamble, NrElements(preamble));

    UT_String meta_val, val;

    if (pDoc->getMetaDataProp(PD_META_KEY_DATE, meta_val) && meta_val.size()) {
      val = UT_String_sprintf("<dc:date>%s</dc:date>\n", meta_val.c_str());
      gsf_output_write(meta, val.size(), (const guint8*)val.c_str());
    }
    if (pDoc->getMetaDataProp(PD_META_KEY_LANGUAGE, meta_val) && meta_val.size()) {
      val = UT_String_sprintf("<dc:language>%s</dc:language>\n", meta_val.c_str());
      gsf_output_write(meta, val.size(), (const guint8*)val.c_str());
    }

    writeToStream(meta, postamble, NrElements(postamble));

    gsf_output_close(meta);
    g_object_unref(G_OBJECT(meta));
    return true;
  }

private:
  OO_MetaDataWriter ();
};

/*****************************************************************************/
/*****************************************************************************/

/*!
 * Class holding 1 static member. Its sole duty is to write
 * out a OOo settings file. Probably will just dump "standard"
 * info to the settings file, since Abi pretty much ignores
 * OOo's settings file on import.
 */
class OO_SettingsWriter
{
public:

  static bool writeSettings(PD_Document * pDoc, GsfOutfile * oo)
  {
    GsfOutput * settings = gsf_outfile_new_child (oo, "settings.xml", FALSE);

    static const char * const preamble [] = 
      {
	"<?xml version='1.0' encoding='UTF-8'?>\n",
	"<!DOCTYPE office:document-settings PUBLIC '-//OpenOffice.org//DTD OfficeDocument 1.0//EN' 'office.dtd'>\n",
	"<office:document-settings xmlns:office='http://openoffice.org/2000/office' xmlns:xlink='http://www.w3.org/1999/xlink' xmlns:config='http://openoffice.org/2001/config' office:version='1.0'>\n",
	"<office:settings>\n",
	"</office:settings>\n",
	"</office:document-settings>"
      };

    writeToStream (settings, preamble, NrElements(preamble));

    gsf_output_close(settings);
    g_object_unref(G_OBJECT(settings));

    return true;
  }

private:
  OO_SettingsWriter ();
};

/*****************************************************************************/
/*****************************************************************************/

/*!
 * Class holding 1 static member. Its sole duty is to write
 * out any pictures from inside the Abi document to the
 * OOo pictures directory
 */
class OO_PicturesWriter
{
public:
  
  static bool writePictures(PD_Document * pDoc, GsfOutfile * oo)
  {
    const char * szName;
    const char * szMimeType;
    const UT_ByteBuf * pByteBuf;

    // create Pictures directory
    GsfOutput * pictures = gsf_outfile_new_child(oo, "Pictures", TRUE);
    
    for (UT_uint32 k=0; (pDoc->enumDataItems(k,NULL,&szName,&pByteBuf,(void**)&szMimeType)); k++)
      {
	// create individual pictures
	UT_String name = UT_String_sprintf("IMG-%d.png", k);
	GsfOutput * img = gsf_outfile_new_child(GSF_OUTFILE(pictures), name.c_str(), FALSE);
	gsf_output_write(img, pByteBuf->getLength(),  pByteBuf->getPointer(0));
	gsf_output_close(img);
	g_object_unref(G_OBJECT(img));
      }

    gsf_output_close(pictures);
    g_object_unref(G_OBJECT(pictures));

    return true;
  }

private:

  OO_PicturesWriter ();
};

/*****************************************************************************/
/*****************************************************************************/

/*!
 * Class holding 1 static member. Its sole duty is to create 
 * the OOo manifest file
 */
class OO_ManifestWriter
{
public:

  static bool writeManifest(PD_Document * pDoc, GsfOutfile * oo)
  {
    // create Pictures directory
    GsfOutput * meta_inf = gsf_outfile_new_child(oo, "META-INF", TRUE);
    GsfOutput * manifest = gsf_outfile_new_child(GSF_OUTFILE(meta_inf), "manifest.xml", FALSE);

    UT_String name;

    static const char * const preamble [] = 
      {
	"<?xml version='1.0' encoding='UTF-8'?>\n",
	"<!DOCTYPE manifest:manifest PUBLIC '-//OpenOffice.org//DTD Manifest 1.0//EN' 'Manifest.dtd'>\n",
	"<manifest:manifest xmlns:manifest='http://openoffice.org/2001/manifest'>\n",
	"<manifest:file-entry manifest:media-type='application/vnd.sun.xml.writer' manifest:full-path='/'/>\n",
	"<manifest:file-entry manifest:media-type='text/xml' manifest:full-path='content.xml'/>\n",
	"<manifest:file-entry manifest:media-type='text/xml' manifest:full-path='styles.xml'/>\n",
	"<manifest:file-entry manifest:media-type='text/xml' manifest:full-path='meta.xml'/>\n",
	"<manifest:file-entry manifest:media-type='text/xml' manifest:full-path='settings.xml'/>\n"
      };

    static const char * const postamble [] =
      {
	"</manifest:manifest>\n"
      };


    writeToStream (manifest, preamble, NrElements(preamble));

    const char * szName;
    const char * szMimeType;
    const UT_ByteBuf * pByteBuf;
    for (UT_uint32 k = 0; (pDoc->enumDataItems(k,NULL,&szName,&pByteBuf,(void**)&szMimeType)); k++)
      {
	if (k == 0) {
	  name = "<manifest:file-entry manifest:media-type='' manifest:full-path='Pictures/'/>\n";
	  gsf_output_write(manifest, name.size(), (const guint8*)name.c_str());
	}
	  
	name = UT_String_sprintf("<manifest:file-entry manifest:media-type='%s' manifest:full-path='Pictures/IMG-%d.png'/>\n", k, szMimeType);
	gsf_output_write (manifest, name.size(), (const guint8*)name.c_str());
      }

    writeToStream (manifest, postamble, NrElements(postamble));

    gsf_output_close(manifest);
    g_object_unref(G_OBJECT(manifest));
    gsf_output_close(meta_inf);
    g_object_unref(G_OBJECT(meta_inf));

    return true;
  }

private:
  OO_ManifestWriter ();
};

/*****************************************************************************/
/*****************************************************************************/

IE_Exp_OpenWriter::IE_Exp_OpenWriter (PD_Document * pDoc)
  : IE_Exp (pDoc), m_oo(0)
{
}

IE_Exp_OpenWriter::~IE_Exp_OpenWriter()
{
}

/*!
 * This writes out our AbiWord file as an OpenOffice
 * compound document
 */
UT_Error IE_Exp_OpenWriter::_writeDocument(void)
{
  UT_return_val_if_fail(m_oo, UT_ERROR);

  if (!OO_MetaDataWriter::writeMetaData(getDoc(), m_oo))
    return UT_ERROR;

  if (!OO_SettingsWriter::writeSettings(getDoc(), m_oo))
    return UT_ERROR;

  if (!OO_PicturesWriter::writePictures(getDoc(), m_oo))
    return UT_ERROR;

  if (!OO_ManifestWriter::writeManifest(getDoc(), m_oo))
    return UT_ERROR;

  OO_StyleAccumulator accumulator(getDoc(), this);
  if (!getDoc()->tellListener(static_cast<PL_Listener *>(&accumulator)))
    return UT_ERROR;

  if (!accumulator.writeStyles(m_oo))
    return UT_ERROR;

  OO_ContentWriter writer(getDoc(), this, accumulator, m_oo);
  if (!getDoc()->tellListener(static_cast<PL_Listener *>(&writer)))
    return UT_ERROR;

  return UT_OK;
}

/*!
 * Open the underlying ZIP file for writing
 */
bool IE_Exp_OpenWriter::_openFile(const char * szFilename)
{
  UT_return_val_if_fail(!m_oo, false);
  
  GsfOutput * sink = gsf_output_stdio_new (szFilename, NULL);
  if (!sink)
    return false;

  m_oo = gsf_outfile_zip_new (sink, NULL);
  g_object_unref(G_OBJECT(sink));

  return (m_oo != 0);
}

/*!
 * Close our underlying ZIP file
 */
bool IE_Exp_OpenWriter::_closeFile(void)
{
  if(m_oo) {
    gsf_output_close(GSF_OUTPUT(m_oo));
    g_object_unref(G_OBJECT(m_oo));
    m_oo = 0;
  }

  return true;
}

/*****************************************************************************/
/*****************************************************************************/
