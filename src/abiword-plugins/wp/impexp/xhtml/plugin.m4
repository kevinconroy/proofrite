dnl= ##########################################################################
dnl= # abiword-plugins: autogen.sh header
dnl= # this file is executed as a shell script
dnl= 
dnl= # 1. abi_plugin_macro is the name of the main macro defined here:
dnl= abi_plugin_macro="ABIPGN_XHTML"
dnl= abi_plugin_macro_init="ABIPGN_XHTML_INIT"
dnl= abi_plugin_macro_end="ABIPGN_XHTML_END"
dnl= 
dnl= # 2. abi_plugin_files is the list of files that configure must generate:
dnl= abi_plugin_files="GNUmakefile xp/GNUmakefile"
dnl= 
dnl= # 3. abi_plugin_desc is a short description of the plugin
dnl= abi_plugin_desc="Plugin to enable import of Multipart HTML documents"
dnl=
dnl= # 4. abi_plugin_enable - whether plugin should be enabled by default 
dnl= abi_plugin_enable="yes"
dnl=
dnl= return
dnl= ##########################################################################

AC_DEFUN([ABIPGN_XHTML_INIT],[

inter7eps_disable=no
tidy_disable=no

])

AC_DEFUN([ABIPGN_XHTML],[

_abi_cppflags_save="$CPPFLAGS"
_abi_ldflags_save="$LDFLAGS"

# Checks for libraries.
# Checks for header files.

ABI_XHTML_I7EPS_CPPFLAGS=""
ABI_XHTML_I7EPS_LDFLAGS=""

AC_ARG_WITH(inter7eps,[  --with-inter7eps=DIR     inter7 EPS library in DIR],[
	if test "x$withval" = "xno"; then
		ABI_PLUGIN_REPORT([xhtml(mht):  inter7 EPS support disabled])
		inter7eps_disable=yes
	elif test "x$withval" != "xyes"; then
		ABI_XHTML_I7EPS_CPPFLAGS="-I$withval/include/eps"
		ABI_XHTML_I7EPS_LDFLAGS="-L$withval/lib"
		CPPFLAGS="$CPPFLAGS -I$withval/include/eps"
		LDFLAGS="$LDFLAGS -L$withval/lib"
	else
		ABI_XHTML_I7EPS_CPPFLAGS="-I/usr/include/eps"
		CPPFLAGS="$CPPFLAGS -I/usr/include/eps"
	fi
],[	ABI_XHTML_I7EPS_CPPFLAGS="-I/usr/include/eps"
	CPPFLAGS="$CPPFLAGS -I/usr/include/eps"
])

if test $inter7eps_disable != yes; then
	AC_CHECK_HEADER(mime.h,[
		ABI_PLUGIN_REPORT([xhtml(mht):  okay])
		ABI_XHTML_I7EPS_CPPFLAGS="$ABI_XHTML_I7EPS_CPPFLAGS -DXHTML_MULTIPART_SUPPORTED"
		ABI_XHTML_I7EPS_LDFLAGS="$ABI_XHTML_I7EPS_LDFLAGS -leps"
	],[	ABI_PLUGIN_REPORT([xhtml(mht):  error - inter7 EPS headers not found])
		ABI_PLUGIN_REPORT([xhtml(mht):          http://www.inter7.com/eps/])
		inter7eps_disable=yes
	])
fi
if test $inter7eps_disable = yes; then
	ABI_XHTML_I7EPS_CPPFLAGS=""
	ABI_XHTML_I7EPS_LDFLAGS=""
fi

ABI_XHTML_TIDY_CPPFLAGS=""
ABI_XHTML_TIDY_LDFLAGS=""

AC_ARG_WITH(libtidy,[  --with-libtidy=DIR       tidy library in DIR],[
	if test "x$withval" = "xno"; then
		ABI_PLUGIN_REPORT([xhtml(html): libtidy support disabled])
		tidy_disable=yes
	elif test "x$withval" != "xyes"; then
		ABI_XHTML_TIDY_CPPFLAGS="-I$withval/include"
		ABI_XHTML_TIDY_LDFLAGS="-L$withval/lib"
		CPPFLAGS="$CPPFLAGS -I$withval/include"
		LDFLAGS="$LDFLAGS -L$withval/lib"
	fi
])

if test $tidy_disable != yes; then
	AC_CHECK_HEADER(tidy.h,[
		ABI_PLUGIN_REPORT([xhtml(html): okay])
		ABI_XHTML_TIDY_CPPFLAGS="$ABI_XHTML_TIDY_CPPFLAGS -DXHTML_HTML_SUPPORTED"
		ABI_XHTML_TIDY_LDFLAGS="$ABI_XHTML_TIDY_LDFLAGS -ltidy"
	],[	ABI_PLUGIN_REPORT([xhtml(html): error - libtidy headers not found])
		ABI_PLUGIN_REPORT([xhtml(html):         http://tidy.sourceforge.net/])
		tidy_disable=yes
	])
fi
if test $tidy_disable = yes; then
	ABI_XHTML_TIDY_CPPFLAGS=""
	ABI_XHTML_TIDY_LDFLAGS=""
fi

ABI_XHTML_CPPFLAGS="$ABI_XHTML_I7EPS_CPPFLAGS $ABI_XHTML_TIDY_CPPFLAGS"
ABI_XHTML_LDFLAGS="$ABI_XHTML_I7EPS_LDFLAGS $ABI_XHTML_TIDY_LDFLAGS"

AC_SUBST(ABI_XHTML_CPPFLAGS)
AC_SUBST(ABI_XHTML_LDFLAGS)

CPPFLAGS="$_abi_cppflags_save"
LDFLAGS="$_abi_ldflags_save"
])

AC_DEFUN([ABIPGN_XHTML_END],[

AM_CONDITIONAL(ABI_XHTML_MHT,[test $inter7eps_disable != yes])
AM_CONDITIONAL(ABI_XHTML_HTML,[test $tidy_disable != yes])

])
