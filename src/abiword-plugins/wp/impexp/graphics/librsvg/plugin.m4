dnl= ##########################################################################
dnl= # abiword-plugins: autogen.sh header
dnl= # this file is executed as a shell script
dnl= 
dnl= # 1. abi_plugin_macro is the name of the main macro defined here:
dnl= abi_plugin_macro="ABIPGN_LIBRSVG"
dnl= 
dnl= # 2. abi_plugin_files is the list of files that configure must generate:
dnl= abi_plugin_files="GNUmakefile unix/GNUmakefile"
dnl= 
dnl= # 3. abi_plugin_desc is a short description of the plugin
dnl= abi_plugin_desc="Plugin to allow abiword to import several image types with gdk-pixbuf"
dnl=
dnl= # 4. abi_plugin_enable - whether plugin should be enabled by default 
dnl= abi_plugin_enable="yes"
dnl=
dnl= return
dnl= ##########################################################################

AC_DEFUN([ABIPGN_LIBRSVG],[

_abi_cppflags_save="$CPPFLAGS"
_abi_ldflags_save="$LDFLAGS"

LIBRSVG_CPPFLAGS=""
LIBRSVG_LDFLAGS=""

# Checks for libraries.
# Checks for header files.

PKG_CHECK_MODULES(_abi_librsvg,librsvg-2.0 >= 2.0,[
	ABI_PLUGIN_REPORT([LibRSVG: okay])
],[	ABI_PLUGIN_REPORT([LibRSVG: error - librsvg-2.0 >= 2.0 required])
	abi_plugin_disable=yes
])
if test $abi_plugin_disable = no; then
	LIBRSVG_CPPFLAGS="$_abi_librsvg_CFLAGS"
	LIBRSVG_LDFLAGS="$_abi_librsvg_LIBS"
fi

AC_SUBST(LIBRSVG_CPPFLAGS)
AC_SUBST(LIBRSVG_LDFLAGS)

CPPFLAGS="$_abi_cppflags_save"
LDFLAGS="$_abi_ldflags_save"
])
