dnl= ##########################################################################
dnl= # abiword-plugins: autogen.sh header
dnl= # this file is executed as a shell script
dnl= 
dnl= # 1. abi_plugin_macro is the name of the main macro defined here:
dnl= abi_plugin_macro="ABIPGN_JPEG"
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

AC_DEFUN([ABIPGN_JPEG],[

_abi_cppflags_save="$CPPFLAGS"
_abi_ldflags_save="$LDFLAGS"

ABI_JPEG_CPPFLAGS=""
ABI_JPEG_LDFLAGS=""

# Checks for libraries.
# Checks for header files.

AC_CHECK_HEADER(jpeglib.h,[
	AC_CHECK_LIB(jpeg,jpeg_read_header,[
		ABI_PLUGIN_REPORT([jpeg: okay])
	],[	ABI_PLUGIN_REPORT([jpeg: error - libjpeg not found])
		abi_plugin_disable=yes
	])
],[	ABI_PLUGIN_REPORT([jpeg: error - jpeg header not found])
	abi_plugin_disable=yes
])

if test $abi_plugin_disable = no; then
	ABI_JPEG_LDFLAGS="-ljpeg"
fi

AC_SUBST(ABI_JPEG_CPPFLAGS)
AC_SUBST(ABI_JPEG_LDFLAGS)

CPPFLAGS="$_abi_cppflags_save"
LDFLAGS="$_abi_ldflags_save"
])
