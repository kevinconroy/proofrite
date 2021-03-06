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

#ifndef AP_UNIXDIALOG_LISTREVISIONS_H
#define AP_UNIXDIALOG_LISTREVISIONS_H

#include <gtk/gtk.h>
#include "ut_types.h"
#include "ap_Dialog_ListRevisions.h"

class XAP_UnixFrame;

/*****************************************************************/

class AP_UnixDialog_ListRevisions: public AP_Dialog_ListRevisions
{
 public:
	AP_UnixDialog_ListRevisions(XAP_DialogFactory * pDlgFactory, XAP_Dialog_Id id);
	virtual ~AP_UnixDialog_ListRevisions(void);

	virtual void			runModal(XAP_Frame * pFrame);

	static XAP_Dialog *		static_constructor(XAP_DialogFactory *, XAP_Dialog_Id id);

 protected:
	typedef enum
	{
		BUTTON_OK,
		BUTTON_CANCEL
	} ResponseId ;
	
	virtual GtkWidget * constructWindow () ;

	static void ok_callback ( GtkWidget *, AP_UnixDialog_ListRevisions * me )
	  {
	    UT_return_if_fail ( me ) ;
	    me->event_OK () ;
	  }

	static void cancel_callback ( GtkWidget *, AP_UnixDialog_ListRevisions * me )
	  {
	    UT_return_if_fail ( me ) ;
	    me->event_Cancel () ;
	  }

	static void destroy_callback ( GtkWidget *, gpointer, AP_UnixDialog_ListRevisions * me )
	  {
	    UT_return_if_fail ( me ) ;
	    me->event_Cancel () ;
	  }

	static void select_row_callback ( GtkWidget *, gint row, gint col, GdkEventButton * event, AP_UnixDialog_ListRevisions * me )
	  {
	    me->select_Row ( row ) ;
	  }

	static void unselect_row_callback ( GtkWidget *, gint row, gint col, GdkEventButton * event, AP_UnixDialog_ListRevisions * me )
	  {
	    me->unselect_Row ();
	  }

	static void dblclick_callback(GtkWidget * widget,
				      GdkEventButton * event,
				      AP_UnixDialog_ListRevisions * me)
	  {
	    // Only respond to double clicks
	    if (event->type == GDK_2BUTTON_PRESS)
	      {
		me->event_OK();
	      }
	  }

	void event_OK () ;
	void event_Cancel () ;

 private:
	
	void constructWindowContents ( GtkWidget * container ) ;

	void select_Row (gint which) ;
	void unselect_Row () ;

	GtkWidget * mClist ;
} ;

#endif /* AP_UNIXDIALOG_LISTREVISIONS_H */
