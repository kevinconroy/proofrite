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

ABI_ROOT:=$(shell pwd)/../../../..

include $(ABI_ROOT)/src/config/abi_defs_wp.mk

CPPSRCS=		Win32Main.cpp
RCSRCS=			Win32Main.rc

PROGRAM=		$(BINDIR)/AbiWord.exe

## TODO should /profile be on the following line ??  does this
## TODO enable linking with profile-libraries and thus bloat us.

ifeq ($(OS_NAME), MINGW32)
MINGRES_INCS=--include-dir=$(ABI_ROOT)/src/wp/ap/win --include-dir=$(ABI_ROOT)/src/af/xap/win
CPPSRCS+=		dummy.cpp

ABI_LIBS=		kernel32 user32 gdi32 winspool comdlg32 advapi32 \
			shell32 uuid comctl32 ole32

LoadOrder=		AbiGr AbiFmt AbiPTbl AbiImpExp AbiXAp AbiWPAp \
			AbiEv AbiUtil AbiImpExp AbiWordVer AbiSpell Abi_libwv fribidi \
			Abi_libpopt Abi_libiconv Abi_libpng Abi_zlib

ABI_APPLIBS=		$(LoadOrder) $(LoadOrder) $(LoadOrder)
ABI_APPLIBDEP=		$(LoadOrder)

SHARED_LDFLAGS =	$(SHARED_FLAGS) -Wl,--dll -Wl,--export-all-symbols -Wl,--enable-auto-import -Wl,--out-implib,libAbiWord.dll.a


else

ABI_LDFLAGS=		-nologo -subsystem:windows -incremental:no -machine:$(LINK_ARCH) -profile
ABI_APPLIBS=		AbiWordVer AbiUtil AbiImpExp AbiPTbl AbiFmt AbiEv \
					AbiXAp AbiGr AbiWPAp AbiSpell Abi_libpng Abi_zlib Abi_libiconv Abi_libwv \
					Abi_libpopt

ABI_APPLIBDEP=		$(ABI_APPLIBS)

####ABI_LIBS=		kernel32 user32 gdi32 winspool comdlg32 advapi32 \
####			shell32 ole32 oleaut32 uuid odbc32 odbccp32
ABI_LIBS=		kernel32 user32 gdi32 winspool comdlg32 advapi32 \
			shell32 uuid comctl32 msvcprt ole32

GARBAGE=		AbiWord.map AbiWord.pdb

endif
ifeq ($(ABI_OPT_CURL),1)
ABI_APPLIBS+=	Abi_libcurl
# Note: ws2_32.lib is the winsock 2 import library (may cause user to require Winsock 2 update)
ABI_LIBS+=		ws2_32
endif


TARGETS=		$(PROGRAM)

include $(ABI_ROOT)/src/config/abi_rules.mk

##################################################################
## everything below here must *FOLLOW* abi_rules
##################################################################

ifeq ($(OS_NAME), MINGW32)
$(PROGRAM): $(OBJS) $(EXTRA_LIBDEP)
	@$(MAKE_OBJDIR)
	@echo Linking dynamic $(PROGRAM)
	$(CCC) -o $(BINDIR)/libAbiWord.dll $(SHARED_LDFLAGS) $(CFLAGS) $(OBJDIR)/dummy.o  $(LDFLAGS) $(EXTRA_LIBS) $(OS_LIBS) $(XLDFLAGS)
	@mv libAbiWord.dll.a $(LIBDIR)
	$(CCC) -o $@ $(CFLAGS) $(OBJDIR)/Win32Main.o $(OBJDIR)/Win32Mainrc.o $(LDFLAGS) -L$(LIBDIR) -lAbiWord.dll $(OS_LIBS) $(XLDFLAGS)
else
$(PROGRAM): $(OBJS) $(EXTRA_LIBDEP)
	@$(MAKE_OBJDIR)
	@echo Linking $(PROGRAM)....
	@$(CC) $(shell echo $(OBJS) | $(TRANSFORM_TO_DOS_PATH))	\
		-Fe$(shell echo $@ | $(TRANSFORM_TO_DOS_PATH))	\
		-link $(LDFLAGS) $(OS_LIBS) $(ABI_LDFLAGS)				\
		$(shell echo $(EXTRA_LIBS) | $(TRANSFORM_TO_DOS_PATH))
endif

build:: $(TARGETS)
	@echo Target $(TARGETS) completed.
