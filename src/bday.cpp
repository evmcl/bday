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

#include "events.h"
#include "BdayFrame.h"
#include <wx/wx.h>
#include <wx/cmdline.h>

class BdayApp : public wxApp
{
  virtual bool OnInit();
};

IMPLEMENT_APP( BdayApp)

bool BdayApp::OnInit()
{
  SetVendorName(wxT("evanmclean.com"));

  bool quick = false;
  if ( GetAppName().CmpNoCase(wxT("bdayquick")) == 0 )
  {
    quick = true;
    SetAppName(wxT("bday"));
  }

  wxCmdLineParser cl(argc, argv);
  cl.AddSwitch(wxT("q"), wxT("quick"), wxT("Exit immediately if there are no current events."));
  cl.AddOption(wxT("t"), wxT("today"), wxT("Run as if the specified date is today."), wxCMD_LINE_VAL_DATE);
  cl.AddOption(wxT("r"), wxT("run-from"), wxT("Capture all events since the specified date."),wxCMD_LINE_VAL_DATE);
  if ( cl.Parse() != 0 )
    return false;

  wxDateTime dt;
  if ( cl.Found(wxT("r"), &dt) )
    Events::setRunFrom(dt);
  if ( cl.Found(wxT("t"), &dt) )
  {
    Events::setToday(dt);
    wxString title(wxT("Events - "));
    title << dt.Format(wxT("%a %d %b %Y"));
    BdayFrame::setDefaultTitle(title);
  }
  else
  {
    wxString title(wxT("Events - "));
    title << wxDateTime::Today().Format(wxT("%a %d %b %Y"));
    BdayFrame::setDefaultTitle(title);
  }

  const Events::Events events = Events::getEvents();
  if ( events.size() <= 0 )
    if ( quick || cl.Found(wxT("q")) )
      return false;

  ::wxInitAllImageHandlers();

  BdayFrame *frame = new BdayFrame();
  frame->set(events);
  frame->Centre();
  frame->Show(true);
  SetTopWindow(frame);
  return true;
}
