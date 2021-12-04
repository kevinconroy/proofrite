dnl= ##########################################################################
dnl= # abiword-plugins: autogen.sh header
dnl= # this file is executed as a shell script
dnl= 
dnl= # 1. abi_plugin_macro is the name of the main macro defined here:
dnl= abi_plugin_macro="ABIPGN_SDW"
dnl= 
dnl= # 2. abi_plugin_files is the list of files that configure must generate:
dnl= abi_plugin_files="GNUmakefile xp/GNUmakefile"
dnl= 
dnl= # 3. abi_plugin_desc is a short description of the plugin
dnl= abi_plugin_desc="Importer for StarWriter <= 5.x files (.sdw)"
dnl=
dnl= # 4. abi_plugin_enable - whether plugin should be enabled by default 
dnl= abi_plugin_enable="yes"
dnl=
dnl= return
dnl= ##########################################################################

AC_DEFUN([ABIPGN_SDW],[

_abi_cppflags_save="$CPPFLAGS"
_abi_ldflags_save="$LDFLAGS"

ABI_SDW_CPPFLAGS=""
ABI_SDW_LDFLAGS=""

# Checks for libraries.
# Checks for header files.

if test $abi_plugin_disable = no; then
	PKG_CHECK_MODULES(ABI_SDW, libgsf-1 >= 1.4.0,[
		ABI_SDW_CPPFLAGS="$ABI_SDW_CFLAGS"
		ABI_SDW_LDFLAGS="$ABI_SDW_LIBS"
		ABI_PLUGIN_REPORT([sdw: okay])
	],[	abi_plugin_disable=yes
		ABI_SDW_CPPFLAGS="$ABI_SDW_CFLAGS"
		ABI_SDW_LDFLAGS="$ABI_SDW_LIBS"
		ABI_PLUGIN_REPORT([sdw: error - libgsf-1 >= 1.4.0 required])
	])
fi

AC_SUBST(ABI_SDW_CPPFLAGS)
AC_SUBST(ABI_SDW_LDFLAGS)

CPPFLAGS="$_abi_cppflags_save"
LDFLAGS="$_abi_ldflags_save"
])
