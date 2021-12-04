dnl= ##########################################################################
dnl= # abiword-plugins: autogen.sh header
dnl= # this file is executed as a shell script
dnl= 
dnl= # 1. abi_plugin_macro is the name of the main macro defined here:
dnl= abi_plugin_macro="ABIPGN_BZ2ABW"
dnl= 
dnl= # 2. abi_plugin_files is the list of files that configure must generate:
dnl= abi_plugin_files="GNUmakefile xp/GNUmakefile"
dnl= 
dnl= # 3. abi_plugin_desc is a short description of the plugin
dnl= abi_plugin_desc="Plugin to allow abiword documents compressed with bzip2"
dnl=
dnl= # 4. abi_plugin_enable - whether plugin should be enabled by default 
dnl= abi_plugin_enable="yes"
dnl=
dnl= return
dnl= ##########################################################################

AC_DEFUN([ABIPGN_BZ2ABW],[

_abi_cppflags_save="$CPPFLAGS"
_abi_ldflags_save="$LDFLAGS"

BZ2ABW_CPPFLAGS=""
BZ2ABW_LDFLAGS=""

# Checks for libraries.
# Checks for header files.

ABI_BZIP2_OPT(yes)
if [ test "$abi_bzip2_opt" = "no" ]; then
        ABI_PLUGIN_REPORT([bz2abw: error - libbz2 not found])
	abi_plugin_disable=yes
else
	ABI_PLUGIN_REPORT([bz2abw: okay])
fi

if test $abi_plugin_disable = no; then
	BZ2ABW_CPPFLAGS="$abi_bzip2_cppflags"
	BZ2ABW_LDFLAGS="$abi_bzip2_ldflags $abi_bzip2_libs"
fi

AC_SUBST(BZ2ABW_CPPFLAGS)
AC_SUBST(BZ2ABW_LDFLAGS)

CPPFLAGS="$_abi_cppflags_save"
LDFLAGS="$_abi_ldflags_save"
])
