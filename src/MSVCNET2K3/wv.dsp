# Microsoft Developer Studio Project File - Name="wv" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=WV - WIN32 DEBUG
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "wv.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wv.mak" CFG="WV - WIN32 DEBUG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "wv - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "wv - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug\obj"
# PROP Intermediate_Dir ".\Debug\obj\wv"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Z7 /Od /Ob1 /Gy /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell" /I "..\expat\xmlparse" /I "..\expat\xmltok" /D "_X86_" /D "DEBUG" /D "_DEBUG" /D "_CTRDBG_MAP_ALLOC" /D "WIN32" /D "UT_DEBUG" /D "PT_TEST" /D "FMT_TEST" /D "UT_TEST" /GF /c
# ADD CPP /nologo /MDd /W3 /Zi /Od /Ob1 /Gy /I "." /I "..\wv" /I "..\wv\exporter" /I "..\libiconv\include" /I "..\wv\oledecod" /I "..\wv\libole2" /I "..\wv\glib-wv" /I "..\wv\libole2\system-includes" /I "..\wv\expat\xmlparse" /I "..\expat\lib" /D "DEBUG" /D "_DEBUG" /D "_CTRDBG_MAP_ALLOC" /D "UT_DEBUG" /D "PT_TEST" /D "FMT_TEST" /D "UT_TEST" /D CONFIGFILE=\".mswordview\" /D TTFDIR=\"\" /D SYBMOLFONTDIR=\"\" /D PATTERNDIR=\"\" /D WINGDINGFONTDIR=\"\" /D "_X86_" /D "WIN32" /D "HAVE_CONFIG_H" /GF /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x41d
# ADD RSC /l 0x41d
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\Debug\obj\libAbi_libwv_s.lib"

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "wv___Win32_Release"
# PROP BASE Intermediate_Dir "wv___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Release\obj"
# PROP Intermediate_Dir ".\Release\obj\wv"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Z7 /Od /Ob1 /Gy /I "..\wv" /I "..\wv\exporter" /I "..\wv\iconv" /I "..\wv\oledecod" /I "..\wv\libole2" /I "..\wv\glib-wv" /I "..\wv\libole2\system-includes" /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /D CONFIGFILE=\".mswordview\" /D TTFDIR=\"\" /D SYBMOLFONTDIR=\"\" /D PATTERNDIR=\"\" /D WINGDINGFONTDIR=\"\" /D "_X86_" /D "DEBUG" /D "_DEBUG" /D "_CTRDBG_MAP_ALLOC" /D "WIN32" /D "UT_DEBUG" /D "PT_TEST" /D "FMT_TEST" /D "UT_TEST" /GF /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MD /W3 /Zi /O1 /Ob2 /I "." /I "..\wv" /I "..\wv\exporter" /I "..\libiconv\include" /I "..\wv\oledecod" /I "..\wv\libole2" /I "..\wv\glib-wv" /I "..\wv\libole2\system-includes" /I "..\wv\expat\xmlparse" /I "..\expat\lib" /D "NDEBUG" /D CONFIGFILE=\".mswordview\" /D TTFDIR=\"\" /D SYBMOLFONTDIR=\"\" /D PATTERNDIR=\"\" /D WINGDINGFONTDIR=\"\" /D "_X86_" /D "WIN32" /D "HAVE_CONFIG_H" /GF /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x41d
# ADD RSC /l 0x41d
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\Debug\obj\libAbi_libwv_s.lib"
# ADD LIB32 /nologo /out:".\Release\obj\libAbi_libwv_s.lib"

!ENDIF 

# Begin Target

# Name "wv - Win32 Debug"
# Name "wv - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Group "exporter Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\wv\exporter\anld.c
DEP_CPP_ANLD_=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\anlv.c
DEP_CPP_ANLV_=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\asumy.c
DEP_CPP_ASUMY=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\asumyi.c
DEP_CPP_ASUMYI=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\atrd.c
DEP_CPP_ATRD_=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\bkd.c
DEP_CPP_BKD_C=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\bkf.c
DEP_CPP_BKF_C=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\bkl.c
DEP_CPP_BKL_C=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\brc.c
DEP_CPP_BRC_C=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\bte.c
DEP_CPP_BTE_C=\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\bx.c
DEP_CPP_BX_C14=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\chp.c
DEP_CPP_CHP_C=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\dcs.c
DEP_CPP_DCS_C=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\dogrid.c
DEP_CPP_DOGRI=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\dop.c
DEP_CPP_DOP_C=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\doptypography.c
DEP_CPP_DOPTY=\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\dttm.c
DEP_CPP_DTTM_=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\fdoa.c
DEP_CPP_FDOA_=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\ffn.c
DEP_CPP_FFN_C=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\fib.c
DEP_CPP_FIB_C=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\filetime.c
DEP_CPP_FILET=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\fld.c
DEP_CPP_FLD_C=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\font.c
DEP_CPP_FONT_=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\frd.c
DEP_CPP_FRD_C=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\fspa.c
DEP_CPP_FSPA_=\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\ftxbxs.c
DEP_CPP_FTXBX=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\generic.c
DEP_CPP_GENER=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\lfo.c
DEP_CPP_LFO_C=\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\lspd.c
DEP_CPP_LSPD_=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\lst.c
DEP_CPP_LST_C=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\lvl.c
DEP_CPP_LVL_C=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\numrm.c
DEP_CPP_NUMRM=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\olst.c
DEP_CPP_OLST_=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\pcd.c
DEP_CPP_PCD_C=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\pgd.c
DEP_CPP_PGD_C=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\phe.c
DEP_CPP_PHE_C=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\prm.c
DEP_CPP_PRM_C=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\rr.c
DEP_CPP_RR_C4a=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\rs.c
DEP_CPP_RS_C4c=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\sed.c
DEP_CPP_SED_C=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\sep.c
DEP_CPP_SEP_C=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\shd.c
DEP_CPP_SHD_C=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\stylesheet.c
DEP_CPP_STYLE=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\summary.c
DEP_CPP_SUMMA=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\support.c
DEP_CPP_SUPPO=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\oledecod\oledecod.h"\
	"..\wv\oledecod\support.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\tbd.c
DEP_CPP_TBD_C=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\tc.c
DEP_CPP_TC_C5c=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\tlp.c
DEP_CPP_TLP_C=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\wkb.c
DEP_CPP_WKB_C=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\wv\exporter\wvexporter.c
DEP_CPP_WVEXP=\
	"..\wv\config.h"\
	"..\wv\exporter\wvexporter-priv.h"\
	"..\wv\exporter\wvexporter.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\exporter\"
# PROP Intermediate_Dir ".\Release\obj\wv\exporter\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# End Group
# Begin Group "glib-wv Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\wv\glib-wv\garray.c"
DEP_CPP_GARRA=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\glib-wv\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\glib-wv\"
# PROP Intermediate_Dir ".\Release\obj\wv\glib-wv\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\wv\glib-wv\glist.c"
DEP_CPP_GLIST=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\glib-wv\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\glib-wv\"
# PROP Intermediate_Dir ".\Release\obj\wv\glib-wv\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\wv\glib-wv\gmem.c"
DEP_CPP_GMEM_=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\glib-wv\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\glib-wv\"
# PROP Intermediate_Dir ".\Release\obj\wv\glib-wv\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\wv\glib-wv\gmessages.c"
DEP_CPP_GMESS=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\glib-wv\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\glib-wv\"
# PROP Intermediate_Dir ".\Release\obj\wv\glib-wv\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\wv\glib-wv\gslist.c"
DEP_CPP_GSLIS=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\glib-wv\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\glib-wv\"
# PROP Intermediate_Dir ".\Release\obj\wv\glib-wv\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\wv\glib-wv\gstrfuncs.c"
DEP_CPP_GSTRF=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\glib-wv\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\glib-wv\"
# PROP Intermediate_Dir ".\Release\obj\wv\glib-wv\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\wv\glib-wv\gtree.c"
DEP_CPP_GTREE=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\glib-wv\"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\glib-wv\"
# PROP Intermediate_Dir ".\Release\obj\wv\glib-wv\"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# End Group
# Begin Group "libole2 Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\wv\libole2\ms-ole-summary.c"
DEP_CPP_MS_OL=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\libole2\"

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\libole2\"
# PROP Intermediate_Dir ".\Release\obj\wv\libole2\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\wv\libole2\ms-ole.c"
DEP_CPP_MS_OLE=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\winmmap.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\libole2\"

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\libole2\"
# PROP Intermediate_Dir ".\Release\obj\wv\libole2\"

!ENDIF 

# End Source File
# End Group
# Begin Group "oledecode Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\wv\oledecod\oledecod.c
DEP_CPP_OLEDE=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\oledecod\oledecod.h"\
	"..\wv\oledecod\support.h"\
	"..\wv\wv.h"\
	

!IF  "$(CFG)" == "wv - Win32 Debug"

# PROP Intermediate_Dir ".\Debug\obj\wv\oledecod\"

!ELSEIF  "$(CFG)" == "wv - Win32 Release"

# PROP BASE Intermediate_Dir ".\Debug\obj\wv\oledecod\"
# PROP Intermediate_Dir ".\Release\obj\wv\oledecod\"

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=..\wv\anld.c
DEP_CPP_ANLD_=\
	"..\wv\config.h"\
	"..\wv\crc32.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\anlv.c
DEP_CPP_ANLV_=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\asumy.c
DEP_CPP_ASUMY=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\asumyi.c
DEP_CPP_ASUMYI=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\atrd.c
DEP_CPP_ATRD_=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\bintree.c
DEP_CPP_BINTR=\
	"..\wv\bintree.h"\
	"..\wv\config.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\bkd.c
DEP_CPP_BKD_C=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\bkf.c
DEP_CPP_BKF_C=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\bkl.c
DEP_CPP_BKL_C=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\blip.c
DEP_CPP_BLIP_=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\brc.c
DEP_CPP_BRC_C=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\bte.c
DEP_CPP_BTE_C=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\bx.c
DEP_CPP_BX_C14=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\chp.c
DEP_CPP_CHP_C=\
	"..\wv\bintree.h"\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\clx.c
DEP_CPP_CLX_C=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\crc32.c
DEP_CPP_CRC32=\
	"..\wv\config.h"\
	"..\wv\crc32.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\dcs.c
DEP_CPP_DCS_C=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\decode_complex.c
DEP_CPP_DECOD=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\decode_simple.c
DEP_CPP_DECODE=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\decompresswmf.c
DEP_CPP_DECOM=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\winmmap.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\decrypt95.c
DEP_CPP_DECRY=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\decrypt97.c
DEP_CPP_DECRYP=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\md5.h"\
	"..\wv\rc4.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\dogrid.c
DEP_CPP_DOGRI=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\dop.c
DEP_CPP_DOP_C=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\doptypography.c
DEP_CPP_DOPTY=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\dttm.c
DEP_CPP_DTTM_=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\error.c
DEP_CPP_ERROR=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\escher.c
DEP_CPP_ESCHE=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\fbse.c
DEP_CPP_FBSE_=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\fdoa.c
DEP_CPP_FDOA_=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\ffn.c
DEP_CPP_FFN_C=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\fib.c
DEP_CPP_FIB_C=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\field.c
DEP_CPP_FIELD=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\filetime.c
DEP_CPP_FILET=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\fkp.c
DEP_CPP_FKP_C=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\fld.c
DEP_CPP_FLD_C=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\font.c
DEP_CPP_FONT_=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\fopt.c
DEP_CPP_FOPT_=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\frd.c
DEP_CPP_FRD_C=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\fspa.c
DEP_CPP_FSPA_=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\ftxbxs.c
DEP_CPP_FTXBX=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\generic.c
DEP_CPP_GENER=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\laolareplace.c
DEP_CPP_LAOLA=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\oledecod\oledecod.h"\
	"..\wv\oledecod\support.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\lfo.c
DEP_CPP_LFO_C=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\list.c
DEP_CPP_LIST_=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\lspd.c
DEP_CPP_LSPD_=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\lst.c
DEP_CPP_LST_C=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\lvl.c
DEP_CPP_LVL_C=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\md5.c
DEP_CPP_MD5_C=\
	"..\wv\config.h"\
	"..\wv\md5.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\mtextra.c
DEP_CPP_MTEXT=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\numrm.c
DEP_CPP_NUMRM=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\olst.c
DEP_CPP_OLST_=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\pap.c
DEP_CPP_PAP_C=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\pcd.c
DEP_CPP_PCD_C=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\pgd.c
DEP_CPP_PGD_C=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\phe.c
DEP_CPP_PHE_C=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\picf.c
DEP_CPP_PICF_=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\prm.c
DEP_CPP_PRM_C=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\rc4.c
DEP_CPP_RC4_C=\
	"..\wv\config.h"\
	"..\wv\rc4.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\reasons.c
DEP_CPP_REASO=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\roman.c
DEP_CPP_ROMAN=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\roman.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\rr.c
DEP_CPP_RR_C4a=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\rs.c
DEP_CPP_RS_C4c=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\sed.c
DEP_CPP_SED_C=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\sep.c
DEP_CPP_SEP_C=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\shd.c
DEP_CPP_SHD_C=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\sprm.c
DEP_CPP_SPRM_=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\strcasecmp.c
DEP_CPP_STRCA=\
	"..\wv\config.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\sttbf.c
DEP_CPP_STTBF=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\stylesheet.c
DEP_CPP_STYLE=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\support.c
DEP_CPP_SUPPO=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\oledecod\oledecod.h"\
	"..\wv\oledecod\support.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	
NODEP_CPP_SUPPO=\
	"..\wv\gdwmfapi.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\symbol.c
DEP_CPP_SYMBO=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\table.c
DEP_CPP_TABLE=\
	"..\wv\bintree.h"\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\tap.c
DEP_CPP_TAP_C=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\tbd.c
DEP_CPP_TBD_C=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\tc.c
DEP_CPP_TC_C5c=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\text.c
DEP_CPP_TEXT_=\
	"..\libiconv\include\iconv.h"\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\tlp.c
DEP_CPP_TLP_C=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\twips.c
DEP_CPP_TWIPS=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\unicode.c
DEP_CPP_UNICO=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\utf.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\utf.c
DEP_CPP_UTF_C=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\hdr.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\plan9.h"\
	"..\wv\utf.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\version.c
DEP_CPP_VERSI=\
	"..\wv\config.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\winmmap.c
DEP_CPP_WINMM=\
	"..\wv\winmmap.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\wkb.c
DEP_CPP_WKB_C=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\wvConfig.c
DEP_CPP_WVCON=\
	"..\expat\lib\expat.h"\
	"..\wv\config.h"\
	"..\wv\expat\xmlparse\xmlparse.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	"..\wv\wvinternal.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\wvHtmlEngine.c
DEP_CPP_WVHTM=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\wvparse.c
DEP_CPP_WVPAR=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-gnomevfs.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\utf.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\wvTextEngine.c
DEP_CPP_WVTEX=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\wv\xst.c
DEP_CPP_XST_C=\
	"..\wv\config.h"\
	"..\wv\glib-wv\glib.h"\
	"..\wv\libole2\ms-ole-summary.h"\
	"..\wv\libole2\ms-ole.h"\
	"..\wv\wv.h"\
	
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\wv\bintree.h
# End Source File
# Begin Source File

SOURCE=..\wv\config.h
# End Source File
# Begin Source File

SOURCE=..\wv\crc32.h
# End Source File
# Begin Source File

SOURCE=..\wv\getopt.h
# End Source File
# Begin Source File

SOURCE=..\wv\hdr.h
# End Source File
# Begin Source File

SOURCE=..\wv\iconv\iconv.h
# End Source File
# Begin Source File

SOURCE=..\wv\iconv\iconv_internal.h
# End Source File
# Begin Source File

SOURCE=..\wv\md5.h
# End Source File
# Begin Source File

SOURCE=..\wv\plan9.h
# End Source File
# Begin Source File

SOURCE=..\wv\rc4.h
# End Source File
# Begin Source File

SOURCE=..\wv\roman.h
# End Source File
# Begin Source File

SOURCE=..\wv\utf.h
# End Source File
# Begin Source File

SOURCE=..\wv\wv.h
# End Source File
# Begin Source File

SOURCE=..\wv\wvinternal.h
# End Source File
# End Group
# End Target
# End Project
