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
 

#ifndef EV_WIN32TABLET_H
#define EV_WIN32TABLET_H

#include "ev_Tablet.h"
#include "ev_EditBits.h"
#include "gr_Win32Stroke.h"


// TODO EV_<platform>Tablet and EV_EditEventMapper are
// TODO unique for each document, although the EditBindings
// TODO may be global.  (ev_<platform>Tablet could be global
// TODO i suppose.)

class AV_View;


class EV_Win32Tablet : public EV_Tablet
{
public:
	EV_Win32Tablet(EV_EditEventMapper * pEEM);

	void reset(void);

	void onButtonDown(AV_View * pView, HWND hWnd, EV_EditMouseButton emb, WPARAM fwKeys, WPARAM xPos, WPARAM yPos);
	void onButtonUp  (AV_View * pView, HWND hWnd, EV_EditMouseButton emb, WPARAM fwKeys, WPARAM xPos, WPARAM yPos);
	void onButtonMove(AV_View * pView, HWND hWnd, WPARAM fwKeys, WPARAM xPos, WPARAM yPos);
	void onDoubleClick(AV_View * pView, HWND hWnd, EV_EditMouseButton emb, WPARAM fwKeys, WPARAM xPos, WPARAM yPos);

  // oh the OOP pain - get rid of the EV_EditMethodContainer* pEMC parameter as soon as we figure out the REAL way to call insertInk
	// void onStroke  (AV_View * pView, HWND hWnd, long xPos, long yPos, GR_Win32Stroke *stroke);
  void onStroke  (AV_View * pView, HWND hWnd, long xPos, long yPos, GR_Win32Stroke *stroke, const EV_EditMethodContainer* pEMC);
	//void onStroke  (AV_View * pView, HWND hWnd, EV_EditMouseButton emb, WPARAM fwKeys, WPARAM xPos, WPARAM yPos, UT_UCSChar *strInk, int inkLength, const EV_EditMethodContainer* pEMC);
	// void onStroke  (AV_View * pView, HWND hWnd, EV_EditMouseButton emb, WPARAM fwKeys, WPARAM xPos, WPARAM yPos, UT_UCSChar *strInk, const EV_EditMethodContainer* pEMC);

protected:
	UT_uint32			m_iCaptureCount;
	EV_EditMouseButton	m_embCaptured;
	UT_uint32			m_clickState;	/* {NoClick,SingleClick,DoubleClick} */
	EV_EditMouseContext	m_contextState;	/* mouse context of click */
};

#endif /* EV_WIN32TABLET_H */
