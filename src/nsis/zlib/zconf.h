/* zconf.h -- configuration of the zlib compression library
 * Copyright (C) 1995-1998 Jean-loup Gailly.
 * For conditions of distribution and use, see copyright notice in zlib.h 
 */

/* @(#) $Id: zconf.h,v 1.1.1.1 2003/05/18 17:58:06 kmconroy Exp $ */

#ifndef _ZCONF_H
#define _ZCONF_H


#define MAX_MEM_LEVEL 9

/* Maximum value for windowBits in deflateInit2 and inflateInit2.
 * WARNING: reducing MAX_WBITS makes minigzip unable to extract .gz files
 * created by gzip. (Files created by minigzip can still be extracted by
 * gzip.)
 */
#ifndef MAX_WBITS
#  define MAX_WBITS   15 /* 32K LZ77 window */
#endif

#define OF(args)  args


#ifndef ZEXPORT
#  define ZEXPORT
#endif
#ifndef ZEXPORTVA
#  define ZEXPORTVA
#endif
#ifndef ZEXTERN
#  define ZEXTERN extern
#endif

#ifndef FAR
#  define FAR
#endif

typedef unsigned char  Byte;  /* 8 bits */
typedef unsigned int   uInt;  /* 16 bits or more */
typedef unsigned long  uLong; /* 32 bits or more */

typedef Byte  FAR Bytef;
typedef char  FAR charf;
typedef int   FAR intf;
typedef uInt  FAR uIntf;
typedef uLong FAR uLongf;

typedef void FAR *voidpf;
typedef void     *voidp;

#ifndef z_off_t
#  define  z_off_t long
#endif


#endif /* _ZCONF_H */
