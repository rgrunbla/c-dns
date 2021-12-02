Name: libcdns
Version: {{ version }}
Release: {{ release }}%{?dist}
Summary: Exporter of C-DNS format
Url: https://gitlab.nic.cz/knot/c-dns
Source: c-dns-%{version}.tar.gz
License: MPLv2.0

BuildRequires:  gcc
BuildRequires:  make
BuildRequires:  cmake
BuildRequires:  boost-devel
BuildRequires:  pkgconfig(zlib)
BuildRequires:  pkgconfig(liblzma)

%package devel
Summary:    Exporter of the C-DNS format (development headers)
Requires:   %{name}%{?_isa} = %{version}-%{release}

%description devel
Headers of C-DNS library.

%description
Library for export of the C-DNS format.

%prep
%autosetup -p1 -n c-dns-%{version}
mkdir build

%build
cd build
cmake \
    -DCMAKE_INSTALL_PREFIX:PATH=%{_prefix} \
    -DBUILD_TESTS=ON \
    -DCMAKE_C_FLAGS="${RPM_OPT_FLAGS}" \
    -DCMAKE_CXX_FLAGS="${RPM_OPT_FLAGS}" \
    ..
make

%install
cd build
make DESTDIR=%{buildroot} install

%files
%license LICENSE
%{_libdir}/libcdns.so.0
%{_libdir}/libcdns.so.0.*


%files devel
%{_libdir}/libcdns.so
%{_libdir}/pkgconfig/cdns.pc
%{_includedir}/cdns/*.h
%dir %{_includedir}/cdns/

%changelog
* {{ now }} Jakub Ružička <jakub.ruzicka@nic.cz> - {{ version }}-{{ release }}
- upstream package
