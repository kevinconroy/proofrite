/* AbiWord
 * Copyright (C) 2001 Dom Lachowicz
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

#include "ie_exp_Text.h"
#include "ut_string.h"
#include "ut_assert.h"

/*****************************************************************/
/*****************************************************************/

class ABI_EXPORT IE_Exp_EML : public IE_Exp_Text
{
public:

  IE_Exp_EML(PD_Document * pDocument)
    : IE_Exp_Text(pDocument, false)
  {
  }

  virtual ~IE_Exp_EML ()
  {
  }

protected:

  virtual UT_Error _writeDocument(void)
  {
    write ("X-Unsent: 1\r\n\r\n");
    return IE_Exp_Text::_writeDocument ();
  }
};

/*****************************************************************/
/*****************************************************************/

class ABI_EXPORT IE_Exp_EML_Sniffer :
  public IE_ExpSniffer
{
public:
  IE_Exp_EML_Sniffer () :
    IE_ExpSniffer("AbiEML::EML")
  {
    // 
  }

  bool recognizeSuffix(const char * szSuffix)
  {
    return (!UT_stricmp(szSuffix,".eml"));
  }
  
  UT_Error constructExporter(PD_Document * pDocument,
			     IE_Exp ** ppie)
  {
	IE_Exp_EML * p = new IE_Exp_EML(pDocument);
	*ppie = p;
	return UT_OK;
  }
  
  bool getDlgLabels(const char ** pszDesc,
		    const char ** pszSuffixList,
		    IEFileType * ft)
  {
    *pszDesc = "Outlook Express Email (.eml)";
    *pszSuffixList = "*.eml";
    *ft = getFileType();
    return true;
  }
};

/*****************************************************************/
/*****************************************************************/

#include "xap_Module.h"

ABI_PLUGIN_DECLARE("EML")

// we use a reference-counted sniffer
static IE_Exp_EML_Sniffer * m_sniffer = 0;

ABI_FAR_CALL
int abi_plugin_register (XAP_ModuleInfo * mi)
{

	if (!m_sniffer)
	{
		m_sniffer = new IE_Exp_EML_Sniffer ();
	}
	else
	{
		m_sniffer->ref();
	}

	mi->name = "Outlook Express EML Exporter";
	mi->desc = "Export AbiWord Documents to email clients";
	mi->version = ABI_VERSION_STRING;
	mi->author = "Dom Lachowicz <cinamod@hotmail.com>";
	mi->usage = "No Usage";

	IE_Exp::registerExporter (m_sniffer);
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

	IE_Exp::unregisterExporter (m_sniffer);
	if (!m_sniffer->unref())
	{
		m_sniffer = 0;
	}

	return 1;
}

ABI_FAR_CALL
int abi_plugin_supports_version (UT_uint32 major, UT_uint32 minor, 
				 UT_uint32 release)
{
  return 1;
}
