#! gmake

## AbiSource Applications
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

ABI_ROOT:=$(shell pwd)/../../..
include $(ABI_ROOT)/src/config/abi_defs_wp.mk
include $(ABI_ROOT)/src/config/abi_rules.mk

##################################################################

PKGBASENAME=AbiSuite-$(ABI_BUILD_VERSION)

ifeq ($(OS_ARCH), x86)
SUFFIX=i386
endif
ifeq ($(OS_ARCH), ppc)
SUFFiX=ppc
endif

ABI_DIST_TARGET=zip

distribution:	$(ABI_DIST_TARGET)

zip:
	@echo "Building binary zip file..."
	$(subst xxxx,$(DIST),$(VERIFY_DIRECTORY))
	rm -rf $(DIST)/tmp
	$(subst xxxx,$(DIST)/tmp,$(VERIFY_DIRECTORY))
	(cd $(OUTDIR); tar cf - AbiSuite) | (cd $(DIST)/tmp;          tar xf -)
	(cd $(OUTDIR); tar cf - bin/Abi*) | (cd $(DIST)/tmp/AbiSuite; tar xf -)
	(cd $(DIST)/tmp; zip -r ../$(PKGBASENAME)-$(SUFFIX).zip AbiSuite)
	(cd $(DIST); rm -rf tmp)
