# Microsoft Developer Studio Project File - Name="libpsiconv" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libpsiconv - Win32 BIDI Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libpsiconv.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libpsiconv.mak" CFG="libpsiconv - Win32 BIDI Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libpsiconv - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libpsiconv - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libpsiconv - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "libpsiconv___Win32_Release"
# PROP BASE Intermediate_Dir "libpsiconv___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release\obj\"
# PROP Intermediate_Dir "Release\obj\libpsiconv"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /I "..\psiconv" /I "..\psiconv\compat" /I "..\wv" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FD /GF /c
# ADD BASE RSC /l 0x41d /d "NDEBUG"
# ADD RSC /l 0x41d /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "libpsiconv - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "libpsiconv___Win32_Debug"
# PROP BASE Intermediate_Dir "libpsiconv___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug\obj\libpsiconv"
# PROP Intermediate_Dir ".\Debug\obj\libpsiconv"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\psiconv" /I "..\psiconv\compat" /I "..\wv" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D snprintf=_snprintf /D vsnprintf=_vsnprintf /FD /GZ /GF /c
# ADD BASE RSC /l 0x41d /d "_DEBUG"
# ADD RSC /l 0x41d /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "libpsiconv - Win32 Release"
# Name "libpsiconv - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\psiconv\psiconv\buffer.c
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\checkuid.c
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\data.c
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\error.c
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\generate_common.c
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\generate_driver.c
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\generate_image.c
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\generate_layout.c
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\generate_page.c
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\generate_simple.c
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\generate_texted.c
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\generate_word.c
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\list.c
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\misc.c
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\parse_common.c
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\parse_driver.c
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\parse_formula.c
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\parse_image.c
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\parse_layout.c
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\parse_page.c
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\parse_sheet.c
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\parse_simple.c
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\parse_texted.c
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\parse_word.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\psiconv\psiconv\buffer.h
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\common.h
# End Source File
# Begin Source File

SOURCE=..\psiconv\config.h
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\data.h
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\error.h
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\general.h
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\generate.h
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\generate_routines.h
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\list.h
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\parse.h
# End Source File
# Begin Source File

SOURCE=..\psiconv\psiconv\parse_routines.h
# End Source File
# End Group
# Begin Group "compat Source files"

# PROP Default_Filter "c,cpp"
# Begin Source File

SOURCE=..\psiconv\compat\dummy.c
# End Source File
# Begin Source File

SOURCE=..\psiconv\compat\getopt.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\psiconv\compat\getopt1.c
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "compat Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\psiconv\compat\compat.h
# End Source File
# Begin Source File

SOURCE=..\psiconv\compat\getopt.h
# PROP Exclude_From_Build 1
# End Source File
# End Group
# End Target
# End Project
