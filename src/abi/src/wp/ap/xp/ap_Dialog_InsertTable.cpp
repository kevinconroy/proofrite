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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ut_assert.h"
#include "ut_string.h"
#include "ut_debugmsg.h"

#include "xap_Dialog_Id.h"
#include "xap_DialogFactory.h"
#include "xap_Dlg_MessageBox.h"

#include "ap_Dialog_InsertTable.h"

AP_Dialog_InsertTable::AP_Dialog_InsertTable(XAP_DialogFactory * pDlgFactory, XAP_Dialog_Id id)
	: XAP_Dialog_NonPersistent(pDlgFactory,id)
{
	m_answer = a_OK;
	
	/* Default values for the dialog box*/
	m_numRows = 2;
	m_numCols = 5;
	m_columnWidth = 0.7f;
}

AP_Dialog_InsertTable::~AP_Dialog_InsertTable(void)
{
}

AP_Dialog_InsertTable::tAnswer AP_Dialog_InsertTable::getAnswer(void) const
{
	return m_answer;
}

AP_Dialog_InsertTable::columnType AP_Dialog_InsertTable::getColumnType(void) const
{
	return m_columnType;
}

UT_uint32 AP_Dialog_InsertTable::getNumRows(void)
{
	return m_numRows;
}

UT_uint32 AP_Dialog_InsertTable::getNumCols(void)
{
	return m_numCols;
}

float AP_Dialog_InsertTable::getColumnWidth(void)
{
	return m_columnWidth;
}
