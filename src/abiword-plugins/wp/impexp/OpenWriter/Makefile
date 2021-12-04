#! gmake

## AbiWord
## Copyright (C) 1998 AbiSource, Inc.
##
## This program is free software; you can redistribute it and/or
## modify it under the terms of the GNU General Public License
## as published by the Free Software Foundation; either version 2
## of the License, or (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  
## 02111-1307, USA.

ABI_ROOT:=$(shell pwd)/../../../../abi
include $(ABI_ROOT)/src/config/abi_defs.mk

DIRS=				xp

LIBRARY_NAME=		OpenWriter
LIBRARY_VERSION=	$(ABI_VERSION)
TARGETS=			$(PLUGIN)

OBJS=				$(OBJDIR)/ie_impexp_OpenWriter.$(OBJ_SUFFIX)

ifeq ($(ABI_FE), Win32)
	OS_LIBS= kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib uuid.lib comctl32.lib wsock32.lib ole32.lib oleaut32.lib 
	EXTRA_LIBS+=  $(BINDIR)/AbiWord.$(LIB_SUFFIX) 
	EXTRA_LIBS+=  win/zipios.$(LIB_SUFFIX)
	ABI_APPLIBS=  Abi_zlib
	OS_DLLFLAGS+= -NODEFAULTLIB:MSVCRT
	OS_DLLFLAGS+= -NODEFAULTLIB:MSVCPRT
else
	EXTRA_LIBS = -lz -lzipios
endif

include $(ABI_ROOT)/src/config/abi_rules.mk

build:: $(TARGETS)
