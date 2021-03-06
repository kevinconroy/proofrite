/* AbiSource Application Framework
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

#include "xap_Dlg_PluginManager.h"
#include "xap_ModuleManager.h"

#include "ut_vector.h"
#include "ut_assert.h"

XAP_Dialog_PluginManager::XAP_Dialog_PluginManager (XAP_DialogFactory * pDlgFactory, 
													XAP_Dialog_Id id)
	: XAP_Dialog_NonPersistent(pDlgFactory,id, "interface/dialogplugins.html")
{
}

XAP_Dialog_PluginManager::~XAP_Dialog_PluginManager ()
{
}

bool XAP_Dialog_PluginManager::activatePlugin (const char * szName) const
{
	UT_ASSERT (szName);
	bool loaded = XAP_ModuleManager::instance ().loadModule (szName);
	XAP_ModuleManager::instance ().registerPending (); // TODO: handle dependencies?
	return loaded;
}

bool XAP_Dialog_PluginManager::deactivatePlugin (XAP_Module * which) const
{
	UT_ASSERT (which);
	XAP_ModuleManager::instance ().unloadModule (which);
	return true;
}

bool XAP_Dialog_PluginManager::deactivateAllPlugins () const
{
	const UT_Vector * pVec = XAP_ModuleManager::instance().enumModules ();

	UT_ASSERT (pVec);
	if (pVec == 0) return false;

	while (UT_uint32 size = pVec->size ())
	{
		if (XAP_Module * pMod = reinterpret_cast<XAP_Module *>(pVec->getNthItem (0)))
		{
			deactivatePlugin (pMod);
		}
		if (pVec->size () == size) // huh?
		{
			UT_ASSERT (UT_SHOULD_NOT_HAPPEN);
			break;
		}
	}
	return true;
}
