dnl= ##########################################################################
dnl= # abiword-plugins: autogen.sh header
dnl= # this file is executed as a shell script
dnl= 
dnl= # 1. abi_plugin_macro is the name of the main macro defined here:
dnl= abi_plugin_macro="ABIPGN_MAGICK"
dnl= 
dnl= # 2. abi_plugin_files is the list of files that configure must generate:
dnl= abi_plugin_files="GNUmakefile xp/GNUmakefile"
dnl= 
dnl= # 3. abi_plugin_desc is a short description of the plugin
dnl= abi_plugin_desc="Plugin to allow abiword to use imagemagick."
dnl=
dnl= # 4. abi_plugin_enable - whether plugin should be enabled by default 
dnl= abi_plugin_enable="yes"
dnl=
dnl= return
dnl= ##########################################################################

AC_DEFUN([ABIPGN_MAGICK],[

_abi_cppflags_save="$CPPFLAGS"
_abi_ldflags_save="$LDFLAGS"

ABI_MAGICK_CPPFLAGS=""
ABI_MAGICK_LDFLAGS=""

# Checks for libraries.
# Checks for header files.

ABI_MAGICKPP_OPT(5.4.0,yes)
if [ test "$abi_magickpp_opt" = "no" ]; then
        ABI_PLUGIN_REPORT([magick: error - Magick++ >= 5.4.0 not found])
	abi_plugin_disable=yes
else
	ABI_PLUGIN_REPORT([magick: okay])
fi

if test $abi_plugin_disable = no; then
	ABI_MAGICK_CPPFLAGS="`$abi_magickpp_config --cppflags`"
	ABI_MAGICK_LDFLAGS="`$abi_magickpp_config --ldflags` `$abi_magickpp_config --libs`"
fi

AC_SUBST(ABI_MAGICK_CPPFLAGS)
AC_SUBST(ABI_MAGICK_LDFLAGS)

CPPFLAGS="$_abi_cppflags_save"
LDFLAGS="$_abi_ldflags_save"
])
