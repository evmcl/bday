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

# Defines
!define NAME "BDay"
!define COMPANY "McLean Computer Services"
!define VERSION 2.0
!define REGKEY "Software\evanmclean.com\bday"
!define URL http://evanmclean.com/
!define INSTALLDIR "$PROGRAMFILES\BDay"

;Various Settings
Name "Simple Birthday and Anniversary Reminder"
OutFile "bday-win32-v${VERSION}.exe"
Icon "..\images\icon.ico"
BrandingText " "
InstallDir "${INSTALLDIR}"
CRCCheck On
XPStyle on
ShowInstDetails show
ShowUninstDetails show
InstallDirRegKey HKLM "${REGKEY}" "Path"
SetOverwrite on

LicenseText "Please review the license agreement before installing BDay.  If you accept all terms of the agreement, click I Agree."
LicenseData "../etc/win32/license.txt"

Page license
Page components
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

VIProductVersion 2.0.0.0
VIAddVersionKey ProductName "${NAME}"
VIAddVersionKey ProductVersion "${VERSION}"
VIAddVersionKey CompanyName "${COMPANY}"
VIAddVersionKey CompanyWebsite "${URL}"
VIAddVersionKey FileVersion "${VERSION}"
VIAddVersionKey FileDescription ""
VIAddVersionKey LegalCopyright "Copyright 2009 Evan McLean"

Section "-Program (required)"
  SetOutPath "${INSTALLDIR}"
  File "bday.exe"
  File "..\etc\win32\COPYING.txt"
  File "..\etc\win32\README.txt"

  SetOutPath "${INSTALLDIR}\help"
  File "..\help\advanced.html"
  File "..\help\index.html"
  File "..\help\license.html"
  File "..\help\linux.html"
  File "..\help\locations.html"

  SetOutPath "${INSTALLDIR}\help\images"
  File "..\help\images\main_window.png"
  File "..\help\images\main_window_editing_events.png"
  File "..\help\images\main_window_lead_time.png"
  File "..\help\images\main_window_run_on_startup.png"

  WriteRegStr HKLM "${REGKEY}" "Path" "${INSTALLDIR}"
  WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}" "DisplayName" "$(^Name)"
  WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}" "DisplayVersion" "${VERSION}"
  WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}" "Publisher" "${COMPANY}"
  WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}" "URLInfoAbout" "${URL}"
  WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}" "DisplayIcon" "${INSTALLDIR}\bday.exe"
  WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}" "UninstallString" "${INSTALLDIR}\uninstall.exe"
  WriteRegDWORD HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}" "NoRepair" 1
  Delete "${INSTALLDIR}\uninstall.exe"
  WriteUninstaller "${INSTALLDIR}\uninstall.exe"
SectionEnd

Section "Programs Menu Shortcut"
  CreateShortCut "$SMPROGRAMS\BDay.lnk" "${INSTALLDIR}\bday.exe" "" "${INSTALLDIR}\bday.exe" 0
SectionEnd

Section "Run on Startup/Login"
  WriteRegStr HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Run" "BDay" "$\"${INSTALLDIR}\bday.exe$\" --quick"
SectionEnd

Function .onInstSuccess
  MessageBox MB_YESNO|MB_ICONQUESTION "Run BDay now?" IDYES RunNow
  Goto Done
  RunNow:
    ExecShell "open" "${INSTALLDIR}\bday.exe"
  Done:
FunctionEnd

UninstallText "This will uninstall the BDay from your computer.  Click Uninstall to start the uninstallation."

Section Uninstall
  Delete "${INSTALLDIR}\bday.exe"
  Delete "${INSTALLDIR}\COPYING.txt"
  Delete "${INSTALLDIR}\README.txt"
  Delete "${INSTALLDIR}\help\advanced.html"
  Delete "${INSTALLDIR}\help\index.html"
  Delete "${INSTALLDIR}\help\license.html"
  Delete "${INSTALLDIR}\help\linux.html"
  Delete "${INSTALLDIR}\help\locations.html"
  Delete "${INSTALLDIR}\help\images\main_window.png"
  Delete "${INSTALLDIR}\help\images\main_window_editing_events.png"
  Delete "${INSTALLDIR}\help\images\main_window_lead_time.png"
  Delete "${INSTALLDIR}\help\images\main_window_run_on_startup.png"
  Delete "${INSTALLDIR}\uninstall.exe"

  RMDir "${INSTALLDIR}\help\images"
  RMDir "${INSTALLDIR}\help"
  RMDir "${INSTALLDIR}"

  Delete "$SMPROGRAMS\BDay.lnk"

  DeleteRegValue HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Run" "BDay"

  DeleteRegKey HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}"
  DeleteRegKey HKLM "${REGKEY}"
  DeleteRegKey HKCU "${REGKEY}"
SectionEnd

