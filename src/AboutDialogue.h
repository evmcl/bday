#ifndef ABOUTDIALOGUE_H_
#define ABOUTDIALOGUE_H_

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

class AboutDialogue : public AboutDialogueGUI
{
protected:
  virtual void onLeftUp( wxMouseEvent& event )
  {
    Close();
  }

public:
  AboutDialogue( wxWindow * parent );
};

#endif /* ABOUTDIALOGUE_H_ */
