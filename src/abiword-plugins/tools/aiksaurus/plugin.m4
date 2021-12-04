dnl= ##########################################################################
dnl= # abiword-plugins: autogen.sh header
dnl= # this file is executed as a shell script
dnl= 
dnl= # 1. abi_plugin_macro is the name of the main macro defined here:
dnl= abi_plugin_macro="ABIPGN_AIKSAURUS"
dnl= 
dnl= # 2. abi_plugin_files is the list of files that configure must generate:
dnl= abi_plugin_files="GNUmakefile xp/GNUmakefile"
dnl= 
dnl= # 3. abi_plugin_desc is a short description of the plugin
dnl= abi_plugin_desc="Plugin to allow abiword to connect with AikSaurus."
dnl=
dnl= # 4. abi_plugin_enable - whether plugin should be enabled by default 
dnl= abi_plugin_enable="yes"
dnl=
dnl= return
dnl= ##########################################################################

AC_DEFUN([ABIPGN_AIKSAURUS],[

_abi_cppflags_save="$CPPFLAGS"
_abi_ldflags_save="$LDFLAGS"

ABI_AIKSAURUS_CPPFLAGS=""
ABI_AIKSAURUS_LDFLAGS=""

# Checks for libraries.
# Checks for header files.

AC_ARG_WITH(Aiksaurus,[  --with-Aiksaurus=DIR    Aiksaurus library in DIR],[
	if [ test "x$withval" = "xno" ]; then
		AC_MSG_ERROR([* * * Aiksaurus library required to build this plugin * * *])
	elif [ test "x$withval" != "xyes" ]; then
		ABI_AIKSAURUS_CPPFLAGS="-I$withval/include"
		ABI_AIKSAURUS_LDFLAGS="-L$withval/lib"
	fi
])

CPPFLAGS="$CPPFLAGS $ABI_AIKSAURUS_CPPFLAGS"
LDFLAGS="$LDFLAGS $ABI_AIKSAURUS_LDFLAGS"

AC_LANG_CPLUSPLUS
AC_CHECK_HEADER(Aiksaurus.h,[
	ABI_AIKSAURUS_LDFLAGS="-lAiksaurus $ABI_AIKSAURUS_LDFLAGS"
],[	ABI_PLUGIN_REPORT([aiksaurus: error - Aiksaurus.h not found])
	abi_plugin_disable=yes
])
AC_LANG_C

if test $abi_plugin_disable = no; then
	dnl other front ends will be possible eventually, but for the moment it's only GTK-1.2

	ABI_GTK12(2)
	ABI_AIKSAURUS_CPPFLAGS="$ABI_AIKSAURUS_CPPFLAGS `$abi_gtk_config --cflags`"
	ABI_AIKSAURUS_LDFLAGS="$ABI_AIKSAURUS_LDFLAGS `$abi_gtk_config --libs`"

	AC_LANG_CPLUSPLUS
	AC_CHECK_HEADER(AiksaurusGTK.h,[
		ABI_AIKSAURUS_LDFLAGS="-lAiksaurusGTK $ABI_AIKSAURUS_LDFLAGS"
	],[	ABI_PLUGIN_REPORT([aiksaurus: error - AiksaurusGTK.h not found])
		abi_plugin_disable=yes
	])
	AC_LANG_C
fi

if test $abi_plugin_disable = no; then
	ABI_PLUGIN_REPORT([aiksaurus: okay])
fi

AC_SUBST(ABI_AIKSAURUS_CPPFLAGS)
AC_SUBST(ABI_AIKSAURUS_LDFLAGS)

CPPFLAGS="$_abi_cppflags_save"
LDFLAGS="$_abi_ldflags_save"
])
