This directory contains the MSVC project files for building fribidi.

***************************************************************************
* IMPORTANT: if MSVC refuses to open the project files (sometimes you get *
* a message along the lines "this file was not created by MSVC", other	  *
* times MSVC just silently fails), then almost certainly the files you	  *
* have use Unix convention for ending lines with \n, rather than the DOS  *
* convention of using \r\n. You just need to use some tool to fix this (I *
* use the free Programmer's File Editor, PFE32.EXE, which makes it easy). *
* Once you do this, MSVC should open the files. 						  *
***************************************************************************

The project files are set to build memory-optimized version of fribidi,
but a target is provided for speed optimized builds as well. If you are
fussy and want something half-way, you will need to build
fribidi_create_char_types.exe, use it to generate fribidi_tab_char_type_?.i
and then set the HAS_FRIBIDI_TAB_CHAR_TYPE_?_I defines accordingly (have
a look at fribidi_char_type.c).

Tomas, 27/07/2002
<tomas@frydrych.uklinux.net>
