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

#ifndef XAP_WIN32DIALOG_LANGUAGE_H
#define XAP_WIN32DIALOG_LANGUAGE_H

#include "xap_Dlg_Language.h"
#include "xap_Win32DialogHelper.h"
#include "xap_Frame.h"

/*****************************************************************/

class XAP_Win32Dialog_Language: public XAP_Dialog_Language
{
public:
	XAP_Win32Dialog_Language(XAP_DialogFactory * pDlgFactory, XAP_Dialog_Id id);
	virtual ~XAP_Win32Dialog_Language(void);

	virtual void			runModal(XAP_Frame * pFrame);

	static XAP_Dialog *		static_constructor(XAP_DialogFactory *, XAP_Dialog_Id id);
	
	static BOOL CALLBACK	s_dlgProc(HWND,UINT,WPARAM,LPARAM);
	static BOOL CALLBACK 	s_treeProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
	void 					_setLanguageAndExit(UINT nLang);
		
protected:
	void  					_fillTreeview(HWND hTV);
	BOOL					_onInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
	BOOL					_onCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
		
	HWND					m_hWnd;

};

#endif /* XAP_WIN32DIALOG_LANGUAGE_H */
