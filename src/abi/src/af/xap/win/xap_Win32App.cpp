/* AbiSource Application Framework
 * Copyright (C) 1998-2000 AbiSource, Inc.
 * BIDI Copyright (c) 2001,2002 Tomas Frydrych
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

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <direct.h>
#include "ut_assert.h"
#include "ut_debugmsg.h"
#include "xap_Args.h"
#include "xap_Win32App.h"
#include "xap_Win32Clipboard.h"
#include "xap_Frame.h"
#include "xap_Win32FrameImpl.h"
#include "xap_Win32Toolbar_Icons.h"
#include "xap_Win32_TB_CFactory.h"
#include "xap_Win32Slurp.h"
#include "xap_Win32EncodingManager.h"

#ifdef _MSC_VER
#pragma warning(disable:4355)	// 'this' used in base member initializer list
#endif


/*****************************************************************/

XAP_Win32App::XAP_Win32App(HINSTANCE hInstance, XAP_Args * pArgs, const char * szAppName)
:	XAP_App(pArgs, szAppName),
	m_hInstance(hInstance),
	m_dialogFactory(this)
{
	UT_ASSERT(hInstance);

	_setAbiSuiteLibDir();
	_setBidiOS();
}

XAP_Win32App::~XAP_Win32App(void)
{
	m_pSlurp->disconnectSlurper();
	DELETEP(m_pSlurp);
}

HINSTANCE XAP_Win32App::getInstance() const
{
	return m_hInstance;
}

bool XAP_Win32App::initialize(void)
{
	// let our base class do it's thing.

	XAP_App::initialize();

	// do anything else we need here...

	m_pSlurp = new XAP_Win32Slurp(this);
	m_pSlurp->connectSlurper();
	char bufExePathname[4096];
	GetModuleFileName(NULL,bufExePathname,NrElements(bufExePathname));

	// TODO these are Application-Specific values.  Move them out of here.
	m_pSlurp->stuffRegistry(".abw",getApplicationName(),bufExePathname,"application/abiword");
	m_pSlurp->stuffRegistry(".zabw",getApplicationName(),bufExePathname,"application/abiword-compressed");

	return true;
}

void XAP_Win32App::reallyExit(void)
{
	PostQuitMessage (0);
}

UT_sint32 XAP_Win32App::makeDirectory(const char * szPath, const UT_sint32 mode ) const { return mkdir(szPath); }

XAP_DialogFactory * XAP_Win32App::getDialogFactory(void)
{
	return &m_dialogFactory;
}

XAP_Toolbar_ControlFactory * XAP_Win32App::getControlFactory(void)
{
	return &m_controlFactory;
}

UT_uint32 XAP_Win32App::_getExeDir(char* pDirBuf, UT_uint32 iBufLen)
{
	UT_uint32 iResult = GetModuleFileName(NULL, pDirBuf, iBufLen);

	if (iResult > 0)
	{
		char* p = pDirBuf + strlen(pDirBuf);
		while (*p != '\\')
		{
			p--;
		}
		UT_ASSERT(p > pDirBuf);
		p++;
		*p = 0;
	}

	return iResult;
}

const char * XAP_Win32App::getUserPrivateDirectory(void)
{
	/* return a pointer to a static buffer */

	char * szAbiDir = "AbiSuite";

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

	static char buf[PATH_MAX];
	memset(buf,0,sizeof(buf));

	DWORD len, len1, len2;

	// On NT, USERPROFILE seems to be set to the directory containing per-user
	// information.  we'll try that first.

	len = GetEnvironmentVariable("USERPROFILE",buf,PATH_MAX);
	if (len)
	{
		UT_DEBUGMSG(("Getting preferences directory from USERPROFILE [%s].\n",buf));
	}
	else
	{
		// If that doesn't work, look for HOMEDRIVE and HOMEPATH.  HOMEPATH
		// is mentioned in the GetWindowsDirectory() documentation at least.
		// These may be set if the SysAdmin did so in the Admin tool....

		len1 = GetEnvironmentVariable("HOMEDRIVE",buf,PATH_MAX);
		len2 = GetEnvironmentVariable("HOMEPATH",&buf[len1],PATH_MAX-len1);
		if (len1 && len2)
		{
			UT_DEBUGMSG(("Getting preferences directory from HOMEDRIVE and HOMEPATH [%s].\n",buf));
		}
		else
		{
			// If that doesn't work, let's just stick it in the WINDOWS directory.

			len = GetWindowsDirectory(buf,PATH_MAX);
			if (len)
			{
				UT_DEBUGMSG(("Getting preferences directory from GetWindowsDirectory() [%s].\n",buf));
			}
			else
			{
				// If that doesn't work, stick it in "C:\"...

				strcpy(buf,"C:\\");
			}
		}
	}

	if (strlen(buf)+strlen(szAbiDir)+2 >= PATH_MAX)
		return NULL;

	if (buf[strlen(buf)-1] != '\\')
		strcat(buf,"\\");
	strcat(buf,szAbiDir);
	return buf;
}

static void s_buildDirName(const UT_Vector& vDirComponents, UT_uint32 iComponentsNeeded, char* pDirBuf)
{
	UT_ASSERT(iComponentsNeeded <= vDirComponents.getItemCount());

	if(iComponentsNeeded == 0)
	{
		strcpy(pDirBuf, "\\");
		return;
	}

	UT_uint32 i = 0;
	strcpy(pDirBuf, (const char*) vDirComponents.getNthItem(i++));

	while(--iComponentsNeeded)
	{
		strcat(pDirBuf, "\\");
		strcat(pDirBuf, (const char*) vDirComponents.getNthItem(i++));
	}
}

void XAP_Win32App::_setAbiSuiteLibDir(void)
{
	char buf[PATH_MAX];
	char buf2[PATH_MAX];
	char szApplicationName[PATH_MAX];
	const char * sz = NULL;

	// see if a command line option [-lib <AbiSuiteLibraryDirectory>] was given

	int kLimit = m_pArgs->m_argc;
	int nFirstArg = 0;	// Win32 does not put the program name in argv[0], so [0] is the first argument
	int k;

	for (k=nFirstArg; k<kLimit; k++)
		if ((*m_pArgs->m_argv[k] == '-') && (UT_stricmp(m_pArgs->m_argv[k],"-lib")==0) && (k+1 < kLimit))
		{
			strcpy(buf,m_pArgs->m_argv[k+1]);
			int len = strlen(buf);
			if (buf[len-1]=='\\')		// trim trailing slash
				buf[len-1] = 0;
			XAP_App::_setAbiSuiteLibDir(buf);
			return;
		}

	// if not, see if ABISUITE_HOME was set in the environment

	if (GetEnvironmentVariable("ABISUITE_HOME",buf,sizeof(buf)) > 0)
	{
		char * p = buf;
		int len = strlen(p);
		if ( (p[0]=='"') && (p[len-1]=='"') )
		{
			// trim leading and trailing DQUOTES
			p[len-1]=0;
			p++;
			len -= 2;
		}
		if (p[len-1]=='\\')				// trim trailing slash
			p[len-1] = 0;
		XAP_App::_setAbiSuiteLibDir(p);
		return;
	}

	// [Win32 only] if not, use something relative to <exedir>
	// if we are in normal distribution format, we have:
	//
	// .../AbiSuite/AbiWord/bin/AbiWord.exe
	//                     /strings/*.strings
	//                     /help/en-US/*.html
	//                     /samples/en-US/*.abw
	//             /AbiShow/bin/AbiShow.exe
	//                     /strings/*.strings
	//                     /help/en-US/*.html
	//                     /samples/en-US/*.abw
	//             /dictionary/*.hash
	//
	// we want to set the library directory to the
	// directory which stand for .../AbiSuite
	// (aka "getExeDir()/../..")
	//
	// if this is a developer build in the canonical build
	// directory, we have:
	//
	// $(OUT)/$os_..._$dbg/bin/AbiWord.exe
	//                        /AbiShow.exe
	//                    /obj/*.obj
	//                    /AbiSuite/AbiWord/strings/*.strings
	//                                     /help/...
	//                                     /samples/...
	//                             /AbiShow/...
	//                             /dictionary/*.hash
	//
	// note that the bin directory is in a different place.
	// in this case, we want to set the library directory to
	// $(OUT)/$os_..._$dbg/AbiSuite
	// (aka "getExeDir()/../AbiSuite")

	if (_getExeDir(buf,sizeof(buf)) > 0)
	{
		int len = strlen(buf);
		if (buf[len-1]=='\\')
			buf[len-1] = 0;

		strcpy(buf2,buf);

		UT_Vector v;
		char * p = strtok(buf2,"\\");
		v.addItem(p);
		while ( (p=strtok(NULL,"\\")) )
			v.addItem(p);

		strcpy(szApplicationName, getApplicationName());
		strtok(szApplicationName, " ");

		int n = v.getItemCount();
		if (   (n > 2)
			&& (UT_stricmp((const char *)v.getNthItem(n-1),"bin")==0)
			&& (UT_stricmp((const char *)v.getNthItem(n-2),szApplicationName)==0))
		{
			s_buildDirName(v, n - 2, buf);
			XAP_App::_setAbiSuiteLibDir(buf);
			return;
		}

		if (   (n > 1)
			&& (UT_stricmp((const char *)v.getNthItem(n-1),"bin")==0))
		{
			s_buildDirName(v, n - 1, buf);
			strcat(buf,"\\AbiSuite");
			XAP_App::_setAbiSuiteLibDir(buf);
			return;
		}

		// [win32 only] if none of this works, just leave it the exe directory.

		XAP_App::_setAbiSuiteLibDir(buf);
		return;
	}

	UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
	return;
}

void XAP_Win32App::enableAllTopLevelWindows(bool b)
{
	UT_uint32 iCount = m_vecFrames.getItemCount();

	for (UT_uint32 ndx=0; ndx<iCount; ndx++)
	{
		XAP_Frame * pFrame = (XAP_Frame *) m_vecFrames.getNthItem(ndx);

		EnableWindow(static_cast<XAP_Win32FrameImpl*>(pFrame->getFrameImpl())->getTopLevelWindow(), b);
	}
}

// This function gets saved geometry from preference file, attempts to validate
// and sets window's placement.  It returns the flag that should be called to
// ShowWindow on the first call.
UT_sint32 XAP_Win32App::setupWindowFromPrefs(UT_sint32 iCmdShow, HWND hwndFrame)
{
	UT_uint32 iHeight, iWidth;
	UT_sint32 x,y;
	UT_uint32 flag;

	// if width & height are <= 0 then assume invalid values so just use system defaults
	if (getGeometry(&x,&y,&iWidth,&iHeight,&flag) && (iWidth > 0) && (iHeight > 0))
	{
		WINDOWPLACEMENT wndPlacement;
		wndPlacement.length = sizeof(WINDOWPLACEMENT); // must do
		// get current windowplacement info, so anything we don't set is correct
		if (!GetWindowPlacement(hwndFrame, &wndPlacement))
		{
			memset(&wndPlacement, 0, sizeof(WINDOWPLACEMENT));
			wndPlacement.length = sizeof(WINDOWPLACEMENT);
		}
		if (flag && (flag <= SW_MAX)) // validate flag
		{
			wndPlacement.showCmd = flag;
			iCmdShow = flag; /* SW_SHOW; */
		}
		else
		{
			wndPlacement.showCmd = iCmdShow; /* SW_SHOWNORMAL; */
		}
		wndPlacement.rcNormalPosition.left = x;
		wndPlacement.rcNormalPosition.top = y;
		wndPlacement.rcNormalPosition.right = x + iWidth;
		wndPlacement.rcNormalPosition.bottom = y + iHeight;
		SetWindowPlacement(hwndFrame, &wndPlacement);
	}

	return iCmdShow;
}

/*
	most of the code in the following function comes from Mozilla
*/
void XAP_Win32App::_setBidiOS(void)
{

	m_eBidiOS = XAP_App::BIDI_SUPPORT_NONE;
/*
	I have run into problems with the built-in win32 bidi support -- it is inconsistent
	It treats some fonts (i.e., the MS fonts) correctly, but some common Hebrew fonts
	it will not reorder. Consequently, I felt that the best solution would be to disable
	the win32 bidi altogether and treating it as a non-bidi system, but there does
	not seem to be a simple way of doing this

	I am going to have another shot at disabling the build in support
	for the main window, and leaving for the GUI only. The main
	changes are in gr_Win32Graphics class. Tomas, Jan 19th, 2003
*/
	const UT_UCS2Char araAin  = 0x0639;
	const UT_UCS2Char one     = 0x0031;

	int distanceArray[2];
	UT_UCS2Char glyphArray[2];
	UT_UCS2Char outStr[] = {0, 0};

	GCP_RESULTSW gcpResult;
	gcpResult.lStructSize = sizeof(GCP_RESULTS);
	gcpResult.lpOutString = (LPWSTR) outStr;     // Output string
	gcpResult.lpOrder = NULL;			// Ordering indices
	gcpResult.lpDx = distanceArray;     // Distances between character cells
	gcpResult.lpCaretPos = NULL;		// Caret positions
	gcpResult.lpClass = NULL;         // Character classifications
#ifdef __MINGW32__
	gcpResult.lpGlyphs = (UINT *) glyphArray;    // Character glyphs
#else	
	gcpResult.lpGlyphs = (unsigned short *) glyphArray;    // Character glyphs
#endif	
	gcpResult.nGlyphs = 2;              // Array size

	UT_UCS2Char inStr[] = {araAin, one};

	HDC displayDC = GetDC(NULL);

	if(!displayDC)
	{
		return;
	}

	if (GetCharacterPlacementW(displayDC, (LPCWSTR)inStr, 2, 0, &gcpResult, GCP_REORDER)
		&& (inStr[0] == outStr[1]) )
	{
		m_eBidiOS = XAP_App::BIDI_SUPPORT_GUI;
		UT_DEBUGMSG(("System has bidi and glyph shaping\n"));
	}
	else
	{
		const UT_UCSChar hebAlef = 0x05D0;
		inStr[0] = hebAlef;
		inStr[1] = one;
		if (GetCharacterPlacementW(displayDC, (LPCWSTR)inStr, 2, 0, &gcpResult, GCP_REORDER)
			&& (inStr[0] == outStr[1]) )
		{
			m_eBidiOS = XAP_App::BIDI_SUPPORT_GUI;
			UT_DEBUGMSG(("System has bidi\n"));
		}
	}

	ReleaseDC(NULL,displayDC);
}

const char * XAP_Win32App::getDefaultEncoding () const
{
	XAP_EncodingManager * pEncodingManager = XAP_EncodingManager::get_instance();
	return pEncodingManager->getNativeSystemEncodingName();
}
