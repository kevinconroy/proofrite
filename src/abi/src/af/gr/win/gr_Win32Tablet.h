/* TAbiWord -- Ink support for AbiWord
 * Copyright (C) 2003 Kevin Conroy
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  
 * 02111-1307, USA.
 */

#ifndef GR_WIN32TABLET_H
#define GR_WIN32TABLET_H

#include <comdef.h>
#include <atlbase.h>
#include <msinkaut_i.c>
#include <msinkaut.h>
//#include "tablet/msinkaut_i.c"
//#include "tablet/msinkaut.h"
#include "inked_i.c"
#include "inked.h"

// KMC: Added to allow for easier conversion from char * to BSTR
// taken from: http://msdn.microsoft.com/library/default.asp?url=/library/en-us/vclang/html/vclrfconvertstringtobstr.asp
/*#include <comutil.h>
#include <stdio.h>
#pragma comment(lib, "comsupp.lib")
#pragma comment(lib, "kernel32.lib")
*/

// The constant GUIDs that we'll be using for various extended properties
#define INK_INKSPACE_POS_X L"{265a10aa-5c7f-4d0c-b9c2-aaf0ca52f2c2}"
#define INK_INKSPACE_POS_Y L"{66976544-149a-4316-a6e8-2f7834b266bc}"

#define INK_DEBUG 0
#define STROKE_DEBUG 0

struct InkPoint {
	long x;
	long y;

	InkPoint() { x = -1; y = -1; }
	InkPoint(long x1, long y1) { x = x1; y = y1; }
};

struct ScreenPoint {
	long x;
	long y;

	ScreenPoint() { x = -1; y = -1; }
	ScreenPoint(long x1, long y1) { x = x1; y = y1; }
};


struct ScreenRect {
	int left;
	int top;
	int height;
	int width;

	ScreenRect() { left = 0; top = 0; height = 0; width = 0; }
	ScreenRect(int left, int top, int height, int width) { this->left = left ; this->top = top; this->height = height; this->width = width; }
};

struct InkRect {
	int left;
	int top;
	int height;
	int width;

	InkRect() { left = 0; top = 0; height = 0; width = 0; }
	InkRect(int left, int top, int height, int width) { this->left = left ; this->top = top; this->height = height; this->width = width; }
};


#endif /* GR_WIN32TABLET_H */

