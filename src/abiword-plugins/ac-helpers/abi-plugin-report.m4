dnl ABI_PLUGIN_REPORT(<message>)
dnl 

AC_DEFUN([ABI_PLUGIN_REPORT],[
	if [ test "x$1" != "x" ]; then
		echo "$1" >> $abi_plugin_topdir/plugin.status
	fi
])
