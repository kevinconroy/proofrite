This is a place holder for libxml2_a.lib and iconv.lib

You may find both these libraries at 
http://www.xmlsoft.org/downloads.html

or better yet get the precompiled Win32 packages at
http://www.fh-frankfurt.de/~igor/projects/libxml/index.html

Get the source code, follow the instructions for building.  We normally want the static libs unless you will place the generated dll in the system path.

Include directories will needed to be created or mapped.
	This means that either copy
		the enitre libxml directory to VC98/include
   Or define those as part of vcvars32.bat INCLUDE search routines.

Place the static libraries in this directory  
	libxml2_a.lib
	iconv_a.lib (rename this to iconv.lib)

And now you are set to build this plug-in.  



