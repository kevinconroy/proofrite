/*
 * AbiCommand - Abiword plugin for a command line interface
 * Copyright (C) 2002 by Martin Sevior
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

#ifndef PLUGIN_ABICOMMAND_H
#define PLUGIN_ABICOMMAND_H
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk/gdkx.h>
#include "glib.h"
#include "glibconfig.h"

#include "ut_assert.h"
#include "ut_debugmsg.h"
#include "xap_Module.h"
#include "xap_App.h"
#include "xap_FrameImpl.h"
#include "xap_UnixFrameImpl.h"
#include "xav_View.h"
#include "fv_View.h"
#include "fv_View.h"
#include "ev_Menu_Layouts.h"
#include "ev_Menu_Labels.h"
#include "ev_EditMethod.h"
#include "pd_Document.h"
#include "xap_UnixNullGraphics.h"
#include "fg_Graphic.h"
#include "ie_imp.h"
#include "ie_impGraphic.h"
#include "ie_exp.h"
#include "ie_types.h"
#include "fl_DocLayout.h"
#include "ut_sleep.h"
#include "xap_FrameImpl.h"
#include "xap_UnixFrameImpl.h"
#include "ap_UnixFrame.h"

class AbiCommand
{
public:
	                         AbiCommand(void);
	virtual                  ~AbiCommand(void);
	void                     doCommands(void);
	UT_sint32                parseTokens(UT_Vector * pToks);
	bool                     printFiles(UT_Vector * pToks);
	bool                     replaceAll(UT_Vector * pToks);
	bool                     replaceNext(UT_Vector * pToks);
	bool                     movePoint(UT_Vector * pToks);
	bool                     deleteText(UT_Vector * pToks);
	bool                     insertText(UT_Vector * pToks);
	bool                     replaceDocument(PD_Document * pDoc);
	void                     clearTokenVector(UT_Vector & Toks);
	bool                     invoke(const char * pszCommand);
	bool                     tokenizeString(UT_Vector & tok, char * pStr);
	void                     nullUpdate();
	bool                     removeGraphicalView(void);
	void                     deleteCurrentDoc(void);
	bool                     viewDoc(void);
private:
	PD_Document *            m_pCurDoc;
	AP_UnixFrame  *          m_pCurFrame;
	AV_View *                m_pCurView;
	UnixNull_Graphics *      m_pG;
	FL_DocLayout *           m_pLayout;
	XAP_App *                m_pApp;
	bool                     m_bViewDoc;

};

#endif /* PLUGIN_ABICOMMAND_H */












