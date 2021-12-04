dnl To be used by plugins' configure.in scripts.
dnl Defines substitution @ABI_CPPFLAGS@
dnl Defines substitution @ABI_LIBS@
dnl Defines substitution @ABI_PLUGIN_DIR@
dnl 
dnl Defines:
dnl  ABI_PLUGIN_SOURCE
dnl  ABI_PLUGIN_VERSION - e.g., "0.9.5" (string)
dnl  ABI_PLUGIN_MAJOR   - e.g., 0       (int)
dnl  ABI_PLUGIN_MINOR   - e.g., 9       (int)
dnl  ABI_PLUGIN_MICRO   - e.g., 5       (int)
dnl 
dnl  abi_plugin_bundle="yes"|"no"
dnl  abi_plugin_debug="yes"|"no"
dnl  abi_plugin_autoskip="yes"|"no"
dnl  abi_plugin_specified="yes"|"no"
dnl 

AC_DEFUN([ABI_PLUGIN_SETUP],[
	dnl exit cleanly and quietly here and now if disabled
	dnl this is a hack to get around hard-coding in autoconf-2.13
	dnl 
	abi_plugin_default=yes
	AC_ARG_ENABLE(all,  --disable-all,[
		if test "x$enableval" = "xno"; then
			abi_plugin_default=no
		fi
	])
	abi_plugin_specified=no
	AC_ARG_ENABLE($1,  --disable-$1,[
		if test "x$enableval" = "xno"; then
			exit 0
		fi
		abi_plugin_specified=yes
	],[	if test $abi_plugin_default = no; then
			exit 0
		fi
	])

	dnl see below
	dnl 
	ABI_PLUGIN_CONFIG

	dnl if autoskip is enabled (the default), plugins have the option to self-disable
	dnl 
	abi_plugin_autoskip=yes
	AC_ARG_ENABLE( autoskip,[  --disable-autoskip      Crash and burn on failure],[
		if [ test "x$enableval" != "xno" ]; then
			abi_plugin_autoskip=no
		fi
	])
])

AC_DEFUN([ABI_PLUGIN_CONFIG],[
	dnl platform detection
	dnl 
	ABI_PLUGIN_PLATFORM

	dnl whether to build bundles - experimental feature: default is no
	dnl 
	abi_plugin_bundle=no
	AC_ARG_ENABLE(bundles,  --enable-bundles,[
		if test "x$enableval" != "xno"; then
			abi_plugin_bundle=yes
		fi
	])

	dnl C preprocessor defines: Debug settings
	dnl 
	abi_plugin_debug=no
	AC_ARG_ENABLE(debug,[  --enable-debug          Use debug settings (default: no)],[
		if [ test "x$enableval" != "xno" ]; then
			abi_plugin_debug=yes
		fi
	])
	if [ test $abi_plugin_debug = yes ]; then
		ABI_CPPFLAGS="-DDEBUG -DUT_DEBUG"
	else
		ABI_CPPFLAGS="-DNDEBUG"
	fi

	dnl Other C preprocessor defines and include path to AbiWord sources
	dnl 
	abi_includes_xp="af/util/xp af/xap/xp af/ev/xp af/gr/xp text/fmt/xp text/ptbl/xp wp/impexp/xp wp/ap/xp other/spell/xp other/fribidi/xp"
	if test $abi_plugin_platform = unix; then
		abi_includes_unix="af/util/unix af/xap/unix wp/ap/unix"
		abi_includes="$abi_includes_xp $abi_includes_unix"
	elif test $abi_plugin_platform = qnx; then
		abi_includes_qnx="af/util/qnx af/xap/qnx wp/ap/qnx"
		abi_includes="$abi_includes_xp $abi_includes_qnx"
	fi
	ABI_INCLUDES=""
	for i in $abi_includes; do
		ABI_INCLUDES="$ABI_INCLUDES -I$abi_plugin_source/src/$i"
	done

	ABI_CPPFLAGS="$ABI_CPPFLAGS $ABI_INCLUDES -DABI_PLUGIN_VERSION=\\\"$abi_plugin_version\\\" -DABI_PLUGIN_MAJOR=$abi_plugin_major -DABI_PLUGIN_MINOR=$abi_plugin_minor -DABI_PLUGIN_MICRO=$abi_plugin_micro -DABI_PLUGIN_SOURCE=1"
	AC_SUBST(ABI_CPPFLAGS)

	dnl On Darwin, plugins need to be linked against the AbiWord executable
	dnl 
	AC_ARG_WITH(AbiWordExec,[  --with-AbiWordExec=PATH (only for Darwin with patched libtool)],[
		if [ test "x$withval" = "xyes" ]; then
			AC_MSG_ERROR([  --with-AbiWordExec=PATH  please specify the AbiWord executable])
		elif [ test "x$withval" != "xno" ]; then
			DYLD_BUNDLE_LOADER($withval)
		fi
	])

	ABI_LIBS=""
	AC_SUBST(ABI_LIBS)

	dnl Installation directory for plugins
	dnl 
	ABI_PLUGIN_DIR="$abi_plugin_target/AbiWord/plugins"
	AC_SUBST(ABI_PLUGIN_DIR)
])
