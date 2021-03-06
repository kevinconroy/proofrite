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

#include "ut_assert.h"
#include "xap_App.h"
#include "xap_CocoaApp.h"
#include "xap_CocoaFrame.h"
#include "ap_Strings.h"
#include "xap_CocoaDialogHelper.h"

#include "ap_CocoaDialog_PageSetup.h"

#include <string.h>
#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

// include the 3 pixmaps that we use in this dialog
#include "orient-vertical.xpm"
#include "orient-horizontal.xpm"
#include "margin.xpm"

#include "ut_debugmsg.h"

/*********************************************************************************/

// static helper functions

static GtkWidget *
create_pixmap (GtkWidget *w, char **data)
{
  GtkWidget *pixmap;
  GdkColormap *colormap;
  GdkPixmap *gdkpixmap;
  GdkBitmap *mask;

  colormap = gtk_widget_get_colormap (w);
  gdkpixmap = gdk_pixmap_colormap_create_from_xpm_d (NULL, colormap, &mask,
						     NULL, (gchar **)data);

  pixmap = gtk_pixmap_new (gdkpixmap, mask);
  gdk_pixmap_unref (gdkpixmap);
  gdk_bitmap_unref (mask);
  return pixmap;
}

static char *
_ev_convert (char * bufResult,
	     const char * szString)
{
	UT_ASSERT (szString && bufResult);
	
	char *pl = bufResult;
	char *s = (char *)szString;

	int len = strlen (szString);
	int i;

	for (i = 0; i < len; i++)
	  {
	    if (*s == '&')
	      s++;
	    else
	      *pl++ = *s++;
	  }

	*pl = 0;
	return bufResult;
}

static int
fp_2_pos (UT_Dimension u)
{
   switch (u)
    {
    case DIM_CM   : return 1;
    case DIM_MM   : return 2;
    case DIM_IN   :
    default :
      return 0;
    } 
}

#define FMT_STRING "%0.2f"
static GtkWidget *
create_entry (float v)
{
  gchar * val;
  GtkWidget * e = gtk_entry_new ();
  gtk_entry_set_max_length (GTK_ENTRY (e), 4);
  val = g_strdup_printf (FMT_STRING, v);
  gtk_entry_set_text (GTK_ENTRY (e), val);
  gtk_entry_set_editable (GTK_ENTRY (e), FALSE);
  gtk_widget_set_usize (e, gdk_string_measure (e->style->font, val) + 15, 0);
  g_free (val);

  return e;
}

/*********************************************************************************/

// some static variables
static fp_PageSize::Predefined last_page_size = fp_PageSize::Custom;
static UT_Dimension last_page_unit = DIM_IN;
static UT_Dimension last_margin_unit = DIM_IN;

/*********************************************************************************/

// a *huge* convenience macro
static char _ev_buf[256];
#ifdef _
#undef _
#endif
#define _(a, x) _ev_convert (_ev_buf, pSS->getValue (a##_STRING_ID_##x))

// string tags to stuff stored in widget data
#define WIDGET_MENU_OPTION_PTR		"menuoptionptr"
#define WIDGET_MENU_VALUE_TAG		"value"

// convenience macro
#define CONNECT_MENU_ITEM_SIGNAL_ACTIVATE(w, m, d, f)				\
        do {												\
                g_object_set_data (G_OBJECT (w), WIDGET_MENU_OPTION_PTR, (gpointer)m);                \
                g_object_set_data (G_OBJECT (w), WIDGET_MENU_VALUE_TAG,  GINT_TO_POINTER(d));                \
	        g_signal_connect (G_OBJECT (w), "activate",	\
                G_CALLBACK (f),		\
                (gpointer)this);							\
        } while (0)

/*********************************************************************************/

// static event callbacks

static void s_ok_clicked (GtkWidget * w, AP_CocoaDialog_PageSetup *dlg)
{
  UT_ASSERT (dlg);
  dlg->event_OK ();
}

static void s_cancel_clicked (GtkWidget * w, AP_CocoaDialog_PageSetup *dlg)
{
  UT_ASSERT (dlg);
  dlg->event_Cancel ();
}

static void s_delete_clicked (GtkWidget * w,
			      gpointer data,
			      AP_CocoaDialog_PageSetup * dlg)
{
  UT_ASSERT (dlg);
  dlg->event_WindowDelete ();
}

static void s_menu_item_activate (GtkWidget * widget)
{
	GtkWidget *option_menu = (GtkWidget *)g_object_get_data (G_OBJECT (widget),
								   WIDGET_MENU_OPTION_PTR);
	UT_ASSERT(option_menu && GTK_IS_OPTION_MENU (option_menu));

	gpointer p = g_object_get_data (G_OBJECT (widget),
					  WIDGET_MENU_VALUE_TAG);

	g_object_set_data (G_OBJECT (option_menu), WIDGET_MENU_VALUE_TAG, p);
}

static void s_page_size_changed (GtkWidget * w, GtkWidget * child, 
				 AP_CocoaDialog_PageSetup *dlg)
{
  UT_ASSERT(w && dlg);

  fp_PageSize::Predefined pos = (fp_PageSize::Predefined)gtk_list_child_position (GTK_LIST(w), child);
  dlg->event_PageSizeChanged (pos);
}

static void s_page_units_changed (GtkWidget * w, AP_CocoaDialog_PageSetup *dlg)
{
  UT_ASSERT(w && dlg);
  s_menu_item_activate (w);
  dlg->event_PageUnitsChanged ();
}

static void s_margin_units_changed (GtkWidget * w, AP_CocoaDialog_PageSetup *dlg)
{
  UT_ASSERT(w && dlg);

  s_menu_item_activate (w);
  dlg->event_MarginUnitsChanged ();
}

/*********************************************************************************/

void AP_CocoaDialog_PageSetup::event_OK (void)
{
	fp_PageSize fp (last_page_size);

	if(fp.Width(DIM_IN) < 1.0 || fp.Height(DIM_IN) < 1.0)
	{
		setAnswer(a_CANCEL);
		gtk_main_quit();
		return;
	}
	
	setPageSize (fp);
	setMarginUnits (last_margin_unit);
	setPageUnits (last_page_unit);
	setPageOrientation (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (m_radioPagePortrait)) ? PORTRAIT : LANDSCAPE);
	setPageScale (gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (m_spinPageScale)));

	setMarginTop (gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (m_spinMarginTop)));
	setMarginBottom (gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (m_spinMarginBottom)));
	setMarginLeft (gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (m_spinMarginLeft)));
	setMarginRight (gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (m_spinMarginRight)));
	setMarginHeader (gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (m_spinMarginHeader)));
	setMarginFooter (gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (m_spinMarginFooter)));

	// The window will only close (on an OK click) if the margins
	// fit inside the paper size.
	if ( validatePageSettings() ) {
		setAnswer (a_OK);
		
		gtk_main_quit();
	}
	else {
		// "The margins selected are too large to fit on the page."
		m_pFrame->showMessageBox(AP_STRING_ID_DLG_PageSetup_ErrBigMargins, 
								 XAP_Dialog_MessageBox::b_O,
								 XAP_Dialog_MessageBox::a_OK);
	}
}

void AP_CocoaDialog_PageSetup::event_Cancel (void)
{
	setAnswer (a_CANCEL);
	gtk_main_quit();
}

void AP_CocoaDialog_PageSetup::event_WindowDelete (void)
{
        event_Cancel();
}

void AP_CocoaDialog_PageSetup::event_PageUnitsChanged (void)
{
  UT_Dimension pu = (UT_Dimension) GPOINTER_TO_INT (g_object_get_data (G_OBJECT (m_optionPageUnits), 
										   WIDGET_MENU_VALUE_TAG));

  float width, height;

  fp_PageSize ps(last_page_size);
  
  // get values  
  width  = (float)ps.Width (pu);
  height = (float)ps.Height (pu);

  last_page_unit = pu;
  
  // set values
  gchar * val;

  val = g_strdup_printf (FMT_STRING, width);
  gtk_entry_set_text (GTK_ENTRY (m_entryPageWidth), val);
  g_free (val);

  val = g_strdup_printf (FMT_STRING, height);
  gtk_entry_set_text (GTK_ENTRY (m_entryPageHeight), val);
  g_free (val);
}

void AP_CocoaDialog_PageSetup::event_PageSizeChanged (fp_PageSize::Predefined pd)
{
  fp_PageSize ps(pd);

  float w, h;

  w = ps.Width (last_page_unit);
  h = ps.Height (last_page_unit);

  // set values
  gchar * val;

  val = g_strdup_printf (FMT_STRING, w);
  gtk_entry_set_text (GTK_ENTRY (m_entryPageWidth), val);
  g_free (val);

  val = g_strdup_printf (FMT_STRING, h);
  gtk_entry_set_text (GTK_ENTRY (m_entryPageHeight), val);
  g_free (val);

  last_page_size = pd;

  if (fp_PageSize::Custom == pd)
  {
	  UT_DEBUGMSG(("FIXME: Make size widgets editable\n"));
  }
  else
  {
	  UT_DEBUGMSG(("FIXME: Make size widgets non-editable\n"));
  }

}

void AP_CocoaDialog_PageSetup::event_MarginUnitsChanged (void)
{
  UT_Dimension mu = (UT_Dimension) GPOINTER_TO_INT (g_object_get_data (G_OBJECT (m_optionMarginUnits),
										   WIDGET_MENU_VALUE_TAG));

  float top, bottom, left, right, header, footer;

  top    = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (m_spinMarginTop));
  bottom = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (m_spinMarginBottom));
  left   = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (m_spinMarginLeft));
  right  = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (m_spinMarginRight));
  header = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (m_spinMarginHeader));
  footer = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (m_spinMarginFooter));

  CONVERT_DIMENSIONS (top,    last_margin_unit, mu);
  CONVERT_DIMENSIONS (bottom, last_margin_unit, mu);
  CONVERT_DIMENSIONS (left,   last_margin_unit, mu);
  CONVERT_DIMENSIONS (right,  last_margin_unit, mu);
  CONVERT_DIMENSIONS (header, last_margin_unit, mu);
  CONVERT_DIMENSIONS (footer, last_margin_unit, mu);

  last_margin_unit = mu;

  gtk_spin_button_set_value (GTK_SPIN_BUTTON (m_spinMarginTop), top);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (m_spinMarginBottom), bottom);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (m_spinMarginLeft), left);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (m_spinMarginRight), right);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (m_spinMarginHeader), header);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (m_spinMarginFooter), footer);
}

/*********************************************************************************/

XAP_Dialog *
AP_CocoaDialog_PageSetup::static_constructor(XAP_DialogFactory * pFactory,
					    XAP_Dialog_Id id)
{
    AP_CocoaDialog_PageSetup * p = new AP_CocoaDialog_PageSetup(pFactory,id);
    return p;
}

AP_CocoaDialog_PageSetup::AP_CocoaDialog_PageSetup (XAP_DialogFactory *pDlgFactory, XAP_Dialog_Id id) 
  : AP_Dialog_PageSetup (pDlgFactory, id)
{
  // nada
}

AP_CocoaDialog_PageSetup::~AP_CocoaDialog_PageSetup (void)
{
  // nada
}

void AP_CocoaDialog_PageSetup::runModal (XAP_Frame *pFrame)
{
    // Build the window's widgets and arrange them
    GtkWidget * mainWindow = _constructWindow();
    UT_ASSERT(mainWindow);

    connectFocus(GTK_WIDGET(mainWindow), pFrame);

	m_pFrame = pFrame;

    // To center the dialog, we need the frame of its parent.
    XAP_CocoaFrame * pCocoaFrame = static_cast<XAP_CocoaFrame *>(pFrame);
    UT_ASSERT(pCocoaFrame);
    
    // Get the GtkWindow of the parent frame
    GtkWidget * parentWindow = pCocoaFrame->getTopLevelWindow();
    UT_ASSERT(parentWindow);
    
    // Center our new dialog in its parent and make it a transient
    // so it won't get lost underneath
    centerDialog(parentWindow, mainWindow);

    // Show the top level dialog,
    gtk_widget_show(mainWindow);

    // Make it modal, and stick it up top
    gtk_grab_add(mainWindow);

    // Run into the GTK event loop for this window.
    gtk_main();
    if(mainWindow && GTK_IS_WIDGET(mainWindow))
      gtk_widget_destroy(mainWindow);
}

void AP_CocoaDialog_PageSetup::_connectSignals (void)
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
	
	g_signal_connect(G_OBJECT(m_window),
			   "delete_event",
			   G_CALLBACK(s_delete_clicked),
			   (gpointer) this);

	g_signal_connect_after(G_OBJECT(m_window),
				 "destroy",
				 NULL,
				 NULL);

}

GtkWidget * AP_CocoaDialog_PageSetup::_constructWindow (void)
{
  const XAP_StringSet * pSS = m_pApp->getStringSet();

  m_window = gtk_dialog_new ();
  gtk_window_set_title (GTK_WINDOW (m_window), _(AP, DLG_PageSetup_Title));

  _constructWindowContents (GTK_DIALOG(m_window)->vbox);

  m_buttonOK = gtk_button_new_with_label (_(XAP, DLG_OK));
  gtk_widget_show (m_buttonOK);
  gtk_container_add (GTK_CONTAINER (GTK_DIALOG(m_window)->action_area), 
		     m_buttonOK);

  m_buttonCancel = gtk_button_new_with_label (_(XAP, DLG_Cancel));
  gtk_widget_show (m_buttonCancel);
  gtk_container_add (GTK_CONTAINER (GTK_DIALOG(m_window)->action_area), m_buttonCancel);

  _connectSignals ();
  return m_window;
}

// this code is glade generated
void AP_CocoaDialog_PageSetup::_constructWindowContents (GtkWidget *container)
{
  GtkWidget *notebook;
  GtkWidget *packerPage;
  GtkWidget *framePaper;
  GtkWidget *tablePaper;
  GtkWidget *entryPageWidth;
  GtkWidget *entryPageHeight;
  GtkWidget *labelWidth;
  GtkWidget *labelHeight;
  GtkWidget *labelPaperSize;
  GtkWidget *optionPageSize;
  GtkWidget *optionPageSize_menu;
  GtkWidget *glade_menuitem;
  GtkWidget *labelPageUnits;
  GtkWidget *optionPageUnits;
  GtkWidget *optionPageUnits_menu;
  GtkWidget *frameOrientation;
  GtkWidget *tableOrientation;
  GSList *tableOrientation_group = NULL;
  GtkWidget *radioPageLandscape;
  GtkWidget *radioPagePortrait;
  GtkWidget *pixmapPortrait;
  GtkWidget *pixmap2;
  GtkWidget *frameScale;
  GtkWidget *table1;
  GtkWidget *label5;
  GtkWidget *label6;
  GObject *spinPageScale_adj;
  GtkWidget *spinPageScale;
  GtkWidget *labelPage;
  GtkWidget *tableMargin;
  GObject *spinMarginBottom_adj;
  GtkWidget *spinMarginBottom;
  GObject *spinMarginFooter_adj;
  GtkWidget *spinMarginFooter;
  GtkWidget *labelMarginUnits;
  GtkWidget *labelTop;
  GtkWidget *labelHeader;
  GtkWidget *labelFooter;
  GtkWidget *labelBottom;
  GtkWidget *customPreview;
  GObject *spinMarginTop_adj;
  GtkWidget *spinMarginTop;
  GObject *spinMarginHeader_adj;
  GtkWidget *spinMarginHeader;
  GtkWidget *vbox3;
  GtkWidget *labelRight;
  GObject *spinMarginRight_adj;
  GtkWidget *spinMarginRight;
  GtkWidget *vbox2;
  GtkWidget *labelLeft;
  GObject *spinMarginLeft_adj;
  GtkWidget *spinMarginLeft;
  GtkWidget *optionMarginUnits;
  GtkWidget *optionMarginUnits_menu;
  GtkWidget *labelMargin;

  const XAP_StringSet * pSS = m_pApp->getStringSet();

  notebook = gtk_notebook_new ();
  gtk_widget_show (notebook);
  gtk_box_pack_start (GTK_BOX (container), notebook, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (notebook), 7);

  packerPage = gtk_packer_new ();
  gtk_packer_set_default_border_width (GTK_PACKER (packerPage), 2);
  gtk_packer_set_default_pad (GTK_PACKER (packerPage), 8, 8);
  gtk_packer_set_default_ipad (GTK_PACKER (packerPage), 2, 2);
  gtk_widget_show (packerPage);
  gtk_container_add (GTK_CONTAINER (notebook), packerPage);
  gtk_container_set_border_width (GTK_CONTAINER (packerPage), 2);

  framePaper = gtk_frame_new (_(AP, DLG_PageSetup_Paper));
  gtk_widget_show (framePaper);
  gtk_packer_add_defaults (GTK_PACKER (packerPage), framePaper, GTK_SIDE_TOP,
                           GTK_ANCHOR_CENTER, (GtkPackerOptions) (GTK_FILL_X));

  tablePaper = gtk_table_new (3, 4, TRUE);
  gtk_widget_show (tablePaper);
  gtk_container_add (GTK_CONTAINER (framePaper), tablePaper);
  gtk_table_set_row_spacings (GTK_TABLE (tablePaper), 4);
  gtk_table_set_col_spacings (GTK_TABLE (tablePaper), 4);

  entryPageWidth = create_entry (getPageSize().Width (getPageUnits ()));
  gtk_widget_show (entryPageWidth);
  gtk_table_attach (GTK_TABLE (tablePaper), entryPageWidth, 3, 4, 0, 1,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
 
  entryPageHeight = create_entry (getPageSize().Height (getPageUnits ()));
  gtk_widget_show (entryPageHeight);
  gtk_table_attach (GTK_TABLE (tablePaper), entryPageHeight, 3, 4, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);

  labelWidth = gtk_label_new (_(AP, DLG_PageSetup_Width));
  gtk_widget_show (labelWidth);
  gtk_table_attach (GTK_TABLE (tablePaper), labelWidth, 2, 3, 0, 1,
                    (GtkAttachOptions) (0),
                    (GtkAttachOptions) (0), 0, 0);

  labelHeight = gtk_label_new (_(AP, DLG_PageSetup_Height));
  gtk_widget_show (labelHeight);
  gtk_table_attach (GTK_TABLE (tablePaper), labelHeight, 2, 3, 1, 2,
                    (GtkAttachOptions) (0),
                    (GtkAttachOptions) (0), 0, 0);

  labelPaperSize = gtk_label_new (_(AP, DLG_PageSetup_Paper_Size));
  gtk_widget_show (labelPaperSize);
  gtk_table_attach (GTK_TABLE (tablePaper), labelPaperSize, 0, 1, 0, 3,
                    (GtkAttachOptions) (0),
                    (GtkAttachOptions) (0), 0, 0);

  optionPageSize = gtk_combo_new ();
  gtk_widget_show (optionPageSize);
  gtk_table_attach (GTK_TABLE (tablePaper), optionPageSize, 1, 2, 0, 3,
                    (GtkAttachOptions) (0),
                    (GtkAttachOptions) (0), 0, 0);

  optionPageSize_menu = gtk_menu_new ();

  // create the drop-down menu with all of our supported page sizes
  GList *popdown_items = NULL;
  for (int i = (int)fp_PageSize::_first_predefined_pagesize_; i < (int)fp_PageSize::_last_predefined_pagesize_dont_use_; i++)
    {
      popdown_items = g_list_append (popdown_items, (void*)fp_PageSize::PredefinedToName ((fp_PageSize::Predefined)i) );
    }
  gtk_combo_set_popdown_strings (GTK_COMBO (optionPageSize), popdown_items);

  last_page_size = fp_PageSize::NameToPredefined (getPageSize ().getPredefinedName ());

  GtkList * optionPageSizeList = GTK_LIST(GTK_COMBO(optionPageSize)->list);
  gtk_list_select_item (optionPageSizeList, (gint)last_page_size);

  g_signal_connect(G_OBJECT(optionPageSizeList), "select-child",
		     G_CALLBACK(s_page_size_changed), (gpointer)this);

  labelPageUnits = gtk_label_new (_(AP, DLG_PageSetup_Units));
  gtk_widget_show (labelPageUnits);
  gtk_table_attach (GTK_TABLE (tablePaper), labelPageUnits, 2, 3, 2, 3,
                    (GtkAttachOptions) (0),
                    (GtkAttachOptions) (0), 0, 0);

  optionPageUnits = gtk_option_menu_new ();
  gtk_widget_show (optionPageUnits);
  gtk_table_attach (GTK_TABLE (tablePaper), optionPageUnits, 3, 4, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);

  optionPageUnits_menu = gtk_menu_new ();

  glade_menuitem = gtk_menu_item_new_with_label (_(XAP, DLG_Unit_inch));
  CONNECT_MENU_ITEM_SIGNAL_ACTIVATE (glade_menuitem, optionPageUnits, DIM_IN, s_page_units_changed);
  gtk_widget_show (glade_menuitem);
  gtk_menu_append (GTK_MENU (optionPageUnits_menu), glade_menuitem);

  glade_menuitem = gtk_menu_item_new_with_label (_(XAP, DLG_Unit_cm));
  CONNECT_MENU_ITEM_SIGNAL_ACTIVATE (glade_menuitem, optionPageUnits, DIM_CM, s_page_units_changed);
  gtk_widget_show (glade_menuitem);
  gtk_menu_append (GTK_MENU (optionPageUnits_menu), glade_menuitem);

  glade_menuitem = gtk_menu_item_new_with_label (_(XAP, DLG_Unit_mm));
  CONNECT_MENU_ITEM_SIGNAL_ACTIVATE (glade_menuitem, optionPageUnits, DIM_MM, s_page_units_changed);
  gtk_widget_show (glade_menuitem);
  gtk_menu_append (GTK_MENU (optionPageUnits_menu), glade_menuitem);

  gtk_option_menu_set_menu (GTK_OPTION_MENU (optionPageUnits), optionPageUnits_menu);
  last_page_unit = getPageUnits ();
  gtk_option_menu_set_history (GTK_OPTION_MENU (optionPageUnits), fp_2_pos (getPageUnits()));

  frameOrientation = gtk_frame_new (_(AP, DLG_PageSetup_Orient));
  gtk_widget_show (frameOrientation);
  gtk_packer_add_defaults (GTK_PACKER (packerPage), frameOrientation, GTK_SIDE_TOP,
                           GTK_ANCHOR_CENTER, (GtkPackerOptions) (GTK_FILL_X));

  tableOrientation = gtk_table_new (2, 2, TRUE);
  gtk_widget_show (tableOrientation);
  gtk_container_add (GTK_CONTAINER (frameOrientation), tableOrientation);
  gtk_table_set_row_spacings (GTK_TABLE (tableOrientation), 1);

  radioPageLandscape = gtk_radio_button_new_with_label (tableOrientation_group, _(AP, DLG_PageSetup_Landscape));
  tableOrientation_group = gtk_radio_button_group (GTK_RADIO_BUTTON (radioPageLandscape));
  gtk_widget_show (radioPageLandscape);
  gtk_table_attach (GTK_TABLE (tableOrientation), radioPageLandscape, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND),
                    (GtkAttachOptions) (0), 0, 0);

  radioPagePortrait = gtk_radio_button_new_with_label (tableOrientation_group, _(AP, DLG_PageSetup_Portrait));
  tableOrientation_group = gtk_radio_button_group (GTK_RADIO_BUTTON (radioPagePortrait));
  gtk_widget_show (radioPagePortrait);
  gtk_table_attach (GTK_TABLE (tableOrientation), radioPagePortrait, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND),
                    (GtkAttachOptions) (0), 0, 0);

  pixmapPortrait = create_pixmap (container, orient_vertical_xpm);
  gtk_widget_show (pixmapPortrait);
  gtk_table_attach (GTK_TABLE (tableOrientation), pixmapPortrait, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);

  pixmap2 = create_pixmap (container, orient_horizontal_xpm);
  gtk_widget_show (pixmap2);
  gtk_table_attach (GTK_TABLE (tableOrientation), pixmap2, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (GTK_FILL), 0, 0);

  if (getPageOrientation () == PORTRAIT)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radioPagePortrait), TRUE);
  else
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radioPageLandscape), TRUE);;

  frameScale = gtk_frame_new (_(AP, DLG_PageSetup_Scale));
  gtk_widget_show (frameScale);
  gtk_packer_add_defaults (GTK_PACKER (packerPage), frameScale, GTK_SIDE_TOP,
                           GTK_ANCHOR_CENTER, (GtkPackerOptions) (GTK_FILL_X));

  table1 = gtk_table_new (1, 4, TRUE);
  gtk_widget_show (table1);
  gtk_container_add (GTK_CONTAINER (frameScale), table1);

  label5 = gtk_label_new (_(AP, DLG_PageSetup_Adjust));
  gtk_widget_show (label5);
  gtk_table_attach (GTK_TABLE (table1), label5, 0, 1, 0, 1,
                    (GtkAttachOptions) (0),
                    (GtkAttachOptions) (0), 0, 0);

  label6 = gtk_label_new (_(AP, DLG_PageSetup_Percent));
  gtk_widget_show (label6);
  gtk_table_attach (GTK_TABLE (table1), label6, 2, 4, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_label_set_justify (GTK_LABEL (label6), GTK_JUSTIFY_FILL);
  gtk_misc_set_alignment (GTK_MISC (label6), 7.45058e-09, 0.5);
  gtk_misc_set_padding (GTK_MISC (label6), 8, 0);

  spinPageScale_adj = gtk_adjustment_new (100, 1, 1000, 1, 25, 25);
  spinPageScale = gtk_spin_button_new (GTK_ADJUSTMENT (spinPageScale_adj), 1, 0);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (spinPageScale), (float)getPageScale ());
  gtk_widget_show (spinPageScale);
  gtk_table_attach (GTK_TABLE (table1), spinPageScale, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);

  labelPage = gtk_label_new (_(AP, DLG_PageSetup_Page));
  gtk_widget_show (labelPage);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (notebook), gtk_notebook_get_nth_page (GTK_NOTEBOOK (notebook), 0), labelPage);

  tableMargin = gtk_table_new (7, 3, FALSE);
  gtk_widget_show (tableMargin);
  gtk_container_add (GTK_CONTAINER (notebook), tableMargin);
  gtk_container_set_border_width (GTK_CONTAINER (tableMargin), 8);

  spinMarginBottom_adj = gtk_adjustment_new (99, 0, 100, 0.1, 1, 1);
  spinMarginBottom = gtk_spin_button_new (GTK_ADJUSTMENT (spinMarginBottom_adj), 1, 1);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (spinMarginBottom), getMarginBottom ());
  gtk_widget_show (spinMarginBottom);
  gtk_table_attach (GTK_TABLE (tableMargin), spinMarginBottom, 1, 2, 6, 7,
                    (GtkAttachOptions) (0),
                    (GtkAttachOptions) (0), 0, 0);

  spinMarginFooter_adj = gtk_adjustment_new (99, 0, 100, 0.1, 1, 1);
  spinMarginFooter = gtk_spin_button_new (GTK_ADJUSTMENT (spinMarginFooter_adj), 1, 1);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (spinMarginFooter), getMarginFooter ());
  gtk_widget_show (spinMarginFooter);
  gtk_table_attach (GTK_TABLE (tableMargin), spinMarginFooter, 2, 3, 6, 7,
                    (GtkAttachOptions) (0),
                    (GtkAttachOptions) (0), 0, 0);

  labelMarginUnits = gtk_label_new (_(AP, DLG_PageSetup_Units));
  gtk_widget_show (labelMarginUnits);
  gtk_table_attach (GTK_TABLE (tableMargin), labelMarginUnits, 0, 1, 0, 1,
                    (GtkAttachOptions) (0),
                    (GtkAttachOptions) (0), 0, 0);

  labelTop = gtk_label_new (_(AP, DLG_PageSetup_Top));
  gtk_widget_show (labelTop);
  gtk_table_attach (GTK_TABLE (tableMargin), labelTop, 1, 2, 0, 1,
                    (GtkAttachOptions) (0),
                    (GtkAttachOptions) (0), 0, 0);

  labelHeader = gtk_label_new (_(AP, DLG_PageSetup_Header));
  gtk_widget_show (labelHeader);
  gtk_table_attach (GTK_TABLE (tableMargin), labelHeader, 2, 3, 0, 1,
                    (GtkAttachOptions) (0),
                    (GtkAttachOptions) (0), 0, 0);

  labelFooter = gtk_label_new (_(AP, DLG_PageSetup_Footer));
  gtk_widget_show (labelFooter);
  gtk_table_attach (GTK_TABLE (tableMargin), labelFooter, 2, 3, 5, 6,
                    (GtkAttachOptions) (0),
                    (GtkAttachOptions) (0), 0, 0);

  labelBottom = gtk_label_new (_(AP, DLG_PageSetup_Bottom));
  gtk_widget_show (labelBottom);
  gtk_table_attach (GTK_TABLE (tableMargin), labelBottom, 1, 2, 5, 6,
                    (GtkAttachOptions) (0),
                    (GtkAttachOptions) (0), 0, 0);

  customPreview = create_pixmap (container, margin_xpm);
  gtk_widget_show (customPreview);
  gtk_table_attach (GTK_TABLE (tableMargin), customPreview, 1, 2, 2, 5,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);

  spinMarginTop_adj = gtk_adjustment_new (99, 0, 100, 0.1, 1, 1);
  spinMarginTop = gtk_spin_button_new (GTK_ADJUSTMENT (spinMarginTop_adj), 1, 1);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (spinMarginTop), getMarginTop ());
  gtk_widget_show (spinMarginTop);
  gtk_table_attach (GTK_TABLE (tableMargin), spinMarginTop, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND),
                    (GtkAttachOptions) (0), 0, 0);

  spinMarginHeader_adj = gtk_adjustment_new (99, 0, 100, 0.1, 1, 1);
  spinMarginHeader = gtk_spin_button_new (GTK_ADJUSTMENT (spinMarginHeader_adj), 1, 1);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (spinMarginHeader), getMarginHeader ());
  gtk_widget_show (spinMarginHeader);
  gtk_table_attach (GTK_TABLE (tableMargin), spinMarginHeader, 2, 3, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND),
                    (GtkAttachOptions) (0), 0, 0);

  vbox3 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox3);
  gtk_table_attach (GTK_TABLE (tableMargin), vbox3, 2, 3, 3, 4,
                    (GtkAttachOptions) (0),
                    (GtkAttachOptions) (0), 0, 0);

  labelRight = gtk_label_new (_(AP, DLG_PageSetup_Right));
  gtk_widget_show (labelRight);
  gtk_box_pack_start (GTK_BOX (vbox3), labelRight, FALSE, FALSE, 0);
  gtk_misc_set_alignment (GTK_MISC (labelRight), 0.5, 1);

  spinMarginRight_adj = gtk_adjustment_new (99, 0, 100, 0.1, 1, 1);
  spinMarginRight = gtk_spin_button_new (GTK_ADJUSTMENT (spinMarginRight_adj), 1, 1);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (spinMarginRight), getMarginRight ());
  gtk_widget_show (spinMarginRight);
  gtk_box_pack_start (GTK_BOX (vbox3), spinMarginRight, FALSE, FALSE, 0);

  vbox2 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox2);
  gtk_table_attach (GTK_TABLE (tableMargin), vbox2, 0, 1, 3, 4,
                    (GtkAttachOptions) (0),
                    (GtkAttachOptions) (0), 0, 0);

  labelLeft = gtk_label_new (_(AP, DLG_PageSetup_Left));
  gtk_widget_show (labelLeft);
  gtk_box_pack_start (GTK_BOX (vbox2), labelLeft, FALSE, FALSE, 0);
  gtk_misc_set_alignment (GTK_MISC (labelLeft), 0.5, 1);

  spinMarginLeft_adj = gtk_adjustment_new (99, 0, 100, 0.1, 1, 1);
  spinMarginLeft = gtk_spin_button_new (GTK_ADJUSTMENT (spinMarginLeft_adj), 1, 1);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (spinMarginLeft), getMarginLeft ());
  gtk_widget_show (spinMarginLeft);
  gtk_box_pack_start (GTK_BOX (vbox2), spinMarginLeft, FALSE, FALSE, 0);

  optionMarginUnits = gtk_option_menu_new ();
  gtk_widget_show (optionMarginUnits);
  gtk_table_attach (GTK_TABLE (tableMargin), optionMarginUnits, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND),
                    (GtkAttachOptions) (0), 0, 0);

  optionMarginUnits_menu = gtk_menu_new ();

  glade_menuitem = gtk_menu_item_new_with_label (_(XAP, DLG_Unit_inch));
  CONNECT_MENU_ITEM_SIGNAL_ACTIVATE (glade_menuitem, optionMarginUnits, DIM_IN, s_margin_units_changed);
  gtk_widget_show (glade_menuitem);
  gtk_menu_append (GTK_MENU (optionMarginUnits_menu), glade_menuitem);

  glade_menuitem = gtk_menu_item_new_with_label (_(XAP, DLG_Unit_cm));
  CONNECT_MENU_ITEM_SIGNAL_ACTIVATE (glade_menuitem, optionMarginUnits, DIM_CM, s_margin_units_changed);
  gtk_widget_show (glade_menuitem);
  gtk_menu_append (GTK_MENU (optionMarginUnits_menu), glade_menuitem);

  glade_menuitem = gtk_menu_item_new_with_label (_(XAP, DLG_Unit_mm));
  CONNECT_MENU_ITEM_SIGNAL_ACTIVATE (glade_menuitem, optionMarginUnits, DIM_MM, s_margin_units_changed);
  gtk_widget_show (glade_menuitem);
  gtk_menu_append (GTK_MENU (optionMarginUnits_menu), glade_menuitem);

  gtk_option_menu_set_menu (GTK_OPTION_MENU (optionMarginUnits), optionMarginUnits_menu);
  last_margin_unit = getMarginUnits ();
  gtk_option_menu_set_history (GTK_OPTION_MENU (optionMarginUnits), fp_2_pos(last_margin_unit));

  labelMargin = gtk_label_new (_(AP, DLG_PageSetup_Margin));
  gtk_widget_show (labelMargin);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (notebook), gtk_notebook_get_nth_page (GTK_NOTEBOOK (notebook), 1), labelMargin);

  // now set our instance data equal to these widgets
  // so that we can query them later
  m_optionPageSize 		= optionPageSize;
  m_entryPageWidth 		= entryPageWidth;
  m_entryPageHeight		= entryPageHeight;
  m_optionPageUnits		= optionPageUnits;
  m_radioPagePortrait		= radioPagePortrait;
  m_radioPageLandscape	        = radioPageLandscape;
  m_spinPageScale		= spinPageScale;

  m_optionMarginUnits		= optionMarginUnits;
  m_spinMarginTop	      	= spinMarginTop;
  m_spinMarginBottom		= spinMarginBottom;
  m_spinMarginLeft		= spinMarginLeft;
  m_spinMarginRight		= spinMarginRight;
  m_spinMarginHeader		= spinMarginHeader;
  m_spinMarginFooter		= spinMarginFooter;
}
