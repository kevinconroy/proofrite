#!/bin/sh
#
#  AbiSource Unix Font Library Installer Program
#  Copyright (C) 1999 AbiSource, Inc.
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#

# Defaults
TEST_PACKAGE_FILE=fonts/fonts.dir
INSTALL_FONTSDIR=fonts
DEFAULT_INSTALL_BASE=/usr/local/AbiSuite

# Program execution
cat <<EOF

  AbiSource Font Installer, Copyright (C) 1999 AbiSource, Inc.

   This program comes with ABSOLUTELY NO WARRANTY; this software is
   free software, and you are welcome to redistribute it under
   certain conditions.  Read the file called COPYING in the archive 
   in which this program arrived for more details.
EOF

# Make sure the fonts are really here
if [ ! -f ${TEST_PACKAGE_FILE} ]
then
    echo ""
    echo "Fatal error: I can't find the file [${TEST_PACKAGE_FILE}], and I can't install fonts"
    echo "without it."
    echo ""
    exit 1
fi

# Read prefix from user
cat <<EOF

  Please specify the directory into which you would like to install the
  AbiSuite Unix fonts.  The default directory is [${DEFAULT_INSTALL_BASE}], 
  but you may provide an alternate path if you wish.  Hit "Enter" to use
  the default value.

  The directory you specify should be the location where the AbiSuite 
  applications are installed.  This is usually [${DEFAULT_INSTALL_BASE}].
EOF

GO=1
while test ${GO} -eq 1
do
    echo ""
    echo -n "Installation path for AbiSuite font software [${DEFAULT_INSTALL_BASE}]: "
    read INSTALL_BASE

    # did they use tildes for home dirs?
    if [ ! -z "`echo ${INSTALL_BASE} | grep '~'`" ]
    then
	INSTALL_BASE = `echo ${INSTALL_BASE} | sed "s:~:${HOME}:"`
    fi

    # did they just hit enter?
    if [ -z "${INSTALL_BASE}" ]
    then
	INSTALL_BASE="${DEFAULT_INSTALL_BASE}"
    fi

    # GO off, passed tests
    GO=0
    if [ ! -d ${INSTALL_BASE} ]
    then
	echo ""
	echo "  I did not find an existing directory [${INSTALL_BASE}]."
	echo "  This probably means that the AbiSuite applications are not currently"
	echo "  installed.  When you install them, be sure to provide this same location"
	echo "  to the AbiSuite applications install program."
	echo ""
	echo -n "The directory [${INSTALL_BASE}] does not exist; do you wish to create it? (y/n) [y]: "
	read CREATE_DIR
	if [ "${CREATE_DIR}" = "n" -o "${CREATE_DIR}" = "N" ]
	then
	    GO=1
	else
	    # create the entire path
	    DESTDIR=${INSTALL_BASE}/${INSTALL_FONTSDIR}
	    mkdir -p ${DESTDIR}
	    if [ $? -ne 0 ]
	    then
		echo ""
		echo "  I couldn't create [${INSTALL_BASE}].  You are probably seeing this error"
 		echo "  because you do not have sufficient permission to perform this operation."
		echo "  You will most likely have to run this script as superuser to write to"
		echo "  system directories."
		# loop around again
		GO=1
	    fi
	fi
    else
	# the directory already exists, go ahead an assume the applications are installed 
	# there
	echo ""
	echo "  I found an existing directory called [${INSTALL_BASE}].  If this is"
	echo "  the location of the AbiSuite applications, everything is in order"
	echo "  and you will want to proceed with the installation.  Existing font"
	echo "  files will be overwritten; they will not be backed up."
	echo ""
	echo -n "Do you want to install into [${INSTALL_BASE}]? (y/n) [y]: "
	read INSTALL_OVER
	if [ "${INSTALL_OVER}" = "n" -o "${INSTALL_OVER}" = "N" ]
	then
	    GO=1
	fi
	# make our subdirectory (fonts) for stuff to go in
	# create the entire path
	DESTDIR=${INSTALL_BASE}/${INSTALL_FONTSDIR}
	mkdir -p ${DESTDIR}
	if [ $? -ne 0 ]
	then
	    echo ""
	    echo "  I couldn't create [${DESTDIR}], "
	    echo "  which is where I will install the fonts.  You are probably seeing "
	    echo "  this error because you do not have sufficient permission to perform"
	    echo "  this operation.  You will most likely have to run this script as "
	    echo "  superuser to write to system directories."
	    # loop around again
	    GO=1
	fi
    fi
done

# Install font directory file
echo ""
echo "Installing X font file index file to [${DESTDIR}]... "
    cp fonts/fonts.dir ${DESTDIR}/
    cp fonts/fonts.scale ${DESTDIR}/
    chmod a-w ${DESTDIR}/fonts.dir
    chmod a-w ${DESTDIR}/fonts.scale

# Install fonts

echo ""
echo "Installing Type 1 ASCII font files to [${DESTDIR}]... "
for ASCIIFILE in fonts/*.pfa
do
    cp ${ASCIIFILE} ${DESTDIR}/
done


echo ""
echo "Installing Type 1 font file metrics to [${DESTDIR}]... "
for METRICFILE in fonts/*.afm
do
    cp ${METRICFILE} ${DESTDIR}/
done

echo ""
echo "Installing Glyph name map files to [${DESTDIR}]... "
for GLYPHFILE in fonts/*.u2g
do
    cp ${GLYPHFILE} ${DESTDIR}/
done


########################################################################
# If we're on Solaris, do the PostScript resource thing.  This script
# and the main install script share this code... change one, change the
# other (please).
########################################################################

OS_NAME=`uname -s`
OS_RELEASE_MAJOR=`uname -r | sed -e "s/\..*//"`

if [ "${OS_NAME}" = "SunOS" -a "${OS_RELEASE_MAJOR}" = "5" ]
then
    if [ -d ${DESTDIR} ]
    then
	echo ""
	echo "Building PostScript font resource database for installed fonts..."
	cd ${DESTDIR}
	/usr/openwin/bin/makepsres
    fi
fi

echo ""
echo "Installation complete.  Unix fonts now reside in [${DESTDIR}]."
echo ""







