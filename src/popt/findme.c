/** \ingroup popt
 * \file popt/findme.c
 */

/* (C) 1998-2000 Red Hat, Inc. -- Licensing details are in the COPYING
   file accompanying popt source distributions, available from 
   ftp://ftp.rpm.org/pub/rpm/dist. */

#include "system.h"
#include "findme.h"

#ifndef SEARCH_PATH_SEPARATOR
#ifdef _WIN32
#define SEARCH_PATH_SEPARATOR ';'
#else
#define SEARCH_PATH_SEPARATOR ':'
#endif
#endif

const char * findProgramPath(const char * argv0) {
    char * path = getenv("PATH");
    char * pathbuf;
    char * start, * chptr;
    char * buf;

    /* If there is a / in the argv[0], it has to be an absolute path */
    if (strchr(argv0, '/')
#ifdef _WIN32
         || strchr(argv0, '\\')	/* Windows & DOS supports \ and / in paths */
#endif
       )
	return xstrdup(argv0);

    if (!path) return NULL;

    start = pathbuf = alloca(strlen(path) + 1);
    buf = malloc(strlen(path) + strlen(argv0) + sizeof("/"));
    strcpy(pathbuf, path);

    chptr = NULL;
    do {
	if ((chptr = strchr(start, SEARCH_PATH_SEPARATOR)))
	    *chptr = '\0';
	sprintf(buf, "%s/%s", start, argv0);

	if (!access(buf, X_OK))
	    return buf;

	if (chptr) 
	    start = chptr + 1;
	else
	    start = NULL;
    } while (start && *start);

    free(buf);

    return NULL;
}
