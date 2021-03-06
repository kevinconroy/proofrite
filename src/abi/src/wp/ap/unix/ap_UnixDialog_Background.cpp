/* AbiWord
 * Copyright (C) 2000-2002 AbiSource, Inc.
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

// This header defines some functions for Unix dialogs,
// like centering them, measuring them, etc.
#include "xap_UnixDialogHelper.h"

#include "xap_App.h"
#include "xap_UnixApp.h"
#include "xap_Frame.h"

#include "ap_Strings.h"
#include "ap_Dialog_Id.h"
#include "ap_UnixDialog_Background.h"
#include "ut_debugmsg.h"

enum
{
	RED,
	GREEN,
	BLUE,
	OPACITY
};

static void s_color_cleared(GtkWidget * btn, AP_UnixDialog_Background * dlg)
{
	UT_ASSERT(dlg);
	dlg->colorCleared();
}

#define CTI(c, v) (int)(c[v] * 255.0)

static void s_color_changed(GtkWidget * csel,
			    AP_UnixDialog_Background * dlg)
{
	UT_ASSERT(csel && dlg);
  
	GtkColorSelection * w = GTK_COLOR_SELECTION(csel);
	gdouble cur [4];

	gtk_color_selection_get_color (w, cur);

	static char buf_color[12];

	sprintf(buf_color,"%02x%02x%02x",CTI(cur, RED), CTI(cur, GREEN), CTI(cur, BLUE));
	dlg->setColor ((const XML_Char *) buf_color);
}

#undef CTI

/*****************************************************************/

XAP_Dialog * AP_UnixDialog_Background::static_constructor(XAP_DialogFactory * pFactory,
													 XAP_Dialog_Id id)
{
	AP_UnixDialog_Background * p = new AP_UnixDialog_Background(pFactory,id);
	return p;
}

AP_UnixDialog_Background::AP_UnixDialog_Background(XAP_DialogFactory * pDlgFactory,
										 XAP_Dialog_Id id)
	: AP_Dialog_Background(pDlgFactory,id)
{
}

AP_UnixDialog_Background::~AP_UnixDialog_Background(void)
{
}

void AP_UnixDialog_Background::runModal(XAP_Frame * pFrame)
{
	UT_return_if_fail(pFrame);

	// Build the window's widgets and arrange them
	GtkWidget * mainWindow = _constructWindow();
	UT_return_if_fail(mainWindow);
	m_dlg = mainWindow;

	switch ( abiRunModalDialog ( GTK_DIALOG(m_dlg), pFrame, this,
								 BUTTON_CANCEL, true ) )
	{
		case BUTTON_OK:
			eventOk () ; break;
		default:
			eventCancel(); break ;
	}
}

GtkWidget * AP_UnixDialog_Background::_constructWindow (void)
{
	GtkWidget * dlg;

	const XAP_StringSet * pSS = m_pApp->getStringSet();
	
	if(isForeground())
	{
		dlg = abiDialogNew ( "background dialog", TRUE, pSS->getValueUTF8(AP_STRING_ID_DLG_Background_TitleFore).c_str()) ;
	}
	else if(isHighlight())
	{
		dlg = abiDialogNew ( "background dialog", TRUE, pSS->getValueUTF8(AP_STRING_ID_DLG_Background_TitleHighlight).c_str()) ;
	}
	else
	{
		dlg = abiDialogNew ( "background dialog", TRUE, pSS->getValueUTF8(AP_STRING_ID_DLG_Background_Title).c_str()) ;
	}

	abiAddStockButton ( GTK_DIALOG(dlg), GTK_STOCK_CANCEL, BUTTON_CANCEL ) ;
	abiAddStockButton ( GTK_DIALOG(dlg), GTK_STOCK_OK, BUTTON_OK ) ;
  
	_constructWindowContents (GTK_DIALOG(dlg)->vbox);
	
	return dlg;
}

void AP_UnixDialog_Background::_constructWindowContents (GtkWidget * parent)
{
	GtkWidget *colorsel;

	GtkWidget * vbox = gtk_vbox_new(false,0);
	gtk_widget_show(vbox);
	gtk_container_add (GTK_CONTAINER(parent), vbox);

	colorsel = gtk_color_selection_new();
	gtk_color_selection_set_has_opacity_control(GTK_COLOR_SELECTION(colorsel), false);
	gtk_widget_show (colorsel);
	gtk_container_add (GTK_CONTAINER(vbox), colorsel);

	const XML_Char *  pszC = getColor();
	UT_RGBColor c(255,255,255);
	if(strcmp(pszC,"transparent") != 0)
	{
		UT_parseColor(pszC,c);
	}
	gdouble currentColor[4] = { 0.0, 0.0, 0.0, 0 };
	currentColor[RED] = ((gdouble) c.m_red / (gdouble) 255.0);
	currentColor[GREEN] = ((gdouble) c.m_grn / (gdouble) 255.0);
	currentColor[BLUE] = ((gdouble) c.m_blu / (gdouble) 255.0);

	gtk_color_selection_set_color (GTK_COLOR_SELECTION(colorsel),
								   currentColor);
	m_wColorsel = colorsel;
//
// Button to clear background color
//
	GtkWidget * clearColor = NULL;
	if(!isForeground())
	{
		const XAP_StringSet * pSS = m_pApp->getStringSet();
		if(isHighlight())
		{
			clearColor = gtk_button_new_with_label (pSS->getValueUTF8 (AP_STRING_ID_DLG_Background_ClearHighlight).c_str());
		}
		else
		{
			clearColor = gtk_button_new_with_label (pSS->getValueUTF8 (AP_STRING_ID_DLG_Background_ClearClr).c_str());
		}
		gtk_widget_show(clearColor);
	
		gtk_container_add(GTK_CONTAINER(vbox),clearColor);
		g_signal_connect(G_OBJECT(clearColor), "clicked",
						G_CALLBACK(s_color_cleared),
						(gpointer) this);
	}
	g_signal_connect (G_OBJECT(colorsel), "color-changed",
							G_CALLBACK(s_color_changed),
						(gpointer) this);
}

void AP_UnixDialog_Background::eventOk (void)
{
	setAnswer (a_OK);
}

void AP_UnixDialog_Background::eventCancel (void)
{
	setAnswer(a_CANCEL);
}

void AP_UnixDialog_Background::colorCleared(void)
{
	setColor(NULL);
	gdouble currentColor[4] = { 1., 1., 1., 0 };
	gtk_color_selection_set_color (GTK_COLOR_SELECTION(m_wColorsel),
								   currentColor);
}	
	


