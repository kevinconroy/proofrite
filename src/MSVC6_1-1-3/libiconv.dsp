# Microsoft Developer Studio Project File - Name="libiconv" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libiconv - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libiconv.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libiconv.mak" CFG="libiconv - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libiconv - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libiconv - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libiconv - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug\obj"
# PROP Intermediate_Dir ".\Debug\obj\libiconv"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Z7 /Od /Ob1 /Gy /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\abi\src\af\gr\win" /I "..\abi\src\spell\other" /I "..\expat\xmlparse" /I "..\expat\xmltok" /D "_X86_" /D "DEBUG" /D "_DEBUG" /D "_CTRDBG_MAP_ALLOC" /D "WIN32" /D "UT_DEBUG" /D "PT_TEST" /D "FMT_TEST" /D "UT_TEST" /GF /c
# ADD CPP /nologo /MDd /W3 /Zi /Od /Ob1 /Gy /I "..\libiconv" /I "..\libiconv\src" /I "..\libiconv\include" /I "..\libiconv\libcharset\include" /I "..\abi\src\af\gr\win" /I "..\abi\src\spell\other" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\wv" /I "..\wv\libole2" /I "..\wv\glib-wv" /I "..\expat\lib" /D "DEBUG" /D "_DEBUG" /D "_CTRDBG_MAP_ALLOC" /D "UT_DEBUG" /D "PT_TEST" /D "FMT_TEST" /D "UT_TEST" /D "_X86_" /D "WIN32" /D HAVE_STRING_H=1 /GF /c
# ADD BASE RSC /l 0x41d
# ADD RSC /l 0x41d
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\Debug\obj\libAbi_libiconv_s.lib"

!ELSEIF  "$(CFG)" == "libiconv - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "libiconv___Win32_Release"
# PROP BASE Intermediate_Dir "libiconv___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Release\obj"
# PROP Intermediate_Dir ".\Release\obj\libiconv"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Z7 /Od /Ob1 /Gy /I "..\libiconv" /I "..\libiconv\src" /I "..\libiconv\include" /I "..\abi\src\af\gr\win" /I "..\abi\src\spell\other" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\wv" /I "..\wv\libole2" /I "..\wv\glib-wv" /D "LIBICONV_PLUG" /D "_X86_" /D "DEBUG" /D "_DEBUG" /D "_CTRDBG_MAP_ALLOC" /D "WIN32" /D "UT_DEBUG" /D "PT_TEST" /D "FMT_TEST" /D "UT_TEST" /GF /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MD /W3 /Zi /O1 /Ob2 /I "..\libiconv" /I "..\libiconv\src" /I "..\libiconv\include" /I "..\libiconv\libcharset\include" /I "..\abi\src\af\gr\win" /I "..\abi\src\spell\other" /I "..\abi\src\af\xap\xp" /I "..\abi\src\af\xap\win" /I "..\abi\src\af\ev\xp" /I "..\abi\src\af\ev\win" /I "..\abi\src\af\util\xp" /I "..\abi\src\af\util\win" /I "..\abi\src\af\gr\xp" /I "..\wv" /I "..\wv\libole2" /I "..\wv\glib-wv" /I "..\expat\lib" /D "NDEBUG" /D "_X86_" /D "WIN32" /D HAVE_STRING_H=1 /GF /c
# ADD BASE RSC /l 0x41d
# ADD RSC /l 0x41d
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\Debug\obj\libAbi_libiconv_s.lib"
# ADD LIB32 /nologo /out:".\Release\obj\libAbi_libiconv_s.lib"

!ENDIF 

# Begin Target

# Name "libiconv - Win32 Debug"
# Name "libiconv - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "c;cpp"
# Begin Source File

SOURCE=..\libiconv\lib\iconv.c
DEP_CPP_ICONV=\
	"..\libiconv\include\iconv.h"\
	"..\libiconv\lib\aliases.h"\
	"..\libiconv\lib\aliases_aix.h"\
	"..\libiconv\lib\aliases_dos.h"\
	"..\libiconv\lib\aliases_extra.h"\
	"..\libiconv\lib\aliases_osf1.h"\
	"..\libiconv\lib\armscii_8.h"\
	"..\libiconv\lib\ascii.h"\
	"..\libiconv\lib\big5.h"\
	"..\libiconv\lib\big5hkscs.h"\
	"..\libiconv\lib\c99.h"\
	"..\libiconv\lib\ces_big5.h"\
	"..\libiconv\lib\ces_gbk.h"\
	"..\libiconv\lib\cjk_variants.h"\
	"..\libiconv\lib\cns11643.h"\
	"..\libiconv\lib\cns11643_1.h"\
	"..\libiconv\lib\cns11643_15.h"\
	"..\libiconv\lib\cns11643_2.h"\
	"..\libiconv\lib\cns11643_3.h"\
	"..\libiconv\lib\cns11643_4.h"\
	"..\libiconv\lib\cns11643_4a.h"\
	"..\libiconv\lib\cns11643_4b.h"\
	"..\libiconv\lib\cns11643_5.h"\
	"..\libiconv\lib\cns11643_6.h"\
	"..\libiconv\lib\cns11643_7.h"\
	"..\libiconv\lib\cns11643_inv.h"\
	"..\libiconv\lib\config.h"\
	"..\libiconv\lib\converters.h"\
	"..\libiconv\lib\cp1046.h"\
	"..\libiconv\lib\cp1124.h"\
	"..\libiconv\lib\cp1125.h"\
	"..\libiconv\lib\cp1129.h"\
	"..\libiconv\lib\cp1133.h"\
	"..\libiconv\lib\cp1161.h"\
	"..\libiconv\lib\cp1162.h"\
	"..\libiconv\lib\cp1163.h"\
	"..\libiconv\lib\cp1250.h"\
	"..\libiconv\lib\cp1251.h"\
	"..\libiconv\lib\cp1252.h"\
	"..\libiconv\lib\cp1253.h"\
	"..\libiconv\lib\cp1254.h"\
	"..\libiconv\lib\cp1255.h"\
	"..\libiconv\lib\cp1256.h"\
	"..\libiconv\lib\cp1257.h"\
	"..\libiconv\lib\cp1258.h"\
	"..\libiconv\lib\cp437.h"\
	"..\libiconv\lib\cp737.h"\
	"..\libiconv\lib\cp775.h"\
	"..\libiconv\lib\cp850.h"\
	"..\libiconv\lib\cp852.h"\
	"..\libiconv\lib\cp853.h"\
	"..\libiconv\lib\cp855.h"\
	"..\libiconv\lib\cp856.h"\
	"..\libiconv\lib\cp857.h"\
	"..\libiconv\lib\cp858.h"\
	"..\libiconv\lib\cp860.h"\
	"..\libiconv\lib\cp861.h"\
	"..\libiconv\lib\cp862.h"\
	"..\libiconv\lib\cp863.h"\
	"..\libiconv\lib\cp864.h"\
	"..\libiconv\lib\cp865.h"\
	"..\libiconv\lib\cp866.h"\
	"..\libiconv\lib\cp869.h"\
	"..\libiconv\lib\cp874.h"\
	"..\libiconv\lib\cp922.h"\
	"..\libiconv\lib\cp932.h"\
	"..\libiconv\lib\cp932ext.h"\
	"..\libiconv\lib\cp936ext.h"\
	"..\libiconv\lib\cp943.h"\
	"..\libiconv\lib\cp949.h"\
	"..\libiconv\lib\cp950.h"\
	"..\libiconv\lib\cp950ext.h"\
	"..\libiconv\lib\dec_hanyu.h"\
	"..\libiconv\lib\dec_kanji.h"\
	"..\libiconv\lib\encodings.def"\
	"..\libiconv\lib\encodings_aix.def"\
	"..\libiconv\lib\encodings_dos.def"\
	"..\libiconv\lib\encodings_extra.def"\
	"..\libiconv\lib\encodings_local.def"\
	"..\libiconv\lib\encodings_osf1.def"\
	"..\libiconv\lib\euc_cn.h"\
	"..\libiconv\lib\euc_jisx0213.h"\
	"..\libiconv\lib\euc_jp.h"\
	"..\libiconv\lib\euc_kr.h"\
	"..\libiconv\lib\euc_tw.h"\
	"..\libiconv\lib\flags.h"\
	"..\libiconv\lib\flushwc.h"\
	"..\libiconv\lib\gb18030.h"\
	"..\libiconv\lib\gb18030ext.h"\
	"..\libiconv\lib\gb18030uni.h"\
	"..\libiconv\lib\gb2312.h"\
	"..\libiconv\lib\gbk.h"\
	"..\libiconv\lib\gbkext1.h"\
	"..\libiconv\lib\gbkext2.h"\
	"..\libiconv\lib\gbkext_inv.h"\
	"..\libiconv\lib\georgian_academy.h"\
	"..\libiconv\lib\georgian_ps.h"\
	"..\libiconv\lib\hkscs.h"\
	"..\libiconv\lib\hp_roman8.h"\
	"..\libiconv\lib\hz.h"\
	"..\libiconv\lib\iso2022_cn.h"\
	"..\libiconv\lib\iso2022_cnext.h"\
	"..\libiconv\lib\iso2022_jp.h"\
	"..\libiconv\lib\iso2022_jp1.h"\
	"..\libiconv\lib\iso2022_jp2.h"\
	"..\libiconv\lib\iso2022_jp3.h"\
	"..\libiconv\lib\iso2022_kr.h"\
	"..\libiconv\lib\iso646_cn.h"\
	"..\libiconv\lib\iso646_jp.h"\
	"..\libiconv\lib\iso8859_1.h"\
	"..\libiconv\lib\iso8859_10.h"\
	"..\libiconv\lib\iso8859_13.h"\
	"..\libiconv\lib\iso8859_14.h"\
	"..\libiconv\lib\iso8859_15.h"\
	"..\libiconv\lib\iso8859_16.h"\
	"..\libiconv\lib\iso8859_2.h"\
	"..\libiconv\lib\iso8859_3.h"\
	"..\libiconv\lib\iso8859_4.h"\
	"..\libiconv\lib\iso8859_5.h"\
	"..\libiconv\lib\iso8859_6.h"\
	"..\libiconv\lib\iso8859_7.h"\
	"..\libiconv\lib\iso8859_8.h"\
	"..\libiconv\lib\iso8859_9.h"\
	"..\libiconv\lib\isoir165.h"\
	"..\libiconv\lib\isoir165ext.h"\
	"..\libiconv\lib\java.h"\
	"..\libiconv\lib\jisx0201.h"\
	"..\libiconv\lib\jisx0208.h"\
	"..\libiconv\lib\jisx0212.h"\
	"..\libiconv\lib\jisx0213.h"\
	"..\libiconv\lib\johab.h"\
	"..\libiconv\lib\johab_hangul.h"\
	"..\libiconv\lib\koi8_r.h"\
	"..\libiconv\lib\koi8_ru.h"\
	"..\libiconv\lib\koi8_t.h"\
	"..\libiconv\lib\koi8_u.h"\
	"..\libiconv\lib\ksc5601.h"\
	"..\libiconv\lib\loop_unicode.h"\
	"..\libiconv\lib\loop_wchar.h"\
	"..\libiconv\lib\loops.h"\
	"..\libiconv\lib\mac_arabic.h"\
	"..\libiconv\lib\mac_centraleurope.h"\
	"..\libiconv\lib\mac_croatian.h"\
	"..\libiconv\lib\mac_cyrillic.h"\
	"..\libiconv\lib\mac_greek.h"\
	"..\libiconv\lib\mac_hebrew.h"\
	"..\libiconv\lib\mac_iceland.h"\
	"..\libiconv\lib\mac_roman.h"\
	"..\libiconv\lib\mac_romania.h"\
	"..\libiconv\lib\mac_thai.h"\
	"..\libiconv\lib\mac_turkish.h"\
	"..\libiconv\lib\mac_ukraine.h"\
	"..\libiconv\lib\mulelao.h"\
	"..\libiconv\lib\nextstep.h"\
	"..\libiconv\lib\riscos1.h"\
	"..\libiconv\lib\shift_jisx0213.h"\
	"..\libiconv\lib\sjis.h"\
	"..\libiconv\lib\tcvn.h"\
	"..\libiconv\lib\tds565.h"\
	"..\libiconv\lib\tis620.h"\
	"..\libiconv\lib\translit.h"\
	"..\libiconv\lib\ucs2.h"\
	"..\libiconv\lib\ucs2be.h"\
	"..\libiconv\lib\ucs2internal.h"\
	"..\libiconv\lib\ucs2le.h"\
	"..\libiconv\lib\ucs2swapped.h"\
	"..\libiconv\lib\ucs4.h"\
	"..\libiconv\lib\ucs4be.h"\
	"..\libiconv\lib\ucs4internal.h"\
	"..\libiconv\lib\ucs4le.h"\
	"..\libiconv\lib\ucs4swapped.h"\
	"..\libiconv\lib\uhc_1.h"\
	"..\libiconv\lib\uhc_2.h"\
	"..\libiconv\lib\utf16.h"\
	"..\libiconv\lib\utf16be.h"\
	"..\libiconv\lib\utf16le.h"\
	"..\libiconv\lib\utf32.h"\
	"..\libiconv\lib\utf32be.h"\
	"..\libiconv\lib\utf32le.h"\
	"..\libiconv\lib\utf7.h"\
	"..\libiconv\lib\utf8.h"\
	"..\libiconv\lib\vietcomb.h"\
	"..\libiconv\lib\viscii.h"\
	"..\libiconv\libcharset\include\libcharset.h"\
	
# End Source File
# Begin Source File

SOURCE=..\libiconv\libcharset\lib\localcharset.c
DEP_CPP_LOCAL=\
	"..\libiconv\src\config.h"\
	
# End Source File
# End Group
# Begin Group "src Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\libiconv\src\aliases.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\armscii_8.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\ascii.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\big5.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\ces_big5.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\ces_gbk.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\cjk_variants.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\cns11643.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\cns11643_1.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\cns11643_2.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\cns11643_3.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\cns11643_inv.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\config.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\converters.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\cp1133.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\cp1250.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\cp1251.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\cp1252.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\cp1253.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\cp1254.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\cp1255.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\cp1256.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\cp1257.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\cp1258.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\cp850.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\cp866.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\cp874.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\cp932.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\cp932ext.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\cp936ext.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\cp950.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\cp950ext.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\euc_cn.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\euc_jp.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\euc_kr.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\euc_tw.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\flags.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\gb12345.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\gb12345ext.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\gb2312.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\gbk.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\gbkext1.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\gbkext2.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\gbkext_inv.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\georgian_academy.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\georgian_ps.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\hp_roman8.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\hz.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\iso2022_cn.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\iso2022_cnext.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\iso2022_jp.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\iso2022_jp1.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\iso2022_jp2.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\iso2022_kr.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\iso8859_1.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\iso8859_10.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\iso8859_13.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\iso8859_14.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\iso8859_15.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\iso8859_2.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\iso8859_3.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\iso8859_4.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\iso8859_5.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\iso8859_6.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\iso8859_7.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\iso8859_8.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\iso8859_9.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\java.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\jisx0201.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\jisx0208.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\jisx0212.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\johab.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\johab_hangul.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\koi8_r.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\koi8_ru.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\koi8_u.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\ksc5601.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\mac_arabic.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\mac_centraleurope.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\mac_croatian.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\mac_cyrillic.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\mac_greek.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\mac_hebrew.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\mac_iceland.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\mac_roman.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\mac_romania.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\mac_thai.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\mac_turkish.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\mac_ukraine.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\mulelao.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\nextstep.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\sjis.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\tcvn.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\tis620.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\translit.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\ucs2.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\ucs2internal.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\ucs2swapped.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\ucs4.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\ucs4internal.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\ucs4swapped.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\utf16.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\utf7.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\utf8.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\src\viscii.h
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\libiconv\include\iconv.h
# End Source File
# Begin Source File

SOURCE=..\libiconv\include\libiconv.h
# End Source File
# End Group
# End Target
# End Project
