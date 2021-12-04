This is a place holder for ImageMagick.lib

ImageMagick.lib will need to be generated and copied to this location
for the Win32 plug-in build of ImageMagick to work.

To create ImageMagick.lib you will need MC Visaul C++ Version 6.0 or better
Check out www.imagemagick.org and get source code for ImageMagick.

Follow steps to build ImageMagick Multithreaded static libraries
-Build Configure
-Run Configure selecting Multithreaded static library
-Build VisualStaticMT.dsw

In the lib directory you will need to run:
		lib /OUT:ImageMagick.lib *.lib

Include directories will needed to be created or mapped.
	This means that either copy
		magick/*.h to VC98/include/magic/*.h
		magick++/lib/magic++.h to VC98/include/magic++.h
		magick++/lib/magic++/*.h to VC98/include/magic++/*.h
   Or define those as part of vcvars32.bat INCLUDE search routines.
                    
With the creation of ImageMagick.lib, copy/move it to this directory and 
continue with the AbiWord build process for this plugin.



