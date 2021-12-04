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

#ifndef GR_WIN32INKOVERLAY_H
#define GR_WIN32INKOVERLAY_H

//include "ap_Frame.h"
//include "xap_Win32FrameImpl.h"
//include "ap_FrameData.h"

#include "xav_View.h"
#include "xap_App.h"
#include "fv_View.h"
#include "gr_DrawArgs.h"
#include "gr_Graphics.h"
#include "ut_types.h"

// the TabletPC Ink support libraries included with the SDK
#include "gr_Win32Tablet.h"
#include "gr_Win32InkOverlayEvents.h"
#include "gr_Win32Ink.h"
#include "gr_Win32Stroke.h"

typedef enum  {
	Black = RGB(0,0,0),
	Blue = RGB(0,0,255),
	Red = RGB(255,0,0),
	Yellow = RGB(255,255,0),
	Orange = RGB(255,153,0),
	Green = RGB(0,153,33)
} InkColor;

typedef enum {
	Smallest = 25,
	Small = 40,
	Medium = 75,
	Large = 150,
	Largest = 300
} InkWidth;

typedef enum {
  Ballpoint = 1,
  Highlighter = 2,
  Marker = 3
} PenType;

// this is a wrapper for the IInkOverlay object which we are accessing via COM/COM+ (not sure which)
class ABI_EXPORT GR_Win32InkOverlay
{
  public:
    GR_Win32InkOverlay(HWND hwndDocumentToBindTo);  // probably want to require something here - like the HWND of the window
    ~GR_Win32InkOverlay(void);

		void SetEventSink(InkOverlayEvents *handler); 

		// reflow
		bool						drawStroke(dg_DrawArgs *pDA, const XML_Char *strStrokeId);
		bool						drawStroke(dg_DrawArgs *pDA, GR_Win32Stroke *ptrStroke);

		// used by Run::clear
		ScreenRect	getScreenRectangle(GR_Graphics *pG, const XML_Char *strStrokeId);
		ScreenRect	getScreenRectangle(GR_Graphics *pG, GR_Win32Stroke *ptrStroke);

		void						draw(long HDC);

		// doesn't reflow, but moves the ink space
		void						scrollInk(GR_Graphics *pG, UT_sint32 xOffset, UT_sint32 yOffset);

		// covert from ink space to screen space
		ScreenPoint			convertToScreenPoint(GR_Graphics *pGR, InkPoint &inkPoint);
		InkPoint				convertToInkPoint(GR_Graphics *pGR, ScreenPoint &screenPoint);

    // gets and sets the current zoom level of this ink overlay
    float           getZoomLevel();
    void            setZoomLevel(float zoomLevel);

		void						deserializeInk(const XML_Char *strInk);

		// color related
		void						setColor(InkColor color);
		const char *		getColorName();

		// width related
		void						setWidth(InkWidth width);
		const char *		getWidthName();		

    // pen type related
    void            setPenType(PenType type);
    const char *		getPenTypeName();

		void						setAntiAliased(bool bolAntiAlised);
		void						setAutoRedraw(bool bolAutoRedraw);

		void						enableInkOverlay();
		void						disableInkOverlay();
		bool						isEnabled();
		
		GR_Win32Ink *   getInk();
		IInkRenderer *  getInkRenderer() { return _getInkRenderer(); };

		void						clearScreen();

  protected:
    virtual void    _initialize();
		virtual void		_comConstructor(IInkOverlay *&pIInkOverlay);

		IInkDrawingAttributes * _getDrawingAttributes();
		void _setDrawingAttributes(IInkDrawingAttributes *inkAttributes);

    bool            _isInkOS();
      
		void						_setInk(IInkDisp *pInk);
		IInkDisp *			_deserializeInk(const XML_Char *strInk);
  /***************************************/

 private:
    void           _updateZoomAndScroll();

		IInkRenderer * _getInkRenderer();
    void           _setInkRenderer(IInkRenderer *pIInkRenderer);

 private:
    /*    KMC, Ink    Why I'm Using an IInkOverlay object    From "Building Tablet PC Applications", Jarrett, Rob and Su, Philip, Chapter 4
    _When Ink Is Not Enough_    The InkCollector class is great at providing real-time ink, but oftentimes you’ll want to give     your users the ability to select, manipulate, and erase the ink they’ve drawn. InkCollector doesn’t     have any support for this, but it’s definitely possible to augment InkCollector and write all that     functionality yourself. However, that would be a rather time-consuming task, and quite a wasteful     one—especially if only standard ink interaction behavior was desired! Tablet PC developers everywhere    would be reinventing the wheel, which isn’t exactly an indicator of a great software platform.    Fortunately, the Tablet PC Platform SDK provides a class named InkOverlay that implements common    ink-interaction behaviors—it supports selecting, moving, resizing, and erasing ink, as well as all    the real-time inking capability that InkCollector has.    NOTE    InkOverlay is a proper superset of the InkCollector—an instance of InkCollector can be replaced by 
    an instance of InkOverlay and it will always function identically.
    */

    // START PRIVATE INK DATA MEMBERS
    //IInkCollector   *pIInkCollector; // ink collector
    IInkOverlay    *m_pIInkOverlay;
		char					 *m_pColor;
		char					 *m_pWidth;
    char           *m_pPenType;
    // END PRIVATE INK DATA MEMEBERS

    // OTHER POTENTIALLY USEFUL PRIVATE DATA MEMBERS
    HWND						m_hwndFrame;
    HWND						m_hwndDocument;	/* the actual document window */

    // current zoom level (start off at 100%)
    float           m_zoomLevel;


		// UNUSED FUNCTIONS (although potential useful)
		// This code *works* but for one reason or another
		// each function below is no longer used to do anything
		// useful. In an effort to keep a clean namespace, I have
		// commented it out. If you are developing new functions
		// for TAbiWord that need Ink support, check out the functions
		// below to make sure that you're not reinventing the wheel.
		//    -- Kevin Conroy, 11 November 2003
		// return ink in a persisted Xml string
		//DEPRECATED char *          collectInk(GR_Graphics *pGR, int screenX, int screenY);    
		// pass in some persisted ink and watch it do it's thing!
		//DEPRECATED void            drawInk(dg_DrawArgs *pDA, const XML_Char *strInk);
		// let's apply some transformations man
		//DEPRECATED void            zoomInk(AV_View *pView);

		// will help set what area is inkable
		//DEPRECATED void            resizeInkAreaToDocument(FV_View *pView);

		// will help use move the ink properly
		//DEPRECATED void            setExtendedProperty(CComBSTR guid, VARIANT value);
		//DEPRECATED void            setExtendedProperty(CComBSTR guid, VARIANT value, IInkDisp *ptrInk);
		//DEPRECATED VARIANT         getExtendedProperty(CComBSTR guid);    
		//DEPRECATED VARIANT         getExtendedProperty(CComBSTR guid, IInkDisp *ptrInk);

		//DEPRECATED void						setInkSpacePosition(long x, long y);
		//DEPRECATED void						setInkSpacePosition(long x, long y, IInkDisp *pInk);

		//DEPRECATED void						getInkSpacePosition(long &x, long &y);
		//DEPRECATED void						getInkSpacePosition(long &x, long &y, IInkDisp *pInk);

		//DEPRECATED void						pixelToInkSpace(GR_Graphics *pGR, long &x, long &y);

		//DEPRECATED char *					serializeInk();
		//DEPRECATED char *					serializeInk(IInkDisp *ptrInk);

		//DEPRECATED IInkDisp *			_getCurrentInk();		
		// manually refresh
    // void            refreshWindow(HWND hwnd);
		//DEPRECATED bool            _isInkRecognizerOS();
};

#endif /* GR_WIN32INKOVERLAY_H */

