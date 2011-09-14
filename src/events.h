#ifndef EVENTS_H_
#define EVENTS_H_

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

#include <list>
#include <wx/string.h>
#include <wx/datetime.h>
#include <wx/filename.h>

namespace Events
{
  typedef std::list<wxString> Events;

  /**
   * Read the system and user event files.
   * @return The set of events to be displayed.
   */
  Events getEvents();

  /**
   * Set the date to be treated as today (used mainly for debugging.)
   * @param today The date to be treated as today.
   */
  void setToday( wxDateTime today );

  /**
   * The date to run from, which must be less than or equal to today.
   * This is used so if any events came due on a day when bday was not
   * run, they will be shown.  This is usually set automatically, but
   * can be explicitly set here for debugging purposes.
   * @param run_from The date to capture events from.
   */
  void setRunFrom( wxDateTime run_from );

  /**
   * Get the system configuration file name.
   */
  wxFileName getSystemConfigFile();

  /**
   * Get the user configuration file name.
   */
  wxFileName getUserConfigFile();

#ifdef __WINDOWS__
/**
 * Get the application configuration file name.
 */
wxFileName getApplicationConfigFile();
#endif
}

#endif /* EVENTS_H_ */
