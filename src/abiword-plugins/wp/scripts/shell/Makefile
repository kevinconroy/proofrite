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

LIBRARY_NAME=		AbiScriptHappy
LIBRARY_VERSION=	$(ABI_VERSION)
TARGETS=			$(PLUGIN)

OBJS=				$(OBJDIR)/ScriptHappy.$(OBJ_SUFFIX)

ifeq ($(ABI_FE), Win32)
	DIRS+= 		win
	OBJS+= 		$(OBJDIR)/fakepopen.$(OBJ_SUFFIX)

	EXTRA_LIBS+=	$(BINDIR)/AbiWord.$(LIB_SUFFIX)
	EXTRA_LIBS+=	$(OBJDIR)/abi_ver.obj
#	EXTRA_LIBS+=	$(OBJDIR)/libAbiUtil_s.$(LIB_SUFFIX)
endif

include $(ABI_ROOT)/src/config/abi_rules.mk

build:: $(TARGETS)
