/* AbiSource Application Framework
 * Copyright (C) 2001 AbiSource, Inc.
 * Copyright (C) 2001 Dom Lachowicz <cinamod@hotmail.com> 
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

#ifndef XAP_MODULE_MANAGER_H
#define XAP_MODULE_MANAGER_H

// Singleton class that will load/unload modules for us

/* pre-emptive dismissal; ut_types.h is needed by just about everything,
 * so even if it's commented out in-file that's still a lot of work for
 * the preprocessor to do...
 */
#ifndef UT_TYPES_H
#include "ut_types.h"
#endif

class UT_Vector;

class XAP_Spider;
class XAP_Module;

class ABI_EXPORT XAP_ModuleManager
{
	friend class XAP_Module;

private:
	XAP_ModuleManager ();

public:
	~XAP_ModuleManager (); // grrr

	static XAP_ModuleManager & instance ();

	bool         loadModule (const char * szFilename);
	UT_uint32    registerPending ();
	void         unloadModule (XAP_Module * module);
private:
	void         unloadModule (UT_sint32 ndx);
public:
	void         unloadUnregistered ();
	void         unloadAllPlugins ();

	const UT_Vector * enumModules () const;

private:

	XAP_ModuleManager(const XAP_ModuleManager &);		// no impl
	void operator=(const XAP_ModuleManager &);	        // no impl

	XAP_Spider * m_spider;

	UT_Vector * m_modules;
};

#endif /* XAP_MODULE_MANAGER_H */
