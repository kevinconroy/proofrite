dnl= ##########################################################################
dnl= # abiword-plugins: autogen.sh header
dnl= # this file is executed as a shell script
dnl= 
dnl= # 1. abi_plugin_macro is the name of the main macro defined here:
dnl= abi_plugin_macro="ABIPGN_HANCOM"
dnl= 
dnl= # 2. abi_plugin_files is the list of files that configure must generate:
dnl= abi_plugin_files="GNUmakefile xp/GNUmakefile"
dnl= 
dnl= # 3. abi_plugin_desc is a short description of the plugin
dnl= abi_plugin_desc=""
dnl=
dnl= # 4. abi_plugin_enable - whether plugin should be enabled by default 
dnl= abi_plugin_enable="yes"
dnl=
dnl= return
dnl= ##########################################################################

AC_DEFUN([ABIPGN_HANCOM],[

_abi_cppflags_save="$CPPFLAGS"
_abi_ldflags_save="$LDFLAGS"

ABI_HANCOM_CPPFLAGS=""
ABI_HANCOM_LDFLAGS=""

# Checks for libraries.
# Checks for header files.

abi_wv_source="$abi_plugin_source/../wv"

ABI_HANCOM_CPPFLAGS="-I$abi_wv_source"

if test $abi_plugin_disable = no; then
	ABI_GLIB12_OPT(0,yes)
	if [ test "$abi_glib_opt" = "no" ]; then
		ABI_PLUGIN_REPORT([hancom: okay (using wv's mini glib)])
		ABI_HANCOM_CPPFLAGS="-I$abi_wv_source/glib-wv $ABI_HANCOM_CPPFLAGS"
	else
		ABI_PLUGIN_REPORT([hancom: okay (using glib)])
		ABI_HANCOM_CPPFLAGS="`$abi_glib_config --cflags` $ABI_HANCOM_CPPFLAGS"
		ABI_HANCOM_LDFLAGS="`$abi_glib_config --libs`"
	fi
fi

AC_SUBST(ABI_HANCOM_CPPFLAGS)
AC_SUBST(ABI_HANCOM_LDFLAGS)

CPPFLAGS="$_abi_cppflags_save"
LDFLAGS="$_abi_ldflags_save"
])
