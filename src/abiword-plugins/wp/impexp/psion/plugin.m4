dnl= ##########################################################################
dnl= # abiword-plugins: autogen.sh header
dnl= # this file is executed as a shell script
dnl= 
dnl= # 1. abi_plugin_macro is the name of the main macro defined here:
dnl= abi_plugin_macro="ABIPGN_PSION"
dnl= 
dnl= # 2. abi_plugin_files is the list of files that configure must generate:
dnl= abi_plugin_files="GNUmakefile xp/GNUmakefile"
dnl= 
dnl= # 3. abi_plugin_desc is a short description of the plugin
dnl= abi_plugin_desc="psion word import"
dnl=
dnl= # 4. abi_plugin_enable - whether plugin should be enabled by default 
dnl= abi_plugin_enable="yes"
dnl=
dnl= return
dnl= ##########################################################################

AC_DEFUN([ABIPGN_PSION],[

_abi_cppflags_save="$CPPFLAGS"
_abi_ldflags_save="$LDFLAGS"

ABI_PSION_CPPFLAGS=""
ABI_PSION_LDFLAGS=""

# Checks for libraries.
# Checks for header files.

AC_ARG_WITH(psiconv,[  --with-psiconv=DIR      use libpsiconv in DIR],[
	if test "x$withval" = "xno"; then
		AC_MSG_ERROR([* * * huh? psiconv required for psion plugin! * * *])
	elif test "x$withval" != "xyes"; then
		CPPFLAGS="$CPPFLAGS -I$withval/include"
		LDFLAGS="$LDFLAGS -L$withval/lib"
	fi
])

AC_CHECK_HEADER(psiconv/parse.h,[
	AC_CHECK_LIB(psiconv,psiconv_file_type,[
		ABI_PLUGIN_REPORT([psion: okay])
	],[	ABI_PLUGIN_REPORT([psion: error - libpsiconv not found])
		abi_plugin_disable=yes
	])
],[	ABI_PLUGIN_REPORT([psion: error - psiconv headers not found])
	abi_plugin_disable=yes
])

if test $abi_plugin_disable = no; then
	ABI_PSION_CPPFLAGS="-I$withval/include"
	ABI_PSION_LDFLAGS="-L$withval/lib -lpsiconv"
fi

AC_SUBST(ABI_PSION_CPPFLAGS)
AC_SUBST(ABI_PSION_LDFLAGS)

CPPFLAGS="$_abi_cppflags_save"
LDFLAGS="$_abi_ldflags_save"
])
