/* AbiWord
 * Copyright (C) 1998-2000 AbiSource, Inc.
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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

#include "ut_debugmsg.h"
#include "ut_assert.h"
#include "ap_StatusBar.h"
#include "ap_FrameData.h"
#include "gr_Graphics.h"
#include "xap_Frame.h"
#include "xav_View.h"
#include "ap_Strings.h"
#include "fl_DocLayout.h"
#include "fv_View.h"

#include "ut_timer.h"

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

#define AP_STATUSBAR_STATUSMESSAGE_REPRESENTATIVE_STRING "MMMMMMMMMMMMMMMMMMMMMMMMMMMM"
#define AP_STATUSBAR_INPUTMODE_REP_STRING "MMMMMMMM"
#define AP_STATUSBAR_INSERTMODE_REP_STRING "MMM"

#define AP_STATUSBAR_MAX_PAGES 999

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

AP_StatusBarField::AP_StatusBarField(AP_StatusBar * pSB)
{
	m_pSB = pSB;
	m_pStatusBarFieldListener = NULL;
	m_fillMethod = MAX_POSSIBLE;
}

AP_StatusBarField::~AP_StatusBarField(void)
{
	if(m_pStatusBarFieldListener)
		delete(m_pStatusBarFieldListener);
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

AP_StatusBarField_TextInfo::AP_StatusBarField_TextInfo(AP_StatusBar *pSB) 
	: AP_StatusBarField(pSB) 
{ 
	memset(m_bufUCS, 0, sizeof(m_bufUCS)); 
	strcpy(m_sRepresentativeString, "");
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
class ap_sbf_PageInfo : public AP_StatusBarField_TextInfo
{
public:
	ap_sbf_PageInfo(AP_StatusBar * pSB);

	virtual void		notify(AV_View * pView, const AV_ChangeMask mask);

private:
	UT_uint32			m_pageNr;
	UT_uint32			m_nrPages;

	const XML_Char *	m_szFormat;
};

ap_sbf_PageInfo::ap_sbf_PageInfo(AP_StatusBar * pSB)
	: AP_StatusBarField_TextInfo(pSB)
{
	m_pageNr = 0;
	m_nrPages = 0;

	m_szFormat = pSB->getFrame()->getApp()->getStringSet()->getValue(AP_STRING_ID_PageInfoField);
	m_fillMethod = REPRESENTATIVE_STRING;
	m_alignmentMethod = LEFT;

	sprintf(m_sRepresentativeString,m_szFormat,AP_STATUSBAR_MAX_PAGES,AP_STATUSBAR_MAX_PAGES);
}

void ap_sbf_PageInfo::notify(AV_View * pavView, const AV_ChangeMask mask)
{
	FV_View * pView = (FV_View *)pavView;
	
	bool bNeedNewString = false;

	if (mask & (AV_CHG_MOTION | AV_CHG_PAGECOUNT))
	{
		UT_uint32 currentPage = pView->getCurrentPageNumForStatusBar(); 
		UT_uint32 newPageCount = pView->getLayout()->countPages();

		if (newPageCount != m_nrPages || m_pageNr != currentPage)
		{
			bNeedNewString = true;
			m_nrPages = newPageCount;
			m_pageNr = currentPage; 
		}
	}

	if (bNeedNewString)
	{
		char buf[AP_MAX_MESSAGE_FIELD];
		sprintf(buf,m_szFormat,m_pageNr,m_nrPages);
		
		// WL: Assume all incoming strings are in UTF-8
		// FIXME: Should we be doing this in a more principled way?
		UT_UCS4_strcpy_utf8_char(m_bufUCS,buf);		

		if (getListener())
			getListener()->notify();

	}
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

class ap_sbf_StatusMessage : public AP_StatusBarField_TextInfo
{
 public:
	ap_sbf_StatusMessage(AP_StatusBar * pSB);

	virtual void		notify(AV_View * pView, const AV_ChangeMask mask);
	void update(UT_UCS4Char *pMessage); // for receiving messages from the status bar itself
};

ap_sbf_StatusMessage::ap_sbf_StatusMessage(AP_StatusBar * pSB)
	: AP_StatusBarField_TextInfo(pSB)
{
	m_fillMethod = MAX_POSSIBLE;
	m_alignmentMethod = LEFT;
	strcpy(m_sRepresentativeString, AP_STATUSBAR_STATUSMESSAGE_REPRESENTATIVE_STRING);
}

void ap_sbf_StatusMessage::notify(AV_View * /*pView*/, const AV_ChangeMask /*mask*/)
{
	UT_UCS4_strcpy(m_bufUCS, m_pSB->getStatusMessage());

	if (getListener())
		getListener()->notify();
}

void ap_sbf_StatusMessage::update(UT_UCS4Char *pMessage)
{
	UT_UCS4_strcpy(m_bufUCS, pMessage);

	if (getListener())
		getListener()->notify();
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

class ap_sbf_InputMode : public AP_StatusBarField_TextInfo
{
 public:
	ap_sbf_InputMode(AP_StatusBar * pSB);
	
	virtual void		notify(AV_View * pView, const AV_ChangeMask mask);
};

ap_sbf_InputMode::ap_sbf_InputMode(AP_StatusBar * pSB)
	: AP_StatusBarField_TextInfo(pSB)
{
	const char * szInputMode = m_pSB->getFrame()->getInputMode();
	// WL: Assume all incoming strings are in UTF-8
	// FIXME: Should we be doing this in a more principled way?
	UT_UCS4_strcpy_utf8_char(m_bufUCS,szInputMode);

	m_fillMethod = REPRESENTATIVE_STRING;
	m_alignmentMethod = LEFT;
	strcpy(m_sRepresentativeString, AP_STATUSBAR_INPUTMODE_REP_STRING);
}

void ap_sbf_InputMode::notify(AV_View * /*pavView*/, const AV_ChangeMask mask)
{
	if (mask & (AV_CHG_INPUTMODE))
	{
		const char * szInputMode = m_pSB->getFrame()->getInputMode();

		// WL: Assume all incoming strings are in UTF-8
		// FIXME: Should we be doing this in a more principled way?
		UT_UCS4_strcpy_utf8_char(m_bufUCS,szInputMode);		

		if (getListener())
			getListener()->notify();
	}
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

class ap_sbf_InsertMode : public AP_StatusBarField_TextInfo
{
 public:
	ap_sbf_InsertMode(AP_StatusBar * pSB);
	
	virtual void        notify(AV_View * pView, const AV_ChangeMask mask);

 private:
	UT_UCSChar m_InsertMode[2][AP_MAX_MESSAGE_FIELD];
	bool m_bInsertMode;
};

ap_sbf_InsertMode::ap_sbf_InsertMode(AP_StatusBar * pSB)
    : AP_StatusBarField_TextInfo(pSB)
{

    UT_UCS4_strcpy_utf8_char(m_InsertMode[(int)true],pSB->getFrame()->getApp()->getStringSet()->getValue(AP_STRING_ID_InsertModeFieldINS));
    UT_UCS4_strcpy_utf8_char(m_InsertMode[(int)false],pSB->getFrame()->getApp()->getStringSet()->getValue(AP_STRING_ID_InsertModeFieldOVR));

    m_bInsertMode = true;

    m_fillMethod = REPRESENTATIVE_STRING;
    m_alignmentMethod = CENTER;
    strcpy(m_sRepresentativeString, AP_STATUSBAR_INSERTMODE_REP_STRING);
}

void ap_sbf_InsertMode::notify(AV_View * /*pavView*/, const AV_ChangeMask mask)
{
    if (mask & (AV_CHG_INSERTMODE))
    {
		AP_FrameData * pData = (AP_FrameData *) m_pSB->getFrame()->getFrameData();
		if (pData) {
			m_bInsertMode = pData->m_bInsertMode;
			UT_UCS4_strcpy(m_bufUCS, m_InsertMode[m_bInsertMode]);
		}

		if (getListener())
			getListener()->notify();
    }
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

class ap_sbf_Language : public AP_StatusBarField_TextInfo
{
 public:
	ap_sbf_Language(AP_StatusBar * pSB);

	virtual void notify(AV_View * pView, const AV_ChangeMask mask);
};

ap_sbf_Language::ap_sbf_Language(AP_StatusBar * pSB)
	: AP_StatusBarField_TextInfo(pSB)
{
	m_fillMethod = REPRESENTATIVE_STRING;
	m_alignmentMethod = CENTER;
	strcpy(m_sRepresentativeString, "mm-MM"); // this should actually be longer.. see old code for info on why
}

void ap_sbf_Language::notify(AV_View * pavView, const AV_ChangeMask mask)
{
	// TODO do we want our own bit for language change?
	//if (mask & (AV_CHG_INSERTMODE))
	{
		const char * szLang = NULL;

		const XML_Char ** props_in = NULL;
		if (pavView && static_cast<FV_View *>(pavView)->getCharFormat(&props_in))
		{
			szLang = UT_getAttribute("lang", props_in);
			FREEP(props_in);

			UT_UCS4_strcpy_utf8_char(m_bufUCS, szLang ? szLang : "");
		}

		if (getListener())
			getListener()->notify();
	}
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// PROGRESSBAR. CURRENTLY UNUSED. MAY BE BROKEN. NEEDS TESTING.

AP_StatusBarField_ProgressBar::AP_StatusBarField_ProgressBar(AP_StatusBar * pSB)
	: AP_StatusBarField(pSB)
{
	m_ProgressStartPoint = 0;
	m_ProgressFlags = 0;
	m_ProgressTimer = NULL;
}

AP_StatusBarField_ProgressBar::~AP_StatusBarField_ProgressBar(void)
{
}

static void updateProgress(UT_Worker * pWorker)
{
    UT_ASSERT(pWorker);

    AP_StatusBarField_ProgressBar *pfspb;
    pfspb = (AP_StatusBarField_ProgressBar *)pWorker->getInstanceData();
    UT_ASSERT(pfspb);

    if(pfspb->getListener())
	    pfspb->getListener()->notify();
}

void AP_StatusBarField_ProgressBar::notify(AV_View * /*pView*/, const AV_ChangeMask /*mask*/)
{
	// do nothing, we get our information from the status bar	
}

void AP_StatusBarField_ProgressBar::setStatusProgressType(int start, int end, int flags)
{
	m_ProgressStart = 
		m_ProgressValue = start;
	m_ProgressEnd = end;
	m_ProgressFlags = flags;
	m_ProgressStartPoint = 0;

	if (m_ProgressTimer) {
		delete m_ProgressTimer;
		m_ProgressTimer = NULL;
	}

	if (m_ProgressStart == m_ProgressEnd &&
	    (m_ProgressFlags & PROGRESS_CMD_MASK) == PROGRESS_STARTBAR) {  
		m_ProgressTimer = UT_Timer::static_constructor(updateProgress, this);
		m_ProgressTimer->stop();
		m_ProgressTimer->set(50);	//Milliseconds
	}	
}

void AP_StatusBarField_ProgressBar::setStatusProgressValue(int value)
{
	m_ProgressValue = value;
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

AP_StatusBar::AP_StatusBar(XAP_Frame * pFrame)
:       m_pFrame(pFrame),
        m_pView(0),
        m_bInitFields(false),
        m_pStatusMessageField(0)
{

#define DclField(type,var)								\
		type * var = new type(this);					\
		UT_ASSERT((var));								\
		m_vecFields.addItem((var));						\
		
		DclField(ap_sbf_PageInfo, pf1);
		DclField(ap_sbf_StatusMessage, pf2);

		m_pStatusMessageField = pf2;	// its in the vector, but we remember it explicitly
		                                // so that setStatusMessage() can do its thing.

		DclField(ap_sbf_InsertMode, pf4);
		DclField(ap_sbf_InputMode, pf3);
		
		DclField(ap_sbf_Language, pf5);

		// TODO add other fields

#undef DclField
		

        m_bufUCS[0] = 0;
}

AP_StatusBar::~AP_StatusBar(void)
{
	UT_VECTOR_PURGEALL(AP_StatusBarField *, m_vecFields);
}

XAP_Frame * AP_StatusBar::getFrame(void) const
{
	return m_pFrame;
}

void AP_StatusBar::setView(AV_View * pView)
{
	m_pView = pView;

	// Register the StatusBar as a ViewListener on the View.
	// This lets us receive notify events as the user interacts
	// with the document (cmdCharMotion, etc).  This will let
	// us update the display as we move from block to block and
	// from column to column.

	AV_ListenerId lidTopRuler;
	m_pView->addListener(static_cast<AV_Listener *>(this),&lidTopRuler);

	if (!m_bInitFields)
	{
		
		m_bInitFields = true;
	}

	// force a full notify of all fields so that they all
	// completely update themselves.
	
	notify(pView,AV_CHG_ALL);
	
	return;
}

bool AP_StatusBar::notify(AV_View * pView, const AV_ChangeMask mask)
{
	// Handle AV_Listener events on the view.	

	// We choose to clear any status message we may have,
	// since it's a pain for the code which set the message
	// to hang around and clear it at some point in the future.
	// This way, message will get cleared any time the user does
	// something with the window.

	if (*m_bufUCS)
		setStatusMessage((UT_UCSChar *)NULL);
	
	// Let each field on the status bar update itself accordingly.
	
	UT_ASSERT(pView==m_pView);
	UT_uint32 kLimit = m_vecFields.getItemCount();
	UT_uint32 k;

	for (k=0; k<kLimit; k++)
	{
		AP_StatusBarField * pf = (AP_StatusBarField *)m_vecFields.getNthItem(k);
		if(pf)
		{
			pf->notify(pView,mask);
		}
	}

	return true;
}

void AP_StatusBar::setStatusMessage(UT_UCSChar * pBufUCS, int redraw)
{
	memset(m_bufUCS, 0, sizeof(m_bufUCS));

	if (pBufUCS && *pBufUCS) {
		UT_ASSERT(UT_UCS4_strlen(pBufUCS) < AP_MAX_MESSAGE_FIELD);
		UT_UCS4_strcpy(m_bufUCS, pBufUCS);
	}
	
 	ap_sbf_StatusMessage * pf = (ap_sbf_StatusMessage *)m_pStatusMessageField;
 	if(pf)
 		pf->update(pBufUCS);
}

void AP_StatusBar::setStatusMessage(const char * pBuf, int redraw)
{
	UT_uint32 len = ((pBuf && *pBuf) ? strlen(pBuf) : 0);
	UT_ASSERT(len*MB_LEN_MAX < AP_MAX_MESSAGE_FIELD);

	UT_UCSChar bufUCS[AP_MAX_MESSAGE_FIELD];

	if (len)
		UT_UCS4_strcpy_utf8_char(bufUCS,pBuf);
	else
		memset(bufUCS,0,sizeof(bufUCS));

 	ap_sbf_StatusMessage * pf = (ap_sbf_StatusMessage *)m_pStatusMessageField;
 	if(pf) {
		pf->update(bufUCS);
	}
}

const UT_UCSChar * AP_StatusBar::getStatusMessage(void) const
{
	return m_bufUCS;
}

void AP_StatusBar::setStatusProgressType(int start, int end, int flags) {
// 	ap_sbf_StatusMessage * pf = (ap_sbf_StatusMessage *)m_pStatusMessageField;
// 	if(pf)
// 	{
// 		pf->setStatusProgressType(start, end, flags);
// 		if (pf->getListener())
// 			pf->getListener()->notify();
// 	}
}

void AP_StatusBar::setStatusProgressValue(int value) {
// 	ap_sbf_StatusMessage * pf = (ap_sbf_StatusMessage *)m_pStatusMessageField;
// 	if(pf)
// 	{
// 		pf->setStatusProgressValue(value);

// 		if (pf->getListener())
// 			pf->getListener()->notify();
// 	}
}
