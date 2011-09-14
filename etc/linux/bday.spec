#
# spec file for package bday
#
# Copyright 2009 Evan McLean
# http://evanmclean.com/
#
# This file is part of BDay.
#
# BDay is free software: you can redistribute it and/or modify it under the
# terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later
# version.
#
# BDay is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
# A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with
# BDay.  If not, see <http://www.gnu.org/licenses/>.

Name:          bday
Summary:       The super simple birthday and anniversary reminder program.
License:       GNU General Public License version 3
Group:         Utilities/Desktop
Version:       2.0
Release:       1
URL:           http://evanmclean.com/
Source0:       %{name}-src-%{version}.tar.bz2
BuildRequires: gcc-c++ wxWidgets-devel update-desktop-files
BuildRoot:     %{_tmppath}/%{name}-%{version}-build
Requires:      libmspack0

%description
BDay is a simple program to help you track birthdays and anniversaries. It runs when you start or log in to your computer, displays any events that are coming up, and then exits when you click OK. It does not hang around in the system tray or as a background process taking up your computer's resources. If there are no events to be displayed, then you wont even see BDay run.

%prep
%setup

%build
cd linux
make

%install
%{__mkdir_p} $RPM_BUILD_ROOT/%{_prefix}/bin
%{__mkdir_p} $RPM_BUILD_ROOT/%{_prefix}/share/applications
%{__mkdir_p} $RPM_BUILD_ROOT/%{_prefix}/share/icons
%{__mkdir_p} $RPM_BUILD_ROOT/%{_prefix}/share/bday/help/images

%{__install} -m 755 linux/bday $RPM_BUILD_ROOT/%{_prefix}/bin/
%{__install} -m 644 etc/linux/bday.desktop $RPM_BUILD_ROOT/%{_prefix}/share/applications/
%{__install} -m 644 etc/linux/bday.png $RPM_BUILD_ROOT/%{_prefix}/share/icons/
%{__install} -m 644 COPYING LICENSE README $RPM_BUILD_ROOT/%{_prefix}/share/bday/
%{__install} -m 644 help/*.html $RPM_BUILD_ROOT/%{_prefix}/share/bday/help/
%{__install} -m 644 help/images/*.png $RPM_BUILD_ROOT/%{_prefix}/share/bday/help/images/

cd $RPM_BUILD_ROOT/%{_prefix}/bin
ln -s bday bdayquick

%clean
%{__rm} -rf $RPM_BUILD_ROOT

%files
%defattr(-, root, root)
%{_prefix}/bin/bday
%{_prefix}/bin/bdayquick
%{_prefix}/share/applications/bday.desktop
%{_prefix}/share/icons/bday.png
%doc %{_prefix}/share/bday/
