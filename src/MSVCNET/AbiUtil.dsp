# Microsoft Developer Studio Project File - Name="AbiUtil" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ABIUTIL - WIN32 DEBUG
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AbiUtil.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AbiUtil.mak" CFG="ABIUTIL - WIN32 DEBUG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AbiUtil - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "AbiUtil - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AbiUtil - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug\obj\af_util"
# PROP Intermediate_Dir ".\Debug\obj\af_util"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Z7 /Od /Ob1 /Gy /I "..\abi\src\wp\ap\xp" /I "..\abi\src\wp\ap\win" /I "..\abi\src\wp\ap\xp\ToolbarIcons" /I "..\abi\src\wp\impexp\xp" /I "..\abi\src\text\fmt\xp" /I "..\abi\src\text\ptbl\xp" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell" /I "..\expat\xmlparse" /I "..\expat\xmltok" /D "_X86_" /D "DEBUG" /D "_DEBUG" /D "_CTRDBG_MAP_ALLOC" /D "WIN32" /D "UT_DEBUG" /D "PT_TEST" /D "FMT_TEST" /D ABIWORD_APP_LIBDIR=\""AbiWord"\" /D "UT_TEST" /D ABIWORD_APP_NAME=\""AbiWord"\" /GF /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /Od /Ob1 /Gy /I "..\libiconv\include" /I "..\libpng" /I "..\zlib" /I "..\wv\iconv" /I "..\abi\src\wp\ap\xp" /I "..\abi\src\wp\ap\win" /I "..\abi\src\wp\ap\xp\ToolbarIcons" /I "..\abi\src\wp\impexp\xp" /I "..\abi\src\text\fmt\xp" /I "..\abi\src\text\ptbl\xp" /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\expat\xmlparse" /I "..\expat\xmltok" /I "..\expat\lib" /I ".." /FI"PCH_ut.h" /D "DEBUG" /D "_DEBUG" /D "_CTRDBG_MAP_ALLOC" /D "UT_DEBUG" /D "PT_TEST" /D "FMT_TEST" /D "UT_TEST" /D "WIN32" /D ABIWORD_APP_NAME=\""AbiWord"\" /D ABIWORD_APP_LIBDIR=\""AbiWord"\" /D _X86_ /D FRIBIDI_EXPORTS /FR /Yu"PCH_ut.h" /GF /c
# ADD BASE RSC /l 0x41d
# ADD RSC /l 0x41d
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\Debug\obj\libAbiUtil_s.lib"

!ELSEIF  "$(CFG)" == "AbiUtil - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AbiUtil___Win32_Release"
# PROP BASE Intermediate_Dir "AbiUtil___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Release\obj\af_util"
# PROP Intermediate_Dir ".\Release\obj\af_util"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Z7 /Od /Ob1 /Gy /I "..\libiconv\include" /I "..\libpng" /I "..\zlib" /I "..\abi\src\wp\ap\xp" /I "..\abi\src\wp\ap\win" /I "..\abi\src\wp\ap\xp\ToolbarIcons" /I "..\abi\src\wp\impexp\xp" /I "..\abi\src\text\fmt\xp" /I "..\abi\src\text\ptbl\xp" /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\wv\iconv" /D "_X86_" /D "DEBUG" /D "_DEBUG" /D "_CTRDBG_MAP_ALLOC" /D "WIN32" /D "UT_DEBUG" /D "PT_TEST" /D "FMT_TEST" /D ABIWORD_APP_LIBDIR=\""AbiWord"\" /D "UT_TEST" /D ABIWORD_APP_NAME=\""AbiWord"\" /GF /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MD /W3 /GX /Zi /O1 /Ob2 /I "..\libiconv\include" /I "..\libpng" /I "..\zlib" /I "..\wv\iconv" /I "..\abi\src\wp\ap\xp" /I "..\abi\src\wp\ap\win" /I "..\abi\src\wp\ap\xp\ToolbarIcons" /I "..\abi\src\wp\impexp\xp" /I "..\abi\src\text\fmt\xp" /I "..\abi\src\text\ptbl\xp" /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\expat\xmlparse" /I "..\expat\xmltok" /I "..\expat\lib" /I ".." /FI"PCH_ut.h" /D "NDEBUG" /D "WIN32" /D ABIWORD_APP_NAME=\""AbiWord"\" /D ABIWORD_APP_LIBDIR=\""AbiWord"\" /D _X86_ /D FRIBIDI_EXPORTS /Yu"PCH_ut.h" /GF /c
# ADD BASE RSC /l 0x41d
# ADD RSC /l 0x41d
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\Debug\obj\libAbiUtil_s.lib"
# ADD LIB32 /nologo /out:".\Release\obj\libAbiUtil_s.lib"

!ENDIF 

# Begin Target

# Name "AbiUtil - Win32 Debug"
# Name "AbiUtil - Win32 Release"
# Begin Group "XP Source Files"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_AbiObject.cpp
DEP_CPP_UT_AB=\
	"..\abi\src\af\util\xp\ut_AbiObject.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_AdobeEncoding.cpp
DEP_CPP_UT_AD=\
	"..\abi\src\af\util\xp\ut_AdobeEncoding.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_allocator.cpp
DEP_CPP_UT_AL=\
	"..\abi\src\af\util\xp\ut_allocator.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_base64.cpp
DEP_CPP_UT_BA=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_base64.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_base64_TestRoutines.cpp
DEP_CPP_UT_BAS=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_base64.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_bijection.cpp
DEP_CPP_UT_BI=\
	"..\abi\src\af\util\xp\ut_bijection.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_bytebuf.cpp
DEP_CPP_UT_BY=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_contextGlyph.cpp
DEP_CPP_UT_CO=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_contextGlyph.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_Language.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Prefs.h"\
	"..\abi\src\af\xap\xp\xap_Prefs_SchemeIds.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_Encoding.cpp
DEP_CPP_UT_EN=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_Encoding.h"\
	"..\abi\src\af\util\xp\ut_exception.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_iconv.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\libiconv\include\iconv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_growbuf.cpp
DEP_CPP_UT_GR=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_growbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_hash.cpp
DEP_CPP_UT_HA=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_iconv.cpp
DEP_CPP_UT_IC=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bijection.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_exception.h"\
	"..\abi\src\af\util\xp\ut_iconv.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xap_EncodingManager.h"\
	"..\expat\lib\expat.h"\
	"..\libiconv\include\iconv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_idle.cpp
DEP_CPP_UT_ID=\
	"..\abi\src\af\util\xp\ut_idle.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_Language.cpp
DEP_CPP_UT_LA=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_Language.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_locale.cpp
DEP_CPP_UT_LO=\
	"..\abi\src\af\util\xp\ut_bijection.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_exception.h"\
	"..\abi\src\af\util\xp\ut_iconv.h"\
	"..\abi\src\af\util\xp\ut_locale.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xap_EncodingManager.h"\
	"..\expat\lib\expat.h"\
	"..\libiconv\include\iconv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_map.cpp
DEP_CPP_UT_MA=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_map.h"\
	"..\abi\src\af\util\xp\ut_pair.h"\
	"..\abi\src\af\util\xp\ut_rbtree.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_math.cpp
DEP_CPP_UT_MAT=\
	"..\abi\src\af\util\xp\ut_math.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_mbtowc.cpp
DEP_CPP_UT_MB=\
	"..\abi\src\af\util\xp\ut_exception.h"\
	"..\abi\src\af\util\xp\ut_iconv.h"\
	"..\abi\src\af\util\xp\ut_locale.h"\
	"..\abi\src\af\util\xp\ut_mbtowc.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\libiconv\include\iconv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_misc.cpp
DEP_CPP_UT_MI=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_OverstrikingChars.cpp
DEP_CPP_UT_OV=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_OverstrikingChars.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_pair.cpp
DEP_CPP_UT_PA=\
	"..\abi\src\af\util\xp\ut_pair.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_png.cpp
DEP_CPP_UT_PN=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\libpng\png.h"\
	"..\libpng\pngconf.h"\
	"..\zlib\zconf.h"\
	"..\zlib\zlib.h"\
	
NODEP_CPP_UT_PN=\
	"..\libpng\alloc.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_rand.cpp
DEP_CPP_UT_RA=\
	"..\abi\src\af\util\xp\ut_rand.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_rbtree.cpp
DEP_CPP_UT_RB=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_rbtree.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_Script.cpp
DEP_CPP_UT_SC=\
	"..\abi\src\af\util\xp\ut_AbiObject.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_Script.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_set.cpp
DEP_CPP_UT_SE=\
	"..\abi\src\af\util\xp\ut_rbtree.h"\
	"..\abi\src\af\util\xp\ut_set.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_spi.cpp
DEP_CPP_UT_SP=\
	"..\abi\src\af\util\xp\ut_exception.h"\
	"..\abi\src\af\util\xp\ut_spi.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_stack.cpp
DEP_CPP_UT_ST=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_stack.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_string.cpp
DEP_CPP_UT_STR=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bijection.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_case.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_exception.h"\
	"..\abi\src\af\util\xp\ut_growbuf.h"\
	"..\abi\src\af\util\xp\ut_iconv.h"\
	"..\abi\src\af\util\xp\ut_mbtowc.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_wctomb.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xap_EncodingManager.h"\
	"..\expat\lib\expat.h"\
	"..\fribidi\fribidi.h"\
	"..\fribidi\fribidi_char_sets.h"\
	"..\fribidi\fribidi_char_sets_cap_rtl.h"\
	"..\fribidi\fribidi_char_sets_cp1255.h"\
	"..\fribidi\fribidi_char_sets_cp1256.h"\
	"..\fribidi\fribidi_char_sets_isiri_3342.h"\
	"..\fribidi\fribidi_char_sets_iso8859_6.h"\
	"..\fribidi\fribidi_char_sets_iso8859_8.h"\
	"..\fribidi\fribidi_char_sets_utf8.h"\
	"..\fribidi\fribidi_config.h"\
	"..\fribidi\fribidi_mem.h"\
	"..\fribidi\fribidi_types.h"\
	"..\libiconv\include\iconv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_string_class.cpp
DEP_CPP_UT_STRI=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_stringbuf.cpp
DEP_CPP_UT_STRIN=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_svg.cpp
DEP_CPP_UT_SV=\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\xp\ut_abi-pango.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_growbuf.h"\
	"..\abi\src\af\util\xp\ut_math.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_stack.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_svg.h"\
	"..\abi\src\af\util\xp\ut_timer.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	
NODEP_CPP_UT_SV=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_test.cpp
DEP_CPP_UT_TE=\
	"..\abi\src\af\util\xp\ut_base64.h"\
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_timer.cpp
DEP_CPP_UT_TI=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_timer.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_types.cpp
DEP_CPP_UT_TY=\
	"..\abi\src\af\util\xp\ut_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_units.cpp
DEP_CPP_UT_UN=\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\xp\ut_abi-pango.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_growbuf.h"\
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
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	
NODEP_CPP_UT_UN=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_vector.cpp
DEP_CPP_UT_VE=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_wctomb.cpp
DEP_CPP_UT_WC=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_exception.h"\
	"..\abi\src\af\util\xp\ut_iconv.h"\
	"..\abi\src\af\util\xp\ut_locale.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_wctomb.h"\
	"..\libiconv\include\iconv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_worker.cpp
DEP_CPP_UT_WO=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_idle.h"\
	"..\abi\src\af\util\xp\ut_timer.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_xml.cpp
DEP_CPP_UT_XM=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_xml_expat.cpp
DEP_CPP_UT_XML=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bijection.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_exception.h"\
	"..\abi\src\af\util\xp\ut_iconv.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xap_EncodingManager.h"\
	"..\expat\lib\expat.h"\
	"..\libiconv\include\iconv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_xml_libxml2.cpp
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "XP Header Files"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_AbiObject.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_AdobeEncoding.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_allocator.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_assert.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_base64.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_bijection.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_bytebuf.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_case.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_contextGlyph.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_debugmsg.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_Encoding.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_exception.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_growbuf.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_hash.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_iconv.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_idle.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_Language.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_locale.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_map.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_math.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_mbtowc.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_misc.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_OverstrikingChars.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_pair.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_path.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_png.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_rand.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_rbtree.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_regex.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_Script.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_set.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_spi.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_stack.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_string.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_string_class.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_stringbuf.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_svg.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_test.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_timer.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_types.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_units.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_vector.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_wctomb.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_worker.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\xp\ut_xml.h
# End Source File
# End Group
# Begin Group "Win32 Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\abi\src\af\util\win\ut_debugmsg.cpp
DEP_CPP_UT_DE=\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\win\ut_path.cpp
DEP_CPP_UT_PAT=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_path.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\win\ut_sleep.cpp
DEP_CPP_UT_SL=\
	"..\abi\src\af\util\win\ut_sleep.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\win\ut_Win32Idle.cpp
DEP_CPP_UT_WI=\
	"..\abi\src\af\util\win\ut_Win32Idle.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_idle.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\win\ut_Win32Locale.cpp
DEP_CPP_UT_WIN=\
	"..\abi\src\af\util\win\ut_Win32Locale.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\win\ut_Win32OS.cpp
DEP_CPP_UT_WIN3=\
	"..\abi\src\af\util\win\ut_Win32OS.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\win\ut_Win32String.cpp
DEP_CPP_UT_WIN32=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\win\ut_Win32Timer.cpp
DEP_CPP_UT_WIN32T=\
	"..\abi\src\af\gr\win\gr_Win32CharWidths.h"\
	"..\abi\src\af\gr\win\gr_Win32Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_CharWidths.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\win\ut_Win32Timer.h"\
	"..\abi\src\af\util\xp\ut_abi-pango.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_growbuf.h"\
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
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	
NODEP_CPP_UT_WIN32T=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\win\ut_xml_msxml.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\win\ut_Xpm2Bmp.cpp
DEP_CPP_UT_XP=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	
# End Source File
# End Group
# Begin Group "Win32 Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\abi\src\af\util\win\ut_sleep.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\win\ut_Win32Idle.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\win\ut_Win32Locale.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\win\ut_Win32OS.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\win\ut_Win32Timer.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\util\win\ut_Xpm2Bmp.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\PCH_ut.cpp
DEP_CPP_PCH_U=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	".\PCH_ut.h"\
	
# ADD CPP /Yc"PCH_ut.h"
# End Source File
# Begin Source File

SOURCE=.\PCH_ut.h
# End Source File
# End Target
# End Project
