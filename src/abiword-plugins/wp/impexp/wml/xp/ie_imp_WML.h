/* AbiWord
 * Copyright (C) 1998 AbiSource, Inc.
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


#ifndef IE_IMP_WML_H
#define IE_IMP_WML_H

#include "ie_imp_XML.h"
#include "ut_stack.h"

class PD_Document;

// The importer/reader for WML files.

class ABI_EXPORT IE_Imp_WML_Sniffer : public IE_ImpSniffer
{
	friend class IE_Imp;

public:
	IE_Imp_WML_Sniffer(const char * name);
	virtual ~IE_Imp_WML_Sniffer() {}

	virtual UT_Confidence_t recognizeContents (const char * szBuf, 
									UT_uint32 iNumbytes);
	virtual UT_Confidence_t recognizeSuffix (const char * szSuffix);
	virtual bool getDlgLabels (const char ** szDesc,
							   const char ** szSuffixList,
							   IEFileType * ft);
	virtual UT_Error constructImporter (PD_Document * pDocument,
										IE_Imp ** ppie);

};

class ABI_EXPORT IE_Imp_WML : public IE_Imp_XML
{
public:
	IE_Imp_WML(PD_Document * pDocument);
	virtual ~IE_Imp_WML();

	void			startElement(const XML_Char *name, 
					      const XML_Char **atts);
	void			endElement(const XML_Char *name);

 private:
	void openTable(const XML_Char **atts);
	void closeTable();
	void openRow(const XML_Char **atts);
	void closeRow();
	void openCell(const XML_Char **atts);
	void closeCell();

	UT_Stack mRowStack;
	UT_Stack mColStack;
};

#endif /* IE_IMP_WML_H */
