/* -*- mode: C++; tab-width: 4; c-basic-offset: 4; -*- */

/* AbiSource Application Framework
 * Copyright (C) 2002 AbiSource, Inc.
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

#include <string.h>

#include "ut_assert.h"
#include "ut_string_class.h"

#include "xap_App.h"
#include "xap_Prefs.h"
#include "xap_Dlg_HTMLOptions.h"

/*****************************************************************/

XAP_Dialog_HTMLOptions::XAP_Dialog_HTMLOptions (XAP_DialogFactory * pDlgFactory,
												XAP_Dialog_Id id)
	: XAP_Dialog_NonPersistent(pDlgFactory,id),
	  m_bShouldSave(true),
	  m_exp_opt(NULL),
	  m_app(NULL)
{
	// 
}

XAP_Dialog_HTMLOptions::~XAP_Dialog_HTMLOptions(void)
{
	// 
}

void XAP_Dialog_HTMLOptions::setHTMLOptions (XAP_Exp_HTMLOptions * exp_opt, XAP_App * app)
{
	UT_ASSERT (exp_opt);

	m_exp_opt = exp_opt;
	m_app = app;
}

void XAP_Dialog_HTMLOptions::set_HTML4 (bool enable)
{
	m_exp_opt->bIs4         = enable;
	m_exp_opt->bIsAbiWebDoc = enable ? false : m_exp_opt->bIsAbiWebDoc;
}

void XAP_Dialog_HTMLOptions::set_PHTML (bool enable)
{
	m_exp_opt->bIs4         = enable ? false : m_exp_opt->bIs4;
	m_exp_opt->bIsAbiWebDoc = enable;
}

void XAP_Dialog_HTMLOptions::set_Declare_XML (bool enable)
{
	if (can_set_Declare_XML ()) m_exp_opt->bDeclareXML = enable;
}

void XAP_Dialog_HTMLOptions::set_Allow_AWML (bool enable)
{
	if (can_set_Allow_AWML ()) m_exp_opt->bAllowAWML = enable;
}

void XAP_Dialog_HTMLOptions::set_Embed_CSS (bool enable)
{
	if (can_set_Embed_CSS ()) m_exp_opt->bEmbedCSS = enable;
}

void XAP_Dialog_HTMLOptions::set_Embed_Images (bool enable)
{
	m_exp_opt->bEmbedImages = enable;
}

void XAP_Dialog_HTMLOptions::saveDefaults ()
{
	UT_ASSERT(m_app);
	if (m_app == NULL) return;

    XAP_Prefs * pPrefs = m_app->getPrefs ();
	if (pPrefs == NULL) return;

	XAP_PrefsScheme * pPScheme = pPrefs->getCurrentScheme ();
	if (pPScheme == NULL) return;

	UT_UTF8String pref;

	if (m_exp_opt->bIs4)
		{
			if (pref.byteLength ()) pref += ",";
			pref += "HTML4";
		}
	if (m_exp_opt->bIsAbiWebDoc)
		{
			if (pref.byteLength ()) pref += ",";
			pref += "PHTML";
		}
	if (m_exp_opt->bDeclareXML)
		{
			if (pref.byteLength ()) pref += ",";
			pref += "?xml";
		}
	if (m_exp_opt->bDeclareXML)
		{
			if (pref.byteLength ()) pref += ",";
			pref += "xmlns:awml";
		}
	if (m_exp_opt->bEmbedCSS)
		{
			if (pref.byteLength ()) pref += ",";
			pref += "+CSS";
		}
	if (m_exp_opt->bEmbedImages)
		{
			if (pref.byteLength ()) pref += ",";
			pref += "data:base64";
		}
	const XML_Char * szValue = (const XML_Char *) pref.utf8_str ();

	pPScheme->setValue (XAP_PREF_KEY_HTMLExportOptions, szValue);
}

void XAP_Dialog_HTMLOptions::restoreDefaults ()
{
	if (m_exp_opt == NULL) return;
	XAP_Dialog_HTMLOptions::getHTMLDefaults (m_exp_opt, m_app);
}

void XAP_Dialog_HTMLOptions::getHTMLDefaults (XAP_Exp_HTMLOptions * exp_opt, XAP_App * app)
{
	UT_ASSERT(exp_opt);

	if (exp_opt == NULL) return;

	exp_opt->bIs4         = false;
	exp_opt->bIsAbiWebDoc = false;
	exp_opt->bDeclareXML  = true;
	exp_opt->bAllowAWML   = true;
	exp_opt->bEmbedCSS    = true;
	exp_opt->bEmbedImages = false;

	if (app == NULL) return;

    const XAP_Prefs * pPrefs = app->getPrefs ();

	if (pPrefs == NULL) return;

	const XML_Char * szValue = NULL;
	bool haveValue = pPrefs->getPrefsValue (XAP_PREF_KEY_HTMLExportOptions, &szValue);

	if (haveValue && szValue)
		{
			const char * pref = (const char *) szValue;

			exp_opt->bIs4         = (strstr (pref, "HTML4")       == NULL) ? false : true;
			exp_opt->bIsAbiWebDoc = (strstr (pref, "PHTML")       == NULL) ? false : true;
			exp_opt->bDeclareXML  = (strstr (pref, "?xml")        == NULL) ? false : true;
			exp_opt->bAllowAWML   = (strstr (pref, "xmlns:awml")  == NULL) ? false : true;
			exp_opt->bEmbedCSS    = (strstr (pref, "+CSS")        == NULL) ? false : true;
			exp_opt->bEmbedImages = (strstr (pref, "data:base64") == NULL) ? false : true;

			if (exp_opt->bIs4) exp_opt->bIsAbiWebDoc = false;
		}
}
