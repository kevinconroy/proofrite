/* AbiWord
 * Copyright (C) 2000,2001 Mike Nordell, Dom Lachowicz, and others
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

#ifndef FP_PAGESIZE_H
#define FP_PAGESIZE_H

#include "ut_types.h"
#include "ut_units.h"

class ABI_EXPORT fp_PageSize
{
public:

	enum Predefined
	{
		_first_predefined_pagesize_ = 0,
		// If you append a predefined pagesize here, don't forget
		// to update the cpp accordingly.

		// namespacing with 'ps' since B[0-9] seem to be reserved
		// for BAUD rates under SUSv3 (according to Daniel E. Eisenbud)

		// Metric sizes, DIN 476
		psDIN_4A = 0,
		psDIN_2A,
		psA0, psA1, psA2, psA3, psA4, psA5, psA6, psA7, psA8, psA9, psA10,
		psDIN_4B,
		psDIN_2B,
		psB0, psB1, psB2, psB3, psB4, psB5, psB6, psB7, psB8, psB9, psB10,
		psC0, psC1, psC2, psC3, psC4,       psC6, psC7, psC8, psC9, psC10,

		// JIS P 0138-61 -- should call this JB5
		psB5_Japan,
		
		psLegal,
		psFolio,
		psLetter,
		psHalf_Letter,
		psExecutive,
		psTabloid_Ledger,
		psMonarch,
		psSuperB,
		psEnvelope_Commercial,
		psEnvelope_Monarch,
		psEnvelope_DL,
		psEnvelope_C5,
		psEuroPostcard,

		psCustom,
		// append new pagesizes here
		_last_predefined_pagesize_dont_use_
	};

	fp_PageSize(Predefined preDef);
	fp_PageSize(const char *name);
	fp_PageSize(double w, double h, UT_Dimension u);

	void Set(Predefined preDef, UT_Dimension u = DIM_none);
	void Set(const char *name, UT_Dimension u = DIM_none);
	void Set(double w, double h, UT_Dimension u = DIM_none);
	void Set(UT_Dimension u) { m_unit = u; }
	inline void setScale( double scale) { m_scale = scale; }
	void setPortrait(void);
	void setLandscape(void);
	bool isPortrait(void) const { return m_bisPortrait; }
	double Width(UT_Dimension u) const;
	double Height(UT_Dimension u) const;

	/* These accessor methods should be used with the 
	 * predefined page sizes to set proper initial margins. */
	/* I don't think this is done at present. */
	double MarginLeft(UT_Dimension u) const;
	double MarginRight(UT_Dimension u) const;
	double MarginTop(UT_Dimension u) const;
	double MarginBottom(UT_Dimension u) const;

	double getScale(void) { return m_scale; }
	UT_Dimension getDims(void) { return m_unit; }
	inline char * getPredefinedName (void) const { return m_predefined; }

	static bool	IsPredefinedName(const char* szPageSizeName);
	static Predefined NameToPredefined(const char *name);
	static const char * PredefinedToName(Predefined preDef);

private:
	char * m_predefined;

	double m_iWidth;
	double m_iHeight;

	double m_iMarginLeft;
	double m_iMarginRight;
	double m_iMarginTop;
	double m_iMarginBottom;

	bool m_bisPortrait;
	double m_scale;
	UT_Dimension m_unit;
};

#endif	// FP_PAGESIZE_H
