#ifndef EDITORFRAME_H_
#define EDITORFRAME_H_

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

#include "GeneratedGui.h"
#include <wx/string.h>
#include <wx/filename.h>

class EditorFrame : public EditorFrameGUI
{
private:
  bool updatedFile;
  const wxFileName fn;
  wxString err;

  void save();

protected:
  virtual void saveClicked( wxCommandEvent& event );
  virtual void helpClicked( wxCommandEvent& event );
  virtual void onClose( wxCloseEvent& event );

  virtual void closeClicked( wxCommandEvent& event )
  {
    Close();
  }

public:
      EditorFrame(
        wxWindow * parent,
        const wxFileName & fn,
        const wxString & title );

  bool isUpdatedFile()
  {
    return updatedFile;
  }

  bool hasError()
  {
    return !err.IsEmpty();
  }

  const wxString & getError()
  {
    return err;
  }
};

#endif /* EDITORFRAME_H_ */
