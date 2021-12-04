# Microsoft Developer Studio Project File - Name="AbiFmt" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ABIFMT - WIN32 DEBUG
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AbiFmt.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AbiFmt.mak" CFG="ABIFMT - WIN32 DEBUG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AbiFmt - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "AbiFmt - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AbiFmt - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug\obj\text_fmt"
# PROP Intermediate_Dir ".\Debug\obj\text_fmt"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Z7 /Od /Ob1 /Gy /I "..\abi\src\wp\ap\xp" /I "..\abi\src\wp\ap\win" /I "..\abi\src\wp\ap\xp\ToobarIcons" /I "..\abi\src\wp\impexp\xp" /I "..\abi\src\text\fmt\xp" /I "..\abi\src\text\ptbl\xp" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell" /I "..\expat\xmlparse" /I "..\expat\xmltok" /D "_X86_" /D "DEBUG" /D "_DEBUG" /D "_CTRDBG_MAP_ALLOC" /D "WIN32" /D "UT_DEBUG" /D "PT_TEST" /D "FMT_TEST" /D ABIWORD_APP_LIBDIR=\""AbiWord"\" /D "UT_TEST" /D ABIWORD_APP_NAME=\""AbiWord"\" /GF /c
# ADD CPP /nologo /MDd /W3 /Zi /Od /Ob1 /Gy /I ".." /I "." /I "..\libiconv\include" /I "..\abi\src\wp\ap\xp" /I "..\abi\src\wp\ap\win" /I "..\abi\src\wp\ap\xp\ToolbarIcons" /I "..\abi\src\wp\impexp\xp" /I "..\abi\src\text\fmt\xp" /I "..\abi\src\text\ptbl\xp" /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\expat\xmlparse" /I "..\expat\xmltok" /I "..\expat\lib" /I "..\abi\src\other\spell\xp" /FI"PCH_fmt.h" /D "DEBUG" /D "_DEBUG" /D "_CTRDBG_MAP_ALLOC" /D "UT_DEBUG" /D "PT_TEST" /D "FMT_TEST" /D "UT_TEST" /D "WIN32" /D ABIWORD_APP_NAME=\""AbiWord"\" /D ABIWORD_APP_LIBDIR=\""AbiWord"\" /D _X86_ /D FRIBIDI_EXPORTS /FR /Yu"PCH_fmt.h" /GF /c
# ADD BASE RSC /l 0x41d
# ADD RSC /l 0x41d
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\Debug\obj\libAbiFmt_s.lib"

!ELSEIF  "$(CFG)" == "AbiFmt - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AbiFmt___Win32_Release"
# PROP BASE Intermediate_Dir "AbiFmt___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Release\obj\text_fmt"
# PROP Intermediate_Dir ".\Release\obj\text_fmt"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Z7 /Od /Ob1 /Gy /I "..\abi\src\wp\ap\xp" /I "..\abi\src\wp\ap\win" /I "..\abi\src\wp\ap\xp\ToolbarIcons" /I "..\abi\src\wp\impexp\xp" /I "..\abi\src\text\fmt\xp" /I "..\abi\src\text\ptbl\xp" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell" /I "..\libiconv\include" /D "_X86_" /D "DEBUG" /D "_DEBUG" /D "_CTRDBG_MAP_ALLOC" /D "WIN32" /D "UT_DEBUG" /D "PT_TEST" /D "FMT_TEST" /D ABIWORD_APP_LIBDIR=\""AbiWord"\" /D "UT_TEST" /D ABIWORD_APP_NAME=\""AbiWord"\" /GF /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MD /W3 /Zi /O1 /Ob2 /I "." /I ".." /I "..\libiconv\include" /I "..\abi\src\wp\ap\xp" /I "..\abi\src\wp\ap\win" /I "..\abi\src\wp\ap\xp\ToolbarIcons" /I "..\abi\src\wp\impexp\xp" /I "..\abi\src\text\fmt\xp" /I "..\abi\src\text\ptbl\xp" /I "..\abi\src\af\gr\win" /I "..\abi\src\other\spell" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\expat\xmlparse" /I "..\expat\xmltok" /I "..\expat\lib" /I "..\abi\src\other\spell\xp" /FI"PCH_fmt.h" /D "NDEBUG" /D "WIN32" /D ABIWORD_APP_NAME=\""AbiWord"\" /D ABIWORD_APP_LIBDIR=\""AbiWord"\" /D _X86_ /D FRIBIDI_EXPORTS /Yu"PCH_fmt.h" /GF /c
# ADD BASE RSC /l 0x41d
# ADD RSC /l 0x41d
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\Debug\obj\libAbiFmt_s.lib"
# ADD LIB32 /nologo /out:".\Release\obj\libAbiFmt_s.lib"

!ENDIF 

# Begin Target

# Name "AbiFmt - Win32 Debug"
# Name "AbiFmt - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fb_Alignment.cpp
DEP_CPP_FB_AL=\
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
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\text\fmt\xp\fb_Alignment.h"\
	"..\abi\src\text\fmt\xp\fb_ColumnBreaker.h"\
	"..\abi\src\text\fmt\xp\fg_Graphic.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_BlockLayout.h"\
	"..\abi\src\text\fmt\xp\fl_ContainerLayout.h"\
	"..\abi\src\text\fmt\xp\fl_DocLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fl_SectionLayout.h"\
	"..\abi\src\text\fmt\xp\fp_Column.h"\
	"..\abi\src\text\fmt\xp\fp_ContainerObject.h"\
	"..\abi\src\text\fmt\xp\fp_Fields.h"\
	"..\abi\src\text\fmt\xp\fp_Line.h"\
	"..\abi\src\text\fmt\xp\fp_Page.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\fmt\xp\fp_Run.h"\
	"..\abi\src\text\fmt\xp\fp_TextRun.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\wp\ap\xp\ap_String_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Strings.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
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
	
NODEP_CPP_FB_AL=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	

!IF  "$(CFG)" == "AbiFmt - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "AbiFmt - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fb_LineBreaker.cpp
DEP_CPP_FB_LI=\
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
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\text\fmt\xp\fb_ColumnBreaker.h"\
	"..\abi\src\text\fmt\xp\fb_LineBreaker.h"\
	"..\abi\src\text\fmt\xp\fg_Graphic.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_BlockLayout.h"\
	"..\abi\src\text\fmt\xp\fl_ContainerLayout.h"\
	"..\abi\src\text\fmt\xp\fl_DocLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fl_SectionLayout.h"\
	"..\abi\src\text\fmt\xp\fp_Column.h"\
	"..\abi\src\text\fmt\xp\fp_ContainerObject.h"\
	"..\abi\src\text\fmt\xp\fp_Fields.h"\
	"..\abi\src\text\fmt\xp\fp_Line.h"\
	"..\abi\src\text\fmt\xp\fp_Page.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\fmt\xp\fp_Run.h"\
	"..\abi\src\text\fmt\xp\fp_TextRun.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\wp\ap\xp\ap_String_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Strings.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
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
	
NODEP_CPP_FB_LI=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fg_Graphic.cpp
DEP_CPP_FG_GR=\
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
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
NODEP_CPP_FG_GR=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fg_GraphicRaster.cpp
DEP_CPP_FG_GRA=\
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
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\text\fmt\xp\fg_Graphic.h"\
	"..\abi\src\text\fmt\xp\fg_GraphicRaster.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
NODEP_CPP_FG_GRA=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fg_GraphicVector.cpp
DEP_CPP_FG_GRAP=\
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
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
NODEP_CPP_FG_GRAP=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fl_AutoLists.cpp
DEP_CPP_FL_AU=\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fl_AutoNum.cpp
DEP_CPP_FL_AUT=\
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
	"..\abi\src\text\fmt\xp\fp_Column.h"\
	"..\abi\src\text\fmt\xp\fp_ContainerObject.h"\
	"..\abi\src\text\fmt\xp\fp_Fields.h"\
	"..\abi\src\text\fmt\xp\fp_Line.h"\
	"..\abi\src\text\fmt\xp\fp_Page.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\fmt\xp\fp_Run.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Fragments.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	"..\abi\src\text\ptbl\xp\pp_TableAttrProp.h"\
	"..\abi\src\text\ptbl\xp\pt_PieceTable.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\pt_VarSet.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeHistory.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\wp\ap\xp\ap_String_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Strings.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
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
	
NODEP_CPP_FL_AUT=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fl_BlockLayout.cpp
DEP_CPP_FL_BL=\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_DrawArgs.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\win\ut_sleep.h"\
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
	"..\abi\src\af\util\xp\ut_png.h"\
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
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Clipboard.h"\
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
	"..\abi\src\other\spell\xp\barbarisms.h"\
	"..\abi\src\other\spell\xp\ispell_def.h"\
	"..\abi\src\other\spell\xp\spell_manager.h"\
	"..\abi\src\text\fmt\xp\fb_Alignment.h"\
	"..\abi\src\text\fmt\xp\fb_ColumnBreaker.h"\
	"..\abi\src\text\fmt\xp\fb_LineBreaker.h"\
	"..\abi\src\text\fmt\xp\fg_Graphic.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_AutoNum.h"\
	"..\abi\src\text\fmt\xp\fl_BlockLayout.h"\
	"..\abi\src\text\fmt\xp\fl_ContainerLayout.h"\
	"..\abi\src\text\fmt\xp\fl_DocLayout.h"\
	"..\abi\src\text\fmt\xp\fl_FootnoteLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fl_SectionLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Squiggles.h"\
	"..\abi\src\text\fmt\xp\fl_TableLayout.h"\
	"..\abi\src\text\fmt\xp\fp_Column.h"\
	"..\abi\src\text\fmt\xp\fp_ContainerObject.h"\
	"..\abi\src\text\fmt\xp\fp_FieldListLabelRun.h"\
	"..\abi\src\text\fmt\xp\fp_Fields.h"\
	"..\abi\src\text\fmt\xp\fp_Line.h"\
	"..\abi\src\text\fmt\xp\fp_Page.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\fmt\xp\fp_Run.h"\
	"..\abi\src\text\fmt\xp\fp_TextRun.h"\
	"..\abi\src\text\fmt\xp\fv_View.h"\
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
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_FmtMark.h"\
	"..\abi\src\text\ptbl\xp\px_CR_FmtMarkChange.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\text\ptbl\xp\px_CR_ObjectChange.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Span.h"\
	"..\abi\src\text\ptbl\xp\px_CR_SpanChange.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Strux.h"\
	"..\abi\src\text\ptbl\xp\px_CR_StruxChange.h"\
	"..\abi\src\wp\ap\xp\ap_Dialog_Goto.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs_SchemeIds.h"\
	"..\abi\src\wp\ap\xp\ap_String_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Strings.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
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
	
NODEP_CPP_FL_BL=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fl_ContainerLayout.cpp
DEP_CPP_FL_CO=\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_DrawArgs.h"\
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
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_Prefs.h"\
	"..\abi\src\af\xap\xp\xap_Prefs_SchemeIds.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\af\xap\xp\xav_View.h"\
	"..\abi\src\text\fmt\xp\fb_ColumnBreaker.h"\
	"..\abi\src\text\fmt\xp\fb_LineBreaker.h"\
	"..\abi\src\text\fmt\xp\fg_Graphic.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_BlockLayout.h"\
	"..\abi\src\text\fmt\xp\fl_ContainerLayout.h"\
	"..\abi\src\text\fmt\xp\fl_DocLayout.h"\
	"..\abi\src\text\fmt\xp\fl_FootnoteLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fl_SectionLayout.h"\
	"..\abi\src\text\fmt\xp\fl_TableLayout.h"\
	"..\abi\src\text\fmt\xp\fp_Column.h"\
	"..\abi\src\text\fmt\xp\fp_ContainerObject.h"\
	"..\abi\src\text\fmt\xp\fp_Fields.h"\
	"..\abi\src\text\fmt\xp\fp_Line.h"\
	"..\abi\src\text\fmt\xp\fp_Page.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\fmt\xp\fp_Run.h"\
	"..\abi\src\text\fmt\xp\fp_TableContainer.h"\
	"..\abi\src\text\fmt\xp\fv_View.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\wp\ap\xp\ap_Dialog_Goto.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs_SchemeIds.h"\
	"..\abi\src\wp\ap\xp\ap_String_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Strings.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
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
	
NODEP_CPP_FL_CO=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fl_DocLayout.cpp
DEP_CPP_FL_DO=\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_DrawArgs.h"\
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
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_AutoNum.h"\
	"..\abi\src\text\fmt\xp\fl_BlockLayout.h"\
	"..\abi\src\text\fmt\xp\fl_ContainerLayout.h"\
	"..\abi\src\text\fmt\xp\fl_DocLayout.h"\
	"..\abi\src\text\fmt\xp\fl_DocListener.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fl_SectionLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Squiggles.h"\
	"..\abi\src\text\fmt\xp\fp_Fields.h"\
	"..\abi\src\text\fmt\xp\fp_Page.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\fmt\xp\fp_Run.h"\
	"..\abi\src\text\fmt\xp\fv_View.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\wp\ap\xp\ap_Dialog_Goto.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs_SchemeIds.h"\
	"..\abi\src\wp\ap\xp\ap_String_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Strings.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
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
	
NODEP_CPP_FL_DO=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fl_DocListener.cpp
DEP_CPP_FL_DOC=\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_DrawArgs.h"\
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
	"..\abi\src\af\xap\xp\xav_View.h"\
	"..\abi\src\text\fmt\xp\fb_ColumnBreaker.h"\
	"..\abi\src\text\fmt\xp\fg_Graphic.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_BlockLayout.h"\
	"..\abi\src\text\fmt\xp\fl_ContainerLayout.h"\
	"..\abi\src\text\fmt\xp\fl_DocLayout.h"\
	"..\abi\src\text\fmt\xp\fl_DocListener.h"\
	"..\abi\src\text\fmt\xp\fl_FootnoteLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fl_SectionLayout.h"\
	"..\abi\src\text\fmt\xp\fl_TableLayout.h"\
	"..\abi\src\text\fmt\xp\fp_Column.h"\
	"..\abi\src\text\fmt\xp\fp_ContainerObject.h"\
	"..\abi\src\text\fmt\xp\fp_Fields.h"\
	"..\abi\src\text\fmt\xp\fp_Line.h"\
	"..\abi\src\text\fmt\xp\fp_Page.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\fmt\xp\fp_Run.h"\
	"..\abi\src\text\fmt\xp\fv_View.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
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
	"..\abi\src\wp\ap\xp\ap_Dialog_Goto.h"\
	"..\abi\src\wp\ap\xp\ap_String_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Strings.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
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
	
NODEP_CPP_FL_DOC=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fl_FootnoteLayout.cpp
DEP_CPP_FL_FO=\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_DrawArgs.h"\
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
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_Prefs.h"\
	"..\abi\src\af\xap\xp\xap_Prefs_SchemeIds.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\af\xap\xp\xav_View.h"\
	"..\abi\src\text\fmt\xp\fb_ColumnBreaker.h"\
	"..\abi\src\text\fmt\xp\fb_LineBreaker.h"\
	"..\abi\src\text\fmt\xp\fg_Graphic.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_BlockLayout.h"\
	"..\abi\src\text\fmt\xp\fl_ContainerLayout.h"\
	"..\abi\src\text\fmt\xp\fl_DocLayout.h"\
	"..\abi\src\text\fmt\xp\fl_FootnoteLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fl_SectionLayout.h"\
	"..\abi\src\text\fmt\xp\fp_Column.h"\
	"..\abi\src\text\fmt\xp\fp_ContainerObject.h"\
	"..\abi\src\text\fmt\xp\fp_Fields.h"\
	"..\abi\src\text\fmt\xp\fp_FootnoteContainer.h"\
	"..\abi\src\text\fmt\xp\fp_Line.h"\
	"..\abi\src\text\fmt\xp\fp_Page.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\fmt\xp\fp_Run.h"\
	"..\abi\src\text\fmt\xp\fv_View.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Glob.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\text\ptbl\xp\px_CR_ObjectChange.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Span.h"\
	"..\abi\src\text\ptbl\xp\px_CR_SpanChange.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Strux.h"\
	"..\abi\src\text\ptbl\xp\px_CR_StruxChange.h"\
	"..\abi\src\wp\ap\xp\ap_Dialog_Goto.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs_SchemeIds.h"\
	"..\abi\src\wp\ap\xp\ap_String_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Strings.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
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
	
NODEP_CPP_FL_FO=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fl_Layout.cpp
DEP_CPP_FL_LA=\
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
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\ptbl\xp\fd_Field.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Object.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\po_Bookmark.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fl_SectionLayout.cpp
DEP_CPP_FL_SE=\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_DrawArgs.h"\
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
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_Prefs.h"\
	"..\abi\src\af\xap\xp\xap_Prefs_SchemeIds.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\af\xap\xp\xav_View.h"\
	"..\abi\src\text\fmt\xp\fb_ColumnBreaker.h"\
	"..\abi\src\text\fmt\xp\fb_LineBreaker.h"\
	"..\abi\src\text\fmt\xp\fg_Graphic.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_BlockLayout.h"\
	"..\abi\src\text\fmt\xp\fl_ContainerLayout.h"\
	"..\abi\src\text\fmt\xp\fl_DocLayout.h"\
	"..\abi\src\text\fmt\xp\fl_FootnoteLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fl_SectionLayout.h"\
	"..\abi\src\text\fmt\xp\fl_TableLayout.h"\
	"..\abi\src\text\fmt\xp\fp_Column.h"\
	"..\abi\src\text\fmt\xp\fp_ContainerObject.h"\
	"..\abi\src\text\fmt\xp\fp_Fields.h"\
	"..\abi\src\text\fmt\xp\fp_Line.h"\
	"..\abi\src\text\fmt\xp\fp_Page.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\fmt\xp\fp_Run.h"\
	"..\abi\src\text\fmt\xp\fp_TableContainer.h"\
	"..\abi\src\text\fmt\xp\fv_View.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Glob.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\text\ptbl\xp\px_CR_ObjectChange.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Span.h"\
	"..\abi\src\text\ptbl\xp\px_CR_SpanChange.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Strux.h"\
	"..\abi\src\text\ptbl\xp\px_CR_StruxChange.h"\
	"..\abi\src\wp\ap\xp\ap_Dialog_Goto.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs_SchemeIds.h"\
	"..\abi\src\wp\ap\xp\ap_String_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Strings.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
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
	
NODEP_CPP_FL_SE=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fl_Squiggles.cpp
DEP_CPP_FL_SQ=\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_DrawArgs.h"\
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
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_Prefs.h"\
	"..\abi\src\af\xap\xp\xap_Prefs_SchemeIds.h"\
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
	"..\abi\src\text\fmt\xp\fl_Squiggles.h"\
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
	"..\abi\src\wp\ap\xp\ap_Dialog_Goto.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
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
	
NODEP_CPP_FL_SQ=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fl_TableLayout.cpp
DEP_CPP_FL_TA=\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_DrawArgs.h"\
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
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_Prefs.h"\
	"..\abi\src\af\xap\xp\xap_Prefs_SchemeIds.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\af\xap\xp\xav_View.h"\
	"..\abi\src\text\fmt\xp\fb_ColumnBreaker.h"\
	"..\abi\src\text\fmt\xp\fb_LineBreaker.h"\
	"..\abi\src\text\fmt\xp\fg_Graphic.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_BlockLayout.h"\
	"..\abi\src\text\fmt\xp\fl_ContainerLayout.h"\
	"..\abi\src\text\fmt\xp\fl_DocLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fl_SectionLayout.h"\
	"..\abi\src\text\fmt\xp\fl_TableLayout.h"\
	"..\abi\src\text\fmt\xp\fp_Column.h"\
	"..\abi\src\text\fmt\xp\fp_ContainerObject.h"\
	"..\abi\src\text\fmt\xp\fp_Fields.h"\
	"..\abi\src\text\fmt\xp\fp_Line.h"\
	"..\abi\src\text\fmt\xp\fp_Page.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\fmt\xp\fp_Run.h"\
	"..\abi\src\text\fmt\xp\fp_TableContainer.h"\
	"..\abi\src\text\fmt\xp\fv_View.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Glob.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\text\ptbl\xp\px_CR_ObjectChange.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Span.h"\
	"..\abi\src\text\ptbl\xp\px_CR_SpanChange.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Strux.h"\
	"..\abi\src\text\ptbl\xp\px_CR_StruxChange.h"\
	"..\abi\src\wp\ap\xp\ap_Dialog_Goto.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs_SchemeIds.h"\
	"..\abi\src\wp\ap\xp\ap_String_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Strings.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
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
	
NODEP_CPP_FL_TA=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fl_TestRoutines.cpp
DEP_CPP_FL_TE=\
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
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\text\fmt\xp\fb_ColumnBreaker.h"\
	"..\abi\src\text\fmt\xp\fg_Graphic.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_BlockLayout.h"\
	"..\abi\src\text\fmt\xp\fl_ContainerLayout.h"\
	"..\abi\src\text\fmt\xp\fl_DocLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fl_SectionLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Squiggles.h"\
	"..\abi\src\text\fmt\xp\fl_TableLayout.h"\
	"..\abi\src\text\fmt\xp\fp_Column.h"\
	"..\abi\src\text\fmt\xp\fp_ContainerObject.h"\
	"..\abi\src\text\fmt\xp\fp_Fields.h"\
	"..\abi\src\text\fmt\xp\fp_Line.h"\
	"..\abi\src\text\fmt\xp\fp_Page.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\fmt\xp\fp_Run.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Fragments.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	"..\abi\src\text\ptbl\xp\pp_TableAttrProp.h"\
	"..\abi\src\text\ptbl\xp\pt_PieceTable.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\pt_VarSet.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeHistory.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\wp\ap\xp\ap_String_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Strings.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
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
	
NODEP_CPP_FL_TE=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fp_Column.cpp
DEP_CPP_FP_CO=\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_DrawArgs.h"\
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
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_Prefs.h"\
	"..\abi\src\af\xap\xp\xap_Prefs_SchemeIds.h"\
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
	"..\abi\src\text\fmt\xp\fp_Column.h"\
	"..\abi\src\text\fmt\xp\fp_ContainerObject.h"\
	"..\abi\src\text\fmt\xp\fp_Line.h"\
	"..\abi\src\text\fmt\xp\fp_Page.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\fmt\xp\fp_TableContainer.h"\
	"..\abi\src\text\fmt\xp\fv_View.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\wp\ap\xp\ap_Dialog_Goto.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
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
	
NODEP_CPP_FP_CO=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fp_ContainerObject.cpp
DEP_CPP_FP_CON=\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_DrawArgs.h"\
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
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_Prefs.h"\
	"..\abi\src\af\xap\xp\xap_Prefs_SchemeIds.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\af\xap\xp\xav_View.h"\
	"..\abi\src\text\fmt\xp\fb_ColumnBreaker.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_ContainerLayout.h"\
	"..\abi\src\text\fmt\xp\fl_DocLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fl_SectionLayout.h"\
	"..\abi\src\text\fmt\xp\fp_Column.h"\
	"..\abi\src\text\fmt\xp\fp_ContainerObject.h"\
	"..\abi\src\text\fmt\xp\fp_Page.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\fmt\xp\fv_View.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\wp\ap\xp\ap_Dialog_Goto.h"\
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
	
NODEP_CPP_FP_CON=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fp_FieldListLabelRun.cpp
DEP_CPP_FP_FI=\
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
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\text\fmt\xp\fb_ColumnBreaker.h"\
	"..\abi\src\text\fmt\xp\fg_Graphic.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_BlockLayout.h"\
	"..\abi\src\text\fmt\xp\fl_ContainerLayout.h"\
	"..\abi\src\text\fmt\xp\fl_DocLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fl_SectionLayout.h"\
	"..\abi\src\text\fmt\xp\fp_FieldListLabelRun.h"\
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
	"..\abi\src\wp\ap\xp\ap_String_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Strings.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
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
	
NODEP_CPP_FP_FI=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fp_FmtMarkRun.cpp
DEP_CPP_FP_FM=\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_DrawArgs.h"\
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
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
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
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_BlockLayout.h"\
	"..\abi\src\text\fmt\xp\fl_ContainerLayout.h"\
	"..\abi\src\text\fmt\xp\fl_DocLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fl_SectionLayout.h"\
	"..\abi\src\text\fmt\xp\fp_Column.h"\
	"..\abi\src\text\fmt\xp\fp_ContainerObject.h"\
	"..\abi\src\text\fmt\xp\fp_Fields.h"\
	"..\abi\src\text\fmt\xp\fp_Line.h"\
	"..\abi\src\text\fmt\xp\fp_Page.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\fmt\xp\fp_Run.h"\
	"..\abi\src\text\fmt\xp\fv_View.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\wp\ap\xp\ap_Dialog_Goto.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs_SchemeIds.h"\
	"..\abi\src\wp\ap\xp\ap_String_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Strings.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
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
	
NODEP_CPP_FP_FM=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fp_FootnoteContainer.cpp
DEP_CPP_FP_FO=\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_DrawArgs.h"\
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
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_Prefs.h"\
	"..\abi\src\af\xap\xp\xap_Prefs_SchemeIds.h"\
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
	"..\abi\src\text\fmt\xp\fl_TableLayout.h"\
	"..\abi\src\text\fmt\xp\fp_Column.h"\
	"..\abi\src\text\fmt\xp\fp_ContainerObject.h"\
	"..\abi\src\text\fmt\xp\fp_FootnoteContainer.h"\
	"..\abi\src\text\fmt\xp\fp_Line.h"\
	"..\abi\src\text\fmt\xp\fp_Page.h"\
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
	"..\abi\src\wp\ap\xp\ap_Dialog_Goto.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
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
	
NODEP_CPP_FP_FO=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fp_Line.cpp
DEP_CPP_FP_LI=\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_DrawArgs.h"\
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
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_Prefs.h"\
	"..\abi\src\af\xap\xp\xap_Prefs_SchemeIds.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\af\xap\xp\xav_View.h"\
	"..\abi\src\text\fmt\xp\fb_Alignment.h"\
	"..\abi\src\text\fmt\xp\fb_ColumnBreaker.h"\
	"..\abi\src\text\fmt\xp\fg_Graphic.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_BlockLayout.h"\
	"..\abi\src\text\fmt\xp\fl_ContainerLayout.h"\
	"..\abi\src\text\fmt\xp\fl_DocLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fl_SectionLayout.h"\
	"..\abi\src\text\fmt\xp\fl_TableLayout.h"\
	"..\abi\src\text\fmt\xp\fp_Column.h"\
	"..\abi\src\text\fmt\xp\fp_ContainerObject.h"\
	"..\abi\src\text\fmt\xp\fp_Fields.h"\
	"..\abi\src\text\fmt\xp\fp_Line.h"\
	"..\abi\src\text\fmt\xp\fp_Page.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\fmt\xp\fp_Run.h"\
	"..\abi\src\text\fmt\xp\fp_TableContainer.h"\
	"..\abi\src\text\fmt\xp\fp_TextRun.h"\
	"..\abi\src\text\fmt\xp\fv_View.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\wp\ap\xp\ap_Dialog_Goto.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs_SchemeIds.h"\
	"..\abi\src\wp\ap\xp\ap_String_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Strings.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
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
	
NODEP_CPP_FP_LI=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fp_Page.cpp
DEP_CPP_FP_PA=\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_DrawArgs.h"\
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
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
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
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_BlockLayout.h"\
	"..\abi\src\text\fmt\xp\fl_ContainerLayout.h"\
	"..\abi\src\text\fmt\xp\fl_DocLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fl_SectionLayout.h"\
	"..\abi\src\text\fmt\xp\fp_Column.h"\
	"..\abi\src\text\fmt\xp\fp_ContainerObject.h"\
	"..\abi\src\text\fmt\xp\fp_Fields.h"\
	"..\abi\src\text\fmt\xp\fp_Line.h"\
	"..\abi\src\text\fmt\xp\fp_Page.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\fmt\xp\fp_Run.h"\
	"..\abi\src\text\fmt\xp\fp_TableContainer.h"\
	"..\abi\src\text\fmt\xp\fv_View.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\wp\ap\xp\ap_Dialog_Goto.h"\
	"..\abi\src\wp\ap\xp\ap_String_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Strings.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
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
	
NODEP_CPP_FP_PA=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fp_PageSize.cpp
DEP_CPP_FP_PAG=\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_types.h"\
	"..\abi\src\af\util\xp\ut_units.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fp_Run.cpp
DEP_CPP_FP_RU=\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_DrawArgs.h"\
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
	"..\abi\src\af\xap\xp\xav_View.h"\
	"..\abi\src\text\fmt\xp\fb_ColumnBreaker.h"\
	"..\abi\src\text\fmt\xp\fg_Graphic.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_BlockLayout.h"\
	"..\abi\src\text\fmt\xp\fl_ContainerLayout.h"\
	"..\abi\src\text\fmt\xp\fl_DocLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fl_SectionLayout.h"\
	"..\abi\src\text\fmt\xp\fl_TableLayout.h"\
	"..\abi\src\text\fmt\xp\fp_Column.h"\
	"..\abi\src\text\fmt\xp\fp_ContainerObject.h"\
	"..\abi\src\text\fmt\xp\fp_Fields.h"\
	"..\abi\src\text\fmt\xp\fp_Line.h"\
	"..\abi\src\text\fmt\xp\fp_Page.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\fmt\xp\fp_Run.h"\
	"..\abi\src\text\fmt\xp\fp_TableContainer.h"\
	"..\abi\src\text\fmt\xp\fp_TextRun.h"\
	"..\abi\src\text\fmt\xp\fv_View.h"\
	"..\abi\src\text\ptbl\xp\fd_Field.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Object.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\po_Bookmark.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\wp\ap\xp\ap_Dialog_Goto.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs_SchemeIds.h"\
	"..\abi\src\wp\ap\xp\ap_String_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Strings.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
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
	
NODEP_CPP_FP_RU=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fp_TableContainer.cpp
DEP_CPP_FP_TA=\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_DrawArgs.h"\
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
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_Prefs.h"\
	"..\abi\src\af\xap\xp\xap_Prefs_SchemeIds.h"\
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
	"..\abi\src\text\fmt\xp\fl_TableLayout.h"\
	"..\abi\src\text\fmt\xp\fp_Column.h"\
	"..\abi\src\text\fmt\xp\fp_ContainerObject.h"\
	"..\abi\src\text\fmt\xp\fp_Line.h"\
	"..\abi\src\text\fmt\xp\fp_Page.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\fmt\xp\fp_TableContainer.h"\
	"..\abi\src\text\fmt\xp\fv_View.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\wp\ap\xp\ap_Dialog_Goto.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
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
	
NODEP_CPP_FP_TA=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fp_TestRoutines.cpp
DEP_CPP_FP_TE=\
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
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\text\fmt\xp\fb_ColumnBreaker.h"\
	"..\abi\src\text\fmt\xp\fg_Graphic.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_BlockLayout.h"\
	"..\abi\src\text\fmt\xp\fl_ContainerLayout.h"\
	"..\abi\src\text\fmt\xp\fl_DocLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fl_SectionLayout.h"\
	"..\abi\src\text\fmt\xp\fp_Column.h"\
	"..\abi\src\text\fmt\xp\fp_ContainerObject.h"\
	"..\abi\src\text\fmt\xp\fp_Fields.h"\
	"..\abi\src\text\fmt\xp\fp_Line.h"\
	"..\abi\src\text\fmt\xp\fp_Page.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\fmt\xp\fp_Run.h"\
	"..\abi\src\text\fmt\xp\fp_TextRun.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\wp\ap\xp\ap_String_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Strings.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
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
	
NODEP_CPP_FP_TE=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fp_TextRun.cpp
DEP_CPP_FP_TEX=\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_DrawArgs.h"\
	"..\abi\src\af\gr\xp\gr_Graphics.h"\
	"..\abi\src\af\gr\xp\gr_Image.h"\
	"..\abi\src\af\gr\xp\gr_VectorImage.h"\
	"..\abi\src\af\util\xp\ut_abi-pango.h"\
	"..\abi\src\af\util\xp\ut_assert.h"\
	"..\abi\src\af\util\xp\ut_bijection.h"\
	"..\abi\src\af\util\xp\ut_bytebuf.h"\
	"..\abi\src\af\util\xp\ut_contextGlyph.h"\
	"..\abi\src\af\util\xp\ut_debugmsg.h"\
	"..\abi\src\af\util\xp\ut_exception.h"\
	"..\abi\src\af\util\xp\ut_growbuf.h"\
	"..\abi\src\af\util\xp\ut_hash.h"\
	"..\abi\src\af\util\xp\ut_iconv.h"\
	"..\abi\src\af\util\xp\ut_Language.h"\
	"..\abi\src\af\util\xp\ut_misc.h"\
	"..\abi\src\af\util\xp\ut_OverstrikingChars.h"\
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
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_BlockLayout.h"\
	"..\abi\src\text\fmt\xp\fl_ContainerLayout.h"\
	"..\abi\src\text\fmt\xp\fl_DocLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fl_SectionLayout.h"\
	"..\abi\src\text\fmt\xp\fp_Column.h"\
	"..\abi\src\text\fmt\xp\fp_ContainerObject.h"\
	"..\abi\src\text\fmt\xp\fp_Fields.h"\
	"..\abi\src\text\fmt\xp\fp_Line.h"\
	"..\abi\src\text\fmt\xp\fp_Page.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\fmt\xp\fp_Run.h"\
	"..\abi\src\text\fmt\xp\fp_TextRun.h"\
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
	"..\abi\src\wp\ap\xp\ap_Prefs.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs_SchemeIds.h"\
	"..\abi\src\wp\ap\xp\ap_String_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Strings.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
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
	
NODEP_CPP_FP_TEX=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fv_View.cpp
DEP_CPP_FV_VI=\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_DrawArgs.h"\
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
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Clipboard.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_Dlg_MessageBox.h"\
	"..\abi\src\af\xap\xp\xap_EncodingManager.h"\
	"..\abi\src\af\xap\xp\xap_Frame.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_Prefs.h"\
	"..\abi\src\af\xap\xp\xap_Prefs_SchemeIds.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\af\xap\xp\xav_View.h"\
	"..\abi\src\other\spell\xp\barbarisms.h"\
	"..\abi\src\other\spell\xp\ispell_def.h"\
	"..\abi\src\other\spell\xp\spell_manager.h"\
	"..\abi\src\text\fmt\xp\fb_ColumnBreaker.h"\
	"..\abi\src\text\fmt\xp\fg_Graphic.h"\
	"..\abi\src\text\fmt\xp\fg_GraphicRaster.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_AutoNum.h"\
	"..\abi\src\text\fmt\xp\fl_BlockLayout.h"\
	"..\abi\src\text\fmt\xp\fl_ContainerLayout.h"\
	"..\abi\src\text\fmt\xp\fl_DocLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fl_SectionLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Squiggles.h"\
	"..\abi\src\text\fmt\xp\fl_TableLayout.h"\
	"..\abi\src\text\fmt\xp\fp_Column.h"\
	"..\abi\src\text\fmt\xp\fp_ContainerObject.h"\
	"..\abi\src\text\fmt\xp\fp_Fields.h"\
	"..\abi\src\text\fmt\xp\fp_Line.h"\
	"..\abi\src\text\fmt\xp\fp_Page.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\fmt\xp\fp_Run.h"\
	"..\abi\src\text\fmt\xp\fp_TableContainer.h"\
	"..\abi\src\text\fmt\xp\fp_TextRun.h"\
	"..\abi\src\text\fmt\xp\fv_View.h"\
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
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\wp\ap\xp\ap_Dialog_Goto.h"\
	"..\abi\src\wp\ap\xp\ap_LeftRuler.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs_SchemeIds.h"\
	"..\abi\src\wp\ap\xp\ap_Ruler.h"\
	"..\abi\src\wp\ap\xp\ap_String_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Strings.h"\
	"..\abi\src\wp\ap\xp\ap_TopRuler.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
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
	
NODEP_CPP_FV_VI=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fv_View_cmd.cpp
DEP_CPP_FV_VIE=\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_DrawArgs.h"\
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
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Clipboard.h"\
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
	"..\abi\src\af\xap\xp\xav_View.h"\
	"..\abi\src\other\spell\xp\barbarisms.h"\
	"..\abi\src\other\spell\xp\ispell_def.h"\
	"..\abi\src\other\spell\xp\spell_manager.h"\
	"..\abi\src\text\fmt\xp\fb_ColumnBreaker.h"\
	"..\abi\src\text\fmt\xp\fg_Graphic.h"\
	"..\abi\src\text\fmt\xp\fg_GraphicRaster.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_AutoNum.h"\
	"..\abi\src\text\fmt\xp\fl_BlockLayout.h"\
	"..\abi\src\text\fmt\xp\fl_ContainerLayout.h"\
	"..\abi\src\text\fmt\xp\fl_DocLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fl_SectionLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Squiggles.h"\
	"..\abi\src\text\fmt\xp\fp_Column.h"\
	"..\abi\src\text\fmt\xp\fp_ContainerObject.h"\
	"..\abi\src\text\fmt\xp\fp_Fields.h"\
	"..\abi\src\text\fmt\xp\fp_Line.h"\
	"..\abi\src\text\fmt\xp\fp_Page.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\fmt\xp\fp_Run.h"\
	"..\abi\src\text\fmt\xp\fp_TableContainer.h"\
	"..\abi\src\text\fmt\xp\fp_TextRun.h"\
	"..\abi\src\text\fmt\xp\fv_View.h"\
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
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\wp\ap\xp\ap_Dialog_Goto.h"\
	"..\abi\src\wp\ap\xp\ap_LeftRuler.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs_SchemeIds.h"\
	"..\abi\src\wp\ap\xp\ap_Ruler.h"\
	"..\abi\src\wp\ap\xp\ap_String_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Strings.h"\
	"..\abi\src\wp\ap\xp\ap_TopRuler.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
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
	
NODEP_CPP_FV_VIE=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fv_View_protected.cpp
DEP_CPP_FV_VIEW=\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_DrawArgs.h"\
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
	"..\abi\src\af\util\xp\ut_worker.h"\
	"..\abi\src\af\util\xp\ut_xml.h"\
	"..\abi\src\af\xap\xp\xad_Document.h"\
	"..\abi\src\af\xap\xp\xap_App.h"\
	"..\abi\src\af\xap\xp\xap_Clipboard.h"\
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
	"..\abi\src\af\xap\xp\xav_View.h"\
	"..\abi\src\other\spell\xp\barbarisms.h"\
	"..\abi\src\other\spell\xp\ispell_def.h"\
	"..\abi\src\other\spell\xp\spell_manager.h"\
	"..\abi\src\text\fmt\xp\fb_ColumnBreaker.h"\
	"..\abi\src\text\fmt\xp\fg_Graphic.h"\
	"..\abi\src\text\fmt\xp\fg_GraphicRaster.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_AutoNum.h"\
	"..\abi\src\text\fmt\xp\fl_BlockLayout.h"\
	"..\abi\src\text\fmt\xp\fl_ContainerLayout.h"\
	"..\abi\src\text\fmt\xp\fl_DocLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fl_SectionLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Squiggles.h"\
	"..\abi\src\text\fmt\xp\fp_Column.h"\
	"..\abi\src\text\fmt\xp\fp_ContainerObject.h"\
	"..\abi\src\text\fmt\xp\fp_Fields.h"\
	"..\abi\src\text\fmt\xp\fp_Line.h"\
	"..\abi\src\text\fmt\xp\fp_Page.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\fmt\xp\fp_Run.h"\
	"..\abi\src\text\fmt\xp\fp_TextRun.h"\
	"..\abi\src\text\fmt\xp\fv_View.h"\
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
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\wp\ap\xp\ap_Dialog_Goto.h"\
	"..\abi\src\wp\ap\xp\ap_LeftRuler.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs.h"\
	"..\abi\src\wp\ap\xp\ap_Prefs_SchemeIds.h"\
	"..\abi\src\wp\ap\xp\ap_Ruler.h"\
	"..\abi\src\wp\ap\xp\ap_String_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Strings.h"\
	"..\abi\src\wp\ap\xp\ap_TopRuler.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
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
	
NODEP_CPP_FV_VIEW=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fv_View_TestRoutines.cpp
DEP_CPP_FV_VIEW_=\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_DrawArgs.h"\
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
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_Prefs.h"\
	"..\abi\src\af\xap\xp\xap_Prefs_SchemeIds.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\af\xap\xp\xav_View.h"\
	"..\abi\src\text\fmt\xp\fb_ColumnBreaker.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
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
	"..\abi\src\wp\ap\xp\ap_Dialog_Goto.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
	"..\abi\src\wp\impexp\xp\ie_types.h"\
	
NODEP_CPP_FV_VIEW_=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fb_Alignment.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fb_ColumnBreaker.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fb_LineBreaker.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fg_Graphic.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fg_GraphicRaster.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fg_GraphicVector.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fl_AutoLists.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fl_AutoNum.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fl_BlockLayout.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fl_ContainerLayout.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fl_DocLayout.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fl_DocListener.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fl_FootnoteLayout.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fl_Layout.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fl_SectionLayout.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fl_Squiggles.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fl_TableLayout.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fp_Column.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fp_ContainerObject.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fp_FieldListLabelRun.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fp_Fields.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fp_FootnoteContainer.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fp_Line.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fp_Page.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fp_PageSize.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fp_Run.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fp_TableContainer.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fp_TextRun.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fv_Cursor.h
# End Source File
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fv_View.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\abi\src\text\fmt\xp\fb_ColumnBreaker.cpp
DEP_CPP_FB_CO=\
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
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\text\fmt\xp\fb_ColumnBreaker.h"\
	"..\abi\src\text\fmt\xp\fg_Graphic.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_BlockLayout.h"\
	"..\abi\src\text\fmt\xp\fl_ContainerLayout.h"\
	"..\abi\src\text\fmt\xp\fl_DocLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fl_SectionLayout.h"\
	"..\abi\src\text\fmt\xp\fp_Column.h"\
	"..\abi\src\text\fmt\xp\fp_ContainerObject.h"\
	"..\abi\src\text\fmt\xp\fp_FootnoteContainer.h"\
	"..\abi\src\text\fmt\xp\fp_Line.h"\
	"..\abi\src\text\fmt\xp\fp_Page.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\fmt\xp\fp_TableContainer.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
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
	
NODEP_CPP_FB_CO=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# End Source File
# Begin Source File

SOURCE=.\PCH_fmt.cpp
DEP_CPP_PCH_F=\
	"..\abi\src\af\ev\xp\ev_EditBits.h"\
	"..\abi\src\af\gr\xp\gr_Caret.h"\
	"..\abi\src\af\gr\xp\gr_DrawArgs.h"\
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
	"..\abi\src\af\xap\xp\xap_Clipboard.h"\
	"..\abi\src\af\xap\xp\xap_Dialog.h"\
	"..\abi\src\af\xap\xp\xap_PangoFontManager.h"\
	"..\abi\src\af\xap\xp\xap_Prefs.h"\
	"..\abi\src\af\xap\xp\xap_Prefs_SchemeIds.h"\
	"..\abi\src\af\xap\xp\xap_String_Id.h"\
	"..\abi\src\af\xap\xp\xap_Strings.h"\
	"..\abi\src\af\xap\xp\xap_Types.h"\
	"..\abi\src\af\xap\xp\xav_Listener.h"\
	"..\abi\src\af\xap\xp\xav_View.h"\
	"..\abi\src\text\fmt\xp\fb_Alignment.h"\
	"..\abi\src\text\fmt\xp\fb_ColumnBreaker.h"\
	"..\abi\src\text\fmt\xp\fb_LineBreaker.h"\
	"..\abi\src\text\fmt\xp\fg_Graphic.h"\
	"..\abi\src\text\fmt\xp\fl_AutoLists.h"\
	"..\abi\src\text\fmt\xp\fl_AutoNum.h"\
	"..\abi\src\text\fmt\xp\fl_BlockLayout.h"\
	"..\abi\src\text\fmt\xp\fl_ContainerLayout.h"\
	"..\abi\src\text\fmt\xp\fl_DocLayout.h"\
	"..\abi\src\text\fmt\xp\fl_Layout.h"\
	"..\abi\src\text\fmt\xp\fl_SectionLayout.h"\
	"..\abi\src\text\fmt\xp\fp_Column.h"\
	"..\abi\src\text\fmt\xp\fp_ContainerObject.h"\
	"..\abi\src\text\fmt\xp\fp_Fields.h"\
	"..\abi\src\text\fmt\xp\fp_Line.h"\
	"..\abi\src\text\fmt\xp\fp_Page.h"\
	"..\abi\src\text\fmt\xp\fp_PageSize.h"\
	"..\abi\src\text\fmt\xp\fp_Run.h"\
	"..\abi\src\text\fmt\xp\fp_TextRun.h"\
	"..\abi\src\text\fmt\xp\fv_View.h"\
	"..\abi\src\text\ptbl\xp\pd_Document.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag.h"\
	"..\abi\src\text\ptbl\xp\pf_Frag_Text.h"\
	"..\abi\src\text\ptbl\xp\pl_Listener.h"\
	"..\abi\src\text\ptbl\xp\pp_AttrProp.h"\
	"..\abi\src\text\ptbl\xp\pp_Property.h"\
	"..\abi\src\text\ptbl\xp\pp_Revision.h"\
	"..\abi\src\text\ptbl\xp\pt_Types.h"\
	"..\abi\src\text\ptbl\xp\px_ChangeRecord.h"\
	"..\abi\src\text\ptbl\xp\px_CR_FmtMark.h"\
	"..\abi\src\text\ptbl\xp\px_CR_FmtMarkChange.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Object.h"\
	"..\abi\src\text\ptbl\xp\px_CR_ObjectChange.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Span.h"\
	"..\abi\src\text\ptbl\xp\px_CR_SpanChange.h"\
	"..\abi\src\text\ptbl\xp\px_CR_Strux.h"\
	"..\abi\src\text\ptbl\xp\px_CR_StruxChange.h"\
	"..\abi\src\wp\ap\xp\ap_Dialog_Goto.h"\
	"..\abi\src\wp\ap\xp\ap_String_Id.h"\
	"..\abi\src\wp\ap\xp\ap_Strings.h"\
	"..\abi\src\wp\impexp\xp\ie_FileInfo.h"\
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
	".\PCH_fmt.h"\
	
NODEP_CPP_PCH_F=\
	"..\abi\src\af\util\xp\pango\pango.h"\
	"..\abi\src\af\util\xp\pango\pangoft2.h"\
	
# ADD CPP /Yc"PCH_fmt.h"
# End Source File
# Begin Source File

SOURCE=.\PCH_fmt.h
# End Source File
# End Target
# End Project
