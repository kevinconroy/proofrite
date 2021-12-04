# Microsoft Developer Studio Project File - Name="AbiSpell" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ABISPELL - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AbiSpell.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AbiSpell.mak" CFG="ABISPELL - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AbiSpell - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "AbiSpell - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AbiSpell - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug\obj"
# PROP Intermediate_Dir ".\Debug\obj\spell"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Z7 /Od /Ob1 /Gy /I "..\abi\src\wp\ap\xp" /I "..\abi\src\wp\ap\win" /I "..\abi\src\wp\ap\xp\ToolbarIcons" /I "..\abi\src\wp\impexp\xp" /I "..\abi\src\text\fmt\xp" /I "..\abi\src\text\ptbl\xp" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell" /I "..\expat\xmlparse" /I "..\expat\xmltok" /D "_X86_" /D "DEBUG" /D "_DEBUG" /D "_CTRDBG_MAP_ALLOC" /D "WIN32" /D "UT_DEBUG" /D "PT_TEST" /D "FMT_TEST" /D ABIWORD_APP_LIBDIR=\""AbiWord"\" /D "UT_TEST" /D ABIWORD_APP_NAME=\""AbiWord"\" /GF /c
# ADD CPP /nologo /MDd /W3 /Zi /Od /Ob1 /Gy /I "..\libiconv\include" /I "..\wv\iconv" /I "..\abi\src\wp\ap\xp" /I "..\abi\src\wp\ap\win" /I "..\abi\src\wp\ap\xp\ToolbarIcons" /I "..\abi\src\wp\impexp\xp" /I "..\abi\src\text\fmt\xp" /I "..\abi\src\text\ptbl\xp" /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\expat\xmlparse" /I "..\expat\xmltok" /I "..\expat\lib" /D "DEBUG" /D "_DEBUG" /D "_CTRDBG_MAP_ALLOC" /D "UT_DEBUG" /D "PT_TEST" /D "FMT_TEST" /D "UT_TEST" /D "WIN32" /D ABIWORD_APP_NAME=\""AbiWord"\" /D ABIWORD_APP_LIBDIR=\""AbiWord"\" /D _X86_ /D FRIBIDI_EXPORTS /FR /GF /c
# ADD BASE RSC /l 0x41d
# ADD RSC /l 0x41d
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\Debug\obj\libAbiSpell_s.lib"

!ELSEIF  "$(CFG)" == "AbiSpell - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AbiSpell___Win32_Release"
# PROP BASE Intermediate_Dir "AbiSpell___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Release\obj"
# PROP Intermediate_Dir ".\Release\obj\spell"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Z7 /Od /Ob1 /Gy /I "..\libiconv/include" /I "..\abi\src\wp\ap\xp" /I "..\abi\src\wp\ap\win" /I "..\abi\src\wp\ap\xp\ToolbarIcons" /I "..\abi\src\wp\impexp\xp" /I "..\abi\src\text\fmt\xp" /I "..\abi\src\text\ptbl\xp" /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\wv\iconv" /D "_X86_" /D "DEBUG" /D "_DEBUG" /D "_CTRDBG_MAP_ALLOC" /D "WIN32" /D "UT_DEBUG" /D "PT_TEST" /D "FMT_TEST" /D ABIWORD_APP_LIBDIR=\""AbiWord"\" /D "UT_TEST" /D ABIWORD_APP_NAME=\""AbiWord"\" /GF /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MD /W3 /Zi /O1 /Ob2 /I "..\libiconv\include" /I "..\wv\iconv" /I "..\abi\src\wp\ap\xp" /I "..\abi\src\wp\ap\win" /I "..\abi\src\wp\ap\xp\ToolbarIcons" /I "..\abi\src\wp\impexp\xp" /I "..\abi\src\text\fmt\xp" /I "..\abi\src\text\ptbl\xp" /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\expat\xmlparse" /I "..\expat\xmltok" /I "..\expat\lib" /D "NDEBUG" /D "WIN32" /D ABIWORD_APP_NAME=\""AbiWord"\" /D ABIWORD_APP_LIBDIR=\""AbiWord"\" /D _X86_ /D FRIBIDI_EXPORTS /GF /c
# ADD BASE RSC /l 0x41d
# ADD RSC /l 0x41d
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\Debug\obj\libAbiSpell_s.lib"
# ADD LIB32 /nologo /out:".\Release\obj\libAbiSpell_s.lib"

!ENDIF 

# Begin Target

# Name "AbiSpell - Win32 Debug"
# Name "AbiSpell - Win32 Release"
# Begin Group "AbiSpell Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\abi\src\other\spell\xp\barbarisms.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\other\spell\xp\ispell.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\other\spell\ispell_checker.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\other\spell\xp\ispell_checker.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\other\spell\xp\ispell_def.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\other\spell\xp\pspell_checker.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\other\spell\xp\sp_spell.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\other\spell\xp\spell_manager.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\abi\src\other\spell\xp\barbarisms.cpp
DEP_CPP_BARBA=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\other\spell\xp\barbarisms.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\other\spell\xp\correct.cpp
DEP_CPP_CORRE=\
	"..\abi\src\af\util\xp\ut_exception.h"\
	"..\abi\src\af\util\xp\ut_iconv.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\other\spell\xp\ispell.h"\
	"..\abi\src\other\spell\xp\ispell_def.h"\
	"..\abi\src\other\spell\xp\msgs.h"\
	"..\libiconv\include\iconv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\other\spell\xp\good.cpp
DEP_CPP_GOOD_=\
	"..\abi\src\af\util\xp\ut_exception.h"\
	"..\abi\src\af\util\xp\ut_iconv.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\other\spell\xp\ispell.h"\
	"..\abi\src\other\spell\xp\ispell_def.h"\
	"..\libiconv\include\iconv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\other\spell\xp\hash.cpp
DEP_CPP_HASH_=\
	"..\abi\src\af\util\xp\ut_exception.h"\
	"..\abi\src\af\util\xp\ut_iconv.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\other\spell\xp\ispell.h"\
	"..\abi\src\other\spell\xp\ispell_def.h"\
	"..\libiconv\include\iconv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\other\spell\xp\ispell_checker.cpp
DEP_CPP_ISPEL=\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\xp\ut_abi-pango.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_exception.h"\
	"..\abi\src\af\util\xp\ut_growbuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_iconv.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_stack.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_timer.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_HashDownloader.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\other\spell\xp\barbarisms.h"\
	"..\abi\src\other\spell\xp\ispell.h"\
	"..\abi\src\other\spell\xp\ispell_checker.h"\
	"..\abi\src\other\spell\xp\ispell_def.h"\
	"..\abi\src\other\spell\xp\sp_spell.h"\
	"..\abi\src\other\spell\xp\spell_manager.h"\
	"..\abi\src\wp\ap\xp\ap_HashDownloader.h"\
	"..\libiconv\include\iconv.h"\
	
NODEP_CPP_ISPEL=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\other\spell\xp\lookup.cpp
DEP_CPP_LOOKU=\
	"..\abi\src\af\util\xp\ut_exception.h"\
	"..\abi\src\af\util\xp\ut_iconv.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\other\spell\xp\ispell.h"\
	"..\abi\src\other\spell\xp\ispell_def.h"\
	"..\abi\src\other\spell\xp\msgs.h"\
	"..\libiconv\include\iconv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\other\spell\xp\makedent.cpp
DEP_CPP_MAKED=\
	"..\abi\src\af\util\xp\ut_exception.h"\
	"..\abi\src\af\util\xp\ut_iconv.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\other\spell\xp\ispell.h"\
	"..\abi\src\other\spell\xp\ispell_def.h"\
	"..\abi\src\other\spell\xp\msgs.h"\
	"..\libiconv\include\iconv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\other\spell\xp\spell_manager.cpp
DEP_CPP_SPELL=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_exception.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_iconv.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\other\spell\xp\barbarisms.h"\
	"..\abi\src\other\spell\xp\ispell.h"\
	"..\abi\src\other\spell\xp\ispell_checker.h"\
	"..\abi\src\other\spell\xp\ispell_def.h"\
	"..\abi\src\other\spell\xp\pspell_checker.h"\
	"..\abi\src\other\spell\xp\spell_manager.h"\
	"..\libiconv\include\iconv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\other\spell\xp\tgood.cpp
DEP_CPP_TGOOD=\
	"..\abi\src\af\util\xp\ut_exception.h"\
	"..\abi\src\af\util\xp\ut_iconv.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\other\spell\xp\ispell.h"\
	"..\abi\src\other\spell\xp\ispell_def.h"\
	"..\libiconv\include\iconv.h"\
	
# End Source File
# End Target
# End Project
