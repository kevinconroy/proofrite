#!/bin/sh
# Copyright (C) 2001-2002 Francis James Franklin <fjf@alinameridon.com>
# Copyright (C) 2001-2002 AbiSource, Inc.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

abi_version=1.1.3

# abi_plugins is the list of subdirectories that are plugins
# The definition of a plugin is a directory containing a file called "plugin.m4".
# 
abi_plugins=

# abi_subdirs is a list of all directories in the current directory that are plugins or
# which have plugins in subdirectories, i.e., those directories into which make should
# recurse...
# 
abi_subdirs=

# abi_recurse is a subset of abi_subdirs which excludes plugins
# 
abi_recurse=

# abi_local is a subset of abi_subdirs which includes only plugins
# 
abi_local=

# abi_makefiles is the list of makefiles that configure must create
# 
abi_makefiles=

# abi_configs is the list of plugins that autoconf should scan
# 
abi_configs=

# abi_files is the list of files that plugins need configure to create
# 
abi_files=

if test "x$CONFIG_SHELL" = "x"; then
  CONFIG_SHELL=/bin/sh
  export CONFIG_SHELL
fi

abi_mode=abi_build

# option to append plugin.m4 to $abi_topdir/acinclude.m4
# 
abi_m4_append=""

# option to list files plugins require to be configured
# 
abi_list_files=""

# option to echo plugin descriptions and defaults
# 
abi_script_defaults=""

# option to echo configure plugin options
# 
abi_script_options=""

# option to echo spec's plugin options
# 
abi_spec_options=""

# option to echo spec's configure options
# 
abi_spec_configs=""

# option to echo spec's summary
# 
abi_spec_summary=""

# Parse our command line options once, thoroughly.
while test "$#" -gt 0
do
  arg="$1"
  shift

  case $arg in
  --query)
    abi_mode=abi_query
    ;;
  --config)
    abi_mode=abi_config
    ;;
  --script)
    abi_mode=abi_script
    ;;
  --spec)
    abi_mode=abi_spec
    ;;
  --m4-append)
    abi_m4_append="--m4-append"
    ;;
  --list-files)
    abi_list_files="--list-files"
    ;;
  --script-defaults)
    abi_script_defaults="--script-defaults"
    ;;
  --script-options)
    abi_script_options="--script-options"
    ;;
  --spec-options)
    abi_spec_options="--spec-options"
    ;;
  --spec-configs)
    abi_spec_configs="--spec-configs"
    ;;
  --spec-summary)
    abi_spec_summary="--spec-summary"
    ;;
  --help|-h)
    echo "Usage:"
    echo "     --script generate wrapper-script for configure"
    echo "     --spec   generate spec templates"
    echo "     --query  list plugin subdirs"
    echo " -h, --help   print this help and exit"
    exit 1
    ;;
  *)
    echo 'Option `'$arg"' not recognized. Try --help for more information."
    exit 1
    ;;
  esac
done

if test "x$abi_topdir" = "x"; then
  abi_topdir=`pwd`
  export abi_topdir
  if test $abi_mode = abi_build; then
    abi_mode=abi_all
    echo "Searching for AbiWord plugins. Please wait..."
  fi
fi
if test "x$abi_dir" = "x"; then
  abi_dir=.
  abi_am=abi_
else
  abi_am=abi_`echo $abi_dir | sed 's@/@_@g'`
fi

# Find plugins
# 
_abi_dir=$abi_dir
for i in *; do
  if test -d $i; then
    if test -r $i/plugin.m4; then
      # Found a plugin!
      abi_plugins="$abi_plugins $i"
      abi_subdirs="$abi_subdirs $i"
      abi_local="$abi_local $i"
      if test "x$abi_list_files" != "x"; then
        . $i/plugin.m4
        for j in $abi_plugin_files; do
          abi_files="$abi_files $i/$j"
        done
      fi
    else
      abi_subquery=`(cd $i > /dev/null && $CONFIG_SHELL $abi_topdir/nextgen.sh --query $abi_list_files)`
      if test "x$abi_subquery" != "x"; then
        for j in $abi_subquery; do
          abi_plugins="$abi_plugins $i/$j"
          if test "x$abi_list_files" != "x"; then
            abi_files="$abi_files $i/$j"
          fi
        done
        abi_subdirs="$abi_subdirs $i"
        abi_recurse="$abi_recurse $i"
        if test $abi_mode = abi_config; then
          if test $_abi_dir = .; then
            abi_dir=$i
          else
            abi_dir=$_abi_dir/$i
          fi
          export abi_dir
          (cd $i > /dev/null && $CONFIG_SHELL $abi_topdir/nextgen.sh --config $abi_m4_append $abi_script_defaults $abi_script_options $abi_spec_options $abi_spec_configs $abi_spec_summary)
        fi
      fi
    fi
  fi
done
abi_dir=$_abi_dir

if test $abi_mode = abi_script; then
  echo '#!/bin/sh'
  echo '# This script auto-generated by abiword-plugins/nextgen.sh'
  echo ''
  echo '# Add any --with-* options to config_opts here:'
  echo '# '
  echo 'config_opts="--disable-all"'
  echo ''
  echo '# --------------------------------------------------------- #'
  echo ''
  ($CONFIG_SHELL $abi_topdir/nextgen.sh --config --script-defaults)
  echo ''
  echo '# ---------------- Don't edit this section ---------------- #'
  echo ''
  ($CONFIG_SHELL $abi_topdir/nextgen.sh --config --script-options)
  echo ''
  echo '# --------------------------------------------------------- #'
  echo ''
  echo $CONFIG_SHELL' ./configure $config_opts'

  # The rest is build stuff, so quit here.
  # 
  exit 0
elif test $abi_mode = abi_spec; then
  echo '# PLUGIN OPTIONS: 1 for yes, 0 for no'
  ($CONFIG_SHELL $abi_topdir/nextgen.sh --config --spec-options)
  echo ''
  ($CONFIG_SHELL $abi_topdir/nextgen.sh --config --spec-configs)
  echo ''
  ($CONFIG_SHELL $abi_topdir/nextgen.sh --config --spec-summary)
  echo ''
  configure_line='./configure --prefix=$RPM_BUILD_ROOT%{ABIPREFIX}/AbiSuite --disable-all'
  for i in $abi_plugins; do
    configure_line="$configure_line %{plugin_`basename $i`}"
  done
  echo $configure_line

  # The rest is build stuff, so quit here.
  # 
  exit 0
elif test $abi_mode = abi_config; then
  if test "x$abi_local" != "x"; then
    if test "x$abi_script_defaults" != "x"; then
      for i in $abi_local; do
        . $i/plugin.m4
        echo '# '$i': '$abi_plugin_desc
        echo '# '
        if test "x$abi_plugin_enable" = "xyes"; then
          echo 'enable_'`echo $i | sed 's/-/_/g'`'=yes'
        else
          echo 'enable_'`echo $i | sed 's/-/_/g'`'=no'
        fi
        echo ''
      done
    elif test "x$abi_script_options" != "x"; then echo ""
      for i in $abi_local; do
        echo 'if test "x$enable_'`echo $i | sed 's/-/_/g'`'" = "xyes"; then'
        echo '  config_opts="$config_opts --enable-'$i'"'
        echo 'else'
        echo '  config_opts="$config_opts --disable-'$i'"'
        echo 'fi'
      done
    elif test "x$abi_spec_options" != "x"; then echo ""
      for i in $abi_local; do
        . $i/plugin.m4
        if test "x$abi_plugin_enable" = "xyes"; then
          echo '%define enable_'$i' 1'
        else
          echo '%define enable_'$i' 0'
        fi
      done
    elif test "x$abi_spec_configs" != "x"; then echo ""
      for i in $abi_local; do
        echo '%if %{enable_'$i'}'
        echo '%define plugin_'$i' --enable-'$i
        echo '%else'
        echo '%define plugin_'$i' --disable-'$i
        echo '%endif'
        echo ''
      done
    elif test "x$abi_spec_summary" != "x"; then echo ""
      for i in $abi_local; do
        abi_plugin_requires=""
        abi_plugin_buildreq=""
        . $i/plugin.m4
        echo '%if %{enable_'$i'}'
        echo '%package plugin-'$i
        echo 'Summary: '$abi_plugin_desc
        echo 'Group: Applications/Productivity'
        if test "x$abi_plugin_requires" != "x"; then
          echo 'Requires: '$abi_plugin_requires
        else
          echo 'Requires: abiword'
        fi
        if test "x$abi_plugin_buildreq" != "x"; then
          echo 'BuildRequires: '$abi_plugin_buildreq
        fi
        echo ''
        echo '%description plugin-'$i
        echo $abi_plugin_desc
        echo '%endif'
        echo ''
      done
    else
      echo "$abi_am="
      for i in $abi_local; do
        echo 'abi_plugin_add=yes'
        echo 'AC_ARG_ENABLE('$i',[  --disable-'$i'],['
        echo '	if test "x$enableval" = "xno"; then'
        echo '		abi_plugin_add=no'
        echo '	fi'
        echo '],[	abi_plugin_add=$abi_plugin_opt'
        echo '])'

        abi_plugin_macro_init=""
        abi_plugin_macro_end=""

        . $i/plugin.m4

        if test "$abi_plugin_macro_init" != ""; then
          echo $abi_plugin_macro_init
	fi

        echo 'if test $abi_plugin_add = yes; then'
        echo '	abi_plugin_disable=no'

        if test "$abi_plugin_macro" != ""; then
          if test "x$abi_m4_append" != "x"; then
            cat $i/plugin.m4 >> $abi_topdir/acinclude.m4
          fi
          echo '	'$abi_plugin_macro
        fi

        echo '	if test $abi_plugin_disable = no; then'
        echo '		'$abi_am'="$'$abi_am $i'"'
        echo '	fi'

        echo 'fi'

        if test "$abi_plugin_macro_end" != ""; then
          echo $abi_plugin_macro_end
	fi
      done
      echo "AC_SUBST($abi_am)"
      echo ''
    fi
  fi

  # The rest is build stuff, so quit here.
  # 
  exit 0
elif test $abi_mode = abi_query; then
  if test "x$abi_list_files" != "x"; then
    if test "x$abi_files" != "x"; then
      for i in $abi_files; do
        echo $i
      done
    fi
  else
    if test "x$abi_plugins" != "x"; then
      for i in $abi_plugins; do
        echo $i
      done
    fi
  fi

  # The rest is build stuff, so quit here.
  # 
  exit 0
else
  if test $abi_mode = abi_all; then
    if test "x$abi_subdirs" = "x"; then
      echo "Sorry. No AbiWord plugins found."
      exit 0
    fi
    if test -f "ac-helpers/abi-plugin-init.m4"; then
      echo "Creating build system for AbiWord plugins"
    else
      echo "This script creates a build system for AbiWord plugins. It deletes and creates a number"
      echo "of files, so it must be run from the top directory of the plugin source tree."
      exit 1
    fi
  else
    if test "x$abi_subdirs" = "x"; then
      echo "Glitch! Shouldn't be building when there are no subdirectories!"
      exit 1
    fi
  fi

  # Create GNUmakefile.am - only a SUBDIRS entry is required.
  # 
  if test $abi_dir = .; then
    abi_makefiles="GNUmakefile"
  else
    abi_makefiles="$abi_dir/GNUmakefile"
  fi
  rm -f GNUmakefile.am
  if test "x$abi_local" = "x"; then
    echo "SUBDIRS = $abi_recurse" > GNUmakefile.am
  else
    echo "SUBDIRS = @$abi_am@ $abi_recurse" > GNUmakefile.am
  fi

# Not sure about this:
# echo "" >> GNUmakefile.am
# echo "DIST_SUBDIRS = $abi_subdirs" >> GNUmakefile.am

  # and recurse into subdirectories...
  # 
  _abi_dir=$abi_dir
  for i in $abi_recurse; do
    if test $_abi_dir = .; then
      abi_dir=$i
    else
      abi_dir=$_abi_dir/$i
    fi
    export abi_dir
    abi_subbuild=`(cd $i > /dev/null && $CONFIG_SHELL $abi_topdir/nextgen.sh)`
    for j in $abi_subbuild; do
      abi_makefiles="$abi_makefiles $j"
    done
  done
  abi_dir=$_abi_dir

  # Standard build just creates GNUmakefile.am, so quit here.
  # 
  if test $abi_mode = abi_build; then
    for i in $abi_makefiles; do
      echo $i
    done
    exit 0
  fi
fi

# Create configure.ac
# 
rm -f configure.ac
cat > configure.ac << EOF
AC_INIT(abiword-plugins, $abi_version, [http://bugzilla.abisource.com/])
AC_CONFIG_SRCDIR([ac-helpers/abi-plugin-init.m4])

dnl First of all AbiWord plugin macros:
dnl 
ABI_PLUGIN_INIT($abi_version)
ABI_PLUGIN_CONFIG

# Checks for programs.
AC_PROG_CC
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

AM_INIT_AUTOMAKE(abiword, $abi_version)

AC_DISABLE_STATIC
AC_PROG_LIBTOOL

AC_C_CONST
AC_C_INLINE

dnl Configure plugin sources
dnl 
dnl AC_CONFIG_SUBDIRS($abi_configs)

abi_plugin_extra=
abi_plugin_opt=yes
AC_ARG_ENABLE(all,[  --disable-all           disable all plugins by default],[
	if test "x\$enableval" = "xno"; then
		abi_plugin_opt=no
	fi
])

EOF
rm -f $abi_topdir/acinclude.m4
($CONFIG_SHELL $abi_topdir/nextgen.sh --config --m4-append) >> configure.ac
cat >> configure.ac << EOF
AC_CONFIG_FILES([
$abi_makefiles
EOF
($CONFIG_SHELL $abi_topdir/nextgen.sh --query --list-files) >> configure.ac
cat >> configure.ac << EOF
])
AC_OUTPUT

if test -f plugin.status; then
	echo ""
	echo "Plugin reports:"
	echo ""
	cat plugin.status
	echo ""
fi
EOF

# Create configure.in
# 
rm -f configure.in
cat > configure.in << EOF
AC_INIT(ac-helpers/abi-plugin-init.m4)

dnl First of all AbiWord plugin macros:
dnl 
ABI_PLUGIN_INIT($abi_version)
ABI_PLUGIN_CONFIG

# Checks for programs.
AC_PROG_CC
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

AM_INIT_AUTOMAKE(abiword, $abi_version)

AC_DISABLE_STATIC
AC_PROG_LIBTOOL

AC_C_CONST
AC_C_INLINE

dnl Configure plugin sources
dnl 
dnl AC_CONFIG_SUBDIRS($abi_configs)

abi_plugin_extra=
abi_plugin_opt=yes
AC_ARG_ENABLE(all,[  --disable-all           disable all plugins by default],[
	if test "x\$enableval" = "xno"; then
		abi_plugin_opt=no
	fi
])

EOF
($CONFIG_SHELL $abi_topdir/nextgen.sh --config) >> configure.in
cat >> configure.in << EOF
AC_OUTPUT([
$abi_makefiles
EOF
($CONFIG_SHELL $abi_topdir/nextgen.sh --query --list-files) >> configure.in
cat >> configure.in << EOF
])

if test -f plugin.status; then
	echo ""
	echo "Plugin reports:"
	echo ""
	cat plugin.status
	echo ""
fi
EOF

# And, finally, call in the big boys...
# 
rm -f autogen.out
rm -f autogen.err

echo "Running libtoolize -f -c"
(libtoolize -f -c >> $abi_topdir/autogen.out 2>> $abi_topdir/autogen.err) || {
  echo "libtoolize failed! Unable to continue."
  exit 1
}

echo "Running aclocal -I ac-helpers $ACLOCAL_FLAGS"
(aclocal -I ac-helpers $ACLOCAL_FLAGS >> $abi_topdir/autogen.out 2>> $abi_topdir/autogen.err) || {
  echo "aclocal failed! Unable to continue."
  exit 1
}

echo "Checking for PKG_CHECK_MODULES..."

pkgcheckdef=`grep PKG_CHECK_MODULES aclocal.m4 | grep AC_DEFUN`
if test "x$pkgcheckdef" = "x"; then
  echo "Running aclocal -I ac-helpers -I ac-helpers/pkg-config $ACLOCAL_FLAGS"
  (aclocal -I ac-helpers -I ac-helpers/pkg-config $ACLOCAL_FLAGS >> $abi_topdir/autogen.out 2>> $abi_topdir/autogen.err) || {
    echo "aclocal failed! Unable to continue."
    exit 1
  }
  pkgcheckdef=`grep PKG_CHECK_MODULES aclocal.m4 | grep AC_DEFUN`
  if test "x$pkgcheckdef" = "x"; then
    echo ""
    echo "error: PKG_CHECK_MODULES isn't defined"
    echo ""
    echo "   Either pkg.m4 wasn't in aclocal's search path or pkgconfig"
    echo "   (or pkgconfig-devel?) isn't installed."
    echo ""
    echo "   If pkg-config is installed in <prefix> then re-run nextgen.sh:"
    echo ""
    echo "       ACLOCAL_FLAGS=\"-I <prefix>/share/aclocal\" ./nextgen.sh"
    echo ""
    exit
  fi
fi

echo "Running automake -a -c --foreign"
(automake -a -c --foreign >> $abi_topdir/autogen.out 2>> $abi_topdir/autogen.err) || {
  echo ">automake failed! Oh, well, trying again (you never know): automake -a --foreign"
  (automake -a --foreign >> $abi_topdir/autogen.out 2>> $abi_topdir/autogen.err) || {
    echo ">automake failed again! Damn. Look, I'll try autoconf anyway, but don't blame me"
    echo " if it all goes horribly wrong. (This ain't easy!) Here goes:"
  }
}

echo "Running autoconf"
(autoconf >> $abi_topdir/autogen.out 2>> $abi_topdir/autogen.err) || {
  echo ">autoconf failed! Sorry - I'm unable to continue."
  exit 1
}