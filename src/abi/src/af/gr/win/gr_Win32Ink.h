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

#ifndef GR_WIN32INK_H
#define GR_WIN32INK_H

#include "xav_View.h"
#include "fv_View.h"
#include "gr_DrawArgs.h"
#include "gr_Graphics.h"
#include "ut_types.h"

// ink related includes
#include "gr_Win32Tablet.h"
#include "gr_Win32Stroke.h"

// a wrapper for the IInkDisp COM class (the Ink object in the TabletPC API)
// Adapter/Wrapper Pattern [GoF]
class ABI_EXPORT GR_Win32Ink
{
  public:
		GR_Win32Ink(IInkDisp *);    
		~GR_Win32Ink(void);
		void				release();

		void				draw(long HDC, IInkRenderer *pInkRenderer);

    // returns the associated GR_Win32Stroke object with the same idea
		GR_Win32Stroke *	getStroke(const XML_Char *strStrokeId);
		GR_Win32Stroke *	getStroke(long strokeId);

		//char *			setXml();
		//GR_Win32Ink *		setXml();		
		char *				serializeInk();
		
		GR_Win32Stroke *	createStroke(VARIANT &packetData);
		void					deleteStroke(IInkStrokeDisp *stroke);


		void				print();
	private:
		char *				serializeInk(IInkDisp *ptrInk);
		IInkDisp *			deserializeInk(const XML_Char *strInk);

		IInkDisp *			m_pInkDisp;

 private:

};

#endif /* GR_WIN32INK_H */

