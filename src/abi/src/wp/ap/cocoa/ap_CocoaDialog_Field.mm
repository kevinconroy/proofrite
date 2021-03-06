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
#include <time.h>

#include "ut_string.h"
#include "ut_assert.h"
#include "ut_debugmsg.h"

// This header defines some functions for Cocoa dialogs,
// like centering them, measuring them, etc.
#include "xap_CocoaDialogHelper.h"

#include "xap_App.h"
#include "xap_CocoaApp.h"
#include "xap_CocoaFrame.h"

#include "ap_Strings.h"
#include "ap_Dialog_Id.h"
#include "ap_Dialog_Field.h"
#include "ap_CocoaDialog_Field.h"


/*****************************************************************/

#define	LIST_ITEM_INDEX_KEY "index"

/*****************************************************************/

XAP_Dialog * AP_CocoaDialog_Field::static_constructor(XAP_DialogFactory * pFactory,
													 XAP_Dialog_Id id)
{
	AP_CocoaDialog_Field * p = new AP_CocoaDialog_Field(pFactory,id);
	return p;
}

AP_CocoaDialog_Field::AP_CocoaDialog_Field(XAP_DialogFactory * pDlgFactory,
										 XAP_Dialog_Id id)
	: AP_Dialog_Field(pDlgFactory,id)
{
	m_windowMain = NULL;

	m_buttonOK = NULL;
	m_buttonCancel = NULL;

	m_listTypes = NULL;
	m_listFields = NULL;
	m_entryParam = NULL;
}

AP_CocoaDialog_Field::~AP_CocoaDialog_Field(void)
{
}


/*****************************************************************/

static void s_ok_clicked(GtkWidget * widget, AP_CocoaDialog_Field * dlg)
{
	UT_ASSERT(widget && dlg);
	dlg->event_OK();
}

static void s_cancel_clicked(GtkWidget * widget, AP_CocoaDialog_Field * dlg)
{
	UT_ASSERT(widget && dlg);
	dlg->event_Cancel();
}

static void s_types_clicked(GtkWidget * widget, gint row, gint column,
							GdkEventButton *event, AP_CocoaDialog_Field * dlg)
{
	UT_ASSERT(widget && dlg);
	dlg->types_changed(row);
}

static void s_delete_clicked(GtkWidget * /* widget */,
							 gpointer /* data */,
							 AP_CocoaDialog_Field * dlg)
{
	UT_ASSERT(dlg);
	dlg->event_WindowDelete();
}


/*****************************************************************/

void AP_CocoaDialog_Field::runModal(XAP_Frame * pFrame)
{
	UT_ASSERT(pFrame);
	// Build the window's widgets and arrange them
	GtkWidget * mainWindow = _constructWindow();
	UT_ASSERT(mainWindow);

	connectFocus(GTK_WIDGET(mainWindow),pFrame);

	// Populate the window's data items
	_populateCatogries();
	
	// To center the dialog, we need the frame of its parent.
	XAP_CocoaFrame * pCocoaFrame = static_cast<XAP_CocoaFrame *>(pFrame);
	UT_ASSERT(pCocoaFrame);
	
	// Get the GtkWindow of the parent frame
	GtkWidget * parentWindow = pCocoaFrame->getTopLevelWindow();
	UT_ASSERT(parentWindow);
	
	// Center our new dialog in its parent and make it a transient
	// so it won't get lost underneath
	centerDialog(parentWindow, mainWindow);

	// Make it modal, and stick it up top
	gtk_grab_add(mainWindow);

	// Show the top level dialog,
	gtk_widget_show_all(mainWindow);

	// Run into the GTK event loop for this window.
	gtk_main();

	if(mainWindow && GTK_IS_WIDGET(mainWindow))
	  gtk_widget_destroy(mainWindow);
}


void AP_CocoaDialog_Field::event_OK(void)
{
	UT_ASSERT(m_windowMain && m_listTypes && m_listFields);
	
	// find item selected in the Types list box, save it to m_iTypeIndex

	GList * typeslistitem = GTK_CLIST(m_listTypes)->selection;

	// if there is no selection
	// is empty, return cancel.  GTK can make this happen.
	if (!(typeslistitem))
	{
		m_answer = AP_Dialog_Field::a_CANCEL;
		gtk_main_quit();
		return;
	}
	// since we only do single mode selection, there is only one
	// item in the GList we just got back

	// For a CList the data value is actually just the row number. We can
	// use this as index to get the actual data value for the row.

	gint indexrow = GPOINTER_TO_INT (typeslistitem->data);
	m_iTypeIndex =  GPOINTER_TO_INT (gtk_clist_get_row_data (GTK_CLIST (m_listTypes), indexrow));
	
	// find item selected in the Field list box, save it to m_iFormatIndex
	GList * fieldslistitem = GTK_CLIST (m_listFields)->selection;

	// if there is no selection
	// is empty, return cancel.  GTK can make this happen.
	if (!(fieldslistitem))
	{
		m_answer = AP_Dialog_Field::a_CANCEL;
		gtk_main_quit();
		return;
	}


	// For a CList the data value is actually just the row number. We can
	// use this as index to get the actual data value for the row.
	indexrow = GPOINTER_TO_INT(fieldslistitem->data);
	m_iFormatIndex = GPOINTER_TO_INT(gtk_clist_get_row_data( GTK_CLIST(m_listFields),indexrow));
	
	setParameter(gtk_entry_get_text(GTK_ENTRY(m_entryParam)));
	m_answer = AP_Dialog_Field::a_OK;
	gtk_main_quit();
}


void AP_CocoaDialog_Field::types_changed(gint row)
{
	UT_ASSERT(m_windowMain && m_listTypes);

	// Update m_iTypeIndex with the row number
	m_iTypeIndex = row;

	// Update the fields list with this new Type
	setFieldsList();
}

void AP_CocoaDialog_Field::event_Cancel(void)
{
	m_answer = AP_Dialog_Field::a_CANCEL;
	gtk_main_quit();
}

void AP_CocoaDialog_Field::event_WindowDelete(void)
{
	m_answer = AP_Dialog_Field::a_CANCEL;	
	gtk_main_quit();
}


void AP_CocoaDialog_Field::setTypesList(void)
{
	gint i;
	gint cnt = 0;
	GtkCList * c_listTypes = GTK_CLIST(m_listTypes);
	for (i = 0;fp_FieldTypes[i].m_Desc != NULL;i++) 
	{
		gtk_clist_append(c_listTypes, (gchar **) & fp_FieldTypes[i].m_Desc  );
		// store index in data pointer
		gtk_clist_set_row_data( c_listTypes, cnt, GINT_TO_POINTER(i));
		cnt++;
	}
	// now select first item in box
	if (i > 0)
	{		
		gtk_clist_select_row(c_listTypes, 0,0);
		m_iTypeIndex = 0;
	}
	else
	{
		UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
	}
}

void AP_CocoaDialog_Field::setFieldsList(void)
{
	UT_ASSERT(m_listFields);
	fp_FieldTypesEnum  FType = fp_FieldTypes[m_iTypeIndex].m_Type;
	gint i;
	GtkCList * c_listFields = GTK_CLIST(m_listFields);

	gtk_clist_clear( c_listFields);

	gint cnt = 0;
	for (i = 0; fp_FieldFmts[i].m_Tag != NULL; i++) 
	{
		if (fp_FieldFmts[i].m_Type == FType)
		{
			gtk_clist_append(c_listFields, (gchar **) & fp_FieldFmts[i].m_Desc );
			gtk_clist_set_row_data(c_listFields, cnt, GINT_TO_POINTER(i));
			cnt++;
		}
	}

	// now select first item in box
	if (i > 0)
	{		
		gtk_clist_select_row( c_listFields, 0,0);
	}
	else 
	{
		UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
	}
}


/*****************************************************************/


GtkWidget * AP_CocoaDialog_Field::_constructWindow(void)
{
	GtkWidget *hboxMain;
	GtkWidget *vbuttonboxButtons;
	GtkWidget *contents;
	const XAP_StringSet * pSS = m_pApp->getStringSet();

	// Start with the main window
	m_windowMain = gtk_window_new (GTK_WINDOW_DIALOG);
	gtk_container_set_border_width (GTK_CONTAINER (m_windowMain), 10);
	gtk_window_set_title (GTK_WINDOW (m_windowMain), pSS->getValue(AP_STRING_ID_DLG_Field_FieldTitle));
	gtk_window_set_policy (GTK_WINDOW (m_windowMain), FALSE, FALSE, FALSE);

	// Add the hbox to hold the contents and the vbox with the buttons
	hboxMain = gtk_hbox_new (FALSE, 5);
	gtk_widget_show (hboxMain);
	gtk_container_add (GTK_CONTAINER (m_windowMain), hboxMain);

	// Now the contents of the dialog box
	contents = _constructWindowContents ();
	gtk_box_pack_start (GTK_BOX (hboxMain), contents, FALSE, TRUE, 0);

	// Now the two buttons
	vbuttonboxButtons = gtk_vbutton_box_new ();
	gtk_box_pack_start (GTK_BOX (hboxMain), 
						vbuttonboxButtons, FALSE, TRUE, 0);
	gtk_button_box_set_layout (GTK_BUTTON_BOX (vbuttonboxButtons), 
							   GTK_BUTTONBOX_START);

	m_buttonOK = gtk_button_new_with_label (pSS->getValue(XAP_STRING_ID_DLG_OK));
	gtk_container_add (GTK_CONTAINER (vbuttonboxButtons), m_buttonOK);
	GTK_WIDGET_SET_FLAGS (m_buttonOK, GTK_CAN_DEFAULT);

	m_buttonCancel = gtk_button_new_with_label (pSS->getValue(XAP_STRING_ID_DLG_Cancel));
	gtk_container_add (GTK_CONTAINER (vbuttonboxButtons), m_buttonCancel);
	GTK_WIDGET_SET_FLAGS (m_buttonCancel, GTK_CAN_DEFAULT);

	// connect all the signals
	_connectSignals ();

    // The main window is shown with gtk_widget_show_all() in runModal().
    
	return m_windowMain;
}

void AP_CocoaDialog_Field::_populateCatogries(void)
{
	// Fill in the two lists
	setTypesList();
	setFieldsList();
}
	
GtkWidget *AP_CocoaDialog_Field::_constructWindowContents (void)
{
	GtkWidget *hbox;
	GtkWidget *vboxTypes;
	GtkWidget *vboxFields;
	GtkWidget *labelTypes;
	GtkWidget *labelFields;
	GtkWidget *scrolledwindowTypes;
	GtkWidget *scrolledwindowFields;
	GtkWidget *labelParam;
	XML_Char * unixstr = NULL;	// used for conversions
	const XAP_StringSet * pSS = m_pApp->getStringSet();

	hbox = gtk_hbox_new (FALSE, 5);

	// Add the types list vbox
	vboxTypes = gtk_vbox_new (FALSE, 0);
	gtk_box_pack_start (GTK_BOX (hbox), vboxTypes, TRUE, TRUE, 0);

	// Label the Types Box
	UT_XML_cloneNoAmpersands(unixstr, pSS->getValue(AP_STRING_ID_DLG_Field_Types));
	labelTypes = gtk_label_new (unixstr);
	FREEP(unixstr);
	gtk_box_pack_start (GTK_BOX (vboxTypes), labelTypes, FALSE, FALSE, 0);
	gtk_misc_set_alignment (GTK_MISC (labelTypes), 0, 0.5);

	// Put a scrolled window into the Types box
	scrolledwindowTypes = gtk_scrolled_window_new (NULL, NULL);
	gtk_widget_set_usize (scrolledwindowTypes, 200, 220);
	gtk_box_pack_start (GTK_BOX (vboxTypes), scrolledwindowTypes, TRUE, TRUE, 0);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindowTypes), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);

	m_listTypes = gtk_clist_new (1);
	gtk_clist_set_selection_mode (GTK_CLIST (m_listTypes), GTK_SELECTION_SINGLE);
	gtk_container_add (GTK_CONTAINER (scrolledwindowTypes), m_listTypes);

	// Add the Fields list vbox
	vboxFields = gtk_vbox_new (FALSE, 0);
	gtk_box_pack_start (GTK_BOX (hbox), vboxFields, TRUE, TRUE, 0);

	// Label the Fields Box
	UT_XML_cloneNoAmpersands(unixstr, pSS->getValue(AP_STRING_ID_DLG_Field_Fields));
	labelFields = gtk_label_new (unixstr);
	FREEP(unixstr);
	gtk_box_pack_start (GTK_BOX (vboxFields), labelFields, FALSE, FALSE, 0);
	gtk_misc_set_alignment (GTK_MISC (labelFields), 0, 0.5);

	// Put a scrolled window into the Fields box
	scrolledwindowFields = gtk_scrolled_window_new (NULL, NULL);
	gtk_widget_set_usize (scrolledwindowFields, 200, 220);
	gtk_box_pack_start (GTK_BOX (vboxFields), scrolledwindowFields, TRUE, TRUE, 0);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindowFields), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);

	m_listFields = gtk_clist_new(1);
	gtk_clist_set_selection_mode (GTK_CLIST (m_listFields), GTK_SELECTION_SINGLE);
	gtk_widget_set_usize (m_listFields, 198, 218);
	gtk_container_add (GTK_CONTAINER (scrolledwindowFields), m_listFields);

	// add the entry for optional parameter
	UT_XML_cloneNoAmpersands(unixstr, pSS->getValue(AP_STRING_ID_DLG_Field_Parameters));
	labelParam = gtk_label_new (unixstr);
	FREEP(unixstr);
	gtk_box_pack_start (GTK_BOX (vboxFields), labelParam, FALSE, FALSE, 0);
	gtk_misc_set_alignment (GTK_MISC (labelParam), 0, 0.5);
	
	m_entryParam = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (vboxFields), m_entryParam, FALSE, FALSE, 0);
	
	g_signal_connect_after(G_OBJECT(m_listTypes),
							 "select_row",
							 G_CALLBACK(s_types_clicked),
							 (gpointer) this);
	return hbox;
}

void AP_CocoaDialog_Field::_connectSignals (void)
{
	// the control buttons
	g_signal_connect(G_OBJECT(m_buttonOK),
					   "clicked",
					   G_CALLBACK(s_ok_clicked),
					   (gpointer) this);
	
	g_signal_connect(G_OBJECT(m_buttonCancel),
					   "clicked",
					   G_CALLBACK(s_cancel_clicked),
					   (gpointer) this);
	
	// the catch-alls
	g_signal_connect(G_OBJECT(m_windowMain),
			   "delete_event",
			   G_CALLBACK(s_delete_clicked),
			   (gpointer) this);

	g_signal_connect_after(G_OBJECT(m_windowMain),
							 "destroy",
							 NULL,
							 NULL);
}
