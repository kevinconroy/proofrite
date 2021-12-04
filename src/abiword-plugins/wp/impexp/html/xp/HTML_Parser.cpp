/* AbiWord: HTML_Parser class, uses libxml2
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

#include <libxml/parser.h>
#include <libxml/parserInternals.h>

#include "HTML_Parser.h"

static void _startElement (void * userData, const xmlChar * name, const xmlChar ** atts);
static void _endElement (void * userData, const xmlChar * name);
static void _charData (void * userData, const xmlChar * buffer, int length);

static xmlEntityPtr _getEntity (void * userData, const xmlChar * name);

HTML_Parser::HTML_Parser () :
  m_pListener(0)
{
  //
}

HTML_Parser::~HTML_Parser ()
{
  //
}

/* WARNING: this sniff mechanism is overly tolerant. libxml2's strength in
 *          parsing is a weakness in detection.
 */
bool HTML_Parser::sniff (const char * buffer, int length)
{
  if ((length == 0) || (buffer == 0)) return false;

  htmlSAXHandler hdl;
  htmlParserCtxtPtr ctxt;

  hdl.internalSubset = NULL;
  hdl.isStandalone = NULL;
  hdl.hasInternalSubset = NULL;
  hdl.hasExternalSubset = NULL;
  hdl.resolveEntity = NULL;
  hdl.getEntity = _getEntity;
  hdl.entityDecl = NULL;
  hdl.notationDecl = NULL;
  hdl.attributeDecl = NULL;
  hdl.elementDecl = NULL;
  hdl.unparsedEntityDecl = NULL;
  hdl.setDocumentLocator = NULL;
  hdl.startDocument = NULL;
  hdl.endDocument = NULL;
  hdl.startElement = _startElement;
  hdl.endElement = _endElement;
  hdl.reference = NULL;
  hdl.characters = _charData;
  hdl.ignorableWhitespace = NULL;
  hdl.processingInstruction = NULL;
  hdl.comment = NULL;
  hdl.warning = NULL;
  hdl.error = NULL;
  hdl.fatalError = NULL;
  hdl.getParameterEntity = NULL;
  hdl.cdataBlock = NULL;
  hdl.externalSubset = NULL;

  m_bStopped = false;
  m_bValid = false;

  // Watch out for libxml2 bug - keep initial buffer << 4000 for safety
  int initial_length = (length <= 128) ? length : 128;

  ctxt = htmlCreatePushParserCtxt (&hdl, (void *) this, buffer, (int) initial_length, 0, XML_CHAR_ENCODING_NONE);
  if (ctxt == 0) return false;

  int length_remaining = length - initial_length;
  const char * ptr = buffer + initial_length;

  while (length_remaining && !m_bValid && !m_bStopped)
    {
      int parse_length = (length_remaining <= 128) ? length_remaining : 127;
      if (htmlParseChunk (ctxt, ptr, parse_length, 0))
	{
	  m_bStopped = true;
	  break;
	}
      length_remaining -= parse_length;
      ptr += parse_length;
    }
  if (!m_bValid && !m_bStopped) htmlParseChunk (ctxt, ptr, 0, 1);

  ctxt->sax = 0;
  htmlFreeParserCtxt (ctxt);

  if (m_bStopped) return false; // Suggests (very) invalid HTML

  return m_bValid;
}

bool HTML_Parser::parse (const char * filename)
{
  if (filename == 0) return false;

  FILE * in = fopen (filename, "rb");
  if (in == 0) return false;

  htmlSAXHandler hdl;
  htmlParserCtxtPtr ctxt = 0;

  hdl.internalSubset = NULL;
  hdl.isStandalone = NULL;
  hdl.hasInternalSubset = NULL;
  hdl.hasExternalSubset = NULL;
  hdl.resolveEntity = NULL;
  hdl.getEntity = _getEntity;
  hdl.entityDecl = NULL;
  hdl.notationDecl = NULL;
  hdl.attributeDecl = NULL;
  hdl.elementDecl = NULL;
  hdl.unparsedEntityDecl = NULL;
  hdl.setDocumentLocator = NULL;
  hdl.startDocument = NULL;
  hdl.endDocument = NULL;
  hdl.startElement = _startElement;
  hdl.endElement = _endElement;
  hdl.reference = NULL;
  hdl.characters = _charData;
  hdl.ignorableWhitespace = NULL;
  hdl.processingInstruction = NULL;
  hdl.comment = NULL;
  hdl.warning = NULL;
  hdl.error = NULL;
  hdl.fatalError = NULL;
  hdl.getParameterEntity = NULL;
  hdl.cdataBlock = NULL;
  hdl.externalSubset = NULL;

  m_bStopped = false;
  m_bValid = false;

  // Watch out for libxml2 bug - keep initial buffer << 4000 for safety
  char buffer[2048];
  int length = fread (buffer, 1, 2048, in);
  int done = (length < 2048) ? 1 : 0;

  if (length)
    {
      ctxt = htmlCreatePushParserCtxt (&hdl, (void *) this, buffer, length, 0, XML_CHAR_ENCODING_NONE);
      if (ctxt == 0) m_bStopped = true;
    }
  if (ctxt)
    {
      while (!done && !m_bStopped)
	{
	  length = fread (buffer, 1, 2048, in);
	  done = (length < 2048) ? 1 : 0;
	  if (htmlParseChunk (ctxt, buffer, length, 0))
	    {
	      m_bStopped = true;
	      break;
	    }
	}
      if (!m_bStopped) htmlParseChunk (ctxt, buffer, 0, 1);
      ctxt->sax = 0;
      htmlFreeParserCtxt (ctxt);
    }
  fclose (in);

  return !m_bStopped;
}

static void _startElement (void * userData, const xmlChar * name, const xmlChar ** atts)
{
  HTML_Parser * pHTML = (HTML_Parser *) userData;

  /* libxml2 can supply atts == 0, which is a little at variance to what is expected...
   */
  const char * ptr = 0;
  const char ** new_atts = (const char **) atts;
  if (atts == 0) new_atts = &ptr;

  pHTML->startElement ((const char *) name, new_atts);
}

static void _endElement (void * userData, const xmlChar * name)
{
  HTML_Parser * pHTML = (HTML_Parser *) userData;
  pHTML->endElement ((const char *) name);
}

static void _charData (void * userData, const xmlChar * buffer, int length)
{
  HTML_Parser * pHTML = (HTML_Parser *) userData;
  pHTML->charData ((const char *) buffer, length);
}

static xmlEntityPtr _getEntity (void * userData, const xmlChar * name)
{
  return xmlGetPredefinedEntity (name);
}

void HTML_Parser::startElement (const char * name, const char ** atts)
{
  if (m_bStopped) return;
  if (!m_bValid)
    {
      if ((strcmp (name, "html") == 0) || (strcmp (name, "html:html") == 0))
	{
	  m_bValid = true;
	}
      else
	{
	  m_bStopped = true;
	  return;
	}
    }
  if (m_pListener) m_pListener->startElement (name, atts);
}

void HTML_Parser::endElement (const char * name)
{
  if (m_bStopped) return;
  if (m_pListener) m_pListener->endElement (name);
}

void HTML_Parser::charData (const char * buffer, int length)
{
  if (m_bStopped) return;
  if (m_pListener) m_pListener->charData (buffer, length);
}
