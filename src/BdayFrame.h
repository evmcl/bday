#ifndef BDAYFRAME_H_
#define BDAYFRAME_H_

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
#include "events.h"

class BdayFrame : public BdayFrameGUI
{
private:
  static wxString title;

  void editFile( const wxFileName & file, const wxString & title );

protected:
  virtual void menuExit( wxCommandEvent& event )
  {
    Close(true);
  }

  virtual void menuAbout( wxCommandEvent& event );
  virtual void menuUserEdit( wxCommandEvent& event );
  virtual void menuSystemEdit( wxCommandEvent& event );
#ifdef __WINDOWS__
  virtual void menuApplicationEdit( wxCommandEvent& event );
  virtual void menuStart( wxCommandEvent& event );
#endif
  virtual void onClose( wxCloseEvent& event );

  virtual void menuContents( wxCommandEvent& event )
  {
    showHelp();
  }

  virtual void OkClicked( wxCommandEvent& event )
  {
    Close();
  }

public:
  BdayFrame();

  void set( const Events::Events & events );
  void reload();
  void showHelp();

  static void setDefaultTitle( const wxString & def_title );
};

#endif /* BDAYFRAME_H_ */
