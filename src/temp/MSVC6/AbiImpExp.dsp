# Microsoft Developer Studio Project File - Name="AbiImpExp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ABIIMPEXP - WIN32 DEBUG
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AbiImpExp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AbiImpExp.mak" CFG="ABIIMPEXP - WIN32 DEBUG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AbiImpExp - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "AbiImpExp - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AbiImpExp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug\obj\wp_impexp"
# PROP Intermediate_Dir ".\Debug\obj\wp_impexp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Z7 /Od /Ob1 /Gy /I "..\abi\src\wp\ap\xp" /I "..\abi\src\wp\ap\win" /I "..\abi\src\wp\ap\xp\ToolbarIcons" /I "..\abi\src\wp\impexp\xp" /I "..\abi\src\text\fmt\xp" /I "..\abi\src\text\ptbl\xp" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell" /I "..\expat\xmlparse" /I "..\expat\xmltok" /D "_X86_" /D "DEBUG" /D "_DEBUG" /D "_CTRDBG_MAP_ALLOC" /D "WIN32" /D "UT_DEBUG" /D "PT_TEST" /D "FMT_TEST" /D ABIWORD_APP_LIBDIR=\""AbiWord"\" /D "UT_TEST" /D ABIWORD_APP_NAME=\""AbiWord"\" /GF /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /Od /Ob1 /Gy /I "..\libiconv\include" /I "..\wv" /I "..\wv\libole2" /I "..\wv\glib-wv" /I "..\wv\exporter" /I "..\libpng" /I "..\zlib" /I "..\wv\iconv" /I "..\psiconv" /I "..\abi\src\wp\ap\xp" /I "..\abi\src\wp\ap\win" /I "..\abi\src\wp\ap\xp\ToolbarIcons" /I "..\abi\src\wp\impexp\xp" /I "..\abi\src\text\fmt\xp" /I "..\abi\src\text\ptbl\xp" /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\expat\xmlparse" /I "..\expat\xmltok" /I "..\expat\lib" /I ".." /FI"PCH_impexp.h" /D "DEBUG" /D "_DEBUG" /D "_CTRDBG_MAP_ALLOC" /D "UT_DEBUG" /D "PT_TEST" /D "FMT_TEST" /D "UT_TEST" /D "WIN32" /D ABIWORD_APP_NAME=\""AbiWord"\" /D ABIWORD_APP_LIBDIR=\""AbiWord"\" /D "_X86_" /D "FRIBIDI_EXPORTS" /FR /Yu"PCH_impexp.h" /GF /c
# ADD BASE RSC /l 0x41d
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\Debug\obj\libAbiImpExp_s.lib"

!ELSEIF  "$(CFG)" == "AbiImpExp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AbiImpExp___Win32_Release"
# PROP BASE Intermediate_Dir "AbiImpExp___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Release\obj\wp_impexp"
# PROP Intermediate_Dir ".\Release\obj\wp_impexp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Z7 /Od /Ob1 /Gy /I "..\wv" /I "..\wv\libole2" /I "..\wv\glib-wv" /I "..\libpng" /I "..\zlib" /I "..\abi\src\wp\ap\xp" /I "..\abi\src\wp\ap\win" /I "..\abi\src\wp\ap\xp\ToolbarIcons" /I "..\abi\src\wp\impexp\xp" /I "..\abi\src\text\fmt\xp" /I "..\abi\src\text\ptbl\xp" /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\wv\iconv" /D "_X86_" /D "DEBUG" /D "_DEBUG" /D "_CTRDBG_MAP_ALLOC" /D "WIN32" /D "UT_DEBUG" /D "PT_TEST" /D "FMT_TEST" /D ABIWORD_APP_LIBDIR=\""AbiWord"\" /D "UT_TEST" /D ABIWORD_APP_NAME=\""AbiWord"\" /GF /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MD /W3 /GX /Zi /O1 /Ob2 /I "..\wv" /I "..\wv\libole2" /I "..\wv\glib-wv" /I "..\wv\exporter" /I "..\libpng" /I "..\zlib" /I "..\wv\iconv" /I "..\psiconv" /I "..\abi\src\wp\ap\xp" /I "..\abi\src\wp\ap\win" /I "..\abi\src\wp\ap\xp\ToolbarIcons" /I "..\abi\src\wp\impexp\xp" /I "..\abi\src\text\fmt\xp" /I "..\abi\src\text\ptbl\xp" /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\expat\xmlparse" /I "..\expat\xmltok" /I "..\expat\lib" /I ".." /FI"PCH_impexp.h" /D "NDEBUG" /D "WIN32" /D ABIWORD_APP_NAME=\""AbiWord"\" /D ABIWORD_APP_LIBDIR=\""AbiWord"\" /D "_X86_" /D "FRIBIDI_EXPORTS" /Yu"PCH_impexp.h" /GF /c
# ADD BASE RSC /l 0x41d
# ADD RSC /l 0x41d
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\Debug\obj\libAbiImpExp_s.lib"
# ADD LIB32 /nologo /out:".\Release\obj\libAbiImpExp_s.lib"

!ENDIF 

# Begin Target

# Name "AbiImpExp - Win32 Debug"
# Name "AbiImpExp - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_exp.cpp
DEP_CPP_IE_EX=\
	"..\abi\src\af\util\xp\ut_AbiObject.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\impexp\xp\ie_exp.h"\
	"..\abi\src\wp\impexp\xp\ie_exp_AbiWord_1.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	

!IF  "$(CFG)" == "AbiImpExp - Win32 Debug"

# ADD CPP /I "..\MSVC6-0.9.0"

!ELSEIF  "$(CFG)" == "AbiImpExp - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_exp_AbiWord_1.cpp
DEP_CPP_IE_EXP=\
	"..\abi\src\af\util\xp\ut_AbiObject.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_base64.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_rbtree.h"\
	"..\abi\src\af\util\xp\ut_set.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Prefs.h"\
	"..\abi\src\af\xap\xp\xap_Prefs_SchemeIds.h"\
	"..\abi\src\af\xap\xp\xap_Resource.h"\
	"..\abi\src\af\xap\xp\xap_ResourceManager.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_AutoNum.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\fd_Field.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pd_Style.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Object.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\po_Bookmark.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Span.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Strux.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs_SchemeIds.h"\
	"..\abi\src\wp\impexp\xp\ie_exp.h"\
	"..\abi\src\wp\impexp\xp\ie_exp_AbiWord_1.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	

!IF  "$(CFG)" == "AbiImpExp - Win32 Debug"

# ADD CPP /I "..\MSVC6-0.9.0"

!ELSEIF  "$(CFG)" == "AbiImpExp - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_exp_AWT.cpp
DEP_CPP_IE_EXP_=\
	"..\abi\src\af\util\xp\ut_AbiObject.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\impexp\xp\ie_exp.h"\
	"..\abi\src\wp\impexp\xp\ie_exp_AbiWord_1.h"\
	"..\abi\src\wp\impexp\xp\ie_exp_AWT.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	

!IF  "$(CFG)" == "AbiImpExp - Win32 Debug"

# ADD CPP /I "..\MSVC6-0.9.0"

!ELSEIF  "$(CFG)" == "AbiImpExp - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_exp_GZipAbiWord.cpp
DEP_CPP_IE_EXP_G=\
	"..\abi\src\af\util\xp\ut_AbiObject.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\impexp\xp\ie_exp.h"\
	"..\abi\src\wp\impexp\xp\ie_exp_AbiWord_1.h"\
	"..\abi\src\wp\impexp\xp\ie_exp_GZipAbiWord.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	"..\zlib\zconf.h"\
	"..\zlib\zlib.h"\
	

!IF  "$(CFG)" == "AbiImpExp - Win32 Debug"

# ADD CPP /I "..\MSVC6-0.9.0"

!ELSEIF  "$(CFG)" == "AbiImpExp - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_exp_HTML.cpp
DEP_CPP_IE_EXP_H=\
	"..\abi\src\af\util\xp\ut_AbiObject.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_base64.h"\
	"..\abi\src\af\util\xp\ut_bijection.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_exception.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_iconv.h"\
	"..\abi\src\af\util\xp\ut_math.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_path.h"\
	"..\abi\src\af\util\xp\ut_stack.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_wctomb.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dialog_Id.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_HTMLOptions.h"\
	"..\abi\src\af\xap\xp\xap_EncodingManager.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_AutoNum.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\fd_Field.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pd_Style.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Object.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\po_Bookmark.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Span.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Strux.h"\
	"..\abi\src\wp\impexp\xp\ie_exp.h"\
	"..\abi\src\wp\impexp\xp\ie_exp_HTML.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_impexp_HTML.h"\
	"..\abi\src\wp\impexp\xp\ie_Table.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	"..\expat\lib\expat.h"\
	

!IF  "$(CFG)" == "AbiImpExp - Win32 Debug"

# ADD CPP /I "..\MSVC6-0.9.0"

!ELSEIF  "$(CFG)" == "AbiImpExp - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_exp_MsWord_97.cpp
DEP_CPP_IE_EXP_M=\
	"..\abi\src\af\util\xp\ut_AbiObject.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_base64.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_Module.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Span.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Strux.h"\
	"..\abi\src\wp\impexp\xp\ie_exp.h"\
	"..\abi\src\wp\impexp\xp\ie_exp_MsWord_97.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
NODEP_CPP_IE_EXP_M=\
	"..\abi\src\wp\impexp\xp\wvexporter.h"\
	

!IF  "$(CFG)" == "AbiImpExp - Win32 Debug"

# ADD CPP /I "..\MSVC6-0.9.0"

!ELSEIF  "$(CFG)" == "AbiImpExp - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_exp_RTF.cpp
DEP_CPP_IE_EXP_R=\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_Transform.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\xp\ut_abi-pango.h"\
	"..\abi\src\af\util\xp\ut_AbiObject.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_base64.h"\
	"..\abi\src\af\util\xp\ut_bijection.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_exception.h"\
	"..\abi\src\af\util\xp\ut_growbuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_iconv.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_rand.h"\
	"..\abi\src\af\util\xp\ut_stack.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_timer.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_wctomb.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_EncodingManager.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_AutoNum.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pd_Style.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Span.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Strux.h"\
	"..\abi\src\wp\impexp\xp\ie_exp.h"\
	"..\abi\src\wp\impexp\xp\ie_exp_RTF.h"\
	"..\abi\src\wp\impexp\xp\ie_exp_RTF_AttrProp.h"\
	"..\abi\src\wp\impexp\xp\ie_exp_RTF_listenerGetProps.h"\
	"..\abi\src\wp\impexp\xp\ie_exp_RTF_listenerWriteDoc.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_Table.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	"..\expat\lib\expat.h"\
	
NODEP_CPP_IE_EXP_R=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	"..\abi\src\wp\impexp\xp\wv.h"\
	

!IF  "$(CFG)" == "AbiImpExp - Win32 Debug"

# ADD CPP /I "..\MSVC6-0.9.0"

!ELSEIF  "$(CFG)" == "AbiImpExp - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_exp_RTF_AttrProp.cpp
DEP_CPP_IE_EXP_RT=\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\text\ptbl\xp\pd_Style.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\impexp\xp\ie_exp_RTF_AttrProp.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_exp_RTF_listenerGetProps.cpp
DEP_CPP_IE_EXP_RTF=\
	"..\abi\src\af\util\xp\ut_AbiObject.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_exception.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_AutoNum.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Span.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Strux.h"\
	"..\abi\src\wp\impexp\xp\ie_exp.h"\
	"..\abi\src\wp\impexp\xp\ie_exp_RTF.h"\
	"..\abi\src\wp\impexp\xp\ie_exp_RTF_AttrProp.h"\
	"..\abi\src\wp\impexp\xp\ie_exp_RTF_listenerGetProps.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	

!IF  "$(CFG)" == "AbiImpExp - Win32 Debug"

# ADD CPP /I "..\MSVC6-0.9.0"

!ELSEIF  "$(CFG)" == "AbiImpExp - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_exp_RTF_listenerWriteDoc.cpp
DEP_CPP_IE_EXP_RTF_=\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_Transform.h"\
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
	"..\abi\src\af\util\xp\ut_math.h"\
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
	"..\abi\src\af\util\xp\ut_wctomb.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_EncodingManager.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\text\fmt\xp\fb_ColumnBreaker.h"\
	"..\abi\src\text\fmt\xp\fg_Graphic.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_AutoNum.h"\
	"..\abi\src\text\fmt\xp\fl_BlockLayout.h"\
	"..\abi\src\text\fmt\xp\fl_ContainerLayout.h"\
	"..\abi\src\text\fmt\xp\fl_DocLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fl_SectionLayout.h"\
	"..\abi\src\text\fmt\xp\fl_TableLayout.h"\
	"..\abi\src\text\fmt\xp\fp_Fields.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\fmt\xp\fp_Run.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Span.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Strux.h"\
	"..\abi\src\wp\ap\xp\ap_String_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Strings.h"\
	"..\abi\src\wp\impexp\xp\ie_exp.h"\
	"..\abi\src\wp\impexp\xp\ie_exp_RTF.h"\
	"..\abi\src\wp\impexp\xp\ie_exp_RTF_AttrProp.h"\
	"..\abi\src\wp\impexp\xp\ie_exp_RTF_listenerWriteDoc.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_Table.h"\
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
	
NODEP_CPP_IE_EXP_RTF_=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	

!IF  "$(CFG)" == "AbiImpExp - Win32 Debug"

# ADD CPP /I "..\MSVC6-0.9.0"

!ELSEIF  "$(CFG)" == "AbiImpExp - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_exp_Text.cpp
DEP_CPP_IE_EXP_T=\
	"..\abi\src\af\util\win\ut_Win32OS.h"\
	"..\abi\src\af\util\xp\ut_AbiObject.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_base64.h"\
	"..\abi\src\af\util\xp\ut_bijection.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_exception.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_iconv.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_wctomb.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dialog_Id.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_Encoding.h"\
	"..\abi\src\af\xap\xp\xap_EncodingManager.h"\
	"..\abi\src\af\xap\xp\xap_Prefs.h"\
	"..\abi\src\af\xap\xp\xap_Prefs_SchemeIds.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\fd_Field.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Object.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\po_Bookmark.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Span.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Strux.h"\
	"..\abi\src\wp\ap\xp\ap_Dialog_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs_SchemeIds.h"\
	"..\abi\src\wp\impexp\xp\ie_exp.h"\
	"..\abi\src\wp\impexp\xp\ie_exp_Text.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	"..\expat\lib\expat.h"\
	

!IF  "$(CFG)" == "AbiImpExp - Win32 Debug"

# ADD CPP /I "..\MSVC6-0.9.0"

!ELSEIF  "$(CFG)" == "AbiImpExp - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_FileInfo.cpp
DEP_CPP_IE_FI=\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_imp.cpp
DEP_CPP_IE_IM=\
	"..\abi\src\af\util\xp\ut_AbiObject.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_stack.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_imp.h"\
	"..\abi\src\wp\impexp\xp\ie_imp_AbiWord_1.h"\
	"..\abi\src\wp\impexp\xp\ie_imp_GraphicAsDocument.h"\
	"..\abi\src\wp\impexp\xp\ie_imp_XML.h"\
	"..\abi\src\wp\impexp\xp\ie_impGraphic.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	

!IF  "$(CFG)" == "AbiImpExp - Win32 Debug"

# ADD CPP /I "..\MSVC6-0.9.0"

!ELSEIF  "$(CFG)" == "AbiImpExp - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_imp_AbiWord_1.cpp
DEP_CPP_IE_IMP=\
	"..\abi\src\af\util\xp\ut_AbiObject.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bijection.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_exception.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_iconv.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_stack.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_EncodingManager.h"\
	"..\abi\src\af\xap\xp\xap_Resource.h"\
	"..\abi\src\af\xap\xp\xap_ResourceManager.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pd_Style.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_imp.h"\
	"..\abi\src\wp\impexp\xp\ie_imp_AbiWord_1.h"\
	"..\abi\src\wp\impexp\xp\ie_imp_XML.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	"..\expat\lib\expat.h"\
	

!IF  "$(CFG)" == "AbiImpExp - Win32 Debug"

# ADD CPP /I "..\MSVC6-0.9.0"

!ELSEIF  "$(CFG)" == "AbiImpExp - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_imp_ClarisWorks.cpp
DEP_CPP_IE_IMP_=\
	"..\abi\src\af\util\xp\ut_AbiObject.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_growbuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_Module.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\impexp\xp\ie_imp.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
NODEP_CPP_IE_IMP_=\
	"..\abi\src\wp\impexp\xp\ie_imp_ClarisWorks.h"\
	"..\expat\lib\expat.h"\
	
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_imp_GraphicAsDocument.cpp
DEP_CPP_IE_IMP_G=\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_Transform.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\xp\ut_abi-pango.h"\
	"..\abi\src\af\util\xp\ut_AbiObject.h"\
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
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_timer.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\text\fmt\xp\fg_Graphic.h"\
	"..\abi\src\text\fmt\xp\fg_GraphicRaster.h"\
	"..\abi\src\text\fmt\xp\fg_GraphicVector.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_imp.h"\
	"..\abi\src\wp\impexp\xp\ie_imp_GraphicAsDocument.h"\
	"..\abi\src\wp\impexp\xp\ie_impGraphic.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
NODEP_CPP_IE_IMP_G=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	

!IF  "$(CFG)" == "AbiImpExp - Win32 Debug"

# ADD CPP /I "..\MSVC6-0.9.0"

!ELSEIF  "$(CFG)" == "AbiImpExp - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_imp_GZipAbiWord.cpp
DEP_CPP_IE_IMP_GZ=\
	"..\abi\src\af\util\xp\ut_AbiObject.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_stack.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_imp.h"\
	"..\abi\src\wp\impexp\xp\ie_imp_AbiWord_1.h"\
	"..\abi\src\wp\impexp\xp\ie_imp_GZipAbiWord.h"\
	"..\abi\src\wp\impexp\xp\ie_imp_XML.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	"..\zlib\zconf.h"\
	"..\zlib\zlib.h"\
	

!IF  "$(CFG)" == "AbiImpExp - Win32 Debug"

# ADD CPP /I "..\MSVC6-0.9.0"

!ELSEIF  "$(CFG)" == "AbiImpExp - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_imp_MsWord_97.cpp
DEP_CPP_IE_IMP_M=\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_Transform.h"\
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
	"..\abi\src\af\util\xp\ut_math.h"\
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
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dialog_Id.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_Password.h"\
	"..\abi\src\af\xap\xp\xap_EncodingManager.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_FrameImpl.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\text\fmt\xp\fg_Graphic.h"\
	"..\abi\src\text\fmt\xp\fg_GraphicRaster.h"\
	"..\abi\src\text\fmt\xp\fg_GraphicVector.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux.h"\
	"..\abi\src\text\ptbl\xp\pf_Fragments.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_TableAttrProp.h"\
	"..\abi\src\text\ptbl\xp\pt_PieceTable.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\pt_VarSet.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeHistory.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\wp\ap\xp\ap_Dialog_Id.h"\
	"..\abi\src\wp\ap\xp\ap_String_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Strings.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_imp.h"\
	"..\abi\src\wp\impexp\xp\ie_imp_MsWord_97.h"\
	"..\abi\src\wp\impexp\xp\ie_imp_MsWord_dump.h"\
	"..\abi\src\wp\impexp\xp\ie_impGraphic.h"\
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
	
NODEP_CPP_IE_IMP_M=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	"..\abi\src\wp\impexp\xp\wv.h"\
	

!IF  "$(CFG)" == "AbiImpExp - Win32 Debug"

# ADD CPP /I "..\MSVC6-0.9.0"

!ELSEIF  "$(CFG)" == "AbiImpExp - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_imp_RTF.cpp
DEP_CPP_IE_IMP_R=\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_DrawArgs.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_Transform.h"\
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
	"..\abi\src\af\util\xp\ut_math.h"\
	"..\abi\src\af\util\xp\ut_mbtowc.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_path.h"\
	"..\abi\src\af\util\xp\ut_rand.h"\
	"..\abi\src\af\util\xp\ut_stack.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_timer.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_wctomb.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_EncodingManager.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_Prefs.h"\
	"..\abi\src\af\xap\xp\xap_Prefs_SchemeIds.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\af\xap\xp\xav_View.h"\
	"..\abi\src\text\fmt\xp\fb_ColumnBreaker.h"\
	"..\abi\src\text\fmt\xp\fg_Graphic.h"\
	"..\abi\src\text\fmt\xp\fg_GraphicRaster.h"\
	"..\abi\src\text\fmt\xp\fg_GraphicVector.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_AutoNum.h"\
	"..\abi\src\text\fmt\xp\fl_BlockLayout.h"\
	"..\abi\src\text\fmt\xp\fl_ContainerLayout.h"\
	"..\abi\src\text\fmt\xp\fl_DocLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fl_SectionLayout.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\fmt\xp\fv_View.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pd_Style.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\wp\ap\xp\ap_Dialog_Goto.h"\
	"..\abi\src\wp\ap\xp\ap_LeftRuler.h"\
	"..\abi\src\wp\ap\xp\ap_Ruler.h"\
	"..\abi\src\wp\ap\xp\ap_TopRuler.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_imp.h"\
	"..\abi\src\wp\impexp\xp\ie_imp_RTF.h"\
	"..\abi\src\wp\impexp\xp\ie_impGraphic.h"\
	"..\abi\src\wp\impexp\xp\ie_Table.h"\
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
	
NODEP_CPP_IE_IMP_R=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	"..\abi\src\wp\impexp\xp\wv.h"\
	

!IF  "$(CFG)" == "AbiImpExp - Win32 Debug"

# ADD CPP /I "..\MSVC6-0.9.0"

!ELSEIF  "$(CFG)" == "AbiImpExp - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_imp_Text.cpp
DEP_CPP_IE_IMP_T=\
	"..\abi\src\af\util\xp\ut_AbiObject.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bijection.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_exception.h"\
	"..\abi\src\af\util\xp\ut_growbuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_iconv.h"\
	"..\abi\src\af\util\xp\ut_mbtowc.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dialog_Id.h"\
	"..\abi\src\af\xap\xp\xap_DialogFactory.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_Encoding.h"\
	"..\abi\src\af\xap\xp\xap_EncodingManager.h"\
	"..\abi\src\af\xap\xp\xap_Prefs.h"\
	"..\abi\src\af\xap\xp\xap_Prefs_SchemeIds.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\ap\xp\ap_Dialog_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs_SchemeIds.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_imp.h"\
	"..\abi\src\wp\impexp\xp\ie_imp_Text.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	"..\expat\lib\expat.h"\
	

!IF  "$(CFG)" == "AbiImpExp - Win32 Debug"

# ADD CPP /I "..\MSVC6-0.9.0"

!ELSEIF  "$(CFG)" == "AbiImpExp - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_imp_XML.cpp
DEP_CPP_IE_IMP_X=\
	"..\abi\src\af\util\xp\ut_AbiObject.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_stack.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Prefs.h"\
	"..\abi\src\af\xap\xp\xap_Prefs_SchemeIds.h"\
	"..\abi\src\af\xap\xp\xap_Resource.h"\
	"..\abi\src\af\xap\xp\xap_ResourceManager.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs_SchemeIds.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_imp.h"\
	"..\abi\src\wp\impexp\xp\ie_imp_XML.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	

!IF  "$(CFG)" == "AbiImpExp - Win32 Debug"

# ADD CPP /I "..\MSVC6-0.9.0"

!ELSEIF  "$(CFG)" == "AbiImpExp - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_impexp_Register.cpp
DEP_CPP_IE_IMPE=\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_Transform.h"\
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
	"..\abi\src\af\util\xp\ut_mbtowc.h"\
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
	"..\abi\src\af\util\xp\ut_wctomb.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_HTMLOptions.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\text\fmt\xp\fb_ColumnBreaker.h"\
	"..\abi\src\text\fmt\xp\fg_Graphic.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_AutoNum.h"\
	"..\abi\src\text\fmt\xp\fl_BlockLayout.h"\
	"..\abi\src\text\fmt\xp\fl_ContainerLayout.h"\
	"..\abi\src\text\fmt\xp\fl_DocLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fl_SectionLayout.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\wp\impexp\xp\ie_exp.h"\
	"..\abi\src\wp\impexp\xp\ie_exp_AbiWord_1.h"\
	"..\abi\src\wp\impexp\xp\ie_exp_AWT.h"\
	"..\abi\src\wp\impexp\xp\ie_exp_GZipAbiWord.h"\
	"..\abi\src\wp\impexp\xp\ie_exp_HTML.h"\
	"..\abi\src\wp\impexp\xp\ie_exp_RTF.h"\
	"..\abi\src\wp\impexp\xp\ie_exp_Text.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_imp.h"\
	"..\abi\src\wp\impexp\xp\ie_imp_AbiWord_1.h"\
	"..\abi\src\wp\impexp\xp\ie_imp_GraphicAsDocument.h"\
	"..\abi\src\wp\impexp\xp\ie_imp_GZipAbiWord.h"\
	"..\abi\src\wp\impexp\xp\ie_imp_MsWord_97.h"\
	"..\abi\src\wp\impexp\xp\ie_imp_RTF.h"\
	"..\abi\src\wp\impexp\xp\ie_imp_Text.h"\
	"..\abi\src\wp\impexp\xp\ie_imp_XML.h"\
	"..\abi\src\wp\impexp\xp\ie_impexp_Register.h"\
	"..\abi\src\wp\impexp\xp\ie_impGraphic.h"\
	"..\abi\src\wp\impexp\xp\ie_impGraphic_PNG.h"\
	"..\abi\src\wp\impexp\xp\ie_impGraphic_SVG.h"\
	"..\abi\src\wp\impexp\xp\ie_Table.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
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
	"..\zlib\zconf.h"\
	"..\zlib\zlib.h"\
	
NODEP_CPP_IE_IMPE=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	

!IF  "$(CFG)" == "AbiImpExp - Win32 Debug"

# ADD CPP /I "..\MSVC6-0.9.0"

!ELSEIF  "$(CFG)" == "AbiImpExp - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\win\ie_impexp_RegisterWin32.cpp
DEP_CPP_IE_IMPEX=\
	"..\abi\src\af\util\xp\ut_AbiObject.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\wp\impexp\xp\ie_exp.h"\
	"..\abi\src\wp\impexp\xp\ie_imp.h"\
	"..\abi\src\wp\impexp\xp\ie_impexp_Register.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_impGraphic.cpp
DEP_CPP_IE_IMPG=\
	"..\abi\src\af\util\xp\ut_AbiObject.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\wp\impexp\xp\ie_impGraphic.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	

!IF  "$(CFG)" == "AbiImpExp - Win32 Debug"

# ADD CPP /I "..\MSVC6-0.9.0"

!ELSEIF  "$(CFG)" == "AbiImpExp - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_impGraphic_PNG.cpp
DEP_CPP_IE_IMPGR=\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_Transform.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\xp\ut_abi-pango.h"\
	"..\abi\src\af\util\xp\ut_AbiObject.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_growbuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
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
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\text\fmt\xp\fg_Graphic.h"\
	"..\abi\src\text\fmt\xp\fg_GraphicRaster.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_impGraphic.h"\
	"..\abi\src\wp\impexp\xp\ie_impGraphic_PNG.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
NODEP_CPP_IE_IMPGR=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	

!IF  "$(CFG)" == "AbiImpExp - Win32 Debug"

# ADD CPP /I "..\MSVC6-0.9.0"

!ELSEIF  "$(CFG)" == "AbiImpExp - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_impGraphic_SVG.cpp
DEP_CPP_IE_IMPGRA=\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_Transform.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\xp\ut_abi-pango.h"\
	"..\abi\src\af\util\xp\ut_AbiObject.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_growbuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
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
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\text\fmt\xp\fg_Graphic.h"\
	"..\abi\src\text\fmt\xp\fg_GraphicVector.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_impGraphic.h"\
	"..\abi\src\wp\impexp\xp\ie_impGraphic_SVG.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
NODEP_CPP_IE_IMPGRA=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	

!IF  "$(CFG)" == "AbiImpExp - Win32 Debug"

# ADD CPP /I "..\MSVC6-0.9.0"

!ELSEIF  "$(CFG)" == "AbiImpExp - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_Table.cpp
DEP_CPP_IE_TA=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_exception.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_iconv.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_stack.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_wctomb.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_Table.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_exp.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_exp_AbiWord_1.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_exp_AWT.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_exp_GZipAbiWord.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_exp_HTML.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_exp_MsWord_97.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_exp_RTF.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_exp_RTF_AttrProp.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_exp_RTF_listenerGetProps.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_exp_RTF_listenerWriteDoc.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_exp_Text.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_FileInfo.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_imp.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_imp_AbiWord_1.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_imp_ClarisWorks.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_imp_GraphicAsDocument.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_imp_GZipAbiWord.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_imp_MsWord_97.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_imp_RTF.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_imp_Text.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_imp_XML.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_impexp_Palm.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_impexp_Register.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_impGraphic.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_impGraphic_JPEG.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_impGraphic_PNG.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_impGraphic_SVG.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_impGraphic_WMF.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_Table.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\impexp\xp\ie_types.h
# End Source File
# Begin Source File

SOURCE=abi\src\af\xap\win\..\..\..\wp\impexp\xp\ie_types.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\PCH_impexp.cpp
DEP_CPP_PCH_I=\
	"..\abi\src\af\util\xp\ut_AbiObject.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_base64.h"\
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
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_wctomb.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_EncodingManager.h"\
	"..\abi\src\af\xap\xp\xap_Module.h"\
	"..\abi\src\af\xap\xp\xap_Prefs.h"\
	"..\abi\src\af\xap\xp\xap_Prefs_SchemeIds.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_AutoNum.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pd_Style.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Span.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Strux.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs_SchemeIds.h"\
	"..\abi\src\wp\impexp\xp\ie_exp.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_imp.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	"..\expat\lib\expat.h"\
	".\PCH_impexp.h"\
	
# ADD CPP /Yc"PCH_impexp.h"
# End Source File
# Begin Source File

SOURCE=.\PCH_impexp.h
# End Source File
# End Target
# End Project
