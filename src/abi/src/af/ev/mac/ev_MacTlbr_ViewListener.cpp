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

#include "ut_types.h"
#include "ut_debugmsg.h"
#include "ut_assert.h"
#include "ev_MacTlbr_ViewListener.h"
#include "ev_MacToolbar.h"

EV_MacToolbar_ViewListener::EV_MacToolbar_ViewListener(EV_MacToolbar * pMacToolbar,
														 AV_View * pView)
{
	m_pMacToolbar = pMacToolbar;
	m_pView = pView;
}

bool EV_MacToolbar_ViewListener::notify(AV_View * pView, const AV_ChangeMask mask)
{
	UT_ASSERT(pView == m_pView);
	
	UT_DEBUGMSG(("MacToolbar_ViewListener::notify [view %p tb %p][mask %p]\n",
				 pView,this,mask));
	
	// this code really could be in EV_MacToolbar, but I didn't want
	// to multiple-inherit it.

	return m_pMacToolbar->refreshToolbar(pView,mask);
}
