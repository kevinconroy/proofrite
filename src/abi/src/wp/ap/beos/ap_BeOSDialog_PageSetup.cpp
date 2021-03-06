/* AbiWord
 * Copyright (C) 2001 AbiSource, Inc.
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

#include "ap_BeOSDialog_PageSetup.h"

AP_BeOSDialog_PageSetup::AP_BeOSDialog_PageSetup(XAP_DialogFactory * pDlgFactory, 
			       XAP_Dialog_Id id) :
  AP_Dialog_PageSetup (pDlgFactory, id)
{
}

AP_BeOSDialog_PageSetup::~AP_BeOSDialog_PageSetup(void)
{
}

XAP_Dialog * AP_BeOSDialog_PageSetup::static_constructor(XAP_DialogFactory * pDlgFactory, XAP_Dialog_Id id)
{
  AP_BeOSDialog_PageSetup * dlg = new AP_BeOSDialog_PageSetup (pDlgFactory, id);
  return dlg;
}

void AP_BeOSDialog_PageSetup::runModal (XAP_Frame *pFrame)
{
  return;
}

// when implementing this dialogue, make sure that if the user sets
// custom page size smaller than 1in x 1in, we return cancel