dnl To be used by plugins' configure.in scripts.
dnl 
dnl ABI_PLUGIN_AUTOSKIP(<message>,<makefile>)
dnl 
dnl Reports <message> and fakes <makefile>

AC_DEFUN([ABI_PLUGIN_AUTOSKIP],[
	if [ test $abi_plugin_autoskip = yes ]; then
		ABI_PLUGIN_REPORT($1)
		if [ test "x$2" != "x" ]; then
			rm -f $2
			cat > $2 << EOF
all:	
	@echo "skipping..."

install:	
	@echo "skipping..."

EOF
		fi
		exit 0
	fi
	echo "$1"
	AC_MSG_ERROR(autoskip disabled)
])
