dnl= ##########################################################################
dnl= # abiword-plugins: autogen.sh header
dnl= # this file is executed as a shell script
dnl= 
dnl= # 1. abi_plugin_macro is the name of the main macro defined here:
dnl= abi_plugin_macro="ABIPGN_GDICT"
dnl= 
dnl= # 2. abi_plugin_files is the list of files that configure must generate:
dnl= abi_plugin_files="GNUmakefile unix/GNUmakefile"
dnl= 
dnl= # 3. abi_plugin_desc is a short description of the plugin
dnl= abi_plugin_desc="Plugin to allow abiword to use gdict"
dnl=
dnl= # 4. abi_plugin_enable - whether plugin should be enabled by default 
dnl= abi_plugin_enable="no"
dnl=
dnl= return
dnl= ##########################################################################

AC_DEFUN([ABIPGN_GDICT],[

_abi_cppflags_save="$CPPFLAGS"
_abi_ldflags_save="$LDFLAGS"

ABI_GDICT_CPPFLAGS=""
ABI_GDICT_LDFLAGS=""

# Checks for libraries.
# Checks for header files.

# ABI_GNOME_OPT(1.2.13,yes)
# if [ test $abi_gnome_opt = no ]; then

dnl only unix builds should need this stuff, so why...?
PKG_CHECK_MODULES(_abi_gtk,gtk+-2.0 >= 2.0,[
	ABI_PLUGIN_REPORT([gdict: okay (no GNOME; using fork-and-exec method)])
],[	ABI_PLUGIN_REPORT([gdict: error - gtk+-2.0 >= 2.0 required])
	abi_plugin_disable=yes
])
if test $abi_plugin_disable = no; then
	ABI_GDICT_CPPFLAGS="$_abi_gtk_CFLAGS -DUSE_FORK_AND_EXEC_METHOD=1"
	ABI_GDICT_LDFLAGS="$_abi_gtk_LIBS"
fi

# else
# 	ABI_GDICT_CPPFLAGS="`$abi_gnome_config --cflags gnomeui gtk glib`"
# 	ABI_GDICT_LDFLAGS="`$abi_gnome_config --libs gnomeui gtk glib`"
# 
# 	CPPFLAGS="$CPPFLAGS $ABI_GDICT_CPPFLAGS"
# 	LDFLAGS="$LDFLAGS $ABI_GDICT_LDFLAGS"
# 
# 	have_libgdict=yes
# 	AC_CHECK_HEADER(libgdict/gdict-defbox.h,[
# 		AC_CHECK_LIB(gdict,gdict_defbox_lookup,have_libgdict=yes,[
# 			have_libgdict=no
# 			AC_MSG_WARN([* * * can't link against libgdict * * *])
# 		],$ABI_GDICT_LDFLAGS)
# 	],[	AC_MSG_WARN([* * * libgdict doesn't appear to be installed * * *])
# 		have_libgdict=no
# 	])
# 
# 	if [ test $have_libgdict = no ]; then
# 		ABI_GTK12(0)
# 		ABI_GDICT_CPPFLAGS="`$abi_gtk_config --cflags` -DUSE_FORK_AND_EXEC_METHOD=1"
# 		ABI_GDICT_LDFLAGS="`$abi_gtk_config --libs`"
# 		ABI_PLUGIN_REPORT([gdict: okay (falling back to fork-and-exec method)])
# 	else
# 		ABI_GDICT_LDFLAGS="-lgdict $ABI_GDICT_LDFLAGS"
# 		ABI_PLUGIN_REPORT([gdict: okay (using libgdict)])
# 	fi
# fi

AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS([unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_PID_T

# Checks for library functions.

AC_SUBST(ABI_GDICT_CPPFLAGS)
AC_SUBST(ABI_GDICT_LDFLAGS)

CPPFLAGS="$_abi_cppflags_save"
LDFLAGS="$_abi_ldflags_save"
])
