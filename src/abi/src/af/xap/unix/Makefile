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

ifeq ($(ABI_OPT_GNOME),1)
DIRS=		$(ABI_GNOME_DIR)
endif

CPPSRCS=		xap_UnixApp.cpp				\
			xap_UnixClipboard.cpp			\
			xap_UnixDialogHelper.cpp		\
			xap_UnixDlg_ClipArt.cpp			\
			xap_UnixDlg_Password.cpp		\
			xap_UnixDlg_Image.cpp			\
			xap_UnixDlg_PluginManager.cpp		\
			xap_UnixDlg_Encoding.cpp		\
			xap_UnixDlg_FileOpenSaveAs.cpp		\
			xap_UnixDlg_FontChooser.cpp		\
			xap_UnixDlg_HTMLOptions.cpp		\
			xap_UnixDlg_MessageBox.cpp		\
			xap_UnixDlg_Print.cpp			\
			xap_UnixDlg_WindowMore.cpp		\
			xap_UnixDlg_Zoom.cpp			\
			xap_UnixDlg_Insert_Symbol.cpp		\
			xap_UnixFontXLFD.cpp			\
			xap_UnixFont.cpp			\
			xap_UnixFontPreview.cpp			\
			xap_UnixPSFont.cpp			\
			xap_UnixFrameImpl.cpp			\
			xap_UnixToolbar_Icons.cpp		\
			xap_UnixModule.cpp                      \
			xap_UnixPSImage.cpp			\
			xap_UnixPSParseAFM.cpp			\
			xap_UnixEncodingManager.cpp 		\
			xap_UnixDlg_Language.cpp		\
	                xap_UnixNullGraphics.cpp                \
			xap_UnixPSGenerate.cpp			\
			xap_UnixPSGraphics.cpp                  \
			xap_UnixGtkColorPicker.cpp              \
	                xap_UnixTableWidget.cpp

# only build these for non-gnome
ifneq ($(ABI_OPT_GNOME),1)
CPPSRCS +=		xap_UnixDlg_About.cpp			\
			xap_UnixDlg_PrintPreview.cpp            
endif

ifneq ($(ABI_OPT_PANGO),1)
CPPSRCS +=		xap_UnixFontManager.cpp
endif

TARGETS=		$(OBJS)
INCLUDES=      -I/usr/X11R6/include

include $(ABI_ROOT)/src/config/abi_rules.mk

build:: $(TARGETS)
