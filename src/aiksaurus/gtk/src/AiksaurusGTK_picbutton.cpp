/*
 * AiksaurusGTK - A GTK interface to the AikSaurus library
 * Copyright (C) 2001 by Jared Davis
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

#include "AiksaurusGTK_picbutton.h"
#include <iostream>
using namespace std;


//
// AiksaurusGTK_menudata class
// ---------------------------
//   This is a hack job that allows us to pass more info through
//   the gtk callback functions.  
//
//   See the comments in the menu functions below for an explanation of why 
//   this is here and what it is used for.
//
class AiksaurusGTK_menudata
{
    public:

        AiksaurusGTK_picbutton* d_picbutton_ptr;
        GList* d_glist_ptr;

        AiksaurusGTK_menudata() : d_picbutton_ptr(NULL), d_glist_ptr(NULL)
        {

        }
};




//////////////////////////////////////////////////////////////////////////
//                                                                      //
//   Creation, Menu Addition, Hover Icon Setting                        //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

AiksaurusGTK_picbutton::AiksaurusGTK_picbutton(GtkWidget *window, const char** normal)
{
	d_window_ptr = window;
	d_style_ptr = gtk_widget_get_style(window);


    // Initialize with no menu stuff at all.
	d_hasmenu = false;
	d_menushowing = false;
    d_menu_data_ptr = NULL;
    d_menu_options_ptr = NULL;
    d_menu_ptr = NULL;
    d_numVisible = 0;

	d_enabled = true;
	d_hashover = false;
	d_mouseover = false;

	d_button_ptr = gtk_button_new();
	gtk_widget_show(d_button_ptr);
	GTK_WIDGET_UNSET_FLAGS(
		d_button_ptr, 
		GTK_CAN_FOCUS
	);
	
	d_normalpixmap_ptr = gdk_pixmap_create_from_xpm_d(
		d_window_ptr->window,
		&d_normalmask_ptr,
		&d_style_ptr->bg[GTK_STATE_NORMAL],
		(gchar**)normal
	);

	d_pixmap_ptr = gtk_pixmap_new(
		d_normalpixmap_ptr,
		d_normalmask_ptr
	);

	gtk_widget_show(d_pixmap_ptr);
	
	gtk_container_add(
		GTK_CONTAINER(d_button_ptr),
		d_pixmap_ptr
	);
}


AiksaurusGTK_picbutton::~AiksaurusGTK_picbutton()
{
    // TO DO: what if this is null?
    gtk_widget_destroy(d_menu_ptr);
    
    if (d_menu_data_ptr != NULL)
        delete[] d_menu_data_ptr;
}


void
AiksaurusGTK_picbutton::setHoverPicture(const char** hover)
{
	d_hashover = true;
	
	d_hoverpixmap_ptr = gdk_pixmap_create_from_xpm_d(
		d_window_ptr->window,
		&d_hovermask_ptr,
		&d_style_ptr->bg[GTK_STATE_NORMAL],
		(gchar**)hover
	);

	g_signal_connect(
		GTK_OBJECT(d_button_ptr),
		"enter",
		GTK_SIGNAL_FUNC(cbHover),
		this
	);

	g_signal_connect(
		GTK_OBJECT(d_button_ptr),
		"leave",
		GTK_SIGNAL_FUNC(cbUnhover),
		this
	);

	handleRelief();
}


GtkWidget* 
AiksaurusGTK_picbutton::getButton()
{
	return d_button_ptr;
}


GtkWidget*
AiksaurusGTK_picbutton::getMenuButton()
{
	return d_menu_button_ptr;
}



//////////////////////////////////////////////////////////////////////////
//                                                                      //
//   Enabling and Disabling Support                                     //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

void
AiksaurusGTK_picbutton::disable()
{
    bool mousestate = d_mouseover;
    d_mouseover = false;
	handleRelief();
    d_mouseover = mousestate;

    d_enabled = false;

	gtk_widget_set_sensitive(
		d_button_ptr,
		false
	);

	if (d_hasmenu)
	{
		gtk_widget_set_sensitive(
			d_menu_button_ptr,
			false
		);
	}
}


void
AiksaurusGTK_picbutton::enable()
{
	d_enabled = true;

	gtk_widget_set_sensitive(
		d_button_ptr,
		true
	);

	if (d_hasmenu)
	{
		gtk_widget_set_sensitive(
			d_menu_button_ptr,
			true
		);
	}

    handleRelief();
}





//////////////////////////////////////////////////////////////////////////
//                                                                      //
//   Hover Effect                                                       //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

void
AiksaurusGTK_picbutton::handleRelief()
{
	const GtkReliefStyle off = GTK_RELIEF_NONE;
	const GtkReliefStyle on = GTK_RELIEF_HALF;

	GtkReliefStyle d_border_state = off;

	if (!d_hashover)
	{
		d_border_state = on;
	}

	else
	{
		if (d_menushowing || d_mouseover)
		{
			d_border_state = on;

			gtk_pixmap_set(
				GTK_PIXMAP(d_pixmap_ptr),
				d_hoverpixmap_ptr,
				d_hovermask_ptr
			);
		}

		else
		{
			gtk_pixmap_set(
				GTK_PIXMAP(d_pixmap_ptr),
				d_normalpixmap_ptr,
				d_normalmask_ptr
			);
		}
	}

	gtk_button_set_relief(
		GTK_BUTTON(d_button_ptr),
		d_border_state
	);

	if (d_hasmenu)
	{
		gtk_button_set_relief(
			GTK_BUTTON(d_menu_button_ptr),
			d_border_state
		);
	}
}


void
AiksaurusGTK_picbutton::hover()
{
	d_mouseover = true;
	handleRelief();
}


void
AiksaurusGTK_picbutton::unhover()
{
	d_mouseover = false;
	handleRelief();
}



//////////////////////////////////////////////////////////////////////////
//                                                                      //
//   Drop-Down Menu                                                     //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//
// GTK provides little or no support for what we're about to try to do.
//
// Our goal:
//   Provide a convenient interface to manage a dynamic dropdown menu.



//
// popMenu: invoked when the menu-button is pressed.
//   displays the menu to the user.
void
AiksaurusGTK_picbutton::popMenu()
{
	d_menushowing = true;
	
    gtk_menu_popup(
		GTK_MENU(d_menu_ptr),
		NULL,
		NULL,
		cbPopupFunction,
		this,
		0,
		0
	);
}


//
// popupFunction: invoked by gtk_menu_popup in popMenu().
//   Calculates the coordinates for the popup menu to appear at. 
//
void
AiksaurusGTK_picbutton::popupFunction(int* x, int* y)
{
	gdk_window_get_origin(d_button_ptr->window, x, y);
	(*y) += d_button_ptr->allocation.height;
}


//
// selectionDone: invoked when the user has clicked off of the menu
//   and the menu is no longer active.  sets the relief of the main
//   buttons back to non-hovering state.
//
void
AiksaurusGTK_picbutton::selectionDone()
{
	d_menushowing = false;
    handleRelief();
}


// 
// cbMenuActivate: invoked when menu option is clicked.
//  gpointer is a pointer-to-AiksaurusGTK_menudata (implemented at top of file).
//  just call menuActivate on the correct picbutton.
//
void 
AiksaurusGTK_picbutton::cbMenuActivate(GtkMenuItem* item, gpointer data)
{
    static_cast<AiksaurusGTK_menudata*>(data)->d_picbutton_ptr->menuActivate(data);
}

//
// menuActivate: invoked by cbMenuActivate
//  gpointer is pointer-to-AiksaurusGTK_menudata (implemented at top of file).
//  call a callback function of the form
//     void callback(GList* entry, gpointer data) 
//  where 'data' is user-data send to addMenu function.
//
typedef void (*AikCallbackFn)(gpointer, gpointer);

void
AiksaurusGTK_picbutton::menuActivate(gpointer item)
{
    AiksaurusGTK_menudata* data = static_cast<AiksaurusGTK_menudata*>(item);
    selectionDone();

    AikCallbackFn f = (AikCallbackFn)d_onclick_function;
    f(data->d_glist_ptr, d_onclick_data);
}


// 
// addMenu function: invoked by user.
//   add a menu button to the picbutton and prepare for running a menu.
//
void
AiksaurusGTK_picbutton::addMenu
(const AiksaurusGTK_strlist& options, GtkSignalFunc onClick, gpointer onClickData)
{
    d_onclick_function = onClick;
    d_onclick_data = onClickData;

	d_hasmenu = true;

	d_menu_button_ptr = gtk_button_new();
	gtk_widget_show(d_menu_button_ptr);

	GTK_WIDGET_UNSET_FLAGS(
		d_menu_button_ptr,
		GTK_CAN_FOCUS
	);

	d_menu_pixmap_ptr = gdk_pixmap_create_from_xpm_d(
		d_window_ptr->window,
		&d_menu_mask_ptr,
		&d_style_ptr->bg[GTK_STATE_NORMAL],
		(gchar**)s_downArrow
	);

	d_menu_pixmap_widget_ptr = gtk_pixmap_new(
		d_menu_pixmap_ptr,
		d_menu_mask_ptr
	);

	gtk_widget_show(d_menu_pixmap_widget_ptr);

	gtk_container_add(
		GTK_CONTAINER(d_menu_button_ptr),
		d_menu_pixmap_widget_ptr
	);

	g_signal_connect(
		GTK_OBJECT(d_menu_button_ptr),
		"enter",
		GTK_SIGNAL_FUNC(cbHover),
		this
	);

	g_signal_connect(
		GTK_OBJECT(d_menu_button_ptr),
		"leave",
		GTK_SIGNAL_FUNC(cbUnhover),
		this
	);

	handleRelief();

	g_signal_connect(
		GTK_OBJECT(d_menu_button_ptr),
		"clicked",
		GTK_SIGNAL_FUNC(cbPopMenu),
		this
	);

    menuCreate();

    d_menu_options_ptr = const_cast<AiksaurusGTK_strlist*>(&options);
}


void
AiksaurusGTK_picbutton::menuCreate()
{
    if (d_menu_ptr != NULL)
        gtk_widget_destroy(d_menu_ptr);

    d_menu_ptr = gtk_menu_new();

    gtk_widget_show(d_menu_ptr);

	g_signal_connect(
		GTK_OBJECT(d_menu_ptr),
		"selection-done",
		GTK_SIGNAL_FUNC(cbSelectionDone),
		this
	);

    if (d_menu_data_ptr != NULL)
        delete[] d_menu_data_ptr;

    d_menu_data_ptr = NULL;
}


void
AiksaurusGTK_picbutton::limitVisibleOptions(int numVisible)
{
    d_numVisible = numVisible;
}

void
AiksaurusGTK_picbutton::updateMenuOptions()
{
    menuCreate();

    GList* itor = const_cast<GList*>(d_menu_options_ptr->list());

    int i = 0;
    d_menu_data_ptr = new AiksaurusGTK_menudata[ d_menu_options_ptr->size() ];

    while(itor != NULL)
    {
        if (d_numVisible > 0)
        {
            if (i >= d_numVisible)
                break;
        }
        
        d_menu_data_ptr[i].d_picbutton_ptr = this;
        d_menu_data_ptr[i].d_glist_ptr = itor;

        GtkWidget* option = gtk_menu_item_new_with_label(
                static_cast<char*>(itor->data)
        );

        gtk_widget_show(option);

        gtk_menu_append(GTK_MENU(d_menu_ptr), option);

        g_signal_connect(
            GTK_OBJECT(option),
            "activate",
            GTK_SIGNAL_FUNC(cbMenuActivate),
            &d_menu_data_ptr[i]
        );

        ++i;
        itor = itor->next;
    }
}


//////////////////////////////////////////////////////////////////////////
//                                                                      //
//   Callback Functions                                                 //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

void AiksaurusGTK_picbutton::cbHover(GtkWidget* w, gpointer data)
{
	static_cast<AiksaurusGTK_picbutton*>(data)->hover();
}

void AiksaurusGTK_picbutton::cbUnhover(GtkWidget* w, gpointer data)
{
	static_cast<AiksaurusGTK_picbutton*>(data)->unhover();
}

void AiksaurusGTK_picbutton::cbPopMenu(GtkWidget* w, gpointer data)
{
	static_cast<AiksaurusGTK_picbutton*>(data)->popMenu();
}

void AiksaurusGTK_picbutton::cbPopupFunction(GtkMenu* menu, int* x, int* y, gboolean* notUsedBool, gpointer data)
{
	static_cast<AiksaurusGTK_picbutton*>(data)->popupFunction(x, y);
}

void AiksaurusGTK_picbutton::cbSelectionDone(GtkMenuShell* menushell, gpointer data)
{
	static_cast<AiksaurusGTK_picbutton*>(data)->selectionDone();
}



//////////////////////////////////////////////////////////////////////////
//                                                                      //
//   XPM Pictures                                                       //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

const char *AiksaurusGTK_picbutton::s_downArrow[]={
"11 16 2 1",
"# c #000000",
". c None",
"...........",
"...........",
"...........",
"...........",
"...........",
"...........",
"..#######..",
"...#####...",
"....###....",
".....#.....",
"...........",
"...........",
"...........",
"...........",
"...........",
"..........."};

