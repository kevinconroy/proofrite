dnl= ##########################################################################
dnl= # abiword-plugins: autogen.sh header
dnl= # this file is executed as a shell script
dnl= 
dnl= # 1. abi_plugin_macro is the name of the main macro defined here:
dnl= abi_plugin_macro="ABIPGN_GDA"
dnl= 
dnl= # 2. abi_plugin_files is the list of files that configure must generate:
dnl= abi_plugin_files="GNUmakefile unix/GNUmakefile"
dnl= 
dnl= # 3. abi_plugin_desc is a short description of the plugin
dnl= abi_plugin_desc="Plugin to allow abiword to use gda"
dnl=
dnl= # 4. abi_plugin_enable - whether plugin should be enabled by default 
dnl= abi_plugin_enable="no"
dnl=
dnl= return
dnl= ##########################################################################

AC_DEFUN([ABIPGN_GDA],[

_abi_cppflags_save="$CPPFLAGS"
_abi_ldflags_save="$LDFLAGS"

ABI_GDA_CPPFLAGS=""
ABI_GDA_LDFLAGS=""

# Checks for libraries.
# Checks for header files.

dnl only unix builds should need this stuff, so why...?
PKG_CHECK_MODULES(_abi_gda,[libgda >= 0.9 libgnomedb >= 0.9],[
	ABI_PLUGIN_REPORT([gda: okay])
],[	ABI_PLUGIN_REPORT([gda: error - libgda and libgnomedb >= 0.9 required])
	abi_plugin_disable=yes
])
if test $abi_plugin_disable = no; then
	ABI_GDA_CPPFLAGS="$_abi_gda_CFLAGS"
	ABI_GDA_LDFLAGS="$_abi_gda_LIBS"
fi

AC_SUBST(ABI_GDA_CPPFLAGS)
AC_SUBST(ABI_GDA_LDFLAGS)

CPPFLAGS="$_abi_cppflags_save"
LDFLAGS="$_abi_ldflags_save"
])
