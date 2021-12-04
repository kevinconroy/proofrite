/*
 * AbiFestVox - Festival plugin for AbiWord
 * Authors:	Rui Miguel Silva Seabra <rms@1407.org>
 * Inspiration: AikSaurus AbiWord plugin by Jared Davis
 * Copyright © 2002 The Free Software Foundation
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

#include "ut_assert.h"
#include "ut_debugmsg.h"
#include "xap_Module.h"
#include "xap_App.h"
#include "xap_Frame.h"
#include "fv_View.h"
#include "ap_Menu_Id.h"
#include "ev_Menu_Actions.h"
#include "ev_Menu.h"
#include "ev_Menu_Layouts.h"
#include "ev_Menu_Labels.h"
#include "ev_EditMethod.h"
#include "xap_Menu_Layouts.h"
#include "fg_Graphic.h"
#include "ie_imp.h"
#include "ie_impGraphic.h"
#include "ie_exp.h"
#include "ie_types.h"

#include "ut_sleep.h"
#include <sys/types.h>  
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

ABI_PLUGIN_DECLARE(AbiFestVox);

static bool AbiFestVox_invoke(AV_View* v, EV_EditMethodCallData *d);

static const char* AbiFestVox_MenuLabel = "&Read Aloud Document";
static const char* AbiFestVox_MenuTooltip = "Read aloud the full document";
static const char* AbiFestVox_ContextMenuLabel = "&Read Aloud";
static const char* AbiFestVox_ContextMenuTooltip = "Reads selected text";
static const char* callbackStr = "AbiFestVox_invoke";


//
// AbiFestVox_addToMenus
// -----------------------
//   Adds "Read Aloud" option to AbiWord's Context Menu.
//
static void AbiFestVox_addToMenus() {
	// First we need to get a pointer to the application itself.
	XAP_App *pApp = XAP_App::getApp();


	// Create an EditMethod that will link our method's name with
	// it's callback function.  This is used to link the name to 
	// the callback.
	EV_EditMethod *myEditMethod = new EV_EditMethod(
		callbackStr,            // name of callback function
		AbiFestVox_invoke,   // callback function itself.
		0,                   // no additional data required.
		""         // description -- allegedly never used for anything
	);

	// Now we need to get the EditMethod container for the application.
	// This holds a series of Edit Methods and links names to callbacks.
	EV_EditMethodContainer* pEMC = pApp->getEditMethodContainer();
    
	// We have to add our EditMethod to the application's EditMethodList
	// so that the application will know what callback to call when a call
	// to "AbiFestVox_invoke" is received.
	pEMC->addEditMethod(myEditMethod);
  

	// Now we need to grab an ActionSet.  This is going to be used later
	// on in our for loop.  Take a look near the bottom.
	EV_Menu_ActionSet* pActionSet = pApp->getMenuActionSet();

    
	// We need to go through and add the menu element to each "frame" 
	// of the application.  We can iterate through the frames by doing
	// XAP_App::getFrameCount() to tell us how many frames there are,
	// then calling XAP_App::getFrame(i) to get the i-th frame.

	int frameCount = pApp->getFrameCount();
	XAP_Menu_Factory * pFact = pApp->getMenuFactory();

	//
	// Put it in the context menu.
	//
	XAP_Menu_Id contextID = pFact->addNewMenuAfter(
			"contextText",NULL,"Bullets and &Numbering",
			EV_MLF_Normal
			);
	// Add Label
	pFact->addNewLabel(
			NULL,contextID,
			AbiFestVox_ContextMenuLabel,
			AbiFestVox_ContextMenuTooltip
			);
	// Create the Action that will be called.
	EV_Menu_Action* contextAction = new EV_Menu_Action(
		contextID,              // id that the layout said we could use
		0,                      // no, we don't have a sub menu.
		1,                      // yes, we raise a dialog.
		0,                      // no, we don't have a checkbox.
		callbackStr,            // name of callback function to call.
		NULL,                   // don't know/care what this is for
		NULL                    // don't know/care what this is for
		);

	//
	// Also put it under word Wount in the main menu,
	//
	XAP_Menu_Id mainID = pFact->addNewMenuAfter(
			"Main",NULL,"&Word Count",EV_MLF_Normal
			);
	pFact->addNewLabel(
			NULL,mainID,AbiFestVox_MenuLabel,
			AbiFestVox_MenuTooltip
			);

	// Create the Action that will be called.
	EV_Menu_Action* mainAction = new EV_Menu_Action(
		mainID,                 // id that the layout said we could use
		0,                      // no, we don't have a sub menu.
		1,                      // yes, we raise a dialog.
		0,                      // no, we don't have a checkbox.
		callbackStr,            // name of callback function to call.
		NULL,                   // don't know/care what this is for
		NULL                    // don't know/care what this is for
		);

	// Now what we need to do is add this particular action to the ActionSet
	// of the application.  This forms the link between our new ID that we 
	// got for this particular frame with the EditMethod that knows how to 
	// call our callback function.  

	pActionSet->addAction(contextAction);
	pActionSet->addAction(mainAction);
    
	for(int i = 0;i < frameCount;++i) {
		// Get the current frame that we're iterating through.
		XAP_Frame* pFrame = pApp->getFrame(i);
		pFrame->rebuildMenus();
    }
}

static void AbiFestVox_RemoveFromMenus () {
	// First we need to get a pointer to the application itself.
	XAP_App *pApp = XAP_App::getApp();

	// remove the edit method
	EV_EditMethodContainer* pEMC = pApp->getEditMethodContainer() ;
	EV_EditMethod * pEM = ev_EditMethod_lookup ( callbackStr ) ;
	pEMC->removeEditMethod ( pEM ) ;
	DELETEP( pEM ) ;

	// now remove crap from the menus
	int frameCount = pApp->getFrameCount();
	XAP_Menu_Factory * pFact = pApp->getMenuFactory();

	pFact->removeMenuItem("contextText",NULL,AbiFestVox_MenuLabel);
	pFact->removeMenuItem("contextText",NULL,AbiFestVox_ContextMenuLabel);
	for(int i = 0;i < frameCount;++i) {
		// Get the current frame that we're iterating through.
		XAP_Frame* pFrame = pApp->getFrame(i);
		pFrame->rebuildMenus();
	}
}
    
static bool AbiFestVox_invoke(AV_View* v, EV_EditMethodCallData *d) {
	return true;
}

// -----------------------------------------------------------------------
//
//      Abiword Plugin Interface 
//
// -----------------------------------------------------------------------
    
ABI_FAR_CALL int abi_plugin_register (XAP_ModuleInfo * mi) {
    mi->name = "AbiFestVox";
    mi->desc = "Use this to hear documents or selected portions of text.";
    mi->version = ABI_VERSION_STRING;
    mi->author = "Rui Miguel Silva Seabra <rms@1407.org>";
    mi->usage = "No Usage";
    
    // Add to AbiWord's menus.
    AbiFestVox_addToMenus();
    
    return 1;
}


ABI_FAR_CALL int abi_plugin_unregister (XAP_ModuleInfo * mi) {
    mi->name = 0;
    mi->desc = 0;
    mi->version = 0;
    mi->author = 0;
    mi->usage = 0;

    AbiFestVox_RemoveFromMenus ();

    return 1;
}


ABI_FAR_CALL int abi_plugin_supports_version (
		UT_uint32 major, UT_uint32 minor, UT_uint32 release) {
    return 1; 
}


