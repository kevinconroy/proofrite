/* AbiWord
 * Copyright (C) 1998 AbiSource, Inc.
 * Copyright (C) 2002 Martin Sevior <msevior@physics.unimelb.edu.au>
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

#ifndef TABLELAYOUT_H
#define TABLELAYOUT_H

#ifdef FMT_TEST
#include <stdio.h>
#endif

#include "ut_types.h"
#include "ut_vector.h"
#include "pt_Types.h"
#include "fl_Layout.h"
#include "fl_ContainerLayout.h"
#include "fl_SectionLayout.h"
#include "pl_Listener.h"
#include "ut_debugmsg.h"
#include "ut_misc.h" // for UT_RGBColor

enum  FL_TableJustification
{
    FL_TABLE_LEFT,
    FL_TABLE_CENTER,
    FL_TABLE_RIGHT,
    FL_TABLE_FULL
};

class fp_Page;
class FL_DocLayout;
class fl_Layout;
class fl_ContainerLayout;
class fl_BlockLayout;
class fl_SectionLayout;
class fl_DocSectionLayout;
class fl_HdrFtrSectionLayout;
class fl_HdrFtrShadow;
class fl_CellLayout;
class fb_LineBreaker;
class fp_ShadowContainer;
class fp_Column;
class fp_Run;
class fp_Line;
class fp_Container;
class fp_HdrFtrContainer;
class fp_TableContainer;
class fp_CellContainer;
class PD_Document;
class PP_AttrProp;
class PX_ChangeRecord_FmtMark;
class PX_ChangeRecord_FmtMarkChange;
class PX_ChangeRecord_Object;
class PX_ChangeRecord_ObjectChange;
class PX_ChangeRecord_Span;
class PX_ChangeRecord_SpanChange;
class PX_ChangeRecord_Strux;
class PX_ChangeRecord_StruxChange;

class fl_ColProps
{
public:
	UT_sint32 m_iColWidth;
};

class fl_RowProps
{
public:
	UT_sint32 m_iRowHeight;
};


class ABI_EXPORT fl_TableLayout : public fl_SectionLayout
{
	friend class fl_DocListener;

public:
	fl_TableLayout(FL_DocLayout* pLayout, PL_StruxDocHandle sdh, PT_AttrPropIndex ap, fl_ContainerLayout * pMyContainerLayout);
	virtual ~fl_TableLayout();

	SectionType     	        getType(void) const { return m_iType; }

	virtual bool		        recalculateFields(UT_uint32 iUpdateCount);
	virtual bool 	            doclistener_changeStrux(const PX_ChangeRecord_StruxChange * pcrxc);
	virtual bool				doclistener_deleteStrux(const PX_ChangeRecord_Strux * pcrx);
	virtual bool                bl_doclistener_insertCell(fl_ContainerLayout* pCell,
											  const PX_ChangeRecord_Strux * pcrx,
											  PL_StruxDocHandle sdh,
											  PL_ListenerId lid,
											  void (* pfnBindHandles)(PL_StruxDocHandle sdhNew,
																	  PL_ListenerId lid,
																	  PL_StruxFmtHandle sfhNew));
	virtual bool                bl_doclistener_insertBlock(fl_ContainerLayout* pCell,
											  const PX_ChangeRecord_Strux * pcrx,
											  PL_StruxDocHandle sdh,
											  PL_ListenerId lid,
											  void (* pfnBindHandles)(PL_StruxDocHandle sdhNew,
																	  PL_ListenerId lid,
																	  PL_StruxFmtHandle sfhNew));

	virtual bool                bl_doclistener_insertEndTable(fl_ContainerLayout*,
											  const PX_ChangeRecord_Strux * pcrx,
											  PL_StruxDocHandle sdh,
											  PL_ListenerId lid,
											  void (* pfnBindHandles)(PL_StruxDocHandle sdhNew,
																	  PL_ListenerId lid,
																	  PL_StruxFmtHandle sfhNew));

	virtual bool               bl_doclistener_insertTable( const PX_ChangeRecord_Strux * pcrx,
											   SectionType iType,
											   PL_StruxDocHandle sdh,
											   PL_ListenerId lid,
											   void (* pfnBindHandles)(PL_StruxDocHandle sdhNew,
																	   PL_ListenerId lid,
																	   PL_StruxFmtHandle sfhNew));

#ifdef FMT_TEST
	virtual void		__dump(FILE * fp) const;
#endif
	void                        setTableContainerProperties(fp_TableContainer * pTab);
	virtual void		        format(void);
	void                        attachCell(fl_ContainerLayout * pCell);
	void                        createTableContainer(void);
	void                        insertTableContainer(fp_TableContainer * pNewTab);
	virtual void		        updateLayout(void);
	void		                updateTable(void);
	virtual void                collapse(void);
	virtual void                markAllRunsDirty(void);
	virtual PT_DocPosition      getPosition(bool bActualBlockPosition = false) const;
	virtual void		        redrawUpdate(void);
	virtual fp_Container*		getNewContainer(fp_Container * pFirstContainer = NULL);
	virtual fl_SectionLayout *  getSectionLayout(void)  const;

	void                        markForRebuild(void) { m_bNeedsRebuild = true;}
	void                        clearRebuild(void) { m_bNeedsRebuild = false;}
	bool                        needsRebuild(void) const { return m_bNeedsRebuild;}
    void                        markForReformat(void) { m_bNeedsReformat = true;}
    bool                        needsReFormat(void) const { return m_bNeedsReformat;}

	UT_sint32                getLeftOffset(void) const;

#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
 UT_sint32                   getLeftOffsetInLayoutUnits(void) const;
#endif
UT_sint32                    getRightOffset(void) const;
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
UT_sint32                    getRightOffsetInLayoutUnits(void) const;
#endif
	UT_sint32                getTopOffset(void) const;
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
 UT_sint32                   getTopOffsetInLayoutUnits(void) const;
#endif
UT_sint32                    getBottomOffset(void) const;
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
UT_sint32                    getBottomOffsetInLayoutUnits(void) const;
#endif
	bool                     isDirty(void) const
		{ return m_bIsDirty;}
	void                     setDirty(void)
		{ m_bIsDirty = true;}
	UT_sint32                getLineThickness(void) const;
	UT_sint32                getColSpacing(void) const;
	UT_sint32                getRowSpacing(void) const;
	UT_sint32                getLeftColPos(void) const
		{ return m_iLeftColPos;}
	const UT_Vector *        getVecColProps(void) const
		{ return &m_vecColProps;}
	const UT_Vector *        getVecRowProps(void) const
		{ return &m_vecRowProps;}

protected:
	virtual void		        _lookupProperties(void);
	void				        _purgeLayout();
private:
	bool                   m_bNeedsRebuild;
	FL_TableJustification  m_iJustification;
	UT_sint32              m_iLeftOffset;
	double                 m_dLeftOffsetUserUnits;
	UT_sint32              m_iRightOffset;
	double                 m_dRightOffsetUserUnits;
	UT_sint32              m_iTopOffset;
	double                 m_dTopOffsetUserUnits;
	UT_sint32              m_iBottomOffset;
	double                 m_dBottomOffsetUserUnits;

#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
	UT_sint32              m_iLeftOffsetLayoutUnits;
	UT_sint32              m_iRightOffsetLayoutUnits;
	UT_sint32              m_iTopOffsetLayoutUnits;
	UT_sint32              m_iBottomOffsetLayoutUnits;
#endif
	
	bool                   m_bIsHomogeneous;
	bool                   m_bSameRowOnTopOfPage;
	UT_sint32              m_iRowNumberForTop;
	UT_sint32              m_iNumberOfRows;
	UT_sint32              m_iNumberOfColumns;
	bool                   m_bColumnsPositionedOnPage;
	bool                   m_bRowsPositionedOnPage;
	bool                   m_bIsDirty;
	bool                   m_bDontImmediatelyLayout;
	UT_sint32              m_iLineThickness;
	UT_sint32              m_iColSpacing;
	UT_sint32              m_iRowSpacing;
	UT_sint32              m_iLeftColPos;
	bool                   m_bRecursiveFormat;
	UT_Vector              m_vecColProps;
	UT_Vector              m_vecRowProps;
};


class ABI_EXPORT fl_CellLayout : public fl_SectionLayout
{
	friend class fl_DocListener;
	friend class fp_TableContainer;
	friend class fp_CellContainer;
public:
	fl_CellLayout(FL_DocLayout* pLayout, PL_StruxDocHandle sdh, PT_AttrPropIndex ap, fl_ContainerLayout * pMyContainerLayout);
	virtual ~fl_CellLayout();

	void            checkAndAdjustCellSize(void);
	virtual bool 	doclistener_changeStrux(const PX_ChangeRecord_StruxChange * pcrxc);
	virtual bool    doclistener_deleteStrux(const PX_ChangeRecord_Strux * pcrx);
	virtual bool    bl_doclistener_insertCell(fl_ContainerLayout* pCell,
											  const PX_ChangeRecord_Strux * pcrx,
											  PL_StruxDocHandle sdh,
											  PL_ListenerId lid,
											  void (* pfnBindHandles)(PL_StruxDocHandle sdhNew,
																	  PL_ListenerId lid,
																	  PL_StruxFmtHandle sfhNew));
	virtual bool    bl_doclistener_insertEndCell(fl_ContainerLayout*,
											  const PX_ChangeRecord_Strux * pcrx,
											  PL_StruxDocHandle sdh,
											  PL_ListenerId lid,
											  void (* pfnBindHandles)(PL_StruxDocHandle sdhNew,
																	  PL_ListenerId lid,
																	  PL_StruxFmtHandle sfhNew));

	void                     setCellContainerProperties(fp_CellContainer * pCell);
	void                     createCellContainer(void);
	virtual void		     format(void);
	virtual void		     updateLayout(void);
	virtual void             collapse(void);
	virtual void             markAllRunsDirty(void);
	virtual fl_SectionLayout *  getSectionLayout(void)  const;
	bool                     recalculateFields(UT_uint32 iUpdateCount);
	virtual void		     redrawUpdate(void);
	virtual fp_Container*	 getNewContainer(fp_Container * pFirstContainer = NULL);
#ifdef FMT_TEST
	void				     __dump(FILE * fp) const;
#endif

	UT_sint32                getLeftOffset(void) const;
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
 UT_sint32                   getLeftOffsetInLayoutUnits(void) const;
#endif
UT_sint32                    getRightOffset(void) const;
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
UT_sint32                    getRightOffsetInLayoutUnits(void) const;
#endif
	UT_sint32                getTopOffset(void) const;
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
 UT_sint32                   getTopOffsetInLayoutUnits(void) const;
#endif
UT_sint32                    getBottomOffset(void) const;
#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
UT_sint32                    getBottomOffsetInLayoutUnits(void) const;
#endif
protected:
	virtual void		     _lookupProperties(void);
	virtual void             _purgeLayout(void);
private:
	bool                   m_bNeedsRebuild;
	UT_sint32              m_iLeftOffset;
	double                 m_dLeftOffsetUserUnits;
	UT_sint32              m_iRightOffset;
	double                 m_dRightOffsetUserUnits;
	UT_sint32              m_iTopOffset;
	double                 m_dTopOffsetUserUnits;
	UT_sint32              m_iBottomOffset;
	double                 m_dBottomOffsetUserUnits;

#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
	UT_sint32              m_iLeftOffsetLayoutUnits;
	UT_sint32              m_iRightOffsetLayoutUnits;
	UT_sint32              m_iTopOffsetLayoutUnits;
	UT_sint32              m_iBottomOffsetLayoutUnits;
#endif
	
	UT_sint32              m_iLeftAttach;
	UT_sint32              m_iRightAttach;
	UT_sint32              m_iTopAttach;
	UT_sint32              m_iBottomAttach;
	
	bool                   m_bCellPositionedOnPage;
	UT_sint32              m_iCellHeight;

// Line properties
	UT_RGBColor            m_cLeftColor;
	UT_RGBColor            m_cRightColor;
	UT_RGBColor            m_cTopColor;
	UT_RGBColor            m_cBottomColor;	
	UT_sint32              m_iLeftStyle;
	UT_sint32              m_iRightStyle;
	UT_sint32              m_iTopStyle;
	UT_sint32              m_iBottomStyle;
	
	UT_sint32              m_iLeftLineThickness;
	UT_sint32              m_iTopLineThickness;
	UT_sint32              m_iRightLineThickness;
	UT_sint32              m_iBottomLineThickness;

// Background properties
	UT_RGBColor            m_cBgColor;
	UT_sint32              m_iBgStyle;

	void                   _updateCell(void);
	void                   _localCollapse();
};

///
/// Define he current supported background fill types
/// DO NOT CHANGE THE EXISTING NUMBERS, EVER!
/// You can add new styles as you please
///
#define FS_OFF	0		// No fill style
#define FS_FILL	1		// Solid fill style
// add more fill styles here

///
/// Define the current supported line style types
/// DO NOT CHANGE THE NUMBERS, EVER!
/// You can add new styles as you please
///
#define LS_OFF		0	// No line style, which means no line is drawn
#define LS_NORMAL	1	// A normal solid line
// add more line styles here

#endif /* TABLELAYOUT_H */

