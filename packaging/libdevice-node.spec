Name:       libdevice-node
Summary:    Library to control OAL APIs
Version:    0.1.0
Release:    1
Group:      Application Framework/Libraries
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
Source1:    %{name}.manifest
BuildRequires:  cmake
BuildRequires:  pkgconfig(vconf)
BuildRequires:  pkgconfig(dlog)

%description
development package of library to control OAL APIs

%package devel
Summary:	Control OAL APIs (devel)
Requires:	%{name} = %{version}-%{release}

%description devel
Library to control OAL APIs (devel)


%prep
%setup -q
cp %{SOURCE1} .
%build
%cmake .
make %{?jobs:-j%jobs}

%install
%make_install

%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig

%files
%{_libdir}/*.so.*
%{_libdir}/hw/default/*.so
%manifest %{name}.manifest
%license LICENSE.APLv2

%files devel
%{_includedir}/device-node/*.h
%{_includedir}/hw/*.h
%{_libdir}/*.so
%{_libdir}/pkgconfig/*.pc
