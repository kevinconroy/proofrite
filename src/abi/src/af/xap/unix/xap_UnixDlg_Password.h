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

#ifndef XAP_UNIXDIALOG_PASSWORD_H
#define XAP_UNIXDIALOG_PASSWORD_H

#include <gtk/gtk.h>
#include "xap_Dlg_Password.h"

class XAP_Frame;

/*****************************************************************/

class XAP_UnixDialog_Password: public XAP_Dialog_Password
{
public:
	XAP_UnixDialog_Password(XAP_DialogFactory * pDlgFactory, XAP_Dialog_Id id);
	virtual ~XAP_UnixDialog_Password(void);

	virtual void			runModal(XAP_Frame * pFrame);

	static XAP_Dialog *		static_constructor(XAP_DialogFactory *, XAP_Dialog_Id id);

 protected:

 private:

	typedef enum
	  {
	    BUTTON_OK,
	    BUTTON_CANCEL
	  } ResponseId ;

	void event_Ok ();
	void event_Cancel ();
	
	void event_Return () ;

	static void s_return_hit ( GtkWidget * entry, XAP_UnixDialog_Password * me )
	  {
	    me->event_Return () ;
	  }

	void _constructWindowContents (GtkWidget * container);
	virtual GtkWidget * _constructWindow ();
	
	GtkWidget * mMainWindow;
	GtkWidget * mTextEntry;
};

#endif /* XAP_UNIXDIALOG_PASSWORD_H */
