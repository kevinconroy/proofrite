/* 
  Nullsoft "SuperPimp" Installation System - main.c - executable header main code

  Copyright (C) 1999-2001 Nullsoft, Inc.

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

  This source distribution includes portions of zlib. see zlib/zlib.h for 
  its license and so forth. Note that this license is also borrowed from zlib.
*/


#include <windows.h>
#include <commctrl.h>
#include "resource.h"
#include "util.h"
#include "fileform.h"
#include "state.h"
#include "ui.h"

#include "lang.h"

extern unsigned long CRC32(unsigned long crc, const unsigned char *buf, unsigned int len);

#if !defined(NSIS_CONFIG_VISIBLE_SUPPORT) && !defined(NSIS_CONFIG_SILENT_SUPPORT)
#error One of NSIS_CONFIG_SILENT_SUPPORT or NSIS_CONFIG_VISIBLE_SUPPORT must be defined.
#endif
#ifdef NSIS_COMPRESS_WHOLE
extern HANDLE dbd_hFile;
#endif
#ifdef NSIS_CONFIG_CRC_SUPPORT
static const char *g_crcinvalid=_LANG_INVALIDCRC;
#else
static const char *g_crcinvalid=_LANG_INVALIDINST;
#endif

#ifdef NSIS_CONFIG_UNINSTALL_SUPPORT
static const char *g_errorcopyinginstall=_LANG_UNINSTINITERROR;
#endif

char g_caption[NSIS_MAX_STRLEN*2];
int g_filehdrsize;
HWND g_hwnd;

static int m_length;
static int m_pos;

#ifdef NSIS_CONFIG_VISIBLE_SUPPORT
#ifdef NSIS_CONFIG_CRC_SUPPORT
static BOOL CALLBACK verProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  if (uMsg == WM_INITDIALOG) 
  {
    SetTimer(hwndDlg,1,250,NULL);
    uMsg = WM_TIMER;
  }
  if (uMsg == WM_TIMER)
  {
    static char bt[64];
    wsprintf(bt,_LANG_VERIFYINGINST,MulDiv(m_pos,100,m_length));

    SetWindowText(hwndDlg,bt);
    SetDlgItemText(hwndDlg,IDC_STR,bt);
  }
  return 0;
}
#endif//NSIS_CONFIG_CRC_SUPPORT
#endif//NSIS_CONFIG_VISIBLE_SUPPORT

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst,LPSTR lpszCmdParam, int nCmdShow)
{
  static int ret;
  static const char *m_Err;
#ifdef NSIS_CONFIG_CRC_SUPPORT
#ifdef NSIS_CONFIG_VISIBLE_SUPPORT
  static HWND hwnd;
#endif
  static int crc;
  static char no_crc;
  static char do_crc;
#endif//NSIS_CONFIG_CRC_SUPPORT
#if defined(NSIS_CONFIG_SILENT_SUPPORT) && defined(NSIS_CONFIG_VISIBLE_SUPPORT)
  static char silent;
#endif//NSIS_CONFIG_SILENT_SUPPORT && NSIS_CONFIG_VISIBLE_SUPPORT
  int left;

#ifdef NSIS_CONFIG_VISIBLE_SUPPORT
  unsigned int verify_time=GetTickCount()+1000;
#endif
  char *cmdline=state_command_line;
  char *realcmds;
  char seekchar=' ';

  InitCommonControls();
  lstrcpyn(state_command_line,GetCommandLine(),NSIS_MAX_STRLEN);

  if (*cmdline == '\"') seekchar = *cmdline++;

  while (*cmdline && *cmdline != seekchar) cmdline=CharNext(cmdline);
  if (*cmdline) cmdline=CharNext(cmdline);
  realcmds=cmdline;

  do
  {
#ifdef NSIS_CONFIG_CRC_SUPPORT
#endif//NSIS_CONFIG_CRC_SUPPORT
    while (*cmdline == ' ') cmdline=CharNext(cmdline);
    if (cmdline[0] != '/') break;
    cmdline++;
#if defined(NSIS_CONFIG_VISIBLE_SUPPORT) && defined(NSIS_CONFIG_SILENT_SUPPORT)
    if (cmdline[0] == 'S' && (cmdline[1] == ' ' || !cmdline[1]))
    {
      silent++;
      cmdline+=2;
    }
    else
#endif//NSIS_CONFIG_SILENT_SUPPORT && NSIS_CONFIG_VISIBLE_SUPPORT
#ifdef NSIS_CONFIG_CRC_SUPPORT
      if (cmdline[0] == 'N' &&
          cmdline[1] == 'C' &&
          cmdline[2] == 'R' &&
          cmdline[3] == 'C' &&
         (cmdline[4] == ' ' || !cmdline[4]))
      {
        no_crc++;
        cmdline+=4;
      }
      else 
#endif//NSIS_CONFIG_CRC_SUPPORT
    if (cmdline[0] == 'D' && cmdline[1] == '=')
    {
      cmdline[-2]=0; // keep this from being passed to uninstaller if necessary
      lstrcpy(state_install_directory,cmdline+2);
      cmdline+=lstrlen(cmdline);
    }
    else while (*cmdline && *cmdline != ' ') cmdline=CharNext(cmdline);
  }
  while (*cmdline);

  lstrcpy(g_caption,_LANG_GENERIC_ERROR);

  g_hInstance=GetModuleHandle(NULL);
  GetModuleFileName(g_hInstance,state_exe_directory,NSIS_MAX_STRLEN);

  g_db_hFile=myOpenFile(state_exe_directory,GENERIC_READ,OPEN_EXISTING);
  if (g_db_hFile==INVALID_HANDLE_VALUE)
  {
    m_Err = _LANG_CANTOPENSELF;
    goto end;
  }

  // make state_exe_directory point to dir, not full exe.
  
  trimslashtoend(state_exe_directory);

  left = m_length = GetFileSize(g_db_hFile,NULL);
  while (left > 0)
  {
    static char temp[512];
    DWORD l=left;
    if (l > 512) l=512;
    if (!ReadFile(g_db_hFile,temp,l,&l,NULL))
    {
      m_Err=g_crcinvalid;
#if defined(NSIS_CONFIG_CRC_SUPPORT) && defined(NSIS_CONFIG_VISIBLE_SUPPORT)
      if (hwnd) DestroyWindow(hwnd);
#endif//NSIS_CONFIG_CRC_SUPPORT
      goto end;
    }

    if (!g_filehdrsize)
    {
      int dbl;
      dbl=isheader((firstheader*)temp);
      if (dbl)
      {
        int a=*(int*)temp;
        g_filehdrsize=m_pos;
        if (dbl > left)
        {
          m_Err=g_crcinvalid;
          goto end;
        }
#if defined(NSIS_CONFIG_SILENT_SUPPORT) && defined(NSIS_CONFIG_VISIBLE_SUPPORT)
        if (a&FH_FLAGS_SILENT) silent++;
#endif//NSIS_CONFIG_SILENT_SUPPORT && NSIS_CONFIG_VISIBLE_SUPPORT

#ifdef NSIS_CONFIG_CRC_SUPPORT
        if (no_crc || !(a&FH_FLAGS_CRC))  break; // if first bit is not set, then no crc checking. 

        do_crc++;

#ifndef NSIS_CONFIG_CRC_ANAL
        left=dbl-4;
        // end crc checking at crc :) this means you can tack shit on the end and it'll still work.              
#else //!NSIS_CONFIG_CRC_ANAL
        left-=4;
#endif//NSIS_CONFIG_CRC_ANAL
        // this is in case the end part is < 512 bytes. 
        if (l > (DWORD)left) l=(DWORD)left;

#else//!NSIS_CONFIG_CRC_SUPPORT
        break;
#endif//!NSIS_CONFIG_CRC_SUPPORT
      }
    }
#ifdef NSIS_CONFIG_CRC_SUPPORT

#ifdef NSIS_CONFIG_VISIBLE_SUPPORT

#ifdef NSIS_CONFIG_SILENT_SUPPORT
    else if (!silent)
#endif//NSIS_CONFIG_SILENT_SUPPORT
    {
      if (hwnd)
      {
        static MSG msg;
        while (PeekMessage(&msg,NULL,0,0,PM_REMOVE)) DispatchMessage(&msg);
      }
      else if (GetTickCount() > verify_time) 
        hwnd=CreateDialog(g_hInstance,MAKEINTRESOURCE(IDD_VERIFY),GetDesktopWindow(),verProc);
    }
#endif//NSIS_CONFIG_VISIBLE_SUPPORT

#ifndef NSIS_CONFIG_CRC_ANAL
    if (left<m_length) 
#endif//NSIS_CONFIG_CRC_ANAL
      crc=CRC32(crc, temp, l);

#endif//NSIS_CONFIG_CRC_SUPPORT
    m_pos+=l;
    left -= l;
  }
#ifdef NSIS_CONFIG_VISIBLE_SUPPORT
#ifdef NSIS_CONFIG_CRC_SUPPORT
  if (hwnd) DestroyWindow(hwnd);
#endif//NSIS_CONFIG_CRC_SUPPORT
#endif//NSIS_CONFIG_VISIBLE_SUPPORT
  if (!g_filehdrsize) m_Err=g_crcinvalid;
  else 
  {
#ifdef NSIS_CONFIG_CRC_SUPPORT
    if (do_crc)
    {
      DWORD l;
      int fcrc;
      SetFilePointer(g_db_hFile,m_pos,NULL,FILE_BEGIN);
      if (!ReadFile(g_db_hFile,&fcrc,4,&l,NULL) || crc != fcrc)
      {
        m_Err=g_crcinvalid;
        goto end;
      }
    }
#endif//NSIS_CONFIG_CRC_SUPPORT
    SetFilePointer(g_db_hFile,g_filehdrsize,NULL,FILE_BEGIN);    

    if (loadHeaders()) m_Err=g_crcinvalid;
  }
  if (m_Err) goto end;

#ifdef NSIS_CONFIG_UNINSTALL_SUPPORT
  if (g_is_uninstaller)
  {
    if (cmdline[0] == '_' && cmdline[1] == '=' && cmdline[2])
    {
      cmdline[-1]=0;
      cmdline+=2;
      if (is_valid_instpath(cmdline))
      {
        lstrcpy(state_install_directory,cmdline);
        lstrcpy(state_output_directory,cmdline);
      }
      else
      {
        m_Err = g_errorcopyinginstall;
        goto end;
      }
    }
    else
    {
      int x,done=0;

      for (x = 0; x < 26; x ++)
      {
        static char s[]="A~NSISu_.exe";
        static char buf2[NSIS_MAX_STRLEN*2];
        static char ibuf[NSIS_MAX_STRLEN];
      
        buf2[0]='\"';
        GetTempPath(sizeof(buf2)-1,buf2+1);
        lstrcat(buf2,s);

        DeleteFile(buf2+1); // clean up after all the other ones if they are there
        
        if (!done)
        {
          // get current name
          int l=GetModuleFileName(g_hInstance,ibuf,sizeof(ibuf));
          // check if it is ?~NSISu_.exe - if so, fuck it
          if (!lstrcmpi(ibuf+l-(sizeof(s)-2),s+1)) break;

          // copy file
          if (CopyFile(ibuf,buf2+1,FALSE))
          {
            HANDLE hProc;
#ifdef NSIS_SUPPORT_MOVEONREBOOT
            MoveFileOnReboot(buf2+1,NULL);
#endif
            if (state_install_directory[0]) lstrcpy(ibuf,state_install_directory);
            else trimslashtoend(ibuf);
            if (!is_valid_instpath(ibuf)) break;
            done++;
            lstrcat(buf2,"\" ");
            lstrcat(buf2,realcmds);
            lstrcat(buf2," _=");
            lstrcat(buf2,ibuf);
            GetTempPath(sizeof(ibuf),ibuf);
            hProc=myCreateProcess(buf2,ibuf);
            if (hProc) CloseHandle(hProc);
            else m_Err = g_errorcopyinginstall;
          }
        }
        s[0]++;
      }
      if (!done) m_Err=g_errorcopyinginstall;
      goto end;      
    }
  }
#endif//NSIS_CONFIG_UNINSTALL_SUPPORT
#ifdef NSIS_CONFIG_VISIBLE_SUPPORT
#ifdef NSIS_CONFIG_SILENT_SUPPORT
  if (!g_inst_cmnheader->silent_install) g_inst_cmnheader->silent_install=silent;
#endif//NSIS_CONFIG_SILENT_SUPPORT
#endif//NSIS_CONFIG_VISIBLE_SUPPORT

  ret=ui_doinstall();

#ifdef NSIS_CONFIG_LOG
  log_write(1);
#endif//NSIS_CONFIG_LOG
end:
  if (g_db_hFile!=INVALID_HANDLE_VALUE) CloseHandle(g_db_hFile);
#ifdef NSIS_COMPRESS_WHOLE
  if (dbd_hFile!=INVALID_HANDLE_VALUE) CloseHandle(dbd_hFile);
#endif
  if (m_Err) MessageBox(NULL,m_Err,g_caption,MB_OK|MB_ICONSTOP);
  ExitProcess(ret);
}

