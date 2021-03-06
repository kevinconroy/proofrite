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

#ifndef AP_QNXDIALOG_NEW_H
#define AP_QNXDIALOG_NEW_H

#include "ap_Dialog_New.h"

class XAP_QNXFrame;

/*****************************************************************/

class AP_QNXDialog_New: public AP_Dialog_New
{
public:
	AP_QNXDialog_New(XAP_DialogFactory * pDlgFactory, XAP_Dialog_Id id);
	virtual ~AP_QNXDialog_New(void);

	virtual void			runModal(XAP_Frame * pFrame);

	static XAP_Dialog *		static_constructor(XAP_DialogFactory *, 
											   XAP_Dialog_Id id);

	void event_Ok ();
	void event_Cancel ();
	void event_ToggleUseTemplate (const char * name);
	void event_ToggleOpenExisting ();
	void event_ToggleStartNew ();
	void event_ToggleSelection(PtWidget_t *w);
	void event_ListClicked();
	
protected:

	virtual PtWidget_t * _constructWindow ();

	void _connectSignals ();

	/* private ... */
	PtWidget_t * m_mainWindow;
	PtWidget_t * m_buttonOk;
	PtWidget_t * m_buttonCancel;


private:
	XAP_Frame * m_pFrame;

	PtWidget_t * m_entryFilename;
	PtWidget_t * m_radioNew;
	PtWidget_t * m_radioExisting;
	PtWidget_t * m_radioEmpty;
	PtWidget_t * m_list;
	
	UT_Vector mTemplates ;

	int done;
};

#endif /* AP_QNXDIALOG_NEW_H */
