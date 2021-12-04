# Microsoft Developer Studio Project File - Name="expat" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=EXPAT - WIN32 DEBUG
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "expat.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "expat.mak" CFG="EXPAT - WIN32 DEBUG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "expat - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "expat - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "expat - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug\obj"
# PROP Intermediate_Dir ".\Debug\obj\expat"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Z7 /Od /Ob1 /Gy /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell\\" /I "..\expat\xmlparse" /I "..\expat\xmltok" /D "_X86_" /D "DEBUG" /D "_DEBUG" /D "_CTRDBG_MAP_ALLOC" /D "WIN32" /D "UT_DEBUG" /D "PT_TEST" /D "FMT_TEST" /D "UT_TEST" /GF /c
# ADD CPP /nologo /MDd /W3 /Zi /Od /Ob1 /Gy /I "..\expat\xmlparse" /I "..\expat\xmltok" /I "..\expat\lib" /D "DEBUG" /D "_DEBUG" /D "_CTRDBG_MAP_ALLOC" /D "UT_DEBUG" /D "PT_TEST" /D "FMT_TEST" /D "UT_TEST" /D "_X86_" /D "WIN32" /D "COMPILED_FROM_DSP" /GF /c
# ADD BASE RSC /l 0x41d
# ADD RSC /l 0x41d
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\Debug\obj\libAbi_expat_s.lib"

!ELSEIF  "$(CFG)" == "expat - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "expat___Win32_Release"
# PROP BASE Intermediate_Dir "expat___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Release\obj"
# PROP Intermediate_Dir ".\Release\obj\expat"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Z7 /Od /Ob1 /Gy /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell\\" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\wv" /D "_X86_" /D "DEBUG" /D "_DEBUG" /D "_CTRDBG_MAP_ALLOC" /D "WIN32" /D "UT_DEBUG" /D "PT_TEST" /D "FMT_TEST" /D "UT_TEST" /GF /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MD /W3 /Zi /O1 /Ob2 /I "..\expat\xmlparse" /I "..\expat\xmltok" /I "..\expat\lib" /D "NDEBUG" /D "_X86_" /D "WIN32" /D "COMPILED_FROM_DSP" /GF /c
# ADD BASE RSC /l 0x41d
# ADD RSC /l 0x41d
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\Debug\obj\libAbi_expat_s.lib"
# ADD LIB32 /nologo /out:".\Release\obj\libAbi_expat_s.lib"

!ENDIF 

# Begin Target

# Name "expat - Win32 Debug"
# Name "expat - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "c"
# Begin Source File

SOURCE=..\expat\lib\xmlparse.c
DEP_CPP_XMLPA=\
	"..\expat\lib\config.h"\
	"..\expat\lib\expat.h"\
	"..\expat\lib\winconfig.h"\
	"..\expat\lib\xmlrole.h"\
	"..\expat\lib\xmltok.h"\
	
# ADD CPP /D VERSION=\"expat_1.95.1\"
# End Source File
# Begin Source File

SOURCE=..\expat\lib\xmlrole.c
DEP_CPP_XMLRO=\
	"..\expat\lib\ascii.h"\
	"..\expat\lib\config.h"\
	"..\expat\lib\winconfig.h"\
	"..\expat\lib\xmlrole.h"\
	"..\expat\lib\xmltok.h"\
	
# End Source File
# Begin Source File

SOURCE=..\expat\lib\xmltok.c
DEP_CPP_XMLTO=\
	"..\expat\lib\ascii.h"\
	"..\expat\lib\asciitab.h"\
	"..\expat\lib\config.h"\
	"..\expat\lib\iasciitab.h"\
	"..\expat\lib\latin1tab.h"\
	"..\expat\lib\nametab.h"\
	"..\expat\lib\utf8tab.h"\
	"..\expat\lib\winconfig.h"\
	"..\expat\lib\xmltok.h"\
	"..\expat\lib\xmltok_impl.c"\
	"..\expat\lib\xmltok_impl.h"\
	"..\expat\lib\xmltok_ns.c"\
	
# End Source File
# Begin Source File

SOURCE=..\expat\lib\xmltok_impl.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\expat\lib\xmltok_ns.c
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\expat\lib\ascii.h
# End Source File
# Begin Source File

SOURCE=..\expat\lib\asciitab.h
# End Source File
# Begin Source File

SOURCE=..\expat\lib\expat.h
# End Source File
# Begin Source File

SOURCE=..\expat\lib\iasciitab.h
# End Source File
# Begin Source File

SOURCE=..\expat\lib\latin1tab.h
# End Source File
# Begin Source File

SOURCE=..\expat\lib\nametab.h
# End Source File
# Begin Source File

SOURCE=..\expat\lib\utf8tab.h
# End Source File
# Begin Source File

SOURCE=..\expat\lib\winconfig.h
# End Source File
# Begin Source File

SOURCE=..\expat\lib\xmlrole.h
# End Source File
# Begin Source File

SOURCE=..\expat\lib\xmltok.h
# End Source File
# Begin Source File

SOURCE=..\expat\lib\xmltok_impl.h
# End Source File
# End Group
# End Target
# End Project
