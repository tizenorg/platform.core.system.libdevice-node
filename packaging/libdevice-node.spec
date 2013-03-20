Name:       libdevice-node
Summary:    Library to control OAL APIs
Version:    0.1.0
Release:    1
Group:      System/Libraries
License:    Apache License, Version 2.0
Source0:    %{name}-%{version}.tar.gz
Source1:    %{name}.manifest
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

%build
CFLAGS="$CFLAGS" cmake . -DCMAKE_INSTALL_PREFIX=%{_prefix}
make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
mkdir -p %{buildroot}/usr/share/license
cp LICENSE %{buildroot}/usr/share/license/device-node
%make_install
cp -a %{SOURCE1} %{buildroot}%{_datadir}/
install -D -d %{buildroot}/etc/rc.d/rc3.d/
install -D -d %{buildroot}/etc/rc.d/rc4.d/
ln -sf ../init.d/smack_device_labeling %{buildroot}/etc/rc.d/rc3.d/S44smack_device_labeling
ln -sf ../init.d/smack_device_labeling %{buildroot}/etc/rc.d/rc4.d/S44smack_device_labeling

%post
if [ ! -e "/lib/firmware/mdnie" ]
then
	mkdir -p /lib/firmware/mdnie
fi

%postun

%files
%{_libdir}/*.so.*
%{_libdir}/udev/rules.d/*
%{_datadir}/license/device-node
%attr(755,root,root) %{_sysconfdir}/rc.d/*
%manifest %{_datadir}/%{name}.manifest

%files devel
%{_includedir}/device-node/*.h
%{_libdir}/*.so
%{_libdir}/pkgconfig/*.pc
