dnl This is not plugin-specific. Namespaces are "abi_bzip2_*" and "_abi_bzip2_*"
dnl 
dnl Usage: 
dnl   ABI_BZIP2_OPT(<optional>) where <optional> = "no"|"yes"
dnl 
dnl Defines:
dnl   abi_bzip2_opt=[yes|no|DIR]
dnl   abi_bzip2_cppflags
dnl   abi_bzip2_ldflags
dnl   abi_bzip2_libs
dnl 

# Check for optional bzip2

AC_DEFUN([ABI_BZIP2_OPT], [
	abi_bzip2_dir=""
	abi_bzip2_cppflags=""
	abi_bzip2_ldflags=""
	abi_bzip2_libs=""
	if [ test "x$1" = "xno" ]; then
		abi_bzip2_opt=required
	else
		abi_bzip2_opt=check
	fi
	
	AC_ARG_WITH(bzip2,[  --with-bzip2=DIR        BZip2 library in DIR],[
		if [ test "x$withval" = "xno" ]; then
			if [ test $abi_bzip2_opt = required ]; then
				AC_MSG_ERROR([* * * BZip2 library required to build this plugin * * *])
			fi
			abi_bzip2_opt=no
		elif [ test "x$withval" = "xyes" ]; then
			abi_bzip2_opt=required
		else
			abi_bzip2_opt=required
			abi_bzip2_dir="$withval"
			abi_bzip2_cppflags="-I$withval/include"
			abi_bzip2_ldflags="-L$withval/lib"
		fi
	])
	if [ test $abi_bzip2_opt != no ]; then
		_abi_bzip2_cppflags="$CPPFLAGS"
		_abi_bzip2_ldflags="$LDFLAGS"

		CPPFLAGS="$CPPFLAGS $abi_bzip2_cppflags"
		LDFLAGS="$LDFLAGS $abi_bzip2_ldflags"

		AC_CHECK_HEADER(bzlib.h,[
			AC_CHECK_LIB(bz2,BZ2_bzWrite,,[
				if [ test $abi_bzip2_opt = required ]; then
					AC_MSG_ERROR([* * * BZip2 library required to build this plugin * * *])
				fi
				AC_MSG_WARN([* * * Proceeding w/o bzip2 * * *])
				abi_bzip2_opt=no
			])
		],[	if [ test $abi_bzip2_opt = required ]; then
				AC_MSG_ERROR([* * * BZip2 library required to build this plugin * * *])
			fi
			abi_bzip2_opt=no
		])

		CPPFLAGS="$_abi_bzip2_cppflags"
		LDFLAGS="$_abi_bzip2_ldflags"
	fi
	if [ test $abi_bzip2_opt != no ]; then
		if [ test "x$abi_bzip2_dir" = "x" ]; then
			abi_bzip2_opt=yes
		else
			abi_bzip2_opt="$abi_bzip2_dir"
		fi
		abi_bzip2_libs="-lbz2"
	fi
])
