/*
 *  test-container.c
 *  container for the button control
 */

/*
** Copyright (C) 2000 Dirk-Jan C. Binnema <dirkjan@gnome.org>
**  
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**  
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**  
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
**  
*/

#include <gnome.h>
#include <liboaf/liboaf.h>
#include <bonobo.h>

#include "xap_UnixDialogHelper.h"

static Bonobo_PropertyBag      prop_bag = CORBA_OBJECT_NIL;
static GtkWidget               *bonobo_win;

/*
 * close the app, but clean up things first
 */
static void on_destroy  (GtkWidget *app, BonoboUIContainer *uic)
{
	if (uic)
		bonobo_object_unref (BONOBO_OBJECT (uic));

        if (prop_bag != CORBA_OBJECT_NIL)
                bonobo_object_release_unref (prop_bag, CORBA_OBJECT_NIL);
        gtk_main_quit ();
}

static gboolean s_entry_activated(GtkWidget * wAbiEntry, gpointer p)
{
	gchar *command;
	gchar ** ptr;
	gint n;
	command = gtk_entry_get_text (GTK_ENTRY (wAbiEntry));
	printf("command is %s \n",command);
	ptr = g_strsplit(command," ",100);
	n = 0;
	while(ptr[n] != NULL)
	{
		n++;
	}
	if(n > 1)
	{
		if(strcmp(ptr[0],"load_file") == 0)
		{
			bonobo_property_bag_client_set_value_string (prop_bag, 
												 "AbiWidget::load_file",(gchar *) ptr[1], NULL);
		}
	}
	else if(strcmp(ptr[0],"cursoron") == 0)
	{
		bonobo_property_bag_client_set_value_gboolean (prop_bag, "AbiWidget::cursoron", TRUE, NULL);
	}
	else
	{
		bonobo_property_bag_client_set_value_string (prop_bag, 
												 "AbiWidget::invoke_noargs",(gchar *) command,NULL);
	}
	g_strfreev (ptr);
	return FALSE;
}

/*
 * Create the container frame, the control, the property bag and the
 * surrounding GTK nicities.
 */
static guint create_app (void)
{
	GtkWidget *box, *control, *button;
	BonoboControlFrame *control_frame;
	CORBA_Environment ev;
	GtkWidget * frame1;
	GtkWidget * hseparator1;
	BonoboUIContainer *uic;
	GtkWidget * hboxEntry;
	GtkWidget * AbiCommandLabel;
	GtkWidget * wAbiEntry;
	/*
	 * create a bonobo application (window)
	 */
	bonobo_win = bonobo_window_new ("AbiWord_control",
					"A container for AbiWord");
	gtk_widget_set_usize (GTK_WIDGET(bonobo_win), 600, 600);

	/*
	 * connect a ui container to the application
	 */
	uic = bonobo_ui_container_new ();
	bonobo_ui_container_set_win (uic, BONOBO_WINDOW(bonobo_win));
	
	/* get a widget, containing the control */

	control = bonobo_widget_new_control("OAFIID:AbiSource_AbiWord_Control",
		 BONOBO_OBJREF (uic));
	if (!control) 
	{
		g_error ("Can't create control\n");
	}
	/*
     *  Now acquire a property bag.
	 *  The property bag is associated with the control frame, so get a
	 *  control frame first
	 */
	CORBA_exception_init (&ev);
	control_frame = bonobo_widget_get_control_frame (BONOBO_WIDGET(control));
	if (!control_frame) 
	{
		g_error ("can't find control frame\n");
	}
	/* 
	 * now, get a ref to the property bag
	 */
	prop_bag = bonobo_control_frame_get_control_property_bag (control_frame, NULL);
	if (prop_bag == CORBA_OBJECT_NIL)
	{
		g_error ("can't connect to property bag\n");
	}
/*
 * Build the gtk support structure.
 */

	box = gtk_vbox_new (FALSE, 0);
	gtk_widget_show(box);
	bonobo_window_set_contents (BONOBO_WINDOW(bonobo_win), box);

 	frame1 = gtk_frame_new ("AbiControl");
	gtk_widget_show (frame1);
	gtk_box_pack_start (GTK_BOX (box), frame1, TRUE, TRUE, 0);
	gtk_frame_set_label_align (GTK_FRAME (frame1), 0.04, 0.5);
	gtk_frame_set_shadow_type (GTK_FRAME (frame1), GTK_SHADOW_ETCHED_OUT);

	hseparator1 = gtk_hseparator_new ();
	gtk_widget_show (hseparator1);
	gtk_box_pack_start (GTK_BOX (box), hseparator1, FALSE, FALSE, 0);

	/* 
     * add the AbiWidget to our app 
	 */

	gtk_container_add (GTK_CONTAINER (frame1), control);

/*
 * Create an entry so we can play with the widget.
 */
	hboxEntry = gtk_hbox_new(FALSE,0);
	gtk_widget_show(hboxEntry);
	gtk_box_pack_start (GTK_BOX (box), hboxEntry, TRUE, TRUE, 0);

	AbiCommandLabel = gtk_label_new("AbiWidget Command: ");
	gtk_widget_show(AbiCommandLabel);
	gtk_box_pack_start (GTK_BOX (hboxEntry), AbiCommandLabel, TRUE, TRUE, 0);
	
	wAbiEntry = gtk_entry_new();
	gtk_widget_show(wAbiEntry);
	gtk_box_pack_start (GTK_BOX (hboxEntry), wAbiEntry, TRUE, TRUE, 0);
	g_signal_connect(G_OBJECT(wAbiEntry),
					   "activate",
					   G_CALLBACK(s_entry_activated),
					   (gpointer) NULL);

	/* 
     * create a "close" button and add it to the app 
     */
	button = gtk_button_new_with_label ("close");
	gtk_box_pack_start(GTK_BOX (box), button, FALSE,FALSE,0);
	g_signal_connect (G_OBJECT(button), "clicked",
			    G_CALLBACK(on_destroy), NULL);

	/* 
     * create a 'destroy' handler, so we can clean things up 
	 */
	g_signal_connect (G_OBJECT(bonobo_win), "destroy", on_destroy, uic);

	/* 
	 * OK Boris let her rip!!!
	 */
	gtk_widget_show_all (GTK_WIDGET(bonobo_win));

/*
 * Send some commands to our control.
 */
	bonobo_property_bag_client_set_value_gboolean (prop_bag, "AbiWidget::map_to_screen", TRUE, NULL);
	bonobo_property_bag_client_set_value_string (prop_bag, 
												 "AbiWidget::load_file", "/home/msevior/abidir/AbiSuite/bin/fred.abw", NULL);
	bonobo_property_bag_client_set_value_gboolean (prop_bag, "AbiWidget::cursoron", TRUE, NULL);

	return FALSE; /* putting TRUE here is a bad idea. I warned you. */
}




int 
main (int argc, char** argv)
{
	CORBA_ORB orb;
	
	gnome_init_with_popt_table ("test-container", "0.0",
				     argc, argv, oaf_popt_options, 0, NULL);

	/*
	 * initialize CORBA, OAF  and bonobo
	 */
	orb = oaf_init (argc,argv);
	if (!orb)
		g_error ("initializing orb failed");
	if (!bonobo_init (orb, NULL, NULL))
		g_error ("could not initialize Bonobo");


	/*
	 * We can't make any CORBA calls unless we're in the main
	 * loop.  So we delay creating the container here.
	 */
	gtk_idle_add ((GtkFunction) create_app, NULL);
	bonobo_main ();

	return 0;
}

