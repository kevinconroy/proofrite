/* AbiWord
 * Copyright (C) 2002 Patrick Lam <plam@mit.edu>
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
 *
 */

#ifndef FOOTNOTECONTAINER_H
#define FOOTNOTECONTAINER_H

#ifdef FMT_TEST
#include <stdio.h>
#endif

#include "ut_misc.h"
#include "ut_types.h"
#include "ut_vector.h"
#include "pt_Types.h"
#include "fp_Page.h"
#include "fp_ContainerObject.h"
#include "fp_Column.h"
#include "gr_Graphics.h"

class fl_TableLayout;
class fl_DocSectionLayout;

class ABI_EXPORT fp_FootnoteContainer : public fp_VerticalContainer
{
public:
	fp_FootnoteContainer(fl_SectionLayout* pSectionLayout);
	virtual ~fp_FootnoteContainer();
	UT_sint32           getValue(void);
	void				layout(void);
	virtual void		clearScreen(void);
	virtual void		draw(dg_DrawArgs*);
	virtual void		draw(GR_Graphics*) {}
	virtual void        setContainer(fp_Container * pContainer);
	virtual fp_Container * getNextContainerInSection(void) const;
	virtual fp_Container * getPrevContainerInSection(void) const;
	virtual fp_Page *   getPage(void) { return m_pPage;}
	void                setPage(fp_Page * pPage);
	fl_DocSectionLayout * getDocSectionLayout(void);

private:
	fp_Page * m_pPage;
};

#endif /* FOOTNOTECONTAINER_H */
