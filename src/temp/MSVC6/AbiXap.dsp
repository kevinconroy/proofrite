# Microsoft Developer Studio Project File - Name="AbiXap" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ABIXAP - WIN32 DEBUG
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AbiXap.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AbiXap.mak" CFG="ABIXAP - WIN32 DEBUG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AbiXap - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "AbiXap - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AbiXap - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug\obj\af_xap"
# PROP Intermediate_Dir ".\Debug\obj\af_xap"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Z7 /Od /Ob1 /Gy /I "..\abi\src\wp\ap\xp" /I "..\abi\src\wp\ap\win" /I "..\abi\src\wp\ap\xp\ToolbarIcons" /I "..\abi\src\wp\impexp\xp" /I "..\abi\src\text\fmt\xp" /I "..\abi\src\text\ptbl\xp" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell" /I "..\expat\xmlparse" /I "..\expat\xmltok" /I "..\libiconv\include" /D "_X86_" /D "DEBUG" /D "_DEBUG" /D "_CTRDBG_MAP_ALLOC" /D "WIN32" /D "UT_DEBUG" /D "PT_TEST" /D "FMT_TEST" /D ABIWORD_APP_LIBDIR=\""AbiWord"\" /D "UT_TEST" /D ABIWORD_APP_NAME=\""AbiWord"\" /GF /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /Od /Ob1 /Gy /I "..\libiconv\include" /I "..\wv\iconv" /I "..\abi\src\wp\ap\xp" /I "..\abi\src\wp\ap\win" /I "..\abi\src\wp\ap\xp\ToolbarIcons" /I "..\abi\src\wp\impexp\xp" /I "..\abi\src\text\fmt\xp" /I "..\abi\src\text\ptbl\xp" /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\expat\xmlparse" /I "..\expat\xmltok" /I "..\expat\lib" /I "..\abi\src\other\spell\xp" /I ".." /FI"PCH_xap.h" /D "DEBUG" /D "_DEBUG" /D "_CTRDBG_MAP_ALLOC" /D "UT_DEBUG" /D "PT_TEST" /D "FMT_TEST" /D "UT_TEST" /D ABI_BUILD_VERSION=\""Win32x"\" /D "WIN32" /D ABIWORD_APP_NAME=\""AbiWord"\" /D ABIWORD_APP_LIBDIR=\""AbiWord"\" /D "_X86_" /D "FRIBIDI_EXPORTS" /FR /Yu"PCH_xap.h" /GF /c
# ADD BASE RSC /l 0x41d
# ADD RSC /l 0x41d
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\Debug\obj\libAbiXap_s.lib"

!ELSEIF  "$(CFG)" == "AbiXap - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AbiXap___Win32_Release"
# PROP BASE Intermediate_Dir "AbiXap___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Release\obj\af_xap"
# PROP Intermediate_Dir ".\Release\obj\af_xap"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Z7 /Od /Ob1 /Gy /I "..\abi\src\wp\ap\xp" /I "..\abi\src\wp\ap\win" /I "..\abi\src\wp\ap\xp\ToolbarIcons" /I "..\abi\src\wp\impexp\xp" /I "..\abi\src\text\fmt\xp" /I "..\abi\src\text\ptbl\xp" /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell" /I "..\libiconv\include" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\wv\iconv" /D "_X86_" /D "DEBUG" /D "_DEBUG" /D "_CTRDBG_MAP_ALLOC" /D "WIN32" /D "UT_DEBUG" /D "PT_TEST" /D "FMT_TEST" /D ABIWORD_APP_LIBDIR=\""AbiWord"\" /D "UT_TEST" /D ABIWORD_APP_NAME=\""AbiWord"\" /GF /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O1 /Ob2 /I "..\libiconv\include" /I "..\wv\iconv" /I "..\abi\src\wp\ap\xp" /I "..\abi\src\wp\ap\win" /I "..\abi\src\wp\ap\xp\ToolbarIcons" /I "..\abi\src\wp\impexp\xp" /I "..\abi\src\text\fmt\xp" /I "..\abi\src\text\ptbl\xp" /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\expat\xmlparse" /I "..\expat\xmltok" /I "..\expat\lib" /I "..\abi\src\other\spell\xp" /I ".." /FI"PCH_xap.h" /D "NDEBUG" /D ABI_BUILD_VERSION=\""Win32x"\" /D "WIN32" /D ABIWORD_APP_NAME=\""AbiWord"\" /D ABIWORD_APP_LIBDIR=\""AbiWord"\" /D "_X86_" /D "FRIBIDI_EXPORTS" /Yu"PCH_xap.h" /GF /c
# ADD BASE RSC /l 0x41d
# ADD RSC /l 0x41d
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\Debug\obj\libAbiXap_s.lib"
# ADD LIB32 /nologo /out:".\Release\obj\libAbiXap_s.lib"

!ENDIF 

# Begin Target

# Name "AbiXap - Win32 Debug"
# Name "AbiXap - Win32 Release"
# Begin Group "XP Source Files"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xad_Document.cpp
DEP_CPP_XAD_D=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_Resource.h"\
	"..\abi\src\af\xap\xp\xap_ResourceManager.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_App.cpp
DEP_CPP_XAP_A=\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\ev\xp\ev_EditMethod.h"\
	"..\abi\src\af\ev\xp\ev_Menu_Actions.h"\
	"..\abi\src\af\ev\xp\ev_Menu_Layouts.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar_Actions.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar_Layouts.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\xp\ut_abi-pango.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bijection.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_exception.h"\
	"..\abi\src\af\util\xp\ut_growbuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_iconv.h"\
	"..\abi\src\af\util\xp\ut_map.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_rand.h"\
	"..\abi\src\af\util\xp\ut_rbtree.h"\
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
	"..\abi\src\af\xap\xp\xap_Args.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dictionary.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_EditMethods.h"\
	"..\abi\src\af\xap\xp\xap_EncodingManager.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_LoadBindings.h"\
	"..\abi\src\af\xap\xp\xap_Menu_ActionSet.h"\
	"..\abi\src\af\xap\xp\xap_Menu_Layouts.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_Prefs.h"\
	"..\abi\src\af\xap\xp\xap_Prefs_SchemeIds.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_ActionSet.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_Layouts.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\expat\lib\expat.h"\
	"..\libiconv\include\iconv.h"\
	
NODEP_CPP_XAP_A=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Args.cpp
DEP_CPP_XAP_AR=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\xap\xp\xap_Args.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Clipboard.cpp
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dialog.cpp
DEP_CPP_XAP_D=\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\xp\ut_abi-pango.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_growbuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
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
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	
NODEP_CPP_XAP_D=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_DialogFactory.cpp
DEP_CPP_XAP_DI=\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\xp\ut_abi-pango.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_growbuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
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
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	
NODEP_CPP_XAP_DI=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dictionary.cpp
DEP_CPP_XAP_DIC=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_growbuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\xap\xp\xap_Dictionary.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dlg_About.cpp
DEP_CPP_XAP_DL=\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dialog_Id.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_About.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\af\xap\xp\xav_View.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dlg_ClipArt.cpp
DEP_CPP_XAP_DLG=\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_ClipArt.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dlg_Encoding.cpp
DEP_CPP_XAP_DLG_=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_Encoding.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_Encoding.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dlg_FileOpenSaveAs.cpp
DEP_CPP_XAP_DLG_F=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_FileOpenSaveAs.h"\
	"..\abi\src\af\xap\xp\xap_Prefs.h"\
	"..\abi\src\af\xap\xp\xap_Prefs_SchemeIds.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dlg_FontChooser.cpp
DEP_CPP_XAP_DLG_FO=\
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
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_FontChooser.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_Preview.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	
NODEP_CPP_XAP_DLG_FO=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dlg_HTMLOptions.cpp
DEP_CPP_XAP_DLG_H=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_HTMLOptions.h"\
	"..\abi\src\af\xap\xp\xap_Prefs.h"\
	"..\abi\src\af\xap\xp\xap_Prefs_SchemeIds.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dlg_Image.cpp
DEP_CPP_XAP_DLG_I=\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
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
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_Image.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_Preview.h"\
	"..\abi\src\af\xap\xp\xap_Preview_Zoom.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	
NODEP_CPP_XAP_DLG_I=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dlg_Insert_Symbol.cpp
DEP_CPP_XAP_DLG_IN=\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\xp\ut_abi-pango.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_growbuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
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
	"..\abi\src\af\xap\xp\xap_Dialog_Id.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_Insert_Symbol.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Draw_Symbol.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_Preview.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	
NODEP_CPP_XAP_DLG_IN=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dlg_Language.cpp
DEP_CPP_XAP_DLG_L=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_Language.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_Language.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\other\spell\xp\barbarisms.h"\
	"..\abi\src\other\spell\xp\spell_manager.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dlg_MessageBox.cpp
DEP_CPP_XAP_DLG_M=\
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
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dlg_Password.cpp
DEP_CPP_XAP_DLG_P=\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_Password.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dlg_PluginManager.cpp
DEP_CPP_XAP_DLG_PL=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_PluginManager.h"\
	"..\abi\src\af\xap\xp\xap_ModuleManager.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dlg_Print.cpp
DEP_CPP_XAP_DLG_PR=\
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
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dialog_Id.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_FileOpenSaveAs.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_Print.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	
NODEP_CPP_XAP_DLG_PR=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dlg_PrintPreview.cpp
DEP_CPP_XAP_DLG_PRI=\
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
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dialog_Id.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_PrintPreview.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	
NODEP_CPP_XAP_DLG_PRI=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dlg_WindowMore.cpp
DEP_CPP_XAP_DLG_W=\
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
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dialog_Id.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_WindowMore.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dlg_Zoom.cpp
DEP_CPP_XAP_DLG_Z=\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
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
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dialog_Id.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_Zoom.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_Preview.h"\
	"..\abi\src\af\xap\xp\xap_Preview_Zoom.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\af\xap\xp\xav_View.h"\
	
NODEP_CPP_XAP_DLG_Z=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Draw_Symbol.cpp
DEP_CPP_XAP_DR=\
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
	"..\abi\src\af\xap\xp\xap_Draw_Symbol.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_Preview.h"\
	
NODEP_CPP_XAP_DR=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_EncodingManager.cpp
DEP_CPP_XAP_E=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bijection.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_exception.h"\
	"..\abi\src\af\util\xp\ut_iconv.h"\
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

SOURCE=..\abi\src\af\xap\xp\xap_FakeClipboard.cpp
DEP_CPP_XAP_F=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\xap\xp\xap_FakeClipboard.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Frame.cpp
DEP_CPP_XAP_FR=\
	"..\abi\src\af\ev\xp\ev_EditBinding.h"\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\ev\xp\ev_EditEventMapper.h"\
	"..\abi\src\af\ev\xp\ev_EditMethod.h"\
	"..\abi\src\af\ev\xp\ev_Keyboard.h"\
	"..\abi\src\af\ev\xp\ev_Menu.h"\
	"..\abi\src\af\ev\xp\ev_Menu_Labels.h"\
	"..\abi\src\af\ev\xp\ev_Menu_Layouts.h"\
	"..\abi\src\af\ev\xp\ev_Mouse.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar_Layouts.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\win\ut_sleep.h"\
	"..\abi\src\af\util\xp\ut_abi-pango.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_growbuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
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
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dialog_Id.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_Zoom.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_Menu_LabelSet.h"\
	"..\abi\src\af\xap\xp\xap_Menu_Layouts.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_Prefs.h"\
	"..\abi\src\af\xap\xp\xap_Prefs_SchemeIds.h"\
	"..\abi\src\af\xap\xp\xap_Scrollbar_ViewListener.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_Layouts.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xap_ViewListener.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\af\xap\xp\xav_View.h"\
	
NODEP_CPP_XAP_FR=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_FrameImpl.cpp
DEP_CPP_XAP_FRA=\
	"..\abi\src\af\ev\xp\ev_Keyboard.h"\
	"..\abi\src\af\ev\xp\ev_Mouse.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\xp\ut_abi-pango.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_growbuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
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
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	
NODEP_CPP_XAP_FRA=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_LoadBindings.cpp
DEP_CPP_XAP_L=\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\xap\xp\xap_LoadBindings.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Log.cpp
DEP_CPP_XAP_LO=\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\ev\xp\ev_EditMethod.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\xap\xp\xap_Log.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\af\xap\xp\xav_View.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Module.cpp
DEP_CPP_XAP_M=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_spi.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\xap\xp\xap_Module.h"\
	"..\abi\src\af\xap\xp\xap_ModuleManager.h"\
	"..\abi\src\af\xap\xp\xap_Spider.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_ModuleManager.cpp
DEP_CPP_XAP_MO=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_exception.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\xap\win\xap_Win32Module.h"\
	"..\abi\src\af\xap\xp\xap_Module.h"\
	"..\abi\src\af\xap\xp\xap_ModuleManager.h"\
	"..\abi\src\af\xap\xp\xap_Spider.h"\
	
NODEP_CPP_XAP_MO=\
	"..\abi\src\af\xap\xp\xap_BeOSModule.h"\
	"..\abi\src\af\xap\xp\xap_CocoaModule.h"\
	"..\abi\src\af\xap\xp\xap_MacCFMModule.h"\
	"..\abi\src\af\xap\xp\xap_MacModule.h"\
	"..\abi\src\af\xap\xp\xap_QNXModule.h"\
	"..\abi\src\af\xap\xp\xap_UnixModule.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Prefs.cpp
DEP_CPP_XAP_P=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_growbuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Prefs.h"\
	"..\abi\src\af\xap\xp\xap_Prefs_SchemeIds.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Preview.cpp
DEP_CPP_XAP_PR=\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
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
	"..\abi\src\af\xap\xp\xap_Preview.h"\
	
NODEP_CPP_XAP_PR=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Preview_Zoom.cpp
DEP_CPP_XAP_PRE=\
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
	"..\abi\src\af\xap\xp\xap_Preview.h"\
	"..\abi\src\af\xap\xp\xap_Preview_Zoom.h"\
	
NODEP_CPP_XAP_PRE=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Scrollbar_ViewListener.cpp
DEP_CPP_XAP_S=\
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
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_Scrollbar_ViewListener.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	
NODEP_CPP_XAP_S=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Spider.cpp
DEP_CPP_XAP_SP=\
	"..\abi\src\af\util\xp\ut_spi.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\xap\xp\xap_Module.h"\
	"..\abi\src\af\xap\xp\xap_Spider.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Strings.cpp
DEP_CPP_XAP_ST=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bijection.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_exception.h"\
	"..\abi\src\af\util\xp\ut_growbuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_iconv.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_wctomb.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_EncodingManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
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

SOURCE=..\abi\src\af\xap\xp\xap_Toolbar_ControlFactory.cpp
DEP_CPP_XAP_T=\
	"..\abi\src\af\ev\xp\ev_Toolbar.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_ControlFactory.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_ViewListener.cpp
DEP_CPP_XAP_V=\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
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
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xap_ViewListener.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\af\xap\xp\xav_View.h"\
	
NODEP_CPP_XAP_V=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32PropertySheet.cpp
DEP_CPP_XAP_W=\
	"..\abi\src\af\ev\win\ev_Win32Keyboard.h"\
	"..\abi\src\af\ev\win\ev_Win32Menu.h"\
	"..\abi\src\af\ev\win\ev_Win32Mouse.h"\
	"..\abi\src\af\ev\win\ev_Win32Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\ev\xp\ev_Keyboard.h"\
	"..\abi\src\af\ev\xp\ev_Menu.h"\
	"..\abi\src\af\ev\xp\ev_Mouse.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar_Control.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\win\ut_Xpm2Bmp.h"\
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
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_timer.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\win\xap_Win32_TB_CFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32App.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogHelper.h"\
	"..\abi\src\af\xap\win\xap_Win32DragAndDrop.h"\
	"..\abi\src\af\xap\win\xap_Win32FrameImpl.h"\
	"..\abi\src\af\xap\win\xap_Win32PropertySheet.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_ControlFactory.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\ap\win\ap_Win32Toolbar_StyleCombo.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id_List.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	"..\libiconv\include\iconv.h"\
	
NODEP_CPP_XAP_W=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xav_View.cpp
DEP_CPP_XAV_V=\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\xp\ut_abi-pango.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_growbuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
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
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\af\xap\xp\xav_View.h"\
	
NODEP_CPP_XAV_V=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# End Group
# Begin Group "XP Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xad_Document.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_App.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Args.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Clipboard.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dialog.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dialog_Id.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_DialogFactory.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dictionary.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dlg_About.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dlg_ClipArt.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dlg_Encoding.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dlg_FileOpenSaveAs.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dlg_FontChooser.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dlg_HTMLOptions.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dlg_Image.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dlg_Insert_Symbol.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dlg_Language.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dlg_PluginManager.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dlg_Print.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dlg_PrintPreview.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dlg_WindowMore.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Dlg_Zoom.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Draw_Symbol.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_EditMethods.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_EncodingManager.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_FakeClipboard.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Frame.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_FrameImpl.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_LoadBindings.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Log.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Menu_ActionSet.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Menu_LabelSet.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Menu_Layouts.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Module.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_ModuleManager.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Prefs.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Prefs_SchemeIds.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Preview.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Preview_Zoom.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Scrollbar_ViewListener.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Spider.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_String_Id.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Strings.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Toolbar_ActionSet.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Toolbar_ControlFactory.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Toolbar_Icons.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Toolbar_LabelSet.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Toolbar_Layouts.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_Types.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xap_ViewListener.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32PropertySheet.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xav_Listener.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\xp\xav_View.h
# End Source File
# End Group
# Begin Group "Win32 Source Files"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32App.cpp
DEP_CPP_XAP_WI=\
	"..\abi\src\af\ev\win\ev_Win32Keyboard.h"\
	"..\abi\src\af\ev\win\ev_Win32Menu.h"\
	"..\abi\src\af\ev\win\ev_Win32Mouse.h"\
	"..\abi\src\af\ev\win\ev_Win32Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\ev\xp\ev_Keyboard.h"\
	"..\abi\src\af\ev\xp\ev_Menu.h"\
	"..\abi\src\af\ev\xp\ev_Mouse.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar_Control.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\xp\ut_abi-pango.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bijection.h"\
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
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_timer.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\win\xap_Win32_TB_CFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32App.h"\
	"..\abi\src\af\xap\win\xap_Win32Clipboard.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32DragAndDrop.h"\
	"..\abi\src\af\xap\win\xap_Win32EncodingManager.h"\
	"..\abi\src\af\xap\win\xap_Win32FrameImpl.h"\
	"..\abi\src\af\xap\win\xap_Win32Slurp.h"\
	"..\abi\src\af\xap\win\xap_Win32Toolbar_Icons.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Args.h"\
	"..\abi\src\af\xap\xp\xap_Clipboard.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_EncodingManager.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_ControlFactory.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_Icons.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\ap\win\ap_Win32Toolbar_StyleCombo.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id_List.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	"..\expat\lib\expat.h"\
	"..\libiconv\include\iconv.h"\
	
NODEP_CPP_XAP_WI=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Clipboard.cpp
DEP_CPP_XAP_WIN=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\xap\win\xap_Win32Clipboard.h"\
	"..\abi\src\af\xap\xp\xap_Clipboard.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32DialogHelper.cpp
DEP_CPP_XAP_WIN3=\
	"..\abi\src\af\ev\win\ev_Win32Keyboard.h"\
	"..\abi\src\af\ev\win\ev_Win32Menu.h"\
	"..\abi\src\af\ev\win\ev_Win32Mouse.h"\
	"..\abi\src\af\ev\win\ev_Win32Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\ev\xp\ev_Keyboard.h"\
	"..\abi\src\af\ev\xp\ev_Menu.h"\
	"..\abi\src\af\ev\xp\ev_Mouse.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar_Control.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\win\ut_Xpm2Bmp.h"\
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
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_timer.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\win\xap_Win32_TB_CFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32App.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogHelper.h"\
	"..\abi\src\af\xap\win\xap_Win32DragAndDrop.h"\
	"..\abi\src\af\xap\win\xap_Win32FrameImpl.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_ControlFactory.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\ap\win\ap_Win32Toolbar_StyleCombo.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id_List.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	"..\libiconv\include\iconv.h"\
	
NODEP_CPP_XAP_WIN3=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_About.cpp
DEP_CPP_XAP_WIN32=\
	"..\abi\src\af\ev\win\ev_Win32Keyboard.h"\
	"..\abi\src\af\ev\win\ev_Win32Menu.h"\
	"..\abi\src\af\ev\win\ev_Win32Mouse.h"\
	"..\abi\src\af\ev\win\ev_Win32Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\ev\xp\ev_Keyboard.h"\
	"..\abi\src\af\ev\xp\ev_Menu.h"\
	"..\abi\src\af\ev\xp\ev_Mouse.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar_Control.h"\
	"..\abi\src\af\gr\win\gr_Win32CharWidths.h"\
	"..\abi\src\af\gr\win\gr_Win32Graphics.h"\
	"..\abi\src\af\gr\win\gr_Win32Image.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_CharWidths.h"\
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
	"..\abi\src\af\util\xp\ut_png.h"\
	"..\abi\src\af\util\xp\ut_stack.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_timer.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\win\xap_Win32_TB_CFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32App.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32Dlg_About.h"\
	"..\abi\src\af\xap\win\xap_Win32DragAndDrop.h"\
	"..\abi\src\af\xap\win\xap_Win32FrameImpl.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dialog_Id.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_About.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_ControlFactory.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\af\xap\xp\xav_View.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\ap\win\ap_Win32Toolbar_StyleCombo.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id_List.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	"..\libiconv\include\iconv.h"\
	
NODEP_CPP_XAP_WIN32=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_ClipArt.cpp
DEP_CPP_XAP_WIN32D=\
	"..\abi\src\af\ev\win\ev_Win32Keyboard.h"\
	"..\abi\src\af\ev\win\ev_Win32Menu.h"\
	"..\abi\src\af\ev\win\ev_Win32Mouse.h"\
	"..\abi\src\af\ev\win\ev_Win32Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\ev\xp\ev_Keyboard.h"\
	"..\abi\src\af\ev\xp\ev_Menu.h"\
	"..\abi\src\af\ev\xp\ev_Mouse.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar_Control.h"\
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
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_timer.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\win\xap_Win32_TB_CFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32App.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32Dlg_ClipArt.h"\
	"..\abi\src\af\xap\win\xap_Win32DragAndDrop.h"\
	"..\abi\src\af\xap\win\xap_Win32FrameImpl.h"\
	"..\abi\src\af\xap\win\xap_Win32Res_Cursors.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgEncoding.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgFont.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgImage.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgInsertPicture.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgInsertSymbol.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgLanguage.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgPassword.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgPlugin.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgWindowMore.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgZoom.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Resources.rc2"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dialog_Id.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_ClipArt.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_ControlFactory.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\ap\win\ap_Win32Toolbar_StyleCombo.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id_List.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	"..\libiconv\include\iconv.h"\
	
NODEP_CPP_XAP_WIN32D=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_Encoding.cpp
DEP_CPP_XAP_WIN32DL=\
	"..\abi\src\af\ev\win\ev_Win32Keyboard.h"\
	"..\abi\src\af\ev\win\ev_Win32Menu.h"\
	"..\abi\src\af\ev\win\ev_Win32Mouse.h"\
	"..\abi\src\af\ev\win\ev_Win32Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\ev\xp\ev_Keyboard.h"\
	"..\abi\src\af\ev\xp\ev_Menu.h"\
	"..\abi\src\af\ev\xp\ev_Mouse.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar_Control.h"\
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
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_timer.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\win\xap_Win32_TB_CFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32App.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32Dlg_Encoding.h"\
	"..\abi\src\af\xap\win\xap_Win32DragAndDrop.h"\
	"..\abi\src\af\xap\win\xap_Win32FrameImpl.h"\
	"..\abi\src\af\xap\win\xap_Win32Res_Cursors.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgEncoding.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgFont.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgImage.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgInsertPicture.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgInsertSymbol.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgLanguage.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgPassword.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgPlugin.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgWindowMore.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgZoom.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Resources.rc2"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dialog_Id.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_Encoding.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_ControlFactory.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\ap\win\ap_Win32Toolbar_StyleCombo.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id_List.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	"..\libiconv\include\iconv.h"\
	
NODEP_CPP_XAP_WIN32DL=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_FileOpenSaveAs.cpp
DEP_CPP_XAP_WIN32DLG=\
	"..\abi\src\af\ev\win\ev_Win32Keyboard.h"\
	"..\abi\src\af\ev\win\ev_Win32Menu.h"\
	"..\abi\src\af\ev\win\ev_Win32Mouse.h"\
	"..\abi\src\af\ev\win\ev_Win32Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\ev\xp\ev_Keyboard.h"\
	"..\abi\src\af\ev\xp\ev_Menu.h"\
	"..\abi\src\af\ev\xp\ev_Mouse.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar_Control.h"\
	"..\abi\src\af\gr\win\gr_Win32CharWidths.h"\
	"..\abi\src\af\gr\win\gr_Win32Graphics.h"\
	"..\abi\src\af\gr\win\gr_Win32Image.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_CharWidths.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\xp\ut_abi-pango.h"\
	"..\abi\src\af\util\xp\ut_AbiObject.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_exception.h"\
	"..\abi\src\af\util\xp\ut_growbuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_iconv.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_png.h"\
	"..\abi\src\af\util\xp\ut_stack.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_svg.h"\
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_timer.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\win\xap_Win32_TB_CFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32App.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32Dlg_FileOpenSaveAs.h"\
	"..\abi\src\af\xap\win\xap_Win32DragAndDrop.h"\
	"..\abi\src\af\xap\win\xap_Win32FrameImpl.h"\
	"..\abi\src\af\xap\win\xap_Win32Res_Cursors.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgEncoding.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgFont.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgImage.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgInsertPicture.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgInsertSymbol.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgLanguage.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgPassword.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgPlugin.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgWindowMore.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgZoom.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Resources.rc2"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dialog_Id.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_FileOpenSaveAs.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_ControlFactory.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\ap\win\ap_Win32Toolbar_StyleCombo.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id_List.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_imp.h"\
	"..\abi\src\wp\impexp\xp\ie_impGraphic.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	"..\libiconv\include\iconv.h"\
	
NODEP_CPP_XAP_WIN32DLG=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_FontChooser.cpp
DEP_CPP_XAP_WIN32DLG_=\
	"..\abi\src\af\ev\win\ev_Win32Keyboard.h"\
	"..\abi\src\af\ev\win\ev_Win32Menu.h"\
	"..\abi\src\af\ev\win\ev_Win32Mouse.h"\
	"..\abi\src\af\ev\win\ev_Win32Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\ev\xp\ev_Keyboard.h"\
	"..\abi\src\af\ev\xp\ev_Menu.h"\
	"..\abi\src\af\ev\xp\ev_Mouse.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar_Control.h"\
	"..\abi\src\af\gr\win\gr_Win32CharWidths.h"\
	"..\abi\src\af\gr\win\gr_Win32Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_CharWidths.h"\
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
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_timer.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\win\xap_Win32_TB_CFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32App.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32Dlg_FontChooser.h"\
	"..\abi\src\af\xap\win\xap_Win32Dlg_Insert_Symbol.h"\
	"..\abi\src\af\xap\win\xap_Win32DragAndDrop.h"\
	"..\abi\src\af\xap\win\xap_Win32FrameImpl.h"\
	"..\abi\src\af\xap\win\xap_Win32PreviewWidget.h"\
	"..\abi\src\af\xap\win\xap_Win32Res_Cursors.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgEncoding.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgFont.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgImage.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgInsertPicture.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgInsertSymbol.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgLanguage.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgPassword.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgPlugin.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgWindowMore.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgZoom.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Resources.rc2"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dialog_Id.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_FontChooser.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_Insert_Symbol.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Draw_Symbol.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_Preview.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_ControlFactory.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\ap\win\ap_Win32Toolbar_StyleCombo.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id_List.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	"..\libiconv\include\iconv.h"\
	
NODEP_CPP_XAP_WIN32DLG_=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_HTMLOptions.cpp
DEP_CPP_XAP_WIN32DLG_H=\
	"..\abi\src\af\ev\win\ev_Win32Keyboard.h"\
	"..\abi\src\af\ev\win\ev_Win32Menu.h"\
	"..\abi\src\af\ev\win\ev_Win32Mouse.h"\
	"..\abi\src\af\ev\win\ev_Win32Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\ev\xp\ev_Keyboard.h"\
	"..\abi\src\af\ev\xp\ev_Menu.h"\
	"..\abi\src\af\ev\xp\ev_Mouse.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar_Control.h"\
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
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_timer.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\win\xap_Win32_TB_CFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32App.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32Dlg_HTMLOptions.h"\
	"..\abi\src\af\xap\win\xap_Win32DragAndDrop.h"\
	"..\abi\src\af\xap\win\xap_Win32FrameImpl.h"\
	"..\abi\src\af\xap\win\xap_Win32Res_Cursors.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgEncoding.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgFont.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgImage.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgInsertPicture.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgInsertSymbol.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgLanguage.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgPassword.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgPlugin.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgWindowMore.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgZoom.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Resources.rc2"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dialog_Id.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_HTMLOptions.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_ControlFactory.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\ap\win\ap_Win32Toolbar_StyleCombo.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id_List.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	"..\libiconv\include\iconv.h"\
	
NODEP_CPP_XAP_WIN32DLG_H=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_Image.cpp
DEP_CPP_XAP_WIN32DLG_I=\
	"..\abi\src\af\ev\win\ev_Win32Keyboard.h"\
	"..\abi\src\af\ev\win\ev_Win32Menu.h"\
	"..\abi\src\af\ev\win\ev_Win32Mouse.h"\
	"..\abi\src\af\ev\win\ev_Win32Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\ev\xp\ev_Keyboard.h"\
	"..\abi\src\af\ev\xp\ev_Menu.h"\
	"..\abi\src\af\ev\xp\ev_Mouse.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar_Control.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\win\ut_Xpm2Bmp.h"\
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
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_timer.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\win\xap_Win32_TB_CFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32App.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogHelper.h"\
	"..\abi\src\af\xap\win\xap_Win32Dlg_Image.h"\
	"..\abi\src\af\xap\win\xap_Win32DragAndDrop.h"\
	"..\abi\src\af\xap\win\xap_Win32FrameImpl.h"\
	"..\abi\src\af\xap\win\xap_Win32Res_Cursors.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgEncoding.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgFont.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgImage.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgInsertPicture.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgInsertSymbol.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgLanguage.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgPassword.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgPlugin.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgWindowMore.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgZoom.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Resources.rc2"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dialog_Id.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_Image.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_ControlFactory.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\ap\win\ap_Win32Toolbar_StyleCombo.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id_List.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	"..\libiconv\include\iconv.h"\
	
NODEP_CPP_XAP_WIN32DLG_I=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_Insert_Symbol.cpp
DEP_CPP_XAP_WIN32DLG_IN=\
	"..\abi\src\af\ev\win\ev_Win32Keyboard.h"\
	"..\abi\src\af\ev\win\ev_Win32Menu.h"\
	"..\abi\src\af\ev\win\ev_Win32Mouse.h"\
	"..\abi\src\af\ev\win\ev_Win32Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\ev\xp\ev_Keyboard.h"\
	"..\abi\src\af\ev\xp\ev_Menu.h"\
	"..\abi\src\af\ev\xp\ev_Mouse.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar_Control.h"\
	"..\abi\src\af\gr\win\gr_Win32CharWidths.h"\
	"..\abi\src\af\gr\win\gr_Win32Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_CharWidths.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\win\ut_Xpm2Bmp.h"\
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
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_timer.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\win\xap_Win32_TB_CFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32App.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogHelper.h"\
	"..\abi\src\af\xap\win\xap_Win32Dlg_Insert_Symbol.h"\
	"..\abi\src\af\xap\win\xap_Win32DragAndDrop.h"\
	"..\abi\src\af\xap\win\xap_Win32FrameImpl.h"\
	"..\abi\src\af\xap\win\xap_Win32PreviewWidget.h"\
	"..\abi\src\af\xap\win\xap_Win32Res_Cursors.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgEncoding.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgFont.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgImage.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgInsertPicture.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgInsertSymbol.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgLanguage.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgPassword.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgPlugin.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgWindowMore.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgZoom.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Resources.rc2"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dialog_Id.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_Insert_Symbol.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Draw_Symbol.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_Preview.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_ControlFactory.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\ap\win\ap_Win32Toolbar_StyleCombo.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id_List.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	"..\libiconv\include\iconv.h"\
	
NODEP_CPP_XAP_WIN32DLG_IN=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_Language.cpp
DEP_CPP_XAP_WIN32DLG_L=\
	"..\abi\src\af\ev\win\ev_Win32Keyboard.h"\
	"..\abi\src\af\ev\win\ev_Win32Menu.h"\
	"..\abi\src\af\ev\win\ev_Win32Mouse.h"\
	"..\abi\src\af\ev\win\ev_Win32Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\ev\xp\ev_Keyboard.h"\
	"..\abi\src\af\ev\xp\ev_Menu.h"\
	"..\abi\src\af\ev\xp\ev_Mouse.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar_Control.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\win\ut_Xpm2Bmp.h"\
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
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_timer.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\win\xap_Win32_TB_CFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32App.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogHelper.h"\
	"..\abi\src\af\xap\win\xap_Win32Dlg_Language.h"\
	"..\abi\src\af\xap\win\xap_Win32DragAndDrop.h"\
	"..\abi\src\af\xap\win\xap_Win32FrameImpl.h"\
	"..\abi\src\af\xap\win\xap_Win32Res_Cursors.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgEncoding.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgFont.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgImage.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgInsertPicture.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgInsertSymbol.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgLanguage.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgPassword.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgPlugin.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgWindowMore.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgZoom.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Resources.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Toolbar_Icons.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dialog_Id.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_Language.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_ControlFactory.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_Icons.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\other\spell\xp\barbarisms.h"\
	"..\abi\src\other\spell\xp\spell_manager.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\ap\win\ap_Win32Toolbar_StyleCombo.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id_List.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	"..\libiconv\include\iconv.h"\
	
NODEP_CPP_XAP_WIN32DLG_L=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_MessageBox.cpp
DEP_CPP_XAP_WIN32DLG_M=\
	"..\abi\src\af\ev\win\ev_Win32Keyboard.h"\
	"..\abi\src\af\ev\win\ev_Win32Menu.h"\
	"..\abi\src\af\ev\win\ev_Win32Mouse.h"\
	"..\abi\src\af\ev\win\ev_Win32Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\ev\xp\ev_Keyboard.h"\
	"..\abi\src\af\ev\xp\ev_Menu.h"\
	"..\abi\src\af\ev\xp\ev_Mouse.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar_Control.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\xp\ut_abi-pango.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_exception.h"\
	"..\abi\src\af\util\xp\ut_growbuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_iconv.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_stack.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_timer.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\win\xap_Win32_TB_CFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32App.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32Dlg_MessageBox.h"\
	"..\abi\src\af\xap\win\xap_Win32DragAndDrop.h"\
	"..\abi\src\af\xap\win\xap_Win32FrameImpl.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_ControlFactory.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\ap\win\ap_Win32Toolbar_StyleCombo.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id_List.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	"..\libiconv\include\iconv.h"\
	
NODEP_CPP_XAP_WIN32DLG_M=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_Password.cpp
DEP_CPP_XAP_WIN32DLG_P=\
	"..\abi\src\af\ev\win\ev_Win32Keyboard.h"\
	"..\abi\src\af\ev\win\ev_Win32Menu.h"\
	"..\abi\src\af\ev\win\ev_Win32Mouse.h"\
	"..\abi\src\af\ev\win\ev_Win32Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\ev\xp\ev_Keyboard.h"\
	"..\abi\src\af\ev\xp\ev_Menu.h"\
	"..\abi\src\af\ev\xp\ev_Mouse.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar_Control.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\win\ut_Xpm2Bmp.h"\
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
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_timer.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\win\xap_Win32_TB_CFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32App.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogHelper.h"\
	"..\abi\src\af\xap\win\xap_Win32Dlg_Password.h"\
	"..\abi\src\af\xap\win\xap_Win32DragAndDrop.h"\
	"..\abi\src\af\xap\win\xap_Win32FrameImpl.h"\
	"..\abi\src\af\xap\win\xap_Win32Res_Cursors.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgEncoding.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgFont.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgImage.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgInsertPicture.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgInsertSymbol.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgLanguage.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgPassword.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgPlugin.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgWindowMore.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgZoom.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Resources.rc2"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dialog_Id.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_Password.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_ControlFactory.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\ap\win\ap_Win32Toolbar_StyleCombo.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id_List.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	"..\libiconv\include\iconv.h"\
	
NODEP_CPP_XAP_WIN32DLG_P=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_PluginManager.cpp
DEP_CPP_XAP_WIN32DLG_PL=\
	"..\abi\src\af\ev\win\ev_Win32Keyboard.h"\
	"..\abi\src\af\ev\win\ev_Win32Menu.h"\
	"..\abi\src\af\ev\win\ev_Win32Mouse.h"\
	"..\abi\src\af\ev\win\ev_Win32Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\ev\xp\ev_Keyboard.h"\
	"..\abi\src\af\ev\xp\ev_Menu.h"\
	"..\abi\src\af\ev\xp\ev_Mouse.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar_Control.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\win\ut_Win32OS.h"\
	"..\abi\src\af\util\win\ut_Xpm2Bmp.h"\
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
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_timer.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\win\xap_Win32_TB_CFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32App.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogHelper.h"\
	"..\abi\src\af\xap\win\xap_Win32Dlg_FileOpenSaveAs.h"\
	"..\abi\src\af\xap\win\xap_Win32Dlg_PluginManager.h"\
	"..\abi\src\af\xap\win\xap_Win32DragAndDrop.h"\
	"..\abi\src\af\xap\win\xap_Win32FrameImpl.h"\
	"..\abi\src\af\xap\win\xap_Win32Res_Cursors.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgEncoding.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgFont.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgImage.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgInsertPicture.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgInsertSymbol.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgLanguage.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgPassword.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgPlugin.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgWindowMore.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgZoom.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Resources.rc2"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dialog_Id.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_FileOpenSaveAs.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_PluginManager.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_Module.h"\
	"..\abi\src\af\xap\xp\xap_ModuleManager.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_ControlFactory.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\ap\win\ap_Win32Toolbar_StyleCombo.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id_List.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	"..\libiconv\include\iconv.h"\
	
NODEP_CPP_XAP_WIN32DLG_PL=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_Print.cpp
DEP_CPP_XAP_WIN32DLG_PR=\
	"..\abi\src\af\ev\win\ev_Win32Keyboard.h"\
	"..\abi\src\af\ev\win\ev_Win32Menu.h"\
	"..\abi\src\af\ev\win\ev_Win32Mouse.h"\
	"..\abi\src\af\ev\win\ev_Win32Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\ev\xp\ev_Keyboard.h"\
	"..\abi\src\af\ev\xp\ev_Menu.h"\
	"..\abi\src\af\ev\xp\ev_Mouse.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar_Control.h"\
	"..\abi\src\af\gr\win\gr_Win32CharWidths.h"\
	"..\abi\src\af\gr\win\gr_Win32Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_CharWidths.h"\
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
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_timer.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\win\xap_Win32_TB_CFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32App.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32Dlg_Print.h"\
	"..\abi\src\af\xap\win\xap_Win32DragAndDrop.h"\
	"..\abi\src\af\xap\win\xap_Win32FrameImpl.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dialog_Id.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_Print.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_ControlFactory.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\ap\win\ap_Win32Toolbar_StyleCombo.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id_List.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	"..\libiconv\include\iconv.h"\
	
NODEP_CPP_XAP_WIN32DLG_PR=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_PrintPreview.cpp
DEP_CPP_XAP_WIN32DLG_PRI=\
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
	"..\abi\src\af\xap\win\xap_Win32Dlg_PrintPreview.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dialog_Id.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_PrintPreview.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	
NODEP_CPP_XAP_WIN32DLG_PRI=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_Stub.cpp
DEP_CPP_XAP_WIN32DLG_S=\
	"..\abi\src\af\ev\win\ev_Win32Keyboard.h"\
	"..\abi\src\af\ev\win\ev_Win32Menu.h"\
	"..\abi\src\af\ev\win\ev_Win32Mouse.h"\
	"..\abi\src\af\ev\win\ev_Win32Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\ev\xp\ev_Keyboard.h"\
	"..\abi\src\af\ev\xp\ev_Menu.h"\
	"..\abi\src\af\ev\xp\ev_Mouse.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar_Control.h"\
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
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_timer.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\win\xap_Win32_TB_CFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32App.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32Dlg_Stub.h"\
	"..\abi\src\af\xap\win\xap_Win32DragAndDrop.h"\
	"..\abi\src\af\xap\win\xap_Win32FrameImpl.h"\
	"..\abi\src\af\xap\win\xap_Win32Res_Cursors.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgEncoding.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgFont.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgImage.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgInsertPicture.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgInsertSymbol.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgLanguage.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgPassword.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgPlugin.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgWindowMore.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgZoom.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Resources.rc2"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dialog_Id.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_Stub.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_ControlFactory.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\ap\win\ap_Win32Toolbar_StyleCombo.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id_List.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	"..\libiconv\include\iconv.h"\
	
NODEP_CPP_XAP_WIN32DLG_S=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_WindowMore.cpp
DEP_CPP_XAP_WIN32DLG_W=\
	"..\abi\src\af\ev\win\ev_Win32Keyboard.h"\
	"..\abi\src\af\ev\win\ev_Win32Menu.h"\
	"..\abi\src\af\ev\win\ev_Win32Mouse.h"\
	"..\abi\src\af\ev\win\ev_Win32Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\ev\xp\ev_Keyboard.h"\
	"..\abi\src\af\ev\xp\ev_Menu.h"\
	"..\abi\src\af\ev\xp\ev_Mouse.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar_Control.h"\
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
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_timer.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\win\xap_Win32_TB_CFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32App.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32Dlg_WindowMore.h"\
	"..\abi\src\af\xap\win\xap_Win32DragAndDrop.h"\
	"..\abi\src\af\xap\win\xap_Win32FrameImpl.h"\
	"..\abi\src\af\xap\win\xap_Win32Res_Cursors.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgEncoding.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgFont.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgImage.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgInsertPicture.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgInsertSymbol.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgLanguage.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgPassword.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgPlugin.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgWindowMore.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgZoom.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Resources.rc2"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dialog_Id.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_WindowMore.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_ControlFactory.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\ap\win\ap_Win32Toolbar_StyleCombo.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id_List.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	"..\libiconv\include\iconv.h"\
	
NODEP_CPP_XAP_WIN32DLG_W=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_Zoom.cpp
DEP_CPP_XAP_WIN32DLG_Z=\
	"..\abi\src\af\ev\win\ev_Win32Keyboard.h"\
	"..\abi\src\af\ev\win\ev_Win32Menu.h"\
	"..\abi\src\af\ev\win\ev_Win32Mouse.h"\
	"..\abi\src\af\ev\win\ev_Win32Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\ev\xp\ev_Keyboard.h"\
	"..\abi\src\af\ev\xp\ev_Menu.h"\
	"..\abi\src\af\ev\xp\ev_Mouse.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar_Control.h"\
	"..\abi\src\af\gr\win\gr_Win32CharWidths.h"\
	"..\abi\src\af\gr\win\gr_Win32Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_CharWidths.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\win\ut_Xpm2Bmp.h"\
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
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_timer.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\win\xap_Win32_TB_CFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32App.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogHelper.h"\
	"..\abi\src\af\xap\win\xap_Win32Dlg_Insert_Symbol.h"\
	"..\abi\src\af\xap\win\xap_Win32Dlg_Zoom.h"\
	"..\abi\src\af\xap\win\xap_Win32DragAndDrop.h"\
	"..\abi\src\af\xap\win\xap_Win32FrameImpl.h"\
	"..\abi\src\af\xap\win\xap_Win32PreviewWidget.h"\
	"..\abi\src\af\xap\win\xap_Win32Res_Cursors.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgEncoding.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgFont.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgImage.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgInsertPicture.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgInsertSymbol.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgLanguage.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgPassword.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgPlugin.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgWindowMore.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgZoom.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Resources.rc2"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dialog_Id.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_Insert_Symbol.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_Zoom.h"\
	"..\abi\src\af\xap\xp\xap_Draw_Symbol.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_Preview.h"\
	"..\abi\src\af\xap\xp\xap_Preview_Zoom.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_ControlFactory.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\af\xap\xp\xav_View.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\ap\win\ap_Win32Toolbar_StyleCombo.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id_List.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	"..\libiconv\include\iconv.h"\
	
NODEP_CPP_XAP_WIN32DLG_Z=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32DragAndDrop.cpp
DEP_CPP_XAP_WIN32DR=\
	"..\abi\src\af\ev\win\ev_Win32Keyboard.h"\
	"..\abi\src\af\ev\win\ev_Win32Menu.h"\
	"..\abi\src\af\ev\win\ev_Win32Mouse.h"\
	"..\abi\src\af\ev\win\ev_Win32Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\ev\xp\ev_Keyboard.h"\
	"..\abi\src\af\ev\xp\ev_Menu.h"\
	"..\abi\src\af\ev\xp\ev_Mouse.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar_Control.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_DrawArgs.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\xp\ut_abi-pango.h"\
	"..\abi\src\af\util\xp\ut_AbiObject.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bijection.h"\
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
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_timer.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\win\xap_Win32_TB_CFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32App.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32DragAndDrop.h"\
	"..\abi\src\af\xap\win\xap_Win32FrameImpl.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_EncodingManager.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_Prefs.h"\
	"..\abi\src\af\xap\xp\xap_Prefs_SchemeIds.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_ControlFactory.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\af\xap\xp\xav_View.h"\
	"..\abi\src\text\fmt\xp\fb_ColumnBreaker.h"\
	"..\abi\src\text\fmt\xp\fg_Graphic.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_BlockLayout.h"\
	"..\abi\src\text\fmt\xp\fl_ContainerLayout.h"\
	"..\abi\src\text\fmt\xp\fl_DocLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fl_SectionLayout.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\fmt\xp\fv_View.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\wp\ap\win\ap_Win32Toolbar_StyleCombo.h"\
	"..\abi\src\wp\ap\xp\ap_Dialog_Goto.h"\
	"..\abi\src\wp\ap\xp\ap_FrameData.h"\
	"..\abi\src\wp\ap\xp\ap_LeftRuler.h"\
	"..\abi\src\wp\ap\xp\ap_Ruler.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id_List.h"\
	"..\abi\src\wp\ap\xp\ap_TopRuler.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_imp.h"\
	"..\abi\src\wp\impexp\xp\ie_impexp_Register.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
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
	
NODEP_CPP_XAP_WIN32DR=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32EncodingManager.cpp
DEP_CPP_XAP_WIN32E=\
	"..\abi\src\af\util\win\ut_Win32Locale.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bijection.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_exception.h"\
	"..\abi\src\af\util\xp\ut_iconv.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\win\xap_Win32EncodingManager.h"\
	"..\abi\src\af\xap\xp\xap_EncodingManager.h"\
	"..\expat\lib\expat.h"\
	"..\libiconv\include\iconv.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32FrameImpl.cpp
DEP_CPP_XAP_WIN32F=\
	"..\abi\src\af\ev\win\ev_Win32Keyboard.h"\
	"..\abi\src\af\ev\win\ev_Win32Menu.h"\
	"..\abi\src\af\ev\win\ev_Win32Mouse.h"\
	"..\abi\src\af\ev\win\ev_Win32Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\ev\xp\ev_EditMethod.h"\
	"..\abi\src\af\ev\xp\ev_Keyboard.h"\
	"..\abi\src\af\ev\xp\ev_Menu.h"\
	"..\abi\src\af\ev\xp\ev_Mouse.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar_Control.h"\
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
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_timer.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\win\winezmouse.h"\
	"..\abi\src\af\xap\win\xap_Win32_TB_CFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32App.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32DragAndDrop.h"\
	"..\abi\src\af\xap\win\xap_Win32FrameImpl.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_ControlFactory.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xap_ViewListener.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\af\xap\xp\xav_View.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\ap\win\ap_Win32Toolbar_StyleCombo.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id_List.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	"..\libiconv\include\iconv.h"\
	
NODEP_CPP_XAP_WIN32F=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32LabelledSeparator.cpp
DEP_CPP_XAP_WIN32L=\
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
	"..\abi\src\af\xap\win\xap_Win32_TB_CFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32App.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32LabelledSeparator.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_ControlFactory.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Module.cpp
DEP_CPP_XAP_WIN32M=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\xap\win\xap_Win32Module.h"\
	"..\abi\src\af\xap\xp\xap_Module.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32PreviewWidget.cpp
DEP_CPP_XAP_WIN32P=\
	"..\abi\src\af\gr\win\gr_Win32CharWidths.h"\
	"..\abi\src\af\gr\win\gr_Win32Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_CharWidths.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\xp\ut_abi-pango.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_growbuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
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
	"..\abi\src\af\xap\win\xap_Win32_TB_CFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32App.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32Dlg_Insert_Symbol.h"\
	"..\abi\src\af\xap\win\xap_Win32PreviewWidget.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_Insert_Symbol.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Draw_Symbol.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_Preview.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_ControlFactory.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	
NODEP_CPP_XAP_WIN32P=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Slurp.cpp
DEP_CPP_XAP_WIN32S=\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\xp\ut_abi-pango.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_growbuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
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
	"..\abi\src\af\xap\win\xap_Win32_TB_CFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32App.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32Slurp.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_Prefs.h"\
	"..\abi\src\af\xap\xp\xap_Prefs_SchemeIds.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_ControlFactory.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	
NODEP_CPP_XAP_WIN32S=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Toolbar_Icons.cpp
DEP_CPP_XAP_WIN32T=\
	"..\abi\src\af\util\win\ut_Xpm2Bmp.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\xap\win\xap_Win32Toolbar_Icons.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_Icons.h"\
	
# End Source File
# End Group
# Begin Group "Win32 Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32_TB_CFactory.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32App.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Clipboard.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32DialogFactory.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32DialogHelper.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_About.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_ClipArt.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_Encoding.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_FileOpenSaveAs.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_FontChooser.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_HTMLOptions.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_Image.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_Insert_Symbol.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_Language.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_MessageBox.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_PluginManager.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_Print.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_PrintPreview.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_Stub.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_WindowMore.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Dlg_Zoom.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32DragAndDrop.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32FrameImpl.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32LabelledSeparator.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Module.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32PreviewWidget.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Slurp.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Toolbar_Icons.h
# End Source File
# End Group
# Begin Group "Win32 RC2 Files"

# PROP Default_Filter "rc2"
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Res_Cursors.rc2
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Res_DlgEncoding.rc2
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Res_DlgFont.rc2
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Res_DlgImage.rc2
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Res_DlgInsertPicture.rc2
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Res_DlgInsertSymbol.rc2
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Res_DlgLanguage.rc2
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Res_DlgPassword.rc2
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Res_DlgPlugin.rc2
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Res_DlgWindowMore.rc2
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Res_DlgZoom.rc2
# End Source File
# Begin Source File

SOURCE=..\abi\src\af\xap\win\xap_Win32Resources.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\PCH_xap.cpp
DEP_CPP_PCH_X=\
	"..\abi\src\af\ev\win\ev_Win32Keyboard.h"\
	"..\abi\src\af\ev\win\ev_Win32Menu.h"\
	"..\abi\src\af\ev\win\ev_Win32Mouse.h"\
	"..\abi\src\af\ev\win\ev_Win32Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\ev\xp\ev_Keyboard.h"\
	"..\abi\src\af\ev\xp\ev_Menu.h"\
	"..\abi\src\af\ev\xp\ev_Mouse.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar.h"\
	"..\abi\src\af\ev\xp\ev_Toolbar_Control.h"\
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
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_timer.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\win\xap_Win32_TB_CFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32App.h"\
	"..\abi\src\af\xap\win\xap_Win32DialogFactory.h"\
	"..\abi\src\af\xap\win\xap_Win32DragAndDrop.h"\
	"..\abi\src\af\xap\win\xap_Win32FrameImpl.h"\
	"..\abi\src\af\xap\win\xap_Win32Res_Cursors.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgEncoding.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgFont.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgImage.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgInsertPicture.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgInsertSymbol.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgLanguage.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgPassword.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgPlugin.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgWindowMore.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Res_DlgZoom.rc2"\
	"..\abi\src\af\xap\win\xap_Win32Resources.rc2"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dialog_Id.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Toolbar_ControlFactory.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\ap\win\ap_Win32Toolbar_StyleCombo.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Toolbar_Id_List.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	"..\libiconv\include\iconv.h"\
	".\PCH_xap.h"\
	
NODEP_CPP_PCH_X=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# ADD CPP /Yc"PCH_xap.h"
# End Source File
# Begin Source File

SOURCE=.\PCH_xap.h
# End Source File
# End Target
# End Project
