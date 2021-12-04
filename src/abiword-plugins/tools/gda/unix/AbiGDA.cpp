/* -*- Mode: C++; tab-width: 8; c-basic-offset: 8 -*- */

/* AbiGDA.cpp - hook up AbiWord to SQL databases
 *
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
 */

#include "xap_Module.h"
#include "xap_App.h"
#include "xap_Frame.h"
#include "fv_View.h"
#include "pd_Document.h"
#include "ap_Menu_Id.h"
#include "ev_Menu_Actions.h"
#include "ev_Menu.h"
#include "ev_Menu_Layouts.h"
#include "ev_Menu_Labels.h"
#include "ev_EditMethod.h"
#include "xap_Menu_Layouts.h"
#include "ut_string_class.h"

#include "xap_UnixFrameImpl.h"
#include "xap_UnixDialogHelper.h"

#include <gtk/gtk.h>
#include <libgda/libgda.h>
#include <libgnomedb/libgnomedb.h>

static const char* GDA_MenuLabel   = "G&DA Database";
static const char* GDA_MenuTooltip = "Mailmerge using a database";
static GdaClient*  connection_pool = NULL;

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------

static bool
handle_recordset (GdaDataModel *recset, PD_Document * pDoc)
{
	gint col = 0;
	gint row = 0;
	gint fieldcount = 0;
	gint rowcount   = 0;
	
	g_return_val_if_fail (GDA_IS_DATA_MODEL (recset), false);
	
	fieldcount = gda_data_model_get_n_columns (GDA_DATA_MODEL (recset));
	rowcount = gda_data_model_get_n_rows (GDA_DATA_MODEL (recset));
	
	if (rowcount <= 0)
		return false;
	
	// TODO: we can only handle 1 row's worth of data ATM
	//for (row = 0; row < rowcount; row++) 
	for (col = 0; col < fieldcount; col++) {
		gchar *str;
		const gchar *title;
		const GdaValue *value;
		
		value = gda_data_model_get_value_at (GDA_DATA_MODEL (recset),
						     col, row);
		str = gda_value_stringify ((GdaValue *) value);
		title = gda_data_model_get_column_title (GDA_DATA_MODEL (recset), col);
		
		pDoc->setMailMergeField (title, str);
		
		g_free (str);
	}
	
	return true;
}

static bool
gda_ok_pressed (GtkWidget * login, GtkWidget * txt, PD_Document * pDoc)
{
	UT_UTF8String dsn_name, user_name, password, sql;	
	
	GdaConnection* cnc;
	GdaDataModel*  recset;
	GdaCommand*    cmd;

	dsn_name  = gnome_db_login_get_dsn (GNOME_DB_LOGIN(login));
	user_name = gnome_db_login_get_username (GNOME_DB_LOGIN(login));
	password  = gnome_db_login_get_password (GNOME_DB_LOGIN(login));

	GtkTextIter start, end;
	
	GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (txt));
	gtk_text_buffer_get_iter_at_offset (buffer, &start, 0);
	gtk_text_buffer_get_iter_at_offset (buffer, &end, -1);
	
	char * editable_txt = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);
	sql = editable_txt;
	g_free (editable_txt);
	
#if 0
	g_print ("dsn: %s\n", dsn_name.utf8_str());
	g_print ("user: %s\n", user_name.utf8_str());
	g_print ("pass: %s\n", password.utf8_str());
	g_print ("sql: %s\n", sql.utf8_str());
#endif

	// todo: investigate also using GDA_CONNECTION_OPTIONS_READ_ONLY
	cnc = gda_client_open_connection (connection_pool, dsn_name.utf8_str(), user_name.utf8_str(), password.utf8_str());
	if (!GDA_IS_CONNECTION (cnc))
		return false;
	
	/* execute command */
	cmd = gda_command_new (sql.utf8_str(), GDA_COMMAND_TYPE_SQL, (GdaCommandOptions)0);
	recset = gda_connection_execute_single_command (cnc, cmd, NULL);
	gda_command_free (cmd);
	
	if (recset == NULL || !GDA_IS_DATA_MODEL (recset))
		return false;
	else
		return handle_recordset (recset, pDoc);  
}

//
// GDA_execSQL
// -------------------
//   This is the function that we actually call to invoke the thesaurus.
//   It should be called when the user hits the thesaurus key (shift+f7?)
//   or chooses "thesaurus" from a menu.
//
static bool 
GDA_execSQL(AV_View* v, EV_EditMethodCallData *d)
{
	// Get the current view that the user is in.
	XAP_Frame *pFrame = XAP_App::getApp()->getLastFocussedFrame();
	FV_View* pView = static_cast<FV_View*>(pFrame->getCurrentView());
	
	GtkWidget * dlg;
	GtkWidget * db_login;
	GtkWidget * text;
	GtkWidget * table;
	GtkWidget * label;

	bool ret = false;

	dlg = abiDialogNew ("gda database", FALSE, "GDA Mailmerge");
	abiAddStockButton(GTK_DIALOG(dlg), GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL);
	abiAddStockButton(GTK_DIALOG(dlg), GTK_STOCK_OK, GTK_RESPONSE_OK);

	db_login = gnome_db_login_new (NULL);
	text = gtk_text_view_new ();
	gtk_widget_set_usize (text, 150, 100);

	table = gnome_db_new_table_widget (1, 2, FALSE);
	label = gnome_db_new_label_widget ("Command");
	gtk_table_attach (GTK_TABLE (table), label, 0, 1, 0, 1, GTK_FILL, GTK_FILL, 2, 2);
	gtk_table_attach (GTK_TABLE (table), text, 1, 2, 0, 1,
			  GTK_FILL, GTK_FILL, 2, 2);

	gtk_container_add (GTK_CONTAINER(GTK_DIALOG(dlg)->vbox), db_login);
	gtk_container_add (GTK_CONTAINER(GTK_DIALOG(dlg)->vbox), table);

	gtk_widget_show_all (dlg);

	switch (abiRunModalDialog (GTK_DIALOG(dlg), pFrame, NULL, GTK_RESPONSE_CANCEL, false))
		{
		case GTK_RESPONSE_OK:
			ret = gda_ok_pressed (db_login, text, pView->getDocument ());
			break;
		}

	abiDestroyWidget (dlg);

	return ret;
}

static void
GDA_removeFromMenus()
{
	// First we need to get a pointer to the application itself.
	XAP_App *pApp = XAP_App::getApp();
	
	// remove the edit method
	EV_EditMethodContainer* pEMC = pApp->getEditMethodContainer() ;
	EV_EditMethod * pEM = ev_EditMethod_lookup ( "GDA_execSQL" ) ;
	pEMC->removeEditMethod ( pEM ) ;
	DELETEP( pEM ) ;
	
	// now remove crap from the menus
	int frameCount = pApp->getFrameCount();
	XAP_Menu_Factory * pFact = pApp->getMenuFactory();
	
	pFact->removeMenuItem("Main",NULL,GDA_MenuLabel);
	for(int i = 0; i < frameCount; ++i)
		{
			// Get the current frame that we're iterating through.
			XAP_Frame* pFrame = pApp->getFrame(i);
			pFrame->rebuildMenus();
		}
}

static void
GDA_addToMenus()
{
	// First we need to get a pointer to the application itself.
	XAP_App *pApp = XAP_App::getApp();
	
	// Create an EditMethod that will link our method's name with
	// it's callback function.  This is used to link the name to 
	// the callback.
	EV_EditMethod *myEditMethod = new EV_EditMethod("GDA_execSQL",  // name of callback function
							GDA_execSQL,    // callback function itself.
							0,                      // no additional data required.
							""                      // description -- allegedly never used for anything
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
	// Put it in the main menu.
	//
	XAP_Menu_Id newID = pFact->addNewMenuAfter("Main",NULL,"&Mail Merge",EV_MLF_Normal);
	pFact->addNewLabel(NULL,newID,GDA_MenuLabel, GDA_MenuTooltip);
	
	// Create the Action that will be called.
	EV_Menu_Action* myAction = new EV_Menu_Action(newID,                     // id that the layout said we could use
						      0,                      // no, we don't have a sub menu.
						      1,                      // yes, we raise a dialog.
						      0,                      // no, we don't have a checkbox.
						      "GDA_execSQL",  // name of callback function to call.
						      NULL,                   // don't know/care what this is for
						      NULL                    // don't know/care what this is for
						      );
	
	// Now what we need to do is add this particular action to the ActionSet
	// of the application.  This forms the link between our new ID that we 
	// got for this particular frame with the EditMethod that knows how to 
	// call our callback function.  
	
	pActionSet->addAction(myAction);
	
	for(int i = 0; i < frameCount; ++i)
		{
			// Get the current frame that we're iterating through.
			XAP_Frame* pFrame = pApp->getFrame(i);
			pFrame->rebuildMenus();
		}
}

// -----------------------------------------------------------------------
//
//      Abiword Plugin Interface 
//
// -----------------------------------------------------------------------

ABI_FAR_CALL
int abi_plugin_register (XAP_ModuleInfo * mi)
{
	/* initialize connection pool if first time */
	if (!GDA_IS_CLIENT (connection_pool)) {
		connection_pool = gda_client_new ();
		if (!connection_pool)
			return 0;
	}
	
	mi->name    = "GDA plugin";
	mi->desc    = "Database support for AbiWord";
	mi->version = ABI_VERSION_STRING;
	mi->author  = "Dom Lachowicz <cinamod@hotmail.com>";
	mi->usage   = "You had better know some SQL...";
	
	// Add the database to AbiWord's menus.
	GDA_addToMenus();
	
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
	
	GDA_removeFromMenus () ;
	
	if (GDA_IS_CLIENT (connection_pool)) {
		g_object_unref (G_OBJECT (connection_pool));
		connection_pool = NULL;
	}
	
	return 1;
}


ABI_FAR_CALL
int abi_plugin_supports_version (UT_uint32 major, UT_uint32 minor, UT_uint32 release)
{
	return 1; 
}
