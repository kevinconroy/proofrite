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

include $(ABI_ROOT)/src/config/abi_defs_hello.mk

CPPSRCS=		UnixMain.cpp

INCLUDES=		$(GTK_CFLAGS)

PROGRAM=		$(BINDIR)/AbiHello

# TODO the Linux linker is fussy about the ordering of libraries.
# TODO in order to get all symbols to resolve, i had to list them
# TODO several times.  see if there is a better way of doing this.

LoadOrder=		AbiGr AbiHEAp AbiXAp AbiEv AbiUtil AbiHelloVer 
ABI_APPLIBS=		$(LoadOrder) $(LoadOrder) $(LoadOrder)
ABI_APPLIBDEP=		$(LoadOrder)

ABI_LIBS=		png $(DL_LIBS)

TARGETS=		$(PROGRAM)

include $(ABI_ROOT)/src/config/abi_rules.mk

##################################################################
## everything below here must *FOLLOW* abi_rules
##################################################################

## TODO decide how/if to build completely statically.
## TODO defer decision until later.
## TODO you'll need to set LD_LIBRARY_PATH to $(BINDIR)
## TODO in your environment in order to run the executable

##LDFLAGS +=		-static
##LDFLAGS +=		-shared

# we override the $(PROGRAM) rule.

$(PROGRAM): $(OBJS) $(EXTRA_LIBDEP)
	@$(MAKE_OBJDIR)
	@echo Linking $(PROGRAM)....
	@$(CCC) -o $@ $(CFLAGS) $(OBJS) -L/usr/local/lib $(LDFLAGS) $(EXTRA_LIBS) $(XLDFLAGS) -L/usr/local/lib 

build:: $(TARGETS)
