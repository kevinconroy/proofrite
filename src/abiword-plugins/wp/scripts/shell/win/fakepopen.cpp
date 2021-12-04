/*
 * Sorta a popen for Windows, except intead of FILE *
 * returns a PIPE * that has HANDLEs for childs stdin/stdout/stderr
 */

#include "fakepopen.h"

#include <string.h>

#include "ut_string_class.h"
#include "ut_debugmsg.h"

// queries OS version, returns true if NT or false otherwise (9x)
static inline bool isNT(void)
{
	OSVERSIONINFO osvi;
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	if (GetVersionEx(&osvi))
		return (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT)?true:false;
	else
		return false; // maybe true? we don't really know do we
}


// spawn specified command and inherit handles [stdout]
static bool CreateChildProcess(char * appName, char *cmdline, PROCESS_INFORMATION *procInfo,
		HANDLE hChildStdIn, HANDLE hChildStdOut, HANDLE hChildStdErr, WORD showWnd=0)
{
//	PROCESS_INFORMATION procInfo; 
	STARTUPINFO startInfo; 

	//initialize structures used to return info
	ZeroMemory( procInfo, sizeof(PROCESS_INFORMATION) ); 
	ZeroMemory( &startInfo, sizeof(STARTUPINFO) ); 
	startInfo.cb = sizeof(STARTUPINFO); 
      startInfo.dwFlags = STARTF_USESTDHANDLES;
	if (showWnd) startInfo.dwFlags |= STARTF_USESHOWWINDOW;
	startInfo.wShowWindow = showWnd;  /* eg SW_HIDE */

      startInfo.hStdOutput = hChildStdOut;
      startInfo.hStdInput  = hChildStdIn;
      startInfo.hStdError  = hChildStdErr;

	// Create the child process. 
	return (CreateProcess(
			appName,    // application module to execute
			cmdline,    // command line 
			NULL,       // process security attributes 
			NULL,       // primary thread security attributes 
			TRUE,       // handles are inherited  ***
			0,          // creation flags 
			NULL,       // use parent's environment 
			NULL,       // use parent's current directory 
			&startInfo, // STARTUPINFO pointer 
			procInfo   // receives PROCESS_INFORMATION 
	) != 0);
} 

static bool getPipe(HANDLE &hChild, HANDLE &hParent, bool modeR=false)
{
	HANDLE hChildNonInherit; 
 
	SECURITY_ATTRIBUTES saAttr; 
 
	// Set the bInheritHandle flag so pipe handles are inherited. 
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES); 
	saAttr.bInheritHandle = TRUE; 
	saAttr.lpSecurityDescriptor = NULL; 
 
	// Create a pipe for the child process.
	{
		BOOL ok;
		if (modeR)
			ok = CreatePipe(&hChild, &hChildNonInherit, &saAttr, 0);
		else
			ok = CreatePipe(&hChildNonInherit, &hChild, &saAttr, 0);
		if (!ok)
		{
			UT_DEBUGMSG(("KJD: pipe creation failed\n"));
			return false;
		}
	}

	// Create noninheritable handle and close the inheritable handle. 
	if (DuplicateHandle(GetCurrentProcess(), hChildNonInherit,
		GetCurrentProcess(), &hParent , 0,
		FALSE, DUPLICATE_SAME_ACCESS) == 0)
	{
		UT_DEBUGMSG(("KJD: DuplicateHandle failed\n"));
		CloseHandle(hChildNonInherit);
		CloseHandle(hChild);
		return INVALID_HANDLE_VALUE;
	}
	CloseHandle(hChildNonInherit);
	return true;
}


// Win32 popen-ish read mode for spawned process, ie returns HANDLE to child's stdout/in/err
// Only those Windows programs that actually write to standard output will work as expected.
PIPE * popen(char *command, const char *mode)
{ 
	HANDLE hChildStdoutWr, hChildStdoutRdDup,
	       hChildStderrWr, hChildStderrRdDup,
	       hChildStdinRd,  hChildStdinWrDup; 
	bool fSuccess;

	PIPE *p = new PIPE;
	if (p == NULL) return NULL;
	ZeroMemory(p, sizeof(PIPE));

	// determine mode
	if (strchr(mode, '+'))
		p->mode = FAKEPOPEN_MODE_READ | FAKEPOPEN_MODE_WRITE;
	else
		if (strchr(mode, 'w'))
			p->mode = FAKEPOPEN_MODE_WRITE;
		else
			p->mode = FAKEPOPEN_MODE_READ;

	// create pipes
	if (!getPipe(hChildStdoutWr, hChildStdoutRdDup))
	{
		delete p;
		return NULL;
	}
 
	if (!getPipe(hChildStderrWr, hChildStderrRdDup))
	{
		CloseHandle(hChildStdoutWr);
		CloseHandle(hChildStdoutRdDup);
		delete p;
		return NULL;
	}
 
	if (!getPipe(hChildStdinRd, hChildStdinWrDup, true))
	{
		CloseHandle(hChildStderrWr);
		CloseHandle(hChildStderrRdDup);
		CloseHandle(hChildStdoutWr);
		CloseHandle(hChildStdoutRdDup);
		delete p;
		return NULL;
	}
 
	// popen runs /bin/sh 'command', perhaps we should do something similar 
	// or at least change it to call associated program, eg active perl for *.pl files
	// otherwise only *.exe, *.com, & *.bat will work
	// We run cmd.exe for NT and command.com for 9x
	UT_String cmd;
	if (isNT())
	{
	      cmd += "cmd.exe /C ";  // NOTE: command should already be quoted if needed
	}
	else
	{
		// This is purposely not 'cmd += "command.com /C ";' as it results in hang on W95
		// TODO: figure out why invoking command.com causes Abi to stop responding on W95.
	}
	cmd += command;	

	// Now create the child process. 
	if (! (fSuccess = CreateChildProcess(NULL, (char *)cmd.c_str(), &(p->procInfo),
							hChildStdinRd, hChildStdoutWr, hChildStderrWr) ))
	{
		UT_DEBUGMSG(("KJD: Create process failed\n"));
	}

	// VERY IMPORTANT, do not forget to close these handles, otherwise its never done reading.
	CloseHandle(hChildStdoutWr);
	CloseHandle(hChildStderrWr);
	CloseHandle(hChildStdinRd);

	if (!fSuccess)
	{
		CloseHandle(hChildStdinWrDup);
		CloseHandle(hChildStderrRdDup);
		CloseHandle(hChildStdoutRdDup);
		delete p;
		return NULL;
	}
	else
	{
		// if we gwant to be able to write to child's stdin
		if (p->mode & FAKEPOPEN_MODE_WRITE)
		{
			p->hChildStdIn = hChildStdinWrDup;
		}
		else
		{
			CloseHandle(hChildStdinWrDup);
			p->hChildStdIn = INVALID_HANDLE_VALUE;
		}

		// if we want to be able to read from child's stdout or stderr
		if (p->mode & FAKEPOPEN_MODE_READ)
		{
			p->hChildStdOut = hChildStdoutRdDup;
			p->hChildStdErr = hChildStderrRdDup;
		}
		else
		{
			CloseHandle(hChildStdoutRdDup);
			CloseHandle(hChildStderrRdDup);
			p->hChildStdOut = INVALID_HANDLE_VALUE;
			p->hChildStdErr = INVALID_HANDLE_VALUE;
		}

		p->size = sizeof(PIPE);
		return p;
	}
} 

// The pclose() function waits for the associated process to terminate and
// returns the exit status of the command as returned by GetExitCodeProcess().
int pclose(PIPE *p)
{
	// validate
	if ((p==NULL) || !p->size) return -1;

	// close our end of the pipe
	if (p->hChildStdIn != INVALID_HANDLE_VALUE) CloseHandle(p->hChildStdIn);
	if (p->hChildStdOut != INVALID_HANDLE_VALUE) CloseHandle(p->hChildStdOut);
	if (p->hChildStdErr != INVALID_HANDLE_VALUE) CloseHandle(p->hChildStdErr);
	
	// wait for process to terminate
	DWORD status = -1;
	if (p->procInfo.hProcess)
	{
		while ((GetExitCodeProcess(p->procInfo.hProcess, &status))?(status == STILL_ACTIVE):0)
		{
			Sleep(10); // milliseconds
		}
	}

	ZeroMemory(p, sizeof(PIPE));
	return status;
}

