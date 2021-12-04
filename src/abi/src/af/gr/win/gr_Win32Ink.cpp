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

#include "gr_Win32Ink.h"

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: ctor
* Purpose: Initalize the class with all of the appropriate variables
****************************************************************************/
GR_Win32Ink::GR_Win32Ink(IInkDisp *ptrInk) {
	// make sure it's not null
	UT_ASSERT(ptrInk);

	// save the pointer to the ink object that we're wrapping
	this->m_pInkDisp = ptrInk;

	// debug
	UT_DEBUGMSG(("After constructor: "));
	// debug
	this->print();
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: dtor
* Purpose: Takes in an XML string from the lower levels and draws it to the ink collector
* Comments: Pass in some persisted ink and watch it do it's thing!
****************************************************************************/
GR_Win32Ink::~GR_Win32Ink(void) {
	// no op
	this->m_pInkDisp->Release();
	this->m_pInkDisp = 0;
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: release
* Purpose: Cleans up the ink
****************************************************************************/
void GR_Win32Ink::release() {
  this->m_pInkDisp->Release();
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: draw
* Purpose: Redraws all of the strokes in this ink layer using the given
*   renderer
****************************************************************************/
void GR_Win32Ink::draw(long HDC, IInkRenderer *pInkRenderer) {
	HRESULT hr = S_OK;

	// the collection of strokes to search
	IInkStrokes *ptrStrokes = 0;

	// get the current strokes collection
	hr = this->m_pInkDisp->get_Strokes(&ptrStrokes);
	UT_ASSERT(SUCCEEDED(hr));

	// redraw them all!
	hr = pInkRenderer->Draw(HDC, ptrStrokes);
	UT_ASSERT(SUCCEEDED(hr));

	/*
	// total number of strokes
	long strokeCount = 0;
	hr = ptrStrokes->get_Count(&strokeCount);
  UT_ASSERT(SUCCEEDED(hr));

	// temp values used to help the search
	IInkStrokeDisp *ptrStroke = 0;
	
	// search for the right stroke
	for(long i = 0; i < strokeCount; i++) {
		// get the stroke that has the specified id!
		hr = ptrStrokes->Item(i, &ptrStroke);
		UT_ASSERT(SUCCEEDED(hr));

		// wrap it... use stack to avoid mem. leaks
		GR_Win32Stroke stroke(ptrStroke);

		// draw the stroke
		stroke.draw(HDC, pInkRenderer);
	}
	*/
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: getStroke
* Purpose: Returns a GR_Win32Stroke object whose Id matches the string passed in
****************************************************************************/
GR_Win32Stroke * GR_Win32Ink::getStroke(const XML_Char *strStrokeId) {
	// return value
	GR_Win32Stroke *ptrWin32Stroke = 0;

	// the stroke id in number form
  long strokeId = 0;

	// convert the string Id back to a number
	strokeId = atoi(strStrokeId);

	// get the stroke
	ptrWin32Stroke = this->getStroke(strokeId);

	return ptrWin32Stroke;
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: getStroke
* Purpose: Returns a GR_Win32Stroke object whose Id matches the string passed in
****************************************************************************/
GR_Win32Stroke * GR_Win32Ink::getStroke(long strokeId) {
  // return value
	GR_Win32Stroke *ptrWin32Stroke = 0;

	HRESULT hr = S_OK;

	// the Stroke object to wrap
	IInkStrokeDisp *ptrStroke = 0;

	// the collection of strokes to search
	IInkStrokes *ptrStrokes = 0;

	// get the current strokes collection
	hr = this->m_pInkDisp->get_Strokes(&ptrStrokes);
	UT_ASSERT(SUCCEEDED(hr));

	// TODO: perhaps we should use an Enum here rather than a manual search
	// NOTE: didn't use an Enum at first because it's a little messy since it
	//   returns the enumeration as a VARIANT which are just a point to work with

	// total number of strokes
	long strokeCount = 0;
	hr = ptrStrokes->get_Count(&strokeCount);
	UT_ASSERT(SUCCEEDED(hr));

	// temp values used to help the search
	long currentId = -1;
	IInkStrokeDisp *ptrCurrentStroke = 0;

	UT_DEBUGMSG(("Looking for stroke Id #[%d]\n", strokeId));

	// search for the right stroke
	for(long i = 0; i < strokeCount; i++) {
		// get the stroke that has the specified id!
		hr = ptrStrokes->Item(i, &ptrCurrentStroke);
		UT_ASSERT(SUCCEEDED(hr));

		// get the id of the stroke we're looking at
		GR_Win32Stroke stroke(ptrCurrentStroke);
		currentId = stroke.getGUID();

		UT_DEBUGMSG(("  Checking stroke Id #[%d] (%d of %d)\n", currentId, i + 1, strokeCount));

		// see if the id's match!
		if(currentId == strokeId) {
			// they match; save the pointer and exit the for loop
			ptrStroke = ptrCurrentStroke;
			break;
		}

		// haven't found the stroke yet, keep going
	}

	// should have a value (unless we didn't find a stroke with that Id for some reason!)
	// KMC 3/1/2004: May be valid to not have found a stroke if we've clipped the stroke
	//				 and the clipped stroke is empty
	// UT_ASSERT(ptrStroke);

	if(ptrStroke) {
		// make a wrapper for the stroke object
		ptrWin32Stroke = new GR_Win32Stroke(ptrStroke);
	}

	return ptrWin32Stroke;
}


/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: serializeInk
* Purpose: Serializes the current ink object
****************************************************************************/
char * GR_Win32Ink::serializeInk() {

	// debug
	UT_DEBUGMSG(("Prior to serialization: "));
	// debug
	this->print();

	return this->serializeInk(this->m_pInkDisp);
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: serializeInk
* Purpose: Serializes the specified ink object
****************************************************************************/
char * GR_Win32Ink::serializeInk(IInkDisp *ptrInk) {
	// save the ink to the buffer in a serialized format
	VARIANT inkBuffer;

	//unsigned short *strInkBuffer;
	HRESULT result;

	//ptrInk->Save(InkPersistenceFormat::IPF_Base64InkSerializedFormat, InkPersistenceCompressionMode::IPCM_Default, &inkBuffer);
	// save it to XML format with normal compression
	result = ptrInk->Save(static_cast<InkPersistenceFormat>(1), static_cast<InkPersistenceCompressionMode>(0), &inkBuffer);

	UT_DEBUGMSG(("KMC: inkBuffer.vt = %d\n", inkBuffer.vt));

	_bstr_t strInkBuffer = inkBuffer.bstrVal;

	// TASK: Get ink from VARIANT type to string (or char *)
	// OPTION 1:
	char *temp_stringInk = strInkBuffer;
	char *stringInk = new char[strlen(temp_stringInk) + 1];
	strcpy(stringInk, temp_stringInk);

	UT_DEBUGMSG(("KMC: stringInk = %s\n", stringInk));
	//UT_DEBUGMSG(("KMC: length=[%d] abiStringInk=[%s]\n", *inkLength, abiStringInk));

	if(SUCCEEDED(result)) {
		UT_DEBUGMSG(("result == %s\n", result));
	}
	else {
		UT_DEBUGMSG(("result not equal to S_OK!\n"));
	}

	return stringInk;
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: deserializeInk
* Purpose: Deserializes the specified ink string
****************************************************************************/
IInkDisp * GR_Win32Ink::deserializeInk(const XML_Char *strInk) {
	HRESULT result = S_OK;
	//IInkDisp *ptrNewInk;
	//CComPtr<IInkDisp> ptrNewInk;

	// get the char * into a VARIANT

	DWORD dataSize;
	// ... assign the byte-size of the persistent data to dataSize
	dataSize = strlen(strInk) * sizeof(XML_Char);

	BYTE* pData = new BYTE[dataSize];
	// ... read the persistent data into the pData buffer here ...
	for(DWORD i = 0; i < dataSize; i++) {
		pData[i] = strInk[i];
	}

	//CComPtr<IInkDisp> pInk;
	//result = pInk->CoCreateInstance(CLSID_InkDisp, NULL, CLSCTX_ALL);
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
* Function: createStroke
* Purpose: Create a new stroke using the specified packet data
****************************************************************************/
GR_Win32Stroke * GR_Win32Ink::createStroke(VARIANT &packetData) {
	GR_Win32Stroke * stroke = 0;
	IInkStrokeDisp *pStrokeDisp = 0;

	HRESULT hr = S_OK;

	VARIANT varPK;	
	VariantInit( &varPK );

	LPBYTE pArrayData = NULL;
	hr = ::SafeArrayAccessData(packetData.parray,(void**) &pArrayData);
	UT_ASSERT(SUCCEEDED(hr));

	// create a clone using the packet data
	// NOTE: varPK (packet description) is currently reserved, so it is
	// just empty variant for now.
	hr = this->m_pInkDisp->CreateStroke(packetData, varPK, &pStrokeDisp);
	UT_ASSERT(SUCCEEDED(hr));

	hr = ::SafeArrayUnaccessData(packetData.parray);
	UT_ASSERT(SUCCEEDED(hr));

	// make a new stroke
	stroke = new GR_Win32Stroke(pStrokeDisp);
	UT_ASSERT(stroke != 0);

	return stroke;
}


/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: getStroke
* Purpose: Returns a GR_Win32Stroke object whose Id matches the string passed in
****************************************************************************/
void GR_Win32Ink::print() {
#if INK_DEBUG
	HRESULT hr = S_OK;

	// the collection of strokes to search
	IInkStrokes *ptrStrokes = 0;

	// get the current strokes collection
	hr = this->m_pInkDisp->get_Strokes(&ptrStrokes);
	UT_ASSERT(SUCCEEDED(hr));

	// TODO: perhaps we should use an Enum here rather than a manual search
	// NOTE: didn't use an Enum at first because it's a little messy since it
	//   returns the enumeration as a VARIANT which are just a pain to work with

	// total number of strokes
	long strokeCount = 0;
	hr = ptrStrokes->get_Count(&strokeCount);
	UT_ASSERT(SUCCEEDED(hr));

	// temp values used to help the search
	long currentId = -1;
	IInkStrokeDisp *ptrCurrentStroke = 0;
	
	UT_DEBUGMSG(("Ink object contains the following strokes:\n"));

	// search for the right stroke
	for(long i = 0; i < strokeCount; i++) {
		// get the stroke that has the specified id!
		hr = ptrStrokes->Item(i, &ptrCurrentStroke);
		UT_ASSERT(SUCCEEDED(hr));

		GR_Win32Stroke stroke(ptrCurrentStroke);
		UT_DEBUGMSG(("   "));
		stroke.print();		
	}

	i++;
	return;
#endif
}

/***************************************************************************
* Author: Kevin M. Conroy (KMC)
* Function: deleteStroke
* Purpose: Deletes the specified stroke from the ink object
****************************************************************************/
void GR_Win32Ink::deleteStroke(IInkStrokeDisp *stroke) {
	HRESULT hr = S_OK;

	// remove the stroke
	hr = this->m_pInkDisp->DeleteStroke(stroke);
	UT_ASSERT(SUCCEEDED(hr));
}
