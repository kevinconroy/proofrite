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

#ifndef XAP_WIN32DIALOG_PRINT_H
#define XAP_WIN32DIALOG_PRINT_H

#include "xap_Dlg_Print.h"
#include "xap_Frame.h"

/*****************************************************************/

class XAP_Win32Dialog_Print : public XAP_Dialog_Print
{
public:
	XAP_Win32Dialog_Print(XAP_DialogFactory * pDlgFactory, XAP_Dialog_Id id);
	virtual ~XAP_Win32Dialog_Print(void);

	virtual void			runModal(XAP_Frame * pFrame);
	virtual GR_Graphics *		getPrinterGraphicsContext(GR_Win32InkOverlay *inkOverlay);
	virtual void			releasePrinterGraphicsContext(GR_Graphics *);

	static XAP_Dialog *		static_constructor(XAP_DialogFactory *, XAP_Dialog_Id id);

protected:
	void					_extractResults(XAP_Frame *pFrame);
	
	PRINTDLG *				m_pPersistPrintDlg;
	DOCINFO				m_DocInfo;
};

#endif /* XAP_WIN32DIALOG_PRINT_H */