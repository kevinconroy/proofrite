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

#This is very bad
#include $(ABI_ROOT)/src/config/abi_defs.mk
include $(ABI_ROOT)/src/config/abi_defs_wp.mk

CPPSRCS=		xap_QNXApp.cpp				\
			xap_QNXClipboard.cpp			\
			xap_QNXDlg_About.cpp			\
			xap_QNXDlg_Image.cpp			\
			xap_QNXDlg_ClipArt.cpp			\
			xap_QNXDlg_Encoding.cpp		\
			xap_QNXDlg_FileOpenSaveAs.cpp		\
			xap_QNXDlg_FontChooser.cpp		\
			xap_QNXDlg_Language.cpp			\
			xap_QNXDlg_MessageBox.cpp		\
			xap_QNXDlg_Password.cpp			\
			xap_QNXDlg_PluginManager.cpp		\
			xap_QNXDlg_Print.cpp			\
			xap_QNXDlg_PrintPreview.cpp             \
			xap_QNXDlg_WindowMore.cpp		\
			xap_QNXDlg_Zoom.cpp			\
			xap_QNXDlg_Insert_Symbol.cpp		\
			xap_QNXEncodingManager.cpp		\
			xap_QNXModule.cpp			\
			xap_QNXToolbar_Icons.cpp \
			xap_QNXFontPreview.cpp	\
			xap_QNXDlg_HTMLOptions.cpp	\
			xap_QNXFrameImpl.cpp

TARGETS=		$(OBJS)

include $(ABI_ROOT)/src/config/abi_rules.mk

build:: $(TARGETS)
