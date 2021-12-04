/*
 * Sorta a popen for Windows, except intead of FILE *
 * returns a PIPE * that has HANDLEs childs stdin/stdout/stderr
 */

#ifndef __FAKEPOPEN_H__
#define __FAKEPOPEN_H__

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FAKEPOPEN_MODE_NONE	0
#define FAKEPOPEN_MODE_READ	1
#define FAKEPOPEN_MODE_WRITE	2

typedef struct PIPE
{
	DWORD size;
	WORD mode;
	HANDLE hChildStdIn, hChildStdOut, hChildStdErr;
	PROCESS_INFORMATION procInfo;
} PIPE;

PIPE * popen(char *command, const char *mode);
int pclose(PIPE *p);

#ifdef __cplusplus
}
#endif

#endif /* __FAKEPOPEN_H__ */
