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


#ifndef IE_IMPEXP_REGISTER_H
#define IE_IMPEXP_REGISTER_H


void IE_ImpExp_RegisterXP ();

// KMC: broken up into seperate functions in case we want to have some control
// over the order in which they are registered.
void IE_ImpExp_RegisterPlatform ();	// must be implemented by the platform
void IE_Imp_RegisterPlatform ();	// must be implemented by the platform
void IE_Exp_RegisterPlatform ();	// must be implemented by the platform

void IE_ImpExp_UnRegisterXP ();

#endif
