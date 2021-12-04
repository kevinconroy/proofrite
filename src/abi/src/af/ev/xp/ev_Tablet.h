/* AbiSource Program Utilities
 * Copyright (C) 1998 AbiSource, Inc.
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
 

#ifndef EV_TABLET_H
#define EV_TABLET_H

#include "ut_types.h"
#include "gr_Win32Stroke.h"

class EV_EditEventMapper;
class EV_EditMethod;
class AV_View;

class ABI_EXPORT EV_Tablet
{
public:
	EV_Tablet(EV_EditEventMapper * pEEM);
	bool invokeTabletMethod(AV_View * pView,
							  EV_EditMethod * pEM,
							  UT_sint32 xPos,
							  UT_sint32 yPos);
	bool invokeTabletMethod(AV_View * pView,
							  EV_EditMethod * pEM,
							  UT_sint32 xPos,
							  UT_sint32 yPos,
                //UT_UCS2Char * pData,
                char *pData,
                //UT_UCSChar *pData,
								UT_uint32 dataLength);
	bool invokeTabletMethod(AV_View * pView,
							  EV_EditMethod * pEM,
							  UT_sint32 xPos,
							  UT_sint32 yPos,
                GR_Win32Stroke *pStroke);
	void setEditEventMap(EV_EditEventMapper * pEEM);

protected:
	EV_EditEventMapper *	m_pEEM;
};

#endif /* EV_TABLET_H */
