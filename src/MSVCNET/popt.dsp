# Microsoft Developer Studio Project File - Name="popt" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=POPT - WIN32 DEBUG
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "popt.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "popt.mak" CFG="POPT - WIN32 DEBUG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "popt - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "popt - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "popt - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "popt___Win32_Release"
# PROP BASE Intermediate_Dir "popt___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release\obj"
# PROP Intermediate_Dir "Release\obj\popt"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /O2 /I "../popt" /I "../popt/intl" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /D "HAVE_STRING" /D X_OK=0 /YX /FD /c
# ADD BASE RSC /l 0x41d /d "NDEBUG"
# ADD RSC /l 0x41d /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "popt - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "popt___Win32_Debug"
# PROP BASE Intermediate_Dir "popt___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug\obj"
# PROP Intermediate_Dir "Debug\obj\popt"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /ZI /Od /I "../popt" /I "../popt/intl" /D "_DEBUG" /D "HAVE_STRING" /D X_OK=0 /D "WIN32" /D "_MBCS" /D "_LIB" /D "HAVE_CONFIG_H" /YX /FD /GZ /c
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

# Name "popt - Win32 Release"
# Name "popt - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\popt\findme.c
# End Source File
# Begin Source File

SOURCE=..\popt\popt.c
# End Source File
# Begin Source File

SOURCE=..\popt\poptconfig.c
# End Source File
# Begin Source File

SOURCE=..\popt\popthelp.c
# End Source File
# Begin Source File

SOURCE=..\popt\poptparse.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\popt\findme.h
# End Source File
# Begin Source File

SOURCE=..\popt\popt.h
# End Source File
# Begin Source File

SOURCE=..\popt\poptint.h
# End Source File
# End Group
# End Target
# End Project
