/* AbiWord
 * Copyright (C) 1998-2002 AbiSource, Inc.
 * Copyright (C) 2002
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

#ifndef AP_WIN32FRAMEIMPL_H
#define AP_WIN32FRAMEIMPL_H

#include "ap_Frame.h"
#include "xap_Win32FrameImpl.h"
#include "ap_FrameData.h"
//include "ut_types.h"

// KMC: START INK
#include "gr_Win32Tablet.h"
#include "gr_Win32Stroke.h"
#include "gr_Win32InkOverlay.h"
#include "gr_Win32InkOverlayEvents.h"
// KMC: END INK

class ABI_EXPORT AP_Win32FrameImpl : public XAP_Win32FrameImpl, public InkOverlayEvents
{
 public:
	AP_Win32FrameImpl(AP_Frame *pFrame); 
	~AP_Win32FrameImpl(void);
	virtual XAP_FrameImpl * createInstance(XAP_Frame *pFrame, XAP_App *pApp);

  GR_Win32InkOverlay * getInkOverlay(void) { return m_pInkOverlay; }

	 // Event: Stroke
  virtual void Stroke(IInkCursor* Cursor, IInkStrokeDisp* Stroke, VARIANT_BOOL *Cancel);

 protected:
	friend class AP_Win32Frame;

	virtual void    _initialize(void);

	virtual void    _refillToolbarsInFrameData();
	virtual void    _rebuildToolbar(UT_uint32 ibar);

	virtual void 		_toggleTopRuler(AP_Win32Frame *pFrame, bool bRulerOn);
	virtual void 		_toggleLeftRuler(AP_Win32Frame *pFrame, bool bRulerOn);

	void            _translateDocumentToScreen(UT_sint32 &x, UT_sint32 &y);

	void            _setXScrollRange(AP_FrameData * pData, AV_View *pView);
	void            _setYScrollRange(AP_FrameData * pData, AV_View *pView);

	static bool     _RegisterClass(XAP_Win32App * app);


	HWND						_getHwndContainer(void) {  return m_hwndContainer; }
	HWND						_getHwndTopRuler(void)  {  return m_hwndTopRuler;  }
	HWND						_getHwndLeftRuler(void) {  return m_hwndLeftRuler; }
	HWND						_getHwndDocument(void)  {  return m_hwndDocument;  }
	HWND						_getHwndHScroll(void)   {  return m_hWndHScroll;   }
	HWND						_getHwndVScroll(void)   {  return m_hWndVScroll;   }

	void						_setVerticalScrollInfo(const SCROLLINFO * psi);
	void						_getVerticalScrollInfo(SCROLLINFO * psi);

	void						_createRulers(XAP_Frame *pFrame) {  _createTopRuler(pFrame); _createLeftRuler(pFrame);  }

	HWND						_createDocumentWindow(XAP_Frame *pFrame, HWND hwndParent,
													  UT_uint32 iLeft, UT_uint32 iTop,
													  UT_uint32 iWidth, UT_uint32 iHeight);
	HWND						_createStatusBarWindow(XAP_Frame *pFrame, HWND hwndParent,
													   UT_uint32 iLeft, UT_uint32 iTop,
													   UT_uint32 iWidth);

  void            _createWin32InkOverlay();
/***************************************/

 private:
	void						_createTopRuler(XAP_Frame *pFrame);
	void						_createLeftRuler(XAP_Frame *pFrame);
	void						_getRulerSizes(AP_FrameData * pData, int &yTopRulerHeight, int &xLeftRulerWidth);
	void						_onSize(AP_FrameData * pData, int nWidth, int nHeight);

	static int 					_getMouseWheelLines();

	void						_startTracking(UT_sint32 x, UT_sint32 y);
	void						_endTracking(UT_sint32 x, UT_sint32 y);
	void						_track(UT_sint32 x, UT_sint32 y);
	bool						_isTracking() const { return m_bMouseWheelTrack; }

  /** window callback functions **/
	static LRESULT CALLBACK			_ContainerWndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK			_DocumentWndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	//static LRESULT CALLBACK		_LeftRulerWndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

 private:
  // START PRIVATE INK DATA MEMBERS
  GR_Win32InkOverlay   *m_pInkOverlay; // ink collector
  // END PRIVATE INK DATA MEMEBERS

	HWND						m_hwndContainer;
	HWND						m_hwndTopRuler;
	HWND						m_hwndLeftRuler;
	HWND						m_hwndDocument;	/* the actual document window */

	HWND						m_hWndHScroll;
	HWND						m_hWndVScroll;
	HWND						m_hWndGripperHack;

	UT_uint32					m_vScale; /* vertical scroll scaling to get around 16-bit scrollbar problems */

	bool						m_bMouseWheelTrack;
	UT_sint32					m_startMouseWheelY;
	UT_sint32					m_startScrollPosition;
	bool						m_bMouseActivateReceived;
	bool 						m_bFirstAfterFocus;

	#define MAXDOCWNDCLSNMSIZE 256
	#define MAXCNTWNDCLSNMSIZE 256
	static char s_ContainerWndClassName[MAXCNTWNDCLSNMSIZE];
	static char s_DocumentWndClassName[MAXDOCWNDCLSNMSIZE];
};

#endif /* AP_WIN32FRAMEIMPL_H */
