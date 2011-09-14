/*
* Copyright 2009 Evan McLean
* http://evanmclean.com/
*
* This file is part of BDay.
*
* BDay is free software: you can redistribute it and/or modify it under the
* terms of the GNU General Public License as published by the Free Software
* Foundation, either version 3 of the License, or (at your option) any later
* version.
*
* BDay is distributed in the hope that it will be useful, but WITHOUT ANY
* WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
* A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with
* BDay.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "BdayFrame.h"
#include "AboutDialogue.h"
#include "EditorFrame.h"
#include "HelpFrame.h"
#include <wx/msgdlg.h>
#include <wx/stdpaths.h>
#ifdef __WINDOWS__
#include <windows.h>
#include <winreg.h>
#endif

#if !defined(__WXMSW__) && !defined(__WXPM__)
#include "../images/icon.xpm"
#endif

#ifdef __WINDOWS__
static void setAutoRun( bool auto_run );
static bool getAutoRun();
#endif

wxString BdayFrame::title(wxT("Events"));

void
BdayFrame::setDefaultTitle( const wxString & def_title )
{
  title = def_title;
}

BdayFrame::BdayFrame() :
  BdayFrameGUI(0)
{
  SetIcon(wxICON(icon));
  SetTitle(title);
  m_okay->SetFocus();
  {
    const wxFileName fn(Events::getSystemConfigFile());
    if ( ( !fn.FileExists() ) && ( !fn.IsDirWritable() ) )
      edit->Delete(systemEventsFile);
  }
#ifndef __WINDOWS__
  file->Delete(start);
  edit->Delete(applicationEventsFile);
#else
  {
    const wxFileName fn(Events::getApplicationConfigFile());
    if ( !fn.FileExists() )
      edit->Delete(applicationEventsFile);
  }

  start->Check(getAutoRun());
#endif
}

void BdayFrame::menuAbout( wxCommandEvent& event )
{
  AboutDialogue dialogue(this);
  dialogue.ShowModal();
}

void BdayFrame::menuUserEdit( wxCommandEvent& event )
{
  editFile(Events::getUserConfigFile(), wxT("User Events File"));
}

void BdayFrame::menuSystemEdit( wxCommandEvent& event )
{
  editFile(Events::getSystemConfigFile(), wxT("System Events File"));
}

void BdayFrame::set( const Events::Events & events )
{
  const wxString nl(wxT("\n"));
  m_textCtrl1->SetValue(wxT(""));
  for ( Events::Events::const_iterator it = events.begin(); it != events.end(); ++it )
    ( *m_textCtrl1 ) << ( *it ) << nl;
}

void BdayFrame::onClose( wxCloseEvent& event )
{
  if ( event.CanVeto() )
  {
    wxWindowList & wnds = GetChildren();
    for ( wxWindowList::iterator it = wnds.begin(); it != wnds.end(); ++it )
      if ( ( *it )->IsKindOf(CLASSINFO(wxFrame)) )
        if ( ! ((wxFrame *)( *it ))->Close() )
        {
          event.Veto(true);
          return;
        }
  }

  event.Skip();
}

void BdayFrame::editFile( const wxFileName & file, const wxString & title )
{
  wxWindowList & wnds = GetChildren();
  for ( wxWindowList::iterator it = wnds.begin(); it != wnds.end(); ++it )
    if ( ( *it )->IsKindOf(CLASSINFO(wxFrame)) )
      if ( ((wxFrame *)( *it ))->GetTitle().IsSameAs(title) )
      {
        ( *it )->Raise();
        return;
      }
  EditorFrame * frame = new EditorFrame(this, file, title);
  if ( frame->hasError() )
  {
    wxMessageDialog mb(this, frame->getError(), GetTitle(), wxOK| wxICON_ERROR);
    mb.ShowModal();
  }
  else
  {
    frame->Show(true);
  }
}

void BdayFrame::reload()
{
  const Events::Events events = Events::getEvents();
  set(events);
}

void BdayFrame::showHelp()
{
  wxWindowList & wnds = GetChildren();
  for ( wxWindowList::iterator it = wnds.begin(); it != wnds.end(); ++it )
    if ( ( *it )->IsKindOf(CLASSINFO(wxFrame)) )
      if ( ((wxFrame *)( *it ))->GetTitle().IsSameAs(HelpFrame::defaultTitle) )
      {
        ( *it )->Raise();
        return;
      }
  HelpFrame * frame = new HelpFrame(this);
  frame->Show(true);
}

#ifdef __WINDOWS__
void BdayFrame::menuApplicationEdit( wxCommandEvent& event )
{
  editFile(Events::getApplicationConfigFile(), wxT("Application Events File"));
}

void BdayFrame::menuStart( wxCommandEvent& event )
{
  const bool auto_run = start->IsChecked();
  setAutoRun(auto_run);
  if ( getAutoRun() != auto_run )
  {
    start->Check(!auto_run);
    wxMessageDialog mb(this
        , auto_run
        ? wxT("Could not set the registry entry to run BDay.")
        : wxT("Could not clear the registry entry to run BDay.")
        , GetTitle(), wxOK);
    mb.ShowModal();
  }
}

static wxString expectedAutoRunValue()
{
  wxString val;
  val
  << wxT('"')
  << wxStandardPaths::Get().GetExecutablePath()
  << wxT("\" --quick")
  ;
  return val;
}

static void setAutoRun( bool auto_run )
{
  HKEY regkey;
  if ( RegOpenKeyEx(HKEY_CURRENT_USER
          , wxT("Software\\Microsoft\\Windows\\CurrentVersion\\Run")
          , 0, KEY_READ | KEY_SET_VALUE, &regkey)
      != ERROR_SUCCESS )
  return;

  RegDeleteValue(regkey, wxT("bday"));

  if ( auto_run )
  {
    const wxString expected(expectedAutoRunValue());
    const wchar_t * ptr = expected.c_str();
    RegSetValueEx(regkey, wxT("bday"), 0, REG_SZ
        , reinterpret_cast<const BYTE *>(ptr)
        , ( expected.size() * sizeof(*ptr) ) + sizeof(*ptr));
  }

  RegCloseKey(regkey);
}

static bool getAutoRun()
{
  HKEY regkey;
  if ( RegOpenKeyEx(HKEY_CURRENT_USER
          , wxT("Software\\Microsoft\\Windows\\CurrentVersion\\Run")
          , 0, KEY_READ, &regkey)
      != ERROR_SUCCESS )
  return false;

  DWORD type = REG_SZ;
  wchar_t buff[4096];
  memset(buff, 0, sizeof(buff));
  DWORD size = sizeof(buff) - sizeof(buff[0]);
  long ret = RegQueryValueEx(regkey, wxT("bday"), 0, &type
      , reinterpret_cast<BYTE *>(buff), &size);

  RegCloseKey(regkey);

  if (( ret != ERROR_SUCCESS )
      || ( type != REG_SZ )
      || ( size <= 0 ))
  return false;

  const wxString expected(expectedAutoRunValue());
  if ( expected.CmpNoCase(buff) != 0 )
  return false;
  if ( !expected.EndsWith(wxT("quick")) )
  return false;
  return true;
}
#endif
