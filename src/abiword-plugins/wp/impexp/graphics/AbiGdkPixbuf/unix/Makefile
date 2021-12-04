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

ABIROOT:=$(shell pwd)/../../../../../..
CC = g++
CPPFLAGS = -Wall -ansi
#
# If this is installed as a peer, this will find abi
#
ABISRC = $(ABIROOT)/abi/src

INCLUDE = -I$(ABISRC)/af/xap/xp \
          -I$(ABISRC)/af/util/xp \
	  -I$(ABISRC)/af/util/unix \
	  -I$(ABISRC)/af/gr/xp \
	  -I$(ABISRC)/text/fmt/xp \
	  -I$(ABISRC)/text/ptbl/xp \
	  -I$(ABISRC)/wp/impexp/xp \
	  -I$(ABISRC)/wp/ap/xp \
	  -I$(ABIROOT)/libpng \
	  -I$(ABIROOT)/expat/lib \
          -I/usr/include/gtk-1.2 \
	  -I/usr/include/glib-1.2 \
	  -I/usr/lib/glib/include/ \
	  -I/usr/include/gdk-pixbuf \


OBJS=				$(OBJDIR)/AbiGdkPixbuf.$(OBJ_SUFFIX)

CPPSRCS= 			AbiGdkPixbuf.cpp

## EXTRA_LIBS = -lgdk-pixbuf 

libAbiGdkPixbuf.so : AbiGdkPixbuf.cpp
	$(CC) $(CPPFLAGS) $(INCLUDE) -shared -o libAbiGdkPixbuf.so AbiGdkPixbuf.cpp 
clean: 
	rm *.so

