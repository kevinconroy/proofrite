dnl This is not plugin-specific.
dnl Namespaces are "abi_xml2_*" and "_abi_xml2_*"
dnl 
dnl Usage: 
dnl   ABI_XML2_OPT(<version>,<optional>) where <optional> = "no"|"yes"
dnl 
dnl Defines:
dnl   abi_xml2_opt=[yes|no|DIR]
dnl   abi_xml2_config  (if abi_xml2_opt != no)
dnl   abi_xml2_version (if abi_xml2_opt != no)
dnl 

# Check for optional libxml2

AC_DEFUN([ABI_XML2_OPT], [	
	abi_xml2_config=""
	abi_xml2_version=""
	if [ test "x$2" = "xyes" ]; then
		abi_xml2_opt=check
	else
		abi_xml2_opt=required
	fi
	AC_ARG_WITH(libxml2,[  --with-libxml2[=DIR]     Use libxml2 [in DIR] ],[
		if [ test "x$withval" = "xno" ]; then
			if [ test $abi_xml2_opt = required ]; then
				AC_MSG_ERROR([* * * libxml2 is not optional! * * *])
			fi
			abi_xml2_opt=no
		elif [ test "x$withval" = "xyes" ]; then
			abi_xml2_opt=required
			abi_xml2_dir=""
		else
			abi_xml2_opt=required
			abi_xml2_dir="$withval"
		fi
	],[	abi_xml2_dir=""
	])
	if [ test $abi_xml2_opt != no ]; then
		if [ test "x$abi_xml2_dir" = "x" ]; then
			AC_PATH_PROG(abi_xml2_config,xml2-config, ,[$PATH])
		else
			AC_PATH_PROG(abi_xml2_config,xml2-config, ,[$abi_xml2_dir/bin:$PATH])
		fi
		if [ test "x$abi_xml2_config" = "x" ]; then
			if [ test $abi_xml2_opt = required ]; then
				AC_MSG_ERROR([* * * unable to find xml2-config in path! * * *])
			fi
			abi_xml2_opt=no
		fi
	fi
	if [ test $abi_xml2_opt != no ]; then
	        if [ $abi_xml2_config --version > /dev/null 2>&1 ]; then
			_abi_xml2_version="$1"
			_abi_xml2_major=`echo $_abi_xml2_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
			_abi_xml2_minor=`echo $_abi_xml2_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
			_abi_xml2_micro=`echo $_abi_xml2_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`

			AC_MSG_CHECKING(for libxml2 >= $_abi_xml2_major.$_abi_xml2_minor.$_abi_xml2_micro)

			abi_xml2_version=`$abi_xml2_config --version`
			abi_xml2_major=`echo $abi_xml2_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
			abi_xml2_minor=`echo $abi_xml2_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
			abi_xml2_micro=`echo $abi_xml2_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`

			abi_xml2_version=""
			if [ test $abi_xml2_major -gt $_abi_xml2_major ]; then
				abi_xml2_version="$abi_xml2_major.$abi_xml2_minor.$abi_xml2_micro"
			elif [ test $abi_xml2_major -eq $_abi_xml2_major ]; then
				if [ test $abi_xml2_minor -gt $_abi_xml2_minor ]; then
					abi_xml2_version="$abi_xml2_major.$abi_xml2_minor.$abi_xml2_micro"
				elif [ test $abi_xml2_minor -eq $_abi_xml2_minor ]; then
					if [ test $abi_xml2_micro -ge $_abi_xml2_micro ]; then
						abi_xml2_version="$abi_xml2_major.$abi_xml2_minor.$abi_xml2_micro"
					fi
				fi
			fi
			if [ test "x$abi_xml2_version" = "x" ]; then
				if [ test $abi_xml2_opt = required ]; then
					AC_MSG_ERROR([* * * libxml2 version is incompatible! require at least "1.2.$1" * * *])
				fi
				abi_xml2_opt=no
				AC_MSG_RESULT(no - $abi_xml2_major.$abi_xml2_minor.$abi_xml2_micro)
			else
				AC_MSG_RESULT(yes - $abi_xml2_version)
			fi
		else
			AC_MSG_WARN([* * * problem obtaining libxml2 version... * * *])
			if [ test $abi_xml2_opt = required ]; then
				AC_MSG_ERROR([* * * unable to determine libxml2 version! * * *])
			fi
			abi_xml2_opt=no
		fi
	fi
	if [ test $abi_xml2_opt != no ]; then
		if [ test "x$abi_xml2_dir" = "x" ]; then
			abi_xml2_opt=yes
		else
			abi_xml2_opt="$abi_xml2_dir"
		fi
	fi
])
