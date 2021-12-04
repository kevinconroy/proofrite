/*
 * Grammar Checker plugin for AbiWord
 * Copyright (C) 2002 by Dom Lachowicz
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
 *
 */

#include <stdlib.h>
#include <stdio.h>

// Abi includes

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

#include "ut_assert.h"
#include "ut_debugmsg.h"

#include "ut_string_class.h"
#include "GrammarChecker.h"

// see LinkGrammarChecker.h's disclaimer
#if defined(USE_LINK)
#include "LinkGrammarChecker.h"
#else
#include "NullGrammarChecker.h"
#endif

/**************************************************************************/
/**************************************************************************/

// our edit method/callback function
static bool EnUs_Grammar_ABI_invoke(AV_View* v, EV_EditMethodCallData *d);

// our menu strings
static const char* EnUs_Grammar_ABI_MenuLabel = "&Grammar Check";
static const char* EnUs_Grammar_ABI_MenuTooltip = "Runs an english grammar check of your document";

// our grammar checker
static IGrammarChecker * s_gmr_chk = NULL ;

/**************************************************************************/
/**************************************************************************/

static void
EnUs_Grammar_ABI_removeFromMenus()
{
  // First we need to get a pointer to the application itself.
  XAP_App *pApp = XAP_App::getApp();

  // remove the edit method
  EV_EditMethodContainer* pEMC = pApp->getEditMethodContainer() ;
  EV_EditMethod * pEM = ev_EditMethod_lookup ( "EnUs_Grammar_ABI_invoke" ) ;
  pEMC->removeEditMethod ( pEM ) ;
  DELETEP( pEM ) ;

  // now remove crap from the menus
  int frameCount = pApp->getFrameCount();
  XAP_Menu_Factory * pFact = pApp->getMenuFactory();

  pFact->removeMenuItem("Main",NULL,EnUs_Grammar_ABI_MenuLabel);
  pFact->removeMenuItem("contextText",NULL,EnUs_Grammar_ABI_MenuLabel);
  for(int i = 0;i < frameCount;++i)
    {
      // Get the current frame that we're iterating through.
      XAP_Frame* pFrame = pApp->getFrame(i);
      pFrame->rebuildMenus();
    }
}

//
// EnUs_Grammar_ABI_addToMenus
// -----------------------
//   Adds "Grammar Checker" option to AbiWord's Tools Menu.
//
static void
EnUs_Grammar_ABI_addToMenus()
{
  // First we need to get a pointer to the application itself.
  XAP_App *pApp = XAP_App::getApp();
  
  
  // Create an EditMethod that will link our method's name with
  // it's callback function.  This is used to link the name to 
  // the callback.
  EV_EditMethod *myEditMethod = new EV_EditMethod(
						  "EnUs_Grammar_ABI_invoke",  // name of callback function
						  EnUs_Grammar_ABI_invoke,    // callback function itself.
						  0,                      // no additional data required.
						  ""                      // description -- allegedly never used for anything
						  );
  
  // Now we need to get the EditMethod container for the application.
  // This holds a series of Edit Methods and links names to callbacks.
  EV_EditMethodContainer* pEMC = pApp->getEditMethodContainer();
  
  // We have to add our EditMethod to the application's EditMethodList
  // so that the application will know what callback to call when a call
  // to "EnUs_Grammar_ABI_invoke" is received.
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
  XAP_Menu_Id newID = pFact->addNewMenuAfter("contextText",NULL,"Bullets and &Numbering",EV_MLF_Normal);
  pFact->addNewLabel(NULL,newID,EnUs_Grammar_ABI_MenuLabel, EnUs_Grammar_ABI_MenuTooltip);
  //
  // Also put it under word Wount in the main menu,
  //
  pFact->addNewMenuAfter("Main",NULL,"&Word Count",EV_MLF_Normal,newID);
  
  // Create the Action that will be called.
  EV_Menu_Action* myAction = new EV_Menu_Action(
						newID,                     // id that the layout said we could use
						0,                      // no, we don't have a sub menu.
						1,                      // yes, we raise a dialog.
						0,                      // no, we don't have a checkbox.
						"EnUs_Grammar_ABI_invoke",  // name of callback function to call.
						NULL,                   // don't know/care what this is for
						NULL                    // don't know/care what this is for
						);
  
  // Now what we need to do is add this particular action to the ActionSet
  // of the application.  This forms the link between our new ID that we 
  // got for this particular frame with the EditMethod that knows how to 
  // call our callback function.  
  
  pActionSet->addAction(myAction);
  
  for(int i = 0;i < frameCount;++i)
    {
        // Get the current frame that we're iterating through.
      XAP_Frame* pFrame = pApp->getFrame(i);
      pFrame->rebuildMenus();
    }
}

/**************************************************************************/
/**************************************************************************/

//
// EnUs_Grammar_ABI_ucsToAscii
// -----------------------
//   Helper function to convert UCS-2 strings into Ascii.
//   NOTE: you must call delete[] on the returned test!!!
//
inline static char*
EnUs_Grammar_ABI_ucsToAscii(const UT_UCSChar* text)
{
  // calculate length of text so that we can create a character
    // buffer of equal size.
  const unsigned int length = UT_UCS_strlen(text);
  
  // allocate ascii characters plus room for a null terminator.    
  char* ret = new char[length+1];
        
  // do the string conversion.  this is simple we just cast to 
    // char since UCS-2 is the same as Ascii for english.    
  for(unsigned int i = 0;i < length;++i)
    {
      ret[i] = (char)text[i];
    }
  
  // finally null terminate the string.    
  ret[length] = '\0';

  // and now return it.
  return ret;    
}

//
// EnUs_Grammar_ABI_asciiToUcs
// -----------------------
//   Helper function to convert Ascii strings into UCS-2.
//   NOTE: you must call delete[] on the returned text!!!
//
inline static UT_UCSChar* 
EnUs_Grammar_ABI_asciiToUcs(const char* text, int& length)
{
  // calculate the length of our text so we can create a UCS-2
  // buffer of equal size.
  length = strlen(text);
  
  // allocate UCS-2 character buffer of same size, plus room for 
  // a null terminator.    
  UT_UCSChar* ret = new UT_UCSChar[length+1];
  
  // convert ascii to UCS-2.  This is simply a cast-loop really.
  for(int i = 0;i < length;++i)
        {
	  ret[i] = (UT_UCSChar)text[i];
        }
  
  // remember to null terminate the string.
  ret[length] = 0;
  
  // now return the string.
  return ret;
}

/**************************************************************************/
/**************************************************************************/

bool EnUs_Grammar_ABI_invoke(AV_View* v, EV_EditMethodCallData *d)
{
  // Get the current view that the user is in.
  XAP_Frame *pFrame = XAP_App::getApp()->getLastFocussedFrame();
  FV_View* pView = static_cast<FV_View*>(pFrame->getCurrentView());
  
  // move to the beginning of the document
  // pView->moveInsPtTo(FV_DOCPOS_BOD);
  
  UT_DEBUGMSG(("DOM: started grammar check!\n"));
  
  UT_ASSERT(s_gmr_chk != NULL);
  if ( NULL == s_gmr_chk )
    return false ;
  
  // main parsing loop
  while ( true )
    {
	// acquire the current sentence
	// pView->extSelTo ( FV_DOCPOS_EOS ) ;

	if (pView->isSelectionEmpty ())
	  {
	    UT_DEBUGMSG(( "Empty selection!\n" )) ;
	    break ;
	  }

	UT_UCSChar * ucs_text = pView->getSelectionText () ;

	if ( !ucs_text || UT_UCS_strlen ( ucs_text ) == 0 )
	  {
	    UT_DEBUGMSG(( "NULL or 0 length input text\n" )) ;
	    break ;
	  }

	char * input_string = EnUs_Grammar_ABI_ucsToAscii(ucs_text);

	UT_DEBUGMSG(( "DOM: input string is %s\n" , input_string )) ;

	if (!s_gmr_chk->check( input_string ))
	  {
	    // show bogus sentence in some meaningful way
	    UT_DEBUGMSG(( "BOGUS Sentence! '%s'\n", input_string )) ;
	  }
	else
	  {
	    UT_DEBUGMSG(( "Good sentence!\n" )) ;
	  }

	delete [] input_string;

	// move the cursor to the end of sentence and continue
	// pView->moveInsPtTo ( FV_DOCPOS_EOS );
	break;
      }

    return true;
}

/**************************************************************************/
/**************************************************************************/

ABI_PLUGIN_DECLARE("EnUsGrammarChecker");

ABI_FAR_CALL
int abi_plugin_register (XAP_ModuleInfo * mi)
{
    mi->name = "English Grammar Checker" ;
    mi->desc = "English-language grammar checker" ;
    mi->version = ABI_VERSION_STRING;
    mi->author = "Dom Lachowicz <cinamod@hotmail.com>" ;
    mi->usage = "No Usage"  ;

    try 
      {
	s_gmr_chk = new IGrammarCheckerInstance ;
      }
    catch( ... )
      {
	return 0 ;
      }

    // Add the thesaurus to AbiWord's menus.
    EnUs_Grammar_ABI_addToMenus() ;
    
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

    if ( s_gmr_chk != NULL )
      {
	DELETEP( s_gmr_chk ) ;
      }

    EnUs_Grammar_ABI_removeFromMenus() ;

    return 1;
}


ABI_FAR_CALL
int abi_plugin_supports_version (UT_uint32 major, UT_uint32 minor, UT_uint32 release)
{
    return 1 ; 
}

/**************************************************************************/
/**************************************************************************/
