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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ut_string.h"
#include "ut_assert.h"
#include "ut_debugmsg.h"

#include "xap_App.h"
#include "xap_Dialog_Id.h"
#include "xap_Win32App.h"
#include "xap_Frame.h"
#include "xap_Win32FrameImpl.h"

#include "xap_Strings.h"
#include "xap_Dialog_Id.h"
#include "xap_Dlg_About.h"
#include "xap_Win32Dlg_About.h"

// #include "xap_Win32Resources.rc2"
#include "gr_Win32Graphics.h"
#include "gr_Win32Image.h"
#include "ut_bytebuf.h"
#include "ut_png.h"

/*****************************************************************/

extern unsigned char g_pngSidebar[];		// see ap_wp_sidebar.cpp
extern unsigned long g_pngSidebar_sizeof;	// see ap_wp_sidebar.cpp

bool XAP_Win32Dialog_About::s_bEventLoopDone;

/*****************************************************************/
XAP_Dialog * XAP_Win32Dialog_About::static_constructor(XAP_DialogFactory * pFactory,
															 XAP_Dialog_Id id)
{
	XAP_Win32Dialog_About * p = new XAP_Win32Dialog_About(pFactory,id);
	return p;
}

XAP_Win32Dialog_About::XAP_Win32Dialog_About(XAP_DialogFactory * pDlgFactory,
											 XAP_Dialog_Id id)
	: XAP_Dialog_About(pDlgFactory,id)
{
	m_pGrImageSidebar = NULL;
}

XAP_Win32Dialog_About::~XAP_Win32Dialog_About(void)
{
	DELETEP(m_pGrImageSidebar);
}

const int ABOUT_WIDTH		= 500;
const int ABOUT_HEIGHT		= 390;
const int BUTTON_WIDTH		= 64;
const int BUTTON_HEIGHT		= 24;
const int BUTTON_GAP		= 10;
const int HEADING_HEIGHT	= 36;
const int VERSION_HEIGHT	= 24;
const int COPYRIGHT_HEIGHT	= 24;
const int GPL_HEIGHT		= 180;

const int ID_BUTTON_URL		= 3000;

void XAP_Win32Dialog_About::runModal(XAP_Frame * pFrame)
{
	// raise the dialog
	XAP_Win32App * pWin32App = static_cast<XAP_Win32App *>(m_pApp);
	m_pFrame = pFrame;

	UT_ByteBuf * pBB = new UT_ByteBuf(g_pngSidebar_sizeof);
	pBB->ins(0,g_pngSidebar,g_pngSidebar_sizeof);

	UT_sint32 iImageWidth;
	UT_sint32 iImageHeight;
		
	UT_PNG_getDimensions(pBB, iImageWidth, iImageHeight);
	
	m_pGrImageSidebar = new GR_Win32Image(NULL);
	m_pGrImageSidebar->convertFromBuffer(pBB, iImageWidth, iImageHeight);

	DELETEP(pBB);

	WNDCLASSEX	wndclassAbout;

	wndclassAbout.cbSize		= sizeof(WNDCLASSEX);
	wndclassAbout.style			= CS_HREDRAW | CS_VREDRAW;
	wndclassAbout.lpfnWndProc = (WNDPROC) s_dlgProc;
	wndclassAbout.cbClsExtra	= 0;
	wndclassAbout.cbWndExtra	= 0;
	wndclassAbout.hInstance		= pWin32App->getInstance();
	wndclassAbout.hIcon			= pWin32App->getIcon();
	wndclassAbout.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wndclassAbout.hbrBackground	= GetSysColorBrush(COLOR_BTNFACE);
	wndclassAbout.lpszMenuName	= NULL;
	wndclassAbout.lpszClassName	= "AbiSource_About";
	wndclassAbout.hIconSm		= pWin32App->getSmallIcon();
	
	if (!RegisterClassEx(&wndclassAbout))
	{
		::MessageBeep(MB_ICONEXCLAMATION);
		return;
	}

	const int iScreenWidth  = ::GetSystemMetrics(SM_CXFULLSCREEN);
	const int iScreenHeight = ::GetSystemMetrics(SM_CYFULLSCREEN);

	HWND hWndFrame = static_cast<XAP_Win32FrameImpl*>(m_pFrame->getFrameImpl())->getTopLevelWindow();

	BringWindowToTop(hWndFrame);
	pWin32App->enableAllTopLevelWindows(FALSE);

	char buf[1024];
	const XAP_StringSet*  pSS = m_pApp->getStringSet();	
	sprintf(buf, pSS->getValue(XAP_STRING_ID_DLG_ABOUT_Title), 
			m_pApp->getApplicationName());

	HWND hwndAbout = CreateWindow(	wndclassAbout.lpszClassName,
									buf,
									WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU,
									(iScreenWidth - ABOUT_WIDTH) / 2,
									(iScreenHeight - ABOUT_HEIGHT) /2,
									ABOUT_WIDTH,
									ABOUT_HEIGHT,
									hWndFrame,
									NULL,
									pWin32App->getInstance(),
									NULL);
	if (!hwndAbout)
	{
		UnregisterClass(wndclassAbout.lpszClassName, pWin32App->getInstance());
		::MessageBeep(MB_ICONEXCLAMATION);
		return;
	}

	SetWindowLong(hwndAbout, GWL_USERDATA, reinterpret_cast<LONG>(this));

	RECT rcClient;
	GetClientRect(hwndAbout, &rcClient);
	const int iWidth  = rcClient.right;
	const int iHeight = rcClient.bottom;
		
	HWND hwndOK = CreateWindow("BUTTON",
							   pSS->getValue(XAP_STRING_ID_DLG_OK),
							   WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
							   iWidth - BUTTON_WIDTH - BUTTON_GAP,
							   iHeight - BUTTON_HEIGHT - BUTTON_GAP,
							   BUTTON_WIDTH,
							   BUTTON_HEIGHT,
							   hwndAbout,
							   (HMENU) IDOK,
							   pWin32App->getInstance(),
							   NULL);

	HWND hwndURL = CreateWindow("BUTTON",
								"www.abisource.com",
								WS_CHILD | WS_VISIBLE | WS_TABSTOP,
								iWidth - BUTTON_WIDTH - BUTTON_GAP - 2*BUTTON_WIDTH - BUTTON_GAP,
								iHeight - BUTTON_HEIGHT - BUTTON_GAP,
								BUTTON_WIDTH*2,
								BUTTON_HEIGHT,
								hwndAbout,
								(HMENU) ID_BUTTON_URL,
								pWin32App->getInstance(),
								NULL);

	HWND hwndStatic_Heading = CreateWindow("STATIC",
										   m_pApp->getApplicationName(),
										   WS_CHILD | WS_VISIBLE | SS_CENTER,
										   iImageWidth,
										   BUTTON_GAP,
										   iWidth - iImageWidth,
										   HEADING_HEIGHT,
										   hwndAbout,
										   (HMENU) 3001,
										   pWin32App->getInstance(),
										   NULL);

	sprintf(buf, XAP_ABOUT_VERSION, XAP_App::s_szBuild_Version); 
	HWND hwndStatic_Version = CreateWindow("STATIC",
										   buf,
										   WS_CHILD | WS_VISIBLE | SS_CENTER,
										   iImageWidth + BUTTON_GAP,
										   BUTTON_GAP + HEADING_HEIGHT + BUTTON_GAP,
										   iWidth - 2*BUTTON_GAP - iImageWidth,
										   VERSION_HEIGHT,
										   hwndAbout,
										   (HMENU) 3002,
										   pWin32App->getInstance(),
										   NULL);

	HWND hwndStatic_Copyright = CreateWindow("STATIC",
											 XAP_ABOUT_COPYRIGHT,
											 WS_CHILD | WS_VISIBLE | SS_LEFT,
											 iImageWidth + BUTTON_GAP,
											 BUTTON_GAP + HEADING_HEIGHT + BUTTON_GAP + VERSION_HEIGHT + 1*BUTTON_GAP,
											 iWidth - 2*BUTTON_GAP - iImageWidth,
											 COPYRIGHT_HEIGHT,
											 hwndAbout,
											 (HMENU) 3003,
											 pWin32App->getInstance(),
											 NULL);

	sprintf(buf, XAP_ABOUT_GPL_LONG, m_pApp->getApplicationName());
	HWND hwndStatic_GPL = CreateWindow("STATIC",
									   buf,
									   WS_CHILD | WS_VISIBLE | SS_LEFT,
									   iImageWidth + BUTTON_GAP,
									   BUTTON_GAP + HEADING_HEIGHT + BUTTON_GAP + VERSION_HEIGHT + 1*BUTTON_GAP + VERSION_HEIGHT + BUTTON_GAP,
									   iWidth - 2*BUTTON_GAP - iImageWidth,
									   GPL_HEIGHT,
									   hwndAbout,
									   (HMENU) 3004,
									   pWin32App->getInstance(),
									   NULL);

	LOGFONT lf = { 0 };
	strcpy(lf.lfFaceName, "MS Sans Serif");
	
	lf.lfHeight = 12;
	lf.lfWeight = 0;
	HFONT hfontPrimary = CreateFontIndirect(&lf);

	lf.lfHeight = 6;
	lf.lfWeight = 0;
	HFONT hfontSmall = CreateFontIndirect(&lf);

	strcpy(lf.lfFaceName, "Arial");
	lf.lfHeight = 36;
	lf.lfWeight = FW_BOLD; 
	HFONT hfontHeading = CreateFontIndirect(&lf);
	
	SendMessage(hwndStatic_Heading, WM_SETFONT, (WPARAM) hfontHeading, 0);

	HWND rgFontReceivers[] =
		{ hwndOK, hwndURL, hwndStatic_Version, hwndStatic_Copyright };

	for (int iWnd = 0; iWnd < NrElements(rgFontReceivers); ++iWnd)
	{
		SendMessage(rgFontReceivers[iWnd], WM_SETFONT, (WPARAM) hfontPrimary, 0);
	}

	SendMessage(hwndStatic_GPL, WM_SETFONT, (WPARAM) hfontSmall, 0);
	
	// the event loop
	{
		MSG msg;

		s_bEventLoopDone = false;
	
		while (!s_bEventLoopDone)
		{
			if (GetMessage(&msg, NULL, 0, 0))
			{
				if( hwndAbout && IsDialogMessage( hwndAbout, &msg ) )
					continue;

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				break;
			}
		}
	}

	DestroyWindow(hwndAbout);

	UnregisterClass(wndclassAbout.lpszClassName, pWin32App->getInstance());

	pWin32App->enableAllTopLevelWindows(true);

	if (GetWindow(hWndFrame, GW_HWNDFIRST) != hWndFrame)
	{
		BringWindowToTop(hWndFrame);
	}

	if (GetFocus() != hWndFrame)
	{
		SetFocus(hWndFrame);
	}
}

BOOL CALLBACK XAP_Win32Dialog_About::s_dlgProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	// This is a static function.

	XAP_Win32Dialog_About * pThis = (XAP_Win32Dialog_About *)GetWindowLong(hWnd,GWL_USERDATA);

	if (!pThis)
	{
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	
	switch (msg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
			
		RECT	r;
		GetClientRect(hWnd, &r);
		r.right = pThis->m_pGrImageSidebar->getDisplayWidth();
		FillRect(hdc, &r, GetSysColorBrush(COLOR_BTNFACE));

		GR_Win32Graphics gr(hdc,hWnd,pThis->m_pFrame->getApp(), 0);
		gr.drawImage(pThis->m_pGrImageSidebar,
					 0,
					 (r.bottom - pThis->m_pGrImageSidebar->getDisplayHeight())/2);
		EndPaint(hWnd,&ps);
		return 0;
	}

	case WM_CHAR:
	{
		switch (wParam)
		{
		case 13:	// CR
		case 27:	// ESC
		case 32:	// SPACE
			s_bEventLoopDone = true;
			return 0;
		}
		
		break;
	}

	case WM_COMMAND:
		return pThis->_onCommand(hWnd,wParam,lParam);

	case WM_DESTROY:
		s_bEventLoopDone = true;
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

BOOL XAP_Win32Dialog_About::_onCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	WORD wNotifyCode = HIWORD(wParam);
	WORD wId = LOWORD(wParam);
	HWND hWndCtrl = (HWND)lParam;

	switch (wId)
	{
	case IDCANCEL:
	case IDOK:							// also XAP_RID_DIALOG_ABOUT_BTN_OK
		s_bEventLoopDone = true;
		return 0;

	case ID_BUTTON_URL:
		m_pFrame->openURL("http://www.abisource.com/");
		return 0;
		
	default:							// we did not handle this notification
		UT_DEBUGMSG(("WM_Command for id %ld\n",wId));
		return 0;						// return zero to let windows take care of it.
	}
}
