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

#include "HelpFrame.h"
#include <wx/msgdlg.h>
#include <wx/stdpaths.h>

#if !defined(__WXMSW__) && !defined(__WXPM__)
#include "../images/icon.xpm"
#endif

const wxString HelpFrame::defaultTitle(wxT("BDay Help"));

HelpFrame::HelpFrame( wxWindow * parent ) :
  HelpFrameGUI(parent, wxID_ANY, defaultTitle, wxPoint(0, 0))
{
  SetIcon(wxICON(icon));
  wxStandardPathsBase & stdp = wxStandardPaths::Get();

  // Try the resource folder (which is really where it should be).
  wxFileName fn(stdp.GetResourcesDir() + wxT("/help"), wxT("index.html"));

#ifndef __WINDOWS__
  // Try /usr/share/bday/help
  if ( ! fn.IsFileReadable() )
    fn = wxFileName(wxT("/usr/share/bday/help"), wxT("index.html"));

  // Try /usr/local/share/bday/help
  if ( ! fn.IsFileReadable() )
    fn = wxFileName(wxT("/usr/local/share/bday/help"), wxT("index.html"));
#endif

  // Try the same folder as the executable.
  if ( ! fn.IsFileReadable() )
    fn = wxFileName(wxFileName(stdp.GetExecutablePath()).GetPath()
    + wxT("/help"), wxT("index.html"));

  // Try the adjacent folder as the executable.
  if ( ! fn.IsFileReadable() )
    fn = wxFileName(wxFileName(stdp.GetExecutablePath()).GetPath()
    + wxT("/../help"), wxT("index.html"));

  if ( fn.IsFileReadable() )
    m_htmlWin1->LoadFile(fn);
  else
    m_htmlWin1->SetPage(wxT("<html><body>Could not find the help file.</body></html>"));
}
