/*
 * Shell Script plugin for AbiWord
 * Copyright (C) 2002 by Dom Lachowicz, Jeremy Davis, and others
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

#include <stdlib.h>
#include <stdio.h>

// Abi includes

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

#include "ut_Script.h"

#ifdef WIN32
#include <windows.h>
#include <ctype.h>
#include "fakepopen.h"
#define SETENV_MISSING
static void preProcessLine(char *data, int len, int bufSize);
#endif

/*!
 * This plugin doesn't actually do anything... well, ok maybe it does
 * This plugin exports 2 editmethods that other plugins can call
 * themselves. The methods:
 *
 * scriptHappy_Invoke : just execute a command
 * scriptHappy_Capture : execute a command and capture its results,
 *                       inserting them back into the current working document
 *
 * The command to invoke is contained in the EV_EditMethodCallData's struct
 * m_pData member variable as a UCS string.
 *
 * This plugin also exports a number of variables to the world before
 * executing the script. These current exported variables are:
 *
 * ABI_SCRIPT_BUILD_ID : the application's build id
 * ABI_SCRIPT_BUILD_VERSION : the application's version
 * ABI_SCRIPT_BUILD_OPTIONS : the application's build options
 * ABI_SCRIPT_BUILD_TARGET : the application's target
 * ABI_SCRIPT_BUILD_COMPILE_TIME : the application's compile time
 * ABI_SCRIPT_BUILD_COMPILE_DATE : the application's compile date
 * ABI_SCRIPT_CURRENT_FILENAME : the current working document's name
 * ABI_SCRIPT_CURRENT_TITLE : the current working document's title
 * ABI_SCRIPT_CURRENT_WORDCOUNT : the current working document's word count
 * ABI_SCRIPT_CURRENT_PARACOUNT : the current working document's paragraph count
 * ABI_SCRIPT_CURRENT_CHARCOUNT : the current working document's character count
 * ABI_SCRIPT_CURRENT_SPACECOUNT : the current working document's space count
 * ABI_SCRIPT_CURRENT_LINECOUNT : the current working document's line count
 * ABI_SCRIPT_CURRENT_PAGECOUNT : the current working document's page count
 *
 */

class ABI_EXPORT ScriptHappy : public UT_Script
{
public:
  ScriptHappy ()
    : mErrorMsg("")
  {
  }

  virtual ~ScriptHappy ()
  {
  }

  virtual UT_Error execute(const char * scriptName)
  {
    mErrorMsg = "" ;
    if ( ev_EditMethod_exists ( "scriptHappy_Capture" ) )
      {
	bool bRet = ev_EditMethod_invoke ( "scriptHappy_Capture",
					   scriptName ) ;

	if ( !bRet )
	  {
	    mErrorMsg = "ScriptHappy didn't work" ;
	    UT_DEBUGMSG(("DOM: scriptHappy_Capture did not work\n"));
	    return UT_ERROR ;
	  }

	UT_DEBUGMSG(("DOM: scriptHappy worked!\n"));
	return UT_OK;
      }
    else
      {
	mErrorMsg = "ScriptHappy not installed" ;
	UT_DEBUGMSG(("DOM: scriptHappy_Capture not installed??\n"));
	    return UT_ERROR ;
      }
  }

  virtual const UT_String& errmsg() const
  {
    return mErrorMsg ;
  }

private:
  UT_String mErrorMsg ;

} ;

class ABI_EXPORT ScriptHappy_Sniffer : public UT_ScriptSniffer
{
public :
  ScriptHappy_Sniffer()
  {
  }

  virtual ~ScriptHappy_Sniffer()
  {
  }

  virtual bool recognizeContents (const char * szBuf, 
				  UT_uint32 iNumbytes)
  {
    // TODO!!
    return true ;
  }

  virtual bool recognizeSuffix (const char * szSuffix)
  {
    // TODO!!
    return true ;
  }

  virtual bool getDlgLabels (const char ** szDesc,
			     const char ** szSuffixList,
			     UT_ScriptIdType * ft)
  {
    *szDesc = "Any Executable file" ;
    *szSuffixList = "*.*";
    *ft = getType();
    return true ;
  }

  virtual UT_Error constructScript (UT_Script ** ppscript)
  {
    UT_DEBUGMSG(("DOM: creating new ScriptHappy\n"));
    *ppscript = new ScriptHappy () ;
    return UT_OK ;
  }

} ;

/*************************************************************************/
/*************************************************************************/

static void ScriptHappy_RegisterPorts () ;
static void ScriptHappy_UnregisterPorts () ;

static EV_EditMethod * invokeMethod = NULL ;
static EV_EditMethod * captureMethod = NULL ;
static ScriptHappy_Sniffer * mSniffer = NULL ;

/*************************************************************************/
/*************************************************************************/

ABI_PLUGIN_DECLARE(ScriptHappy);

ABI_FAR_CALL
int abi_plugin_register (XAP_ModuleInfo * mi)
{
  mi->name = "ScriptHappy";
  mi->desc = "Run other programs from within AbiWord";
  mi->version = ABI_VERSION_STRING;
  mi->author = "Dom Lachowicz <cinamod@hotmail.com>";
  mi->usage = "No Usage";
  
  ScriptHappy_RegisterPorts () ;
  
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
  
  ScriptHappy_UnregisterPorts () ;

  return 1;
}

ABI_FAR_CALL
int abi_plugin_supports_version (UT_uint32 major, UT_uint32 minor, UT_uint32 release)
{
  return 1; 
}

/*************************************************************************/
/*************************************************************************/

// TODO: move this to a more global place - UT_Setenv would be nice ;-)
static void ScriptHappy_SetEnv ( const char * key, const char * value )
{
  if ( !key || !value ) 
    return ;

#if defined(SETENV_MISSING)
  UT_String var ( key ) ;
  var += "=" ;
  var += value ;
  putenv ( var.c_str() ) ;
#else
  setenv ( key, value, 1 ) ;
#endif
}

inline static char*
ScriptHappy_ucsToAscii( const UT_UCSChar* text, UT_uint32 length )
{
  // allocate ascii characters plus room for a null terminator.    
  char* ret = new char[ length+1 ] ;
  
  // do the string conversion.  this is simple we just cast to 
  // char since UCS-2 is the same as Ascii for english.    
  for( unsigned int i = 0; i < length; ++i )
    {
      ret[ i ] = ( char )text[ i ] ;
    }
  
  // finally null terminate the string.    
  ret[ length ] = ret[ length+1] = 0 ;
  
  // and now return it.
  return ret ;    
}

inline static UT_UCSChar* 
ScriptHappy_asciiToUcs( const char* text, int& length )
{
    // calculate the length of our text so we can create a UCS-2
  // buffer of equal size.
  length = strlen( text ) ;
  
  // allocate UCS-2 character buffer of same size, plus room for 
  // a null terminator.    
  UT_UCSChar* ret = new UT_UCSChar[ length+1 ] ;
  
    // convert ascii to UCS-2.  This is simply a cast-loop really.
  for( int i = 0; i < length; ++i )
    {
      ret[ i ] = ( UT_UCSChar )text[ i ] ;
    }
    
  // remember to null terminate the string.
  ret[ length ] = 0 ;
  
  // now return the string.
  return ret ;
}

/*************************************************************************/
/*************************************************************************/

static void ScriptHappy_ExportVariables ( FV_View * v )
{
  XAP_App * pApp = XAP_App::getApp () ;
  
  // things exported from the app
  ScriptHappy_SetEnv ( "ABI_SCRIPT_BUILD_ID", XAP_App::getBuildId() ) ;
  ScriptHappy_SetEnv ( "ABI_SCRIPT_BUILD_VERSION", XAP_App::getBuildVersion() ) ;
  ScriptHappy_SetEnv ( "ABI_SCRIPT_BUILD_OPTIONS", XAP_App::getBuildOptions() ) ;
  ScriptHappy_SetEnv ( "ABI_SCRIPT_BUILD_TARGET", XAP_App::getBuildTarget() ) ;
  ScriptHappy_SetEnv ( "ABI_SCRIPT_BUILD_COMPILE_TIME", XAP_App::getBuildCompileTime() ) ;
  ScriptHappy_SetEnv ( "ABI_SCRIPT_BUILD_COMPILE_DATE", XAP_App::getBuildCompileDate() ) ;

  XAP_Frame * pFrame = pApp->getLastFocussedFrame () ;

  // things exported from the frame
  ScriptHappy_SetEnv ( "ABI_SCRIPT_CURRENT_FILENAME", pFrame->getFilename () ) ;
  ScriptHappy_SetEnv ( "ABI_SCRIPT_CURRENT_TITLE", pFrame->getTitle ( 256 ) ) ;

  // things exported from the view
  FV_DocCount docCount = v->countWords () ;

  ScriptHappy_SetEnv ( "ABI_SCRIPT_CURRENT_WORDCOUNT", UT_String_sprintf ("%u", docCount.word).c_str() ) ;
  ScriptHappy_SetEnv ( "ABI_SCRIPT_CURRENT_PARACOUNT", UT_String_sprintf ("%u", docCount.para).c_str() ) ;
  ScriptHappy_SetEnv ( "ABI_SCRIPT_CURRENT_CHARCOUNT", UT_String_sprintf ("%u", docCount.ch_no).c_str() ) ;
  ScriptHappy_SetEnv ( "ABI_SCRIPT_CURRENT_SPACECOUNT", UT_String_sprintf ("%u", docCount.ch_sp).c_str() ) ;
  ScriptHappy_SetEnv ( "ABI_SCRIPT_CURRENT_LINECOUNT", UT_String_sprintf ("%u", docCount.line).c_str() ) ;
  ScriptHappy_SetEnv ( "ABI_SCRIPT_CURRENT_PAGECOUNT", UT_String_sprintf ("%u", docCount.page).c_str() ) ;

  return ;
}

static bool ScriptHappy_Invoke( AV_View* v, EV_EditMethodCallData *d )
{
  if ( v && d && d->m_pData && d->m_dataLength )
    {
      FV_View * view = static_cast<FV_View *>(v) ;
      ScriptHappy_ExportVariables( view ) ;
      
      // the command to execute
      char * callData = ScriptHappy_ucsToAscii ( d->m_pData, d->m_dataLength ) ;
      UT_DEBUGMSG(("DOM: trying to invoke %s\n",callData));

      int rtn = system ( callData ) ;

      if (!rtn)
	{
	  UT_DEBUGMSG(("DOM: call failed\n"));
	}

      DELETEPV( callData ) ;
      
      return ( rtn == 0 ? true : false ) ;
    }
  UT_DEBUGMSG(("DOM: not running scripthappy_invoke - assertion failed\n"));
  return false ;
}

static bool ScriptHappy_Capture( AV_View* v, EV_EditMethodCallData *d )
{  
  if ( v && d && d->m_pData && d->m_dataLength )
    {
      FV_View * view = static_cast<FV_View *>(v) ;
      ScriptHappy_ExportVariables( view ) ;
      
      // the command to execute
      char * command = ScriptHappy_ucsToAscii ( d->m_pData, d->m_dataLength ) ;

      UT_DEBUGMSG(("DOM: trying to capture '%s'\n",command));
      
      // open up a pipe for reading
#ifdef WIN32
      PIPE * pipe;
#else
      FILE * pipe;
#endif
      pipe = popen ( command, "r" ) ;
      if ( !pipe )
	{
	  UT_DEBUGMSG(("Couldn't execute pipe\n"));
	  DELETEPV ( command );
	  return false ;
	}
      DELETEPV ( command ) ;      
            
      char script_output [ 64 ] = "" ;

#if 0
      // prime the buffer - not sure why this is needed, it just doesn't
      // work without this pre-read
      fgets ( script_output, sizeof(script_output), pipe ) ;
#endif

      // suck in our data
#ifdef WIN32
      DWORD bytesRead;
      while ( ReadFile(pipe->hChildStdOut, script_output, sizeof(script_output)-1, &bytesRead, NULL) && bytesRead)
#else
      while ( fgets ( script_output, sizeof ( script_output ), pipe ) != NULL )
#endif
	{
#ifdef WIN32
	  // note we require sizeof(script_output) to <= MAX_SIGNED_INT, and assume we read at least 1 less bytes
	  preProcessLine(script_output, (int)bytesRead, sizeof(script_output));
#endif
	  int howMany = 0 ;
	  UT_UCSChar * script_ucsdata = ScriptHappy_asciiToUcs ( script_output, howMany ) ;
	  if ( howMany )
            view->cmdCharInsert ( script_ucsdata, howMany );
	  DELETEPV ( script_ucsdata ) ;
	}
      
#ifdef WIN32
	{
		// we only provide a limited view of stderr's output
		char maxMsg[ 1024 ];
      	if ( ReadFile(pipe->hChildStdErr, maxMsg, sizeof(maxMsg)-1, &bytesRead, NULL) && bytesRead)
		{
		  preProcessLine(maxMsg, (int)bytesRead, sizeof(maxMsg));
		  UT_String stderrMsg;
		  stderrMsg = "Data was output on child's stderr, partial output follows:\n";
		  stderrMsg += maxMsg;
		  MessageBox(NULL, stderrMsg.c_str(), "Text found on stderr ...", MB_OK);
		}
	}
#endif
      
      // close the pipe
      pclose ( pipe ) ;
      
      return true ;
    }

  UT_DEBUGMSG(("DOM: not running scripthappy_capture - assertion failed\n"));
  return false ;
}

static void ScriptHappy_UnregisterPorts ()
{
  // Get the EditMethod container for the application.
  EV_EditMethodContainer* pEMC = XAP_App::getApp()->getEditMethodContainer() ;

  if ( invokeMethod )
    {
      pEMC->removeEditMethod ( invokeMethod ) ;
      DELETEP( invokeMethod ) ;
    }
  
  if ( captureMethod )
    {
      pEMC->removeEditMethod ( captureMethod ) ;
      DELETEP( captureMethod ) ;
    }

  // unregister this plugin
  UT_ASSERT( mSniffer ) ;
  UT_ScriptLibrary::instance().unregisterScript ( mSniffer ) ;
  DELETEP( mSniffer ) ;
  UT_DEBUGMSG(("DOM: unregistered script!\n"));
}

static void ScriptHappy_RegisterPorts ()
{
  // Now we need to get the EditMethod container for the application.
  // This holds a series of Edit Methods and links names to callbacks.
  EV_EditMethodContainer* pEMC = XAP_App::getApp()->getEditMethodContainer() ;
  
  // Create an EditMethod that will link our method's name with
  // it's callback function.  This is used to link the name to 
  // the callback.
  invokeMethod = new EV_EditMethod(
				   "scriptHappy_Invoke",  // name of callback function
				   ScriptHappy_Invoke,    // callback function itself.
				   0,                      // no additional data required.
				   ""                      // description -- allegedly never used for anything
				   ) ;
  
  // Create an EditMethod that will link our method's name with
  // it's callback function.  This is used to link the name to 
  // the callback.
  captureMethod = new EV_EditMethod(
				    "scriptHappy_Capture",  // name of callback function
				    ScriptHappy_Capture,    // callback function itself.
				    0,                      // no additional data required.
				    ""                      // description -- allegedly never used for anything
				    ) ;
  
  // We have to add our EditMethod to the application's EditMethodList
  pEMC->addEditMethod ( invokeMethod ) ;
  pEMC->addEditMethod ( captureMethod ) ;

  // register a sniffer
  mSniffer = new ScriptHappy_Sniffer () ;
  UT_ScriptLibrary::instance().registerScript ( mSniffer ) ;
  UT_DEBUGMSG(("DOM: registered script!\n"));
}


// Windows utility functions
#ifdef WIN32

// converts \r\n or \n\r to just \n
// ensure's '\0' terminated (if adjusted_len==bufSize then last character lost)
// convert any OEM data to something displayable (instead of blocks[])
void preProcessLine(char *data, int len, int bufSize)
{
	if (data==NULL) return;
	char *buffer = new char[bufSize];
	if (buffer == NULL) return;

	int j = 0;
	for (register int i = 0; i < len; i++, j++)
	{
		register char value = data[i];
		switch (value)
		{
			case '\n':
			case '\r':
			{
				register char lookingfor = (value == '\r')?'\n':'\r';
				if ((i+1 < len) && (data[i+1] == lookingfor))
					i++; // skip next character

				buffer[j] = '\n';
				break;
			}
			default:
			{
				//UT_DEBUGMSG(("KJD: %c [%i]\n", value, (unsigned int)value));
				buffer[j]=(isascii(value))?value:'?';
				break;
			}	
		}
	}

	len = (j < bufSize)?j:j-1;
	buffer[len] = '\0'; // ensure '\0' terminated
	memcpy(data, buffer, len+1);
	delete[] buffer;

	// a better approach of course would be to map to unicode equivalent during conversion to UCS
	OemToCharA(data, data);
}

#endif  /* WIN32 */
