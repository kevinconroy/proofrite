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


#ifndef PP_TABLEATTRPROP_H
#define PP_TABLEATTRPROP_H

#include "ut_types.h"
#include "ut_vector.h"
#include "pt_Types.h"
#include "pp_AttrProp.h"


// pp_TableAttrProp implements an unbounded table of PP_AttrProp
// objects.  Each PP_AttrProp represents the complete Attribute/
// Property state of one or more pieces (subsequences) of the
// document.

class ABI_EXPORT pp_TableAttrProp
{
public:
	pp_TableAttrProp();
	~pp_TableAttrProp();

	bool					addAP(PP_AttrProp * pAP,
								  UT_uint32 * pSubscript);
	bool					createAP(UT_uint32 * pSubscript);

	bool					createAP(const XML_Char ** attributes,
									 const XML_Char ** properties,
									 UT_uint32 * pSubscript);

	bool					createAP(const UT_Vector * pVector,
									 UT_uint32 * pSubscript);

	bool					findMatch(const PP_AttrProp * pMatch,
									  UT_uint32 * pSubscript) const;
	
	const PP_AttrProp *		getAP(UT_uint32 subscript) const;

protected:
	UT_Vector				m_vecTable;
};

#endif /* PP_TABLEATTRPROP_H */
