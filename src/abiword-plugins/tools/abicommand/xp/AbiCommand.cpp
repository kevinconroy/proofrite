/*
 * AbiCommand - Abiword plugin for a command line interface
 * Copyright (C) 2002 by Martin Sevior
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

#include "ut_assert.h"
#include "ut_debugmsg.h"
#include "xap_Module.h"
#include "xap_App.h"
#include "xap_Frame.h"
#include "fv_View.h"
#include "ap_Menu_Id.h"
#include "ev_Menu_Actions.h"
#include "ev_Menu.h"
#include "ev_Menu_Layouts.h"
#include "ev_Menu_Labels.h"
#include "ev_EditMethod.h"
#include "xap_Menu_Layouts.h"
#include "fg_Graphic.h"
#include "ie_imp.h"
#include "ie_impGraphic.h"
#include "ie_exp.h"
#include "ie_types.h"

#include "ut_sleep.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "AbiCommand.h"
//using namespace std;


ABI_PLUGIN_DECLARE(AbiCommand);

static bool AbiCommand_invoke(AV_View* v, EV_EditMethodCallData *d);

//
// AbiCommand_registerMethod()
// -----------------------
//   Adds AbiCommand_invoke to the EditMethod list
//
static void AbiCommand_registerMethod()
{
    // First we need to get a pointer to the application itself.
    XAP_App *pApp = XAP_App::getApp();

    
    // Create an EditMethod that will link our method's name with
    // it's callback function.  This is used to link the name to 
    // the callback.
    EV_EditMethod *myEditMethod = new EV_EditMethod(
        "AbiCommand_invoke",  // name of callback function
        AbiCommand_invoke,    // callback function itself.
        0,                      // no additional data required.
        ""                      // description -- allegedly never used for anything
    );
   
    // Now we need to get the EditMethod container for the application.
    // This holds a series of Edit Methods and links names to callbacks.
    EV_EditMethodContainer* pEMC = pApp->getEditMethodContainer();
    
    // We have to add our EditMethod to the application's EditMethodList
    // so that the application will know what callback to call when a call

    pEMC->addEditMethod(myEditMethod);

}


static void AbiCommand_RemoveFromMethods ()
{
  // First we need to get a pointer to the application itself.
  XAP_App *pApp = XAP_App::getApp();

  // remove the edit method
  EV_EditMethodContainer* pEMC = pApp->getEditMethodContainer() ;
  EV_EditMethod * pEM = ev_EditMethod_lookup ( "AbiCOmmand_invoke" ) ;
  pEMC->removeEditMethod ( pEM ) ;
  DELETEP( pEM ) ;
}

    
// -----------------------------------------------------------------------
//
//      Abiword Plugin Interface 
//
// -----------------------------------------------------------------------
    
ABI_FAR_CALL
int abi_plugin_register (XAP_ModuleInfo * mi)
{
    mi->name = "AbiCommand";
    mi->desc = "This is a command line interface to AbiWord";
    mi->version = ABI_VERSION_STRING;
    mi->author = "Martin Sevior <msevior@physics.unimelb.edu.au>";
    mi->usage = "AbiCommand_invoke";
    
    // Add to AbiWord's menus.
    AbiCommand_registerMethod();
    return 1;
}


ABI_FAR_CALL
int abi_plugin_unregister (XAP_ModuleInfo * mi)
{
    mi->name = 0;
    mi->desc = 0;
    mi->version = 0;
    mi->author = 0;
    mi->usage = 0;

    AbiCommand_RemoveFromMethods ();

    return 1;
}


ABI_FAR_CALL
int abi_plugin_supports_version (UT_uint32 major, UT_uint32 minor, UT_uint32 release)
{
    return 1; 
}

// -----------------------------------------------------------------------
//
//     AbiCommand Invocation Code
//
// -----------------------------------------------------------------------


//
// AbiCommand_invoke
// -------------------
//   This is the function that we actually call to make command line 
//   interface.
//
static bool  AbiCommand_invoke(AV_View* v, EV_EditMethodCallData *d)
{
//
// Do something useful...
// 
	AbiCommand myCommand;
	myCommand.doCommands();
	return true;
}

AbiCommand::AbiCommand(void) :
	m_pCurDoc(NULL),
	m_pCurFrame(NULL),
	m_pCurView(NULL),
	m_pG(NULL),
	m_pLayout(NULL),
	m_bViewDoc(false)
{
	m_pApp = XAP_App::getApp();
}

AbiCommand::~AbiCommand(void)
{
	deleteCurrentDoc();
}

void AbiCommand::deleteCurrentDoc(void)
{
//
// Delete the current view, frame and document.
//
	bool bUnref = (m_pCurFrame == NULL);
	if(m_pCurFrame != NULL)
	{
		m_pApp->forgetFrame(m_pCurFrame);
	}
//
// Deleting the frame also deletes the layout, view and graphics classes
//
	DELETEP(m_pCurFrame);
	if(bUnref)
	{
		UNREFP(m_pCurDoc);
	}
	m_pCurView = NULL;
	m_pG = NULL;
	m_pLayout = NULL;
	m_pCurView = NULL;
}

void AbiCommand::doCommands(void)
{
	char * pCom = NULL;
	UT_Vector toks;
	bool bQuit = false;
	UT_uint32 i = 0;
	printf("AbiWord command line plugin: Type ""quit"" to exit \n");
	while(!bQuit)
	{
//
// Read a line
//
		if(pCom)
		{
			free(pCom);
		}
		pCom = readline("AbiWord:> ");

		// Quit on EOF
		if (!pCom)
			break;

//
// break it into tokens
//
		tokenizeString(toks,pCom);
		FREEP(pCom);
		if(toks.getItemCount() > 0)
		{
			UT_String * pTok = (UT_String *) toks.getNthItem(0);
			if(pTok && UT_strcmp(pTok->c_str(),"quit") == 0)
			{
				bQuit = true;
			}
			else
			{
				UT_sint32 bres = parseTokens(&toks);
				if(bres == 0)
				{
					printf("OK\n");
				}
				else
				{
					printf("error %d \n",bres);
				}
			}
			clearTokenVector(toks);
		}
	}
}

/*!
 * Break the string into tokens. Handles quotes and double quotes.
\params char * pStr String from readline
\params UT_Vector & reference to the vector we'll fill with UT_String * pointers.
 */
bool AbiCommand::tokenizeString(UT_Vector & tok, char * pStr)
{
	char * str = UT_strdup(pStr);
	char * pt = str;
	bool bQuote = false;
	bool bSkipSpace = false;
	char * anchor = str;
	size_t point = 0;
	size_t nchars = strlen(str)+1;
	while(point < nchars)
	{
		point++;
		if(*pt == ' ' && bSkipSpace)
		{
			pt++;
			anchor++;
			continue;
		}
		else if(*pt == ' ' && !bQuote)
		{
			bSkipSpace = true;
			*pt = 0;
			UT_String * pTok = new UT_String(anchor);
			printf(" anchor =%x string is %s \n",anchor,pTok->c_str());
			tok.addItem((void *) pTok);
			pt++;
			anchor = pt;
			continue;
		}
		else if(*pt == 0)
		{
			bQuote = false;
			UT_String * pTok = new UT_String(anchor);
			tok.addItem((void *) pTok);
			break;
		}
		else if(*pt == '"')
		{
//
// Unless there is a "", The quote is a delimeter. First look for double ""
//
//
// Found it, put a " into the current token and shift the remaining
// text.
//
			if( point < nchars && (*(pt+1) == '"') && bQuote)
			{
				char * pt1 = pt+1;
				char * pt2 = pt1;
				pt2++;
				while(*pt2 != 0)
				{
					*pt1 = *pt2;
					pt1++;
					pt2++;
				}
				pt +=2;
				nchars--;
				continue;
			}

//
// OK we've reached the end of the quoted text. Inject this segment into
// a token. Move the point and anchor past this quote in the stream.
//
			if(bQuote)
			{
				bQuote = false;
				*pt = 0;
				UT_String * pTok = new UT_String(anchor);
				tok.addItem((void *) pTok);
				pt++;
				anchor=pt;
				continue;
			}
//
// OK we're here if a previous quote was not in the stream. If we're not
// in skip space write the current text from the anchor into the token.
// otherwise set the anchor point just past the quote.
//
			if(bSkipSpace)
			{
				bSkipSpace = false;
				pt++;
				bQuote = true;
				anchor = pt;
				continue;
			}
//
// Tokenize the text from anchor.
//
			*pt = 0;
			UT_String * pTok = new UT_String(anchor);
			tok.addItem((void *) pTok);
			bQuote = true;
			pt++;
			anchor= pt;
		} // Handled "" !!
//
// Otherwise just increment the pt pointer. Leave anchor in place.
//
		else
		{
			bSkipSpace = false;
			pt++;
		}
	}
	FREEP(str);
	if(!bQuote)
	{
		return true;
	}
	else
	{
//
// We have umatched "  "
//
		return false;
	}
}

/*!
 * clear the token vector pointed to by pvecToks
 */
void AbiCommand::clearTokenVector(UT_Vector & vecToks)
{
	UT_uint32 i =0;
	for(i=0; i< vecToks.getItemCount(); i++)
	{
		UT_String * pComm = (UT_String *) vecToks.getNthItem(i);
		delete pComm;
	}
	vecToks.clear();
}

//
// parse the UT_String * tokens within the vector pToks.
//
UT_sint32 AbiCommand::parseTokens(UT_Vector * pToks)
{
	UT_uint32 count = pToks->getItemCount();
	if(count == 0)
	{
		return -1;
	}
	UT_uint32 i =0;
	printf("Number of tokens here is %d \n",count);
	for(i=0; i< count; i++)
	{
		UT_String * pstr = (UT_String *) pToks->getNthItem(i);
		printf("Token %d string is %s \n",i,pstr->c_str());
	}

	UT_String * pCom0 = (UT_String *) pToks->getNthItem(0);

	printf("first command is %s \n",pCom0->c_str());

//
// New document
//
	if(UT_strcmp(pCom0->c_str(),"new")==0)
	{
		printf("Attempting to create a new document \n");
		PD_Document * pDoc = new PD_Document(m_pApp);
		UT_Error error = pDoc->newDocument();
		if(error != UT_OK)
		{
			UNREFP(pDoc);
			printf("Error creating new document error %d \n", error);
			return (UT_sint32) error;
		}
		replaceDocument(pDoc);
		return 0;
	}
//
// Load in a document
//
	if(UT_strcmp(pCom0->c_str(),"load")==0)
	{
		printf("Attempting to load a document \n");
		if(count >= 2)
		{
			UT_String * pCom1 =  (UT_String *) pToks->getNthItem(1);
			PD_Document * pDoc = new PD_Document(m_pApp);
			UT_Error error = pDoc->readFromFile(pCom1->c_str(),IEFT_Unknown);
			if(error != UT_OK)
			{
				UNREFP(pDoc);
				printf("Error loading %s error %d \n",pCom1->c_str(),error);
				return (UT_sint32) error;
			}
			replaceDocument(pDoc);
			return 0;
//
// We're finished a Load!
//
		}
	}

//
// printfile
//
	else if(UT_strcmp(pCom0->c_str(),"printfile")==0)
	{
		if(count >= 2)
		{
			bool bres = printFiles(pToks);
			if(bres)
			{
				return 0;
			}
			return -1;
		}
	}
//
// inserttext
//
	else if(UT_strcmp(pCom0->c_str(),"inserttext")==0)
	{
		if(count >= 2)
		{
			bool bres = insertText(pToks);
			if(bres)
			{
				return 0;
			}
			return -1;
		}
	}
//
// delete
//
	else if(UT_strcmp(pCom0->c_str(),"delete")==0)
	{
		bool bres = deleteText(pToks);
		if(bres)
		{
			return 0;
		}
		return -1;
	}
//
// Replace Next
//
	else if(UT_strcmp(pCom0->c_str(),"replacenext")==0)
	{
		if(count > 2)
		{
			bool bres = replaceNext(pToks);
			if(bres)
			{
				return 0;
			}
			return -1;
		}
	}
//
// replaceAll
//
	else if(UT_strcmp(pCom0->c_str(),"replaceall")==0)
	{
		if(count > 2)
		{
			bool bres = replaceAll(pToks);
			if(bres)
			{
				return 0;
			}
			return -1;
		}
	}
//
// Move point to somewhere
//
	else if(UT_strcmp(pCom0->c_str(),"movept")==0)
	{
		if(count > 1)
		{
			bool bres = movePoint(pToks);
			if(bres)
			{
				return 0;
			}
			return -1;
		}
	}
//
// Open a graphical window on the document
//
	else if(UT_strcmp(pCom0->c_str(),"visualedit")==0)
	{
		bool res = viewDoc();
		if(res)
		{
			return 0;
		}
		else
		{
			return -1;
		}
	}
//
// Start selection
//
	else if(UT_strcmp(pCom0->c_str(),"selectstart")==0)
	{
		if(m_pCurView)
		{
			PT_DocPosition pos = m_pCurView->getPoint();
			((FV_View *)m_pCurView)->cmdSelect(pos,pos);
			return 0;
		}
		else
		{
			return -1;
		}
	}
//
// Clear selection
//
	else if(UT_strcmp(pCom0->c_str(),"selectclear")==0)
	{
		if(m_pCurView)
		{
			m_pCurView->cmdUnselectSelection();
			return 0;
		}
		else
		{
			return -1;
		}
	}
//
// findnext
//
	else if(UT_strcmp(pCom0->c_str(),"findnext")==0)
	{
		if(m_pCurView && (pToks->getItemCount()> 1))
		{
			bool bEOD = false;
			UT_String * pFind = (UT_String *) pToks->getNthItem(1);
			const UT_UCSChar * pUCSFind = (const UT_UCSChar *) UT_calloc(pFind->size()+1,sizeof(UT_UCSChar));
			((FV_View *)m_pCurView)->findNext(pUCSFind,true,bEOD);
			FREEP(pUCSFind);
			if(!bEOD)
			{
				return 0;
			}
			return -1;
		}
		else
		{
			return -1;
		}
	}

//
// Save
//
	else if(UT_strcmp(pCom0->c_str(),"save")==0)
	{
		if(m_pCurDoc)
		{
			IEFileType ieft = 0;
			if(pToks->getItemCount() > 1)
			{
				UT_String * pCom1 = (UT_String *) pToks->getNthItem(1);
				char* suffix = rindex(pCom1->c_str(), '.');
				if(i != 0)
				{
					ieft = IE_Exp::fileTypeForSuffix(suffix);
					printf("Doing file export as %d for %s \n",ieft,pCom1->c_str());
				}
				else
				{
					ieft = (IEFileType) m_pCurDoc->getLastOpenedType();
				}
				m_pCurDoc->saveAs(pCom1->c_str(),ieft);
				return 0;
			}
			UT_String sFile = m_pCurDoc->getFileName();
			ieft = (IEFileType) m_pCurDoc->getLastOpenedType();
			m_pCurDoc->saveAs(sFile.c_str(),ieft);
			return 0;
		}
		return -1;
	}
//
// Help
//
	else if(UT_strcmp(pCom0->c_str(),"help")==0)
	{
		printf("Currently implemented commands are...\n");
		printf("help - prints this message \n");
		printf("new - create a new empty document.\n");
		printf("load <filename> - load <filename> replacing the current document. \n");
		printf("printfile <filename1> <filename2>... -  print the current document into the filenames listed.\n");
		printf("replaceall <find> <target> - replace every occurance of <find> with <target> in the current document. \n");
		printf("replacenext <find> <target> - replace the next occurance of <find> with <target> in the current document. \n");
		printf("inserttext <target> - Insert <target> at the current point in the document. \n");
		printf("delete <args> - Delete <args> characters at the current point in the document. \n");
		printf("replacenext <find> <target> - replace the next occurance of <find> with <target> in the current document. \n");
		printf("movept <arg> - Move the current point to another location in the current document. \n");
		printf("  options for arg are: BOD,EOD,BOP,EOP,BOS,EOS,BOL,EOL,BOW,+num,-num,num \n");
		printf("selectstart - Start a selection at the current point \n");
		printf("selectclear - Clear the current selection.\n");
		printf("findnext <target> - Find the next occurance of target and select it.\n");
		printf("save <filename> - Save the current document.\n");
		printf("  If filename is omitted the file is saved to it's original name \n");
		printf("  Otherwise the extension of the filename is used to determine the format of the file\n");
		printf("visualedit - popup a visual window and edit the file or just preview what you've done \n");
		printf("  close the window when finished.\n");

		return 0;
	}

	else
	  {
	    if ( ev_EditMethod_exists (*pCom0) )
	      {
		UT_String calldata ;
		
		for ( int i = 1; i < count; i++ )
		  {
		    UT_String * pComm = (UT_String *) pToks->getNthItem(i);
		    calldata += *pComm ;
		  }
		printf ( "EditMethod %s exists. Calling with %s\n", pCom0->c_str(), calldata.c_str() ) ;
		if ( ev_EditMethod_invoke ( *pCom0, calldata ) )
		  return 0 ;
		return -1 ;
	      }
	    else
	      {
		printf ( "EditMethod %s does not exist.\n", pCom0->c_str());
	      }
	  }

	return -1;	
}

//
// This method calls the method defined in ap_EditMethod.cpp via it's
// name with the current nullgraphics view as the controlling view.
//
bool AbiCommand::invoke(const char * pszCommand)
{
	const EV_EditMethod *	pEM = m_pApp->getEditMethodContainer()->findEditMethodByName(pszCommand);
	if(pEM == NULL)
	{
		return false;
	}
	return pEM->Fn(m_pCurView,(EV_EditMethodCallData *) NULL);
}
//
// Viewdoc. Popup an abiword window on the current document.
//
bool AbiCommand::viewDoc(void)
{
	m_bViewDoc = true;
	bool res= invoke("newWindow");
	while(m_pCurFrame && m_pCurFrame->getViewNumber() > 0)
	{
		nullUpdate();
	}
#if 0
//
// Don't need this since the user has deleted the clone anyway.
//
// Delete any clones that might exist.
//
	if(m_bViewDoc)
	{
		UT_Vector vecClones;
		m_pApp->getClones(&vecClones,m_pCurFrame);
		UT_uint32 i =0;
		for(i=0; i< vecClones.getItemCount(); i++)
		{
			XAP_Frame * pF = (XAP_Frame *) vecClones.getNthItem(i);
			if(pF != static_cast<XAP_Frame *>(m_pCurFrame))
			{
				m_pApp->forgetFrame(pF);
				pF->close();
				delete pF;
			}
		}
	}
#endif
	return true;
}
	
//
// Move the insertion point to various places.
//
bool AbiCommand::movePoint(UT_Vector * pToks)
{
    bool bRelMove = false;
    bool bAbsMove = false;
    UT_sint32 amt = 0;
	if(m_pCurView != NULL)
	{
		UT_String * pTarget = (UT_String *) pToks->getNthItem(1);
		FV_DocPos docpos;
		if(UT_stricmp(pTarget->c_str(),"BOD") == 0)
		{
			docpos = FV_DOCPOS_BOD;
		}
		else if(UT_stricmp(pTarget->c_str(),"EOD") == 0)
		{
			docpos = FV_DOCPOS_EOD;
		}
		else if(UT_stricmp(pTarget->c_str(),"BOB") == 0)
		{
			docpos = FV_DOCPOS_BOB;
		}
		else if(UT_stricmp(pTarget->c_str(),"EOB") == 0)
		{
			docpos = FV_DOCPOS_EOB;
		}
		else if(UT_stricmp(pTarget->c_str(),"BOP") == 0)
		{
			docpos = FV_DOCPOS_BOP;
		}
		else if(UT_stricmp(pTarget->c_str(),"EOP") == 0)
		{
			docpos = FV_DOCPOS_EOP;
		}
		else if(UT_stricmp(pTarget->c_str(),"BOL") == 0)
		{
			docpos = FV_DOCPOS_BOL;
		}
		else if(UT_stricmp(pTarget->c_str(),"EOL") == 0)
		{
			docpos = FV_DOCPOS_EOL;
		}
		else if(UT_stricmp(pTarget->c_str(),"BOS") == 0)
		{
			docpos = FV_DOCPOS_BOS;
		}
		else if(UT_stricmp(pTarget->c_str(),"EOS") == 0)
		{
			docpos = FV_DOCPOS_EOS;
		}
		else if(UT_stricmp(pTarget->c_str(),"BOW") == 0)
		{
			docpos = FV_DOCPOS_BOW;
		}
		else if(*(pTarget->c_str()) == '+' || *(pTarget->c_str()) == '-')
		{
			bRelMove = true;
			amt = atoi(pTarget->c_str());
		}
        else if(atoi(pTarget->c_str()) != 0)
        {
            bAbsMove = true;
            amt = atoi(pTarget->c_str());
        }
        else
        {
            return false;
        }
        if(bRelMove && amt != 0)
        {
            bool bForward = (amt > 0);
		    static_cast<FV_View *>(m_pCurView)->cmdCharMotion(bForward,amt);
            return true;
        }
        if(bAbsMove && amt != 0)
        {
            PT_DocPosition posBOD;
            PT_DocPosition posEOD;
            PT_DocPosition pos = (PT_DocPosition) amt;
		    static_cast<FV_View *>(m_pCurView)->getEditableBounds(true,posEOD);
		    static_cast<FV_View *>(m_pCurView)->getEditableBounds(false,posBOD);
            if(amt >= posBOD && amt <= posEOD)
            {
		         static_cast<FV_View *>(m_pCurView)->setPoint(pos);
            }
            else
            {
                 return false;
            }
        }
        else if( amt < 0)
        {
            return false;
        }
		static_cast<FV_View *>(m_pCurView)->moveInsPtTo(docpos);
		return true;
	}
	return false;
}
//
// Replace every instance of the string in token 1 with the string in
// token 2
//
bool AbiCommand::replaceAll(UT_Vector * pToks)
{
	if(m_pCurView != NULL)
	{
		UT_String * pFind = (UT_String *) pToks->getNthItem(1);
		UT_String * pReplace = (UT_String *) pToks->getNthItem(2);
		const UT_UCSChar * pUCSFind = (const UT_UCSChar *) UT_calloc(pFind->size()+1,sizeof(UT_UCSChar));
		const UT_UCSChar * pUCSReplace = (const UT_UCSChar *) UT_calloc(pReplace->size()+1,sizeof(UT_UCSChar));
		UT_UCS4_strcpy_char(const_cast<UT_UCS4Char *>(pUCSFind), pFind->c_str());
		UT_UCS4_strcpy_char(const_cast<UT_UCS4Char *>(pUCSReplace), pReplace->c_str());
		static_cast<FV_View *>(m_pCurView)->findSetStartAtInsPoint();
		static_cast<FV_View *>(m_pCurView)->findReplaceAll(pUCSFind ,pUCSReplace,true);
		FREEP(pUCSFind);
		FREEP(pUCSReplace);
		return true;
	}
	return false;
}
//
// Insert the text on the command line into the document at the current
// Point.
//
bool AbiCommand::insertText(UT_Vector * pToks)
{
	if(m_pCurView != NULL && pToks->getItemCount() > 1)
	{
		UT_String * pText = (UT_String *) pToks->getNthItem(1);
		UT_UCSChar * pUCSText = (UT_UCSChar *) UT_calloc(pText->size()+1,sizeof(UT_UCSChar));
		UT_UCS4_strcpy_char((UT_UCS4Char *) pUCSText, pText->c_str());
		static_cast<FV_View *>(m_pCurView)->cmdCharInsert(pUCSText,pText->size());
		FREEP(pUCSText);
		return true;
	}
	return false;
}
//
// Delete the text at the current point according to the argument on the 
// command line.
//
bool AbiCommand::deleteText(UT_Vector * pToks)
{
	if(m_pCurView != NULL)
	{
		UT_String * pCom1 = (UT_String *) pToks->getNthItem(1);
		UT_sint32 count = atoi(pCom1->c_str());
		bool bForward = (count > 0);
		static_cast<FV_View *>(m_pCurView)->cmdCharDelete(bForward,count);
		return true;
	}
	return false;
}

//
// Replace the next instance of the string in token 1 with the string in
// token 2
//
bool AbiCommand::replaceNext(UT_Vector * pToks)
{
	if(m_pCurView != NULL)
	{
		UT_String * pFind = (UT_String *) pToks->getNthItem(1);
		UT_String * pReplace = (UT_String *) pToks->getNthItem(2);
		const UT_UCSChar * pUCSFind = (const UT_UCSChar *) UT_calloc(pFind->size()+1,sizeof(UT_UCSChar));
		const UT_UCSChar * pUCSReplace = (const UT_UCSChar *) UT_calloc(pReplace->size()+1,sizeof(UT_UCSChar));
		UT_UCS4_strcpy_char(const_cast<UT_UCS4Char *>(pUCSFind), pFind->c_str());
		UT_UCS4_strcpy_char(const_cast<UT_UCS4Char *>(pUCSReplace), pReplace->c_str());
		bool bEOD = false;
		static_cast<FV_View *>(m_pCurView)->findReplace(pUCSFind ,pUCSReplace,true,bEOD);
		FREEP(pUCSFind);
		FREEP(pUCSReplace);
		if(!bEOD)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}
//
// Print the current documents to the files listed on the command line
//
bool AbiCommand::printFiles(UT_Vector * pToks)
{
	UT_uint32 i=0;
	for(i=1; i< pToks->getItemCount();i++)
	{
		UT_String * pFile = (UT_String *) pToks->getNthItem(i);
		PS_Graphics * pG = new PS_Graphics (pFile->c_str(),
											m_pCurDoc->getFileName(), 
											m_pApp->getApplicationName(), 
											static_cast<XAP_UnixApp *>(m_pApp)->getFontManager(),
											true, 
											m_pApp);
		// create a new layout and view object for the doc
		FL_DocLayout *pDocLayout = new FL_DocLayout(m_pCurDoc,pG);
		FV_View *printView = new FV_View(m_pApp,0,pDocLayout);
		pDocLayout->fillLayouts();

		// get the width, height, orient
		UT_sint32 iWidth = pDocLayout->getWidth();
		UT_sint32 iHeight = pDocLayout->getHeight() / pDocLayout->countPages();

		bool orient = printView->getPageSize().isPortrait();
		pG->setPortrait (orient);  

		// setup the drawing args
		dg_DrawArgs da;
		memset(&da, 0, sizeof(da));
		da.pG = NULL;

		pG->setColorSpace(GR_Graphics::GR_COLORSPACE_COLOR);
		pG->setPageSize(printView->getPageSize().getPredefinedName());

		if(pG->startPrint())
		{
			// iterate over the pages, printing each one
			for (UT_uint32 k = 1; (k <= pDocLayout->countPages()); k++)
			{
				pG->m_iRasterPosition = (k-1)*iHeight;
				pG->startPage(pFile->c_str(), k, orient, iWidth, iHeight);
				printView->draw(k-1, &da);
			}
			pG->endPrint();
		}
		DELETEP(pDocLayout);
		DELETEP(printView);
		DELETEP(pG);
	}
	return true;
}

void AbiCommand::nullUpdate(void)
{
	if(m_bViewDoc)
	{
		UT_uint32 i =0;
		for(i=0; i < 5;i++)
		{
			gtk_main_iteration();
		}
	}
}
//
// Doc loaded OK, delete the old stuff, put in the new stuff
//
bool AbiCommand::replaceDocument(PD_Document * pDoc)
{
//
// Delete the current document.
//
	deleteCurrentDoc();
//
// Put the new document in place.
//
	m_pCurDoc = pDoc;
	XAP_UnixApp * pUnixApp = (XAP_UnixApp *) m_pApp;
	m_pCurFrame = new AP_UnixFrame(pUnixApp);
	UT_String extension(".bak~");
	m_pCurFrame->setAutoSaveFileExt(extension);
	m_pG = new UnixNull_Graphics(pUnixApp->getFontManager(), m_pApp);
	
	m_pLayout = new FL_DocLayout(m_pCurDoc, (GR_Graphics *) m_pG);
	m_pCurView = new FV_View(m_pApp, m_pCurFrame, m_pLayout);
	m_pCurFrame->setView((AV_View *) m_pCurView);
	m_pCurFrame->setDoc((AD_Document *) m_pCurDoc);
	m_pLayout->fillLayouts();
	((FV_View *) m_pCurView)->setPoint(2);
	return true;
}







