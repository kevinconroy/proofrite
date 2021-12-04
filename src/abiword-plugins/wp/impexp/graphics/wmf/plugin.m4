dnl= ##########################################################################
dnl= # abiword-plugins: autogen.sh header
dnl= # this file is executed as a shell script
dnl= 
dnl= # 1. abi_plugin_macro is the name of the main macro defined here:
dnl= abi_plugin_macro="ABIPGN_WMF"
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

AC_DEFUN([ABIPGN_WMF],[

_abi_cppflags_save="$CPPFLAGS"
_abi_ldflags_save="$LDFLAGS"

ABI_WMF_CPPFLAGS=""
ABI_WMF_LDFLAGS=""

# Checks for libraries.
# Checks for header files.

ABI_LIBWMF_OPT(0.2.8,yes)
if [ test "$abi_libwmf_opt" = "no" ]; then
	ABI_PLUGIN_REPORT([wmf: error - libwmf >= 0.2.8 not found])
	abi_plugin_disable=yes
else
	ABI_PLUGIN_REPORT([wmf: okay])
fi

if test $abi_plugin_disable = no; then
	ABI_WMF_CPPFLAGS="`$abi_libwmf_config --cflags`"
	ABI_WMF_LDFLAGS="`$abi_libwmf_config --libs`"
fi

AC_SUBST(ABI_WMF_CPPFLAGS)
AC_SUBST(ABI_WMF_LDFLAGS)

CPPFLAGS="$_abi_cppflags_save"
LDFLAGS="$_abi_ldflags_save"
])

AC_DEFUN([ABI_LIBWMF_OPT],[
	abi_libwmf_config=""
	abi_libwmf_version=""
	if [ test "x$2" = "xyes" ]; then
		abi_libwmf_opt=check
	else
		abi_libwmf_opt=required
	fi
	AC_ARG_WITH(libwmf,[  --with-libwmf[=DIR]     Use libwmf [in DIR] ],[
		if [ test "x$withval" = "xno" ]; then
			if [ test $abi_libwmf_opt = required ]; then
				AC_MSG_ERROR([* * * libwmf is not optional! * * *])
			fi
			abi_libwmf_opt=no
		elif [ test "x$withval" = "xyes" ]; then
			abi_libwmf_opt=required
			abi_libwmf_dir=""
		else
			abi_libwmf_opt=required
			abi_libwmf_dir="$withval"
		fi
	],[	abi_libwmf_dir=""
	])
	if [ test $abi_libwmf_opt != no ]; then
		if [ test "x$abi_libwmf_dir" = "x" ]; then
			AC_PATH_PROG(abi_libwmf_config,libwmf-config, ,[$PATH])
		else
			AC_PATH_PROG(abi_libwmf_config,libwmf-config, ,[$abi_libwmf_dir/bin:$PATH])
		fi
		if [ test "x$abi_libwmf_config" = "x" ]; then
			if [ test $abi_libwmf_opt = required ]; then
				AC_MSG_ERROR([* * * unable to find libwmf-config in path! * * *])
			fi
			abi_libwmf_opt=no
		fi
	fi
	if [ test $abi_libwmf_opt != no ]; then
	        if [ $abi_libwmf_config --version > /dev/null 2>&1 ]; then
			_abi_libwmf_version="$1"
			_abi_libwmf_major=`echo $_abi_libwmf_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
			_abi_libwmf_minor=`echo $_abi_libwmf_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
			_abi_libwmf_micro=`echo $_abi_libwmf_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`

			AC_MSG_CHECKING(for libwmf >= $_abi_libwmf_major.$_abi_libwmf_minor.$_abi_libwmf_micro)

			abi_libwmf_version=`$abi_libwmf_config --version`
			abi_libwmf_major=`echo $abi_libwmf_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
			abi_libwmf_minor=`echo $abi_libwmf_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
			abi_libwmf_micro=`echo $abi_libwmf_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`

			abi_libwmf_version=""
			if [ test $abi_libwmf_major -gt $_abi_libwmf_major ]; then
				abi_libwmf_version="$abi_libwmf_major.$abi_libwmf_minor.$abi_libwmf_micro"
			elif [ test $abi_libwmf_major -eq $_abi_libwmf_major ]; then
				if [ test $abi_libwmf_minor -gt $_abi_libwmf_minor ]; then
					abi_libwmf_version="$abi_libwmf_major.$abi_libwmf_minor.$abi_libwmf_micro"
				elif [ test $abi_libwmf_minor -eq $_abi_libwmf_minor ]; then
					if [ test $abi_libwmf_micro -ge $_abi_libwmf_micro ]; then
						abi_libwmf_version="$abi_libwmf_major.$abi_libwmf_minor.$abi_libwmf_micro"
					fi
				fi
			fi
			if [ test "x$abi_libwmf_version" = "x" ]; then
				if [ test $abi_libwmf_opt = required ]; then
					AC_MSG_ERROR([* * * libwmf version is incompatible! require at least "1.2.$1" * * *])
				fi
				abi_libwmf_opt=no
				AC_MSG_RESULT(no - $abi_libwmf_major.$abi_libwmf_minor.$abi_libwmf_micro)
			else
				AC_MSG_RESULT(yes - $abi_libwmf_version)
			fi
		else
			AC_MSG_WARN([* * * problem obtaining libwmf version... * * *])
			if [ test $abi_libwmf_opt = required ]; then
				AC_MSG_ERROR([* * * unable to determine libwmf version! * * *])
			fi
			abi_libwmf_opt=no
		fi
	fi
	if [ test $abi_libwmf_opt != no ]; then
		if [ test "x$abi_libwmf_dir" = "x" ]; then
			abi_libwmf_opt=yes
		else
			abi_libwmf_opt="$abi_libwmf_dir"
		fi
	fi
])
