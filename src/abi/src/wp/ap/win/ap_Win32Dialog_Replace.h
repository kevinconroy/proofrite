/* AbiWord
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

#ifndef AP_WIN32DIALOG_REPLACE_H
#define AP_WIN32DIALOG_REPLACE_H

#include "ap_Dialog_Replace.h"
#include "xap_Frame.h"


/*****************************************************************/

class AP_Win32Dialog_Replace: public AP_Dialog_Replace
{
public:
	AP_Win32Dialog_Replace(XAP_DialogFactory * pDlgFactory, XAP_Dialog_Id id);
	virtual ~AP_Win32Dialog_Replace(void);

	virtual void			runModal(XAP_Frame * pFrame){};
	virtual void			runModeless(XAP_Frame * pFrame);
	virtual void			notifyActiveFrame(XAP_Frame *pFrame);
	virtual void			notifyCloseFrame(XAP_Frame *pFrame);
	virtual void			destroy(void);
	virtual void			activate(void);
	virtual void *			pGetWindowHandle( void ) { return (void*)m_hWnd; }

	static XAP_Dialog * 	static_constructor(XAP_DialogFactory *, XAP_Dialog_Id id);
	static BOOL CALLBACK	s_dlgProc(HWND,UINT,WPARAM,LPARAM);
	
protected:
	void					_initButtons(HWND hWnd);
	BOOL					_onInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
	BOOL					_onCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
	BOOL					_onBtn_FindNext(HWND hWnd);
	BOOL					_onBtn_Replace(HWND hWnd);
	BOOL					_onBtn_ReplaceAll(HWND hWnd);
	HWND					m_hWnd;
};

#endif /* AP_WIN32DIALOG_REPLACE_H */
