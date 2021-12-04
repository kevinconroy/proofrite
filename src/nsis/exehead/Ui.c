#include <windows.h>
#include <shlobj.h>
#include "resource.h"

#include "fileform.h"
#include "state.h"
#include "util.h"
#include "ui.h"
#include "exec.h"

#define LB_ICONWIDTH 20
#define LB_ICONHEIGHT 20

int g_quit_flag; // set when Quit has been called (meaning bail out ASAP)

#if NSIS_MAX_INST_TYPES >= 31 || NSIS_MAX_INST_TYPES < 1
#error invalid value for NSIS_MAX_INST_TYPES
#endif

char g_autoclose;
char g_noicon;
int progress_bar_pos, progress_bar_len;

HWND g_progresswnd;

static char g_tmp[4096];

// sent to the last child window to tell it that the install thread is done
#define WM_NOTIFY_INSTPROC_DONE (WM_USER+0x4)

// sent to the outer window to tell it to go to the next inner window
#define WM_NOTIFY_OUTER_NEXT (WM_USER+0x8)

// update message used by DirProc and SelProc for space display
#define WM_IN_UPDATEMSG (WM_USER+0xf)


#ifdef NSIS_CONFIG_VISIBLE_SUPPORT
static BOOL CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
static int CALLBACK WINAPI BrowseCallbackProc( HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
#ifdef NSIS_CONFIG_LICENSEPAGE
static BOOL CALLBACK LicenseProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
#endif
static BOOL CALLBACK DirProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
static BOOL CALLBACK SelProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
static BOOL CALLBACK InstProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
static BOOL CALLBACK UninstProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
#endif//NSIS_CONFIG_VISIBLE_SUPPORT

static DWORD WINAPI install_thread(LPVOID p);

HWND bgWnd_Init(HINSTANCE hInstance, char *title, int color1, int color2, int);

HWND insthwnd, insthwnd2,insthwndbutton;

void *g_inst_combinedheader;
section *g_inst_section;
entry *g_inst_entry;
#ifdef NSIS_CONFIG_UNINSTALL_SUPPORT
int g_is_uninstaller;
static int g_max_page=1;
static int g_page_offs=4;
#else
#define g_max_page 3
#define g_page_offs 0
#endif

static int m_page=-1,m_abort;
static HWND m_curwnd;
static int m_whichcfg;

#ifdef NSIS_CONFIG_LOG
static void build_g_logfile()
{
  lstrcpy(g_log_file,state_install_directory);
  addtrailingslash(g_log_file);
  lstrcat(g_log_file,"install.log");
}
#endif

#ifdef NSIS_CONFIG_VISIBLE_SUPPORT
static void fixchildfornoicon(HWND hwndDlg, HWND fix)
{
  RECT r;
  int h;
  GetWindowRect(fix,&r);
  h=r.bottom-r.top;
  r.left=r.right;
  ScreenToClient(hwndDlg,(LPPOINT)&r);
  SetWindowPos(fix,NULL,0,r.top,r.left,h,SWP_NOACTIVATE|SWP_NOZORDER);
}

static void handlesubicon(HWND hwndDlg)
{
  if (g_noicon)
  {
    ShowWindow(GetDlgItem(hwndDlg,IDC_ULICON),SW_HIDE);
    fixchildfornoicon(hwndDlg,GetDlgItem(hwndDlg,IDC_INTROTEXT));
    if (g_progresswnd) fixchildfornoicon(hwndDlg,g_progresswnd);
  }
}
#endif//NSIS_CONFIG_VISIBLE_SUPPORT


int ui_doinstall(void)
{
  g_noicon=g_inst_cmnheader->misc_flags&4;
  g_autoclose=g_inst_cmnheader->misc_flags&1;
#ifdef NSIS_CONFIG_UNINSTALL_SUPPORT
  if (!g_is_uninstaller)
  {
    g_max_page=3;
    g_page_offs=0;
#else
  {
#endif
    if (!is_valid_instpath(state_install_directory))
    {
      if (g_inst_header->install_reg_key_ptr>=0)
      {
        myRegGetStr((HKEY)g_inst_header->install_reg_rootkey,
          GetStringFromStringTab(g_inst_header->install_reg_key_ptr),
            GetStringFromStringTab(g_inst_header->install_reg_value_ptr),ps_tmpbuf);
        if (ps_tmpbuf[0])
			  {
          char *p=ps_tmpbuf;
          char *e;
          if (p[0]=='\"')
          {
            char *p2=CharNext(p);
            p=p2;
            while (*p2 && *p2 != '\"') p2=CharNext(p2);
            *p2=0;
          }
          // p is the path now, check for .exe extension

          e=p+lstrlen(p)-4;
          if (e > p)
          {
            // if filename ends in .exe, and is not a directory, remove the filename
            if (!lstrcmpi(e,".exe"))        // check extension
            {
              DWORD d;
              d=GetFileAttributes(p);
              if (d == (DWORD)-1 || !(d&FILE_ATTRIBUTE_DIRECTORY))
              {
                e=scanendslash(p);
                if (e>=p) *e=0;
              }
            }
          }

          lstrcpy(state_install_directory,p);
        }
      }
    }
    if (!is_valid_instpath(state_install_directory))
    {
      process_string_fromtab(state_install_directory,g_inst_header->install_directory_ptr);
    }

#ifdef NSIS_CONFIG_LOG
    if (g_inst_cmnheader->silent_install==2)
    {
      build_g_logfile();
      log_dolog=1;
    }
#endif
  }

  process_string_fromtab(g_caption,g_inst_cmnheader->caption_ptr);

#ifdef NSIS_CONFIG_VISIBLE_SUPPORT
#ifdef NSIS_CONFIG_SILENT_SUPPORT
  if (!g_inst_cmnheader->silent_install)
#endif//NSIS_CONFIG_SILENT_SUPPORT
  {
    HWND h=GetDesktopWindow();
#ifdef NSIS_SUPPORT_BGBG
    if (g_inst_cmnheader->bg_color1 != -1)
    {
      h=bgWnd_Init(g_hInstance,g_caption,g_inst_cmnheader->bg_color1,g_inst_cmnheader->bg_color2,g_inst_cmnheader->bg_textcolor);
    }
#endif//NSIS_SUPPORT_BGBG
#ifdef NSIS_SUPPORT_CODECALLBACKS
    g_hwnd=h;
    if (ExecuteCodeSegment(g_inst_entry,g_inst_cmnheader->code_onInit,NULL)) return 1;
    g_hwnd=NULL;
#endif//NSIS_SUPPORT_CODECALLBACKS
    return DialogBox(g_hInstance,MAKEINTRESOURCE(IDD_INST),h,DialogProc);
  }
#endif//NSIS_CONFIG_VISIBLE_SUPPORT
#ifdef NSIS_CONFIG_SILENT_SUPPORT
#ifdef NSIS_CONFIG_VISIBLE_SUPPORT
  else
#endif
  {
#ifdef NSIS_SUPPORT_CODECALLBACKS
    if (ExecuteCodeSegment(g_inst_entry,g_inst_cmnheader->code_onInit,NULL)) return 1;
#endif//NSIS_SUPPORT_CODECALLBACKS
    if (install_thread(NULL))
    {
#ifdef NSIS_SUPPORT_CODECALLBACKS
      if (!g_quit_flag) ExecuteCodeSegment(g_inst_entry,g_inst_cmnheader->code_onInstFailed,NULL);
#endif//NSIS_SUPPORT_CODECALLBACKS
      return 1;
    }
#ifdef NSIS_SUPPORT_CODECALLBACKS
    ExecuteCodeSegment(g_inst_entry,g_inst_cmnheader->code_onInstSuccess,NULL);
#endif//NSIS_SUPPORT_CODECALLBACKS
    return 0;
  }
#endif//NSIS_CONFIG_SILENT_SUPPORT
}


#ifdef NSIS_CONFIG_VISIBLE_SUPPORT
static int CALLBACK WINAPI BrowseCallbackProc( HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	if (uMsg==BFFM_INITIALIZED)
	{
		GetDlgItemText((HWND)lpData,IDC_DIR,g_tmp,sizeof(g_tmp));
		SendMessage(hwnd,BFFM_SETSELECTION,(WPARAM)1,(LPARAM)g_tmp);
	}
	return 0;
}


static BOOL CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  static HICON hIcon;
  if (uMsg == WM_DESTROY && hIcon) { DeleteObject(hIcon); hIcon=0; }
  if (uMsg == WM_INITDIALOG || uMsg == WM_NOTIFY_OUTER_NEXT)
  {
    int iscp=0,islp=0,isdp=0,ispotentiallydp=0;
    int delta=(uMsg == WM_NOTIFY_OUTER_NEXT)?wParam:0;
    int prev_page=m_page;
    static struct
    {
      char *id;
      DLGPROC proc;
    }
    windows[]=
    {
#ifdef NSIS_CONFIG_LICENSEPAGE
      {MAKEINTRESOURCE(IDD_LICENSE),LicenseProc},
#else
      {NULL,NULL},
#endif
#ifdef NSIS_CONFIG_COMPONENTPAGE
      {MAKEINTRESOURCE(IDD_SELCOM),SelProc},
#else
      {NULL,NULL},
#endif
      {MAKEINTRESOURCE(IDD_DIR),DirProc},
      {MAKEINTRESOURCE(IDD_INSTFILES),InstProc},
#ifdef NSIS_CONFIG_UNINSTALL_SUPPORT
      {MAKEINTRESOURCE(IDD_UNINST),UninstProc},
      {MAKEINTRESOURCE(IDD_INSTFILES),InstProc},
#endif
    };

    if (uMsg == WM_INITDIALOG)
    {
      g_hwnd=hwndDlg;
      SetDlgItemText(hwndDlg,IDC_VERSTR,GetStringFromStringTab(g_inst_cmnheader->branding_ptr));
      hIcon=LoadIcon(g_hInstance,MAKEINTRESOURCE(IDI_ICON2));
      SetClassLong(hwndDlg,GCL_HICON,(long)hIcon);
      SetDlgItemText(hwndDlg,IDCANCEL,GetStringFromStringTab(g_inst_cmnheader->cancelbutton_ptr));
#ifdef NSIS_CONFIG_UNINSTALL_SUPPORT
      if (!g_is_uninstaller)
#endif
        SetDlgItemText(hwndDlg,IDC_BACK,GetStringFromStringTab(g_inst_header->backbutton_ptr));
      ShowWindow(hwndDlg,SW_SHOW);
    }

#ifdef NSIS_CONFIG_UNINSTALL_SUPPORT
    if (g_is_uninstaller)
    {
      islp=(g_inst_uninstheader->uninstalltext_ptr>=0);
      iscp++;
    }
    else
#endif//NSIS_CONFIG_UNINSTALL_SUPPORT
    {
#ifdef NSIS_CONFIG_LICENSEPAGE
      if (g_inst_header->licensedata_ptr>=0) islp++;
#endif//NSIS_CONFIG_LICENSEPAGE
#ifdef NSIS_CONFIG_COMPONENTPAGE
      if (g_inst_header->componenttext_ptr>=0) iscp++;
#endif//NSIS_CONFIG_COMPONENTPAGE
      if (g_inst_header->text_ptr>=0) ispotentiallydp++;
      if (ispotentiallydp &&
          !((g_inst_cmnheader->misc_flags&2) &&
            is_valid_instpath(state_install_directory)
#ifdef NSIS_SUPPORT_CODECALLBACKS
            && !ExecuteCodeSegment(g_inst_entry,g_inst_header->code_onVerifyInstDir,NULL)
#endif//NSIS_SUPPORT_CODECALLBACKS
            )) isdp++;
    }

    if (m_page<=0) delta=1;
    do
    {
      int count=1;  // Number of pages to move by
#ifdef NSIS_SUPPORT_CODECALLBACKS
      // Call onNext|PrevPage for every not-definitely-disabled page
      if (ExecuteCodeSegment(g_inst_entry,delta>0?g_inst_cmnheader->code_onNextPage:g_inst_header->code_onPrevPage,NULL))
      {
        if (g_quit_flag)  // Quit instruction used?
          m_page=count=-1;
        // Mmm - relies on ps_tmpbuf still being set from the Abort command - safe?
        else if ((count = myatoi(ps_tmpbuf)) != 0)
          count /= (delta = (count>0?1:-1));
      }
#endif//NSIS_SUPPORT_CODECALLBACKS
      // Skip any definitely-disabled pages, then the required number of pages
      while ((m_page==0 && !islp) || (m_page==1 && !iscp) || (m_page==2 && !ispotentiallydp) || (--count>=0))
        m_page+=delta;
      // Skip any possibly-disabled pages
    } while ((m_page >= 0) && (m_page <= g_max_page) && (m_page==2 && !isdp));

#ifdef NSIS_SUPPORT_CODECALLBACKS
    if (m_page>g_max_page) ExecuteCodeSegment(g_inst_entry,g_inst_cmnheader->code_onInstSuccess,NULL);
#endif//NSIS_SUPPORT_CODECALLBACKS

    if (m_curwnd && (m_page!=prev_page))
    {
      DestroyWindow(m_curwnd);
      m_curwnd=0;
    }

    if (m_page < 0 || m_page > g_max_page)
    {
      EndDialog(hwndDlg,0);
    }
    else if (!m_curwnd)
    {
      HWND hwndtmp;
      SetDlgItemText(hwndDlg,IDOK,GetStringFromStringTab(
        (m_page == g_max_page) ? g_inst_cmnheader->closebutton_ptr :
#ifdef NSIS_CONFIG_UNINSTALL_SUPPORT
        g_is_uninstaller ? g_inst_uninstheader->uninstbutton_ptr :
#endif
#ifdef NSIS_CONFIG_LICENSEPAGE
        (m_page == 0) ? g_inst_header->licensebutton_ptr :
#endif
        (m_page == 2 || (m_page == 1 && !isdp)) ? g_inst_header->installbutton_ptr :
        g_inst_header->nextbutton_ptr
      ));
      lstrcpy(g_tmp,g_caption);
      process_string_fromtab(g_tmp+lstrlen(g_tmp),g_inst_cmnheader->subcaption_ptrs[m_page]);

      SetWindowText(hwndDlg,g_tmp);

      m_curwnd=CreateDialog(g_hInstance,windows[g_page_offs+m_page].id,hwndDlg,windows[g_page_offs+m_page].proc);
      if (m_curwnd)
      {
        RECT r;
        GetWindowRect(GetDlgItem(hwndDlg,IDC_CHILDRECT),&r);
        ScreenToClient(hwndDlg,(LPPOINT)&r);
        SetWindowPos(m_curwnd,0,r.left,r.top,0,0,SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOZORDER);
        ShowWindow(m_curwnd,SW_SHOWNA);
      }

      hwndtmp=GetDlgItem(hwndDlg,IDC_BACK);
#ifdef NSIS_CONFIG_UNINSTALL_SUPPORT
      ShowWindow(hwndtmp,(m_page&&!g_is_uninstaller)?SW_SHOWNA:SW_HIDE);
      if (!g_is_uninstaller)
#else
      ShowWindow(hwndtmp,m_page?SW_SHOWNA:SW_HIDE);
#endif
        EnableWindow(hwndtmp, (m_page==1&&islp) || (m_page==2&&(islp||iscp)));
      SetFocus(GetDlgItem(hwndDlg,IDOK));
    }
  }
  if (uMsg == WM_COMMAND)
  {
    int id=LOWORD(wParam);

    if (id == IDOK && m_curwnd)
    {
      SendMessage(hwndDlg,WM_NOTIFY_OUTER_NEXT,1,0);
    }
    if (
#ifdef NSIS_CONFIG_UNINSTALL_SUPPORT
      !g_is_uninstaller &&
#endif
      (id == IDC_BACK && m_curwnd && m_page>0))
    {
      EnableWindow(GetDlgItem(hwndDlg, IDOK), TRUE);
      SendMessage(hwndDlg,WM_NOTIFY_OUTER_NEXT,-1,0);
    }
    if (id == IDCANCEL)
    {
      if (m_abort)
      {
#ifdef NSIS_SUPPORT_CODECALLBACKS
        ExecuteCodeSegment(g_inst_entry,g_inst_cmnheader->code_onInstFailed,NULL);
#endif//NSIS_SUPPORT_CODECALLBACKS
        EndDialog(hwndDlg,2);
      }
      else
      {
#ifdef NSIS_SUPPORT_CODECALLBACKS
        if (!ExecuteCodeSegment(g_inst_entry,g_inst_cmnheader->code_onUserAbort,NULL))
#endif//NSIS_SUPPORT_CODECALLBACKS
        {
          EndDialog(hwndDlg,1);
        }
      }
    }
  }
  if (uMsg == WM_CLOSE)
  {
    if (!IsWindowEnabled(GetDlgItem(hwndDlg,IDCANCEL)) && IsWindowEnabled(GetDlgItem(hwndDlg,IDOK)))
      SendMessage(hwndDlg,WM_COMMAND,IDOK,0);
  }
  return 0;
}


#ifdef NSIS_CONFIG_LICENSEPAGE
static BOOL CALLBACK LicenseProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  if (uMsg == WM_INITDIALOG)
  {
    handlesubicon(hwndDlg);
    SetDlgItemText(hwndDlg,IDC_EDIT1,GetStringFromStringTab(g_inst_header->licensedata_ptr));
    SetDlgItemText(hwndDlg,IDC_INTROTEXT,GetStringFromStringTab(g_inst_header->licensetext_ptr));
  }
  if (uMsg == WM_CLOSE) SendMessage(GetParent(hwndDlg),WM_CLOSE,0,0);
  return 0;
}
#endif

#ifdef NSIS_CONFIG_UNINSTALL_SUPPORT
static BOOL CALLBACK UninstProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  if (uMsg == WM_INITDIALOG)
  {
    handlesubicon(hwndDlg);
    SetDlgItemText(hwndDlg,IDC_UNINSTFROM,GetStringFromStringTab(g_inst_uninstheader->uninstalltext2_ptr));
    SetDlgItemText(hwndDlg,IDC_INTROTEXT,GetStringFromStringTab(g_inst_uninstheader->uninstalltext_ptr));
    SetDlgItemText(hwndDlg,IDC_EDIT1,state_install_directory);
  }
  return 0;
}
#endif


static void inttosizestr(int kb, char *str)
{
  while (*str) str++;
  if (kb < 1024) wsprintf(str,"%dKB",kb);
  else if (kb < 1024*1024) wsprintf(str,"%d.%dMB",kb>>10,((kb*10)>>10)%10);
  else wsprintf(str,"%d.%dGB%s",kb>>20,((kb*10)>>20)%10,(GetVersion()&0x80000000) ? "+":"");
}

static BOOL CALLBACK DirProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  if (uMsg == WM_DESTROY)
  {
    GetDlgItemText(hwndDlg,IDC_DIR,state_install_directory,NSIS_MAX_STRLEN);
#ifdef NSIS_CONFIG_LOG
    build_g_logfile();
    log_dolog = !!IsDlgButtonChecked(hwndDlg,IDC_CHECK1);
#endif
  }
  if (uMsg == WM_INITDIALOG)
  {
    handlesubicon(hwndDlg);
#ifdef NSIS_CONFIG_LOG
    if (GetAsyncKeyState(VK_SHIFT)&0x8000)
    {
      HWND h=GetDlgItem(hwndDlg,IDC_CHECK1);
      SetWindowText(h,"Log install process");
      ShowWindow(h,SW_SHOWNA);
    }
#endif
    SetDlgItemText(hwndDlg,IDC_DIR,state_install_directory);
    SetDlgItemText(hwndDlg,IDC_INTROTEXT,GetStringFromStringTab(g_inst_header->text_ptr));
    SetDlgItemText(hwndDlg,IDC_BROWSE,GetStringFromStringTab(g_inst_header->browse_ptr));
    SetDlgItemText(hwndDlg,IDC_SELDIRTEXT,GetStringFromStringTab(g_inst_header->dirsubtext_ptr));
    SendMessage(hwndDlg,WM_IN_UPDATEMSG,0,0);
  }
  if (uMsg == WM_COMMAND)
  {
    int id=LOWORD(wParam);
    if (id == IDC_DIR && HIWORD(wParam) == EN_CHANGE)
    {
      SendMessage(hwndDlg,WM_IN_UPDATEMSG,0,0);
    }
		if (id == IDC_BROWSE)
		{
			char name[256];
      char str[256];
      BROWSEINFO bi={0,};
			ITEMIDLIST *idlist;
			GetDlgItemText(hwndDlg,IDC_DIR,name,256);
			GetDlgItemText(hwndDlg,IDC_SELDIRTEXT,str,256);
			bi.hwndOwner = hwndDlg;
			bi.pszDisplayName = name;
			bi.lpfn=BrowseCallbackProc;
			bi.lParam=(LPARAM)hwndDlg;
			bi.lpszTitle = str;
			bi.ulFlags = BIF_RETURNONLYFSDIRS;
			idlist = SHBrowseForFolder( &bi );
			if (idlist)
      {
        const char *post_str;
        const char *p;
        IMalloc *m;
				SHGetPathFromIDList( idlist, name );
        SHGetMalloc(&m);
        if (m)
        {
          m->lpVtbl->Free(m,idlist);
          m->lpVtbl->Release(m);
        }
        post_str=GetStringFromStringTab(g_inst_header->install_directory_ptr);

        p=scanendslash(post_str);
        if (p >= post_str && *++p)
        {
          post_str=p;
          p=name+lstrlen(name)-lstrlen(post_str);
          if (p <= name || *CharPrev(name,p)!='\\' || lstrcmpi(p,post_str))
          {
            addtrailingslash(name);
            lstrcat(name,post_str);
          }
        }

				SetDlgItemText(hwndDlg,IDC_DIR,name);
        uMsg = WM_IN_UPDATEMSG;
			}
		}
  }
  if (uMsg == WM_IN_UPDATEMSG)
  {
    static char s[NSIS_MAX_STRLEN];
    int is_valid_path;
    int x;
    int total=0, available=-1;
    DWORD spc,bps,fc,tc;
    GetDlgItemText(hwndDlg,IDC_DIR,state_install_directory,NSIS_MAX_STRLEN);
    is_valid_path=is_valid_instpath(state_install_directory);

    mini_memcpy(s,state_install_directory,NSIS_MAX_STRLEN);
    s[sizeof(s)-1]=0;
    if (s[1] == ':') s[3]=0;
    else if (s[0] == '\\' && s[1] == '\\') // \\ path
    {
      addtrailingslash(s);
    }

    if (GetDiskFreeSpace(s,&spc,&bps,&fc,&tc))
    {
      DWORD r;
      DWORD v=0x7fffffff;
      r=bps*spc*(fc>>10);
      if (!r) r=(bps*spc*fc)>>10;
      if (r > v) r=v;
      available=(int)r;
    }
    for (x = 0; x < g_inst_header->num_sections; x ++)
    {
#ifdef NSIS_CONFIG_COMPONENTPAGE
      if (g_inst_section[x].default_state&DFS_SET)
#endif
       total+=g_inst_section[x].size_kb;
    }
    lstrcpy(s,GetStringFromStringTab(g_inst_header->spacerequired_ptr));
    inttosizestr(total,s);
    SetDlgItemText(hwndDlg,IDC_SPACEREQUIRED,s);
    if (available != -1)
    {
      lstrcpy(s,GetStringFromStringTab(g_inst_header->spaceavailable_ptr));
      inttosizestr(available,s);
      SetDlgItemText(hwndDlg,IDC_SPACEAVAILABLE,s);
    }
    else
      SetDlgItemText(hwndDlg,IDC_SPACEAVAILABLE,"");

    EnableWindow(GetDlgItem(GetParent(hwndDlg),IDOK),
      is_valid_path && (available >= total || available == -1)
#ifdef NSIS_SUPPORT_CODECALLBACKS
      && !ExecuteCodeSegment(g_inst_entry,g_inst_header->code_onVerifyInstDir,NULL)
#endif
      );
  }
  return 0;
}

#ifdef NSIS_CONFIG_COMPONENTPAGE
static HBITMAP hBMcheck[2];

int m_num_insttypes;

static BOOL CALLBACK SelProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  HWND hwndCombo1 = GetDlgItem(hwndDlg,IDC_COMBO1);
  HWND hwndList1 = GetDlgItem(hwndDlg,IDC_LIST1);
  if (uMsg == WM_INITDIALOG)
  {
    int x;
    int a=0;
    handlesubicon(hwndDlg);
    hBMcheck[0]=LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
    hBMcheck[1]=LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_BITMAP2));
    SetDlgItemText(hwndDlg,IDC_INTROTEXT,GetStringFromStringTab(g_inst_header->componenttext_ptr));
    SetDlgItemText(hwndDlg,IDC_TEXT1,GetStringFromStringTab(g_inst_header->componentsubtext_ptr[0]));
    SetDlgItemText(hwndDlg,IDC_TEXT2,GetStringFromStringTab(g_inst_header->componentsubtext_ptr[1]));
    if (g_inst_header->install_types_ptr[0]<0)
    {
      ShowWindow(hwndCombo1,SW_HIDE);
    }
    else
    {
      for (m_num_insttypes = 0; m_num_insttypes < NSIS_MAX_INST_TYPES && 
        g_inst_header->install_types_ptr[m_num_insttypes]>=0; m_num_insttypes ++)
      {
        SendMessage(hwndCombo1,CB_ADDSTRING,0,(LPARAM)GetStringFromStringTab(g_inst_header->install_types_ptr[m_num_insttypes]));
      }
      if (g_inst_header->no_custom_instmode_flag!=1) SendMessage(hwndCombo1,CB_ADDSTRING,0,(LPARAM)GetStringFromStringTab(g_inst_header->custom_ptr));
      SendMessage(hwndCombo1,CB_SETCURSEL,m_whichcfg,0);
    }

    for (x = 0; x < g_inst_header->num_sections; x ++)
    {
      if (g_inst_section[x].name_ptr>=0)
      {
        int p;
        process_string_fromtab(ps_tmpbuf,g_inst_section[x].name_ptr);
        p=SendMessage(hwndList1,LB_ADDSTRING,0,(LPARAM)ps_tmpbuf);

        if (m_num_insttypes && m_whichcfg != m_num_insttypes && !(g_inst_section[x].default_state&DFS_RO))
        {
          if ((g_inst_section[x].default_state>>m_whichcfg) & 1)
            g_inst_section[x].default_state|=DFS_SET;
          else
            g_inst_section[x].default_state&=~DFS_SET;
        }

        SendMessage(hwndList1,LB_SETITEMDATA,p,x);

        if (g_inst_section[x].default_state & DFS_SET)
          SendMessage(hwndList1,LB_SETSEL,TRUE,p);
      }
    }
    SendDlgItemMessage(hwndDlg,IDC_LIST1,WM_VSCROLL,SB_TOP,0);

    SendMessage(hwndDlg,WM_IN_UPDATEMSG,0,0);
  }
  if (uMsg == WM_COMMAND)
  {
    int r,a,x;
    int id=LOWORD(wParam),code=HIWORD(wParam);
    if (id == IDC_LIST1 && code==LBN_SELCHANGE)
    {
      // check to see which install type we are
      for (r = 0; r < m_num_insttypes; r ++)
      {
        for (a = x = 0; x < g_inst_header->num_sections; x ++)
        {
          if (g_inst_section[x].name_ptr>=0)
          {
            if (GetStringFromStringTab(g_inst_section[x].name_ptr)[0] != '-')
            {
              if (g_inst_header->no_custom_instmode_flag==1) 
                SendMessage(hwndList1,LB_SETSEL,(g_inst_section[x].default_state>>m_whichcfg)&1,a);
              else if (!(g_inst_section[x].default_state&DFS_RO))
                if (!(g_inst_section[x].default_state&(1<<r)) != !SendMessage(hwndList1,LB_GETSEL,a,0)) break;
            }
            a++;
          }
        }
        if (x == g_inst_header->num_sections) break;
      }

      if (!g_inst_header->no_custom_instmode_flag)
      {
        SendMessage(hwndCombo1,CB_SETCURSEL,r,0);
        m_whichcfg=r;
        uMsg=WM_IN_UPDATEMSG;
      }

      for (a = x = 0; x < g_inst_header->num_sections; x ++)
      {
        if (g_inst_section[x].name_ptr>=0)
        {
          if (!(g_inst_section[x].default_state&DFS_RO))
          {
            if (SendDlgItemMessage(hwndDlg,IDC_LIST1,LB_GETSEL,a,0))
              g_inst_section[x].default_state|=DFS_SET;
            else
              g_inst_section[x].default_state&=~DFS_SET;
          }
          a++;
        }
      }    
#if defined(NSIS_SUPPORT_CODECALLBACKS) && defined(NSIS_CONFIG_COMPONENTPAGE)
      {
        extern HWND g_lbSectionHack;
        g_lbSectionHack=hwndList1;
        ExecuteCodeSegment(g_inst_entry,g_inst_header->code_onSelChange,NULL);
        g_lbSectionHack=0;
      }
#endif//NSIS_SUPPORT_CODECALLBACKS && NSIS_CONFIG_COMPONENTPAGE
    }
    if (id == IDC_COMBO1 && code==CBN_SELCHANGE)
    {
      int t=SendMessage(hwndCombo1,CB_GETCURSEL,0,0);
      if (t != CB_ERR)
      {
        m_whichcfg=t;
        if (m_whichcfg != m_num_insttypes)
        {
          int x,a;
          for (x = a = 0; x < g_inst_header->num_sections; x ++)
          {
            if (g_inst_section[x].name_ptr>=0)
            {
              if (!(g_inst_section[x].default_state & DFS_RO))
              {
                int n=(g_inst_section[x].default_state & (1<<m_whichcfg));
                if (n) g_inst_section[x].default_state|=DFS_SET;
                else g_inst_section[x].default_state&=~DFS_SET;

                SendMessage(hwndList1,LB_SETSEL,n,a);
              }
              a++;
            }
          }
          SendMessage(hwndList1,WM_VSCROLL,SB_TOP,0);
        }
        uMsg=WM_IN_UPDATEMSG;
      }
    }
  }
  if (uMsg == WM_DESTROY)
  {
    DeleteObject(hBMcheck[0]);
    DeleteObject(hBMcheck[1]);
  }
  if (uMsg == WM_IN_UPDATEMSG)
  {
    int x,total;
    char s[128];
    if (g_inst_header->no_custom_instmode_flag==2)
    {
      int c=(m_whichcfg == m_num_insttypes && m_num_insttypes)<<3;// SW_SHOWNA=8, SW_HIDE=0
      ShowWindow(hwndList1,c);
      ShowWindow(GetDlgItem(hwndDlg,IDC_TEXT2),c);
    }

    for (total=x=0; x < g_inst_header->num_sections; x ++)
    {
      if (g_inst_section[x].default_state&DFS_SET)
        total+=g_inst_section[x].size_kb;
    }
    lstrcpy(s,GetStringFromStringTab(g_inst_header->spacerequired_ptr));
    inttosizestr(total,s);
    SetDlgItemText(hwndDlg,IDC_SPACEREQUIRED,s);
  }
  if (uMsg == WM_MEASUREITEM)
  {
    LPMEASUREITEMSTRUCT lpmis = (LPMEASUREITEMSTRUCT) lParam;
    char text[64];

    SendDlgItemMessage(hwndDlg,IDC_LIST1,LB_GETTEXT,lpmis->itemID,(LPARAM)text);
    lpmis->itemHeight = (text[0]=='-')?(text[1]?17:5):LB_ICONHEIGHT;
    return TRUE;
  }
  if (uMsg == WM_CTLCOLORLISTBOX)
  {
    SetTextColor((HDC)wParam,GetNearestColor((HDC)wParam,RGB(0,0,0)));
    SetBkColor((HDC)wParam,RGB(255,255,255));
    return (int)GetStockObject(WHITE_BRUSH);
  }
  if (uMsg == WM_DRAWITEM)
  {
    LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT) lParam;

    if (lpdis->itemID != -1)
    {
      if (lpdis->itemAction == ODA_SELECT || lpdis->itemAction == ODA_DRAWENTIRE)
      {
        HBITMAP oldbm;
        HDC memdc;

        SendMessage(lpdis->hwndItem, LB_GETTEXT, lpdis->itemID, (LPARAM) g_tmp);

        if (g_tmp[0]=='-')
        {
          HPEN oldpen;
          HPEN pen;
          int w=(lpdis->rcItem.right-lpdis->rcItem.left)/8;
          int y=lpdis->rcItem.top/2+lpdis->rcItem.bottom/2;
          pen=CreatePen(PS_SOLID,0,RGB(192,192,192));
          oldpen=SelectObject(lpdis->hDC,pen);
          MoveToEx(lpdis->hDC,lpdis->rcItem.left+w,y,NULL);
          LineTo(lpdis->hDC,lpdis->rcItem.right-w,y);
          SelectObject(lpdis->hDC,oldpen);
          DeleteObject(pen);

          if (g_tmp[1])
          {
            RECT r=lpdis->rcItem;
            COLORREF oldc=GetTextColor(lpdis->hDC);
            SetTextColor(lpdis->hDC,RGB(192,192,192));
            DrawText(lpdis->hDC,g_tmp+1,-1,&r,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
            SetTextColor(lpdis->hDC,oldc);
          }
        }
        else
        {
          int idx;
          RECT r=lpdis->rcItem;
          r.left+=LB_ICONWIDTH+2;
          DrawText(lpdis->hDC,g_tmp,-1,&r,DT_VCENTER|DT_LEFT|DT_SINGLELINE);
          memdc=CreateCompatibleDC(lpdis->hDC);
         
          if (g_inst_section[lpdis->itemData].default_state&DFS_RO)
            idx=!(g_inst_section[lpdis->itemData].default_state&DFS_SET);
          else
            idx=!(lpdis->itemState & ODS_SELECTED);
         
          oldbm=SelectObject(memdc,hBMcheck[idx]);
          BitBlt(lpdis->hDC,lpdis->rcItem.left,lpdis->rcItem.top,LB_ICONWIDTH,LB_ICONHEIGHT,memdc,0,0,SRCCOPY);
          SelectObject(memdc,oldbm);
          DeleteObject(memdc);
        }
      }
    }
    return TRUE;
  }
  return 0;
}
#endif//NSIS_CONFIG_COMPONENTPAGE

#endif//NSIS_CONFIG_VISIBLE_SUPPORT

int ui_st_updateflag=0x3;
static int ui_st_scnt;

void update_status_text(const char *text1, const char *text2)
{
  if (insthwnd)
  {
    if (lstrlen(text1)+lstrlen(text2) >= sizeof(ps_tmpbuf)) return;

    lstrcpy(ps_tmpbuf,text1);
    lstrcat(ps_tmpbuf,text2);
    if ((ui_st_updateflag&1))
    {
      SendMessage(insthwnd,LB_ADDSTRING,(WPARAM)0,(LPARAM)ps_tmpbuf);
      if (IsWindowVisible(insthwnd) && --ui_st_scnt<0)
      {
        ui_st_scnt=7; // this a hack for the win9x smoothscroll crap.
        SendMessage(insthwnd,WM_VSCROLL,SB_BOTTOM,0);
      }
    }
    if ((ui_st_updateflag&2)) SetWindowText(insthwnd2,ps_tmpbuf);
  }
}


static DWORD WINAPI install_thread(LPVOID p)
{
  HWND hwndDlg=(HWND)p;
#ifdef NSIS_CONFIG_UNINSTALL_SUPPORT
  if (g_is_uninstaller)
  {
    if (ExecuteCodeSegment(g_inst_entry,g_inst_uninstheader->code,g_progresswnd)) m_abort++;
  }
  else
  {
#endif
    int m_inst_sec=0;
    while (m_inst_sec<g_inst_header->num_sections && !m_abort)
    {
#ifdef NSIS_CONFIG_COMPONENTPAGE
      if (g_inst_section[m_inst_sec].default_state&DFS_SET
#ifdef NSIS_CONFIG_SILENT_SUPPORT
        || g_inst_cmnheader->silent_install
#endif//NSIS_CONFIG_SILENT_SUPPORT
        )
#endif
      {
        log_printf2("Section: \"%s\"",GetStringFromStringTab(g_inst_section[m_inst_sec].name_ptr));
        if (ExecuteCodeSegment(g_inst_entry,g_inst_section[m_inst_sec].code,g_progresswnd)) m_abort++;
      }
#ifdef NSIS_CONFIG_COMPONENTPAGE
      else
      {
        log_printf2("Skipping section: \"%s\"",GetStringFromStringTab(g_inst_section[m_inst_sec].name_ptr));
      }
#endif
      m_inst_sec++;
    }
#ifdef NSIS_CONFIG_UNINSTALL_SUPPORT
  }
#endif
  if (hwndDlg) SendMessage(hwndDlg,WM_NOTIFY_INSTPROC_DONE,m_abort,0);
  return m_abort;
}

#ifdef NSIS_CONFIG_VISIBLE_SUPPORT
static BOOL CALLBACK InstProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  static HBRUSH hBrush;
  static int lb_bg,lb_fg;
  if (uMsg == WM_DESTROY && hBrush) DeleteObject(hBrush);
  if (uMsg == WM_INITDIALOG)
  {
    DWORD id;
    HWND hwnd;
    int num=0;
    int x=0;
    LOGBRUSH lb;
    lb.lbStyle=BS_SOLID;

    insthwndbutton=GetDlgItem(hwndDlg,IDC_SHOWDETAILS);
    insthwnd2=GetDlgItem(hwndDlg,IDC_INTROTEXT);
    insthwnd=GetDlgItem(hwndDlg,IDC_LIST1);
#ifdef NSIS_CONFIG_UNINSTALL_SUPPORT
    if (g_is_uninstaller)
    {
      num=g_inst_uninstheader->code_size;
    }
    else
#endif
    {
      log_printf3("New install of \"%s\" to \"%s\"",GetStringFromStringTab(g_inst_cmnheader->name_ptr),state_install_directory);
      for (; x < g_inst_header->num_sections; x ++)
      {
#ifdef NSIS_CONFIG_COMPONENTPAGE
        if (g_inst_section[x].default_state&DFS_SET)
#endif
          num+=g_inst_section[x].code_size;
      }
    }
    lb.lbColor=lb_bg=g_inst_cmnheader->lb_bg;
    lb_fg=g_inst_cmnheader->lb_fg;
    SetWindowText(insthwndbutton,GetStringFromStringTab(g_inst_cmnheader->showdetailsbutton_ptr));
    if (g_inst_cmnheader->show_details)
    {
      ShowWindow(insthwndbutton,SW_HIDE);
      if (g_inst_cmnheader->show_details != 2) ShowWindow(insthwnd,SW_SHOWNA);
      else insthwndbutton=NULL;
    }
    progress_bar_len=num;

    g_progresswnd=GetDlgItem(hwndDlg,IDC_PROGRESS1+(g_inst_cmnheader->progress_flags&1));
    ShowWindow(g_progresswnd,SW_SHOWNA);
    SendMessage(g_progresswnd,PBM_SETRANGE,0,MAKELPARAM(0,30000));
    SendMessage(g_progresswnd,PBM_SETPOS,0,0);
    if (lb_fg != -1)
    {
      if (g_inst_cmnheader->progress_flags&2)
      {
#ifdef PBM_SETBARCOLOR
        SendMessage(g_progresswnd,PBM_SETBARCOLOR,0,lb_fg);
#endif
#ifdef PBM_SETBKCOLOR
        SendMessage(g_progresswnd,PBM_SETBKCOLOR,0,lb_bg);
#endif
      }
      hBrush=CreateBrushIndirect(&lb);
    }
    handlesubicon(hwndDlg);

    hwnd=GetParent(hwndDlg);
    EnableWindow(GetDlgItem(hwnd,IDOK),0);
    EnableWindow(GetDlgItem(hwnd,IDCANCEL),0);

    CloseHandle(CreateThread(NULL,0,install_thread,(LPVOID)hwndDlg,0,&id));
  }
  if (uMsg == WM_CTLCOLORLISTBOX && lb_fg != -1)
  {
    SetTextColor((HDC)wParam,GetNearestColor((HDC)wParam,lb_fg));
    SetBkColor((HDC)wParam,lb_bg);
    return (int)hBrush;
  }
  if (uMsg == WM_COMMAND && LOWORD(wParam) == IDC_SHOWDETAILS)
  {
    ShowWindow(GetDlgItem(hwndDlg,IDC_SHOWDETAILS),SW_HIDE);
    SendMessage(insthwnd,WM_VSCROLL,SB_BOTTOM,0);
    ShowWindow(insthwnd,SW_SHOWNA);
  }
  if (uMsg == WM_NOTIFY_INSTPROC_DONE)
  {
    if (g_quit_flag) EndDialog(GetParent(hwndDlg),1);
    else if (!wParam)
    {
      HWND h2=GetParent(hwndDlg);
      HWND h=GetDlgItem(h2,IDOK);
      EnableWindow(h,1);
      if (!g_autoclose)
      {
        ShowWindow(g_hwnd,SW_SHOWNA);
        lstrcpy(g_tmp,g_caption);
        process_string_fromtab(g_tmp+lstrlen(g_caption),g_inst_cmnheader->subcaption_ptrs[g_max_page+1]);
        ui_st_scnt=0;
        update_status_text(GetStringFromStringTab(g_inst_cmnheader->completed_ptr),"");
        SetWindowText(h2,g_tmp);
        SetFocus(h);
      }
      else
      {
        SendMessage(GetParent(hwndDlg),WM_NOTIFY_OUTER_NEXT,1,0);
      }
    }
    else
    {
      HWND h=GetDlgItem(GetParent(hwndDlg),IDCANCEL);
      EnableWindow(h,1);
      SetFocus(h);
    }
  }
  return 0;
}
#endif//NSIS_CONFIG_VISIBLE_SUPPORT
