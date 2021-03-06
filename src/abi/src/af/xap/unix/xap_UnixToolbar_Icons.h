/* AbiSource Application Framework
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

#ifndef XAP_UNIXTOOLBARICONS_H
#define XAP_UNIXTOOLBARICONS_H

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include "ut_types.h"
#include "xap_Toolbar_Icons.h"

/*****************************************************************/

class AP_UnixToolbar_Icons : public AP_Toolbar_Icons
{
public:
	AP_UnixToolbar_Icons(void);
	~AP_UnixToolbar_Icons(void);

	bool			getPixmapForIcon(GdkWindow * window, GdkColor * background,
									 const char * szIconName, GtkWidget ** pwPixmap);
	
protected:
};

#endif /* XAP_UNIXTOOLBARICONS_H */
