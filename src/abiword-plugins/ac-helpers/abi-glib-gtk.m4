dnl This is not plugin-specific. Namespaces are "abi_glib_*", "abi_gtk_*"
dnl 
dnl Usage: 
dnl   ABI_GLIB12_OPT(<micro-version>,<optional>) where <optional> = "no"|"yes"
dnl   ABI_GTK12(<micro-version>)
dnl 
dnl Defines:
dnl   abi_glib_opt=[yes|no|DIR]
dnl   abi_glib_config (if abi_glib_opt != no)
dnl   abi_gtk_config
dnl 

# Check for optional glib

AC_DEFUN([ABI_GLIB12_OPT], [	
	abi_glib_config=""
	if [ test "x$2" = "xyes" ]; then
		abi_glib_opt=check
	else
		abi_glib_opt=required
	fi
	AC_ARG_WITH(glib,[  --with-glib[=DIR]  Use glib (v1.2) [in DIR] ],[
		if [ test "x$withval" = "xno" ]; then
			if [ test $abi_glib_opt = required ]; then
				AC_MSG_ERROR([* * * glib-1.2 is not optional! * * *])
			fi
			abi_glib_opt=no
		elif [ test "x$withval" = "xyes" ]; then
			abi_glib_opt=required
			abi_glib_dir=""
		else
			abi_glib_opt=required
			abi_glib_dir="$withval"
		fi
	],[	abi_glib_dir=""
	])
	if [ test $abi_glib_opt != no ]; then
		if [ test "x$abi_glib_dir" = "x" ]; then
			AC_PATH_PROG(abi_glib_config,glib12-config, ,[$PATH])
		else
			AC_PATH_PROG(abi_glib_config,glib12-config, ,[$abi_glib_dir/bin:$PATH])
		fi
		if [ test "x$abi_glib_config" = "x" ]; then
			if [ test "x$abi_glib_dir" = "x" ]; then
				AC_PATH_PROG(abi_glib_config,glib-config, ,[$PATH])
			else
				AC_PATH_PROG(abi_glib_config,glib-config, ,[$abi_glib_dir/bin:$PATH])
			fi
		fi
		if [ test "x$abi_glib_config" = "x" ]; then
			if [ test $abi_glib_opt = required ]; then
				AC_MSG_ERROR([* * * unable to find glib12-config or glib-config in path! * * *])
			fi
			abi_glib_opt=no
		fi
	fi
	if [ test $abi_glib_opt != no ]; then
	        if [ $abi_glib_config --version > /dev/null 2>&1 ]; then
			abi_glib_opt_version=`$abi_glib_config --version`
			abi_glib_opt_major=`echo $abi_glib_opt_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
			abi_glib_opt_minor=`echo $abi_glib_opt_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
			abi_glib_opt_micro=`echo $abi_glib_opt_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`

			abi_glib_opt_version=""
			if [ test $abi_glib_opt_major -eq 1 ]; then
				if [ test $abi_glib_opt_minor -eq 2 ]; then
					if [ test $abi_glib_opt_micro -ge "$1" ]; then
						abi_glib_opt_version="1.2.$abi_glib_opt_micro"
					fi
				fi
			fi
			if [ test "x$abi_glib_opt_version" = "x" ]; then
				if [ test $abi_glib_opt = required ]; then
					AC_MSG_ERROR([* * * glib version is incompatible! require at least "1.2.$1" * * *])
				fi
				abi_glib_opt=no
			fi
		else
			AC_MSG_WARN([* * * problem obtaining glib version... * * *])
			if [ test $abi_glib_opt = required ]; then
				AC_MSG_ERROR([* * * unable to determine glib version! * * *])
			fi
			abi_glib_opt=no
		fi
	fi
	if [ test $abi_glib_opt != no ]; then
		if [ test "x$abi_glib_dir" = "x" ]; then
			abi_glib_opt=yes
		else
			abi_glib_opt="$abi_glib_dir"
		fi
	fi
])

# Check for required gtk+

AC_DEFUN([ABI_GTK12], [	
	abi_gtk_config=""
	AC_ARG_WITH(gtk,[  --with-gtk[=DIR]   Use gtk+ (v1.2) [in DIR] ],[
		if [ test "x$withval" = "xno" ]; then
			AC_MSG_ERROR([* * * gtk-1.2 is not optional! * * *])
		elif [ test "x$withval" = "xyes" ]; then
			abi_gtk_dir=""
		else
			abi_gtk_dir="$withval"
		fi
	],[	abi_gtk_dir=""
	])
	if [ test "x$abi_gtk_dir" = "x" ]; then
		AC_PATH_PROG(abi_gtk_config,gtk12-config, ,[$PATH])
	else
		AC_PATH_PROG(abi_gtk_config,gtk12-config, ,[$abi_gtk_dir/bin:$PATH])
	fi
	if [ test "x$abi_gtk_config" = "x" ]; then
		if [ test "x$abi_gtk_dir" = "x" ]; then
			AC_PATH_PROG(abi_gtk_config,gtk-config, ,[$PATH])
		else
			AC_PATH_PROG(abi_gtk_config,gtk-config, ,[$abi_gtk_dir/bin:$PATH])
		fi
	fi
	if [ test "x$abi_gtk_config" = "x" ]; then
		AC_MSG_ERROR([* * * unable to find gtk12-config or gtk-config in path! * * *])
	fi
        if [ $abi_gtk_config --version > /dev/null 2>&1 ]; then
		abi_gtk_version=`$abi_gtk_config --version`
		abi_gtk_major=`echo $abi_gtk_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
		abi_gtk_minor=`echo $abi_gtk_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
		abi_gtk_micro=`echo $abi_gtk_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`

		abi_gtk_version=""
		if [ test $abi_gtk_major -eq 1 ]; then
			if [ test $abi_gtk_minor -eq 2 ]; then
				if [ test $abi_gtk_micro -ge "$1" ]; then
					abi_gtk_version="1.2.$abi_gtk_micro"
				fi
			fi
		fi
		if [ test "x$abi_gtk_version" = "x" ]; then
			AC_MSG_ERROR([* * * gtk version is incompatible! require at least "1.2.$1" * * *])
		fi
	else
		AC_MSG_ERROR([* * * unable to determine gtk version! * * *])
	fi
])
