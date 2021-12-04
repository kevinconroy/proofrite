# Microsoft Developer Studio Project File - Name="libpng" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=LIBPNG - WIN32 DEBUG
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libpng.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libpng.mak" CFG="LIBPNG - WIN32 DEBUG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libpng - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libpng - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libpng - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release\obj\"
# PROP Intermediate_Dir ".\Release\obj\libpng"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\zlib" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /YX /FD /GF /c
# ADD BASE RSC /l 0x41d /d "NDEBUG"
# ADD RSC /l 0x41d /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "libpng - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug\obj\libpng"
# PROP Intermediate_Dir "Debug\obj\libpng"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /Od /I "..\zlib" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /YX /FD /GZ /GF /c
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

# Name "libpng - Win32 Release"
# Name "libpng - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\libpng\png.c
# End Source File
# Begin Source File

SOURCE=..\libpng\pngerror.c
# End Source File
# Begin Source File

SOURCE=..\libpng\pngget.c
# End Source File
# Begin Source File

SOURCE=..\libpng\pngmem.c
# End Source File
# Begin Source File

SOURCE=..\libpng\pngpread.c
# End Source File
# Begin Source File

SOURCE=..\libpng\pngread.c
# End Source File
# Begin Source File

SOURCE=..\libpng\pngrio.c
# End Source File
# Begin Source File

SOURCE=..\libpng\pngrtran.c
# End Source File
# Begin Source File

SOURCE=..\libpng\pngrutil.c
# End Source File
# Begin Source File

SOURCE=..\libpng\pngset.c
# End Source File
# Begin Source File

SOURCE=..\libpng\pngtrans.c
# End Source File
# Begin Source File

SOURCE=..\libpng\pngwio.c
# End Source File
# Begin Source File

SOURCE=..\libpng\pngwrite.c
# End Source File
# Begin Source File

SOURCE=..\libpng\pngwtran.c
# End Source File
# Begin Source File

SOURCE=..\libpng\pngwutil.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\libpng\png.h
# End Source File
# Begin Source File

SOURCE=..\libpng\pngconf.h
# End Source File
# End Group
# End Target
# End Project
