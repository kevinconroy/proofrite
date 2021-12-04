dnl= ##########################################################################
dnl= # abiword-plugins: autogen.sh header
dnl= # this file is executed as a shell script
dnl= 
dnl= # 1. abi_plugin_macro is the name of the main macro defined here:
dnl= abi_plugin_macro="ABIPGN_GYPSY"
dnl= 
dnl= # 2. abi_plugin_files is the list of files that configure must generate:
dnl= abi_plugin_files="GNUmakefile xp/GNUmakefile"
dnl= 
dnl= # 3. abi_plugin_desc is a short description of the plugin
dnl= abi_plugin_desc="Plugin to allow abiword to use python"
dnl=
dnl= # 4. abi_plugin_enable - whether plugin should be enabled by default 
dnl= abi_plugin_enable="no"
dnl=
dnl= return
dnl= ##########################################################################

AC_DEFUN([ABIPGN_GYPSY],[

_abi_cppflags_save="$CPPFLAGS"
_abi_ldflags_save="$LDFLAGS"

ABI_GYPSY_CPPFLAGS=""
ABI_GYPSY_LDFLAGS=""

# Checks for libraries.
# Checks for header files.

AC_ARG_WITH(python,[  --with-python=DIR        Python 2.2 library in DIR],[
	if test "x$withval" = "xno"; then
		ABI_PLUGIN_REPORT([gypsython: Python support disabled])
		abi_plugin_disable=yes
	elif test "x$withval" != "xyes"; then
		ABI_GYPSY_CPPFLAGS="-I$withval/include/python2.2"
		ABI_GYPSY_LDFLAGS="-L$withval/lib"
		CPPFLAGS="$CPPFLAGS -I$withval/include/python2.2"
		LDFLAGS="$LDFLAGS -L$withval/lib"
	else
		ABI_GYPSY_CPPFLAGS="-I/usr/include/python2.2"
		CPPFLAGS="$CPPFLAGS -I/usr/include/python2.2"
	fi
],[	ABI_GYPSY_CPPFLAGS="-I/usr/include/python2.2"
	CPPFLAGS="$CPPFLAGS -I/usr/include/python2.2"
])

if test $abi_plugin_disable != yes; then
	AC_CHECK_HEADER(Python.h,[
		AC_CHECK_LIB(python2.2,Py_Initialize,[
			ABI_GYPSY_LDFLAGS="$ABI_GYPSY_LDFLAGS -lpython2.2"
			ABI_PLUGIN_REPORT([gypsython: okay])
		],[	ABI_PLUGIN_REPORT([gypsython: error - Python library not found])
			abi_plugin_disable=yes
		])
	],[	ABI_PLUGIN_REPORT([gypsython: error - Python header not found])
		abi_plugin_disable=yes
	])
fi

AC_SUBST(ABI_GYPSY_CPPFLAGS)
AC_SUBST(ABI_GYPSY_LDFLAGS)

CPPFLAGS="$_abi_cppflags_save"
LDFLAGS="$_abi_ldflags_save"
])
