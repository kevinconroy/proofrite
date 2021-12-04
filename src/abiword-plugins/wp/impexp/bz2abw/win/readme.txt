This is a place holder for libbz2.lib

libbz2.lib will need to be generated and copied to this location
for the Win32 plug-in build of ImageMagick to work.

bzi2 and libbzip2 can be found at:
http://sourceware.cygnus.com/bzip2/index.html

Get the source code, follow the instructions for building.  We normally want the static libs unless you will place the generated dll in the system path.

Include directories will needed to be created or mapped.
	This means that either copy
		bzlib.h to VC98/include/bzlib.h.h
   Or define those as part of vcvars32.bat INCLUDE search routines.

Place in this directory  
	libbz2.lib

And now you are set to build this plug-in.  from  the bz2abw directory use make under the cygwin system for abiword.


