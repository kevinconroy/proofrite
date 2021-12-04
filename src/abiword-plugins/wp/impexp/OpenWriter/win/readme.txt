This is a place holder for zipios.lib and the zipios++ header directory

zipios.lib will need to be generated and copied to this location
for the Win32 plug-in build of libOpenWriter.dll to work.

zipios++ can be found at
http://zipios.sourceforge.net/

zipios++ is in a beta state for Windows and requires special handling.  Hopefully in the near future it will build more successfully as it is required for this plugin. Get the source code, follow the instructions for building.  

Certain zlib Include files will needed to be created or mapped to.
	This means that either copy
		zlib.h to VC98/include/zlib.h
		zconf.h to VC98/include/zconf.h
   Or define where to find those files as part of vcvars32.bat INCLUDE search routines.

Place in this directory (win)
	zipios.lib
	and the entire zipios++ header directory

And now you are set to build this plug-in.  Go back to the OpenWriter directory and type make

Note - unable to get make ABI_OPT_DEBUG=1 to build successfully


