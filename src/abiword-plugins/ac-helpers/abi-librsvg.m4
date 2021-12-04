dnl This is not plugin-specific.
dnl Namespaces are "abi_librsvg_*" and "_abi_librsvg_*"
dnl 
dnl Usage: 
dnl   ABI_LIBRSVG_OPT(<version>,<optional>) where <optional> = "no"|"yes"
dnl 
dnl Defines:
dnl   abi_librsvg_opt=[yes|no|DIR]
dnl   abi_librsvg_config  (if abi_librsvg_opt != no)
dnl   abi_librsvg_version (if abi_librsvg_opt != no)
dnl 

# Check for optional librsvg-2.0

AC_DEFUN([ABI_LIBRSVG_OPT], [	
	abi_librsvg_config=""
	abi_librsvg_version=""
	if [ test "x$2" = "xyes" ]; then
		abi_librsvg_opt=check
	else
		abi_librsvg_opt=required
	fi
	AC_ARG_WITH(librsvg,[  --with-librsvg[=DIR]  Use librsvg [in DIR] ],[
		if [ test "x$withval" = "xno" ]; then
			if [ test $abi_librsvg_opt = required ]; then
				AC_MSG_ERROR([* * * librsvg is not optional! * * *])
			fi
			abi_librsvg_opt=no
		elif [ test "x$withval" = "xyes" ]; then
			abi_librsvg_opt=required
			abi_librsvg_dir=""
		else
			abi_librsvg_opt=required
			abi_librsvg_dir="$withval"
		fi
	],[	abi_librsvg_dir=""
	])
	if [ test $abi_librsvg_opt != no ]; then
		if [ test "x$abi_librsvg_dir" = "x" ]; then
			AC_PATH_PROG(abi_librsvg_config,librsvg-config, ,[$PATH])
		else
			AC_PATH_PROG(abi_librsvg_config,librsvg-config, ,[$abi_librsvg_dir/bin:$PATH])
		fi
		if [ test "x$abi_librsvg_config" = "x" ]; then
			if [ test $abi_librsvg_opt = required ]; then
				AC_MSG_ERROR([* * * unable to find librsvg-config in path! * * *])
			fi
			abi_librsvg_opt=no
		fi
	fi
	if [ test $abi_librsvg_opt != no ]; then
	        if [ $abi_librsvg_config --version > /dev/null 2>&1 ]; then
			_abi_librsvg_version="$1"
			_abi_librsvg_major=`echo $_abi_librsvg_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
			_abi_librsvg_minor=`echo $_abi_librsvg_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
			_abi_librsvg_micro=`echo $_abi_librsvg_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`

			AC_MSG_CHECKING(for librsvg >= $_abi_librsvg_major.$_abi_librsvg_minor.$_abi_librsvg_micro)

			abi_librsvg_version=`$abi_librsvg_config --version`
			abi_librsvg_major=`echo $abi_librsvg_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
			abi_librsvg_minor=`echo $abi_librsvg_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
			abi_librsvg_micro=`echo $abi_librsvg_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`

			abi_librsvg_version=""
			if [ test $abi_librsvg_major -gt $_abi_librsvg_major ]; then
				abi_librsvg_version="$abi_librsvg_major.$abi_librsvg_minor.$abi_librsvg_micro"
			elif [ test $abi_librsvg_major -eq $_abi_librsvg_major ]; then
				if [ test $abi_librsvg_minor -gt $_abi_librsvg_minor ]; then
					abi_librsvg_version="$abi_librsvg_major.$abi_librsvg_minor.$abi_librsvg_micro"
				elif [ test $abi_librsvg_minor -eq $_abi_librsvg_minor ]; then
					if [ test $abi_librsvg_micro -ge $_abi_librsvg_micro ]; then
						abi_librsvg_version="$abi_librsvg_major.$abi_librsvg_minor.$abi_librsvg_micro"
					fi
				fi
			fi
			if [ test "x$abi_librsvg_version" = "x" ]; then
				if [ test $abi_librsvg_opt = required ]; then
					AC_MSG_ERROR([* * * librsvg version is incompatible! require at least "1.2.$1" * * *])
				fi
				abi_librsvg_opt=no
				AC_MSG_RESULT(no - $abi_librsvg_major.$abi_librsvg_minor.$abi_librsvg_micro)
			else
				AC_MSG_RESULT(yes - $abi_librsvg_version)
			fi
		else
			AC_MSG_WARN([* * * problem obtaining librsvg version... * * *])
			if [ test $abi_librsvg_opt = required ]; then
				AC_MSG_ERROR([* * * unable to determine librsvg version! * * *])
			fi
			abi_librsvg_opt=no
		fi
	fi
	if [ test $abi_librsvg_opt != no ]; then
		if [ test "x$abi_librsvg_dir" = "x" ]; then
			abi_librsvg_opt=yes
		else
			abi_librsvg_opt="$abi_librsvg_dir"
		fi
	fi
])
