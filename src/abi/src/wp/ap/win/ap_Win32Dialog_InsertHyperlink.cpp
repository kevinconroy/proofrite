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

#include <windows.h>

#include "ut_string.h"
#include "ut_assert.h"
#include "ut_debugmsg.h"

#include "xap_App.h"
#include "xap_Win32App.h"
#include "xap_Win32FrameImpl.h"

#include "ap_Strings.h"
#include "ap_Dialog_Id.h"
#include "ap_Dialog_InsertHyperlink.h"
#include "ap_Win32Dialog_InsertHyperlink.h"

#include "ap_Win32Resources.rc2"

/*****************************************************************/

XAP_Dialog * AP_Win32Dialog_InsertHyperlink::static_constructor(XAP_DialogFactory * pFactory,
													 XAP_Dialog_Id id)
{
	AP_Win32Dialog_InsertHyperlink * p = new AP_Win32Dialog_InsertHyperlink(pFactory,id);
	return p;
}

AP_Win32Dialog_InsertHyperlink::AP_Win32Dialog_InsertHyperlink(XAP_DialogFactory * pDlgFactory,
										 XAP_Dialog_Id id)
	: AP_Dialog_InsertHyperlink(pDlgFactory,id),
	_win32Dialog(this)
{
}

AP_Win32Dialog_InsertHyperlink::~AP_Win32Dialog_InsertHyperlink(void)
{
}

void AP_Win32Dialog_InsertHyperlink::runModal(XAP_Frame * pFrame)
{
	UT_ASSERT(pFrame);

	_win32Dialog.runModal( pFrame,
                           AP_DIALOG_ID_INSERTHYPERLINK,
                           AP_RID_DIALOG_INSERTHYPERLINK,
                           this);


}

#define _DS(c,s)	SetDlgItemText(hWnd,AP_RID_DIALOG_##c,pSS->getValue(AP_STRING_ID_##s))
#define _DSX(c,s)	SetDlgItemText(hWnd,AP_RID_DIALOG_##c,pSS->getValue(XAP_STRING_ID_##s))

BOOL AP_Win32Dialog_InsertHyperlink::_onInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	XAP_Win32App * app = static_cast<XAP_Win32App *> (m_pApp);
	UT_ASSERT(app);

	const XAP_StringSet * pSS = m_pApp->getStringSet();

	// localize dialog title
	_win32Dialog.setDialogTitle( pSS->getValue(AP_STRING_ID_DLG_InsertHyperlink_Title) );

	// localize controls
	_DSX(INSERTHYPERLINK_BTN_OK,			DLG_OK);
	_DSX(INSERTHYPERLINK_BTN_CANCEL,		DLG_Cancel);

	_DS(INSERTHYPERLINK_LBL_MSG,			DLG_InsertHyperlink_Msg);

	// initial data
	_win32Dialog.resetContent(AP_RID_DIALOG_INSERTHYPERLINK_LBX_LINK);

	UT_uint32 count = getExistingBookmarksCount();
	for( UT_uint32 i = 0; i < count; i++)
	{
		_win32Dialog.addItemToList( AP_RID_DIALOG_INSERTHYPERLINK_LBX_LINK,
                                    getNthExistingBookmark( i ) );
	}

	SetFocus(GetDlgItem(hWnd,AP_RID_DIALOG_INSERTHYPERLINK_EBX_LINK));

	if(getHyperlink())
	{
		_win32Dialog.setControlText(AP_RID_DIALOG_INSERTHYPERLINK_EBX_LINK, getHyperlink());
		_win32Dialog.selectControlText(AP_RID_DIALOG_INSERTHYPERLINK_EBX_LINK, 0, -1);
	}

	return 0; // 0 because we called set focus
}

BOOL AP_Win32Dialog_InsertHyperlink::_onCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	WORD wNotifyCode = HIWORD(wParam);
	WORD wId = LOWORD(wParam);
	HWND hWndCtrl = (HWND)lParam;

	switch (wId)
	{
	case IDCANCEL:
		setAnswer( a_CANCEL );
		EndDialog(hWnd,0);
		return 1;

	case IDOK:
		{
			char buf[_MAX_PATH];
			_win32Dialog.getControlText( AP_RID_DIALOG_INSERTHYPERLINK_EBX_LINK,
                            			 buf,
                            			 _MAX_PATH );
			setHyperlink(buf);
		}
		setAnswer( a_OK );
		EndDialog(hWnd, 0);
		return 1;

	case AP_RID_DIALOG_INSERTHYPERLINK_LBX_LINK:
		{
			UT_sint32 result = _win32Dialog.getListSelectedIndex( wId );
			if( result != LB_ERR )
			{
				char buf[_MAX_PATH];
				_win32Dialog.getListText( wId, result, buf );
				_win32Dialog.setControlText(AP_RID_DIALOG_INSERTHYPERLINK_EBX_LINK, buf);
			}
		}
		return 1;

	default:							// we did not handle this notification
		UT_DEBUGMSG(("WM_Command for id %ld\n",wId));
		return 0;						// return zero to let windows take care of it.
	}
}

BOOL AP_Win32Dialog_InsertHyperlink::_onDeltaPos(NM_UPDOWN * pnmud)
{
	return 0;
}
