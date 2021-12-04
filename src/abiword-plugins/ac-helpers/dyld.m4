# This stuff is specific to building on Darwin using fjf's libtool patch
# 
# DYLD_BUNDLE_LOADER(EXECUTABLE-PATH)
# -----------------------------------
AC_DEFUN([DYLD_BUNDLE_LOADER],
[if test "x$1" != "x"; then _lt_bundle_loader="-bundle_loader $1"; else _lt_bundle_loader=''; fi])
