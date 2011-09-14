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

#include "EditorFrame.h"
#include "BdayFrame.h"
#include <wx/textfile.h>
#include <wx/msgdlg.h>

#if !defined(__WXMSW__) && !defined(__WXPM__)
#include "../images/icon.xpm"
#endif

EditorFrame::EditorFrame(
  wxWindow * parent,
  const wxFileName & fn,
  const wxString & title ) :
  EditorFrameGUI(parent, wxID_ANY, title), updatedFile(false), fn(fn)
{
  m_textCtrl2->SetFocus();
  CentreOnParent();
  SetIcon(wxICON(icon));
  m_textCtrl3->SetValue(fn.GetFullPath());
  if ( fn.FileExists() )
  {
    wxTextFile file;
    if ( !file.Open(fn.GetFullPath()) )
    {
      wxString msg(wxT("ERROR: Could not open file: "));
      msg.Append(fn.GetFullPath());
      err = msg;
      return;
    }

    const wxString nl(wxT("\n"));
    wxString buff;
    buff.Alloc(fn.GetSize().ToULong());
    const int num_lines = file.GetLineCount();
    for ( int xi = 0; xi < num_lines; ++xi )
    {
      if ( xi > 0 )
        buff << nl;
      buff << file[xi];
    }
    m_textCtrl2->SetValue(buff);
    m_textCtrl2->DiscardEdits();

    if ( !fn.IsFileWritable() )
    {
      m_textCtrl2->SetEditable(false);
      m_save->Disable();
      wxString ro_title(title);
      ro_title << wxT(" (READ-ONLY)");
      SetTitle(ro_title);
      m_close->SetFocus();
    }
  }
  else
  {
    if ( !fn.IsDirWritable() )
    {
      m_textCtrl2->SetEditable(false);
      m_save->Disable();
    }
  }
}

void EditorFrame::onClose( wxCloseEvent& event )
{
  if ( event.CanVeto() && m_textCtrl2->IsEditable()
      && m_textCtrl2->IsModified() )
  {
    wxString msg(wxT("Save "));
    msg += fn.GetFullName();
    msg += wxT('?');
    wxMessageDialog mb(this, msg, GetTitle(), wxCANCEL| wxYES_NO | wxICON_QUESTION);
    switch ( mb.ShowModal() )
    {
    case wxID_YES:
      save();
      break;

    case wxID_NO:
      break;

    default:
      event.Veto(true);
      return;
    }
  }

  event.Skip();
}

void EditorFrame::saveClicked( wxCommandEvent& event )
{
  save();
  Close(true);
}

void EditorFrame::helpClicked( wxCommandEvent& event )
{
  ((BdayFrame *)GetParent())->showHelp();
}

void EditorFrame::save()
{
  wxTextFile file(fn.GetFullPath());
  const int num_lines = m_textCtrl2->GetNumberOfLines();
  for ( int xi = 0; xi < num_lines; ++xi )
    file.AddLine(m_textCtrl2->GetLineText(xi));
  file.Write();
  updatedFile = true;
  ((BdayFrame *)GetParent())->reload();
  m_textCtrl2->DiscardEdits();
}
