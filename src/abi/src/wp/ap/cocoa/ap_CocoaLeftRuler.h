/* AbiWord
 * Copyright (C) 1998 AbiSource, Inc.
 * Copyright (C) 2001 Hubert Figuiere
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

#ifndef AP_COCOALEFTRULER_H
#define AP_COCOALEFTRULER_H

// Class for dealing with the horizontal ruler at the left of
// a document window.

/*****************************************************************/

#import <Cocoa/Cocoa.h>

#include "ut_types.h"
#include "ap_LeftRuler.h"
#include "gr_CocoaGraphics.h"
class XAP_Frame;


/*****************************************************************/

class AP_CocoaLeftRuler : public AP_LeftRuler
{
public:
	AP_CocoaLeftRuler(XAP_Frame * pFrame);
	virtual ~AP_CocoaLeftRuler(void);

	XAP_CocoaNSView *		createWidget(void);
	virtual void	setView(AV_View * pView);

	// cheats for the callbacks
	void				getWidgetPosition(int * x, int * y);
	XAP_CocoaNSView * 		getWidget(void) { return m_wLeftRuler; };
	NSWindow * 	getRootWindow(void);

//	void _ruler_style_changed (void);
	
private:
	static bool _graphicsUpdateCB(NSRect * aRect, GR_CocoaGraphics *pG, void* param);
	
	XAP_CocoaNSView *		m_wLeftRuler;
	NSWindow *	m_rootWindow;

#if 0
	class _fe
	{
	public:
		static gint button_press_event(GtkWidget * w, GdkEventButton * e);
		static gint button_release_event(GtkWidget * w, GdkEventButton * e);
		static gint configure_event(GtkWidget* w, GdkEventConfigure *e);
		static gint motion_notify_event(GtkWidget* w, GdkEventMotion* e);
		static gint key_press_event(GtkWidget* w, GdkEventKey* e);
		static gint delete_event(GtkWidget * w, GdkEvent * /*event*/, gpointer /*data*/);
		static gint abi_expose_repaint( gpointer /* AP_CocoaLeftRuler * */ p);
		static void destroy (GtkWidget * /*widget*/, gpointer /*data*/);
	};
#endif
};

#endif /* AP_COCOALEFTRULER_H */
