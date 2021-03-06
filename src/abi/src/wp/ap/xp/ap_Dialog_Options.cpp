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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ut_assert.h"
#include "ut_string.h"
#include "ut_string_class.h"
#include "ut_units.h"
#include "ut_debugmsg.h"

#include "xap_Dialog_Id.h"
#include "xad_Document.h"
#include "xap_DialogFactory.h"
#include "xap_Dlg_MessageBox.h"
#include "xap_Frame.h"
#include "xap_Prefs.h"
#include "fv_View.h"
#include "fl_DocLayout.h"

#include "ap_Dialog_Options.h"
#include "ap_Prefs_SchemeIds.h"
#include "ap_Strings.h"
#include "ap_FrameData.h"

AP_Dialog_Options::AP_Dialog_Options(XAP_DialogFactory * pDlgFactory, XAP_Dialog_Id id)
	: XAP_Dialog_NonPersistent(pDlgFactory,id, "interface/dialogpreferences.html"),
	  m_answer(a_OK),
	  m_pFrame(0),	// needs to be set from runModal for some of the event_'s to work
	  m_pageNum(-1)
{
}

AP_Dialog_Options::~AP_Dialog_Options(void)
{
}

AP_Dialog_Options::tAnswer AP_Dialog_Options::getAnswer(void) const
{
	return m_answer;
}

inline void Save_Pref_Bool(  XAP_PrefsScheme *pPrefsScheme,
							 XML_Char const * key,
							 bool var )
{
	XML_Char szBuffer[2] = {0,0};
	szBuffer[0] = ((var)==true ? '1' : '0');
	pPrefsScheme->setValue( key, szBuffer );
}

void AP_Dialog_Options::_storeWindowData(void)
{
	XAP_Prefs *pPrefs = m_pApp->getPrefs();
	UT_ASSERT(pPrefs);

	AP_FrameData *pFrameData = (AP_FrameData *)m_pFrame->getFrameData();
	UT_ASSERT(pFrameData);

	XAP_PrefsScheme *pPrefsScheme = pPrefs->getCurrentScheme();
	UT_ASSERT(pPrefsScheme);

	// turn off all notification to PrefListeners via XAP_Prefs
	pPrefs->startBlockChange();

	// before we continue to remember all the changed values, check to see if
	// we have turned OFF PrefsAutoSave.  If so, toggle that value, then force
	// a prefs save, then update everything else
	//			shack@uiuc.edu
	if ( pPrefs->getAutoSavePrefs() == true && _gatherPrefsAutoSave() == false ) {

		pPrefs->setAutoSavePrefs( false );
		pPrefs->savePrefsFile();				// TODO: check the results
	}
	else {	// otherwise, just set the value
		pPrefs->setAutoSavePrefs( _gatherPrefsAutoSave() );
	}

	// try again to make sure we've got an updatable scheme
	pPrefsScheme = pPrefs->getCurrentScheme(true);
	UT_ASSERT(pPrefsScheme);

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	// save the values to the Prefs classes
	Save_Pref_Bool( pPrefsScheme, AP_PREF_KEY_AutoSpellCheck, _gatherSpellCheckAsType() );
	Save_Pref_Bool( pPrefsScheme, AP_PREF_KEY_SpellCheckCaps, _gatherSpellUppercase() );
	Save_Pref_Bool( pPrefsScheme, AP_PREF_KEY_SpellCheckNumbers, _gatherSpellNumbers() );
	Save_Pref_Bool( pPrefsScheme, AP_PREF_KEY_SpellCheckInternet, _gatherSpellInternet() );
	Save_Pref_Bool(pPrefsScheme, AP_PREF_KEY_ShowSplash,_gatherShowSplash());
	Save_Pref_Bool( pPrefsScheme, XAP_PREF_KEY_SmartQuotesEnable, _gatherSmartQuotesEnable() );

	Save_Pref_Bool( pPrefsScheme, AP_PREF_KEY_CursorBlink, _gatherViewCursorBlink() );
	Save_Pref_Bool( pPrefsScheme, AP_PREF_KEY_RulerVisible, _gatherViewShowRuler() );
	Save_Pref_Bool( pPrefsScheme, AP_PREF_KEY_StandardBarVisible, _gatherViewShowStandardBar() );
	Save_Pref_Bool( pPrefsScheme, AP_PREF_KEY_FormatBarVisible, _gatherViewShowFormatBar() );
	Save_Pref_Bool( pPrefsScheme, AP_PREF_KEY_ExtraBarVisible, _gatherViewShowExtraBar() );
	Save_Pref_Bool( pPrefsScheme, AP_PREF_KEY_StatusBarVisible, _gatherViewShowStatusBar() );
	Save_Pref_Bool( pPrefsScheme, AP_PREF_KEY_ParaVisible, _gatherViewUnprintable() );
	Save_Pref_Bool( pPrefsScheme, XAP_PREF_KEY_AllowCustomToolbars, _gatherAllowCustomToolbars() );
	Save_Pref_Bool( pPrefsScheme, XAP_PREF_KEY_AutoLoadPlugins, _gatherAutoLoadPlugins() );
	Save_Pref_Bool( pPrefsScheme, AP_PREF_KEY_DefaultDirectionRtl, _gatherOtherDirectionRtl() );
	Save_Pref_Bool( pPrefsScheme, XAP_PREF_KEY_UseContextGlyphs, _gatherOtherUseContextGlyphs() );
	Save_Pref_Bool( pPrefsScheme, XAP_PREF_KEY_SaveContextGlyphs, _gatherOtherSaveContextGlyphs() );
	Save_Pref_Bool( pPrefsScheme, XAP_PREF_KEY_UseHebrewContextGlyphs, _gatherOtherHebrewContextGlyphs() );

#if 1
	// JOAQUIN - fix this: Dom
	UT_DEBUGMSG(("Saving Auto Save File [%i]\n", _gatherAutoSaveFile()));
	Save_Pref_Bool( pPrefsScheme, XAP_PREF_KEY_AutoSaveFile, _gatherAutoSaveFile() );

	UT_String stVal;

	_gatherAutoSaveFileExt(stVal);
	UT_DEBUGMSG(("Saving Auto Save File Ext [%s]\n", stVal.c_str()));
	pPrefsScheme->setValue(XAP_PREF_KEY_AutoSaveFileExt, stVal.c_str());
	_gatherAutoSaveFilePeriod(stVal);
	UT_DEBUGMSG(("Saving Auto Save File with a period of [%s]\n", stVal.c_str()));
	pPrefsScheme->setValue(XAP_PREF_KEY_AutoSaveFilePeriod, stVal.c_str());
	
	// Jordi: win32 specific for now
	_gatherDocLanguage(stVal);
	if (stVal.length())
	{
		UT_DEBUGMSG(("Setting default document language to [%s]\n", stVal.c_str()));
		pPrefsScheme->setValue(XAP_PREF_KEY_DocumentLocale, stVal.c_str());
	}
	
	_gatherUILanguage(stVal);
	if (stVal.length())
	{
		UT_DEBUGMSG(("Setting default UI language to [%s]\n", stVal.c_str()));
		pPrefsScheme->setValue(AP_PREF_KEY_StringSet, stVal.c_str());
	}
	
	
#endif
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	// If we changed whether the ruler is to be visible
	// or hidden, then update the current window:
	// (If we didn't change anything, leave it alone)
	if ( _gatherViewShowRuler() != pFrameData->m_bShowRuler )
	{
		pFrameData->m_bShowRuler = _gatherViewShowRuler() ;
		m_pFrame->toggleRuler(pFrameData->m_bShowRuler);
	}

	// Same for status bar
	if (_gatherViewShowStatusBar() != pFrameData->m_bShowStatusBar)
	{
		pFrameData->m_bShowStatusBar = _gatherViewShowStatusBar();
		m_pFrame->toggleStatusBar(pFrameData->m_bShowStatusBar);
	}


	// TODO: Don't use 0, 1, 2, but AP_TOOLBAR_STANDARD, AP_TOOLBAR_FORMAT, AP_TOOLBAR_EXTRA...
	if (_gatherViewShowStandardBar() != pFrameData->m_bShowBar[0])
	{
		pFrameData->m_bShowBar[0] = _gatherViewShowStandardBar();
		m_pFrame->toggleBar(0, pFrameData->m_bShowBar[0]);
	}

	if (_gatherViewShowFormatBar() != pFrameData->m_bShowBar[1])
	{
		pFrameData->m_bShowBar[1] = _gatherViewShowFormatBar();
		m_pFrame->toggleBar(1, pFrameData->m_bShowBar[1]);
	}

	if (_gatherViewShowExtraBar() != pFrameData->m_bShowBar[3])
	{
		pFrameData->m_bShowBar[3] = _gatherViewShowExtraBar();
		m_pFrame->toggleBar(3, pFrameData->m_bShowBar[3]);
	}

	if ( _gatherViewUnprintable() != pFrameData->m_bShowPara )
	{
		pFrameData->m_bShowPara = _gatherViewUnprintable() ;
		AV_View * pAVView = m_pFrame->getCurrentView();
		UT_ASSERT(pAVView);

		FV_View * pView = static_cast<FV_View *> (pAVView);

		pView->setShowPara(pFrameData->m_bShowPara);
	}


	if ( _gatherAllowCustomToolbars() != m_pFrame->getApp()->areToolbarsCustomizable() )
	{
		m_pFrame->getApp()->setToolbarsCustomizable(_gatherAllowCustomToolbars());
	}

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	// save ruler units value
	pPrefsScheme->setValue((XML_Char*)AP_PREF_KEY_RulerUnits,
				   (XML_Char*)UT_dimensionName( _gatherViewRulerUnits()) );

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	// save default paper size
	UT_ASSERT(sizeof(XML_Char) && sizeof(char));
	pPrefsScheme->setValue((XML_Char*)XAP_PREF_KEY_DefaultPageSize,
				   (XML_Char*)fp_PageSize::PredefinedToName( _gatherDefaultPageSize()) );


	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	// save screen color
	UT_ASSERT(sizeof(XML_Char) && sizeof(char));
	pPrefsScheme->setValue((XML_Char*)XAP_PREF_KEY_ColorForTransparent,
				   _gatherColorForTransparent() );


	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	// allow XAP_Prefs to notify all the listeners of changes

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	// TODO: change to snprintf
	XML_Char szBuffer[40];
	sprintf( szBuffer, "%i", _gatherNotebookPageNum() );
	pPrefsScheme->setValue((XML_Char*)AP_PREF_KEY_OptionsTabNumber,
				   (XML_Char*)szBuffer );

	// allow the prefListeners to receive their calls
	pPrefs->endBlockChange();

	// if we hit the Save button, then force a save after the gather
	if ( m_answer == a_SAVE ) {
		pPrefs->savePrefsFile();				// TODO: check the results
	}

}

void AP_Dialog_Options::_setColorForTransparent(const XML_Char *
												pzsColorForTransparent)
{
	strncpy(m_CurrentTransparentColor,pzsColorForTransparent,9);
}

const XML_Char * AP_Dialog_Options::_gatherColorForTransparent(void)
{
	return (const XML_Char *) m_CurrentTransparentColor;
}

void AP_Dialog_Options::_eventSave(void)
{
	m_answer = a_SAVE;

	_storeWindowData();

	m_answer = a_OK;
}

void AP_Dialog_Options::_populateWindowData(void)
{
	bool			b;
	XAP_Prefs		*pPrefs = 0;
	const XML_Char	*pszBuffer = 0;

	// TODO: move this logic when we get a PrefsListener API and turn this
	//		 dialog into an app-specific

	pPrefs = m_pApp->getPrefs();
	UT_ASSERT( pPrefs );

	// ------------ Spell
	if (pPrefs->getPrefsValueBool((XML_Char*)AP_PREF_KEY_AutoSpellCheck,&b))
		_setSpellCheckAsType (b);

	if (pPrefs->getPrefsValueBool((XML_Char*)AP_PREF_KEY_SpellCheckCaps,&b))
		_setSpellUppercase (b);

	if (pPrefs->getPrefsValueBool((XML_Char*)AP_PREF_KEY_SpellCheckNumbers,&b))
		_setSpellNumbers (b);

	if (pPrefs->getPrefsValueBool((XML_Char*)AP_PREF_KEY_SpellCheckInternet,&b))
		_setSpellInternet (b);

	// ------------ Smart Quotes
	if (pPrefs->getPrefsValueBool((XML_Char*)XAP_PREF_KEY_SmartQuotesEnable,&b))
		_setSmartQuotesEnable (b);

	if (pPrefs->getPrefsValue((XML_Char*)XAP_PREF_KEY_DefaultPageSize, &pszBuffer)) {
		UT_ASSERT(sizeof(XML_Char) == sizeof(char));
		_setDefaultPageSize (fp_PageSize::NameToPredefined((char*) pszBuffer));
	}

	// ------------ Prefs
	_setPrefsAutoSave( pPrefs->getAutoSavePrefs() );

	//-------------ShowSplash
	if (pPrefs->getPrefsValueBool((XML_Char*)AP_PREF_KEY_ShowSplash,&b))
		_setShowSplash (b);

	// ------------ View
	if (pPrefs->getPrefsValue((XML_Char*)AP_PREF_KEY_RulerUnits,&pszBuffer))
		_setViewRulerUnits (UT_determineDimension(pszBuffer));

	if (pPrefs->getPrefsValueBool((XML_Char*)AP_PREF_KEY_RulerVisible,&b))
		_setViewShowRuler (b);


	if (pPrefs->getPrefsValueBool((XML_Char*)AP_PREF_KEY_StandardBarVisible,&b))
		_setViewShowStandardBar (b);

	if (pPrefs->getPrefsValueBool((XML_Char*)AP_PREF_KEY_FormatBarVisible,&b))
		_setViewShowFormatBar (b);

	if (pPrefs->getPrefsValueBool((XML_Char*)AP_PREF_KEY_ExtraBarVisible,&b))
		_setViewShowExtraBar (b);

	if (pPrefs->getPrefsValueBool((XML_Char*)AP_PREF_KEY_StatusBarVisible,&b))
		_setViewShowStatusBar (b);

	if (pPrefs->getPrefsValueBool((XML_Char*)AP_PREF_KEY_ParaVisible,&b))
		_setViewUnprintable (b);

	if (pPrefs->getPrefsValueBool((XML_Char*)AP_PREF_KEY_CursorBlink,&b))
		_setViewCursorBlink (b);

	if (pPrefs->getPrefsValueBool((XML_Char*)XAP_PREF_KEY_AllowCustomToolbars,&b))
		_setAllowCustomToolbars(b);

	if (pPrefs->getPrefsValueBool((XML_Char*)XAP_PREF_KEY_AutoLoadPlugins,&b))
		_setAutoLoadPlugins(b);

#if 1
	// TODO: JOAQUIN FIX THIS
	if (pPrefs->getPrefsValueBool((XML_Char*)XAP_PREF_KEY_AutoSaveFile,&b))
		_setAutoSaveFile (b);

	UT_String stBuffer;
	if (pPrefs->getPrefsValue(XAP_PREF_KEY_AutoSaveFileExt, stBuffer))
		_setAutoSaveFileExt(stBuffer);

	if (pPrefs->getPrefsValue(XAP_PREF_KEY_AutoSaveFilePeriod, stBuffer))
		_setAutoSaveFilePeriod(stBuffer);
		
	//Just for win32 
	if (pPrefs->getPrefsValue(XAP_PREF_KEY_DocumentLocale, stBuffer))
		_setDocLanguage(stBuffer);
		
	if (pPrefs->getPrefsValue(AP_PREF_KEY_StringSet, stBuffer))
		_setUILanguage(stBuffer);
		
#endif

	// ------------ Screen Color

	const XML_Char * pszColorForTransparent = NULL;
	if (pPrefs->getPrefsValue(XAP_PREF_KEY_ColorForTransparent, &pszColorForTransparent))
		_setColorForTransparent(pszColorForTransparent);


	// ------------ the page tab number
	int which = getInitialPageNum ();
	if ((which == -1) && pPrefs->getPrefsValue((XML_Char*)AP_PREF_KEY_OptionsTabNumber,&pszBuffer))
		_setNotebookPageNum (atoi(pszBuffer));
	else
	  _setNotebookPageNum(which);

	//------------- other
	if (pPrefs->getPrefsValueBool(AP_PREF_KEY_DefaultDirectionRtl,&b))
		_setOtherDirectionRtl (b);
	if (pPrefs->getPrefsValueBool(XAP_PREF_KEY_UseContextGlyphs,&b))
		_setOtherUseContextGlyphs (b);
	if (pPrefs->getPrefsValueBool(XAP_PREF_KEY_SaveContextGlyphs,&b))
		_setOtherSaveContextGlyphs (b);
	if (pPrefs->getPrefsValueBool(XAP_PREF_KEY_UseHebrewContextGlyphs,&b))
		_setOtherHebrewContextGlyphs (b);

	// enable/disable controls
	_initEnableControls();
}


void AP_Dialog_Options::_enableDisableLogic( tControl id )
{
	UT_DEBUGMSG(("_enableDisableLogic: id %d, myId %d\n", id,id_CHECK_OTHER_USE_CONTEXT_GLYPHS));

	switch (id)
	{

/*	- Since HIDE_ERRORS is not implemented, no need to toggle it on/off
	case id_CHECK_SPELL_CHECK_AS_TYPE:
		// if we 'check as we type', then enable the 'hide' option
		_controlEnable( id_CHECK_SPELL_HIDE_ERRORS,
						_gatherSpellCheckAsType() );
		break;
*/

	case id_CHECK_OTHER_USE_CONTEXT_GLYPHS:
		_controlEnable( id_CHECK_OTHER_SAVE_CONTEXT_GLYPHS, _gatherOtherUseContextGlyphs());
		_controlEnable( id_CHECK_OTHER_HEBREW_CONTEXT_GLYPHS, _gatherOtherUseContextGlyphs());
		break;

	default:
		// do nothing
		break;
	}
}

// The initialize the controls (i.e., disable controls not coded yet)
void AP_Dialog_Options::_initEnableControls()
{
	// spelling
	_controlEnable( id_CHECK_SPELL_SUGGEST, 		false );
	_controlEnable( id_CHECK_SPELL_HIDE_ERRORS, 	false );
	_controlEnable( id_CHECK_SPELL_MAIN_ONLY,		false );
	_controlEnable( id_CHECK_SPELL_INTERNET,		true );
	_controlEnable( id_LIST_DICTIONARY, 			false );
	_controlEnable( id_BUTTON_DICTIONARY_EDIT,		false );
	_controlEnable( id_BUTTON_IGNORE_EDIT,			false );

	// prefs
	_controlEnable( id_COMBO_PREFS_SCHEME,			false );

	// view
	_controlEnable( id_CHECK_VIEW_ALL,				false );
	_controlEnable( id_CHECK_VIEW_HIDDEN_TEXT,		false );

	// general
	_controlEnable( id_BUTTON_SAVE, 				false );
	_controlEnable( id_CHECK_OTHER_SAVE_CONTEXT_GLYPHS, _gatherOtherUseContextGlyphs());
	_controlEnable( id_CHECK_OTHER_HEBREW_CONTEXT_GLYPHS, _gatherOtherUseContextGlyphs());

	//
	// If the prefs color for transparent is white initially disable the choose
	// color button
	//
	if(UT_strcmp(m_CurrentTransparentColor,"ffffff") == 0)
	{
		_controlEnable( id_PUSH_CHOOSE_COLOR_FOR_TRANSPARENT, false);
	}
	else
	{
		_controlEnable( id_PUSH_CHOOSE_COLOR_FOR_TRANSPARENT, true);
	}

}

void AP_Dialog_Options::_event_SetDefaults(void)
{
	XAP_Prefs		*pPrefs;
	const XML_Char	*old_name;
	int currentPage;

	pPrefs = m_pApp->getPrefs();
	UT_ASSERT(pPrefs);

	// SetDefaults
	//	To set the defaults, save the scheme name and notebook page number,
	//	re-populate the window with the _builtin_ scheme, then reset the
	//	scheme name and page number.
	// If the user hits cancel, then nothing is saved in user_prefs

	old_name = pPrefs->getCurrentScheme()->getSchemeName();

	currentPage = _gatherNotebookPageNum();

	pPrefs->setCurrentScheme("_builtin_");

	_populateWindowData();

	// TODO i'm not sure you want to do the following at this
	// TODO time.  setting to "defaults" should probably just
	// TODO set us to "_builtin_" and that's it.  if the user
	// TODO then changes something, we should create a new
	// TODO scheme and fill in the new value.  --jeff
	_setNotebookPageNum( currentPage );
	pPrefs->setCurrentScheme(old_name);
}

void AP_Dialog_Options::_event_IgnoreReset(void)
{
	UT_DEBUGMSG(("AP_Dialog_Options::_event_IgnoreReset\n"));
	UT_ASSERT( m_pFrame );

	// TODO:  shack@uiuc.edu: waiting for a vote for reset strings...

	// Ask "Do you want to reset ignored words in the current document?"
	XAP_Dialog_MessageBox::tAnswer ans = m_pFrame->showMessageBox(AP_STRING_ID_DLG_Options_Prompt_IgnoreResetCurrent,
								XAP_Dialog_MessageBox::b_YNC,
								XAP_Dialog_MessageBox::a_NO); // should this be YES?


	// if hit cancel, go no further
	// if no hit, don't do anything else, even prompt for other docs
	if (ans == XAP_Dialog_MessageBox::a_CANCEL ||
		ans == XAP_Dialog_MessageBox::a_NO )
	{
		UT_DEBUGMSG(("No/Canceled\n"));
		return;
	}

	// do it
	UT_DEBUGMSG(("Yes\n"));
	UT_ASSERT(ans == XAP_Dialog_MessageBox::a_YES );

	// ask another question : "Do you want to reset ignored words in all the
	// documents?" , but only if # frames > 1
	XAP_App *pApp = m_pFrame->getApp();
	UT_ASSERT(pApp);
	if (pApp->getFrameCount() > 1)
	{

		ans = m_pFrame->showMessageBox(AP_STRING_ID_DLG_Options_Prompt_IgnoreResetAll,
									XAP_Dialog_MessageBox::b_YNC,
									XAP_Dialog_MessageBox::a_NO); // should this be YES?


		// if cancel, don't to ANYTHING
		if (ans == XAP_Dialog_MessageBox::a_CANCEL )
		{
			UT_DEBUGMSG(("No/Canceled\n"));
			return;
		}
	}

	// ------------------------- actually do it
	if ( ans == XAP_Dialog_MessageBox::a_NO )
	{
		// if no to all documents, then just reset current (because we made it
		// this far
		m_pFrame->getCurrentDoc()->clearIgnores();

		((FV_View *)m_pFrame->getCurrentView())->getLayout()->recheckIgnoredWords();
	}
	else
	{
		// reset all doc's ignored words
		UT_uint32 ndx;
		for ( ndx = 0; ndx < pApp->getFrameCount(); ndx++ )
		{
			XAP_Frame *pFrame = pApp->getFrame(ndx);

			pFrame->getCurrentDoc()->clearIgnores();
			((FV_View *)pFrame->getCurrentView())->getLayout()->recheckIgnoredWords();
		}
	}

	// TODO : recheck spelling

}

void AP_Dialog_Options::_event_IgnoreEdit(void)
{
	UT_DEBUGMSG(("AP_Dialog_Options::_event_IgnoreEdit\n"));
}

void AP_Dialog_Options::_event_DictionaryEdit(void)
{
	UT_DEBUGMSG(("AP_Dialog_Options::_event_DictionaryEdit\n"));
}
