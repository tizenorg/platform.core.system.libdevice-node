Name:       libdevice-node
Summary:    Library to control OAL APIs
Version:    0.1.0
Release:    1
Group:      System/Libraries
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
Source1:    %{name}.manifest
Source2:    smack-device-labeling.service
BuildRequires:  cmake
BuildRequires:  pkgconfig(vconf)
BuildRequires:  pkgconfig(dlog)

%description
development package of library to control OAL APIs

%package devel
Summary:	Control OAL APIs (devel)
Group:		Development/Libraries
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

mkdir -p %{buildroot}%{_libdir}/systemd/system/basic.target.wants
install -m 644 %{SOURCE2} %{buildroot}%{_libdir}/systemd/system/
ln -s ../smack-device-labeling.service %{buildroot}%{_libdir}/systemd/system/basic.target.wants/
mkdir -p %{buildroot}/lib/firmware/mdnie


%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig

%files
%{_libdir}/*.so.*
%{_prefix}/lib/udev/rules.d/*
%{_libdir}/systemd/system/smack-device-labeling.service
%{_libdir}/systemd/system/basic.target.wants/smack-device-labeling.service
/lib/firmware/mdnie
%manifest %{name}.manifest

%files devel
%{_includedir}/device-node/*.h
%{_libdir}/*.so
%{_libdir}/pkgconfig/*.pc
