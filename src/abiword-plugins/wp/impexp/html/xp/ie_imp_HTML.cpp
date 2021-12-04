/* AbiWord: ie_imp_HTML - plugin for non-XHTML HTML
 * Copyright (C) 2002 Francis James Franklin <fjf@alinameridon.com>
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


#include <stdio.h>
#include <string.h>
#include <ctype.h>

// AbiWord includes

#include "ut_misc.h"
#include "ut_bytebuf.h"
#include "ut_growbuf.h"
#include "ut_assert.h"
#include "ut_debugmsg.h"

#include "pd_Document.h"
#include "pd_Style.h"

// Local includes

#include "ie_imp_HTML.h"

#include "HTML_Parser.h"

#include "HTML_colors.h"
#include "HTML_tags.h"
#include "HTML_utils.h"

#include "HTML_TokenStack.h"
#include "HTML_TextState.h"

/*****************************************************************/
/*****************************************************************/

#include "xap_Module.h"

ABI_PLUGIN_DECLARE("HTML")

// we use a reference-counted sniffer
static IE_Imp_HTML_Sniffer * m_sniffer = 0;

ABI_FAR_CALL
int abi_plugin_register (XAP_ModuleInfo * mi)
{
  if (!m_sniffer)
    {
      m_sniffer = new IE_Imp_HTML_Sniffer ();
    }
  else
    {
      m_sniffer->ref ();
    }

  mi->name = "HTML Importer";
  mi->desc = "Import HTML Documents (Experimental)";
  mi->version = ABI_PLUGIN_VERSION;
  mi->author = "Abi, the Ant, & fjf, her friend.";
  mi->usage = "See back of Prayer Wheel for instructions.";

  IE_Imp::registerImporter (m_sniffer);
  return 1;
}

ABI_FAR_CALL
int abi_plugin_unregister (XAP_ModuleInfo * mi)
{
  mi->name = 0;
  mi->desc = 0;
  mi->version = 0;
  mi->author = 0;
  mi->usage = 0;

  UT_ASSERT (m_sniffer);

  IE_Imp::unregisterImporter (m_sniffer);

  if (!m_sniffer->unref ())
    {
      m_sniffer = 0; // Shouldn't this be deleted?
    }

  return 1;
}

ABI_FAR_CALL
int abi_plugin_supports_version (UT_uint32 major, UT_uint32 minor, UT_uint32 release)
{
#if 0
  /* Is there a correct way to do this?
   */
  if ((major == 1) && (minor == 0) /* && (release >= 0) */) return 1;

  /* Strict check for development versions
   */
  return (((  major == (UT_uint32) ABI_PLUGIN_MAJOR)
        && (  minor == (UT_uint32) ABI_PLUGIN_MINOR)
        && (release == (UT_uint32) ABI_PLUGIN_MICRO)) ? 1 : 0);
#else
  return 1 ;
#endif
}

/*****************************************************************/
/*****************************************************************/

IE_Imp_HTML_Sniffer::IE_Imp_HTML_Sniffer () :
  IE_ImpSniffer("AbiHTML::HTML")
{
  // 
}

UT_Confidence_t IE_Imp_HTML_Sniffer::supportsMIME (const char * szMIME)
{
  if (UT_strcmp (IE_FileInfo::mapAlias (szMIME), IE_MIME_HTML) == 0)
    {
      return UT_CONFIDENCE_GOOD;
    }
  return UT_CONFIDENCE_ZILCH;
}

UT_Confidence_t IE_Imp_HTML_Sniffer::recognizeContents (const char * szBuf, UT_uint32 iNumbytes)
{
#ifdef USE_HTML_PARSER_SNIFFER
  HTML_Parser parser;
  return ( parser.sniff (szBuf, iNumbytes) ? UT_CONFIDENCE_PERFECT : UT_CONFIDENCE_ZILCH );
#else
  UT_uint32 i = 0;
  const char * ptr = szBuf;
  while (isspace ((int) (*ptr)))
    {
      ptr++;
      i++;
      if (i == iNumbytes) break;
    }
  if (i == iNumbytes) return UT_CONFIDENCE_ZILCH;
  if (*ptr != '<') return UT_CONFIDENCE_ZILCH;

  UT_uint8 found_html = UT_CONFIDENCE_ZILCH;
  ptr++;
  i++;
  while (i < iNumbytes - 4)
    {
      if (UT_strnicmp (ptr, "html", 4) == 0)
	{
	  found_html = UT_CONFIDENCE_PERFECT;
	  break;
	}
      ptr++;
      i++;
    }
  return found_html;
#endif
}

UT_Confidence_t IE_Imp_HTML_Sniffer::recognizeSuffix (const char * szSuffix)
{
  if (!(UT_stricmp (szSuffix, ".html")) || !(UT_stricmp (szSuffix, ".htm")))
    return UT_CONFIDENCE_PERFECT;
  return UT_CONFIDENCE_ZILCH;
}

UT_Error IE_Imp_HTML_Sniffer::constructImporter (PD_Document * pDocument, IE_Imp ** ppie)
{
  IE_Imp_HTML * p = new IE_Imp_HTML (pDocument);
  *ppie = p;
  return UT_OK;
}

bool IE_Imp_HTML_Sniffer::getDlgLabels (const char ** pszDesc, const char ** pszSuffixList, IEFileType * ft)
{
  *pszDesc = "HTML (.html, .htm)";
  *pszSuffixList = "*.html; *.htm";
  *ft = getFileType ();
  return true;
}

/*****************************************************************/
/*****************************************************************/

IE_Imp_HTML::IE_Imp_HTML (PD_Document * pDocument) :
  IE_Imp(pDocument),
  m_hasContent(false),
  m_stripWhitespace(true),
  m_stripFirstspace(true),
  m_inSection(false),
  m_inBlock(false),
  m_bookmarkOpen(false),
  m_hyperlinkOpen(false),
  m_bookmark(0),
  m_hyperlink(0),
  m_DocumentPlace(dp_PreDocument),
  m_CharDataMode(cdm_Ignore),
  m_pHTML(0),
  m_pBB(0),
  m_error(UT_OK)
{
  //
}

IE_Imp_HTML::~IE_Imp_HTML ()
{
  FREEP(m_bookmark);
  FREEP(m_hyperlink);

  DELETEP (m_pHTML);
  DELETEP (m_pBB);
}

/*****************************************************************/
/*****************************************************************/

UT_Error IE_Imp_HTML::importFile (const char * szFilename)
{
  if (!m_TokenStack.reset ()) return UT_OUTOFMEM;
  if (!m_TextState.reset ())  return UT_OUTOFMEM;

  m_hasContent = false;

  m_inSection = false;
  m_inBlock = false;

  m_pHTML = new HTML_Parser;
  m_pHTML->setListener (this);

  m_DocumentPlace = dp_PreDocument;
  m_CharDataMode = cdm_Ignore;

  m_error = UT_OK;
  if (!m_pHTML->parse (szFilename)) m_error = ((m_error == UT_OK) ? UT_IE_BOGUSDOCUMENT : m_error);

  DELETEP (m_pHTML);

  if ((m_error == UT_OK) && !m_hasContent) // If no errors & document has no content, add an empty block.
    if (!_Block ())
      m_error = UT_ERROR;

  return m_error;
}

/*****************************************************************/
/*****************************************************************/

bool IE_Imp_HTML::_Section (const char * type /* = 0 */)
{
  const char * attribute[4];
  const char ** atts = 0;

  if (type)
    {
      attribute[0] = "type";
      attribute[1] = type;
      attribute[2] = 0;
      attribute[3] = 0;
      atts = (const char **) attribute;
    }
  fprintf (stderr, "Adding Section...\n");
  if (getDoc()->appendStrux (PTX_Section, atts))
    {
      m_inSection = true;
      m_inBlock = false;
      return true;
    }
  return false;
}

/* Just a simple block. Lists require many more args
 */
bool IE_Imp_HTML::_Block (const char * style /* = 0 */, const char * props /* = 0 */)
{
  if (!m_inSection)
    if (!_Section ())
      return false;

  if (m_inBlock) // close any open links before starting new block
    {
      if (m_bookmarkOpen)  bookmark (false);
      if (m_hyperlinkOpen) hyperlink (false);
    }

  if (style == 0) style = "Normal";
  if (props == 0) props = "text-align:left";

  const char * attribute[6];

  attribute[0] = "style";
  attribute[1] = style;
  attribute[2] = "props";
  attribute[3] = props;
  attribute[4] = 0;
  attribute[5] = 0;

  const char ** atts = (const char **) attribute;
  fprintf (stderr, "Adding Block...\n");
  if (getDoc()->appendStrux (PTX_Block, atts))
    {
      // If no content is added, a blank document will be returned from the importer
      m_hasContent = true;
      m_inBlock = true;

      if (m_bookmark)  bookmark (true);  // open link if pending
      if (m_hyperlink) hyperlink (true); // open link if pending

      return true;
    }
  return false;
}

/*****************************************************************/
/*****************************************************************/

void IE_Imp_HTML::bookmark (bool start)
{
  if (m_bookmark == 0) return;

  if (!m_inBlock) // There's an odd case where bookmark/hyperlink exists outside of any block structure...
    {
      if (!start)
	{
	  free (m_bookmark);
	  m_bookmark = 0;
	  m_bookmarkOpen = start;
	}
      return;
    }
  if (m_bookmarkOpen == start) return;

  const char * attribute[6];

  if (start)
    {
      attribute[0] = "type";
      attribute[1] = "start";
    }
  else
    {
      attribute[0] = "type";
      attribute[1] = "end";
    }
  attribute[2] = "name";
  attribute[3] = m_bookmark;
  attribute[4] = 0;
  attribute[5] = 0;

  const char ** atts = (const char **) attribute;

  getDoc()->appendObject (PTO_Bookmark, atts);

  if (!start)
    {
      free (m_bookmark);
      m_bookmark = 0;
    }
  m_bookmarkOpen = start;
}

void IE_Imp_HTML::hyperlink (bool start)
{
  if (m_hyperlink == 0) return;

  if (!m_inBlock) // There's an odd case where bookmark/hyperlink exists outside of any block structure...
    {
      if (!start)
	{
	  free (m_hyperlink);
	  m_hyperlink = 0;
	  m_hyperlinkOpen = start;
	}
      return;
    }
  if (m_hyperlinkOpen == start) return;

  const char * attribute[4];

  attribute[0] = "xlink:href";
  attribute[1] = m_hyperlink;
  attribute[2] = 0;
  attribute[3] = 0;

  const char ** atts = (const char **) attribute;

  if (start)
    getDoc()->appendObject (PTO_Hyperlink, atts);
  else
    getDoc()->appendObject (PTO_Hyperlink, 0);

  if (!start)
    {
      free (m_hyperlink);
      m_hyperlink = 0;
    }
  m_hyperlinkOpen = start;
}

/*****************************************************************/
/*****************************************************************/

/* Call-back used by defineStyles
 */
void IE_Imp_HTML::addStyle (const char ** atts)
{
  PD_Style * pStyle = 0;

  if (getDoc()->getStyle (atts[7], &pStyle))
    {
      if (pStyle->addAttributes (atts))
	{
	  pStyle->getBasedOn ();
	  pStyle->getFollowedBy ();
	}
    }
  else getDoc()->appendStyle (atts);
}

/*****************************************************************/
/*****************************************************************/

void IE_Imp_HTML::charData (const char * buffer, int length)
{
  for (int i = 0; i < length; i++) fputc ((int) buffer[i], stderr); // DEBUG
  if (m_CharDataMode == cdm_Ignore) return;

  if (m_pBB == 0) m_pBB = new UT_ByteBuf;
  m_pBB->append ((UT_Byte *) buffer, (UT_uint32) length); // How safe is this ?? Assumes sizeof(xmlChar)==sizeof(UT_Byte)
}

void IE_Imp_HTML::flushData ()
{
  if (m_pBB == 0) return;

  if (m_pBB->getLength ()) stripData ();
  if (m_pBB->getLength ())
    {
      /* Set text properties
       */
      char * style = m_TextState.getStyle ();
      char * props = m_TextState.getProps ();

      if (!m_inBlock)
	if (!_Block (style))
	  {
	    m_error = UT_ERROR;
	    return;
	  }

      if (style && props)
	{
	  const char * attribute[6];

	  attribute[0] = "style";
	  attribute[1] = style;
	  if (*props)
	    {
	      attribute[2] = "props";
	      attribute[3] = props;
	    }
	  else
	    {
	      attribute[2] = 0;
	      attribute[3] = 0;
	    }
	  attribute[4] = 0;
	  attribute[5] = 0;

	  const char ** atts = (const char **) attribute;
	  fprintf (stderr, "Adding Format... style=\"%s\" props=\"%s\"\n", style, props);
	  getDoc()->appendFmt (atts);
	}
      fprintf (stderr, "Added Format\n");
      /* Add accumulated char. data to document
       */
      UT_GrowBuf * pGB = new UT_GrowBuf;
      UT_decodeUTF8string ((const char *) m_pBB->getPointer (0), m_pBB->getLength (), pGB);
      if (pGB->getLength ())
	{
	  fprintf (stderr, "Adding Span...\n");
	  getDoc()->appendSpan ((UT_UCSChar *) pGB->getPointer (0), pGB->getLength ());
	}

      /* Clear buffer
       */
      m_pBB->truncate (0);
    }
}

void IE_Imp_HTML::stripData ()
{
  UT_uint32 len = m_pBB->getLength ();
  UT_uint32 pos = 0;

  const UT_Byte * buf = m_pBB->getPointer (pos);

  bool deleteSpace = ((m_stripWhitespace && m_stripFirstspace) ? true : false);

  /* m_stripFirstspace is set by TT_H? and TT_P; "Firstspace" is the 1st space after the <h?> or <p>
   */
  m_stripFirstspace = false;

  while (pos < len)
    {
      buf = m_pBB->getPointer (pos);

      if (buf[0] == UCS_CR) // always convert CRLF & CR to LF.
	{
	  if ((pos + 1) < len)
	    if (buf[1] == UCS_LF)
	      {
		m_pBB->del (pos, 1);
		len = m_pBB->getLength ();
		continue;
	      }
	  UT_Byte lf = UCS_LF;
	  m_pBB->overwrite (pos, &lf, 1);
	  continue;
	}
      if (m_stripWhitespace && UT_UCS4_isspace (buf[0])) // if stripping, convert all whitespace to space.
	if (buf[0] != UCS_SPACE)
	  {
	    UT_Byte sp = UCS_SPACE;
	    m_pBB->overwrite (pos, &sp, 1);
	    continue;
	  }
      if (deleteSpace && (buf[0] == UCS_SPACE))
	{
	  m_pBB->del (pos, 1);
	  len = m_pBB->getLength ();
	  continue;
	}
      deleteSpace = false;

      if (m_stripWhitespace && (buf[0] == UCS_SPACE))
	{
	  deleteSpace = true; // if stripping, remove all subsequent whitespace
	  pos++;
	  continue;
	}
      if (buf[0] < 0x80) // plain us-ascii part of latin-1
	{
	  pos++;
	  continue;
	}
      if ((buf[0] & 0xf0) == 0xf0) // lead byte in 4-byte surrogate pair
	{
	  // surrogate pairs are defined in section 3.7 of the unicode standard version 2.0 as an extension
	  // mechanism for rare characters in future extensions of the unicode standard.
	  m_pBB->del (pos, ((len - pos) >= 4) ? 4 : (len - pos));
	  len = m_pBB->getLength ();
	  UT_ASSERT (UT_NOT_IMPLEMENTED);
	  continue;
	}
      if ((buf[0] & 0xe0) == 0xe0) // lead byte in 3-byte sequence
	{
	  if ((len - pos) >= 3)
	    {
	      pos += 3;
	    }
	  else
	    {
	      m_pBB->del (pos, len - pos);
	      len = m_pBB->getLength ();
	    }
	  continue;
	}
      if ((buf[0] & 0xc0) == 0xc0) // lead byte in 2-byte sequence
	{
	  if ((len - pos) >= 2)
	    {
	      pos += 2;
	    }
	  else
	    {
	      m_pBB->del (pos, len - pos);
	      len = m_pBB->getLength ();
	    }
	  continue;
	}

      /* Hopefully, shouldn't get here... delete & pray!
       */
      m_pBB->del (pos, 1);
      len = m_pBB->getLength ();
    }
}

void IE_Imp_HTML::startElement (const char * name, const char ** atts)
{
  fprintf (stderr, "<%s>", name); // DEBUG

  int token = s_mapNameToToken (name);

  switch (m_DocumentPlace) // libxml2 does all the hard work; the checks here are redundant, probably
    {
    case dp_PreDocument:
      if (token == TT_HTML) m_DocumentPlace = dp_PreHead;
      else m_error = UT_ERROR;
      break;
    case dp_PreHead:
      if (token == TT_HEAD) m_DocumentPlace = dp_Head;
      else if (token == TT_BODY) m_DocumentPlace = dp_Body;
      else m_error = UT_ERROR;
      break;
    case dp_Head:
      break;
    case dp_PreBody:
      if (token == TT_BODY) m_DocumentPlace = dp_Body;
      else if (token == TT_HEAD) m_DocumentPlace = dp_Head; // Allow multiple <head>[]</head> - unfortunately possible!
      else m_error = UT_ERROR;
      break;
    case dp_Body:
      break;
    case dp_PostBody:
      m_error = UT_ERROR;
      break;
    case dp_PostDocument:
      m_error = UT_ERROR;
      break;
    }
  if (m_error != UT_OK) { m_pHTML->stop (); return; }

  if ((m_CharDataMode == cdm_Body))
    if (!m_TextState.push ())
      {
	m_error = UT_OUTOFMEM;
	m_pHTML->stop ();
	return;
      }

  _Element (token, name, atts, true);

  if (m_error == UT_OK)
    if (!m_TokenStack.push (token))
      {
	m_error = UT_OUTOFMEM;
	m_pHTML->stop ();
      }
}

void IE_Imp_HTML::endElement (const char * name)
{
  fprintf (stderr, "</%s>", name); // DEBUG

  int token = s_mapNameToToken (name);

  if (m_TokenStack.pop () != token) m_error = UT_ERROR; // the pop is the important part
  if (m_error != UT_OK) { m_pHTML->stop (); return; }

  switch (m_DocumentPlace) // libxml2 does all the hard work; the checks here are redundant, probably
    {
    case dp_PreDocument:
      m_error = UT_ERROR;
      break;
    case dp_PreHead:
      m_error = UT_ERROR;
      break;
    case dp_Head:
      if (token == TT_HEAD) m_DocumentPlace = dp_PreBody;
      break;
    case dp_PreBody:
      m_error = UT_ERROR;
      break;
    case dp_Body:
      if (token == TT_BODY) m_DocumentPlace = dp_PostBody;
      break;
    case dp_PostBody:
      if (token == TT_HTML) m_DocumentPlace = dp_PostDocument;
      else m_error = UT_ERROR;
      break;
    case dp_PostDocument:
      m_error = UT_ERROR;
      break;
    }
  if (m_error != UT_OK) { m_pHTML->stop (); return; }

  _Element (token, name, 0, false);

  if ((m_CharDataMode == cdm_Body) && (m_error == UT_OK))
    if (!m_TextState.pop ())
      {
	m_error = UT_ERROR;
	m_pHTML->stop ();
      }
}

void IE_Imp_HTML::_Element (int token, const char * name, const char ** atts, bool start)
{
  if (m_CharDataMode == cdm_Body) flushData ();

  switch (token)
    {
    case TT_OTHER: // 		0	// ?		Tag not recognized (not an error, though)
      break;

    case TT_HTML: // 		1	// <html>	Document main/first tag
      break;

    case TT_HEAD: // 		2	// <head>	(child of <html>; 1 instance; precedes <body>)
      break;
    case TT_BODY: // 		3	// <body>	(child of <html>; 1 instance; follows <head>)
      if (start) m_TextState.defineStyles (this);
      break;

    case TT_TITLE: // 		4	// <title>	(child of <head>)
      if (!m_TokenStack.child_of_head ()) break;
      break;
    case TT_STYLE: // 		5	// <style>	(child of <head>)
      if (!m_TokenStack.child_of_head ()) break;
      break;
    case TT_DIV: // 		6	// <div>	[B] Used with style sheets to produce layers, boxes, etc.
					//		AbiWord uses these in its XHTML output to denote sections
					//		but this seems an uncommon use.
      break;
    case TT_SPAN: // 		7	// <span>	Like <div>, this is used in conjuction with style sheets
      break;
    case TT_LAYER: // 		8	// <layer>	Layer
      break;

    case TT_LINK: // 		9	// <link>	(child of <head>; no children; no end tag)
      if (!m_TokenStack.child_of_head ()) break;
      break;
    case TT_BASE: // 		10	// <base>	(child of <head>; no children; no end tag)
      if (!m_TokenStack.child_of_head ()) break;
      break;
    case TT_META: // 		11	// <meta>	(child of <head>; no children; no end tag)
      if (!m_TokenStack.child_of_head ()) break;
      break;

    case TT_A: // 		21	// <a>		Anchor or Hyperlink (can't nest links)
      if (m_TokenStack.descendant_of (TT_A)) break;
      if (start)
	{
	  const char * name = s_attrLookup (atts, "id"); // "id" is preferred by XHTML 1.1 standard
	  if (name == 0) name = s_attrLookup (atts, "name");
	  if (name) // bookmark
	    {
	      m_bookmarkOpen = false;
	      m_bookmark = UT_strdup (name);
	      bookmark (start);
	      break;
	    }
	  const char * link = s_attrLookup (atts, "xlink:href");
	  if (link == 0) link = s_attrLookup (atts, "href");
	  if (link)
	    {
	      if (link[0] == '#') // in-doc reference to bookmark
		if (link[1])
		  {
		    m_hyperlinkOpen = false;
		    m_hyperlink = UT_strdup (link);
		    hyperlink (start);
		    break;
		  }
	      // else: external reference
	    }
	}
      else
	{
	  if (m_bookmarkOpen)
	    {
	      bookmark (start); // start == false
	      m_bookmarkOpen = false;
	    }
	  if (m_hyperlinkOpen)
	    {
	      hyperlink (start); // start == false
	      m_hyperlinkOpen = false;
	    }
	}
      break;

    case TT_H1: // 		22	// <h1>		Headings
      if (!m_TokenStack.child_of_body ()) break;
      if (start)
	{
	  if (m_TokenStack.descendant_of (TT_PRE))
	    m_TextState.reset (TextState::bs_FixedHeading1, false); // don't truncate TextState
	  else
	    m_TextState.reset (TextState::bs_Heading1);
	  m_stripFirstspace = true;
	  m_inBlock = false;
	  m_CharDataMode = cdm_Body;
	}
      else
	{
	  if (m_bookmarkOpen)  bookmark (start);  // start == false
	  if (m_hyperlinkOpen) hyperlink (start); // start == false
	  m_inBlock = false;
	  if (m_TokenStack.descendant_of (TT_PRE))
	    m_TextState.reset (TextState::bs_FixedNormal, false); // this resets more than necessary...
	  else
	    m_CharDataMode = cdm_Ignore;
	}
      break;
    case TT_H2: // 		23	// <h2>
      if (!m_TokenStack.child_of_body ()) break;
      if (start)
	{
	  if (m_TokenStack.descendant_of (TT_PRE))
	    m_TextState.reset (TextState::bs_FixedHeading2, false); // don't truncate TextState
	  else
	    m_TextState.reset (TextState::bs_Heading2);
	  m_stripFirstspace = true;
	  m_inBlock = false;
	  m_CharDataMode = cdm_Body;
	}
      else
	{
	  if (m_bookmarkOpen)  bookmark (start);  // start == false
	  if (m_hyperlinkOpen) hyperlink (start); // start == false
	  m_inBlock = false;
	  if (m_TokenStack.descendant_of (TT_PRE))
	    m_TextState.reset (TextState::bs_FixedNormal, false); // this resets more than necessary...
	  else
	    m_CharDataMode = cdm_Ignore;
	}
      break;
    case TT_H3: // 		24	// <h3>
      if (!m_TokenStack.child_of_body ()) break;
      if (start)
	{
	  if (m_TokenStack.descendant_of (TT_PRE))
	    m_TextState.reset (TextState::bs_FixedHeading3, false); // don't truncate TextState
	  else
	    m_TextState.reset (TextState::bs_Heading3);
	  m_stripFirstspace = true;
	  m_inBlock = false;
	  m_CharDataMode = cdm_Body;
	}
      else
	{
	  if (m_bookmarkOpen)  bookmark (start);  // start == false
	  if (m_hyperlinkOpen) hyperlink (start); // start == false
	  m_inBlock = false;
	  if (m_TokenStack.descendant_of (TT_PRE))
	    m_TextState.reset (TextState::bs_FixedNormal, false); // this resets more than necessary...
	  else
	    m_CharDataMode = cdm_Ignore;
	}
      break;
    case TT_H4: // 		25	// <h4>		Normal size but bold, others relative (usually) (?)
      if (!m_TokenStack.child_of_body ()) break;
      if (start)
	{
	  if (m_TokenStack.descendant_of (TT_PRE))
	    m_TextState.reset (TextState::bs_FixedHeading4, false); // don't truncate TextState
	  else
	    m_TextState.reset (TextState::bs_Heading4);
	  m_stripFirstspace = true;
	  m_inBlock = false;
	  m_CharDataMode = cdm_Body;
	}
      else
	{
	  if (m_bookmarkOpen)  bookmark (start);  // start == false
	  if (m_hyperlinkOpen) hyperlink (start); // start == false
	  m_inBlock = false;
	  if (m_TokenStack.descendant_of (TT_PRE))
	    m_TextState.reset (TextState::bs_FixedNormal, false); // this resets more than necessary...
	  else
	    m_CharDataMode = cdm_Ignore;
	}
      break;
    case TT_H5: // 		26	// <h5>
      if (!m_TokenStack.child_of_body ()) break;
      if (start)
	{
	  if (m_TokenStack.descendant_of (TT_PRE))
	    m_TextState.reset (TextState::bs_FixedHeading5, false); // don't truncate TextState
	  else
	    m_TextState.reset (TextState::bs_Heading5);
	  m_stripFirstspace = true;
	  m_inBlock = false;
	  m_CharDataMode = cdm_Body;
	}
      else
	{
	  if (m_bookmarkOpen)  bookmark (start);  // start == false
	  if (m_hyperlinkOpen) hyperlink (start); // start == false
	  m_inBlock = false;
	  if (m_TokenStack.descendant_of (TT_PRE))
	    m_TextState.reset (TextState::bs_FixedNormal, false); // this resets more than necessary...
	  else
	    m_CharDataMode = cdm_Ignore;
	}
      break;
    case TT_H6: // 		27	// <h6>
      if (!m_TokenStack.child_of_body ()) break;
      if (start)
	{
	  if (m_TokenStack.descendant_of (TT_PRE))
	    m_TextState.reset (TextState::bs_FixedHeading6, false); // don't truncate TextState
	  else
	    m_TextState.reset (TextState::bs_Heading6);
	  m_stripFirstspace = true;
	  m_inBlock = false;
	  m_CharDataMode = cdm_Body;
	}
      else
	{
	  if (m_bookmarkOpen)  bookmark (start);  // start == false
	  if (m_hyperlinkOpen) hyperlink (start); // start == false
	  m_inBlock = false;
	  if (m_TokenStack.descendant_of (TT_PRE))
	    m_TextState.reset (TextState::bs_FixedNormal, false); // this resets more than necessary...
	  else
	    m_CharDataMode = cdm_Ignore;
	}
      break;

    case TT_ADDRESS: // 	29	// <address>	Author's address { set italics }
      if (start) m_TextState.setItalic ();
      break;

/* Structured Text: Phrase elements
 */
    case TT_EM: // 		40	// <em>		Emphasis { toggle italics }
      if (start) m_TextState.toggleItalic ();
      break;
    case TT_STRONG: // 		41	// <strong>	Stronger emphasis { set bold }
      if (start) m_TextState.setBold ();
      break;
    case TT_DFN: // 		42	// <dfn>	Defining instance { ? }
      if (start) m_TextState.setUnderline ();
      break;
    case TT_CODE: // 		43	// <code>	Computer code { use fixed width font }
      if (start) m_TextState.setFontFamily ("Courier");
      break;
    case TT_SAMP: // 		44	// <samp>	Sample output { use fixed width font }
      if (start) m_TextState.setFontFamily ("Courier");
      break;
    case TT_KBD: // 		45	// <kbd>	Text to be entered by user { use fixed width font }
      if (start) m_TextState.setFontFamily ("Courier");
      break;
    case TT_VAR: // 		46	// <var>	Variable/Argument { use fixed width font }
      if (start) m_TextState.setFontFamily ("Courier");
      break;
    case TT_CITE: // 		47	// <cite>	Citation/Reference { no action }
      break;
    case TT_ABBR: // 		48	// <abbr>	Abbreviation { no action }
      break;
    case TT_ACRONYM: // 	49	// <acronym>	Acronym { no action }
      break;

/* Structured Text: Quotations
 */
    case TT_Q: // 		50	// <q>		Quote { quotation mark e.g. `, ', ", <<, - a job for smart quotes?  }
      break;
    case TT_BLOCKQUOTE: // 	51	// <blockquote>	[B] Block quote { separate paragraph; indented }
      break;

/* Structured Text: Subscripts and superscripts
 */
    case TT_SUB: // 		52	// <sub>	Subscript
      if (m_TokenStack.descendant_of (TT_PRE)) break; // Is this possible?
      if (start) m_TextState.setScriptStyle (TextState::ss_Sub);
      break;
    case TT_SUP: // 		53	// <sup>	Superscript
      if (m_TokenStack.descendant_of (TT_PRE)) break; // Is this possible?
      if (start) m_TextState.setScriptStyle (TextState::ss_Super);
      break;

/* Lines And Paragraphs: Paragraphs
 */
    case TT_P: // 		54	// <p>		[B] New paragraph
					//		Can't contain other block elements, inc. self
					//		(Ignore empty paragraphs.)
      if (!m_TokenStack.child_of_body ()) break;
      if (start)
	{
	  if (m_TokenStack.descendant_of (TT_PRE))
	    m_TextState.reset (TextState::bs_FixedNormal, false); // don't truncate TextState
	  else
	    m_TextState.reset (TextState::bs_Normal);
	  m_stripFirstspace = true;
	  m_inBlock = false;
	  m_CharDataMode = cdm_Body;
	}
      else
	{
	  if (m_bookmarkOpen)  bookmark (start);  // start == false
	  if (m_hyperlinkOpen) hyperlink (start); // start == false
	  m_inBlock = false;
	  if (m_TokenStack.descendant_of (TT_PRE))
	    m_TextState.reset (TextState::bs_FixedNormal, false); // this resets more than necessary...
	  else
	    m_CharDataMode = cdm_Ignore;
	}
      break;

/* Lines And Paragraphs: Controlling line breaks
 */
    case TT_BR: // 		55	// <br>		Forced line break
      if (start) m_inBlock = false;
      break;

/* Lines And Paragraphs: Preformatted text
 */
    case TT_PRE: // 		56	// <pre>	Preformatted text { use fixed width font; white space critical }
					//		Can't contain: <img>, <object>, <big>, <small>, <sub>, <sup>
      if (!m_TokenStack.child_of_body ()) break;
      if (m_TokenStack.descendant_of (TT_PRE)) break; // Is this possible?
      if (start)
	{
	  m_TextState.reset (TextState::bs_FixedNormal);
	  m_inBlock = false;
	  m_CharDataMode = cdm_Body;
	  m_stripWhitespace = false;
	}
      else
	{
	  if (m_bookmarkOpen)  bookmark (start);  // start == false
	  if (m_hyperlinkOpen) hyperlink (start); // start == false
	  m_inBlock = false;
	  m_CharDataMode = cdm_Ignore;
	  m_stripWhitespace = true;
	}
      break;

/* Lines And Paragraphs: Marking document changes
 */
    case TT_INS: // 		57	// <ins>	Insert { set color red }
      if (start) m_TextState.setForeground (CC_red);
      break;
    case TT_DEL: // 		58	// <del>	Delete { set color red; set strike-through }
      if (start)
	{
	  m_TextState.setForeground (CC_red);
	  m_TextState.setLineThrough ();
	}
      break;

/* Lists: Unordered lists, ordered lists, and list items
 */
    case TT_OL: // 		59	// <ol>		Ordered list (children must be <li>)
      break;
    case TT_UL: // 		60	// <ul>		Unordered list (children must be <li>)
      break;
    case TT_LI: // 		61	// <li>		List item (</li> optional)
      break;

/* Lists: Definition lists
 */
    case TT_DL: // 		62	// <dl>		Definition list
      break;
    case TT_DT: // 		63	// <dt>		Definition term { set bold }
      break;
    case TT_DD: // 		64	// <dd>		Definition description { indent }
      break;

/* Lists: <dir> & <menu>
 */
//  case TT_DIR: // 		TT_UL	// <dir>	Directory list { cf. <ul> }
//    break;
//  case TT_MENU: // 		TT_UL	// <menu>	Menu list { cf. <ul> }
//    break;

/* Tables: 
 */
    case TT_TABLE: // 		65	// <table>	Table
      break;
    case TT_CAPTION: // 	66	// <caption>	Caption (child of <table>)
      break;
    case TT_THEAD: // 		67	// <thead>	Table Head (child of <table> acting as new <table>)
      break;
    case TT_TFOOT: // 		68	// <tfoot>	Table Foot (child of <table> acting as new <table>)
      break;
    case TT_TBODY: // 		69	// <tbody>	Table Body (child of <table> acting as new <table>)
      break;
    case TT_COLGROUP: // 	70	// <colgroup>	Un-partition existing columns into one
      break;
    case TT_COL: // 		71	// <col>	Subdivide grouped column (child of <colgroup>)
      break;
    case TT_TR: // 		72	// <tr>		Row (child of <table>)
      break;
    case TT_TH: // 		73	// <th>		Header { set bold } (child of <tr>)
      break;
    case TT_TD: // 		74	// <td>		Data (child of <tr>)
      break;

/* Objects, Images & Applets: Including an image
 */
    case TT_IMG: // 		75	// <img>	Image tag (empty; no children; no end tag)
      if (m_TokenStack.descendant_of (TT_PRE)) break; // Is this possible?
      break;

/* Objects, Images & Applets: Generic inclusion
 */
    case TT_OBJECT: // 		76	// <object>	Object
      if (m_TokenStack.descendant_of (TT_PRE)) break; // Is this possible?
      break;

/* Objects, Images & Applets: Object initialization
 */
    case TT_PARAM: // 		77	// <param>	Option for object (empty; no children; no end tag)
      break;

/* Objects, Images & Applets: Including an applet
 */
    case TT_APPLET: // 		78	// <applet>	Applet
      break;

/* Objects, Images & Applets: Client-side image maps
 */
    case TT_MAP: // 		79	// <map>	Map
      break;
    case TT_AREA: // 		80	// <area>	Area with map (child of <map>; empty; no children; no end tag)
      break;

/* Alignment, Font Styles etc.: Alignment
 */
    case TT_CENTER: // 		81	// <center>	= <div align="center">
      break;

/* Alignment, Font Styles etc.: Font style elements
 */
    case TT_TT: // 		82	// <tt>		Fixed width { set fixed width }
      if (start) m_TextState.setFontFamily ("Courier");
      break;
    case TT_I: // 		83	// <i>		Italic { set italics }
      if (start) m_TextState.setItalic ();
      break;
    case TT_B: // 		84	// <b>		Bold { set bold }
      if (start) m_TextState.setBold ();
      break;
    case TT_BIG: // 		85	// <big>	Large { inc. font size }
      if (m_TokenStack.descendant_of (TT_PRE)) break; // Is this possible?
      if (start) m_TextState.scaleFontSize (1.25f);
      break;
    case TT_SMALL: // 		86	// <small>	Small { dec. font size }
      if (m_TokenStack.descendant_of (TT_PRE)) break; // Is this possible?
      if (start) m_TextState.scaleFontSize (0.8f);
      break;
    case TT_S: // 		87	// <s>		Strike-through { set strike-through }
      if (start) m_TextState.setLineThrough ();
      break;
//  case TT_STRIKE: // 		TT_S	// <strike>	Strike-through { set strike-through }
//    break;
    case TT_U: // 		88	// <u>		Underline { set underline }
      if (start) m_TextState.setUnderline ();
      break;

/* Alignment, Font Styles etc.: Font modifier elements
 */
    case TT_FONT: // 		89	// <font>	Set new font (mother of all...)
      if (start)
	{
	  const char * color = s_attrLookup (atts, "color");
	  if (color)
	    {
	      UT_HashColor hash;
	      const char * hexColor = hash.setColor (color);
	      if (hexColor) m_TextState.setForeground (hexColor + 1);
	    }
	}
      break;
    case TT_BASEFONT: // 	90	// <basefont>	Default font (font sizes calculated relative to base-font)
      break;

/* Alignment, Font Styles etc.: Rules
 */
    case TT_HR: // 		91	// <hr>		Horizontal rule (empty; no children; no end tag)
      if (start) m_inBlock = false;
      break;

/* Frames:
 */
    case TT_FRAMESET: // 	92	// <frameset>	Set of frames { no action }
      break;
    case TT_FRAME: // 		93	// <frame>	A frame (child of frameset) { no action }
      break;
    case TT_NOFRAMES: // 	94	// <noframes>	Frameless version { no action }
      break;
    case TT_IFRAME: // 		95	// <iframe>	Inline frame { no action }
      break;

/* Forms:
 */
    case TT_FORM: // 		96	// <form>	Form { no action }
      break;
    case TT_INPUT: // 		97	// <input>	Input { no action }
      break;
    case TT_BUTTON: // 		98	// <button>	Button { no action }
      break;
    case TT_SELECT: // 		99	// <select>	Select { no action }
      break;
    case TT_OPTGROUP: // 	100	// <optgroup>	Opt. Group { no action }
      break;
    case TT_OPTION: // 		101	// <option>	Option { no action }
      break;
    case TT_TEXTAREA: // 	102	// <textarea>	Text area { no action }
      break;
    case TT_ISINDEX: // 	103	// <isindex>	Index { no action }
      break;
    case TT_LABEL: // 		104	// <label>	Label { no action }
      break;
    case TT_FIELDSET: // 	105	// <fieldset>	Field set { no action }
      break;
    case TT_LEGEND: // 		106	// <legend>	Legend { no action }
      break;

/* Scripts:
 */
    case TT_SCRIPT: // 		107	// <script>	Script { no action }
      break;
    case TT_NOSCRIPT: // 	108	// <noscript>	Alt. to script { no action }
      break;

/* Misc:
 */
    case TT_BDO: // 		109	// <bdo>	BiDi override
      break;

/* Misc:
 */
    case TT_RUBY: // 		110	// <ruby>	Ruby block
    case TT_RT: // 		111	// <rp>		Ruby parenthesis
    case TT_RP: // 		112	// <rt>		Ruby text
	// For now we just want to render any text between these tags
	// Eventually we want to render the <rt> text above the
	// <ruby> text.  The <rp> text will not be rendered but should
	// be retained so it can be exported.
      break;

    default:
      break;
    }
  if (m_error != UT_OK) { m_pHTML->stop (); return; }
}
