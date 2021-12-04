dnl This is not plugin-specific.
dnl Namespaces are "abi_gnome_*" and "_abi_gnome_*"
dnl 
dnl Usage: 
dnl   ABI_GNOME_OPT(<version>,<optional>) where <optional> = "no"|"yes"
dnl 
dnl Defines:
dnl   abi_gnome_opt=[yes|no|DIR]
dnl   abi_gnome_config  (if abi_gnome_opt != no)
dnl   abi_gnome_version (if abi_gnome_opt != no)
dnl 

# Check for optional gnome

AC_DEFUN([ABI_GNOME_OPT], [	
	abi_gnome_config=""
	abi_gnome_version=""
	if [ test "x$2" = "xyes" ]; then
		abi_gnome_opt=check
	else
		abi_gnome_opt=required
	fi
	AC_ARG_WITH(gnome,[  --with-gnome[=DIR]      Use gnome [in DIR] ],[
		if [ test "x$withval" = "xno" ]; then
			if [ test $abi_gnome_opt = required ]; then
				AC_MSG_ERROR([* * * gnome is not optional! * * *])
			fi
			abi_gnome_opt=no
		elif [ test "x$withval" = "xyes" ]; then
			abi_gnome_opt=required
			abi_gnome_dir=""
		else
			abi_gnome_opt=required
			abi_gnome_dir="$withval"
		fi
	],[	abi_gnome_dir=""
	])
	if [ test $abi_gnome_opt != no ]; then
		if [ test "x$abi_gnome_dir" = "x" ]; then
			AC_PATH_PROG(abi_gnome_config,gnome-config,,[$PATH])
		else
			AC_PATH_PROG(abi_gnome_config,gnome-config,,[$abi_gnome_dir/bin:$PATH])
		fi
		if [ test "x$abi_gnome_config" = "x" ]; then
			if [ test $abi_gnome_opt = required ]; then
				AC_MSG_ERROR([* * * unable to find gnome-config in path! * * *])
			fi
			abi_gnome_opt=no
		fi
	fi
	if [ test $abi_gnome_opt != no ]; then
	        if [ $abi_gnome_config --version > /dev/null 2>&1 ]; then
			_abi_gnome_version="$1"
			_abi_gnome_major=`echo $_abi_gnome_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
			_abi_gnome_minor=`echo $_abi_gnome_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
			_abi_gnome_micro=`echo $_abi_gnome_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`

			AC_MSG_CHECKING(for gnome >= $_abi_gnome_major.$_abi_gnome_minor.$_abi_gnome_micro)

			abi_gnome_version=`$abi_gnome_config --version | sed 's/gnome-libs //'`
			abi_gnome_major=`echo $abi_gnome_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
			abi_gnome_minor=`echo $abi_gnome_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
			abi_gnome_micro=`echo $abi_gnome_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`
			abi_gnome_point=`echo $abi_gnome_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\4/'`
			if test "$abi_gnome_point" = ""; then
				abi_gnome_micro=`echo $abi_gnome_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`
			fi

			abi_gnome_version=""
			if [ test $abi_gnome_major -gt $_abi_gnome_major ]; then
				abi_gnome_version="$abi_gnome_major.$abi_gnome_minor.$abi_gnome_micro"
			elif [ test $abi_gnome_major -eq $_abi_gnome_major ]; then
				if [ test $abi_gnome_minor -gt $_abi_gnome_minor ]; then
					abi_gnome_version="$abi_gnome_major.$abi_gnome_minor.$abi_gnome_micro"
				elif [ test $abi_gnome_minor -eq $_abi_gnome_minor ]; then
					if [ test $abi_gnome_micro -ge $_abi_gnome_micro ]; then
						abi_gnome_version="$abi_gnome_major.$abi_gnome_minor.$abi_gnome_micro"
					fi
				fi
			fi
			if [ test "x$abi_gnome_version" = "x" ]; then
				if [ test $abi_gnome_opt = required ]; then
					AC_MSG_ERROR([* * * gnome version is incompatible! require at least "1.2.$1" * * *])
				fi
				abi_gnome_opt=no
				AC_MSG_RESULT(no - $abi_gnome_major.$abi_gnome_minor.$abi_gnome_micro)
			else
				AC_MSG_RESULT(yes - $abi_gnome_version)
			fi
		else
			AC_MSG_WARN([* * * problem obtaining gnome version... * * *])
			if [ test $abi_gnome_opt = required ]; then
				AC_MSG_ERROR([* * * unable to determine gnome version! * * *])
			fi
			abi_gnome_opt=no
		fi
	fi
	if [ test $abi_gnome_opt != no ]; then
		if [ test "x$abi_gnome_dir" = "x" ]; then
			abi_gnome_opt=yes
		else
			abi_gnome_opt="$abi_gnome_dir"
		fi
	fi
])
