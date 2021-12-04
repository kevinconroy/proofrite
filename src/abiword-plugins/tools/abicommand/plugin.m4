dnl= ##########################################################################
dnl= # abiword-plugins: autogen.sh header
dnl= # this file is executed as a shell script
dnl= 
dnl= # 1. abi_plugin_macro is the name of the main macro defined here:
dnl= abi_plugin_macro="ABIPGN_ABICOMMAND"
dnl= 
dnl= # 2. abi_plugin_files is the list of files that configure must generate:
dnl= abi_plugin_files="GNUmakefile xp/GNUmakefile"
dnl= 
dnl= # 3. abi_plugin_desc is a short description of the plugin
dnl= abi_plugin_desc="Enables AbiWord to be used as a commanded daemon."
dnl= 
dnl= # 4. abi_plugin_enable - whether plugin should be enabled by default
dnl= abi_plugin_enable="yes"
dnl= 
dnl= return
dnl= ##########################################################################

AC_DEFUN([ABIPGN_ABICOMMAND],[

_abi_cppflags_save="$CPPFLAGS"
_abi_ldflags_save="$LDFLAGS"

ABI_COMMAND_CPPFLAGS=""
ABI_COMMAND_LDFLAGS=""

# Checks for libraries.
# Checks for header files.

have_readline=unknown
AC_CHECK_HEADER(readline/readline.h,[
	AC_CHECK_HEADER(readline/history.h,[
		AC_CHECK_LIB(readline,readline,[
			have_readline=yes
			LDFLAGS="-ltermcap $LDFLAGS"
			ABI_COMMAND_LDFLAGS="-ltermcap $ABI_COMMAND_LDFLAGS"
		],[	AC_CHECK_LIB(readline,rl_initialize,[
				have_readline=yes
				LDFLAGS="-lcurses $LDFLAGS"
				ABI_COMMAND_LDFLAGS="-lcurses $ABI_COMMAND_LDFLAGS"
			],have_readline=no,-lcurses)
		],-ltermcap)
	],have_readline=no)
],have_readline=no)

if [ test $have_readline != yes ]; then
	ABI_PLUGIN_REPORT([abicommand: error - readline libs or hdrs not found])
	abi_plugin_disable=yes

else
	ABI_COMMAND_LDFLAGS="-lreadline -lhistory $ABI_COMMAND_LDFLAGS"

	dnl only unix builds should need this stuff, so why...?
	PKG_CHECK_MODULES(_abi_gtk,gtk+-2.0 >= 2.0,[
		ABI_PLUGIN_REPORT([abicommand: okay])
	],[	ABI_PLUGIN_REPORT([abicommand: error - gtk+-2.0 >= 2.0 required])
		abi_plugin_disable=yes
	])
	if test $abi_plugin_disable = no; then
		ABI_COMMAND_CPPFLAGS="$ABI_COMMAND_LDFLAGS $_abi_gtk_CFLAGS"
		ABI_COMMAND_LDFLAGS="$ABI_COMMAND_LDFLAGS $_abi_gtk_LIBS"
	fi
fi

AC_SUBST(ABI_COMMAND_CPPFLAGS)
AC_SUBST(ABI_COMMAND_LDFLAGS)

CPPFLAGS="$_abi_cppflags_save"
LDFLAGS="$_abi_ldflags_save"
])
