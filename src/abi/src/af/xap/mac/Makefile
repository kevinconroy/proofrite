#! gmake

## AbiSource Application Framework
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

include $(ABI_ROOT)/src/config/abi_defs.mk

CPPSRCS=		xap_MacApp.cpp			\
			xap_MacClipboard.cpp		\
			xap_MacDlg_About.cpp		\
			xap_MacDlg_Image.cpp		\
			xap_MacDlg_ClipArt.cpp		\
			xap_MacDlg_FileOpenSaveAs.cpp	\
			xap_MacDlg_FontChooser.cpp	\
			xap_MacDlg_Language.cpp		\
			xap_MacDlg_Insert_Symbol.cpp	\
			xap_MacDlg_MessageBox.cpp	\
			xap_MacDlg_Password.cpp		\
			xap_MacDlg_PluginManager.cpp	\
			xap_MacDlg_Print.cpp		\
			xap_MacDlg_PrintPreview.cpp     \
			xap_MacDlg_WindowMore.cpp	\
			xap_MacDlg_Zoom.cpp		\
			xap_MacEncodingManager.cpp	\
			xap_MacFontManager.cpp		\
			xap_MacFrame.cpp		\
			xap_MacModule.cpp		\
			xap_MacTlbr_Icons.cpp		\
			xap_MacToolbar_Control.cpp

REZSRCS=		xap_MacDlg_MessageBox.r		\
                        xap_MacResources.r

TARGETS=		$(OBJS)

include $(ABI_ROOT)/src/config/abi_rules.mk

build:: $(TARGETS)
