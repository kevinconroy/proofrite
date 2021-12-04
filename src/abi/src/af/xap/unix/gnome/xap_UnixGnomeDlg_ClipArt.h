/* AbiSource Application Framework
 * Copyright (C) 2001 AbiSource, Inc.
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

#ifndef XAP_UNIXGNOMEDIALOG_CLIPART_H
#define XAP_UNIXGNOMEDIALOG_CLIPART_H

#include <libgnomeui-2.0/gnome.h>
#include "xap_Dlg_ClipArt.h"

/*****************************************************************/

class XAP_UnixGnomeDialog_ClipArt: public XAP_Dialog_ClipArt
{
 public:
	XAP_UnixGnomeDialog_ClipArt(XAP_DialogFactory * pDlgFactory, XAP_Dialog_Id id);
	virtual ~XAP_UnixGnomeDialog_ClipArt(void);

	static XAP_Dialog *		static_constructor(XAP_DialogFactory *, XAP_Dialog_Id id);

	virtual void			runModal(XAP_Frame * pFrame);
 private:

	GtkWidget * _constructPreviewPane ();

	GtkWidget * m_dialog;
	gint m_index;
};

#endif /* XAP_UNIXGNOMEDIALOG_CLIPART_H */
