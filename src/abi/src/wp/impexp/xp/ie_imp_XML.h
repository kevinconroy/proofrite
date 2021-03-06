/* -*- mode: C++; tab-width: 4; c-basic-offset: 4; -*- */

/* AbiWord
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
 */


#ifndef IE_IMP_XML_H
#define IE_IMP_XML_H

#include <stdio.h>

#include "ut_xml.h"

#include "ut_vector.h"
#include "ut_stack.h"
#include "ie_imp.h"
#include "ut_bytebuf.h"
#include "ut_string_class.h"
#include "ut_hash.h"

class PD_Document;

struct ABI_EXPORT xmlToIdMapping {
  char *m_name;
  int m_type;
};

// The importer/reader for reading generic
// XML documents. Currently, the following classes derive from this:
//
// ABW, AWT, GZABW
// DBK
// WML
// XHTML
// XSL-FO
// KWORD 1 && 2 (soon)

class ABI_EXPORT IE_Imp_XML : public IE_Imp, public UT_XML::Listener
{
public:
    IE_Imp_XML(PD_Document * pDocument, bool whiteSignificant);
    virtual ~IE_Imp_XML();

    virtual UT_Error	importFile(const char * szFilename);

    /* (Partial) Implementation of UT_XML::Listener
     *
     * You *must* override these next two methods:
     */
    virtual void startElement (const XML_Char * name, const XML_Char ** atts);
    virtual void endElement (const XML_Char * name);
    /*
     * but you get this one for free:
     */
    virtual void charData (const XML_Char * buffer, int length);

    /* If you don't wish the XML parser to use the standard/default file handler, you
     * can provide your own via an implementation of UT_XML::Reader here:
     */
protected:
    void setReader (UT_XML::Reader * pReader) { m_pReader = pReader; }
private:
    UT_XML::Reader * m_pReader;

public:
    void		    incOperationCount(void) { m_iOperationCount++; }
    UT_uint32		getOperationCount(void) const { return m_iOperationCount; }

protected:
    int             _mapNameToToken (const char * name, xmlToIdMapping * idlist, int len);

    const XML_Char* _getXMLPropValue(const XML_Char *name, const XML_Char **atts);

    UT_uint32		_getInlineDepth(void) const;
    bool			_pushInlineFmt(const XML_Char ** atts);
    void			_popInlineFmt(void);

    typedef enum _parseState { _PS_Init,
			       _PS_Doc,
			       _PS_Sec,
			       _PS_Block,
			       _PS_DataSec,
			       _PS_DataItem,
			       _PS_StyleSec,
			       _PS_Style,
			       _PS_IgnoredWordsSec,
			       _PS_IgnoredWordsItem,
			       _PS_ListSec,
			       _PS_List,
			       _PS_Field,
			       _PS_PageSize,
			       _PS_MetaData,
				   _PS_Meta,
				   _PS_RevisionSec,
				   _PS_Revision
    } ParseState;

 protected:

    // TODO: make us private, refactor code
    UT_Error        m_error;
    ParseState      m_parseState;

    bool			m_bLoadIgnoredWords;
    XML_Char		m_charDataSeen[4];
    UT_uint32		m_lenCharDataSeen;
    UT_uint32		m_lenCharDataExpected;
    UT_uint32		m_iOperationCount;
    bool			m_bSeenCR;
    bool            m_bWhiteSignificant;
    bool            m_bWasSpace;

    UT_Vector		m_vecInlineFmt;
    UT_Stack		m_stackFmtStartIndex;

    UT_ByteBuf		m_currentDataItem;
    XML_Char *		m_currentDataItemName;
    XML_Char *		m_currentDataItemMimeType;
    bool			m_currentDataItemEncoded;

    FILE *			m_fp;
	const char *	m_szFileName;

    UT_String		m_currentMetaDataName;
	UT_uint32       m_currentRevisionId;

	UT_StringPtrMap m_tokens;
};

#endif /* IE_IMP_XML_H */
