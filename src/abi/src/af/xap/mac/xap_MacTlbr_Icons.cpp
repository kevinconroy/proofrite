/* -*- c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */
/* AbiSource Application Framework
 * Copyright (C) 1998 AbiSource, Inc.
 * Copyright (C) 1999 John Brewer DBA Jera Design
 * Copyright (C) 2001 Hubert Figuiere
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
 
#include <QuickDraw.h>

#include "ut_types.h"
#include "ut_assert.h"
#include "ut_Xpm2Bmp.h"
#include "xap_MacTlbr_Icons.h"

AP_MacToolbar_Icons::AP_MacToolbar_Icons(void)
{
}

AP_MacToolbar_Icons::~AP_MacToolbar_Icons(void)
{
	// TODO do we need to keep some kind of list
	// TODO of the things we have created and
	// TODO handed out, so that we can delete them ??
}

bool AP_MacToolbar_Icons::getBitmapForIcon(const char * szIconName,
					   PicHandle * pIconHandle)
{
	UT_ASSERT(szIconName && *szIconName);
	UT_ASSERT(pIconHandle);
	UT_uint32 maxWidth, maxHeight;
	maxWidth = maxHeight = 16;
	
	const char ** pIconData = NULL;
	UT_uint32 sizeofIconData = 0;		// number of cells in the array
	
	bool bFound = _findIconDataByName(szIconName, &pIconData, &sizeofIconData);
	if (!bFound) {
		return false;
	}
	
	bool bCreated = UT_Xpm2Pict(pIconData,sizeofIconData,pIconHandle);
	
	return bCreated;
}

