/* TAbiWord -- Ink support for AbiWord
* Copyright (C) 2003 Kevin Conroy
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


#ifndef GR_WIN32STROKE_H
#define GR_WIN32STROKE_H

#include "xav_View.h"
#include "fv_View.h"
#include "gr_DrawArgs.h"
#include "gr_Graphics.h"
#include "ut_types.h"
#include "math.h"

#ifndef PI
#define PI 3.1415926538
#endif

// ink related includes
#include "gr_Win32Tablet.h"

// defines the size of the sliding window to use when calculating
// the insertion point using the Law Of Cosines method; MUST BE ODD!!!
// KMC: We have found that a window size of 5, 7, 9, 11, or 13 is
// sufficient for determining the insertion point. Erroring on a slightly
// larger window seems to improve the calculation.
// KMC 10 Nov 2003: Will set window size to 11 after several tests
// using the StrokeDataViewer spike in .NET to test various sizes; 11 seems good
#define WINDOW_SIZE 17 // <-- THIS NUMBER MUST BE ODD

// flag if we should draw the bounding box of the stroke
#define DRAW_BOUNDING_BOX 0

// flag if we should draw the insertion point of the stroke
#define DRAW_INSERTION_POINT 0

class GR_Win32InkOverlay;
class GR_Win32Ink;

// this is a wrapper for the IInkStrokeDisp object which we are accessing via COM/COM+ (not sure which)
class ABI_EXPORT GR_Win32Stroke
{
public:
	GR_Win32Stroke(IInkStrokeDisp *pIInkStrokeDisp);  
	~GR_Win32Stroke();

	InkPoint			getInsertionPoint();

	InkPoint			getStartPoint();	
	InkPoint			getEndPoint();
	InkPoint			getNthPoint(long index);
	long				getPointCount();
	
	XML_Char *			getXmlId();

	ScreenRect	getScreenRectange(GR_Win32InkOverlay *pInkOverlay, GR_Graphics *pG);

	void				draw(GR_Graphics *pG, long HDC, IInkRenderer *pInkRenderer);

	bool				reflow(dg_DrawArgs *pDA);

	ScreenPoint	getCurrentScreenPosition();
	void				setCurrentScreenPosition(ScreenPoint screenPoint);
	bool				hasCurrentScreenPosition();

	InkPoint		getBaselineInkOffset();
	void				setBaselineInkOffset(InkPoint inkPoint);
	bool				hasBaselineInkOffset();

	int					getGUID();
	void				setGUID(int guid);
	bool				hasGUID();

	GR_Win32Ink	*		getInk();


	GR_Win32Stroke *	clipStroke(GR_Graphics *pG, ScreenRect clippingRegion);
	GR_Win32Stroke *	clipStroke(InkRect clippingRegion);

	GR_Win32Stroke *	clone();

	void				print();

	void	removeFromScreen();

	IInkDrawingAttributes * getDrawingAttributes();
	void					setDrawingAttributes(IInkDrawingAttributes * drawAttrs);
protected:
	long					_getId();

	InkPoint *		_getPoints(long *numPoints);

	// various insertion point algorithms
	InkPoint			_getInsertionPoint_LastPoint();
	InkPoint			_getInsertionPoint_LawOfCosines(int window_size);

	SAFEARRAY *			_getPointSafeArray();

	InkPoint			_calculateOffset(InkPoint currentInkPosition, InkPoint drawingInkPosition);

	InkPoint			_midpoint(InkPoint p1, InkPoint p2);
	double				_distance(InkPoint p1, InkPoint p2);
	double				_calculateAngle(InkPoint A, InkPoint B, InkPoint C);


	VARIANT				_getExtendedProperty(CComBSTR guid); 
	void				_setExtendedProperty(CComBSTR guid, VARIANT value); 
	bool				_hasExtendedProperty(CComBSTR guid);
private:
	// stores the pointer to the IInkStrokeDisp that we're wrapping
	IInkStrokeDisp *m_pIInkStrokeDisp;

	// the array of points associated with this stroke as returned by the underlying
	// IInkStrokeDisp; keep a pointer to it so we can use the lazy loader pattern
	SAFEARRAY * _psa;
};

#endif /* GR_WIN32STROKE_H */

