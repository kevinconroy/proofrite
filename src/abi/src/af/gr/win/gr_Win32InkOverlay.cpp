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

#define WIN32_LEAN_AND_MEAN
#define NOWINABLE
#define NOMETAFILE
#define NOSERVICE
#define NOIME
#define NOMCX
#include <windows.h>

#include "gr_Win32Graphics.h"
#include "gr_Win32Image.h"
#include <xap_Win32App.h>

#include <xap_Win32Res_Cursors.rc2>

#include "ut_debugmsg.h"
#include "ut_assert.h"
#include "ut_string.h"
#include "ut_Win32OS.h"

#include "gr_Win32InkOverlay.h"

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: ctor
* Purpose: Initalize the class with all of the appropriate variables
* TODO : probably want to require something here - like the HWND of the window
****************************************************************************/
GR_Win32InkOverlay::GR_Win32InkOverlay(HWND hwndDocumentToBindTo) {
	this->m_hwndDocument = hwndDocumentToBindTo;

	this->_initialize();
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: dtor
* Purpose: Takes in an XML string from the lower levels and draws it to the ink collector
* Comments: Pass in some persisted ink and watch it do it's thing!
****************************************************************************/
GR_Win32InkOverlay::~GR_Win32InkOverlay(void) {
	//TODO: add destructor call to m_pIInkOverlay
	this->m_pIInkOverlay->Release();
	this->m_pIInkOverlay = 0;
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: SetEventSink
* Purpose: Tells the COM InkCollector/InkOverlay where to send its events
****************************************************************************/
void GR_Win32InkOverlay::SetEventSink(InkOverlayEvents *handler) {
	HRESULT hrInk = S_OK;

	// initalize it for event forwarding
	hrInk = handler->Init();
	UT_ASSERT(SUCCEEDED(hrInk));

	// hook it up to the ink overlay we're wrapping
	hrInk = handler->AdviseInkOverlay(this->m_pIInkOverlay);
	UT_ASSERT(SUCCEEDED(hrInk));
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: _comConstructor
* Purpose: Wrapper for the call to the COM constructor for the TabletPC object
****************************************************************************/
void GR_Win32InkOverlay::_comConstructor(IInkOverlay * &pIInkOverlay) {
	HRESULT hrInk = S_OK;

	// make the ink overlay
	hrInk = CoCreateInstance(CLSID_InkOverlay, NULL, CLSCTX_INPROC_SERVER, 
		IID_IInkOverlay, 
		(void **) &pIInkOverlay);

	UT_ASSERT(SUCCEEDED(hrInk));
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: refresh
* Purpose: Invalidates the ink layer in the hopes that it will correct our refresh issues
****************************************************************************/
void GR_Win32InkOverlay::draw(long HDC) {
	HRESULT hr = S_OK;

	// redraw all of the ink
	this->getInk()->draw(HDC, this->getInkRenderer());

	/*
	IInkRectangle *pInkRectangle = 0;

	// make a new ink rectangle
	hr = CoCreateInstance(CLSID_InkRectangle, NULL, CLSCTX_INPROC_SERVER, 
	IID_IInkRectangle, 
	(void **) &pInkRectangle);
	UT_ASSERT(SUCCEEDED(hr));

	// figure out how large of an area we're covering
	this->m_pIInkOverlay->GetWindowInputRectangle(&pInkRectangle);
	UT_ASSERT(SUCCEEDED(hr));

	// redraw the whole bloody thing
	hr = this->m_pIInkOverlay->Draw(pInkRectangle);
	UT_ASSERT(SUCCEEDED(hr));
	*/

	// get the renderer
	// IInkRenderer *pRenderer = this->getInkRenderer();
	// redraw all of the strokes
	// pRenderer->(hDC, this->getInk()->getStrokes());	
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: _initalize
* Purpose: To create a new instance of an ink collector or an ink overlay 
* Comments: Still debating if a collector or overlay is better (depends on refresh rates)
****************************************************************************/
void GR_Win32InkOverlay::_initialize() {
	// make sure we've got the handle of the window to bind this inkoverlay to
	UT_ASSERT(this->m_hwndDocument != 0);

	// set zoom level to 100% by default
	m_zoomLevel = 1;

	// zero it out
	m_pColor = new char[10];
	strcpy(m_pColor, "\0\0\0\0\0\0\0\0\0\0");
	m_pWidth = new char[10];
	strcpy(m_pWidth, "\0\0\0\0\0\0\0\0\0\0");
	m_pPenType = new char[15];
	strcpy(m_pWidth, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0");

	// first make sure that we support ink on the current system
	if(this->_isInkOS()) {
		// will be used to track the ink collector/overlay
		HRESULT hrInk;

		_comConstructor(m_pIInkOverlay);

		// Tell InkCollector the window to collect ink in (should be the current frame/document)
		hrInk = m_pIInkOverlay->put_hWnd((long)m_hwndDocument);
		UT_ASSERT(SUCCEEDED(hrInk));

		// set the pen type to ball point
		setPenType(Ballpoint);

		// set the ink color to black
		setColor(Red);

		// set the width of the ink to medium
		setWidth(Medium);

		// turn on antialised
		setAntiAliased(true);

		InkOverlayAttachMode mode = IOAM_Behind; // IOAM_InFront;
		this->m_pIInkOverlay->put_AttachMode(mode);    


		/*
		this->m_pIInkOverlay->put_CollectionMode(ICM_InkOnly);

		VARIANT packetGUID;
		SAFEARRAY* pArray = ::SafeArrayCreateVector( VT_UI1, 0, 2);
		if ( pArray == NULL ) return 0; // E_FAIL;

		::SafeArrayPutElement(psa,&i,bstr_X.m_str);		
		::SafeArrayPutElement(psa,&i,bstr_X.m_str);

		CComVariant var;
		var.vt = VT_BSTR|VT_ARRAY;
		var.parray = pArray;

		LPBYTE pArrayData = NULL;
		hr = ::SafeArrayAccessData(pArray,(void**) &pArrayData);
		UT_ASSERT(SUCCEEDED(hr));
		this->m_pIInkOverlay->put_DesiredPacketDescription(packetGUIDs);
		*/

		// turn on autodraw
		setAutoRedraw(false);

		// enable the ink overlay
		enableInkOverlay();

		// debug message
		UT_DEBUGMSG(("Creating ink collector\n"));
	}
	else {
		UT_DEBUGMSG(("Cannot create ink support; Microsoft TabletPC Runtime missing.\n"));
	}
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: _getDrawingAttributes
* Purpose: Returns a pointer the IInkDrawingAttributes for the current ink overlay
****************************************************************************/
IInkDrawingAttributes * GR_Win32InkOverlay::_getDrawingAttributes() {
	HRESULT hrInk = S_OK;

	// pointer to return
	IInkDrawingAttributes *inkAttributes = 0;

	// get the ink attributes
	hrInk = m_pIInkOverlay->get_DefaultDrawingAttributes(&inkAttributes);
	UT_ASSERT(SUCCEEDED(hrInk));

	return inkAttributes;
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: _setDrawingAttributes
* Purpose: Sets the pointer to the IInkDrawingAttributes for the current ink overlay
****************************************************************************/
void GR_Win32InkOverlay::_setDrawingAttributes(IInkDrawingAttributes *inkAttributes) {
	HRESULT hrInk = S_OK;

	// set the ink attributes
	m_pIInkOverlay->putref_DefaultDrawingAttributes(inkAttributes);
	UT_ASSERT(SUCCEEDED(hrInk));
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: setColor
* Purpose: Sets the color of the current ink collector
****************************************************************************/
void GR_Win32InkOverlay::setColor(InkColor color) {
	HRESULT hrInk = S_OK;

	// get a pointer to the IInkDrawingAttributes for the current overlay
	IInkDrawingAttributes *inkAttributes = this->_getDrawingAttributes();

	// set the color
	hrInk = inkAttributes->put_Color(color);
	UT_ASSERT(SUCCEEDED(hrInk));

	// save the drawing attributes
	this->_setDrawingAttributes(inkAttributes);

	// update the color string
	if(color == Black) {
		strcpy(m_pColor, "Black");
	}
	else if(color == Red) {
		strcpy(m_pColor, "Red");
	}
	else if(color == Blue) {
		strcpy(m_pColor, "Blue");
	}
	else if(color == Green) {
		strcpy(m_pColor, "Green");
	}
	else if(color == Yellow) {
		strcpy(m_pColor, "Yellow");
	}
	else if(color == Orange) {
		strcpy(m_pColor, "Orange");
	}

}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: getColorName
* Purpose: Gets the name of the current color of the ink collector
****************************************************************************/
const char * GR_Win32InkOverlay::getColorName() {
	return (this->m_pColor);
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: setWidth
* Purpose: Sets the width of the current ink collector
****************************************************************************/
void GR_Win32InkOverlay::setWidth(InkWidth width) {
	HRESULT hrInk = S_OK;

	// get a pointer to the IInkDrawingAttributes for the current overlay
	IInkDrawingAttributes *inkAttributes = this->_getDrawingAttributes();

	// set the color
	if(strcmp(this->getPenTypeName(), "Highlighter") == 0) {
		hrInk = inkAttributes->put_Height((float)width * 5);
		UT_ASSERT(SUCCEEDED(hrInk));

		hrInk = inkAttributes->put_Width((float)sqrt((float)width));
		UT_ASSERT(SUCCEEDED(hrInk));
	}
	else if(strcmp(this->getPenTypeName(), "Ballpoint") == 0) {
		hrInk = inkAttributes->put_Width((float)width);
		UT_ASSERT(SUCCEEDED(hrInk));

		hrInk = inkAttributes->put_Height((float)width);
		UT_ASSERT(SUCCEEDED(hrInk));
	}
	else if(strcmp(this->getPenTypeName(), "Marker") == 0) {
		hrInk = inkAttributes->put_Width((float)width * 2);
		UT_ASSERT(SUCCEEDED(hrInk));

		hrInk = inkAttributes->put_Height((float)width * 2);
		UT_ASSERT(SUCCEEDED(hrInk));
	}

	// save the drawing attributes
	this->_setDrawingAttributes(inkAttributes);

	// update the color string
	if(width == Smallest) {
		strcpy(m_pWidth, "Smallest");
	}
	else if(width == Small) {
		strcpy(m_pWidth, "Small");
	}
	else if(width == Medium) {
		strcpy(m_pWidth, "Medium");
	}
	else if(width == Large) {
		strcpy(m_pWidth, "Large");
	}
	else if(width == Largest) {
		strcpy(m_pWidth, "Largest");
	}
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: getWidthName
* Purpose: Gets the name of the current width of the ink collector
****************************************************************************/
const char * GR_Win32InkOverlay::getWidthName() {
	return (this->m_pWidth);
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: setPenType
* Purpose: Sets the pen type of the current ink collector
****************************************************************************/
void GR_Win32InkOverlay::setPenType(PenType type) {
	HRESULT hrInk = S_OK;

	// get a pointer to the IInkDrawingAttributes for the current overlay
	IInkDrawingAttributes *inkAttributes = this->_getDrawingAttributes();

	// update the pen type string and send the pent tip to the draw atts
	if(type == Ballpoint) {
		hrInk = inkAttributes->put_PenTip(IPT_Ball);
		UT_ASSERT(SUCCEEDED(hrInk));
		hrInk = inkAttributes->put_RasterOperation(IRO_CopyPen);
		UT_ASSERT(SUCCEEDED(hrInk));

		strcpy(m_pPenType, "Ballpoint");

		this->setColor(Red);
		this->setWidth(Medium);
	}
	else if(type == Highlighter) {
		hrInk = inkAttributes->put_PenTip(IPT_Rectangle);
		UT_ASSERT(SUCCEEDED(hrInk));
		// mask pen causes the ink that is drawn to appear underneath
		// of other ink
		// (windows journal uses this to do highlighting)
		hrInk = inkAttributes->put_RasterOperation(IRO_MaskPen);
		UT_ASSERT(SUCCEEDED(hrInk));

		strcpy(m_pPenType, "Highlighter");

		this->setColor(Yellow);
		this->setWidth(Medium);
	}
	else if(type == Marker) {
		hrInk = inkAttributes->put_PenTip(IPT_Ball);
		UT_ASSERT(SUCCEEDED(hrInk));
		hrInk = inkAttributes->put_RasterOperation(IRO_CopyPen);
		UT_ASSERT(SUCCEEDED(hrInk));

		strcpy(m_pPenType, "Marker");

		this->setColor(Black);
		this->setWidth(Medium);
	}

	// save the drawing attributes
	this->_setDrawingAttributes(inkAttributes);

}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: getPenTypeName
* Purpose: Gets the name of the current pen type of the ink collector
****************************************************************************/
const char * GR_Win32InkOverlay::getPenTypeName() {
	return (this->m_pPenType);
}



/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: setAntiAliased
* Purpose: Sets the color of the current ink collector
****************************************************************************/
void GR_Win32InkOverlay::setAntiAliased(bool bolAntiAlised) {
	HRESULT hrInk = S_OK;

	// need to pass it in as a variant!
	VARIANT_BOOL varAntiAlised = VARIANT_FALSE;

	// see if we need to reset it to true
	if(bolAntiAlised) {
		varAntiAlised = VARIANT_TRUE;
	}

	// get a pointer to the IInkDrawingAttributes for the current overlay
	IInkDrawingAttributes *inkAttributes = this->_getDrawingAttributes();

	// set the antialined
	hrInk = inkAttributes->put_AntiAliased(varAntiAlised); // turn on anti-aliased
	UT_ASSERT(SUCCEEDED(hrInk));

	// save the drawing attributes
	this->_setDrawingAttributes(inkAttributes);
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: setAutoRedraw
* Purpose: Determines if the ink overlay automatically redraws itself when the
*   host window becomes invalidated
****************************************************************************/
void GR_Win32InkOverlay::setAutoRedraw(bool bolAutoRedraw) {
	HRESULT hrInk = S_OK;

	// need to pass it in as a variant!
	VARIANT_BOOL varAutoRedraw = VARIANT_FALSE;

	// see if we need to reset it to true
	if(bolAutoRedraw) {
		varAutoRedraw = VARIANT_TRUE;
	}

	// whether to redraw currently captured ink when the host window gets invalidated
	hrInk = m_pIInkOverlay->put_AutoRedraw(varAutoRedraw);    
	UT_ASSERT(SUCCEEDED(hrInk));
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: enableInkOverlay
* Purpose: Enables ink collection
****************************************************************************/
void GR_Win32InkOverlay::enableInkOverlay() {
	HRESULT hrInk = S_OK;

	// whether to redraw currently captured ink when the host window gets invalidated
	hrInk = m_pIInkOverlay->put_Enabled(VARIANT_TRUE);    
	UT_ASSERT(SUCCEEDED(hrInk));
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: disableInkOverlay
* Purpose: Disables ink collection
****************************************************************************/
void GR_Win32InkOverlay::disableInkOverlay() {
	HRESULT hrInk = S_OK;

	// whether to redraw currently captured ink when the host window gets invalidated
	hrInk = m_pIInkOverlay->put_Enabled(VARIANT_FALSE);    
	UT_ASSERT(SUCCEEDED(hrInk));
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: isEnabled
* Purpose: Query to determine if ink overlay is enabled or not
****************************************************************************/
bool GR_Win32InkOverlay::isEnabled() {
	bool bolReturn = false;

	HRESULT hr = S_OK;

	VARIANT_BOOL bolCollecting = false;

	// see if ink overlay is enabled or not
	hr = this->m_pIInkOverlay->get_Enabled(&bolCollecting);
	UT_ASSERT(SUCCEEDED(hr));

	// if we are enabled, then we're collecting ink
	//if(bolCollecting != 0) {
	if(bolCollecting == VARIANT_TRUE) {
		return bolReturn = true;
	}

	return bolReturn;
}

/***************************************************************************
* Author: Sam George, Microsoft Corporation, added by Kevin M. Conroy (KMC)
* Function: _scrollInk
* Purpose: Scrolls the ink; This method is delegated responsiblity by 
*		GR_Win32Graphics::scroll. That is, whenever the AbiWord framework detects a scroll
*		event that needs to cause a call to the Win32 API through GR_Win32Graphics, we
*		forward the necessary information to this function to allow us to scroll the
*		ink overlay appropriately.
* Source: http://www.tabletpcdeveloper.com/content/whitepapers/inkchat/
****************************************************************************/
void GR_Win32InkOverlay::scrollInk(GR_Graphics *pG, UT_sint32 xOffset, UT_sint32 yOffset) {
	HRESULT hr = S_OK;

	UT_DEBUGMSG(("scroll ink layer %d horizontally and %d vertically\n", xOffset, yOffset));

	// get the current renderer
	IInkRenderer *ptrRenderer = this->_getInkRenderer();

	if(ptrRenderer != 0) {
		// first we create a new ink transform to use
		IInkTransform * pIInkTransform;

		// make a new transform to apply to the ink (do we want to make new or get it from the ink overlay?)
		hr = CoCreateInstance(CLSID_InkTransform, NULL, CLSCTX_INPROC_SERVER, 
			IID_IInkTransform, (void **) &pIInkTransform);

		// rather than make a new one, get the existing transform!!!
		//CComPtr<IInkTransform> pIInkTransform;

		hr = ptrRenderer->GetViewTransform(pIInkTransform); 
		UT_ASSERT(SUCCEEDED(hr));

		// Convert to ink space.  Since we are updating the view 
		// transform of the renderer, the origin of the ink coordinates 
		// may have moved relative to the screen.    
		ScreenPoint screenScrollOffset(xOffset, yOffset);
		InkPoint inkScrollOffset = this->convertToInkPoint(pG, screenScrollOffset);

		ScreenPoint screenOrigin(0, 0);
		InkPoint inkOrigin = this->convertToInkPoint(pG, screenOrigin);

		float horizontalTranslate = (float)(inkScrollOffset.x - inkOrigin.x);
		float verticalTranslate = (float)(inkScrollOffset.y - inkOrigin.y);

		UT_DEBUGMSG(("   transform: horzTrans[%f], vertTrans[%f]\n", horizontalTranslate, verticalTranslate));

		hr = pIInkTransform->Translate(horizontalTranslate, verticalTranslate);
		UT_ASSERT(SUCCEEDED(hr));

		/*
		// apply horizontal scroll
		hr = pIInkTransform->put_eDx((float)(inkScrollOffset.x - inkOrigin.x));
		UT_ASSERT(SUCCEEDED(hr));

		// apply vertical scroll
		hr = pIInkTransform->put_eDy((float)(inkScrollOffset.y - inkOrigin.y));
		UT_ASSERT(SUCCEEDED(hr));
		*/

		// Apply a translation transform to the ink	
		hr = ptrRenderer->SetViewTransform(pIInkTransform);
		UT_ASSERT(SUCCEEDED(hr));

		// set the current renderer back
		this->_setInkRenderer(ptrRenderer); 

		//this->disableInkOverlay();
		// redraw all of the strokes
		//this->clearScreen();
		//this->draw((long)((GR_Win32Graphics *)pG)->getHDC());
		//this->enableInkOverlay();

		// Let's not do GR_Win32Graphic's functionality!!!
		// HWND hWnd = ((GR_Win32Graphics *)pG)->getHwnd();	
		// We've moved the ink.  Make sure it gets repainted.
		// InvalidateRgn(hWnd, NULL, true);
		// UpdateWindow(hWnd);
	}
}


/***************************************************************************
* Author: Sam George, Microsoft Corporation, added by Kevin M. Conroy (KMC)
* Function: _isInkOS
* Purpose: Returns a bool signifying if the current system is capable of supporting ink
* Source: http://www.tabletpcdeveloper.com/content/whitepapers/inkchat/
****************************************************************************/
bool GR_Win32InkOverlay::_isInkOS(void) {
	bool                          InkEnabledOS;
	CComPtr<IInkOverlay>          spIInkOverlay;

	InkEnabledOS = false;
	// Create an InkOverlay object.
	HRESULT hr = spIInkOverlay.CoCreateInstance(CLSID_InkOverlay);
	if (SUCCEEDED(hr))
	{
		// InkOverlay object is present.  We can collect and render Ink
		InkEnabledOS = true;
	}

	return InkEnabledOS;
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: deserializeInk
* Purpose: Deserializes the specified ink string
****************************************************************************/
void GR_Win32InkOverlay::deserializeInk(const XML_Char *strInk) {
	IInkDisp * ptrInk = 0;

	// make sure we have ink to deseralize
	if(strInk) {
		ptrInk = this->_deserializeInk(strInk);

		// replace the current ink object
		this->_setInk(ptrInk);
	}

	return;
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: deserializeInk
* Purpose: Deserializes the specified ink string
****************************************************************************/
IInkDisp *	GR_Win32InkOverlay::_deserializeInk(const XML_Char *strInk) {
	HRESULT result = S_OK;

	// get the char * into a VARIANT

	DWORD dataSize;
	// ... assign the byte-size of the persistent data to dataSize
	dataSize = strlen(strInk) * sizeof(XML_Char);

	BYTE* pData = new BYTE[dataSize];
	// ... read the persistent data into the pData buffer here ...
	for(DWORD i = 0; i < dataSize; i++) {
		pData[i] = strInk[i];
	}

	IInkDisp *pInk;
	result = CoCreateInstance(CLSID_InkDisp, NULL, CLSCTX_INPROC_SERVER, IID_IInkDisp, (void **) &pInk);

	SAFEARRAY* pArray = ::SafeArrayCreateVector( VT_UI1, 0, dataSize);
	if ( pArray == NULL ) return 0; // E_FAIL;

	CComVariant serialData;
	serialData.vt = VT_ARRAY | VT_UI1;
	serialData.parray = pArray;

	HRESULT hr = S_OK;
	LPBYTE pArrayData = NULL;
	hr = ::SafeArrayAccessData(pArray,(void**) &pArrayData);
	if ( FAILED(hr) ) return 0; // hr;

	::CopyMemory(pArrayData, pData, dataSize);
	hr = ::SafeArrayUnaccessData(pArray);
	if ( FAILED(hr) ) return 0; // hr;

	hr = pInk->Load(serialData); // populate ink object from the persistent

	return pInk;
}


/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: _updateZoomAndScroll
* Purpose: Private helper method which construct an ink transformation matrix
*   and passed it to the ink overlay which use it to apply the correct transformations
*   to the ink that is currently being rendered
* Source: Based on the InkZoom::UpdateZoomAndScroll method found in InkZoom.cs as a part of the
*   "Ink Zoom" sample that comes with "Microsoft Tablet PC Platform SDK: Samples and Source Code"
*   The same sample notes the following fact:
*      "Renderer's view and object transforms are used to perform
*       zooming and scrolling.  The view transform applies to the 
*       points and pen width.  The object transform  applies 
*       only to the points.  Depending on whether the user has 
*       selected to apply the transform to pen width, update the 
*       view or object transform."
****************************************************************************/
void GR_Win32InkOverlay::_updateZoomAndScroll() {
	HRESULT hr = S_OK;

	// first we create a new ink transform to use
	IInkTransform *pIInkTransform = 0;

	// make a new transform to apply to the ink (do we want to make new or get it from the ink overlay?)
	hr = CoCreateInstance(CLSID_InkTransform, NULL, CLSCTX_INPROC_SERVER, 
		IID_IInkTransform, (void **) &pIInkTransform);
	UT_ASSERT(SUCCEEDED(hr));

	// get the current renderer
	IInkRenderer *ptrRenderer = this->_getInkRenderer();

	// actually, let's not get the current ink transform
	// as we want to apply a clean zoom... may be a problem
	// (i.e. perhaps we should detect the old zoom level and use
	//  a factor from that because otherwise we might lose something)
	//hr = ptrRenderer->GetViewTransform(pIInkTransform);
	//UT_ASSERT(SUCCEEDED(hr));

	//if(FAILED(hr)) return;

	// set the scale multiplers equal to the current zoom level
	float horizontal = this->getZoomLevel();
	float vertical = this->getZoomLevel();

	// set the transform to be the current zoom
	hr = pIInkTransform->ScaleTransform(horizontal, vertical);
	UT_ASSERT(SUCCEEDED(hr));

	/*
	// get grey width and height (may be 0 if we're in ViewMode.VIEW_NORMAL)
	float greyWidth = 0;  // = 25; // only when ViewMode.VIEW_PREVIEW
	float greyHeight = 0; // = 25; // only when ViewMode.VIEW_PREVIEW

	// set the transform to account for the grey spacing on the top and left
	pIInkTransform->Translate(greyWidth, greyHeight);
	*/

	UT_DEBUGMSG(("applied zoom/scroll transformation\n"));

	// set the view transform (will update ink width as well)
	hr = ptrRenderer->SetViewTransform(pIInkTransform);
	UT_ASSERT(SUCCEEDED(hr));

	// set the current renderer back
	// this->_setInkRenderer(ptrRenderer); 

}


/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: _getInkRenderer
* Purpose: Accessor method for the current zoom level
****************************************************************************/
float GR_Win32InkOverlay::getZoomLevel() {
	float zoomLevel = 0;

	// set it to the private zoom level
	zoomLevel = this->m_zoomLevel;

	return zoomLevel;
}


/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: _getInkRenderer
* Purpose: Accessor method for the current zoom level
****************************************************************************/
void GR_Win32InkOverlay::setZoomLevel(float zoomLevel)
{
	// make sure it's a valid zoom level
	if(zoomLevel > 0) {
		// see if we actually have to change anything
		if(this->m_zoomLevel != zoomLevel) {
			// update private zoom level
			this->m_zoomLevel = zoomLevel;

			// refresh the ink renderer to reflect the new zoom level
			this->_updateZoomAndScroll();
		}
	}
}


/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: _getInkRenderer
* Purpose: Accessor method for the IInkRenderer associated with the current IInkOverlay
****************************************************************************/
IInkRenderer * GR_Win32InkOverlay::_getInkRenderer() {
	HRESULT hr = S_OK;

	IInkRenderer * pIInkRenderer = 0;

	if (this) {
		// make sure we have something
		if(this->m_pIInkOverlay != 0) {
			// get the ink renderer
			hr = this->m_pIInkOverlay->get_Renderer(&pIInkRenderer);

			// make sure it worked
			UT_ASSERT(SUCCEEDED(hr));
		}
	}

	return pIInkRenderer;
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: _setInkRenderer
* Purpose:  Accessor method for the IInkRenderer associated with the current IInkOverlay
****************************************************************************/
void GR_Win32InkOverlay::_setInkRenderer(IInkRenderer *pIInkRenderer) {
	HRESULT hr = S_OK;

	// make sure we have something
	if(this->m_pIInkOverlay != 0) {
		// get the ink renderer
		hr = this->m_pIInkOverlay->putref_Renderer(pIInkRenderer);

		// make sure it worked
		UT_ASSERT(SUCCEEDED(hr));
	}

	return;
}


/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: clearSceen
* Purpose: Clears all of the ink off of the ink collector
* Comments: May want to take in a rectangular area and have this
*  function (or a helper function) clear that arrea and then
*  redraw it (need to look into the AbiWord Windows rendering
*  process [talk to Sevior] and figure it all out...)
****************************************************************************/
void GR_Win32InkOverlay::clearScreen() {
	IInkDisp *pIInk = 0;
	HRESULT hr = S_OK;

	// KMC Please note:
	// this function should actually be named "get rid
	// of all of the ink from the old document so that
	// it doesn't appear on the new document"

	// get the ink object
	hr = this->m_pIInkOverlay->get_Ink(&pIInk);

	// clear the strokes
	hr = pIInk->DeleteStrokes();

	/*
	KMC This code actually does clear the screen without
	KMC deleting the strokes, however it seems that we
	KMC are only using clear screen when we want to load
	KMC a new document onto the ink space, therefore
	KMC we want to delete all of the existing strokes,
	KMC as show above.

	IInkRectangle *pInkRectangle = 0;

	// make a new ink rectangle
	hr = CoCreateInstance(CLSID_InkRectangle, NULL, CLSCTX_INPROC_SERVER, 
	IID_IInkRectangle, 
	(void **) &pInkRectangle);
	UT_ASSERT(SUCCEEDED(hr));

	// figure out how large of an area we're covering
	this->m_pIInkOverlay->GetWindowInputRectangle(&pInkRectangle);
	UT_ASSERT(SUCCEEDED(hr));

	// redraw the whole bloody thing
	hr = this->m_pIInkOverlay->Draw(pInkRectangle);
	UT_ASSERT(SUCCEEDED(hr));
	*/

	return;
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: convertToScreenPoint
* Purpose: Converts an ink point to screen coordinates
****************************************************************************/
ScreenPoint GR_Win32InkOverlay::convertToScreenPoint(GR_Graphics *pGR, InkPoint &inkPoint) {
	// return value
	ScreenPoint screenPoint(inkPoint.x, inkPoint.y);

	HRESULT ret = S_OK;

	// get the win graphics
	GR_Win32Graphics *pWinGraphics = (GR_Win32Graphics *)pGR;

	// get the HDC of the graphics so we know what pixel space we're in
	HDC hdc;
	hdc = pWinGraphics->getHDC(); 

	// get the renderer
	IInkRenderer *pIInkRenderer = this->_getInkRenderer();

	// translate from pixel space to ink space
	pIInkRenderer->InkSpaceToPixel((long)hdc, &screenPoint.x, &screenPoint.y);

	return screenPoint;
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: convertToInkPoint
* Purpose: Converts a screen point to ink coordinates
****************************************************************************/
InkPoint GR_Win32InkOverlay::convertToInkPoint(GR_Graphics *pGR, ScreenPoint &screenPoint) {
	// return value
	InkPoint inkPoint(screenPoint.x, screenPoint.y);

	HRESULT ret = S_OK;

	// get the win graphics
	GR_Win32Graphics *pWinGraphics = (GR_Win32Graphics *)pGR;

	// get the HDC of the graphics so we know what pixel space we're in
	HDC hdc;
	hdc = pWinGraphics->getHDC(); 

	// get the renderer
	IInkRenderer *pIInkRenderer = this->_getInkRenderer();

	// translate from pixel space to ink space
	ret = pIInkRenderer->PixelToInkSpace((long)hdc, &inkPoint.x, &inkPoint.y);
	UT_ASSERT(SUCCEEDED(ret));

	return inkPoint;
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: drawInk
* Purpose: Takes in an XML string that identifies a stroke and the draw arguments associated
*   with that stroke. This function then finds that stroke, applies the appropriate transformation
*   and redraws the stroke to the screen.
* Comments: Pass in some persisted ink and watch it do it's thing!
* Parameters:
*   dg_DrawArgs *pDA: Pointer to a draw args class which has current GR_Graphics, x and y,
*     and an indication if we're only doing dirty runs or not
*   XML_Char *strInk: String containing the id of the stroke that we wish to reflow and 
*			redraw on the screen
* Returns: true if the stroke reflowed and we need to redraw the old area in order
*     to get rid of the "ghost" stroke, false otherwise
****************************************************************************/
bool GR_Win32InkOverlay::drawStroke(dg_DrawArgs *pDA, const XML_Char *strStrokeId) {
	// make sure not null
	UT_ASSERT(pDA);
	UT_ASSERT(strStrokeId);

	// get the current ink object
	GR_Win32Ink *ptrInk = this->getInk();

	// get the stroke object that we're trying to find
	GR_Win32Stroke *ptrStroke = ptrInk->getStroke(strStrokeId);

	// make sure that we found the stroke object!
	if(ptrStroke) {
		// now make sure that we're drawing the ink on the screen!
		return this->drawStroke(pDA, ptrStroke);
	}

	return false;
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: drawStroke
* Purpose: Given a valid Stroke object, this function applies the appropriate transformation
*   and redraws the stroke to the screen.
* Parameters:
*   dg_DrawArgs *pDA: Pointer to a draw args class which has current GR_Graphics, x and y,
*     and an indication if we're only doing dirty runs or not
*   GR_Win32Stroke *ptrStroke: The GR_Win32Stroke object to reflow and redraw on the screen
* Returns: true if the stroke reflowed and we need to redraw the old area in order
*     to get rid of the "ghost" stroke, false otherwise
****************************************************************************/
bool GR_Win32InkOverlay::drawStroke(dg_DrawArgs *pDA, GR_Win32Stroke *ptrStroke) {
	bool value = false;

	// make sure not null
	UT_ASSERT(pDA);
	UT_ASSERT(ptrStroke);

	HRESULT hr = S_OK;

	// reflow the stroke to match its new position on the screen
	value = ptrStroke->reflow(pDA);

	// figure out the graphics Windows Id which we need to do a redraw
	GR_Graphics *pG = pDA->pG;
	GR_Win32Graphics *pGWin = (GR_Win32Graphics *)pG;
	HDC graphics = pGWin->getHDC();

	// get the ink renderer (which will be used to draw the stroke)
	IInkRenderer *pIInkRenderer = this->_getInkRenderer();

	// now draw the stroke on the ink overlay by passing it the renderer to use!
	ptrStroke->draw(pG, (long)graphics, pIInkRenderer);

	// debug
	if(INK_DEBUG) {
		InkPoint insertPoint = ptrStroke->getInsertionPoint();
		ScreenPoint rectPosition = this->convertToScreenPoint(pG, insertPoint);

		// insertion point
		UT_RGBColor blue(0,0,255);
		pGWin->fillRect(blue, rectPosition.x - 4, rectPosition.y - 4, 9, 9);
	}

	return value;
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: getScreenRectangle
* Purpose: Takes in an XML string that identifies a stroke and the draw arguments associated
*   with that stroke. This function then finds that stroke and returns its bounding box
* Parameters:
*   XML_Char *strInk: String containing the id of the stroke that we wish to reflow and 
*			redraw on the screen
****************************************************************************/
ScreenRect GR_Win32InkOverlay::getScreenRectangle(GR_Graphics *pG, const XML_Char *strStrokeId) {
	// return value
	ScreenRect box(0,0,0,0);

	// make sure not null
	UT_ASSERT(strStrokeId);

	// get the current ink object
	GR_Win32Ink *ptrInk = this->getInk();

	// get the stroke object that we're trying to find
	GR_Win32Stroke *ptrStroke = ptrInk->getStroke(strStrokeId);

	// make sure that we found the stroke object!
	if(ptrStroke) {
		// now make sure that we're drawing the ink on the screen!
		box = this->getScreenRectangle(pG, ptrStroke);
	}

	return box;
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: getScreenRectangle
* Purpose: Given a valid Stroke object, this function returns its bounding box
* Parameters:
*   GR_Win32Stroke *ptrStroke: The GR_Win32Stroke object to reflow and redraw on the screen
****************************************************************************/
ScreenRect GR_Win32InkOverlay::getScreenRectangle(GR_Graphics *pG, GR_Win32Stroke *ptrStroke) {
	// make sure not null
	UT_ASSERT(ptrStroke);

	HRESULT hr = S_OK;

	// reflow the stroke to match its new position on the screen
	return ptrStroke->getScreenRectange(this, pG);

	/*
	// figure out the graphics Windows Id which we need to do a redraw
	GR_Graphics *pG = pDA->pG;
	GR_Win32Graphics *pGWin = (GR_Win32Graphics *)pG;
	HDC graphics = pGWin->getHDC();

	// get the ink renderer (which will be used to draw the stroke)
	IInkRenderer *pIInkRenderer = this->_getInkRenderer();

	// now draw the stroke on the ink overlay by passing it the renderer to use!
	ptrStroke->draw(pIInkRenderer, (long)graphics);
	*/
}


/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: _setInk
* Purpose: Replace the current ink object with a new one
****************************************************************************/
void GR_Win32InkOverlay::_setInk(IInkDisp *pInk) {
	HRESULT hr = S_OK;

	// perhaps we're already disabled!; won't want to reenable at end!
	bool enable = this->isEnabled();

	if(enable) {
		// have to disable before you're allowed to change the ink
		this->disableInkOverlay();
	}

	// get the current ink object
	hr = this->m_pIInkOverlay->putref_Ink(pInk);
	UT_ASSERT(SUCCEEDED(hr));

	// renable if we were enabled before this method was called
	if(enable) {
		this->enableInkOverlay();
	}

	return;	
}


/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: getInk
* Purpose: Returns the GR_Win32Ink object that we're currently displaying
****************************************************************************/
GR_Win32Ink * GR_Win32InkOverlay::getInk() {
	// return value
	GR_Win32Ink *ptrWin32Ink = 0;

	HRESULT hr = S_OK;

	// the value that we'll be wrapping
	IInkDisp *pInk = 0;

	// get the current ink object
	hr = this->m_pIInkOverlay->get_Ink(&pInk);
	UT_ASSERT(SUCCEEDED(hr));

	// make a wrapper for the IInkDisp pointer
	ptrWin32Ink = new GR_Win32Ink(pInk);

	return ptrWin32Ink;	
}


// UNUSED FUNCTIONS (although potential useful)
// This code *works* but for one reason or another
// each function below is no longer used to do anything
// useful. In an effort to keep a clean namespace, I have
// commented it out. If you are developing new functions
// for TAbiWord that need Ink support, check out the functions
// below to make sure that you're not reinventing the wheel.
//    -- Kevin Conroy, 11 November 2003
//
///***************************************************************************
//* Author: Sam George, Microsoft Corporation, added by Kevin M. Conroy (KMC)
//* Function: _isInkRecognizerOS
//* Purpose: Returns a bool signifying if the current system is capable of supporting ink recognition
//* Source: http://www.tabletpcdeveloper.com/content/whitepapers/inkchat/
//****************************************************************************/
//bool GR_Win32InkOverlay::_isInkRecognizerOS(void) {
//	bool                          defaultRecoInstalled;
//	CComPtr<IInkRecognizerContext> spIInkRecognizerContext;
//
//	defaultRecoInstalled = false;
//	// Create the default recognition context
//	HRESULT hr = spIInkRecognizerContext.CoCreateInstance(CLSID_InkRecognizerContext);
//	if (SUCCEEDED(hr))
//	{
//		// The default recognizer is installed.  We can reco Ink
//		defaultRecoInstalled = true;
//	}
//
//	return defaultRecoInstalled;
//}
//
///***************************************************************************
//* Author: Kevin M. Conroy (KMC)
//* Function: setExtendedProperty
//* Purpose: Sets the extended property for the current ink object
//****************************************************************************/
//void GR_Win32InkOverlay::setExtendedProperty(CComBSTR guid, VARIANT value) {
//	HRESULT ret = S_OK;
//
//	// get the ink 
//	IInkDisp *ptrInk;
//	ret = m_pIInkOverlay->get_Ink(&ptrInk);
//	UT_ASSERT(SUCCEEDED(ret));
//
//	setExtendedProperty(guid, value, ptrInk);
//}
//
///***************************************************************************
//* Author: Kevin M. Conroy (KMC)
//* Function: setExtendedProperty
//* Purpose: Sets the extended property for the specified ink object
//****************************************************************************/
//void GR_Win32InkOverlay::setExtendedProperty(CComBSTR guid, VARIANT value, IInkDisp *ptrInk) {
//	HRESULT ret = S_OK;
//
//	// get the extended properties collection
//	IInkExtendedProperties *ptrExtendedProperties = 0;
//	ret = ptrInk->get_ExtendedProperties(&ptrExtendedProperties);
//	UT_ASSERT(SUCCEEDED(ret));
//
//	// see if we already have this property; if so, update the value
//	VARIANT_BOOL bolExists = VARIANT_FALSE;
//	ret = ptrExtendedProperties->DoesPropertyExist(guid, &bolExists);
//	UT_ASSERT(SUCCEEDED(ret));
//
//	// pointer to property
//	IInkExtendedProperty *ptrExtendedProperty = 0;
//
//	if(bolExists == VARIANT_TRUE) {
//		// need to get the property and update it
//
//		// get it
//		VARIANT key;
//		key.bstrVal = guid;
//		ret = ptrExtendedProperties->Item(key, &ptrExtendedProperty);
//		UT_ASSERT(SUCCEEDED(ret));
//
//		// update it (should be reflected in memory)
//		ret = ptrExtendedProperty->put_Data(value);
//		UT_ASSERT(SUCCEEDED(ret));
//	}
//	else {
//		// need to add it
//		ret = ptrExtendedProperties->Add(guid, value, &ptrExtendedProperty);
//		UT_ASSERT(SUCCEEDED(ret));
//	}
//
//	// debug
//	UT_DEBUGMSG(("ptrExtendedProperty made using value[%i]\n", value.lVal));
//}
//
///***************************************************************************
//* Author: Kevin M. Conroy (KMC)
//* Function: getExtendedProperty
//* Purpose: Gets an extended property for the current ink object
//****************************************************************************/
//VARIANT GR_Win32InkOverlay::getExtendedProperty(CComBSTR guid) {
//	HRESULT ret = S_OK;
//
//	// get the ink 
//	IInkDisp *ptrInk = 0;
//	ret = m_pIInkOverlay->get_Ink(&ptrInk);
//	UT_ASSERT(SUCCEEDED(ret));
//
//	return getExtendedProperty(guid, ptrInk);
//}
//
///***************************************************************************
//* Author: Kevin M. Conroy (KMC)
//* Function: getExtendedProperty
//* Purpose: Gets an extended property for the specified ink object
//****************************************************************************/
//VARIANT GR_Win32InkOverlay::getExtendedProperty(CComBSTR guid, IInkDisp *ptrInk) {
//	VARIANT value;
//	HRESULT ret = S_OK;
//
//	// get the extended properties collection
//	IInkExtendedProperties *ptrExtendedProperties = 0;
//	ret = ptrInk->get_ExtendedProperties(&ptrExtendedProperties);
//	UT_ASSERT(SUCCEEDED(ret));
//
//	// see if we already have this property; if so, update the value
//	VARIANT_BOOL bolExists = VARIANT_FALSE;
//	ret = ptrExtendedProperties->DoesPropertyExist(guid, &bolExists);
//	UT_ASSERT(SUCCEEDED(ret));
//
//	IInkExtendedProperty *ptrExtendedProperty;
//
//	if(bolExists == VARIANT_TRUE) {
//		// need to get the property and update it
//
//		// get it
//		VARIANT key;
//		VariantInit(&key);
//		key.vt = VT_BSTR;
//		key.bstrVal = guid;
//		ret = ptrExtendedProperties->Item(key, &ptrExtendedProperty);
//		UT_ASSERT(SUCCEEDED(ret));
//
//		// update it (should be reflected in memory)
//		ret = ptrExtendedProperty->get_Data(&value);
//		UT_ASSERT(SUCCEEDED(ret));
//	}
//	else {
//		// not here!!!
//		VariantInit(&value);
//		value.vt = VT_BOOL;
//		value.boolVal = VARIANT_FALSE;
//	}
//
//	return value;
//}
//
///***************************************************************************
//* Author: Kevin M. Conroy (KMC)
//* Function: collectInk
//* Purpose: Returns a string representation of the ink that was just put onto the collector
//* Comments: Not sure what string type to return - hacking away at it for now
//****************************************************************************/
//char * GR_Win32InkOverlay::collectInk(GR_Graphics *pGR, int screenX, int screenY) {
//	// start KMC: stroke handler for ap_Win32FrameImpl.cpp
//	HRESULT ret = S_OK;
//
//	// get the win graphics
//	GR_Win32Graphics *pWinGraphics = (GR_Win32Graphics *)pGR;
//
//	// get the renderer
//	IInkRenderer *pIInkRenderer = 0;
//	ret = this->m_pIInkOverlay->get_Renderer(&pIInkRenderer);
//	UT_ASSERT(SUCCEEDED(ret));
//
//	// get the HDC of the graphics so we know what pixel space we're in
//	HDC hdc;
//	hdc = pWinGraphics->getHDC();      
//
//	// translate from pixel space to ink space
//	long inkX = screenX;
//	long inkY = screenY;
//
//	// convert to ink space
//	this->pixelToInkSpace(pGR, inkX, inkY);
//
//	// KMC: Not so fast... let's delay this until the first draw
//	// save them to the extended properties
//	// this->setInkSpacePosition(inkX, inkY);
//
//	char *stringInk = 0;
//	stringInk = this->serializeInk();
//
//	// MANUAL INFORCE A REFRESH
//	//RedrawWindow(m_hwndDocument, NULL, NULL, RDW_INTERNALPAINT);
//
//	return stringInk;
//	//END KMC
//}
//
///***************************************************************************
//* Author: Kevin M. Conroy (KMC)
//* Function: _getCurrentInk
//* Purpose: Returns the current ink object
//****************************************************************************/
//IInkDisp * GR_Win32InkOverlay::_getCurrentInk() {
//	// get the ink 
//	IInkDisp *ptrInk = 0;
//	HRESULT ret = S_OK;
//
//	ret = m_pIInkOverlay->get_Ink(&ptrInk);
//
//	return ptrInk;
//}
//
///***************************************************************************
//* Author: Kevin M. Conroy (KMC)
//* Function: serializeInk
//* Purpose: Serializes the current ink object
//****************************************************************************/
//char * GR_Win32InkOverlay::serializeInk() {
//	IInkDisp *ptrInk = this->_getCurrentInk();
//
//	return this->serializeInk(ptrInk);
//}
//
///***************************************************************************
//* Author: Kevin M. Conroy (KMC)
//* Function: serializeInk
//* Purpose: Serializes the specified ink object
//****************************************************************************/
//char *	GR_Win32InkOverlay::serializeInk(IInkDisp *ptrInk) {
//	// save the ink to the buffer in a serialized format
//	VARIANT inkBuffer;
//
//	//unsigned short *strInkBuffer;
//	HRESULT result = S_OK;
//
//	//ptrInk->Save(InkPersistenceFormat::IPF_Base64InkSerializedFormat, InkPersistenceCompressionMode::IPCM_Default, &inkBuffer);
//	// save it to XML format with normal compression
//	result = ptrInk->Save(static_cast<InkPersistenceFormat>(1), static_cast<InkPersistenceCompressionMode>(0), &inkBuffer);
//
//	UT_DEBUGMSG(("KMC: inkBuffer.vt = %d\n", inkBuffer.vt));
//
//	_bstr_t strInkBuffer = inkBuffer.bstrVal;
//
//	// TASK: Get ink from VARIANT type to string (or char *)
//	// OPTION 1:
//	char *temp_stringInk = strInkBuffer;
//	char *stringInk = new char[strlen(temp_stringInk) + 1];
//	strcpy(stringInk, temp_stringInk);
//
//	UT_DEBUGMSG(("KMC: stringInk = %s\n", stringInk));
//	//UT_DEBUGMSG(("KMC: length=[%d] abiStringInk=[%s]\n", *inkLength, abiStringInk));
//
//	if(SUCCEEDED(result)) {
//		UT_DEBUGMSG(("result == %s\n", result));
//	}
//	else {
//		UT_DEBUGMSG(("result not equal to S_OK!\n"));
//	}
//
//	return stringInk;
//}
//
//
///***************************************************************************
//* Author: Kevin M. Conroy (KMC)
//* Function: resizeInkAreaToDocument
//* Purpose: Limits the area of the screen that is inkable to match the document (in other words,
//*    it will prevent the "grey" area on the side and top of the screen in ViewMode.VIEW_PREVIEW
//*    from being inkable.
//* Parameters:
//*   FV_View *pView: A pointer to the current FV_View object which provides us with information
//*     about the current visual state of TAbiWord
//****************************************************************************/
//void GR_Win32InkOverlay::resizeInkAreaToDocument(FV_View *pView) {
//	HRESULT hrInk;
//
//	// make sure that we have a view
//	if(pView != 0) {
//		UT_Vector *vRect = new UT_Vector();
//		UT_Vector *vPages = new UT_Vector();
//
//		// get the width of the grey left area
//		UT_sint32 greyWidth = pView->getPageViewLeftMargin();
//		UT_DEBUGMSG(("greyWidth=%i\n", greyWidth));
//
//		// get the width of the grey top area
//		UT_sint32 greyHeight = pView->getPageViewTopMargin();
//		UT_DEBUGMSG(("greyHeight=%i\n", greyHeight));
//
//		// get the document width
//		UT_sint32 width = pView->getWindowWidth();
//
//		// get the document height
//		UT_sint32 height = pView->getWindowHeight();
//
//		IInkRectangle *pIInkRectangle = 0;
//
//		hrInk = CoCreateInstance(CLSID_InkRectangle, NULL, CLSCTX_INPROC_SERVER, 
//			IID_IInkRectangle, 
//			(void **) &pIInkRectangle);
//
//		hrInk = this->m_pIInkOverlay->GetWindowInputRectangle(&pIInkRectangle);
//
//		long top = 0;
//		hrInk = pIInkRectangle->get_Top(&top);
//		UT_DEBUGMSG(("pIInkRectangle->top=%i\n", top));
//
//		long left = 0;
//		hrInk = pIInkRectangle->get_Left(&left);
//		UT_DEBUGMSG(("pIInkRectangle->left=%i\n", left));
//
//		// remove grey area
//		hrInk = pIInkRectangle->put_Left(greyWidth);
//
//		// remove grey area
//		hrInk = pIInkRectangle->put_Top(greyHeight);
//
//		// set right = window width - grey width
//		width = width - greyWidth;
//		hrInk = pIInkRectangle->put_Right(width);
//
//		// set bottom = window height - grey height
//		height = height - greyHeight;
//		hrInk = pIInkRectangle->put_Bottom(height);
//
//		// update it
//		hrInk = this->m_pIInkOverlay->SetWindowInputRectangle(pIInkRectangle);
//
//		// make sure it worked
//		UT_ASSERT(SUCCEEDED(hrInk));
//	}
//
//	return;
//}
//
//
///***************************************************************************
//* Author: Kevin M. Conroy (KMC)
//* Function: drawInk
//* Purpose: Takes in an XML string from the lower levels and draws it to the ink collector
//* Comments: Pass in some persisted ink and watch it do it's thing!
//* Parameters:
//*   dg_DrawArgs *pDA: Pointer to a draw args class which has current GR_Graphics, x and y,
//*     and an indication if we're only doing dirty runs or not
//*   XML_Char *strInk: String containing the persisted IInkDisp object that we'll be recreating
//*     and adding back to the IInkOverlay/IInkCollector
//****************************************************************************/
//void GR_Win32InkOverlay::drawInk(dg_DrawArgs *pDA, const XML_Char *strInk) {
//	UT_ASSERT(pDA);
//	UT_ASSERT(strInk);
//
//	if(true) {
//		// really should just clear based on stroke or something
//		this->clearScreen();
//
//		//AV_View *pView = this->getFrame()->getCurrentView();
//
//		HRESULT result = S_OK;
//		HRESULT hr = S_OK;
//
//		UT_DEBUGMSG(("hresult = %i\n", result));
//
//		// causes a thread to exit!! (and then when reabled, causes another WM_PAINT message to be sent!)
//		//this->disableInkOverlay();
//
//		// get the char * into a VARIANT
//		IInkDisp *pInk = 0;
//		pInk = this->_deserializeInk(strInk);
//
//		GR_Graphics *pG = pDA->pG;
//		GR_Win32Graphics *pGWin = (GR_Win32Graphics *)pG;
//		HDC graphics = pGWin->getHDC();
//
//		/*** START CALCULATE OFFSETS ****/
//		// now let's figure out how much we need to scale this ink
//		long xCurrent = pDA->xoff;
//		long yCurrent = pDA->yoff;
//
//		// get the ink renderer
//		IInkRenderer *pIInkRenderer = this->_getInkRenderer();
//
//		// convert the coords from pixel to ink so we know
//		// how much ink context transformation to apply
//		pIInkRenderer->PixelToInkSpace((long)graphics, &xCurrent, &yCurrent);
//
//		// generate guids
//		CComBSTR bstrGuidX(INK_INKSPACE_POS_X);
//		CComBSTR bstrGuidY(INK_INKSPACE_POS_Y);
//
//		// grab the location of the stroke
//		VARIANT xScreen = this->getExtendedProperty(bstrGuidX, pInk);
//		VARIANT yScreen = this->getExtendedProperty(bstrGuidY, pInk);
//
//		// figure out where the stroke already is
//		long xOriginal = (long)xScreen.lVal;
//		long yOriginal = (long)yScreen.lVal;
//
//		// we could modify it here, but then it won't get saved back to the piece table... no good
//		if(xOriginal == -1 && yOriginal == -1) {
//			//... insert hack about seeing position equal to current
//		}
//
//		// calculate right transition
//		long xOffset = xCurrent - xOriginal;
//		long yOffset = yCurrent - yOriginal;
//		/*** END CALCULATE OFFSETS ****/
//
//		/*** START APPLY OFFSETS ****/
//		IInkStrokes *pInkStrokes;		
//		// get the stroke
//		hr = pInk->get_Strokes(&pInkStrokes);
//		UT_ASSERT(SUCCEEDED(hr));
//
//		// make a new transform which will describe the move
//		IInkTransform *pInkTransform;
//		hr = CoCreateInstance(CLSID_InkTransform, NULL, CLSCTX_INPROC_SERVER, IID_IInkTransform, (void **) &pInkTransform);
//		UT_ASSERT(SUCCEEDED(hr));
//
//		// tell the transform where to move the ink to
//		hr = pInkTransform->Translate((float)xOffset, (float)yOffset);
//		UT_ASSERT(SUCCEEDED(hr));
//
//		// pass the strokes the transformation object which will
//		// in turn cause the stroke data to change accordingly
//		hr = pInkStrokes->Transform(pInkTransform, VARIANT_TRUE); 
//		UT_ASSERT(SUCCEEDED(hr));
//		/*** END APPLY OFFSETS ****/
//
//		// draw it by hand
//		hr = pIInkRenderer->Draw((long)graphics, pInkStrokes);
//		UT_DEBUGMSG(("hresult after ink = %i\n", hr));
//
//		// REMOVE THIS SINCE WE'RE GOING TO TRY TO DRAW THEM BY HAND
//		// put the ink on the overlay!!
//		// result = this->m_pIInkOverlay->putref_Ink(pInk);
//		// UT_DEBUGMSG(("hresult after ink = %i\n", result));
//		// UT_ASSERT(SUCCEEDED(result));
//
//		// not using enabled since it seems to cause problems
//		//this->enableInkOverlay();
//	}
//}
//
//
///***************************************************************************
//* Author: Kevin M. Conroy (KMC)
//* Function: setInkSpacePosition
//* Purpose: Sets the current position of the stroke (in ink space)
//****************************************************************************/
//void GR_Win32InkOverlay::setInkSpacePosition(long x, long y)
//{
//	// put something in as a place holder
//	VARIANT xPos;
//	VariantInit(&xPos);
//	xPos.vt = VT_I4;
//	xPos.lVal = x;
//
//	VARIANT yPos;
//	VariantInit(&yPos);
//	yPos.vt = VT_I4;
//	yPos.lVal = y;
//
//	// save the current ink location
//	CComBSTR bstrGuidX(INK_INKSPACE_POS_X);
//	CComBSTR bstrGuidY(INK_INKSPACE_POS_Y);
//
//	this->setExtendedProperty(bstrGuidX, xPos);
//	this->setExtendedProperty(bstrGuidY, yPos);
//}
//
///***************************************************************************
//* Author: Kevin M. Conroy (KMC)
//* Function: setInkSpacePosition
//* Purpose: Sets the current position of the stroke (in ink space)
//****************************************************************************/
//void GR_Win32InkOverlay::setInkSpacePosition(long x, long y, IInkDisp *pInk)
//{
//	// put something in as a place holder
//	VARIANT xPos;
//	VariantInit(&xPos);
//	xPos.vt = VT_I4;
//	xPos.lVal = x;
//
//	VARIANT yPos;
//	VariantInit(&yPos);
//	yPos.vt = VT_I4;
//	yPos.lVal = y;
//
//	// save the current ink location
//	CComBSTR bstrGuidX(INK_INKSPACE_POS_X);
//	CComBSTR bstrGuidY(INK_INKSPACE_POS_Y);
//
//	this->setExtendedProperty(bstrGuidX, xPos, pInk);
//	this->setExtendedProperty(bstrGuidY, yPos, pInk);
//}
//
///***************************************************************************
//* Author: Kevin M. Conroy (KMC)
//* Function: getScreenPosition
//* Purpose: Returns the current position of the stroke (in ink space)
//****************************************************************************/
//void GR_Win32InkOverlay::getInkSpacePosition(long &x, long &y)
//{
//	// generate guids
//	CComBSTR bstrGuidX(INK_INKSPACE_POS_X);
//	CComBSTR bstrGuidY(INK_INKSPACE_POS_Y);
//
//	// grab the location of the stroke
//	VARIANT xScreen = this->getExtendedProperty(bstrGuidX);
//	VARIANT yScreen = this->getExtendedProperty(bstrGuidY);
//
//	x = -1;
//	y = -1;
//
//	// figure out where the stroke already is
//	if(xScreen.vt == VT_I4) {			
//		x = (long)xScreen.lVal;
//	}
//	if(xScreen.vt == VT_I4) {			
//		y = (long)yScreen.lVal;
//	}
//}
//
///***************************************************************************
//* Author: Kevin M. Conroy (KMC)
//* Function: getScreenPosition
//* Purpose: Returns the current position of the stroke (in ink space)
//****************************************************************************/
//void GR_Win32InkOverlay::getInkSpacePosition(long &x, long &y, IInkDisp *pInk)
//{
//	// generate guids
//	CComBSTR bstrGuidX(INK_INKSPACE_POS_X);
//	CComBSTR bstrGuidY(INK_INKSPACE_POS_Y);
//
//	// grab the location of the stroke
//	VARIANT xScreen = this->getExtendedProperty(bstrGuidX, pInk);
//	VARIANT yScreen = this->getExtendedProperty(bstrGuidY, pInk);
//
//	x = -1;
//	y = -1;
//
//	// figure out where the stroke already is
//	if(xScreen.vt == VT_I4) {			
//		x = (long)xScreen.lVal;
//	}
//	if(xScreen.vt == VT_I4) {			
//		y = (long)yScreen.lVal;
//	}
//}
//
///***************************************************************************
//* Author: Kevin M. Conroy (KMC)
//* Function: PixelToInkSpace
//* Purpose: Converts the values in x and y from screen to ink space
//****************************************************************************/
//void GR_Win32InkOverlay::pixelToInkSpace(GR_Graphics *pGR, long &x, long &y) {
//	HRESULT ret = S_OK;
//
//	// get the win graphics
//	GR_Win32Graphics *pWinGraphics = (GR_Win32Graphics *)pGR;
//
//	// get the HDC of the graphics so we know what pixel space we're in
//	HDC hdc;
//	hdc = pWinGraphics->getHDC(); 
//
//	// get the renderer
//	IInkRenderer *pIInkRenderer = 0;
//	ret = this->m_pIInkOverlay->get_Renderer(&pIInkRenderer);
//	UT_ASSERT(SUCCEEDED(ret));
//
//	// translate from pixel space to ink space
//	pIInkRenderer->PixelToInkSpace((long)hdc, &x, &y);
//}
//
///***************************************************************************
//* Author: Kevin M. Conroy (KMC)
//* Function: zoomInk
//* Purpose: Zooms the ink in or out (depending on zoom factor)
//****************************************************************************/
//void GR_Win32InkOverlay::zoomInk(AV_View *pView) {
//	// go down thru AbiWord objects to get the current zoom level (perhaps not 
//	// the best way, but it seems to work)
//	UT_ASSERT(pView != 0);
//	GR_Graphics *pGraphics = pView->getGraphics();
//	GR_Win32Graphics *pWinGraphics = (GR_Win32Graphics *)pGraphics;
//
//	// the current zoom percentage level
//	int percentZoom = pWinGraphics->getZoomPercentage();
//
//	// convert to the decimal factor
//	float fZoom = (float)percentZoom / 100;
//
//	// update the zoom level
//	this->setZoomLevel(fZoom);
//}
///***************************************************************************
//* Author: Kevin M. Conroy (KMC)
//* Function: refreshWindow
//* Purpose: An attempt to force a redraw of the screen (WM_PAINT)
//****************************************************************************/
//void GR_Win32InkOverlay::refreshWindow(HWND hwnd) {
//	// http://msdn.microsoft.com/library/default.asp?url=/library/en-us/gdi/pantdraw_81pz.asp
//	// forces a WM_PAINT
//	// RedrawWindow(hwnd, NULL, NULL, RDW_INTERNALPAINT);
//}
