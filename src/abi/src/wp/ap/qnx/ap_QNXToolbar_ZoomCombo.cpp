/* AbiWord
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

#include "ut_assert.h"
#include "ut_vector.h"
#include "ap_QNXToolbar_ZoomCombo.h"
#include "ap_Toolbar_Id.h"
#include "xap_Frame.h"
#include "xap_App.h"
/*****************************************************************/
EV_Toolbar_Control * AP_QNXToolbar_ZoomCombo::static_constructor(EV_Toolbar * pToolbar,
														  XAP_Toolbar_Id id)
{
	AP_QNXToolbar_ZoomCombo * p = new AP_QNXToolbar_ZoomCombo(pToolbar,id);
	return p;
}

AP_QNXToolbar_ZoomCombo::AP_QNXToolbar_ZoomCombo(EV_Toolbar * pToolbar,
													 XAP_Toolbar_Id id)
	: EV_Toolbar_Control(pToolbar/*,id*/)
{
	UT_ASSERT(id==AP_TOOLBAR_ID_ZOOM);

	m_nPixels = 60;		// TODO: do a better calculation
	m_nLimit = 6;
}

AP_QNXToolbar_ZoomCombo::~AP_QNXToolbar_ZoomCombo(void)
{
	// nothing to purge.  contents are static strings
	free(m_vecContents.getNthItem(6));
	free(m_vecContents.getNthItem(7));
	free(m_vecContents.getNthItem(8));

}

/*****************************************************************/

bool AP_QNXToolbar_ZoomCombo::populate(void)
{
	// clear anything that's already there
	m_vecContents.clear();

	// populate the vector
	m_vecContents.addItem((void *) "200%");
	m_vecContents.addItem((void *) "150%");
	m_vecContents.addItem((void *) "100%");
	m_vecContents.addItem((void *) "75%");
	m_vecContents.addItem((void *) "50%");
	m_vecContents.addItem((void *) "25%");

	const XAP_StringSet * pSS = XAP_App::getApp()->getStringSet();
	
	m_vecContents.addItem((void *)strdup(pSS->getValueUTF8(XAP_STRING_ID_TB_Zoom_PageWidth).c_str()));
	m_vecContents.addItem((void *)strdup(pSS->getValueUTF8(XAP_STRING_ID_TB_Zoom_WholePage ).c_str()));
	m_vecContents.addItem((void *)strdup(pSS->getValueUTF8(XAP_STRING_ID_TB_Zoom_Percent ).c_str()));

	return true;
}

