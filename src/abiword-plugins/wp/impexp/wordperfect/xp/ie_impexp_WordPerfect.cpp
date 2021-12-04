/* AbiWord
 * Copyright (C) 2001 AbiSource, Inc.
 * Copyright (C) 2002 Marc Maurer (j.m.maurer@student.utwente.nl)
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

/* See bug 1764
 * "This product is not manufactured, approved, or supported by 
 * Corel Corporation or Corel Corporation Limited."
 */

#include "ie_impexp_WordPerfect.h"

#define PLUGIN_NAME "AbiWordPerfect::WordPerfect"

ABI_PLUGIN_DECLARE("WordPerfect")
static IE_Imp_WordPerfect_Sniffer * m_ImpSniffer = 0;
static IE_Exp_WordPerfect_Sniffer * m_ExpSniffer = 0;

ABI_FAR_CALL
int abi_plugin_register (XAP_ModuleInfo * mi)
{

	if (!m_ImpSniffer)
	{
		m_ImpSniffer = new IE_Imp_WordPerfect_Sniffer (PLUGIN_NAME);
	}
	else
	{
		m_ImpSniffer->ref();
	}

	if (!m_ExpSniffer)
	{
		m_ExpSniffer = new IE_Exp_WordPerfect_Sniffer (PLUGIN_NAME);
	}
	else
	{
		m_ExpSniffer->ref();
	}

	UT_ASSERT (m_ImpSniffer);
	UT_ASSERT (m_ExpSniffer);

	mi->name    = "WordPerfect 6/7/8/9 (tm) Importer/Exporter";
	mi->desc    = "Import/Export WordPerfect 6/7/8/9 (tm) Documents";
	mi->version = ABI_VERSION_STRING;
	mi->author  = "William Lachance, Marc Maurer";
	mi->usage   = "No Usage";

	IE_Imp::registerImporter (m_ImpSniffer);
	IE_Exp::registerExporter (m_ExpSniffer);
	return 1;
}

ABI_FAR_CALL
int abi_plugin_unregister (XAP_ModuleInfo * mi)
{
	mi->name    = 0;
	mi->desc    = 0;
	mi->version = 0;
	mi->author  = 0;
	mi->usage   = 0;

	UT_ASSERT (m_ImpSniffer);
	UT_ASSERT (m_ExpSniffer);

	IE_Imp::unregisterImporter (m_ImpSniffer);
	IE_Exp::unregisterExporter (m_ExpSniffer);
	
	if (!m_ImpSniffer->unref())
	{
	
		m_ImpSniffer = 0;
	}
	
	if (!m_ExpSniffer->unref())
	{
		m_ExpSniffer = 0;
	}

	return 1;
}

ABI_FAR_CALL
int abi_plugin_supports_version (UT_uint32 major, UT_uint32 minor, 
								 UT_uint32 release)
{
  return 1;
}
