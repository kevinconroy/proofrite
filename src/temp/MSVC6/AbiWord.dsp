# Microsoft Developer Studio Project File - Name="AbiWord" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ABIWORD - WIN32 DEBUG
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AbiWord.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AbiWord.mak" CFG="ABIWORD - WIN32 DEBUG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AbiWord - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "AbiWord - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AbiWord - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug\bin"
# PROP Intermediate_Dir ".\Debug\obj"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Z7 /Od /Ob1 /Gy /I "..\abi\src\wp\ap\xp" /I "..\abi\src\wp\ap\win" /I "..\abi\src\wp\ap\xp\ToolbarIcons" /I "..\abi\src\wp\impexp\xp" /I "..\abi\src\text\fmt\xp" /I "..\abi\src\text\ptbl\xp" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell" /I "..\expat\xmlparse" /I "..\expat\xmltok" /D "_X86_" /D "DEBUG" /D "_DEBUG" /D "_CTRDBG_MAP_ALLOC" /D "WIN32" /D "UT_DEBUG" /D "PT_TEST" /D "FMT_TEST" /D ABIWORD_APP_LIBDIR=\""AbiWord"\" /D "UT_TEST" /D ABIWORD_APP_NAME=\""AbiWord"\" /GF /c
# ADD CPP /nologo /MDd /W3 /Zi /Od /Ob1 /Gy /I "..\abi\src\wp\ap\xp" /I "..\abi\src\wp\ap\win" /I "..\abi\src\wp\ap\xp\ToolbarIcons" /I "..\abi\src\wp\impexp\xp" /I "..\abi\src\text\fmt\xp" /I "..\abi\src\text\ptbl\xp" /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\expat\xmlparse" /I "..\expat\xmltok" /I "..\expat\lib" /I "..\popt" /D "DEBUG" /D "_DEBUG" /D "_CTRDBG_MAP_ALLOC" /D "UT_DEBUG" /D "PT_TEST" /D "FMT_TEST" /D "UT_TEST" /D ABIWORD_APP_NAME=\""AbiWord"\" /D ABIWORD_APP_LIBDIR=\""AbiWord"\" /D "_X86_" /D "WIN32" /D "FRIBIDI_EXPORTS" /Fr /GF /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /i "..\abi\src\af\xap\win" /i "..\abi\src\wp\ap\win" /i "..\..\ap\win" /i "..\..\..\af\xap\win" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 msvcprtd.lib MSVCRTD.LIB kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib uuid.lib comctl32.lib ole32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:".\Debug\obj"
# SUBTRACT LINK32 /verbose /profile /incremental:no

!ELSEIF  "$(CFG)" == "AbiWord - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AbiWord___Win32_Release"
# PROP BASE Intermediate_Dir "AbiWord___Win32_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Release\bin"
# PROP Intermediate_Dir ".\Release\obj"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Zi /Od /Ob1 /Gy /I "..\abi\src\wp\ap\xp" /I "..\abi\src\wp\ap\win" /I "..\abi\src\wp\ap\xp\ToolbarIcons" /I "..\abi\src\wp\impexp\xp" /I "..\abi\src\text\fmt\xp" /I "..\abi\src\text\ptbl\xp" /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /D "_X86_" /D "DEBUG" /D "_DEBUG" /D "_CTRDBG_MAP_ALLOC" /D "WIN32" /D "UT_DEBUG" /D "PT_TEST" /D "FMT_TEST" /D ABIWORD_APP_LIBDIR=\""AbiWord"\" /D "UT_TEST" /D ABIWORD_APP_NAME=\""AbiWord"\" /GF /c
# SUBTRACT BASE CPP /Fr /YX
# ADD CPP /nologo /MD /W3 /Zi /O1 /Ob2 /I "..\abi\src\wp\ap\xp" /I "..\abi\src\wp\ap\win" /I "..\abi\src\wp\ap\xp\ToolbarIcons" /I "..\abi\src\wp\impexp\xp" /I "..\abi\src\text\fmt\xp" /I "..\abi\src\text\ptbl\xp" /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\expat\xmlparse" /I "..\expat\xmltok" /I "..\expat\lib" /I "..\popt" /D "NDEBUG" /D "WIN32" /D ABIWORD_APP_NAME=\""AbiWord"\" /D ABIWORD_APP_LIBDIR=\""AbiWord"\" /D _X86_ /D FRIBIDI_EXPORTS /GF /c
# ADD BASE RSC /l 0x409 /i "..\abi\src\af\xap\win" /i "..\abi\src\wp\ap\win" /d "_DEBUG"
# ADD RSC /l 0x409 /i "..\abi\src\af\xap\win" /i "..\abi\src\wp\ap\win" /i "..\..\ap\win" /i "..\..\..\af\xap\win" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib uuid.lib comctl32.lib libAbi_expat_s.lib libAbi_libiconv_s.lib libAbi_libwv_s.lib libAbiEv_s.lib libAbiGr_s.lib libAbiUtil_s.lib libAbiXap_s.lib libAbiSpell_s.lib libAbiPTbl_s.lib libAbiFmt_s.lib libAbiWPAp_s.lib libAbiImpExp_s.lib msvcprt.lib libAbiWordVer_s.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:".\Debug\obj"
# SUBTRACT BASE LINK32 /incremental:no
# ADD LINK32 msvcprt.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib uuid.lib comctl32.lib ole32.lib /nologo /subsystem:windows /profile /map /debug /machine:I386 /libpath:".\Debug\obj"
# SUBTRACT LINK32 /verbose

!ENDIF 

# Begin Target

# Name "AbiWord - Win32 Debug"
# Name "AbiWord - Win32 Release"
# Begin Source File

SOURCE=..\abi\src\wp\ap\win\abiword_app_16.ico
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\main\win\abiword_app_16.ico
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\ap\win\abiword_app_32.ico
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\main\win\abiword_app_32.ico
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\ap\win\abiword_doc_16.ico
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\main\win\abiword_doc_16.ico
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\ap\win\abiword_doc_32.ico
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\main\win\abiword_doc_32.ico
# End Source File
# Begin Source File

SOURCE=.\ap_wp_sidebar.cpp
# End Source File
# Begin Source File

SOURCE=.\ap_wp_splash.cpp
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\exchange.cur
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\main\win\exchange.cur
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\hand1.cur
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\main\win\hand1.cur
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\main\win\Win32Main.cpp
DEP_CPP_WIN32=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\win\xap_Win32_TB_CFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32App.h"\
	"..\abi\src\af\xap\win\xap_Win32Clipboard.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Args.h"\
	"..\abi\src\af\xap\xp\xap_Clipboard.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Prefs.h"\
	"..\abi\src\af\xap\xp\xap_Prefs_SchemeIds.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_ControlFactory.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\wp\ap\win\ap_Win32App.h"\
	"..\abi\src\wp\ap\win\ap_Win32Clipboard.h"\
	"..\abi\src\wp\ap\win\ap_Win32Prefs.h"\
	"..\abi\src\wp\ap\xp\ap_App.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs_SchemeIds.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	"..\popt\popt.h"\
	
NODEP_CPP_WIN32=\
	"..\abi\src\wp\ap\xp\xap_BeOSApp.h"\
	"..\abi\src\wp\ap\xp\xap_CocoaApp.h"\
	"..\abi\src\wp\ap\xp\xap_MacApp.h"\
	"..\abi\src\wp\ap\xp\xap_QNXApp.h"\
	"..\abi\src\wp\ap\xp\xap_UnixApp.h"\
	"..\abi\src\wp\ap\xp\xap_UnixGnomeApp.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\main\win\Win32Main.rc
# End Source File
# End Target
# End Project
