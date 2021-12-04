/* AbiWord
 * Copyright (C) 2000 AbiSource, Inc.
 * Copyright (C) 2000, 2001 Frodo Looijaard <frodol@dds.nl>
 * Copyright (C) 2002 Dom Lachowicz
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

// completely generic code to allow this to be a plugin

#include "ie_imp_Psion.h"
#include "ie_exp_Psion.h"
#include "xap_Module.h"

ABI_PLUGIN_DECLARE("Psion")

#define PLUGIN_WORD "AbiPsion::Psion (Word)"
#define PLUGIN_TEXT "AbiPsion::Psion (Text)"

// we use a reference-counted sniffer
static IE_Exp_Psion_Word_Sniffer * m_expword_sniffer = 0;
static IE_Exp_Psion_TextEd_Sniffer * m_exptexted_sniffer = 0;
static IE_Imp_Psion_Word_Sniffer * m_impword_sniffer = 0;
static IE_Imp_Psion_TextEd_Sniffer * m_imptexted_sniffer = 0;

ABI_FAR_CALL
int abi_plugin_register (XAP_ModuleInfo * mi)
{

	if (!m_expword_sniffer && !m_exptexted_sniffer)
	{
		m_expword_sniffer = new IE_Exp_Psion_Word_Sniffer (PLUGIN_WORD);
		m_exptexted_sniffer = new IE_Exp_Psion_TextEd_Sniffer (PLUGIN_TEXT);
	}
	else
	{
		m_expword_sniffer->ref();
		m_exptexted_sniffer->ref();
	}

	if (!m_impword_sniffer && !m_imptexted_sniffer)
	{
		m_impword_sniffer = new IE_Imp_Psion_Word_Sniffer (PLUGIN_WORD);
		m_imptexted_sniffer = new IE_Imp_Psion_TextEd_Sniffer (PLUGIN_TEXT);
	}
	else
	{
		m_impword_sniffer->ref();
		m_imptexted_sniffer->ref();
	}

	mi->name = "Psion Import/Export";
	mi->desc = "Read and Write Psion Documents";
	mi->version = ABI_VERSION_STRING;
	mi->author = "Abi the Ant";
	mi->usage = "No Usage";

	IE_Exp::registerExporter (m_expword_sniffer);
	IE_Exp::registerExporter (m_exptexted_sniffer);

	IE_Imp::registerImporter (m_impword_sniffer);
	IE_Imp::registerImporter (m_imptexted_sniffer);

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

	UT_ASSERT (m_expword_sniffer && m_exptexted_sniffer);

	IE_Exp::unregisterExporter (m_expword_sniffer);
	IE_Exp::unregisterExporter (m_exptexted_sniffer);
	if (!m_expword_sniffer->unref() && !m_exptexted_sniffer->unref())
	{
		m_expword_sniffer = 0;
		m_exptexted_sniffer = 0;
	}

	UT_ASSERT (m_impword_sniffer && m_imptexted_sniffer);

	IE_Imp::unregisterImporter (m_impword_sniffer);
	IE_Imp::unregisterImporter (m_imptexted_sniffer);
	if (!m_impword_sniffer->unref() || m_imptexted_sniffer->unref())
	{
		m_impword_sniffer = 0;
		m_imptexted_sniffer = 0;
	}

	return 1;
}

ABI_FAR_CALL
int abi_plugin_supports_version (UT_uint32 major, UT_uint32 minor, 
				 UT_uint32 release)
{
  return 1;
}
