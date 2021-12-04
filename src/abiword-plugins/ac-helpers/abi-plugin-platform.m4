# start: abiword-plugins/ac-helpers/abi-plugin-platform.m4
#
# Copyright (C) 2002 Francis James Franklin <fjf@alinameridon.com>
# Copyright (C) 2002 AbiSource, Inc.
# Copyright (C) 2001 Sam Tobin-Hochstadt
#
# This file is free software; you may copy and/or distribute it with
# or without modifications, as long as this notice is preserved.
# This software is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even
# the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
# PURPOSE.
#
# The above license applies to THIS FILE ONLY, the abiword code
# itself may be copied and distributed under the terms of the GNU
# GPL, see COPYING for more details
#
# This file detects which of the AbiWord platforms we are currently
# building on.  The detection logic in question is mostly by Jeff
# Hostetler, and is taken from the original AbiWord build system.  
#
# TODO Rewrite this to use $host, which is likely to be more accurate
# and actually maintained.

dnl To be used by plugins' configure.in scripts.
dnl 
dnl Defines:
dnl  abi_plugin_platform="unix"|"qnx"
dnl 

AC_DEFUN([ABI_PLUGIN_PLATFORM],[
	dnl these should probably be cleaned up a little... [TODO]
	dnl 
	OS_NAME=`uname -s | sed "s/\//-/" | sed "s/_/-/" | sed "s/-.*//g"`
	OS_RELEASE=`uname -r | sed "s/\//-/" | sed "s/[() ].*//g"`

	case $OS_NAME in
	QNX) abi_plugin_platform=qnx ;;
	*) abi_plugin_platform=unix ;;
	esac

	if test $abi_plugin_platform = qnx; then
		if test "x$CC" = "x"; then
			CC="qcc"
			export CC
		fi
		if test "x$CXX" = "x"; then
			if test "$OS_RELEASE" = "6.1.0"; then
				CXX="QCC -Vgcc_ntox86"
			else
				CXX="QCC -Vgcc_ntox86_gpp"
			fi
			export CXX
		fi
	fi
])

#
# end: abiword-plugins/ac-helpers/abi-plugin-platform.m4
