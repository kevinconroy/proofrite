/* AbiWord
 * Copyright (C) 2002 Nicolas Mercier <nscreetch@free.fr>
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

/*****************************************************************************\
* projet Oeuf - Coquille : module d'importation/exportation de fichier pour   *
*                          Abiword                                            *
* Nicolas MERCIER <nmr@infobi.com>                                            *
*                                                                             *
* 05/07/2002                                                                  *
\*****************************************************************************/

#include	<stdio.h>
#include <errno.h>

#if TIME_WITH_SYS_TIME
#include <sys/time.h>
#include <time.h>
#else
#if HAVE_SYS_TIME_H
#include <sys/time.h>
#else
#include <time.h>
#endif
#endif

// Coquille
#include	"coquille.h"
#include	"coquilleImp.h"
#include	"coquilleExp.h"
#include	"xap_App.h"
#include	"xap_Frame.h"
#include	"xap_Menu_Layouts.h"
#include	"fv_View.h"
#include	"ap_Menu_Id.h"
#include	"ev_Menu_Actions.h"
#include	"ev_Menu.h"
#include	"ev_Menu_Layouts.h"
#include	"ev_Menu_Labels.h"
#include	"ev_EditMethod.h"
// AbiWord includes
#include	"xap_App.h"
#include	"xap_Module.h"
#include	"ut_map.h"
#include	"ut_vector.h"

// autres includes
#include	<string.h>
// #include	<stl.h>

/*****************************************************************************/
ABI_PLUGIN_DECLARE	("Coquille")

/* version du module */
#define	PLUGIN_VERSION	"0.85"
/* version 1.0.0  de AbiWord (au moins) */
#define	PLUGIN_MAJOR	1
#define	PLUGIN_MINOR	0
#define	PLUGIN_REL		0

static IE_Imp_Coquille_Sniffer * m_impCSniffer = NULL;
static IE_Exp_Coquille_Sniffer * m_expCSniffer = NULL;


UT_Vector header_values (5);
/* creation date */
int m_dDay, m_dMonth, m_dYear;

UT_Vector * get_header (void)
{
	return &header_values;
}
/*****************************************************************************/
keyvalue :: keyvalue (char *key, char *value)
{
	m_key = new UT_String (key);
	m_value = new UT_String (value);
}

keyvalue :: ~keyvalue ()
{
//	delete m_key;
//	delete m_value;
}
/*****************************************************************************/
ABI_FAR_CALL int abi_plugin_register (XAP_ModuleInfo * mi)
{
	time_t doc_time;	// Current time
	struct tm *doc_date;	// Current date

	char key [100];
	char value [100];
	char tmp [2];

	/* coquille sniffers */
	if (!m_impCSniffer)
		m_impCSniffer = new IE_Imp_Coquille_Sniffer ();
	else
		m_impCSniffer -> ref();

	if (!m_expCSniffer)
		m_expCSniffer = new IE_Exp_Coquille_Sniffer ();
	else
		m_expCSniffer -> ref();


	mi -> name = DOCUMENT_NAME " Importer/Exporter";
	mi -> desc = "Import/Export " DOCUMENT_NAME " Documents\n";
	mi -> version = PLUGIN_VERSION;
	mi -> author = "Nicolas MERCIER <linux@infobi.com> / Infobi";
	mi -> usage = "No usage";
	
	IE_Imp::registerImporter (m_impCSniffer);
	IE_Exp::registerExporter (m_expCSniffer);

	/* opens configuration file */
	FILE *file = NULL;
	file = fopen (
			UT_catPathname (XAP_App::getApp () -> getUserPrivateDirectory (), "coquille.conf"),
			"r"
		);
	if (!file)
			file = fopen (
				UT_catPathname (XAP_App::getApp () -> getAbiSuiteLibDir (), "coquille.conf"),
			"r"
		);
	if (!file)
	{
		/* not our days: the file doesn't exist :( */
		/* ok, let's create it =) */
		file = fopen (
			UT_catPathname (XAP_App::getApp () -> getUserPrivateDirectory (), "coquille.conf"),
			"w+"
		);
		fprintf (file, "coq-title=\n");
		fprintf (file, "coq-version=\n");
		fprintf (file, "coq-author=\n");
		fprintf (file, "coq-validation=\n");
		fprintf (file, "coq-codaff=\n");
		fclose (file);
		file = fopen (
			UT_catPathname (XAP_App::getApp () -> getUserPrivateDirectory (), "coquille.conf"),
			"r"
		);

	}

	if (file)
	{
		//printf ("file opened!\n");
		while (! feof (file))
		{
			int result = fscanf (file, " %100[^=]%1[=]%100[^\n] ", key, tmp, value);
			if (result < 1) continue;
			if (result < 3) *value = '\0';

			header_values . push_back ((void *) new keyvalue (key, value));
		}
	}

	/* current date */
	doc_time = time (NULL);
	doc_date = localtime (&doc_time);
	m_dDay = doc_date -> tm_mday;			/* jour */
	m_dMonth = doc_date -> tm_mon + 1;		/* mois */
	m_dYear = doc_date -> tm_year + 1900;	/* année */

	return 1;
}
/*****************************************************************************/

/*****************************************************************************/
ABI_FAR_CALL int abi_plugin_unregister (XAP_ModuleInfo * mi)
{
	memset ((void *) mi, 0, sizeof (XAP_ModuleInfo));

//	UT_ASSERT (m_impCSniffer);
//	UT_ASSERT (m_expCSniffer);

	IE_Imp::unregisterImporter (m_impCSniffer);
	if (!m_impCSniffer->unref())
	{
		delete m_impCSniffer;
		m_impCSniffer = NULL;
	}

	IE_Exp::unregisterExporter (m_expCSniffer);
	if (!m_expCSniffer->unref())
	{
		delete m_expCSniffer;
		m_expCSniffer = NULL;
	}
	return 1;
}
/*****************************************************************************/

/*****************************************************************************/
ABI_FAR_CALL int abi_plugin_supports_version (int major, int minor, int rel)
{
	if (
			(major > PLUGIN_MAJOR)
		||	(major == PLUGIN_MAJOR && minor > PLUGIN_MINOR)
		||	(major == PLUGIN_MAJOR && minor == PLUGIN_MINOR && rel >= PLUGIN_REL)
	)
	{
		return 1;
	}
	else
	{
		UT_DEBUGMSG(("FAILED!\n"));
		UT_DEBUGMSG(("plugin only supports versions 1.0.0 and above of AbiWord\n"));
		return 0;
	}
}
/*****************************************************************************/

/* i don't need this anymore */
#if	0

static const char* MenuLabel = "&Editer l'en-tête";
static const char* MenuTooltip = "Permet de modifier les informations de l'en-tête";

/*****************************************************************************/
static bool dbx_invoke(AV_View* v, EV_EditMethodCallData *d)
{
	/* ouvre une zoulie boite de dialogue */

	/* this code was created by me, without any model.
	 * there is a very high probability that it doesn't work =( */

	return true;
}

static void addToMenus (void)
{
	/* this code was mostly taken from AbiGimp plugin */
	
	// First we need to get a pointer to the application itself.
	XAP_App *pApp = XAP_App::getApp();

	
	// Create an EditMethod that will link our method's name with
	// it's callback function.  This is used to link the name to 
	// the callback.
	EV_EditMethod *myEditMethod = new EV_EditMethod(
		"dbx_invoke",		// name of callback function
		dbx_invoke,			// callback function itself.
		0,					// no additional data required.
		""					// description -- allegedly never used for anything
	);
   
	// Now we need to get the EditMethod container for the application.
	// This holds a series of Edit Methods and links names to callbacks.
	EV_EditMethodContainer* pEMC = pApp->getEditMethodContainer();
	
	// We have to add our EditMethod to the application's EditMethodList
	// so that the application will know what callback to call when a call
	// to "AiksaurusABI_invoke" is received.
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
	XAP_Menu_Id newID = pFact->addNewMenuAfter("ContextText",NULL,"&Hyperlink",EV_MLF_Normal);
	pFact->addNewLabel(NULL,newID,MenuLabel, MenuTooltip);

// Put it after Word Count in the Main menu

	pFact->addNewMenuAfter("Main",NULL,"&Word Count",EV_MLF_Normal,newID);
//
// Also put it under word Count in the main menu,
//
	// Create the Action that will be called.
	EV_Menu_Action* myAction = new EV_Menu_Action(
	newID,					 // id that the layout said we could use
	0,					  // no, we don't have a sub menu.
	1,					  // yes, we raise a dialog.
	0,					  // no, we don't have a checkbox.
	"dbx_invoke",  // name of callback function to call.
	NULL,				   // don't know/care what this is for
	NULL					// don't know/care what this is for
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

static void removeFromMenus (void)
{
  // First we need to get a pointer to the application itself.
  XAP_App *pApp = XAP_App::getApp();

  // remove the edit method
  EV_EditMethodContainer* pEMC = pApp->getEditMethodContainer() ;
  EV_EditMethod * pEM = ev_EditMethod_lookup ( "dbx_invoke" ) ;
  pEMC->removeEditMethod ( pEM ) ;
  DELETEP( pEM ) ;

  // now remove crap from the menus
  int frameCount = pApp->getFrameCount();
  XAP_Menu_Factory * pFact = pApp->getMenuFactory();

  pFact->removeMenuItem("Main",NULL,MenuLabel);
  pFact->removeMenuItem("ContextText",NULL,MenuLabel);
  for(int i = 0;i < frameCount;++i)
  {
      // Get the current frame that we're iterating through.
      XAP_Frame* pFrame = pApp->getFrame(i);
      pFrame->rebuildMenus();
  }
}
/*****************************************************************************/
#endif
