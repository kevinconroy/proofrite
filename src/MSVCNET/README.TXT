AbiWord Microsoft Visual C++ 6.0 project files and project workspace

Files top copy or rename to make it build:

expat/lib/expat.h.in           -> expat/lib/expat.h
popt/config.h.msvc             -> popt/config.h
psiconv/config.h.msvc          -> psiconv/config.h
psiconv/psiconv/general.h.msvc -> psiconv/psiconv/general.h
wv/config.h.msvc               -> wv/config.h
wv/version.c.win32             -> wv/version.c

In the libiconv module you must copy or rename
include/iconv.h.msvc-static                 -> include/iconv.h
include/libiconv.h.msvc                     -> include/libiconv.h
libcharset/config.h.msvc                    -> libcharset/config.h
libcharset/include/libcharset.h.in -> libcharset/include/libcharset.h
