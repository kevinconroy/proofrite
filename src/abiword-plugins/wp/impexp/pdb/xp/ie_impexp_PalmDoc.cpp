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


#include "ie_imp_PalmDoc.h"
#include "ie_exp_PalmDoc.h"
#include "xap_Module.h"

ABI_PLUGIN_DECLARE("PalmDoc")

#define PLUGIN_NAME "AbiPalmDoc::PalmDoc"

// we use a reference-counted sniffer
static IE_Imp_PalmDoc_Sniffer * m_impSniffer = 0;
static IE_Exp_PalmDoc_Sniffer * m_expSniffer = 0;

ABI_FAR_CALL
int abi_plugin_register (XAP_ModuleInfo * mi)
{

	if (!m_impSniffer)
	{
		m_impSniffer = new IE_Imp_PalmDoc_Sniffer (PLUGIN_NAME);
	}
	else
	{
		m_impSniffer->ref();
	}

	if (!m_expSniffer)
	{
		m_expSniffer = new IE_Exp_PalmDoc_Sniffer (PLUGIN_NAME);
	}
	else
	{
		m_expSniffer->ref();
	}

	mi->name = "PalmDoc Importer/Exporter";
	mi->desc = "Import/Export PalmDoc Documents";
	mi->version = ABI_VERSION_STRING;
	mi->author = "Abi the Ant";
	mi->usage = "No Usage";

	IE_Imp::registerImporter (m_impSniffer);
	IE_Exp::registerExporter (m_expSniffer);
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

	UT_ASSERT (m_impSniffer);
	UT_ASSERT (m_expSniffer);

	IE_Imp::unregisterImporter (m_impSniffer);
	if (!m_impSniffer->unref())
	{
		m_impSniffer = 0;
	}
	IE_Exp::unregisterExporter (m_expSniffer);
	if (!m_expSniffer->unref())
	{
		m_expSniffer = 0;
	}

	return 1;
}

ABI_FAR_CALL
int abi_plugin_supports_version (UT_uint32 major, UT_uint32 minor, 
								 UT_uint32 release)
{
  return 1;
}

