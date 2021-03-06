#! gmake

## AbiSource Applications
## Copyright (C) 1999 AbiSource, Inc.
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

ABI_ROOT:=$(shell pwd)/../../..
include $(ABI_ROOT)/src/config/abi_defs_wp.mk
include $(ABI_ROOT)/src/config/abi_rules.mk

##################################################################
## This makefile serves two purposes.  It exposes an "install" 
## target, wherein it installs AbiSuite applications.  The
## eventual layout of these files is $(prefix)/AbiSuite, except
## for symbolic links in $(prefix/bin.  /usr/local is a good value
##  to use for $(prefix), and it is the default.
## 
## If you're looking to build distribution packages, this Makefile
## also provides the "distribution" target, which depends on 
## installation targets specific to the distribution layouts
## it will build.  These targets might be named "install_redhat"
## or "install_debian"; they place the program components into places
## their respective distributions would expect to find them.  These
## targets will be called by package tools like RPM.

# The plain "install" common to all Unix targets
install:
	@TARGET=$(prefix)/AbiSuite BINDIR=$(prefix)/bin SRCDIR=$(OUTDIR) \
		SCRIPTDIR=$(ABI_ROOT)/src/pkg/common/unix/scripts \
		$(ABI_ROOT)/src/pkg/common/unix/scripts/install.sh

########################################################################

# If tgz is inside $ABI_DIST_TARGET
ifneq ($(findstring tgz,$(ABI_DIST_TARGET)),)
        DIST_DEPS += tgz
endif

# If tbz is inside $ABI_DIST_TARGET
ifneq ($(findstring tbz,$(ABI_DIST_TARGET)),)
        DIST_DEPS += tbz
endif

# Tgz target is provided by a common Unix makefile

include $(ABI_ROOT)/src/pkg/common/unix/tgz.mk
include $(ABI_ROOT)/src/pkg/common/unix/tbz.mk

########################################################################

# This target should build all packages defined for this platform
distribution: $(DIST_DEPS)

