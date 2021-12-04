/* GypsyPlugin
 * Copyright (C) 2002 Mauro Colorio
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

#include "Gypsython.h"

// Gypsy plugin runs python embedded in abiword

static bool Gypsython_invoke(AV_View* v, EV_EditMethodCallData *d);

Gypsython * mygypsython;

Gypsython::Gypsython(void):
  m_pCurDoc(NULL),
  m_sModulePath(0)

  //	m_pCurView(NULL),
  //	m_pFrame(NULL),

{
  m_pApp = XAP_App::getApp();
  m_pFrame = XAP_App::getApp()->getLastFocussedFrame();
  m_pCurView = static_cast <FV_View *>(m_pFrame->getCurrentView());	
}

Gypsython::~Gypsython(void)
{
  FREEP( m_sModulePath );
}


// Python stuffs

#ifdef __cplusplus
extern "C" {
#endif

  // This inserts a test inside Abiword  
  static PyObject *
  Gypsython_insertText(PyObject *self, PyObject *pyArgs)
  {
    char * pystring;
    
    PyArg_ParseTuple(pyArgs, "s", &pystring);
    
    mygypsython->insertText( pystring );
    
    Py_INCREF(Py_None);
    return Py_None;
  }

  static PyObject *
  Gypsython_setPaperColor(PyObject *self, PyObject *pyArgs)
  {
    char * pycolor;
    
    PyArg_ParseTuple(pyArgs, "s", &pycolor);
    
    mygypsython->setPaperColor( pycolor );
    
    Py_INCREF(Py_None);
    return Py_None;
  }

  static PyObject *
  Gypsython_editHeader(PyObject *self, PyObject *pyArgs)
  {
    mygypsython->editHeader();
    
    Py_INCREF(Py_None);
    return Py_None;
  }


  static PyObject *
  Gypsython_editFooter(PyObject *self, PyObject *pyArgs)
  {
    mygypsython->editFooter();
    
    Py_INCREF(Py_None);
    return Py_None;
  }

  static PyObject *
  Gypsython_editBody(PyObject *self, PyObject *pyArgs)
  {
    mygypsython->editBody();
    
    Py_INCREF(Py_None);
    return Py_None;
  }


  static PyObject *
  Gypsython_openFile(PyObject *self, PyObject *pyArgs)
  {
    char * pyfilename;
    
    PyArg_ParseTuple(pyArgs, "s", &pyfilename);
    
    mygypsython->openFile( pyfilename );
    Py_INCREF(Py_None);
    return Py_None;

  }


  // Here it's where you have to add your method to be avaible from the python namespace
  static PyMethodDef GypysthonMethods[] = {
    {"insertText", Gypsython_insertText, METH_VARARGS, "let's you insert some text in abiword"},
    {"setPaperColor", Gypsython_setPaperColor, METH_VARARGS, "change paper's color"},
    {"editHeader", Gypsython_editHeader, METH_VARARGS, "Edits header"},
    {"editFooter", Gypsython_editFooter, METH_VARARGS, "Edits footer"},
    {"editBody", Gypsython_editBody, METH_VARARGS, "Edits boody"},
    {"openFile", Gypsython_openFile, METH_VARARGS, "Open a file"},
    {NULL, NULL} //Sentinel 
  };
  
  bool initgypsython()
  {
    
    static char modname__doc__[] = "This module let's you work with python.";
    
    (void) Py_InitModule("gypsython", GypysthonMethods);
    
    return true;
    
  }
  
#ifdef __cplusplus
}
#endif

// End python stuffs

//
// insertText, Puts string on a view
bool Gypsython::insertText(char * text)
{
  if(m_pCurView != NULL){
    UT_UCSChar * pUCSText = (UT_UCSChar *) UT_calloc(strlen(text)+1,sizeof(UT_UCSChar));
    UT_UCS4_strcpy_char((UT_UCS4Char *) pUCSText, text);
    static_cast<FV_View *>(m_pCurView)->cmdCharInsert(pUCSText,strlen(text));
    FREEP(pUCSText);
    return true;
  }
  return false;
}



XAP_Frame * Gypsython::openFile(char * filename)
{
  XAP_Frame *     RETVAL;
  
  // printf("openFile\n");
  RETVAL = m_pApp->newFrame();
  RETVAL->loadDocument(filename, 0, true);

  m_pCurView = static_cast <FV_View *>(m_pFrame->getCurrentView());
  return RETVAL;

}



bool Gypsython::setPaperColor(char * color)
{
  static_cast<FV_View *>(m_pCurView)->setPaperColor((XML_Char*) color);
  return true;

}


bool Gypsython::editHeader()
{
  static_cast<FV_View *>(m_pCurView)->cmdEditHeader();
  return true;
}

bool Gypsython::editFooter()
{
  static_cast<FV_View *>(m_pCurView)->cmdEditFooter();
  return true;
}

bool Gypsython::editBody()
{

 static_cast<FV_View *>(m_pCurView)->clearHdrFtrEdit();
 static_cast<FV_View *>(m_pCurView)->warpInsPtToXY(0, 0, false);

 return true;
}
// AskScriptFilename
// -------------------

bool Gypsython::AskScriptFilename()
{
  XAP_DialogFactory * pDialogFactory
    = (XAP_DialogFactory *)(m_pFrame->getDialogFactory());
  
  XAP_Dialog_Id id = XAP_DIALOG_ID_FILE_OPEN;  
  
  XAP_Dialog_FileOpenSaveAs * pDialog
    = (XAP_Dialog_FileOpenSaveAs *)(pDialogFactory->requestDialog(id));
  UT_ASSERT(pDialog);
  if (!pDialog)
    return false;
  
  pDialog->runModal(m_pFrame);
  
  XAP_Dialog_FileOpenSaveAs::tAnswer ans = pDialog->getAnswer();
  bool bOK = (ans == XAP_Dialog_FileOpenSaveAs::a_OK);


  if( (bOK) && (pDialog->getPathname()) )
	     m_sModulePath = UT_strdup(pDialog->getPathname());
  

  if (m_sModulePath == 0) return false; // oops
  int length = strlen (m_sModulePath); 

  if (length > 4) if (strcmp (m_sModulePath+length-4,".pyc") == 0) m_sModulePath[length-4] = 0;
  if (length > 3) if (strcmp (m_sModulePath+length-3,".py") == 0) m_sModulePath[length-3] = 0;


  pDialogFactory->releaseDialog(pDialog);
  return true;
}

bool Gypsython::DoCommand()
{
  // Get the current view that the user is in.
  char loadmodulestring[255];
  
  if (!AskScriptFilename())
    return false; 
  
  Py_Initialize();
  
  initgypsython();	
  
  //strcpy(m_sModulePath,"E:/abiword/abi/src/WIN32_1.3.15_i386_OBJ/bin/prova.py");
  //	Well this can prevent to do a import gypsython in the script...but it's so ugly!! 
  sprintf(loadmodulestring,
	  "import sys\n"
	  "import os\n"
	  "import string\n"	
	  "import gypsython\n"   // I need my own namespace:)
	  "(filepath, filename) = os.path.split('%s')\n"  // if someone knows a better way to do this..
	  "sys.path.append(filepath)\n__import__(filename)",m_sModulePath); 
  PyRun_SimpleString(loadmodulestring); 
  
  /* PyImport_ImportModule( (char *)UT_basename(m_sModulePath));	*/	     
  
  // test row PyRun_SimpleString("import gypsython\ngypsython.insertText('from prg')");
  
  Py_Finalize();
  
  return true;
}	


// 
// Gypsython_invoke
// -------------------
//   This is the function that we actually call to invoke the 
//   embedded python 


static bool Gypsython_invoke(AV_View * v, EV_EditMethodCallData * d)
{
  
  mygypsython = new Gypsython();	
  
  mygypsython->DoCommand();
  
  return true;
  
}

static const char * Python_MenuLabel = "Run Python script";
static const char * Python_MenuTooltip = "Runs a python script";

static void
Python_RemoveFromMenus ()
{
  // First we need to get a pointer to the application itself.
  XAP_App *pApp = XAP_App::getApp();

  // remove the edit method
  EV_EditMethodContainer* pEMC = pApp->getEditMethodContainer() ;
  EV_EditMethod * pEM = ev_EditMethod_lookup ( "Gypsython_invoke" ) ;
  pEMC->removeEditMethod ( pEM ) ;
  DELETEP( pEM ) ;
  
  // now remove crap from the menus
  int frameCount = pApp->getFrameCount();
  XAP_Menu_Factory * pFact = pApp->getMenuFactory();
  
  pFact->removeMenuItem("Main",NULL,Python_MenuLabel);
  pFact->removeMenuItem("contextText",NULL,Python_MenuLabel);
  for(int i = 0;i < frameCount;++i){
    // Get the current frame that we're iterating through.
    XAP_Frame* pFrame = pApp->getFrame(i);
    pFrame->rebuildMenus();
  }
}

static void Python_addToMenus()
{
  // First we need to get a pointer to the application itself.
  XAP_App * pApp = XAP_App::getApp();
  
  // Create an EditMethod that will link our method's name with
  // it's callback function.  This is used to link the name to 
  // the callback.
  EV_EditMethod * myEditMethod = new EV_EditMethod(
						   "Gypsython_invoke",// name of callback function
						   Gypsython_invoke,// callback function itself.
						   0,// no additional data required.
						   ""// description -- allegedly never used for anything
						   );
  
  // Now we need to get the EditMethod container for the application.
  // This holds a series of Edit Methods and links names to callbacks.
  EV_EditMethodContainer * pEMC = pApp->getEditMethodContainer();
  
  // We have to add our EditMethod to the application's EditMethodList
  // so that the application will know what callback to call when a call
  // to "Gypsython_invoke" is received.
  pEMC->addEditMethod(myEditMethod);
  
  
  // Now we need to grab an ActionSet.  This is going to be used later
  // on in our for loop.  Take a look near the bottom.
  EV_Menu_ActionSet * pActionSet = pApp->getMenuActionSet();
  
  
  // We need to go through and add the menu element to each "frame" 
  // of the application.  We can iterate through the frames by doing
  // XAP_App::getFrameCount() to tell us how many frames there are,
  // then calling XAP_App::getFrame(i) to get the i-th frame.
  
  int frameCount = pApp->getFrameCount();
  XAP_Menu_Factory * pFact = pApp->getMenuFactory();
  
  // 
  // Put it in the context menu.
  // 
  XAP_Menu_Id newID = pFact->addNewMenuAfter("contextText", NULL, "Bullets and &Numbering", EV_MLF_Normal);
  pFact->addNewLabel(NULL, newID, Python_MenuLabel, Python_MenuTooltip);
  
  // 
  // Also put it under word Wount in the main menu,
  // 
  pFact->addNewMenuAfter("Main", NULL, "&Word Count", EV_MLF_Normal, newID);
  
  // Create the Action that will be called.
  EV_Menu_Action * myAction = new EV_Menu_Action(
						 newID,// id that the layout said we could use
						 0,// no, we don't have a sub menu.
						 1,// yes, we raise a  dialog.
						 0,// no, we don't have a checkbox.
						 "Gypsython_invoke",// name of callback function to call.
						 NULL,// don't know/care what this is for
						 NULL // don't know/care what this is for
						 );

  // Now what we need to do is add this particular action to the ActionSet
  // of the application.  This forms the link between our new ID that we 
  // got for this particular frame with the EditMethod that knows how to 
  // call our callback function.
  
  pActionSet->addAction(myAction);
  
  for (int i = 0; i < frameCount; ++i){
    // Get the current frame that we're iterating through.
    XAP_Frame * pFrame = pApp->getFrame(i);
    pFrame->rebuildMenus();
  }
}

// -----------------------------------------------------------------------
// 
// Abiword Plugin Interface 
// 
// -----------------------------------------------------------------------

ABI_FAR_CALL int abi_plugin_register(XAP_ModuleInfo * mi)
{
  mi->name = "Python plugin";
  mi->desc = "Python plugin";
  mi->version = ABI_VERSION_STRING;
  mi->author = "Mauro Colorio";
  mi->usage = "No Usage";
  
  // Add the Python to AbiWord's menus.
  Python_addToMenus();
  
  return 1;
}

ABI_FAR_CALL int abi_plugin_unregister(XAP_ModuleInfo * mi)
{
  mi->name = 0;
  mi->desc = 0;
  mi->version = 0;
  mi->author = 0;
  mi->usage = 0;
  
  Python_RemoveFromMenus ();
  
  return 1;
}

ABI_FAR_CALL int abi_plugin_supports_version(UT_uint32 major, UT_uint32 minor,
					     UT_uint32 release)
{
  return 1;
}
