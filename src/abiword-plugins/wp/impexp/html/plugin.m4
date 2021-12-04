dnl= ##########################################################################
dnl= # abiword-plugins: autogen.sh header
dnl= # this file is executed as a shell script
dnl= 
dnl= # 1. abi_plugin_macro is the name of the main macro defined here:
dnl= abi_plugin_macro="ABIPGN_HTML"
dnl= 
dnl= # 2. abi_plugin_files is the list of files that configure must generate:
dnl= abi_plugin_files="GNUmakefile xp/GNUmakefile"
dnl= 
dnl= # 3. abi_plugin_desc is a short description of the plugin
dnl= abi_plugin_desc="Plugin to enable import of arbitrary HTML documents"
dnl=
dnl= # 4. abi_plugin_enable - whether plugin should be enabled by default 
dnl= abi_plugin_enable="yes"
dnl=
dnl= return
dnl= ##########################################################################

AC_DEFUN([ABIPGN_HTML],[

_abi_cppflags_save="$CPPFLAGS"
_abi_ldflags_save="$LDFLAGS"

ABI_HTML_CPPFLAGS=""
ABI_HTML_LDFLAGS=""

# Checks for libraries.
# Checks for header files.

ABI_XML2_OPT(2.4.9,yes)
if [ test "$abi_xml2_opt" = "no" ]; then
	ABI_PLUGIN_REPORT([html: error - libxml2 >= 2.4.9 not found])
	abi_plugin_disable=yes
else
	ABI_PLUGIN_REPORT([html: okay])
fi

if test $abi_plugin_disable = no; then
	ABI_HTML_CPPFLAGS="`$abi_xml2_config --cflags` -DHAVE_LIBXML2"
	ABI_HTML_LDFLAGS="`$abi_xml2_config --libs`"
fi

AC_SUBST(ABI_HTML_CPPFLAGS)
AC_SUBST(ABI_HTML_LDFLAGS)

CPPFLAGS="$_abi_cppflags_save"
LDFLAGS="$_abi_ldflags_save"
])
