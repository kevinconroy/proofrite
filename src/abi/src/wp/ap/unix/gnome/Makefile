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

ABI_ROOT:=$(shell pwd)/../../../../..

include $(ABI_ROOT)/src/config/abi_defs_wp.mk

ABI_WP_INCS+=	/wp/ap/$(ABI_NATIVE)/$(ABI_GNOME_DIR)

PLATFORM_OBJS+=	$(OBJDIR)/ap_$(ABI_FE)$(ABI_GNOME_PREFIX)App.$(OBJ_SUFFIX)			\
		$(OBJDIR)/ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_New.$(OBJ_SUFFIX)		\
		$(OBJDIR)/ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_Break.$(OBJ_SUFFIX)		\
		$(OBJDIR)/ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_InsertTable.$(OBJ_SUFFIX)		\
		$(OBJDIR)/ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_Columns.$(OBJ_SUFFIX)		\
		$(OBJDIR)/ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_Field.$(OBJ_SUFFIX)		\
		$(OBJDIR)/ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_Goto.$(OBJ_SUFFIX)		\
		$(OBJDIR)/ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_InsertBookmark.$(OBJ_SUFFIX)	\
		$(OBJDIR)/ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_InsertHyperlink.$(OBJ_SUFFIX)	\
		$(OBJDIR)/ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_Insert_DateTime.$(OBJ_SUFFIX)   \
		$(OBJDIR)/ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_Replace.$(OBJ_SUFFIX)		\
		$(OBJDIR)/ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_WordCount.$(OBJ_SUFFIX)         \
		$(OBJDIR)/ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_Paragraph.$(OBJ_SUFFIX)         \
		$(OBJDIR)/ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_PageNumbers.$(OBJ_SUFFIX)       \
		$(OBJDIR)/ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_PageSetup.$(OBJ_SUFFIX)         \
		$(OBJDIR)/ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_Lists.$(OBJ_SUFFIX)		\
		$(OBJDIR)/ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_Spell.$(OBJ_SUFFIX)		\
		$(OBJDIR)/ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_Styles.$(OBJ_SUFFIX)		\
		$(OBJDIR)/ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_ToggleCase.$(OBJ_SUFFIX)	\
		$(OBJDIR)/ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_Tab.$(OBJ_SUFFIX)		\
		$(OBJDIR)/ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_Background.$(OBJ_SUFFIX)	\
		$(OBJDIR)/ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_HdrFtr.$(OBJ_SUFFIX)	\
		$(OBJDIR)/ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_Options.$(OBJ_SUFFIX) \
		$(OBJDIR)/ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_MetaData.$(OBJ_SUFFIX) \
		$(OBJDIR)/ap_NautilusView.$(OBJ_SUFFIX) 


CPPSRCS=		ap_$(ABI_FE)$(ABI_GNOME_PREFIX)App.cpp			\
			ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_New.cpp		\
			ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_Break.cpp		\
			ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_InsertTable.cpp		\
			ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_Columns.cpp	\
			ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_Field.cpp		\
			ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_Goto.cpp		\
			ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_InsertBookmark.cpp \
			ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_InsertHyperlink.cpp \
			ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_Insert_DateTime.cpp \
			ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_Replace.cpp	\
			ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_WordCount.cpp     \
			ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_PageNumbers.cpp   \
			ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_PageSetup.cpp     \
			ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_Paragraph.cpp     \
			ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_Lists.cpp		\
			ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_Spell.cpp		\
			ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_ToggleCase.cpp	\
			ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_Styles.cpp		\
			ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_Tab.cpp		\
			ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_Background.cpp	\
			ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_HdrFtr.cpp	\
			ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_Options.cpp  \
			ap_$(ABI_FE)$(ABI_GNOME_PREFIX)Dialog_MetaData.cpp  \
			ap_NautilusView.cpp 


TARGETS=		$(OBJS)

include $(ABI_ROOT)/src/config/abi_rules.mk

build:: $(TARGETS)
