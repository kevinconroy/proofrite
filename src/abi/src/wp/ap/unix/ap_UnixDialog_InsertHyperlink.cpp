/* AbiWord
 * Copyright (C) 2000 AbiSource, Inc.
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

// This header defines some functions for Unix dialogs,
// like centering them, measuring them, etc.
#include "xap_UnixDialogHelper.h"

#include "xap_App.h"
#include "xap_UnixApp.h"
#include "xap_Frame.h"

#include "ap_Strings.h"
#include "ap_Dialog_Id.h"
#include "ap_Dialog_InsertHyperlink.h"
#include "ap_UnixDialog_InsertHyperlink.h"

/*****************************************************************/

XAP_Dialog * AP_UnixDialog_InsertHyperlink::static_constructor(XAP_DialogFactory * pFactory,
													 XAP_Dialog_Id id)
{
	AP_UnixDialog_InsertHyperlink * p = new AP_UnixDialog_InsertHyperlink(pFactory,id);
	return p;
}

AP_UnixDialog_InsertHyperlink::AP_UnixDialog_InsertHyperlink(XAP_DialogFactory * pDlgFactory,
										 XAP_Dialog_Id id)
	: AP_Dialog_InsertHyperlink(pDlgFactory,id)
{
	m_windowMain = 0;
	//m_comboEntry = 0;
	m_clist = 0;
	m_pBookmarks = 0;
	m_iRow = -1;
	m_entry = 0;
}

AP_UnixDialog_InsertHyperlink::~AP_UnixDialog_InsertHyperlink(void)
{
  DELETEPV(m_pBookmarks);
}

/*****************************************************************/

static void s_blist_clicked(GtkWidget *clist, gint row, gint column,
										  GdkEventButton *event, AP_UnixDialog_InsertHyperlink *me)
{
	me->setRow(row);
	gtk_entry_set_text(GTK_ENTRY(me->m_entry), me->m_pBookmarks[row]);
}

/***********************************************************************/
void AP_UnixDialog_InsertHyperlink::runModal(XAP_Frame * pFrame)
{
	UT_ASSERT(pFrame);
	// Build the window's widgets and arrange them
	GtkWidget * mainWindow = _constructWindow();
	UT_ASSERT(mainWindow);

	// select the first row of the list (this must come after the
 	// call to _connectSignals)
 	gtk_clist_unselect_row(GTK_CLIST(m_clist),0,0);

	switch(abiRunModalDialog(GTK_DIALOG(mainWindow), pFrame, this, BUTTON_CANCEL, false))
	  {
	  case BUTTON_OK:
	    event_OK (); break;
	  default:
	    event_Cancel(); break ;
	  }

	abiDestroyWidget(mainWindow);
}

void AP_UnixDialog_InsertHyperlink::event_OK(void)
{
	UT_ASSERT(m_windowMain);
	// get the bookmark name, if any (return cancel if no name given)
	const gchar * res = gtk_entry_get_text(GTK_ENTRY(m_entry));
	if(res && *res)	
	{
		setAnswer(AP_Dialog_InsertHyperlink::a_OK);
		setHyperlink((XML_Char*)res);
	}
	else
	{
		setAnswer(AP_Dialog_InsertHyperlink::a_CANCEL);
	}
}

void AP_UnixDialog_InsertHyperlink::event_Cancel(void)
{
	setAnswer(AP_Dialog_InsertHyperlink::a_CANCEL);
}

void AP_UnixDialog_InsertHyperlink::_constructWindowContents ( GtkWidget * vbox2 )
{
  const XAP_StringSet * pSS = m_pApp->getStringSet();

  GtkWidget *label1;

  label1 = gtk_label_new (pSS->getValueUTF8(AP_STRING_ID_DLG_InsertHyperlink_Msg).c_str());
  gtk_widget_show (label1);
  gtk_box_pack_start (GTK_BOX (vbox2), label1, TRUE, FALSE, 3);

  m_entry = gtk_entry_new();
  gtk_box_pack_start (GTK_BOX (vbox2), m_entry, FALSE, FALSE, 0);
  gtk_widget_show(m_entry);

  if ( getHyperlink() != NULL )
    gtk_entry_set_text ( GTK_ENTRY(m_entry), getHyperlink() ) ;

  // the bookmark list
  m_swindow  = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (m_swindow),GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_widget_show(m_swindow);
  gtk_box_pack_start (GTK_BOX (vbox2), m_swindow, FALSE, FALSE, 0);
	
  m_clist = gtk_clist_new (1);
  gtk_clist_set_selection_mode(GTK_CLIST(m_clist), GTK_SELECTION_BROWSE);
  gtk_clist_column_titles_hide(GTK_CLIST(m_clist));
  //gtk_box_pack_start (GTK_BOX (vbox2), m_blist, FALSE, FALSE, 0);

  DELETEPV(m_pBookmarks);
  m_pBookmarks = new const XML_Char *[getExistingBookmarksCount()];
	
  for (int i = 0; i < (int)getExistingBookmarksCount(); i++)
  	  m_pBookmarks[i] = getNthExistingBookmark(i);

  int (*my_cmp)(const void *, const void *) =
  	  (int (*)(const void*, const void*)) UT_XML_strcmp;
    	
  qsort(m_pBookmarks, getExistingBookmarksCount(),sizeof(XML_Char*),my_cmp);

  for (int i = 0; i < (int)getExistingBookmarksCount(); i++)
  	  gtk_clist_append (GTK_CLIST (m_clist), (gchar**) &m_pBookmarks[i]);

  gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(m_swindow),m_clist);

  const XML_Char * hyperlink = getHyperlink();
  if (hyperlink)
  {
	gtk_entry_set_text(GTK_ENTRY(m_entry), hyperlink);
// TODO uncomment line below when bug 920 gets fixed.
//	gtk_editable_select_region (GTK_EDITABLE(m_entry), 0, -1);
  }
}

GtkWidget*  AP_UnixDialog_InsertHyperlink::_constructWindow(void)
{
  GtkWidget *vbox2;
  GtkWidget *frame1;

  const XAP_StringSet * pSS = m_pApp->getStringSet();

  m_windowMain = abiDialogNew("insert table dialog", TRUE, pSS->getValueUTF8(AP_STRING_ID_DLG_InsertHyperlink_Title).c_str());

  frame1 = gtk_frame_new (NULL);
  gtk_widget_show (frame1);
  gtk_container_add (GTK_CONTAINER (GTK_DIALOG(m_windowMain)->vbox), frame1);
  gtk_container_set_border_width (GTK_CONTAINER (frame1), 4);

  vbox2 = gtk_vbox_new (FALSE, 6);
  gtk_widget_show (vbox2);
  gtk_container_add (GTK_CONTAINER (frame1), vbox2);
  gtk_container_set_border_width (GTK_CONTAINER (vbox2), 5);

  _constructWindowContents ( vbox2 );

  abiAddStockButton(GTK_DIALOG(m_windowMain), GTK_STOCK_CANCEL, BUTTON_CANCEL);
  abiAddStockButton(GTK_DIALOG(m_windowMain), GTK_STOCK_OK, BUTTON_OK);

  gtk_widget_grab_focus (m_entry);

  // connect all the signals
  _connectSignals ();
  gtk_widget_show_all ( m_windowMain ) ;

  return m_windowMain;
}

void AP_UnixDialog_InsertHyperlink::_connectSignals (void)
{
	g_signal_connect (G_OBJECT (m_clist), "select_row",
						G_CALLBACK (s_blist_clicked), this);
}
