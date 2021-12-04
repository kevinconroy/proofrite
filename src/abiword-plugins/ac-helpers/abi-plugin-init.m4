AC_DEFUN([ABI_PLUGIN_INIT],[
	dnl Initialize variables:
	dnl 
	abi_plugin_major=""
	abi_plugin_minor=""
	abi_plugin_micro=""
	abi_plugin_source=""
	abi_plugin_target=""
	abi_plugin_version=""

	abi_plugin_topdir=`pwd`
	rm -f $abi_plugin_topdir/plugin.status

	dnl platform detection
	dnl 
	ABI_PLUGIN_PLATFORM

	dnl Set plugins version:
	dnl 
	if [ test "x$1" = "x" ]; then
		AC_MSG_ERROR([No AbiWord plugins version number!])
	fi
	abi_plugin_version="$1"
	abi_plugin_major=`echo $abi_plugin_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
	abi_plugin_minor=`echo $abi_plugin_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
	abi_plugin_micro=`echo $abi_plugin_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`
	abi_plugin_version="$abi_plugin_major.$abi_plugin_minor.$abi_plugin_micro"
	echo ""
	echo "Configuring AbiWord plugins for Version $abi_plugin_version"
	echo ""

	dnl Find the AbiWord sources:
	dnl 
	AC_MSG_CHECKING(for AbiWord source)
	AC_ARG_WITH(abiword,[  --with-abiword=DIR      AbiWord source is in DIR],[
		if [ test "x$withval" = "xno" ]; then
			AC_MSG_ERROR([* * * AbiWord sources are required for building plugins! * * *])
		elif [ test "x$withval" = "xyes" ]; then
			AC_MSG_WARN([* * * assuming peer directory for sources * * *])
		else
			if [ test -d "$withval" ]; then
				abi_plugin_source="$withval"
			else
				AC_MSG_ERROR("$withval is not a directory")
			fi
		fi
	],[	if test -d ../abi; then
			abi_plugin_source="../abi"
		else
			AC_MSG_ERROR([can't find AbiWord source in peer; use --with-abiword=DIR])
		fi
	])
	if [ test "x$abi_plugin_source" = "x" ]; then
		AC_MSG_ERROR([* * * unable to find AbiWord sources - which are required! * * *])
	else
		AC_MSG_RESULT($abi_plugin_source)
	fi
	case $abi_plugin_source in
	/* | ?:/*)
	  # absolute path
	  ;;
	*)
	  # relative path
	  abi_plugin_source="\$(top_builddir)/$abi_plugin_source"
	  ;;
	esac

	dnl Find AbiWord
	dnl
	if [ test "x$prefix" = "xNONE" ]; then
		AC_PATH_PROG(ABIWORD,AbiWord-2.0,,[$PATH])
		if [ test "x$ABIWORD" = "x" ]; then
			AC_MSG_ERROR([* * * Unable to find AbiWord-2.0 in path; please specify AbiSuite dir with --prefix * * *])
		else
			abi_plugin_target=`cat "$ABIWORD" | grep "^ABISUITE_HOME" | sed 's/ABISUITE_HOME=//'`
			if [ test "x$abi_plugin_target" = "x" ]; then
				AC_MSG_ERROR([* * * Unable to determine location of AbiSuite dir; please specify with --prefix * * *])
			fi
		fi
	else
		abi_plugin_target="$prefix"
	fi
	echo ""
	echo "Installing plugins in $abi_plugin_target/AbiWord/plugins"
	echo ""

	export abi_plugin_major
	export abi_plugin_minor
	export abi_plugin_micro
	export abi_plugin_source
	export abi_plugin_target
	export abi_plugin_version
	export abi_plugin_topdir

	dnl Finally, specify some options, even if they're irrelevant at the top level.
	dnl 
	AC_ARG_WITH(      bzip2,[  --with-bzip2=DIR        BZip2 library in DIR],,)
	AC_ARG_WITH(       glib,[  --with-glib=DIR         Use glib (v1.2) in DIR],,)
	AC_ARG_WITH(        gtk,[  --with-gtk=DIR          Use gtk+ (v1.2) in DIR],,)
	AC_ARG_WITH( gdk_pixbuf,[  --with-gdk-pixbuf=DIR   Use gdk-pixbuf in DIR],,)
	AC_ARG_WITH(      gnome,[  --with-gnome=DIR        Use gnome in DIR],,)
	AC_ARG_WITH(ImageMagick,[  --with-ImageMagick=DIR  Use ImageMagick in DIR],,)
	AC_ARG_WITH(    libxml2,[  --with-libxml2=DIR      Use libxml2 in DIR],,)

	AC_ARG_WITH(AbiWordExec,[  --with-AbiWordExec=PATH (only for Darwin with patched libtool)],,)

	AC_ARG_ENABLE(  bundles,[  --enable-bundles        Enable building of bundles (default: no)],,)
	AC_ARG_ENABLE(    debug,[  --enable-debug          Use debug settings (default: no)],,)
	AC_ARG_ENABLE( autoskip,[  --disable-autoskip      Crash and burn on failure],,)
])
