# This spec file creates three packages:
#
#	Everything:
#		(this is equivalent to two others together)
#			fribidiN-version-release-arch.rpm
#	Runtime material: Shared library and command line tool
#			libfribidiN-version-release-arch.rpm
#	Development material: Static library and header files
#		(requires libfribidi)
#			libfribidiN-devel-version-release-arch.rpm
#	Where N is the major version number.

%define name fribidi
%define ver 0.10.4
%define major 0
%define minor 10
%define micro 4
%define apiver 2
%define rel 0
%define prefix %{_prefix}

Name: %{name}
Version: %{ver}
Release: %{rel}
Serial: %{apiver}
License: LGPL
Source: http://prdownloads.sourceforge.net/%{name}/%{name}-%{ver}.tar.gz
URL: http://%{name}.sourceforge.net/
BuildRoot: %{_tmppath}/%{name}
Summary: Library implementing the Unicode Bidirectional Algorithm
Group: System/Libraries
%description
A library to handle bidirectional scripts (eg. hebrew, arabic), so that
the display is done in the proper way; while the text data itself is
always written in logical order.

%package -n %{name}%{major}
Summary: Library implementing the Unicode Bidirectional Algorithm
Group: System/Libraries
Provides: lib%{name}%{major}
Provides: lib%{name}%{major}-devel
%description -n %{name}%{major}
A library to handle bidirectional scripts (eg. hebrew, arabic), so that
the display is done in the proper way; while the text data itself is
always written in logical order.

Install %{name}%{major} if you want to run or develop programs that use %{name}.


%package -n lib%{name}%{major}
Summary: Library implementing the Unicode Bidirectional Algorithm
Group: System/Libraries
Conflicts: %{name}%{major}
%description -n lib%{name}%{major}
The lib%{name}%{major} package includes the shared libraries for the %{name}%{major} package.

Install lib%{name}%{major} if you want to run programs which use %{name}.


%package -n lib%{name}%{major}-devel
Summary: Library implementing the Unicode Bidirectional Algorithm
Group: Development/C
Requires: lib%{name}%{major} = %{ver}
Conflicts: %{name}%{major}
%description -n lib%{name}%{major}-devel
The lib%{name}%{major}-devel package includes the static libraries and header files
for the %{name}%{major} package.

Install lib%{name}%{major}-devel if you want to develop programs which will use
%{name}.


%prep
%setup

%build
if [ ! -x ./configure ];then 
./bootstrap
fi

./configure %{_target_platform}                                         \
	--prefix=%{_prefix}             --exec-prefix=%{_exec_prefix}   \
	--bindir=%{_bindir}             --sbindir=%{_sbindir}           \
	--sysconfdir=%{_sysconfdir}     --datadir=%{_datadir}           \
	--includedir=%{_includedir}                                     \
	--libdir=%{_libdir}             --libexecdir=%{_libexecdir}     \
	--mandir=%{_mandir}             --infodir=%{_infodir}           \
	--localstatedir=%{_localstatedir} --sharedstatedir=%{_sharedstatedir}
 
make OPT_CFLAGS="$RPM_OPT_FLAGS"

%install
rm -rf "$RPM_BUILD_ROOT"
mkdir -p "$RPM_BUILD_ROOT%{prefix}"
make DESTDIR="$RPM_BUILD_ROOT" install


%clean
rm -rf "$RPM_BUILD_ROOT"

%post -n %{name}%{major} -p /sbin/ldconfig
%postun -n %{name}%{major} -p /sbin/ldconfig

%post -n lib%{name}%{major} -p /sbin/ldconfig
%postun -n lib%{name}%{major} -p /sbin/ldconfig

%files -n %{name}%{major}
%defattr(-,root,root)
%doc README AUTHORS COPYING ChangeLog TODO THANKS NEWS
%{_bindir}/%{name}
%{_bindir}/%{name}-config
%{_libdir}/*.so.*
%{_libdir}/pkgconfig/%{name}.pc
%{_libdir}/*.a
%{_libdir}/*.la
%{_libdir}/*.so
%{_includedir}/*

%files -n lib%{name}%{major}
%defattr(-, root, root)
%doc README AUTHORS COPYING ChangeLog TODO THANKS NEWS
%{_bindir}/%{name}
%{_bindir}/%{name}-config
%{_libdir}/*.so.*

%files -n lib%{name}%{major}-devel
%defattr(-, root, root)
%{_libdir}/*.a
%{_libdir}/*.la
%{_libdir}/*.so
%{_includedir}/*
%{_libdir}/pkgconfig/%{name}.pc


%changelog

* Tue Mar 12 2002  Behdad Esfahbod <behdad@bamdad.org>
- Use License instead of Copyright
- Moved pkgconfig to devel package instead of lib package.

* Sat Jan 26 2002  Behdad Esfahbod <behdad@bamdad.org>
- CFLAGS changed to OPT_CFLAGS.

* Wed Jan  9 2002  Behdad Esfahbod <behdad@bamdad.org>
- First spec released.
