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

#include <gsf/gsf-utils.h>
#include "xap_Module.h"
#include "ie_impexp_OpenWriter.h"

/*****************************************************************************/
/*****************************************************************************/

// completely generic C-interface code to allow this to be a plugin

ABI_PLUGIN_DECLARE("OpenWriter")
  
// we use a reference-counted sniffer
static IE_Imp_OpenWriter_Sniffer * m_imp_sniffer = 0;
static IE_Exp_OpenWriter_Sniffer * m_exp_sniffer = 0;

ABI_FAR_CALL
int abi_plugin_register (XAP_ModuleInfo * mi)
{
  gsf_init ();

  if (!m_imp_sniffer)
      m_imp_sniffer = new IE_Imp_OpenWriter_Sniffer ();
  else
      m_imp_sniffer->ref();
  IE_Imp::registerImporter (m_imp_sniffer);

  // turn on these branches after OO export sort-of works
  if (!m_exp_sniffer)
      m_exp_sniffer = new IE_Exp_OpenWriter_Sniffer ();
  else
      m_exp_sniffer->ref();
  IE_Exp::registerExporter (m_exp_sniffer);
  
  mi->name    = "OpenOffice Writer Filter";
  mi->desc    = "Import/Export OpenOffice Writer documents";
  mi->version = ABI_VERSION_STRING;
  mi->author  = "Dom Lachowicz <cinamod@hotmail.com>";
  mi->usage   = "No Usage";
  
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
  
  IE_Imp::unregisterImporter (m_imp_sniffer);
  if (!m_imp_sniffer->unref())
      m_imp_sniffer = 0;

  IE_Exp::unregisterExporter (m_exp_sniffer);
  if (!m_exp_sniffer->unref())
      m_exp_sniffer = 0;

  gsf_shutdown ();
  
  return 1;
}

ABI_FAR_CALL
int abi_plugin_supports_version (UT_uint32 major, UT_uint32 minor, 
				 UT_uint32 release)
{
  return 1;
}

/****************************************************************************/
/****************************************************************************/
