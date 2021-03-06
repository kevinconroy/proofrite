/* AbiSource Application Framework
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

// TODO add code to do an auto save anytime anything is changed.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ut_debugmsg.h"
#include "ut_growbuf.h"
#include "ut_string.h"
#include "ut_string_class.h"
#include "xap_Prefs.h"

struct xmlToIdMapping {
	char *m_name;
	int m_type;
};

static  UT_sint32 compareStrings(const void * ppS1, const void * ppS2)
{
	const char ** sz1 = (const char **) (ppS1);
	const char ** sz2 = (const char **) (ppS2);
	return UT_stricmp(*sz1, *sz2);
}

enum
{
	TT_ABIPREFERENCES,
	TT_GEOMETRY,
	TT_PLUGIN,
	TT_RECENT,
	TT_SCHEME,
	TT_SELECT
};

// keep these in alphabetical order
static struct xmlToIdMapping s_Tokens[] =
{
	{ "AbiPreferences",		TT_ABIPREFERENCES },
	{ "Geometry",			TT_GEOMETRY },
	{ "Plugin",				TT_PLUGIN },
	{ "Recent",				TT_RECENT },
	{ "Scheme",				TT_SCHEME },
	{ "Select",				TT_SELECT }
};

/*****************************************************************/

XAP_PrefsScheme::XAP_PrefsScheme( XAP_Prefs *pPrefs, const XML_Char * szSchemeName)
	: m_hash(41)
{
	m_pPrefs = pPrefs;
	m_uTick = 0;

	if (szSchemeName && *szSchemeName)
		UT_XML_cloneString((XML_Char *&)m_szName,szSchemeName);
	else
		m_szName = NULL;
}

XAP_PrefsScheme::~XAP_PrefsScheme(void)
{
	FREEP(m_szName);

	// loop through and free the values
	UT_Vector * pVec = m_hash.enumerate ();

	UT_uint32 cnt = pVec->size();

	for (UT_uint32 i = 0 ; i < cnt; i++)
	  {
	    char * val = (char *)pVec->getNthItem (i);
	    FREEP(val);
	  }

	DELETEP(pVec);
}

const XML_Char * XAP_PrefsScheme::getSchemeName(void) const
{
	return m_szName;
}

bool XAP_PrefsScheme::setSchemeName(const XML_Char * szNewSchemeName)
{
	FREEP(m_szName);
	return UT_XML_cloneString(m_szName,szNewSchemeName);
}

bool XAP_PrefsScheme::setValue(const XML_Char * szKey, const XML_Char * szValue)
{
	++m_uTick;
	const void * pEntry = m_hash.pick(szKey);
	if (pEntry)
	{
		if (strcmp((const char*)szValue,(const char *)pEntry) == 0)
			return true;				// equal values, no changes required
		
		FREEP(pEntry);
		m_hash.set (szKey, 
			    (void *)UT_strdup (szValue));
	}
	else
	{
		// otherwise, need to add a new entry
		m_hash.insert(szKey,
			      (void *)UT_strdup(szValue));
	}

	m_pPrefs->_markPrefChange( szKey );

	return true;
}

bool XAP_PrefsScheme::setValueBool(const XML_Char * szKey, bool bValue)
{
	return setValue(szKey, (XML_Char*) ((bValue) ? "1" : "0"));
}

bool XAP_PrefsScheme::getValue(const XML_Char * szKey, const XML_Char ** pszValue) const
{
	const void *pEntry = m_hash.pick(szKey);
	if (!pEntry)
		return false;

	if (pszValue)
		*pszValue = (const XML_Char*)pEntry;
	return true;
}

bool XAP_PrefsScheme::getValue(const UT_String &stKey, UT_String &stValue) const
{
	const void * pEntry = m_hash.pick(stKey);
	if (!pEntry)
		return false;

	stValue = (const char *)pEntry;
	return true;
}

bool XAP_PrefsScheme::getValueBool(const XML_Char * szKey, bool * pbValue) const
{
	*pbValue = false;				// assume something
	
	const XML_Char * szValue = NULL;
	if (!getValue(szKey,&szValue))
		return false;				// bogus keyword ??

	if (!szValue || !*szValue)
		return false;				// no value for known keyword ??

	switch (szValue[0])
	{
	case '1':
	case 't':
	case 'T':
	case 'y':
	case 'Y':
		*pbValue = true;
		return true;

	default:
		*pbValue = false;
		return true;
	}
}

bool XAP_PrefsScheme::getNthValue(UT_uint32 k, const XML_Char ** pszKey, const XML_Char ** pszValue) const
{
	if (k >= (UT_uint32)m_hash.size())
		return false;
//
// Output prefs in alphabetic Order.
//
	UT_Vector vecKeys;
	UT_Vector * vecD = m_hash.keys();
	UT_uint32 i=0;
	vecKeys.clear();
	for(i=0; i< vecD->getItemCount(); i++)
	{
		vecKeys.addItem((void *) static_cast<UT_String *>(vecD->getNthItem(i))->c_str());
	}
	vecKeys.qsort(compareStrings);
	delete vecD;
	const char * szKey = NULL;
	const char * szValue = NULL;
	szKey = (const XML_Char *) vecKeys.getNthItem(k);
	szValue = (const XML_Char *)  m_hash.pick(szKey);
	if(szValue && *szValue)
	{
		*pszKey = szKey;
		*pszValue = szValue;
		return true;
	}
	else
	{
		*pszKey = NULL;
		*pszValue = NULL;
		return false;
	}
}

/*****************************************************************/

bool XAP_Prefs::getAutoSavePrefs(void) const
{
	return m_bAutoSavePrefs;
}

void XAP_Prefs::setAutoSavePrefs(bool bAuto)
{
	m_bAutoSavePrefs = bAuto;

	// TODO if turning autosave on, we should do a save now....
	// TODO if was on and turning off, should we save it now ??
}

/*****************************************************************/

bool XAP_Prefs::getUseEnvLocale(void) const
{
	return m_bUseEnvLocale;
}

void XAP_Prefs::setUseEnvLocale(bool bUse)
{
	m_bUseEnvLocale = bUse;
}

/*****************************************************************/

UT_uint32 XAP_Prefs::getMaxRecent(void) const
{
	return m_iMaxRecent;
}

void XAP_Prefs::setMaxRecent(UT_uint32 k)
{
	UT_ASSERT(k<=XAP_PREF_LIMIT_MaxRecent);

	if (k > XAP_PREF_LIMIT_MaxRecent)
		k = XAP_PREF_LIMIT_MaxRecent;

	m_iMaxRecent = k;
}

UT_uint32 XAP_Prefs::getRecentCount(void) const
{
	return m_vecRecent.getItemCount();
}

const char * XAP_Prefs::getRecent(UT_uint32 k) const
{
	// NB: k is one-based
	UT_ASSERT(k <= m_iMaxRecent);

	const char * pRecent = NULL;
	
	if (k <= m_vecRecent.getItemCount())
	{
		pRecent = (const char *) m_vecRecent.getNthItem(k - 1);
	}

	return pRecent;
}
	
void XAP_Prefs::addRecent(const char * szRecent)
{
	const char * sz;
	bool bFound = false;

	if (m_iMaxRecent == 0)
		return;		// NOOP

	// was it already here? 
	for (UT_uint32 i=0; i<m_vecRecent.getItemCount(); i++)
	{
		sz = (const char *)m_vecRecent.getNthItem(i);
		if ((sz==szRecent) || !strcmp(sz, szRecent))
		{
			// yep, we're gonna move it up
			m_vecRecent.deleteNthItem(i);
			bFound = true;
			break;
		}
	}

	if (!bFound)
	{
		// nope.  make a new copy to store
		UT_cloneString((char *&)sz, szRecent);
	}

	m_vecRecent.insertItemAt((void *)sz, 0);
	_pruneRecent();
}

void XAP_Prefs::removeRecent(UT_uint32 k)
{
	UT_ASSERT(k>0);
	UT_ASSERT(k<=getRecentCount());

	char * sz = (char *) m_vecRecent.getNthItem(k-1);
	FREEP(sz);

	m_vecRecent.deleteNthItem(k-1);
}

void XAP_Prefs::_pruneRecent(void)
{
	UT_sint32 i;
	UT_uint32 count = getRecentCount();

	if (m_iMaxRecent == 0)
	{
		// nuke the whole thing
		for (i = (signed) count; i > 0 ; i--)
		{
			char * sz = (char *) m_vecRecent.getNthItem(i-1);
			FREEP(sz);
		}

		m_vecRecent.clear();
	}
	else if (count > m_iMaxRecent)
	{
		// prune entries past m_iMaxRecent
		for (i = (signed) count; i > (signed) m_iMaxRecent; i--)
			removeRecent(i);
	}
}
/*****************************************************************/

bool XAP_Prefs::setGeometry(UT_sint32 posx, UT_sint32 posy, UT_uint32 width, UT_uint32 height, UT_uint32 flags) 
{
	m_parserState.m_bFoundGeometry = true;
	m_geom.m_width = width;
	m_geom.m_height = height;
	m_geom.m_posx = posx;
	m_geom.m_posy = posy;
	m_geom.m_flags = flags;

	//For now we turn on the autosave of prefs so that we can save this setting ... is this bad?
	setAutoSavePrefs(true);	
	
	return true;
}

bool XAP_Prefs::getGeometry(UT_sint32 *posx, UT_sint32 *posy, UT_uint32 *width, UT_uint32 *height, UT_uint32 *flags)
{
	if (m_parserState.m_bFoundGeometry == false) {
		return false;
	}
	if (width) { 
		*width = m_geom.m_width; 
	}
	if (height) {
		*height = m_geom.m_height;
	}
	if (posx) {
		*posx = m_geom.m_posx;
	}
	if (posy) {
		*posy = m_geom.m_posy;
	}
	if (flags) {
		*flags = m_geom.m_flags;
	}
	return true;
}


/*****************************************************************/

XAP_Prefs::XAP_Prefs(XAP_App * pApp) 
	: m_ahashChanges( 20 )
{
	m_pApp = pApp;
	m_bAutoSavePrefs = (atoi(XAP_PREF_DEFAULT_AutoSavePrefs) ? true : false);
	m_bUseEnvLocale = (atoi(XAP_PREF_DEFAULT_UseEnvLocale) ? true : false);
	m_currentScheme = NULL;
	m_builtinScheme = NULL;
	m_iMaxRecent = atoi(XAP_PREF_DEFAULT_MaxRecent);
	m_bInChangeBlock = false;

	memset(&m_geom, 0, sizeof(m_geom));

	// NOTE: since constructors cannot report malloc
	// NOTE: failures (and since it is virtual back
	// NOTE: to the application), our creator must call
	// NOTE: loadBuiltinPrefs().

	// NOTE: we do not initialize the values in m_parserState
	// NOTE: since they are only used by the parser, it can
	// NOTE: initialize them.
}

XAP_Prefs::~XAP_Prefs(void)
{
	UT_VECTOR_PURGEALL(XAP_PrefsScheme *, m_vecSchemes);
	UT_VECTOR_PURGEALL(XAP_PrefsScheme *, m_vecPluginSchemes);
	UT_VECTOR_FREEALL(char *, m_vecRecent);
	UT_VECTOR_PURGEALL(tPrefsListenersPair *, m_vecPrefsListeners);
}

/*****************************************************************/

XAP_PrefsScheme * XAP_Prefs::_getNthScheme(UT_uint32 k, const UT_Vector &vecSchemes) const
{
	UT_uint32 kLimit = vecSchemes.getItemCount();
	if (k < kLimit)
		return (XAP_PrefsScheme *)vecSchemes.getNthItem(k);
	else
		return NULL;
}

XAP_PrefsScheme * XAP_Prefs::getNthScheme(UT_uint32 k) const
{
	return _getNthScheme(k, m_vecSchemes);
}

XAP_PrefsScheme * XAP_Prefs::getNthPluginScheme(UT_uint32 k) const
{
	return _getNthScheme(k, m_vecPluginSchemes);
}

XAP_PrefsScheme * XAP_Prefs::getScheme(const XML_Char * szSchemeName) const
{
	UT_uint32 kLimit = m_vecSchemes.getItemCount();
	UT_uint32 k;

	for (k=0; k<kLimit; k++)
	{
		XAP_PrefsScheme * p = getNthScheme(k);
		UT_ASSERT(p);
		if (strcmp((const char*)szSchemeName,(const char*)p->getSchemeName()) == 0)
			return p;
	}

	return NULL;
}

XAP_PrefsScheme * XAP_Prefs::getPluginScheme(const XML_Char * szSchemeName) const
{
	UT_uint32 kLimit = m_vecPluginSchemes.getItemCount();
	UT_uint32 k;

	for (k=0; k<kLimit; k++)
	{
		XAP_PrefsScheme * p = getNthPluginScheme(k);
		UT_ASSERT(p);
		if (strcmp((const char*)szSchemeName,(const char*)p->getSchemeName()) == 0)
			return p;
	}

	return NULL;
}

bool XAP_Prefs::addScheme(XAP_PrefsScheme * pNewScheme)
{
	const XML_Char * szBuiltinSchemeName = getBuiltinSchemeName();
	const XML_Char * szThisSchemeName = pNewScheme->getSchemeName();
	
	if (strcmp((const char*)szThisSchemeName, (const char*)szBuiltinSchemeName) == 0)
	{
		UT_ASSERT(m_builtinScheme == NULL);
		m_builtinScheme = pNewScheme;
	}
	
	return (m_vecSchemes.addItem(pNewScheme) == 0);
}

bool XAP_Prefs::addPluginScheme(XAP_PrefsScheme * pNewScheme)
{
	return (m_vecPluginSchemes.addItem(pNewScheme) == 0);
}


XAP_PrefsScheme * XAP_Prefs::getCurrentScheme(bool bCreate)
{
	if (bCreate)
	{
		// the builtin scheme is not updatable, 
		// so we may need to create one that is
		if ( !strcmp((const char*)m_currentScheme->getSchemeName(), "_builtin_") ) 
		{
	

		const XML_Char new_name[] = "_custom_";

			if (setCurrentScheme(new_name))
			{
				// unused _custom_ scheme is lying around, so recycle it
				UT_ASSERT(UT_TODO);

				// HYP: reset the current scheme's hash table contents?
				// ALT: replace the existing scheme with new empty one
			}
			else
			{
				// we need to create it
				XAP_PrefsScheme * pNewScheme = new XAP_PrefsScheme(this, new_name);
				UT_ASSERT(pNewScheme);	
				addScheme(pNewScheme);
				setCurrentScheme(new_name);
			}
		}
	}

	return m_currentScheme;
}

bool XAP_Prefs::setCurrentScheme(const XML_Char * szSchemeName)
{
	// set the current scheme.

	// TODO notify the application that the scheme has changed

	XAP_PrefsScheme * p = getScheme(szSchemeName);
	if (!p)
		return false;

	UT_DEBUGMSG(("Preferences::setCurrentScheme [%s].\n",szSchemeName));
	
	m_currentScheme = p;
	return true;
}

/*****************************************************************/
static const XML_Char DEBUG_PREFIX[] = "DeBuG";  // case insensitive
static const XML_Char NO_PREF_VALUE[] = "";

bool XAP_Prefs::getPrefsValue(const XML_Char * szKey, const XML_Char ** pszValue) const
{
	// a convenient routine to get a name/value pair from the current scheme

	UT_ASSERT(m_currentScheme);

	if (m_currentScheme->getValue(szKey,pszValue))
		return true;
	if (m_builtinScheme->getValue(szKey,pszValue))
		return true;
	// It is legal for there to be arbitrary preference tags that start with 
	// "Debug", and Abi apps won't choke.  The idea is that developers can use
	// these to selectively trigger development-time behaviors.
	if (UT_XML_strnicmp(szKey, DEBUG_PREFIX, sizeof(DEBUG_PREFIX) - 1) == 0)
	{
		*pszValue = NO_PREF_VALUE;
		return true;
	}

	UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
	return false;
}

bool XAP_Prefs::getPrefsValue(const UT_String &stKey, UT_String &stValue) const
{
	UT_ASSERT(m_currentScheme);

	if (m_currentScheme->getValue(stKey, stValue))
		return true;
	if (m_builtinScheme->getValue(stKey, stValue))
		return true;
	
	// It is legal for there to be arbitrary preference tags that start with 
	// "Debug", and Abi apps won't choke.  The idea is that developers can use
	// these to selectively trigger development-time behaviors.
	if (UT_XML_strnicmp(stKey.c_str(), DEBUG_PREFIX, sizeof(DEBUG_PREFIX) - 1) == 0)
	{
		stValue = NO_PREF_VALUE;
		return true;
	}

	UT_DEBUGMSG(("JCA: key: [%s] Value: [%s]", stKey.c_str(), stValue.c_str()));
	UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
	return false;
}

bool XAP_Prefs::getPrefsValueBool(const XML_Char * szKey, bool * pbValue) const
{
	// a convenient routine to get a name/value pair from the current scheme

	UT_ASSERT(m_currentScheme);

	if (m_currentScheme->getValueBool(szKey,pbValue))
		return true;
	if (m_builtinScheme->getValueBool(szKey,pbValue))
		return true;
	// It is legal for there to be arbitrary preference tags that start with 
	// "Debug", and Abi apps won't choke.  The idea is that developers can use
	// these to selectively trigger development-time behaviors.
	if (UT_XML_strnicmp(szKey, DEBUG_PREFIX, sizeof(DEBUG_PREFIX) - 1) == 0)
	{
		*pbValue = false;
		return true;
	}

	UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
	return false;
}


#ifndef __MRC__
static int n_compare (const char *name, const xmlToIdMapping *id)
{
	return strcmp (name, id->m_name);
}
#else
extern "C" static int n_compare (const void *name, const void *id)
{
	return strcmp ((const char *)name, ((const xmlToIdMapping *)id)->m_name);
}
#endif


/*****************************************************************/

void XAP_Prefs::startElement(const XML_Char *name, const XML_Char **atts)
{
	if (m_bLoadSystemDefaultFile) /* redirection - used to happen earlier */
	{
		_startElement_SystemDefaultFile (name, atts);
		return;
	}

	XAP_PrefsScheme * pNewScheme = NULL; // must be freed
	
	if (!m_parserState.m_parserStatus)		// eat if already had an error
		return;

	xmlToIdMapping * id = NULL;
	id = (xmlToIdMapping *)bsearch ((const void*)name, (const void*)s_Tokens,
									sizeof(s_Tokens)/sizeof(xmlToIdMapping),
									sizeof (xmlToIdMapping),
#ifndef __MRC__
									(int (*)(const void*, const void*))
#endif
									n_compare);
	if (!id)
		return;

	switch (id->m_type)
	{
		case TT_ABIPREFERENCES:
		{
		m_parserState.m_bFoundAbiPreferences = true;

		// we expect something of the form:
		// <AbiPreferences app="AbiWord" ver="1.0">...</AbiPreferences>

		const XML_Char ** a = atts;
		while (a && *a)
		{
			UT_ASSERT(a[1] && *a[1]);	// require a value for each attribute keyword

			if (strcmp((const char*)a[0], "app") == 0)
			{
				// TODO the following test will fail if you are running
				// TODO both an AbiWord (release) build and an AbiWord
				// TODO Personal (development/personal) build.  That is,
				// TODO you'll lose your MRU list if you alternate between
				// TODO the two types of executables.
				
				const char * szThisApp = m_pApp->getApplicationName();
				UT_DEBUGMSG(("Found preferences for application [%s] (this is [%s]).\n",
							a[1],szThisApp));
				if (strcmp((const char*)a[1],szThisApp) != 0)
				{
					UT_DEBUGMSG(("Preferences file does not match this application.\n"));
					goto InvalidFileError;
				}
			}
			else if (strcmp((const char*)a[0], "ver") == 0)
			{
				// TODO test version number
			}

			a += 2;
		}
		break;
		}
		case TT_SELECT:
		{
		m_parserState.m_bFoundSelect = true;
		
		// we expect something of the form:
		// <Select
		//     scheme="myScheme"
		//     autosaveprefs="1"
		//     useenvlocale="1"
		//     />

		const XML_Char ** a = atts;
		while (a && *a)
		{
			UT_ASSERT(a[1] && *a[1]);	// require a value for each attribute keyword

			if (strcmp((const char*)a[0], "scheme") == 0)
			{
				FREEP(m_parserState.m_szSelectedSchemeName);
				if (!UT_cloneString((char *&)m_parserState.m_szSelectedSchemeName,(const char*)a[1]))
					goto MemoryError;
			}
			else if (strcmp((char*)a[0], "autosaveprefs") == 0)
			{
				// m_bAutoSavePrefs controls whether we automatically
				// save any changes in the preferences during
				// interactive use/manipulation of the UI or if
				// we wait until the user explicitly does a save.
				// MSFT has this annoying tendency to session-persist
				// almost everything in the UI -- we can do that,
				// but lets not make it the default....
				
				m_bAutoSavePrefs = (*a[1] == '1');
			}
			else if (strcmp((const char*)a[0], "useenvlocale") == 0)
			{
				m_bUseEnvLocale = (*a[1] == '1');
			}
			
			a += 2;
		}

		if (!m_parserState.m_szSelectedSchemeName)
		{
			UT_DEBUGMSG(("No scheme selected in <Select...>\n"));
			goto InvalidFileError;
		}
		break;
		}
		case TT_SCHEME:
		{
		// we found a preferences scheme.  we expect something of the form:
		// <Scheme name="myScheme" n0="v0" n1="v1" ... />
		// where the [nk,vk] are arbitrary name/value pairs that mean
		// something to the application.
		//
		// if there are duplicated name/value pairs our behavior is
		// undefined -- we remember the last one that the XML parser
		// give us.

		bool bIsNamed = false;
		
		pNewScheme = new XAP_PrefsScheme(this, NULL);
		if (!pNewScheme)
			goto MemoryError;
		
		const XML_Char ** a = atts;
		while (*a)
		{
			UT_ASSERT(a[1] && *a[1]);	// require a value for each attribute keyword

			if (strcmp((const char*)a[0], "name") == 0)
			{
				bIsNamed = true;
				
				const XML_Char * szBuiltinSchemeName = getBuiltinSchemeName();

				if (strcmp((const char*)a[1], (const char*)szBuiltinSchemeName) == 0)
				{
					UT_DEBUGMSG(("Reserved scheme name [%s] found in file; ignoring.\n",a[1]));
					goto IgnoreThisScheme;
				}

				if (getScheme(a[1]))
				{
					UT_DEBUGMSG(("Duplicate scheme [%s]; ignoring latter instance.\n",a[1]));
					goto IgnoreThisScheme;
				}

				if (!pNewScheme->setSchemeName(a[1]))
					goto MemoryError;

				UT_DEBUGMSG(("Found Preferences scheme [%s].\n",a[1]));
			}
			else
			{
				if (!pNewScheme->setValue(a[0],a[1]))
					goto MemoryError;
			}

			a += 2;
		}

		if (!addScheme(pNewScheme))
			goto MemoryError;
		pNewScheme = NULL;				// we don't own it anymore
		break;
		}
		case TT_PLUGIN:
		{
		// Almost the same as TT_SCHEME, except is denoted by <Plugin ... /> 
		// instead of <Scheme ... /> and has no builtin to deal with

		bool bIsNamed = false;
		
		pNewScheme = new XAP_PrefsScheme(this, NULL);
		if (!pNewScheme)
			goto MemoryError;
		
		const XML_Char ** a = atts;
		while (*a)
		{
			UT_ASSERT(a[1] && *a[1]);	// require a value for each attribute keyword

			if (strcmp((const char*)a[0], "name") == 0)
			{
				bIsNamed = true;
				
				if (getPluginScheme(a[1]))
				{
					UT_DEBUGMSG(("Duplicate Plugin scheme [%s]; ignoring latter instance.\n",a[1]));
					goto IgnoreThisScheme;
				}

				if (!pNewScheme->setSchemeName(a[1]))
					goto MemoryError;

				UT_DEBUGMSG(("Found Preferences Plugin scheme [%s].\n",a[1]));
			}
			else
			{
				if (!pNewScheme->setValue(a[0],a[1]))
					goto MemoryError;
			}

			a += 2;
		}

		if (!addPluginScheme(pNewScheme))
			goto MemoryError;
		pNewScheme = NULL;				// we don't own it anymore
		break;
		}
		case TT_RECENT:
		{
		m_parserState.m_bFoundRecent = true;
		
		// we expect something of the form:
		// <Recent max="4" name1="v1" name2="v2" ... />

		const XML_Char ** a = atts;
		while (*a)
		{
			UT_ASSERT(a[1] && *a[1]);	// require a value for each attribute keyword

			if (strcmp((const char*)a[0], "max") == 0)
			{
				m_iMaxRecent = atoi((const char*)a[1]);
			}
			else if (strncmp((const char*)a[0], "name", 4) == 0)
			{
				// NOTE: taking advantage of the fact that XML_Char == char
				UT_ASSERT((sizeof(XML_Char) == sizeof(char)));
				XML_Char * sz;
				UT_XML_cloneString((XML_Char *&)sz, a[1]);

				// NOTE: we keep the copied string in the vector
				m_vecRecent.addItem((void *)sz);
			}

			a += 2;
		}

		_pruneRecent();
		break;
		}
		case TT_GEOMETRY:
		{
			if (m_geom.m_flags &  PREF_FLAG_GEOMETRY_NOUPDATE) break;
			m_parserState.m_bFoundGeometry = true;
		
			// we expect something of the form:
			// <Geometry width="xxx" height="xxx" posx="xxx" posy="xxx" />
			
			// These are the fall-back defaults which will be applied
			// if the user does NOT specify a geometry argument or
			// have set preference values. We only want to obey the
			// size not a position.

			// (Both m_geom and the temporary variables are
			// initialized so partial/invalid preference data from the
			// file will still have sensible fall-back defaults).
			UT_uint32 width = 800, height = 600, flags = PREF_FLAG_GEOMETRY_SIZE;
			UT_sint32 posx = 0, posy = 0;

			m_geom.m_width = width;
			m_geom.m_height = height;
			m_geom.m_posx = posx;
			m_geom.m_posy = posy;
			m_geom.m_flags = flags;
			
			const XML_Char ** a = atts;
			while (*a)
			{
				UT_ASSERT(a[1] && *a[1]);	// require a value for each attribute keyword
				
				if (strcmp((const char*)a[0], "width") == 0)
				{
					width = atoi((const char*)a[1]);
				}
				else if (strcmp((const char*)a[0], "height") == 0)
				{
					height = atoi((const char*)a[1]);
				}
				else if (strcmp((const char*)a[0], "posx") == 0)
				{
					posx = atoi((const char*)a[1]);
				}
				else if (strcmp((const char*)a[0], "posy") == 0)
				{
					posy = atoi((const char*)a[1]);
				}
				else if (strcmp((const char*)a[0], "flags") == 0)
				{
					flags = atoi((const char*)a[1]) & ~PREF_FLAG_GEOMETRY_NOUPDATE;
				}
				
				a += 2;
			}

			// Override the fall-backs as appropriate with preference
			// settings.
			if (flags & PREF_FLAG_GEOMETRY_SIZE)
			{
				m_geom.m_width = width;
				m_geom.m_height = height;
				m_geom.m_flags |= PREF_FLAG_GEOMETRY_SIZE;
			}
			if (flags & PREF_FLAG_GEOMETRY_POS)
			{
				m_geom.m_posx = posx;
				m_geom.m_posy = posy;
				m_geom.m_flags |= PREF_FLAG_GEOMETRY_POS;
			}
		}
	}
	// successful parse of tag...


IgnoreThisScheme:
	DELETEP(pNewScheme);
	return;								// success

MemoryError:
	UT_DEBUGMSG(("Memory error parsing preferences file.\n"));
InvalidFileError:
	m_parserState.m_parserStatus = false;			// cause parser driver to bail
	DELETEP(pNewScheme);
	return;
}

void XAP_Prefs::endElement(const XML_Char * /* name */)
{
	// everything in this file is contained in start-tags
	return;
}

void XAP_Prefs::charData(const XML_Char * /* s */, int /* len */)
{
	// everything in this file is contained in start-tags
	return;
}

/*****************************************************************/


bool XAP_Prefs::loadPrefsFile(void)
{
	bool bResult = false;			// assume failure
	const char * szFilename;

	m_parserState.m_parserStatus = true;
	m_parserState.m_bFoundAbiPreferences = false;
	m_parserState.m_bFoundSelect = false;
	m_parserState.m_szSelectedSchemeName = NULL;
	m_parserState.m_bFoundRecent = false;
	m_parserState.m_bFoundGeometry = false;

	m_bLoadSystemDefaultFile = false;

	UT_XML parser;

	szFilename = getPrefsPathname();
	if (!szFilename)
	{
		UT_DEBUGMSG(("could not get pathname for preferences file.\n"));
		goto Cleanup;
	}

	parser.setListener (this);
	if ((parser.parse (szFilename) != UT_OK) || (!m_parserState.m_parserStatus))
	{
		UT_DEBUGMSG(("Problem reading (Preferences) document\n"));
		goto Cleanup;
	}

	// we succeeded in parsing the file,
	// now check for higher-level consistency.

	if (!m_parserState.m_bFoundAbiPreferences)
	{
		UT_DEBUGMSG(("Did not find <AbiPreferences...>\n"));
		goto Cleanup;
	}
	if (!m_parserState.m_bFoundSelect)
	{
		UT_DEBUGMSG(("Did not find <Select...>\n"));
		goto Cleanup;
	}
	if (!m_parserState.m_bFoundRecent)
	{
		UT_DEBUGMSG(("Did not find <Recent...>\n"));
		// Note: it's ok if we didn't find it...
	}
	if (!m_parserState.m_bFoundGeometry)
	{
		UT_DEBUGMSG(("Did not find <Geometry...>\n"));
		// Note: it's ok if we didn't find it...
	}

	UT_ASSERT(m_parserState.m_szSelectedSchemeName);
	if (!setCurrentScheme(m_parserState.m_szSelectedSchemeName))
	{
		UT_DEBUGMSG(("Selected scheme [%s] not found in preferences file.\n",
					m_parserState.m_szSelectedSchemeName));
		goto Cleanup;
	}

	bResult = true;
Cleanup:
	FREEP(m_parserState.m_szSelectedSchemeName);

	return bResult;
}

bool XAP_Prefs::savePrefsFile(void)
{
	bool bResult = false;			// assume failure
	const char * szFilename;
	FILE * fp = NULL;

	szFilename = getPrefsPathname();
	if (!szFilename)
	{
		UT_DEBUGMSG(("could not get pathname for preferences file.\n"));
		goto Cleanup;
	}

	fp = fopen(szFilename, "w");
	if (!fp)
	{
		UT_DEBUGMSG(("could not open preferences file [%s].\n",szFilename));
		goto Cleanup;
	}

	// write a comment block as a prolog.
	// NOTE: this is human readable information only.
	
	fprintf(fp,"<!-- =====================================================================  -->\n");
	fprintf(fp,"<!-- This file contains AbiSuite Preferences.  AbiSuite is a suite of Open  -->\n");
	fprintf(fp,"<!-- Source desktop applications developed by AbiSource, Inc.  Information  -->\n");
	fprintf(fp,"<!-- about this application can be found at http://www.abisource.com        -->\n");
	fprintf(fp,"<!-- You should not edit this file by hand.                                 -->\n");
	fprintf(fp,"<!-- =====================================================================  -->\n");
	fprintf(fp,"\n");

#ifdef DEBUG
	if (XAP_App::s_szBuild_ID && XAP_App::s_szBuild_ID[0])
	{
		fprintf(fp,"<!--         Build_ID          = ");
		fprintf(fp,XAP_App::s_szBuild_ID);
		fprintf(fp," -->\n");
	}
	if (XAP_App::s_szBuild_Version && XAP_App::s_szBuild_Version[0])
	{
		fprintf(fp,"<!--         Build_Version     = ");
		fprintf(fp,XAP_App::s_szBuild_Version);
		fprintf(fp," -->\n");
	}
	if (XAP_App::s_szBuild_Options && XAP_App::s_szBuild_Options[0])
	{
		fprintf(fp,"<!--         Build_Options     = ");
		fprintf(fp,XAP_App::s_szBuild_Options);
		fprintf(fp," -->\n");
	}
	if (XAP_App::s_szBuild_Target && XAP_App::s_szBuild_Target[0])
	{
		fprintf(fp,"<!--         Build_Target      = ");
		fprintf(fp,XAP_App::s_szBuild_Target);
		fprintf(fp," -->\n");
	}
	if (XAP_App::s_szBuild_CompileTime && XAP_App::s_szBuild_CompileTime[0])
	{
		fprintf(fp,"<!--         Build_CompileTime = ");
		fprintf(fp,XAP_App::s_szBuild_CompileTime);
		fprintf(fp," -->\n");
	}
	if (XAP_App::s_szBuild_CompileDate && XAP_App::s_szBuild_CompileDate[0])
	{
		fprintf(fp,"<!--         Build_CompileDate = ");
		fprintf(fp,XAP_App::s_szBuild_CompileDate);
		fprintf(fp," -->\n");
	}
#endif
	
	// end of prolog.
	// now we begin the actual document.

	UT_ASSERT(m_builtinScheme);
	
	fprintf(fp,"\n<AbiPreferences app=\"%s\" ver=\"%s\">\n",
			m_pApp->getApplicationName(),
			"1.0");
	{
		fprintf(fp,("\n"
					"\t<Select\n"
					"\t    scheme=\"%s\"\n"
					"\t    autosaveprefs=\"%d\"\n"
					"\t    useenvlocale=\"%d\"\n"
					"\t/>\n"),
				m_currentScheme->getSchemeName(),
				(UT_uint32)m_bAutoSavePrefs,
				(UT_uint32)m_bUseEnvLocale);

		UT_uint32 kLimit = m_vecSchemes.getItemCount();
		UT_uint32 k;

		const XML_Char * szBuiltinSchemeName = getBuiltinSchemeName();

		for (k=0; k<kLimit; k++)
		{
			XAP_PrefsScheme * p = getNthScheme(k);
			UT_ASSERT(p);

			const XML_Char * szThisSchemeName = p->getSchemeName();
			bool bIsBuiltin = (p == m_builtinScheme);

			if (bIsBuiltin)
			{
				fprintf(fp,("\n"
							"\t<!-- The following scheme, %s, contains the built-in application\n"
							"\t**** defaults and adjusted by the installation system defaults.  This scheme\n"
							"\t**** is only written here as a reference.  Any schemes following this one\n"
							"\t**** only list values that deviate from the built-in values.\n"
							"\t**** Items values must observe XML encoding for double quote (&quot;),\n"
							"\t**** ampersand (&amp;), and angle brackets (&lt; and &gt;).\n"
							"\t-->\n"),
						szBuiltinSchemeName);
			}

			fprintf(fp,"\n\t<Scheme\n\t\tname=\"%s\"\n",szThisSchemeName);

			const XML_Char * szKey;
			const XML_Char * szValue;
			UT_uint32 j;

			for (j=0;(p->getNthValue(j, &szKey, &szValue)) ; j++)
			{
				bool need_print;
				need_print = false;
				if (bIsBuiltin)
				{
					// for the builtin set, we print every value
					need_print = true;
				}
				else
				{
					// for non-builtin sets, we only print the values which are different
					// from the builtin set.
					const XML_Char * szBuiltinValue = NO_PREF_VALUE;
					m_builtinScheme->getValue(szKey,&szBuiltinValue);
					if (strcmp((const char*)szValue,(const char*)szBuiltinValue) != 0 ||
						// Always print debug values
					strncmp((const char*)szKey, (const char*)DEBUG_PREFIX,
						sizeof(DEBUG_PREFIX) - 1) == 0)
					{
						need_print = true;
					}
				}
				if (need_print == true)
				{
					// szValue is UTF8.  Convert to Unicode and then
					// do XML-encoding of XML-special characters and
					// non-ASCII characters.  The printed value
					// strings will get XML parsing and conversion to
					// UTF8 the next time the application reads the
					// prefs file.
					UT_GrowBuf gb;
					UT_decodeUTF8string(szValue, UT_XML_strlen(szValue), &gb);
					UT_uint32 length = gb.getLength();
					fprintf(fp,"\t\t%s=\"",szKey);
					for (UT_uint32 udex=0; udex<length; ++udex)
					{
						UT_UCSChar ch = *(gb.getPointer(udex));
						switch (ch)
						{
						case '&':   fputs("&amp;", fp);  break;
						case '<':   fputs("&lt;", fp);  break;
						case '>':   fputs("&gt;", fp);  break;
						case '"':   fputs("&quot;", fp);  break;
						default:
							if (ch < ' ' || ch >= 128)
							{
								fprintf(fp, "&#x%x;", ch);
							}
							else
							{
								putc(ch, fp);
							}
						}
					}
					fputs("\"\n", fp);
				}
			}
				
			fprintf(fp,"\t\t/>\n");
		}

		// add Plugin Scheme (plugin specific preferences) if they exist
		kLimit = m_vecPluginSchemes.getItemCount();
		for (k=0; k<kLimit; k++)
		{
			XAP_PrefsScheme * p = getNthPluginScheme(k);
			UT_ASSERT(p);

			const XML_Char * szThisSchemeName = p->getSchemeName();
			fprintf(fp,"\n\t<Plugin\n\t\tname=\"%s\"\n",szThisSchemeName);

			const XML_Char * szKey;
			const XML_Char * szValue;
			UT_uint32 j;

			for (j=0;(p->getNthValue(j, &szKey, &szValue)) ; j++)
			{
					// szValue is UTF8.  Convert to Unicode and then
					// do XML-encoding of XML-special characters and
					// non-ASCII characters.  The printed value
					// strings will get XML parsing and conversion to
					// UTF8 the next time the application reads the
					// prefs file.
					UT_GrowBuf gb;
					UT_decodeUTF8string(szValue, UT_XML_strlen(szValue), &gb);
					UT_uint32 length = gb.getLength();
					fprintf(fp,"\t\t%s=\"",szKey);
					for (UT_uint32 udex=0; udex<length; ++udex)
					{
						UT_UCSChar ch = *(gb.getPointer(udex));
						switch (ch)
						{
						case '&':   fputs("&amp;", fp);  break;
						case '<':   fputs("&lt;", fp);  break;
						case '>':   fputs("&gt;", fp);  break;
						case '"':   fputs("&quot;", fp);  break;
						default:
							if (ch < ' ' || ch >= 128)
							{
								fprintf(fp, "&#x%x;", ch);
							}
							else
							{
								putc(ch, fp);
							}
						}
					}
					fputs("\"\n", fp);
			}
				
			fprintf(fp,"\t\t/>\n");
		}
		// end Plugin preferences

		fprintf(fp,"\n\t<Recent\n\t\tmax=\"%d\"\n",
				(UT_uint32)m_iMaxRecent);

		kLimit = m_vecRecent.getItemCount();

		for (k=0; k<kLimit; k++)
		{
			const char * szRecent = getRecent(k+1);

			fprintf(fp,"\t\tname%d=\"%s\"\n",k+1,szRecent);
		}
				
		fprintf(fp,"\t\t/>\n");

		fprintf(fp,"\n\t<Geometry\n");
		fprintf(fp,"\t\twidth=\"%u\"\n", m_geom.m_width); 
		fprintf(fp,"\t\theight=\"%u\"\n", m_geom.m_height); 
		fprintf(fp,"\t\tposx=\"%d\"\n", m_geom.m_posx); 
		fprintf(fp,"\t\tposy=\"%d\"\n", m_geom.m_posy); 
		fprintf(fp,"\t\tflags=\"%d\"\n", m_geom.m_flags); 
		fprintf(fp,"\t\t/>\n");
	}

	fprintf(fp,"\n</AbiPreferences>\n");
	
Cleanup:
	if (fp)
		fclose(fp);
	return bResult;

}

/*****************************************************************/

void XAP_Prefs::_startElement_SystemDefaultFile(const XML_Char *name, const XML_Char **atts)
{
	// routine to parse system default preferences file and
	// overlay values onto the builtin scheme.
	
	if (!m_parserState.m_parserStatus)		// eat if already had an error
		return;

	if (strcmp((const char*)name, "SystemDefaults") == 0)
	{
		// we found the system default preferences scheme.
		//
		// we expect something of the form:
		// <SystemDefaults n0="v0" n1="v1" ... />
		// where the [nk,vk] are arbitrary name/value pairs
		// that mean something to the application.
		//
		// if there are duplicated name/value pairs our behavior is
		// undefined -- we remember the last one that the XML parser
		// give us.

		const XML_Char ** a = atts;
		while (a && *a)
		{
			UT_ASSERT(a[1] && *a[1]);	// require a value for each attribute keyword

			// we ignore "name=<schemename>" just incase they copied and
			// pasted a user-profile into the system file.
			
			if (strcmp((const char*)a[0], "name") != 0)
				if (!m_builtinScheme->setValue(a[0],a[1]))
					goto MemoryError;

			a += 2;
		}
	}
	else
	{
		UT_DEBUGMSG(("Ignoring tag [%s] in system default preferences file.\n",name));
	}

	return;								// success

MemoryError:
	UT_DEBUGMSG(("Memory error parsing preferences file.\n"));
	m_parserState.m_parserStatus = false;			// cause parser driver to bail
	return;
}

/*****************************************************************/

bool XAP_Prefs::loadSystemDefaultPrefsFile(const char * szSystemDefaultPrefsPathname)
{
	UT_ASSERT(szSystemDefaultPrefsPathname && *szSystemDefaultPrefsPathname);
	
	bool bResult = false;			// assume failure
	m_parserState.m_parserStatus = true;

	m_bLoadSystemDefaultFile = true;

	UT_XML parser;
	parser.setListener (this);
	if ((parser.parse (szSystemDefaultPrefsPathname) != UT_OK) || (!m_parserState.m_parserStatus))
	{
		UT_DEBUGMSG(("Problem reading (System Default Preferences) document\n"));
		goto Cleanup;
	}

	// we succeeded in parsing the file,

	bResult = true;
Cleanup:
	return bResult;
}

/*****************************************************************/

void XAP_Prefs::addListener	  ( PrefsListener pFunc, void *data )
{
	tPrefsListenersPair *pPair = new tPrefsListenersPair;	

	UT_ASSERT(pPair);
	UT_ASSERT(pFunc);

	pPair->m_pFunc = pFunc;
	pPair->m_pData = data;

	m_vecPrefsListeners.addItem( (void *)pPair );
}

// optional parameter, data.  If given (i.e., != 0), will try to match data,
// otherwise, will delete all calls to pFunc
void XAP_Prefs::removeListener ( PrefsListener pFunc, void *data )
{
	UT_uint32 index;
	tPrefsListenersPair *pPair;

	for ( index = 0; index < m_vecPrefsListeners.getItemCount(); index++ )
	{
		pPair = (tPrefsListenersPair *)m_vecPrefsListeners.getNthItem(index);
		UT_ASSERT(pPair);
		if ( pPair ) {
			if ( pPair->m_pFunc == pFunc && (!data || pPair->m_pData == data) ) {
				m_vecPrefsListeners.deleteNthItem(index);
				delete pPair;
			}
		}
	}
}

void XAP_Prefs::_markPrefChange( const XML_Char *szKey )
{
	if ( m_bInChangeBlock )
	{
		const void * uth_e = m_ahashChanges.pick(szKey );

		if ( uth_e ) 
			uth_e = (const void *)1;
		else
			m_ahashChanges.insert(szKey, (void *)1);	

		// notify later
	}
	else
	{
		UT_StringPtrMap	changes(3);
		changes.insert(szKey, (void *)1);	

		_sendPrefsSignal(&changes);
	}
}

void XAP_Prefs::startBlockChange()
{
	m_bInChangeBlock = true;
}

void XAP_Prefs::endBlockChange()
{
	if ( m_bInChangeBlock ) 
	{
		m_bInChangeBlock = false;
		_sendPrefsSignal( &m_ahashChanges );
	}
}

void XAP_Prefs::_sendPrefsSignal( UT_StringPtrMap *hash  )
{
	UT_uint32	index;
	for ( index = 0; index < m_vecPrefsListeners.getItemCount(); index++ )
	{
		tPrefsListenersPair *p = (tPrefsListenersPair *)
			m_vecPrefsListeners.getNthItem( index );

		UT_ASSERT(p && p->m_pFunc);
	
		(p->m_pFunc)(m_pApp, this, hash, p->m_pData);
	}
}
