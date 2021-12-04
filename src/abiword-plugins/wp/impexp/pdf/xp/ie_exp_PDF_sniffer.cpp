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

/*****************************************************************/

UT_Error IE_Exp_PDF::_writeDocument(void)
{
  m_pListener = new s_PDF_Listener(getDoc(),this);
  if (!m_pListener)
    return UT_IE_NOMEMORY;
  if (!getDoc()->tellListener(static_cast<PL_Listener *>(m_pListener)))
    return UT_ERROR;
  delete m_pListener;

  m_pListener = NULL;

  return ((m_error) ? UT_IE_COULDNOTWRITE : UT_OK);
}

/*****************************************************************/

class s_PDF_Listener : public PL_Listener
  {
  public:
    s_PDF_Listener(PD_Document * pDocument,
                   IE_Exp_PDF * pie);
    virtual ~s_PDF_Listener();

    virtual bool		populate(PL_StruxFmtHandle sfh,
                           const PX_ChangeRecord * pcr);

    virtual bool		populateStrux(PL_StruxDocHandle sdh,
                                const PX_ChangeRecord * pcr,
                                PL_StruxFmtHandle * psfh);

    virtual bool		change(PL_StruxFmtHandle sfh,
                         const PX_ChangeRecord * pcr);

    virtual bool		insertStrux(PL_StruxFmtHandle sfh,
                              const PX_ChangeRecord * pcr,
                              PL_StruxDocHandle sdh,
                              PL_ListenerId lid,
                              void (* pfnBindHandles)(PL_StruxDocHandle sdhNew,
                                                      PL_ListenerId lid,
                                                      PL_StruxFmtHandle sfhNew));

    virtual bool		signal(UT_uint32 iSignal);
  protected:

    void           _handlePageSize(PT_AttrPropIndex api);
    void           _handleAttributes(PT_AttrPropIndex api);
    void				_handleStyles(void);
    void				_handleDataItems(void);
    void           _outputData(const UT_UCSChar * data, UT_uint32 length);

    void				_closeSection(void);
    void				_closeBlock(void);
    void				_closeSpan(void);
    void				_openBlock(PT_AttrPropIndex api);
    void				_openSection(PT_AttrPropIndex api);
    void				_openSpan(PT_AttrPropIndex api, PT_BlockOffset pos, UT_uint32 len);
    void           _writeMarginSize(PT_AttrPropIndex api, char * name);

  private:
    PD_Document *		m_pDocument;
    IE_Exp_PDF *    m_pie;

    bool				m_bFirstWrite;

    UT_String			m_sFormats;
    UT_String			m_sLayout;

    int             m_iImgCnt;

    UT_Vector m_pages;	 //(of page_t 's)
    page_t * m_current_page;
    int m_numpages;

  };


/*****************************************************************/
/*****************************************************************/

IE_Exp_PDF_Sniffer::IE_Exp_PDF_Sniffer () :
  IE_ExpSniffer("AbiPDF::PDF")
{
  // 
}

bool IE_Exp_PDF_Sniffer::recognizeSuffix(const char * szSuffix)
{
  return (!UT_stricmp(szSuffix,".pdf"));
}

UT_Error IE_Exp_PDF_Sniffer::constructExporter(PD_Document * pDocument,
    IE_Exp ** ppie)
{
  IE_Exp_PDF * p = new IE_Exp_PDF(pDocument);
  *ppie = p;
  return UT_OK;
}

bool IE_Exp_PDF_Sniffer::getDlgLabels(const char ** pszDesc,
                                      const char ** pszSuffixList,
                                      IEFileType * ft)
{
  *pszDesc = "PDF (.pdf)";
  *pszSuffixList = "*.pdf";
  *ft = getFileType();
  return true;
}



s_PDF_Listener::s_PDF_Listener(PD_Document * pDocument,
                               IE_Exp_PDF * pie)
    : m_pDocument (pDocument), m_pie (pie),
    m_bInSection(false), m_bInBlock(false),
    m_bInSpan(false), m_bFirstWrite(true),
    m_sFormats(""), m_sLayout(""), m_iImgCnt(0),m_numpages(0)
{
  //just writes out heading... nothing to do here folks.
}

s_PDF_Listener::~s_PDF_Listener()
{
  //finish off any open tags
  m_pie->write_document(m_pages);
}

bool s_PDF_Listener::populate(PL_StruxFmtHandle /*sfh*/, const PX_ChangeRecord * pcr)
{
  switch (pcr->getType())
    {
    case PX_ChangeRecord::PXT_InsertSpan:
      {
        const PX_ChangeRecord_Span * pcrs =
          static_cast<const PX_ChangeRecord_Span *> (pcr);

        PT_AttrPropIndex api = pcr->getIndexAP();
        if (api)
          {
            _openSpan(api,pcrs->getBlockOffset(),pcrs->getLength());
          }

        PT_BufIndex bi = pcrs->getBufIndex();

        //passes the text;
        _outputData(m_pDocument->getPointer(bi),pcrs->getLength());

        if (api)
          {
            _closeSpan();
          }
        return true;
      }

    case PX_ChangeRecord::PXT_InsertObject:
      {
        const PX_ChangeRecord_Object * pcro = static_cast<const PX_ChangeRecord_Object *> (pcr);
        //PT_AttrPropIndex api = pcr->getIndexAP();

        switch (pcro->getObjectType())
          {
          case PTO_Image:
          case PTO_Field:
          case PTO_Hyperlink:
          case PTO_Bookmark:
            return true;

          default:
            {
              UT_ASSERT(0);
              return false;
            }
          }
      }
    case PX_ChangeRecord::PXT_InsertFmtMark:
      return true;

    default:
      UT_ASSERT(0);
      return false;
    }
}

bool s_PDF_Listener::populateStrux(PL_StruxDocHandle /*sdh*/,
                                   const PX_ChangeRecord * pcr,
                                   PL_StruxFmtHandle * psfh)
{
  UT_ASSERT(pcr->getType() == PX_ChangeRecord::PXT_InsertStrux);
  const PX_ChangeRecord_Strux * pcrx = static_cast<const PX_ChangeRecord_Strux *> (pcr);
  *psfh = 0;							// we don't need it.

  switch (pcrx->getStruxType())
    {
    case PTX_Section:
      {
        _closeSpan();
        _closeBlock();
        _closeSection();

        PT_AttrPropIndex indexAP = pcr->getIndexAP();
        const PP_AttrProp* pAP = NULL;
        if (m_pDocument->getAttrProp(indexAP, &pAP) && pAP)
          {
            const XML_Char* pszSectionType = NULL;
            pAP->getAttribute("type", pszSectionType);
            if (!pszSectionType	|| (0 == UT_strcmp(pszSectionType, "doc")))
              {
                _openSection(pcr->getIndexAP());
              }
            else
            {}
          }
        else
        {}
        return true;
      }

    case PTX_SectionHdrFtr:
      {
        // TODO???
        return true;
      }

    case PTX_Block:
      {
        _closeSpan();
        _closeBlock();
        _openBlock(pcr->getIndexAP());
        return true;
      }

    default:
      {
        UT_ASSERT(0);
        return false;
      }

    }
}

bool s_PDF_Listener::signal(UT_uint32 /* iSignal */)
{
  UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
  return false;
}

bool s_PDF_Listener::change(PL_StruxFmtHandle /*sfh*/,
                            const PX_ChangeRecord * /*pcr*/)
{
  UT_ASSERT(0);						// this function is not used.
  return false;
}

bool s_PDF_Listener::insertStrux(PL_StruxFmtHandle /*sfh*/,
                                 const PX_ChangeRecord * /*pcr*/,
                                 PL_StruxDocHandle /*sdh*/,
                                 PL_ListenerId /* lid */,
                                 void (* /*pfnBindHandles*/)(PL_StruxDocHandle /* sdhNew */,
                                                             PL_ListenerId /* lid */,
                                                             PL_StruxFmtHandle /* sfhNew */))
{
  UT_ASSERT(0);						// this function is not used.
  return false;
}

/*****************************************************************/
/*****************************************************************/

int justificationToNumber(const char * justification_name)
{
  if (! strcmp(justification_name,"left"))
    return 0;
  else if (! strcmp(justification_name,"center"))
    return 1;
  else if (! strcmp(justification_name,"right"))
    return 2;
  else if (! strcmp(justification_name,"justify"))
    return 3;
  else
    {
      UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
      return "";
    }
}

//do not destroy !!
int s_PDF_Listener::_MarginSize(PT_AttrPropIndex api, char * name)
{
  UT_String buf;
  const XML_Char * szValue;
  const PP_AttrProp * pAP = NULL;
  bool bHaveProp = m_pDocument->getAttrProp(api,&pAP);
  UT_ASSERT((bHaveProp));

  UT_String_sprintf(buf, "page-margin-%s", name);
  szValue = PP_evalProperty(buf.c_str(),
                            NULL, NULL, pAP, m_pDocument, true);
  return UT_convertToDimension(szValue, DIM_PT));
}

void s_PDF_Listener::_handlePageSize(PT_AttrPropIndex api)
{

  /*
  Doesn't work

  m_pages[m_numpages-1]->width = m_pDocument->m_docPageSize.Width(DIM_PT);
  m_pages[m_numpages-1]->length = m_pDocument->m_docPageSize.Height(DIM_PT);

  m_pages[m_numpages-1]->left = m_pDocument->m_docPageSize.MarginLeft(DIM_PT);
  	m_pages[m_numpages-1]->right = m_pDocument->m_docPageSize.MarginRight(DIM_PT);
  m_pages[m_numpages-1]->top = m_pDocument->m_docPageSize.MarginTop(DIM_PT);
  m_pages[m_numpages-1]->bottom = m_pDocument->m_docPageSize.MarginBottom(DIM_PT);
  */

  // m_pDocument->m_docPageSize.isPortrait())  orientation does not matter!

  // background_color[3]
  m_bFirstWrite = false;

  return;
}

void s_PDF_Listener::_handleDataItems(void)
{
  const char * szName;
  const char * szMimeType;
  const UT_ByteBuf * pByteBuf;

  for (UT_uint32 k=0; (m_pDocument->enumDataItems(k,NULL,&szName,&pByteBuf,(void**)&szMimeType)); k++)
  {}

  return;
}

void s_PDF_Listener::_handleStyles(void)
{
}

void s_PDF_Listener::_openSection(PT_AttrPropIndex api)
{
  if (m_bFirstWrite)
    {
      m_numpages++;
      m_pages.addItem(new page_t);
      _handlePageSize(api);
    }
  m_bInSection = true;

}


void s_PDF_Listener::_openBlock(PT_AttrPropIndex api)
{

  const PP_AttrProp * pAP = NULL;
  bool bHaveProp = m_pDocument->getAttrProp(api,&pAP);

  m_bInBlock = true;

  double left_indent = 0;
  if (pAP->getProperty("margin-left", szValue))
    left_indent = UT_convertToDimension(szValue, DIM_PT);
  double first_indent = left_indent;
  if (pAP->getProperty("text-indent", szValue))
    first_indent += UT_convertToDimension(szValue, DIM_PT);
  double right_indent = 0;
  if (pAP->getProperty("margin-right", szValue))
    right_indent = UT_convertToDimension(szValue, DIM_PT);

  // m_sLayout += UT_convertToDimensionlessString(left_indent,"2.4");
  double before_offset = 0;
  if (pAP->getProperty("margin-top", szValue))
    before_offset = UT_convertToDimension(szValue, DIM_PT);
  double after_offset = 0;
  if (pAP->getProperty("margin-bottom", szValue))
    after_offset = UT_convertToDimension(szValue,DIM_PT);

  //	m_sLayout += UT_convertToDimensionlessString(before_offset,"2.4");


  bool bLinesTogether=false;
  if (pAP->getProperty("keep-together", szValue))
    bLinesTogether = (UT_stricmp(szValue,"true") == 0);
  bool bKeepWithNext=false;
  if (pAP->getProperty("keep-with-next", szValue))
    bKeepWithNext = (UT_stricmp(szValue,"true") == 0);

  if (pAP->getProperty("bgcolor", szValue))
    {
      //"color=\"#" ((const char *)szValue);
    }

  if (pAP->getProperty("color", szValue))
  {}

  if (pAP->getProperty("lang", szValue))
  {}

  if (pAP->getProperty("font-size", szValue))
  {}

  if (pAP->getProperty("font-family", szValue))
  {}
  else
  {}

  if (pAP->getProperty("font-weight", szValue))
    {

    }

  if (pAP->getProperty("font-style", szValue))
  {}

  if (pAP->getProperty("font-stretch", szValue))
    {
      //??
    }
}

void s_PDF_Listener::_openSpan(PT_AttrPropIndex api, PT_BlockOffset pos, UT_uint32 len)
{
  const PP_AttrProp * pAP = NULL;
  bool bHaveProp = m_pDocument->getAttrProp(api,&pAP);
  UT_String buf;

  UT_String typeface;
  UT_String style;
  r_text * temp_text_render = new r_text;
  render_t * temp_render = new render_t;


  if (bHaveProp && pAP)
    {
      // query and output properties
      const XML_Char * szValue = 0;

      if (pAP->getProperty("font-family", szValue))
        {
          typeface = (char *)szValue;
        }
      else
        {
          typeface = "times"; //FIX should be capitalized?
        }
      style = "";
      if (pAP->getProperty("font-weight", szValue))
        {
          style += szValue; //szValue, "bold"
        }
      if (pAP->getProperty("font-style", szValue))
        {
          style += szValue // szValue, "italic"
                 }

               //adds the font now, and save its number;

               temp_text_render->typeface = m_pie->addfont(typeface,style);

      if (pAP->getProperty("font-size", szValue))
        {
          temp_text_render->size = UT_convertToDimension(szValue, DIM_PT);
        }
      else
        {
          temp_text_render->size = 12;
        }
      //temp_text_render->spacing = ; character spacing.
      if (pAP->getProperty("text-position", szValue))
        {
          // TODO reduce font size and raise or lower as necessary

          //if (!UT_stricmp (szValue, "subscript"))
          //else if (!UT_stricmp (szValue, "superscript"))
        }

      if (pAP->getProperty("color", szValue))
        {
          UT_String red, green, blue;
          UT_RGBColor rgb;

          // convert from hex/decimal
          UT_parseColor(szValue, rgb);

          temp_text_render->rgb[0] = rgb.m_red;
          temp_text_render->rgb[1] = rgb.m_grn;
          temp_text_render->rgb[2] = rgb.m_blu;
        }
      else
        {
          //FIX? Black is 0,0,0 right?
          temp_text_render->rgb[0] = 0;
          temp_text_render->rgb[1] = 0;
          temp_text_render->rgb[2] = 0;
        }


      // TODO need to determine width/ height of text, then x,y of render;

      if (pAP->getProperty("text-decoration", szValue))
        {
          if (strstr (szValue, "underline"))
            {
              //TODO create a line in position under text;
            }
          if (strstr (szValue, "line-through"))
            {
              //TODO create a line in position in center of text;
            }
        }



      if (pAP->getProperty("bgcolor", szValue))
        {
          //TODO add a RENDER_BOX to page with background color with same
          //TODO size as text field.
        }

    }

}


void s_PDF_Listener::_closeBlock(void)
{
}

void s_PDF_Listener::_closeSection(void)
{
}

void s_PDF_Listener::_closeSpan(void)
{
}

/*****************************************************************/
/*****************************************************************/

void s_PDF_Listener::_outputData(const UT_UCSChar * data, UT_uint32 length)
{

  // PDF uses windows character set.

  UT_String sBuf;
  const UT_UCSChar * pData;

  UT_ASSERT(sizeof(UT_Byte) == sizeof(char));

  // for (pData=data; (pData<data+length); /**/)
  /*	{
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

  	case UCS_LF:					// LF -- representing a Forced-Line-Break
  		// TODO
  		UT_ASSERT(UT_TODO);
  		pData++;
  		break;
  		
  	case UCS_VTAB:					// VTAB -- representing a Forced-Column-Break
  		// TODO
  		UT_ASSERT(UT_TODO);
  		pData++;
  		break;
  		
  	case UCS_FF:					// FF -- representing a Forced-Page-Break
  		// TODO:
  		UT_ASSERT(UT_TODO);
  		pData++;
  		break;
  		
  	default:
  	*/
  if (*pData > 0x007f)
    {
      if(XAP_EncodingManager::get_instance()->isUnicodeLocale() ||
          (XAP_EncodingManager::get_instance()->try_nativeToU(0xa1) == 0xa1))

        {
          XML_Char * pszUTF8 = UT_encodeUTF8char(*pData++);
          while (*pszUTF8)
            {
              sBuf += (char)*pszUTF8;
              pszUTF8++;
            }
        }
      else
        {
          /*
          Try to convert to native encoding and if
          character fits into byte, output raw byte. This 
          is somewhat essential for single-byte non-latin
          languages like russian or polish - since
          tools like grep and sed can be used then for
          these files without any problem.
          Networks and mail transfers are 8bit clean
          these days.  - VH
          */
          UT_UCSChar c = XAP_EncodingManager::get_instance()->try_UToNative(*pData);
          if (c==0 || c>255)
            {
              sBuf += UT_String_sprintf("&#x%x;",*pData++);
            }
          else
            {
              sBuf += (char)c;
              pData++;
            }
        }
    }
  else
    {
      sBuf += (char)*pData++;
    }

  //current text renderer        ->buffer = sBuf;
}
