# Microsoft Developer Studio Project File - Name="AbiPTbl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=AbiPTbl - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AbiPTbl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AbiPTbl.mak" CFG="AbiPTbl - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AbiPTbl - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "AbiPTbl - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AbiPTbl - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug\obj\text_ptbl"
# PROP Intermediate_Dir ".\Debug\obj\text_ptbl"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Z7 /Od /Ob1 /Gy /I "..\abi\src\wp\ap\xp" /I "..\abi\src\wp\ap\win" /I "..\abi\src\wp\ap\xp\ToolbarIcons" /I "..\abi\src\wp\impexp\xp" /I "..\abi\src\text\fmt\xp" /I "..\abi\src\text\ptbl\xp" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell" /I "..\expat\xmlparse" /I "..\expat\xmltok" /D "_X86_" /D "DEBUG" /D "_DEBUG" /D "_CTRDBG_MAP_ALLOC" /D "WIN32" /D "UT_DEBUG" /D "PT_TEST" /D "FMT_TEST" /D ABIWORD_APP_LIBDIR=\""AbiWord"\" /D "UT_TEST" /D ABIWORD_APP_NAME=\""AbiWord"\" /GF /c
# ADD CPP /nologo /MDd /W3 /Zi /Od /Ob1 /Gy /I "..\abi\src\wp\ap\xp" /I "..\abi\src\wp\ap\win" /I "..\abi\src\wp\ap\xp\ToolbarIcons" /I "..\abi\src\wp\impexp\xp" /I "..\abi\src\text\fmt\xp" /I "..\abi\src\text\ptbl\xp" /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\expat\xmlparse" /I "..\expat\xmltok" /I "..\expat\lib" /FI"PCH_ptbl.h" /D "DEBUG" /D "_DEBUG" /D "_CTRDBG_MAP_ALLOC" /D "UT_DEBUG" /D "PT_TEST" /D "FMT_TEST" /D "UT_TEST" /D "WIN32" /D ABIWORD_APP_NAME=\""AbiWord"\" /D ABIWORD_APP_LIBDIR=\""AbiWord"\" /D _X86_ /D FRIBIDI_EXPORTS /FR /Yu"PCH_ptbl.h" /GF /c
# ADD BASE RSC /l 0x41d
# ADD RSC /l 0x41d
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\Debug\obj\libAbiPTbl_s.lib"

!ELSEIF  "$(CFG)" == "AbiPTbl - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AbiPTbl___Win32_Release"
# PROP BASE Intermediate_Dir "AbiPTbl___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Release\obj\text_ptbl"
# PROP Intermediate_Dir ".\Release\obj\text_ptbl"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Z7 /Od /Ob1 /Gy /I "..\abi\src\wp\ap\xp" /I "..\abi\src\wp\ap\win" /I "..\abi\src\wp\ap\xp\ToolbarIcons" /I "..\abi\src\wp\impexp\xp" /I "..\abi\src\text\fmt\xp" /I "..\abi\src\text\ptbl\xp" /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /D "_X86_" /D "DEBUG" /D "_DEBUG" /D "_CTRDBG_MAP_ALLOC" /D "WIN32" /D "UT_DEBUG" /D "PT_TEST" /D "FMT_TEST" /D ABIWORD_APP_LIBDIR=\""AbiWord"\" /D "UT_TEST" /D ABIWORD_APP_NAME=\""AbiWord"\" /GF /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MD /W3 /Zi /O1 /Ob2 /I "..\abi\src\wp\ap\xp" /I "..\abi\src\wp\ap\win" /I "..\abi\src\wp\ap\xp\ToolbarIcons" /I "..\abi\src\wp\impexp\xp" /I "..\abi\src\text\fmt\xp" /I "..\abi\src\text\ptbl\xp" /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\expat\xmlparse" /I "..\expat\xmltok" /I "..\expat\lib" /FI"PCH_ptbl.h" /D "NDEBUG" /D "WIN32" /D ABIWORD_APP_NAME=\""AbiWord"\" /D ABIWORD_APP_LIBDIR=\""AbiWord"\" /D _X86_ /D FRIBIDI_EXPORTS /Yu"PCH_ptbl.h" /GF /c
# ADD BASE RSC /l 0x41d
# ADD RSC /l 0x41d
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\Debug\obj\libAbiPTbl_s.lib"
# ADD LIB32 /nologo /out:".\Release\obj\libAbiPTbl_s.lib"

!ENDIF 

# Begin Target

# Name "AbiPTbl - Win32 Debug"
# Name "AbiPTbl - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\fd_Field.cpp
DEP_CPP_FD_FI=\
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
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\fd_Field.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_FmtMark.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Object.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
	"..\abi\src\text\ptbl\xp\pf_Fragments.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\po_Bookmark.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_TableAttrProp.h"\
	"..\abi\src\text\ptbl\xp\pt_PieceTable.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\pt_VarSet.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeHistory.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pd_Document.cpp
DEP_CPP_PD_DO=\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\win\ut_sleep.h"\
	"..\abi\src\af\util\xp\ut_abi-pango.h"\
	"..\abi\src\af\util\xp\ut_AbiObject.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_base64.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_growbuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_path.h"\
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
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_Prefs.h"\
	"..\abi\src\af\xap\xp\xap_Prefs_SchemeIds.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_AutoNum.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\fd_Field.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pd_Style.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_FmtMark.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Object.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
	"..\abi\src\text\ptbl\xp\pf_Fragments.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\po_Bookmark.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_TableAttrProp.h"\
	"..\abi\src\text\ptbl\xp\pt_PieceTable.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\pt_VarSet.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeHistory.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Span.h"\
	"..\abi\src\text\ptbl\xp\px_CR_SpanChange.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Strux.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs_SchemeIds.h"\
	"..\abi\src\wp\impexp\xp\ie_exp.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_imp.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
NODEP_CPP_PD_DO=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	"..\abi\src\wp\impexp\xp\libgnomevfs\gnome-vfs.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pd_Document_TestRoutines.cpp
DEP_CPP_PD_DOC=\
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
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
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
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pd_Style.cpp
DEP_CPP_PD_ST=\
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
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pd_Style.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
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
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pf_Frag.cpp
DEP_CPP_PF_FR=\
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
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
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
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pf_Frag_FmtMark.cpp
DEP_CPP_PF_FRA=\
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
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_FmtMark.h"\
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
	"..\abi\src\text\ptbl\xp\px_CR_FmtMark.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pf_Frag_Object.cpp
DEP_CPP_PF_FRAG=\
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
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\fd_Field.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Object.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
	"..\abi\src\text\ptbl\xp\pf_Fragments.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\po_Bookmark.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_TableAttrProp.h"\
	"..\abi\src\text\ptbl\xp\pt_PieceTable.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\pt_VarSet.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeHistory.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pf_Frag_Strux.cpp
DEP_CPP_PF_FRAG_=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
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
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Strux.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pf_Frag_Strux_Block.cpp
DEP_CPP_PF_FRAG_S=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
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
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Block.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Strux.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pf_Frag_Strux_Section.cpp
DEP_CPP_PF_FRAG_ST=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
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
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Section.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Strux.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pf_Frag_TestRoutines.cpp
DEP_CPP_PF_FRAG_T=\
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
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\fd_Field.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_FmtMark.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Object.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Block.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Section.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
	"..\abi\src\text\ptbl\xp\pf_Fragments.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\po_Bookmark.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_TableAttrProp.h"\
	"..\abi\src\text\ptbl\xp\pt_PieceTable.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\pt_VarSet.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeHistory.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pf_Frag_Text.cpp
DEP_CPP_PF_FRAG_TE=\
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
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
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
	"..\abi\src\text\ptbl\xp\px_CR_Span.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pf_Fragments.cpp
DEP_CPP_PF_FRAGM=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
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
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux.h"\
	"..\abi\src\text\ptbl\xp\pf_Fragments.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pf_Frags_TestRoutines.cpp
DEP_CPP_PF_FRAGS=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Fragments.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\po_Bookmark.cpp
DEP_CPP_PO_BO=\
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
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\fd_Field.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Object.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
	"..\abi\src\text\ptbl\xp\pf_Fragments.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\po_Bookmark.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_TableAttrProp.h"\
	"..\abi\src\text\ptbl\xp\pt_PieceTable.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\pt_VarSet.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeHistory.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pp_AttrProp.cpp
DEP_CPP_PP_AT=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_pair.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pp_Property.cpp
DEP_CPP_PP_PR=\
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
	"..\abi\src\text\ptbl\xp\pd_Style.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pp_Revision.cpp
DEP_CPP_PP_RE=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_string_class.h"\
	"..\abi\src\af\util\xp\ut_stringbuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pp_TableAttrProp.cpp
DEP_CPP_PP_TA=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_string.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_TableAttrProp.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pt_PieceTable.cpp
DEP_CPP_PT_PI=\
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
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\fd_Field.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pd_Style.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_FmtMark.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Object.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Block.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Section.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
	"..\abi\src\text\ptbl\xp\pf_Fragments.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\po_Bookmark.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_TableAttrProp.h"\
	"..\abi\src\text\ptbl\xp\pt_PieceTable.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\pt_VarSet.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeHistory.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Span.h"\
	"..\abi\src\text\ptbl\xp\px_CR_SpanChange.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Strux.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pt_PT_Append.cpp
DEP_CPP_PT_PT=\
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
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\fd_Field.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_FmtMark.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Object.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Block.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Section.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
	"..\abi\src\text\ptbl\xp\pf_Fragments.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\po_Bookmark.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_TableAttrProp.h"\
	"..\abi\src\text\ptbl\xp\pt_PieceTable.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\pt_VarSet.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeHistory.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Span.h"\
	"..\abi\src\text\ptbl\xp\px_CR_SpanChange.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Strux.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pt_PT_ChangeObject.cpp
DEP_CPP_PT_PT_=\
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
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\fd_Field.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Object.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
	"..\abi\src\text\ptbl\xp\pf_Fragments.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\po_Bookmark.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_TableAttrProp.h"\
	"..\abi\src\text\ptbl\xp\pt_PieceTable.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\pt_VarSet.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeHistory.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\text\ptbl\xp\px_CR_ObjectChange.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pt_PT_ChangeSpan.cpp
DEP_CPP_PT_PT_C=\
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
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\fd_Field.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pd_Style.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_FmtMark.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Object.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Block.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Section.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
	"..\abi\src\text\ptbl\xp\pf_Fragments.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\po_Bookmark.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	"..\abi\src\text\ptbl\xp\pp_TableAttrProp.h"\
	"..\abi\src\text\ptbl\xp\pt_PieceTable.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\pt_VarSet.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeHistory.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Span.h"\
	"..\abi\src\text\ptbl\xp\px_CR_SpanChange.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Strux.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pt_PT_ChangeStrux.cpp
DEP_CPP_PT_PT_CH=\
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
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\fd_Field.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pd_Style.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_FmtMark.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Object.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Block.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Section.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
	"..\abi\src\text\ptbl\xp\pf_Fragments.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\po_Bookmark.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	"..\abi\src\text\ptbl\xp\pp_TableAttrProp.h"\
	"..\abi\src\text\ptbl\xp\pt_PieceTable.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\pt_VarSet.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeHistory.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Strux.h"\
	"..\abi\src\text\ptbl\xp\px_CR_StruxChange.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pt_PT_DeleteObject.cpp
DEP_CPP_PT_PT_D=\
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
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\fd_Field.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Object.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Block.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Section.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
	"..\abi\src\text\ptbl\xp\pf_Fragments.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\po_Bookmark.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_TableAttrProp.h"\
	"..\abi\src\text\ptbl\xp\pt_PieceTable.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\pt_VarSet.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeHistory.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pt_PT_DeleteSpan.cpp
DEP_CPP_PT_PT_DE=\
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
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\fd_Field.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_FmtMark.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Object.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Block.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Section.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
	"..\abi\src\text\ptbl\xp\pf_Fragments.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\po_Bookmark.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	"..\abi\src\text\ptbl\xp\pp_TableAttrProp.h"\
	"..\abi\src\text\ptbl\xp\pt_PieceTable.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\pt_VarSet.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeHistory.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Span.h"\
	"..\abi\src\text\ptbl\xp\px_CR_SpanChange.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Strux.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pt_PT_DeleteStrux.cpp
DEP_CPP_PT_PT_DEL=\
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
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Block.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Section.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
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
	"..\abi\src\text\ptbl\xp\px_CR_Span.h"\
	"..\abi\src\text\ptbl\xp\px_CR_SpanChange.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Strux.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pt_PT_FmtMark.cpp
DEP_CPP_PT_PT_F=\
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
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_FmtMark.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
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
	"..\abi\src\text\ptbl\xp\px_CR_FmtMark.h"\
	"..\abi\src\text\ptbl\xp\px_CR_FmtMarkChange.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pt_PT_Glob.cpp
DEP_CPP_PT_PT_G=\
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
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Block.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Section.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
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
	"..\abi\src\text\ptbl\xp\px_CR_Glob.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Span.h"\
	"..\abi\src\text\ptbl\xp\px_CR_SpanChange.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Strux.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pt_PT_InsertObject.cpp
DEP_CPP_PT_PT_I=\
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
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\fd_Field.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Object.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
	"..\abi\src\text\ptbl\xp\pf_Fragments.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\po_Bookmark.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_TableAttrProp.h"\
	"..\abi\src\text\ptbl\xp\pt_PieceTable.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\pt_VarSet.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeHistory.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\text\ptbl\xp\px_CR_ObjectChange.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pt_PT_InsertSpan.cpp
DEP_CPP_PT_PT_IN=\
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
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\fd_Field.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_FmtMark.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Object.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Block.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Section.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
	"..\abi\src\text\ptbl\xp\pf_Fragments.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\po_Bookmark.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	"..\abi\src\text\ptbl\xp\pp_TableAttrProp.h"\
	"..\abi\src\text\ptbl\xp\pt_PieceTable.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\pt_VarSet.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeHistory.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Span.h"\
	"..\abi\src\text\ptbl\xp\px_CR_SpanChange.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Strux.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pt_PT_InsertStrux.cpp
DEP_CPP_PT_PT_INS=\
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
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\fd_Field.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_FmtMark.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Object.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Block.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Section.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
	"..\abi\src\text\ptbl\xp\pf_Fragments.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\po_Bookmark.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	"..\abi\src\text\ptbl\xp\pp_TableAttrProp.h"\
	"..\abi\src\text\ptbl\xp\pt_PieceTable.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\pt_VarSet.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeHistory.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Strux.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pt_PT_Listener.cpp
DEP_CPP_PT_PT_L=\
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
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\fd_Field.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_FmtMark.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Object.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Block.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Section.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
	"..\abi\src\text\ptbl\xp\pf_Fragments.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\po_Bookmark.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_TableAttrProp.h"\
	"..\abi\src\text\ptbl\xp\pt_PieceTable.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\pt_VarSet.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeHistory.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Span.h"\
	"..\abi\src\text\ptbl\xp\px_CR_SpanChange.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Strux.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pt_PT_Styles.cpp
DEP_CPP_PT_PT_S=\
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
	"..\abi\src\af\util\xp\ut_test.h"\
	"..\abi\src\af\util\xp\ut_timer.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pd_Style.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
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
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
NODEP_CPP_PT_PT_S=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pt_PT_TestRoutines.cpp
DEP_CPP_PT_PT_T=\
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
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Block.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Section.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
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
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pt_PT_Undo.cpp
DEP_CPP_PT_PT_U=\
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
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\fd_Field.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_FmtMark.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Object.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Block.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Section.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
	"..\abi\src\text\ptbl\xp\pf_Fragments.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\po_Bookmark.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_TableAttrProp.h"\
	"..\abi\src\text\ptbl\xp\pt_PieceTable.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\pt_VarSet.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeHistory.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_FmtMark.h"\
	"..\abi\src\text\ptbl\xp\px_CR_FmtMarkChange.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Glob.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\text\ptbl\xp\px_CR_ObjectChange.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Span.h"\
	"..\abi\src\text\ptbl\xp\px_CR_SpanChange.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Strux.h"\
	"..\abi\src\text\ptbl\xp\px_CR_StruxChange.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pt_VarSet.cpp
DEP_CPP_PT_VA=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_growbuf.h"\
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
	"..\abi\src\text\ptbl\xp\pd_Style.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_TableAttrProp.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\pt_VarSet.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\px_CH_TestRoutines.cpp
DEP_CPP_PX_CH=\
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
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Block.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux_Section.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
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
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\px_ChangeHistory.cpp
DEP_CPP_PX_CHA=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
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
	"..\abi\src\text\ptbl\xp\px_ChangeHistory.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Span.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\px_ChangeRecord.cpp
DEP_CPP_PX_CHAN=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
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
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\px_CR_FmtMark.cpp
DEP_CPP_PX_CR=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
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
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_FmtMark.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\px_CR_FmtMarkChange.cpp
DEP_CPP_PX_CR_=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
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
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_FmtMarkChange.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\px_CR_Glob.cpp
DEP_CPP_PX_CR_G=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
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
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Glob.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\px_CR_Object.cpp
DEP_CPP_PX_CR_O=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
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
	"..\abi\src\text\ptbl\xp\fd_Field.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Object.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\po_Bookmark.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\px_CR_ObjectChange.cpp
DEP_CPP_PX_CR_OB=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
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
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_ObjectChange.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\px_CR_Span.cpp
DEP_CPP_PX_CR_S=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
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
	"..\abi\src\text\ptbl\xp\fd_Field.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Object.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\po_Bookmark.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Span.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\px_CR_SpanChange.cpp
DEP_CPP_PX_CR_SP=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
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
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_SpanChange.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\px_CR_Strux.cpp
DEP_CPP_PX_CR_ST=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
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
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Strux.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\px_CR_StruxChange.cpp
DEP_CPP_PX_CR_STR=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
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
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_StruxChange.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\px_CR_TestRoutines.cpp
DEP_CPP_PX_CR_T=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
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
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Glob.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Span.h"\
	"..\abi\src\text\ptbl\xp\px_CR_SpanChange.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\fd_Field.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pd_Document.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pd_Style.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pf_Frag.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pf_Frag_FmtMark.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pf_Frag_Object.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pf_Frag_Strux.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pf_Frag_Strux_Block.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pf_Frag_Strux_Section.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pf_Frag_Text.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pf_Fragments.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pl_Listener.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\po_Bookmark.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pp_AttrProp.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pp_Property.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pp_Revision.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pp_TableAttrProp.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pt_PieceTable.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pt_Types.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\pt_VarSet.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\px_ChangeHistory.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\px_ChangeRecord.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\px_CR_FmtMark.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\px_CR_FmtMarkChange.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\px_CR_Glob.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\px_CR_Object.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\px_CR_ObjectChange.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\px_CR_Span.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\px_CR_SpanChange.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\px_CR_Strux.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\ptbl\xp\px_CR_StruxChange.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\PCH_ptbl.cpp
DEP_CPP_PCH_P=\
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
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\af\util\xp\ut_vector.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\fd_Field.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_FmtMark.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Object.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Strux.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
	"..\abi\src\text\ptbl\xp\pf_Fragments.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\po_Bookmark.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_TableAttrProp.h"\
	"..\abi\src\text\ptbl\xp\pt_PieceTable.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\pt_VarSet.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeHistory.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	".\PCH_ptbl.h"\
	
# ADD CPP /Yc"PCH_ptbl.h"
# End Source File
# Begin Source File

SOURCE=.\PCH_ptbl.h
# End Source File
# End Target
# End Project
