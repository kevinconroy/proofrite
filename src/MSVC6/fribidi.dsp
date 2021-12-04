# Microsoft Developer Studio Project File - Name="fribidi" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=FRIBIDI - WIN32 DEBUG
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "fribidi.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "fribidi.mak" CFG="FRIBIDI - WIN32 DEBUG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "fribidi - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "fribidi - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "fribidi - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release\obj"
# PROP BASE Intermediate_Dir "Release\obj\fribidi"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release\obj"
# PROP Intermediate_Dir ".\Release\obj\fribidi"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /O2 /I "../fribidi" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "DYNAMIC_CRC_TABLE" /D "FRIBIDI_EXPORTS" /D "HAS_FRIBIDI_TAB_CHAR_TYPE_9_I" /D "HAS_FRIBIDI_TAB_CHAR_TYPE_2_I" /D "FRIBIDI_NO_CHARSETS" /YX /FD /GF /c
# ADD BASE RSC /l 0x41d /d "NDEBUG"
# ADD RSC /l 0x41d /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\Release\obj\fribidiMT.lib"

!ELSEIF  "$(CFG)" == "fribidi - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug\obj"
# PROP BASE Intermediate_Dir "Debug\obj\fribidi"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug\obj"
# PROP Intermediate_Dir ".\Debug\obj\fribidi"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Zi /Od /Ob1 /Gy /I "../fribidi" /D "WIN32" /D "DEBUG" /D "_DEBUG" /D "FRIBIDI_EXPORTS" /D "HAS_FRIBIDI_TAB_CHAR_TYPE_9_I" /D "HAS_FRIBIDI_TAB_CHAR_TYPE_2_I" /D "FRIBIDI_NO_CHARSETS" /D "STDC_HEADERS" /FR /FD /GZ /GF /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x41d /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "fribidi - Win32 Release"
# Name "fribidi - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\fribidi\config.h.in

!IF  "$(CFG)" == "fribidi - Win32 Release"

!ELSEIF  "$(CFG)" == "fribidi - Win32 Debug"

# Begin Custom Build
InputPath=..\fribidi\config.h.in

"..\fribidi\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\fribidi\config.h.in ..\fribidi\config.h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\fribidi\fribidi.c
# End Source File
# Begin Source File

SOURCE=..\fribidi\fribidi_char_type.c
# End Source File
# Begin Source File

SOURCE=..\fribidi\fribidi_mem.c
# End Source File
# Begin Source File

SOURCE=..\fribidi\fribidi_mirroring.c
# End Source File
# Begin Source File

SOURCE=..\fribidi\fribidi_types.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\fribidi\fribidi.h
# End Source File
# Begin Source File

SOURCE=..\fribidi\fribidi_config.h
# End Source File
# Begin Source File

SOURCE=..\fribidi\fribidi_mem.h
# End Source File
# Begin Source File

SOURCE=..\fribidi\fribidi_types.h
# End Source File
# Begin Source File

SOURCE=..\fribidi\fribidi_unicode.h
# End Source File
# End Group
# End Target
# End Project
