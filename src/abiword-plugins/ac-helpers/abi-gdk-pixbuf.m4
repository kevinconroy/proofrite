dnl This is not plugin-specific.
dnl Namespaces are "abi_gdkpixbuf_*" and "_abi_gdkpixbuf_*"
dnl 
dnl Usage: 
dnl   ABI_GDKPIXBUF_OPT(<version>,<optional>) where <optional> = "no"|"yes"
dnl 
dnl Defines:
dnl   abi_gdkpixbuf_opt=[yes|no|DIR]
dnl   abi_gdkpixbuf_config  (if abi_gdkpixbuf_opt != no)
dnl   abi_gdkpixbuf_version (if abi_gdkpixbuf_opt != no)
dnl 

# Check for optional gdk-pixbuf

AC_DEFUN([ABI_GDKPIXBUF_OPT], [	
	abi_gdkpixbuf_config=""
	abi_gdkpixbuf_version=""
	if [ test "x$2" = "xyes" ]; then
		abi_gdkpixbuf_opt=check
	else
		abi_gdkpixbuf_opt=required
	fi
	AC_ARG_WITH(gdk_pixbuf,[  --with-gdk-pixbuf[=DIR]  Use gdk-pixbuf [in DIR] ],[
		if [ test "x$withval" = "xno" ]; then
			if [ test $abi_gdkpixbuf_opt = required ]; then
				AC_MSG_ERROR([* * * gdk-pixbuf is not optional! * * *])
			fi
			abi_gdkpixbuf_opt=no
		elif [ test "x$withval" = "xyes" ]; then
			abi_gdkpixbuf_opt=required
			abi_gdkpixbuf_dir=""
		else
			abi_gdkpixbuf_opt=required
			abi_gdkpixbuf_dir="$withval"
		fi
	],[	abi_gdkpixbuf_dir=""
	])
	if [ test $abi_gdkpixbuf_opt != no ]; then
		if [ test "x$abi_gdkpixbuf_dir" = "x" ]; then
			AC_PATH_PROG(abi_gdkpixbuf_config,gdk-pixbuf-config, ,[$PATH])
		else
			AC_PATH_PROG(abi_gdkpixbuf_config,gdk-pixbuf-config, ,[$abi_gdkpixbuf_dir/bin:$PATH])
		fi
		if [ test "x$abi_gdkpixbuf_config" = "x" ]; then
			if [ test $abi_gdkpixbuf_opt = required ]; then
				AC_MSG_ERROR([* * * unable to find gdk-pixbuf-config in path! * * *])
			fi
			abi_gdkpixbuf_opt=no
		fi
	fi
	if [ test $abi_gdkpixbuf_opt != no ]; then
	        if [ $abi_gdkpixbuf_config --version > /dev/null 2>&1 ]; then
			_abi_gdkpixbuf_version="$1"
			_abi_gdkpixbuf_major=`echo $_abi_gdkpixbuf_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
			_abi_gdkpixbuf_minor=`echo $_abi_gdkpixbuf_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
			_abi_gdkpixbuf_micro=`echo $_abi_gdkpixbuf_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`

			AC_MSG_CHECKING(for gdk-pixbuf >= $_abi_gdkpixbuf_major.$_abi_gdkpixbuf_minor.$_abi_gdkpixbuf_micro)

			abi_gdkpixbuf_version=`$abi_gdkpixbuf_config --version`
			abi_gdkpixbuf_major=`echo $abi_gdkpixbuf_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
			abi_gdkpixbuf_minor=`echo $abi_gdkpixbuf_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
			abi_gdkpixbuf_micro=`echo $abi_gdkpixbuf_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`

			abi_gdkpixbuf_version=""
			if [ test $abi_gdkpixbuf_major -gt $_abi_gdkpixbuf_major ]; then
				abi_gdkpixbuf_version="$abi_gdkpixbuf_major.$abi_gdkpixbuf_minor.$abi_gdkpixbuf_micro"
			elif [ test $abi_gdkpixbuf_major -eq $_abi_gdkpixbuf_major ]; then
				if [ test $abi_gdkpixbuf_minor -gt $_abi_gdkpixbuf_minor ]; then
					abi_gdkpixbuf_version="$abi_gdkpixbuf_major.$abi_gdkpixbuf_minor.$abi_gdkpixbuf_micro"
				elif [ test $abi_gdkpixbuf_minor -eq $_abi_gdkpixbuf_minor ]; then
					if [ test $abi_gdkpixbuf_micro -ge $_abi_gdkpixbuf_micro ]; then
						abi_gdkpixbuf_version="$abi_gdkpixbuf_major.$abi_gdkpixbuf_minor.$abi_gdkpixbuf_micro"
					fi
				fi
			fi
			if [ test "x$abi_gdkpixbuf_version" = "x" ]; then
				if [ test $abi_gdkpixbuf_opt = required ]; then
					AC_MSG_ERROR([* * * gdk-pixbuf version is incompatible! require at least "1.2.$1" * * *])
				fi
				abi_gdkpixbuf_opt=no
				AC_MSG_RESULT(no - $abi_gdkpixbuf_major.$abi_gdkpixbuf_minor.$abi_gdkpixbuf_micro)
			else
				AC_MSG_RESULT(yes - $abi_gdkpixbuf_version)
			fi
		else
			AC_MSG_WARN([* * * problem obtaining gdk-pixbuf version... * * *])
			if [ test $abi_gdkpixbuf_opt = required ]; then
				AC_MSG_ERROR([* * * unable to determine gdk-pixbuf version! * * *])
			fi
			abi_gdkpixbuf_opt=no
		fi
	fi
	if [ test $abi_gdkpixbuf_opt != no ]; then
		if [ test "x$abi_gdkpixbuf_dir" = "x" ]; then
			abi_gdkpixbuf_opt=yes
		else
			abi_gdkpixbuf_opt="$abi_gdkpixbuf_dir"
		fi
	fi
])
