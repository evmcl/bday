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
#include "tokeniser.h"
#include <set>
#include <wx/stdpaths.h>
#include <wx/textfile.h>
#include <wx/confbase.h>
#ifdef __WINDOWS__
#include <wx/msw/regconf.h>
#else
#include <wx/fileconf.h>
#endif
#include <wx/app.h>
static int conv( wxDateTime::Month month );

namespace // (local)
{
  /**
   * A simple collector to hold the event text and how many days
   * away so it can be sorted appropriately in the set.
   */
  class DayEvent
  {
  public:
    const int daysAway;
    const wxString event;

    DayEvent( int da, const wxString & ev ) :
      daysAway(da), event(ev)
    {
      // empty
    }
  };

  int compare( const DayEvent & lhs, const DayEvent & rhs )
  {
    int ret = lhs.daysAway - rhs.daysAway;
    if ( ret == 0 )
      ret = lhs.event.CmpNoCase(rhs.event);
    return ret;
  }

  bool operator<( const DayEvent & lhs, const DayEvent & rhs )
  {
    return compare(lhs, rhs) < 0;
  }

  bool operator>( const DayEvent & lhs, const DayEvent & rhs )
  {
    return compare(lhs, rhs) > 0;
  }

  bool operator==( const DayEvent & lhs, const DayEvent & rhs )
  {
    return compare(lhs, rhs) == 0;
  }

  typedef std::set<DayEvent> DayEvents;

  // Days away value for storing error messages.
  static const int ERROR_DAY = -5000;

  // Days away value for storing warning messages.
  static const int WARNING_DAY = -4000;

  // The default number of days warning you get before an event.
  static const int DEFAULT_LEAD_TIME = 5;

  // The maximum lead time you can have (not that it would necessarily make sense...
  static const int MAX_LEAD_TIME = 999;

  static const int MONTH_LENGTHS[] =
  { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

  class Event
  {
  public:
    int dom;
    wxDateTime::WeekDay dow;
    int dow_offset;
    bool months[12];
    int year;
    int year_offset;
    int lead_time;
    wxString text;

    Event( int lead_time ) :
      dom(0), dow(wxDateTime::Mon), dow_offset(1), year(0), year_offset(0),
          lead_time(lead_time)
    {
      memset(months, 0, sizeof ( months ));
    }

    bool isDayConsistent()
    {
      if ( dom == 0 )
        return true;
      const int day = ( dom > 0 )
        ? dom : ( dom * -1 );
      for ( int xi = 0; xi < 12; ++xi )
        if ( months[xi] )
          if ( day > MONTH_LENGTHS[xi] )
            return false;
      return true;
    }

    /**
     * If there is only one month nominated, return the name of it.
     */
    const wchar_t * getMonth() const
    {
      const wchar_t * mon = 0;
      for ( int xi = 0; xi < 12; ++xi )
        if ( months[xi] )
        {
          if ( mon != 0 )
            return 0; // More than one month nominated.
          switch ( xi )
          {
          case 0:
            mon = wxT("Jan");
            break;
          case 1:
            mon = wxT("Feb");
            break;
          case 2:
            mon = wxT("Mar");
            break;
          case 3:
            mon = wxT("Apr");
            break;
          case 4:
            mon = wxT("May");
            break;
          case 5:
            mon = wxT("Jun");
            break;
          case 6:
            mon = wxT("Jul");
            break;
          case 7:
            mon = wxT("Aug");
            break;
          case 8:
            mon = wxT("Sep");
            break;
          case 9:
            mon = wxT("Oct");
            break;
          case 10:
            mon = wxT("Nov");
            break;
          case 11:
            mon = wxT("Dec");
            break;
          }
        }
      return mon;
    }

    wxDateTime getDate( const wxDateTime & month ) const
    {
      if ( !forThisMonth(month) )
        return wxInvalidDateTime;
      if ( dom == 0 )
        return getDow(month);

      const int last_day = wxDateTime::GetNumberOfDays(month.GetMonth(),
        month.GetYear());
      int real_dom = ( dom >= 0 )
        ? dom : ( last_day + 1 + dom );
      if ( ( real_dom < 1 ) || ( real_dom > last_day ) )
        return wxInvalidDateTime;
      wxDateTime dt(month);
      dt.SetDay(real_dom);
      return dt;
    }

  private:
    bool forThisMonth( const wxDateTime & month ) const
    {
      if ( !months[conv(month.GetMonth())] )
        return false;
      const int current_year = month.GetYear();
      if ( current_year < year )
        return false;
      if ( year_offset > 0 )
        if ( current_year > ( year + year_offset - 1 ) )
          return false;
      return true;
    }

    wxDateTime getDow( const wxDateTime & month ) const
    {
      wxDateTime dt(month);
      if ( dow_offset > 0 )
      {
        dt.SetDay(1);
        while ( dt.GetWeekDay() != dow )
          dt += wxDateSpan::Day();
        for ( int xi = 1; xi < dow_offset; ++xi )
          dt += wxDateSpan::Week();
      }
      else
      {
        dt.SetDay(
          wxDateTime::GetNumberOfDays(month.GetMonth(), month.GetYear()));
        while ( dt.GetWeekDay() != dow )
          dt -= wxDateSpan::Day();
        for ( int xi = -1; xi > dow_offset; --xi )
          dt -= wxDateSpan::Week();
      }

      // Make sure still in the same month and year.
      if ( ( dt.GetMonth() != month.GetMonth() ) || ( dt.GetYear()
          != month.GetYear() ) )
        return wxInvalidDateTime;
      return dt;
    }
  };

  class FileProcessor
  {
  private:
    const wxFileName & fn;
    int linenum;
    int lead_time;
    DayEvents & events;

    bool Line( const wxString & line );
    bool LeadTime( Tokeniser & tok );
    bool Include( const wxString & ifn );
    bool Err( const wxChar * msg );
    void Emit( const Event & event );
    wxString
        Format( const Event & event, const wxDateTime & dt, const int days );

    bool SyntaxErr()
    {
      return Err(wxT("Not a valid event or command."));
    }

  public:
    FileProcessor( const wxFileName & fn, DayEvents & events, int lead_time =
        MAX_LEAD_TIME ) :
      fn(fn), linenum(0), lead_time(lead_time), events(events)
    {
    }

    bool Process();

  };

  static wxDateTime today = wxInvalidDateTime;
  static wxDateTime runFrom = wxInvalidDateTime;
  static const wxTimeSpan twoHours = wxTimeSpan::Hours(2);
  static const wxDateSpan oneMonth = wxDateSpan::Month();
} // namespace (local)

static int diff( const wxDateTime & lhs, const wxDateTime & rhs )
{
  if ( rhs >= lhs )
    return ( ( rhs + twoHours ) - lhs ).GetDays();
  return ( ( rhs - twoHours ) - lhs ).GetDays();
}

#ifndef __WINDOWS__
static wxFileName getUserPropertiesFolder()
{
  return wxFileName(wxStandardPaths::Get().GetUserConfigDir(), wxT(".bday"));
}

static wxFileName getUserPropertiesFile()
{
  return wxFileName(getUserPropertiesFolder().GetFullPath(), wxT("properties.txt"));
}
#endif

static wxConfigBase * getProperties()
{
  wxConfigBase::DontCreateOnDemand();
  wxConfigBase * config = wxConfigBase::Get(false);
  if ( config == 0 )
  {
#ifdef __WINDOWS__
    config = new wxRegConfig(wxT("bday"), wxT("evanmclean.com"), wxEmptyString,
        wxEmptyString, wxCONFIG_USE_LOCAL_FILE);
#else
    config = new wxFileConfig(wxTheApp->GetAppName(),
      wxTheApp->GetVendorName(), getUserPropertiesFile().GetFullPath(),
      wxEmptyString, wxCONFIG_USE_LOCAL_FILE);
#endif
  }
  return config;
}

/**
 * Process the specified file.
 * @param fn The file to read.
 * @param events The container to store the events.
 * @return True if there were any events in the file, even if they were not for the current date.
 */
static bool processFile( const wxFileName & fn, DayEvents & events )
{
  FileProcessor proc(fn, events);
  return proc.Process();
}

static const wxChar * strpos( wxChar ch, const wxChar * str )
{
  while ( *str != wxT('\0') )
  {
    if ( ch == *str )
      return str;
    ++str;
  }
  return 0;
}

static int conv( wxDateTime::Month month )
{
  switch ( month )
  {
  case wxDateTime::Jan:
    return 0;
  case wxDateTime::Feb:
    return 1;
  case wxDateTime::Mar:
    return 2;
  case wxDateTime::Apr:
    return 3;
  case wxDateTime::May:
    return 4;
  case wxDateTime::Jun:
    return 5;
  case wxDateTime::Jul:
    return 6;
  case wxDateTime::Aug:
    return 7;
  case wxDateTime::Sep:
    return 8;
  case wxDateTime::Oct:
    return 9;
  case wxDateTime::Nov:
    return 10;
  case wxDateTime::Dec:
    return 11;
  default:
    return -1;
  }
}

static bool toDayOfWeek( const wxString & str, wxDateTime::WeekDay & dow )
{
  if ( str.length() > 3 )
    return toDayOfWeek(str.Left(3), dow);
  if ( str.CmpNoCase(wxT("Mon")) == 0 )
  {
    dow = wxDateTime::Mon;
    return true;
  }
  if ( str.CmpNoCase(wxT("Tue")) == 0 )
  {
    dow = wxDateTime::Tue;
    return true;
  }
  if ( str.CmpNoCase(wxT("Wed")) == 0 )
  {
    dow = wxDateTime::Wed;
    return true;
  }
  if ( str.CmpNoCase(wxT("Thu")) == 0 )
  {
    dow = wxDateTime::Thu;
    return true;
  }
  if ( str.CmpNoCase(wxT("Fri")) == 0 )
  {
    dow = wxDateTime::Fri;
    return true;
  }
  if ( str.CmpNoCase(wxT("Sat")) == 0 )
  {
    dow = wxDateTime::Sat;
    return true;
  }
  if ( str.CmpNoCase(wxT("Sun")) == 0 )
  {
    dow = wxDateTime::Sun;
    return true;
  }
  return false;
}

static bool toMonth( const wxString & str, int & month )
{
  if ( str.CmpNoCase(wxT("Jan")) == 0 )
  {
    month = 0;
    return true;
  }
  if ( str.CmpNoCase(wxT("Feb")) == 0 )
  {
    month = 1;
    return true;
  }
  if ( str.CmpNoCase(wxT("Mar")) == 0 )
  {
    month = 2;
    return true;
  }
  if ( str.CmpNoCase(wxT("Apr")) == 0 )
  {
    month = 3;
    return true;
  }
  if ( str.CmpNoCase(wxT("May")) == 0 )
  {
    month = 4;
    return true;
  }
  if ( str.CmpNoCase(wxT("Jun")) == 0 )
  {
    month = 5;
    return true;
  }
  if ( str.CmpNoCase(wxT("Jul")) == 0 )
  {
    month = 6;
    return true;
  }
  if ( str.CmpNoCase(wxT("Aug")) == 0 )
  {
    month = 7;
    return true;
  }
  if ( str.CmpNoCase(wxT("Sep")) == 0 )
  {
    month = 8;
    return true;
  }
  if ( str.CmpNoCase(wxT("Oct")) == 0 )
  {
    month = 9;
    return true;
  }
  if ( str.CmpNoCase(wxT("Nov")) == 0 )
  {
    month = 10;
    return true;
  }
  if ( str.CmpNoCase(wxT("Dec")) == 0 )
  {
    month = 11;
    return true;
  }
  return false;
}

static bool toMonths( const wxString & str, bool * months )
{
  const size_t len = str.length();
  size_t start = 0;
  while ( start < len )
  {
    bool range = false;
    size_t end = start;
    while ( end < len )
    {
      wxChar ch = str[end];
      if ( ch == wxT('-') )
      {
        range = true;
        break;
      }
      if ( ch == wxT(',') )
      {
        range = false;
        break;
      }
      ++end;
    }

    int smonth;
    if ( !toMonth(str.Mid(start, end - start), smonth) )
      return false;
    if ( !range )
    {
      months[smonth] = true;
    }
    else
    {
      start = end + 1;
      if ( start >= len )
        return false;
      while ( end < len )
      {
        if ( str[end] == wxT(',') )
          break;
        ++end;
      }
      int emonth;
      if ( !toMonth(str.Mid(start, end - start), emonth) )
        return false;
      if ( emonth < smonth )
      {
        int tmp = smonth;
        smonth = emonth;
        emonth = tmp;
      }
      for ( int mon = smonth; mon <= emonth; ++mon )
        months[mon] = true;
    }
    start = end + 1;
  }
  return true;
}

static Events::Events processFiles()
{
  DayEvents events;
  bool any_events = false;
#ifdef __WINDOWS__
  if ( processFile(Events::getApplicationConfigFile(), events) )
  any_events = true;
#endif
  if ( processFile(Events::getSystemConfigFile(), events) )
    any_events = true;
  if ( processFile(Events::getUserConfigFile(), events) )
    any_events = true;
  if ( !any_events )
    events.insert(DayEvent(WARNING_DAY + 1, wxT("No events in the configuration files.")));

  // Load the (correctly ordered) DayEvents into the Events list.
  Events::Events ev;
  for ( DayEvents::iterator it = events.begin(); it != events.end(); ++it )
    ev.push_back(it->event);
  return ev;
}

static void init()
{
  if ( today.IsValid() )
    today.ResetTime();
  else
    today = wxDateTime::Today();

  if ( !runFrom.IsValid() )
  {
    wxConfigBase * config = getProperties();
    const wxString last_run = config->Read(wxT("last_run"), wxEmptyString);
    if ( !last_run.IsEmpty() )
    {
      wxDateTime lastRun;
      if ( lastRun.ParseDate(last_run) != 0 )
        runFrom = lastRun + wxDateSpan::Day();
    }
  }
  if ( !runFrom.IsValid() )
  {
    runFrom = today;
  }
  else
  {
    if ( runFrom > today )
      runFrom = today;
  }
}

static void finish()
{
  if ( today == wxDateTime::Today() )
  {
#ifndef __WINDOWS__
    wxFileName file = getUserPropertiesFile();
    if ( !file.DirExists() )
      file.Mkdir(0700);
#endif
    wxConfigBase * config = getProperties();
    config->Write(wxT("last_run"), today.FormatISODate());
    config->Flush();
  }
}

namespace Events
{
  void setToday( wxDateTime today )
  {
    ::today = today;
  }

  void setRunFrom( wxDateTime run_from )
  {
    ::runFrom = run_from;
  }

  /**
   * Get the events.
   * @return A list of the events.
   */
  Events getEvents()
  {
    init();
    const Events ev = processFiles();
    finish();
    return ev;
  }

  wxFileName getSystemConfigFile()
  {
#ifdef __WINDOWS__
    return wxFileName(wxStandardPaths::Get().GetConfigDir() + wxT(".txt"));
#else
    return wxFileName(wxStandardPaths::Get().GetConfigDir(), wxT("bdayrc"));
#endif
  }

  wxFileName getUserConfigFile()
  {
#ifdef __WINDOWS__
    return wxFileName(wxStandardPaths::Get().GetUserConfigDir(), wxT("bday.txt"));
#else
    return wxFileName(wxStandardPaths::Get().GetUserConfigDir(), wxT(".bdayrc"));
#endif
  }

#ifdef __WINDOWS__
wxFileName getApplicationConfigFile()
{
  return wxFileName(wxStandardPaths::Get().GetResourcesDir(), wxT("bday.txt"));
}
#endif

} // namespace Events

bool FileProcessor::Process()
{
  if ( !fn.FileExists() )
    return false;
  wxTextFile file;
  if ( !file.Open(fn.GetFullPath()) )
  {
    wxString msg(wxT("ERROR: Could not open file: "));
    msg.Append(fn.GetFullPath());
    events.insert(DayEvent(ERROR_DAY, msg));
    return true;
  }

  linenum = 0;
  lead_time = DEFAULT_LEAD_TIME;
  bool any_events = false;
  const int num_lines = file.GetLineCount();
  for ( int xi = 0; xi < num_lines; ++xi )
  {
    ++linenum;
    if ( Line(file[xi].Trim(false).Trim(true)) )
      any_events = true;
  }

  file.Close();
  return any_events;
}

bool FileProcessor::Line( const wxString & line )
{
  if ( line.length() <= 0 ) // empty line
    return false;
  switch ( line[0] )
  {
  case wxT('#'):
  case wxT(';'):
    return false; // comment line
  }

  Tokeniser tok(line);
  const wxString first_word(tok.GetNextToken());

  // See if the first word matches any commands, and dispatch to them.
  if ( first_word.CmpNoCase(wxT("include")) == 0 )
    return Include(tok.GetRemainingString());

  if ( first_word.CmpNoCase(wxT("lead")) == 0 )
    return LeadTime(tok);

  // Assume it is an event
  Event ev(lead_time);

  // Process the first word.
  if ( strpos(first_word[0], wxT("0123456789+-")) != 0 )
  {
    long dom;
    if ( !first_word.ToLong( &dom) )
      return SyntaxErr();
    if ( ( dom == 0 ) || ( dom > 31 ) || ( dom < -31 ) )
      return Err(wxT("Day must be between 1 and 31 (positive or negative)."));
    ev.dom = dom;
  }
  else
  {
    wxDateTime::WeekDay dow;
    if ( !toDayOfWeek(first_word, dow) )
      return SyntaxErr();
    long offset = 1;
    if ( first_word.length() > 3 )
    {
      if ( !first_word.Mid(3).ToLong( &offset) )
        return SyntaxErr();
      if ( ( offset == 0 ) || ( offset > 5 ) || ( offset < -5 ) )
        return Err(
          wxT("Day of the week offset must be between 1 and 5 (positive or negative)."));
    }
    ev.dow = dow;
    ev.dow_offset = offset;
  }

  // Process the months;
  {
    const wxString months(tok.GetNextToken());
    if ( months.length() <= 0 )
      return SyntaxErr();
    if ( !toMonths(months, ev.months) )
      return SyntaxErr();
  }

  // Process optional year.
  {
    const wxString year(tok.PeekNextToken());
    const size_t len = year.length();
    if ( len >= 4 )
    {
      size_t signpos = 1;
      while ( ( signpos < len ) && ( year[signpos] != '+' ) )
        ++signpos;
      if ( signpos >= len )
      {
        long ye;
        if ( year.ToLong( &ye) )
          if ( ( ye >= 1000 ) && ( ye <= 9999 ) )
          {
            ev.year = (int) ye;
            tok.FindNextToken(); // Consume the token.
          }
      }
      else
      {
        long ye;
        if ( year.Mid(0, signpos).ToLong( &ye) )
          if ( ( ye >= 1000 ) && ( ye <= 9999 ) )
          {
            if ( ( signpos + 1 ) < len )
            {
              long offset;
              if ( year.Mid(signpos + 1).ToLong( &offset) )
              {
                if ( ( offset > 0 ) && ( offset < 999 ) )
                {
                  ev.year = (int) ye;
                  ev.year_offset = (int) offset;
                  tok.FindNextToken(); // Consume the token.
                }
                else
                {
                  return Err(wxT("Year offset must be between 1 and 999"));
                }
              }
            }
          }
      }
    }
  }

  // Process option lead time
  {
    const wxString lt(tok.PeekNextToken());
    long num;
    if ( lt.ToLong( &num) )
      if ( ( num > 0 ) && ( num <= MAX_LEAD_TIME ) )
      {
        ev.lead_time = num;
        tok.FindNextToken(); // Consume the token.
      }
  }

  // Get the event text
  ev.text = tok.GetRemainingString();
  if ( ev.text.length() <= 0 )
    return SyntaxErr();

  // Check consistency of month days.
  if ( !ev.isDayConsistent() )
  {
    wxString msg(wxT("Day value "));
    msg << ev.dom << wxT(" out of range for ");
    const wchar_t * mon = ev.getMonth();
    if ( mon == 0 )
      msg << wxT("at least one of the nominated months.");
    else
      msg << mon << wxT('.');
    return Err(msg);
  }

  // Check 29th Feb.
  if ( ( ( ev.dom == 29 ) || ( ev.dom == -29 ) ) && ev.months[1] && ( ev.year
      != 0 ) )
  {
    if ( !wxDateTime::IsLeapYear(ev.year) )
    {
      wxString msg;
      msg << ev.year << wxT(" is not a leap year.");
      return Err(msg);
    }
  }

  Emit(ev);
  return true;
}

void FileProcessor::Emit( const Event & event )
{
  wxDateTime proc_month = runFrom;
  proc_month.SetDay(1);
  while ( diff(today, proc_month) <= event.lead_time )
  {
    const wxDateTime dt = event.getDate(proc_month);
    if ( dt.IsValid() )
    {
      const int days = diff(today, dt);
      if ( ( days <= event.lead_time ) && ( dt >= runFrom ) )
        events.insert(DayEvent(days, Format(event, dt, days)));
    }

    proc_month += oneMonth;
  }
}

wxString FileProcessor::Format(
  const Event & event,
  const wxDateTime & dt,
  const int days )
{
  wxString text(event.text);
  text << wxT(' ');
  if ( event.year > 0 )
    text << wxT('(') << ( dt.GetYear() - event.year ) << wxT(") ");
  switch ( days )
  {
  case 0:
    text << wxT("today.");
    break;

  case 1:
    text << wxT("tomorrow.");
    break;

  case -1:
    text << wxT("yesterday.");
    break;

  default:
    if ( days > 0 )
      text << wxT("in ") << days << wxT(" days (") << dt.Format(wxT("%a %d %b %Y")) << wxT(").");
    else
      text << ( days * -1 ) << wxT(" days ago (") << dt.Format(wxT("%a %d %b %Y")) << wxT(").");
    break;
  }
  return text;
}

bool FileProcessor::LeadTime( Tokeniser & tok )
{
  {
    const wxString time(tok.GetNextToken());
    if ( time.CmpNoCase(wxT("time")) != 0 )
      return SyntaxErr();
  }

  const wxString ltstr(tok.GetRemainingString());
  if ( ltstr.length() <= 0 )
    return SyntaxErr();
  long lt;
  if ( !ltstr.ToLong( &lt) )
    return SyntaxErr();
  if ( lt < 0 )
    return SyntaxErr();
  if ( lt > MAX_LEAD_TIME )
  {
    lt = MAX_LEAD_TIME;
    wxString msg(wxT("Lead time cannot be greater than "));
    msg.Append(MAX_LEAD_TIME);
    return Err(msg);
  }
  lead_time = lt;
  return false;
}

bool FileProcessor::Include( const wxString & ifn )
{
  const wxFileName file(ifn);
  if ( !file.FileExists() )
  {
    wxString msg(wxT("Include file does not exist: "));
    msg.Append(file.GetFullPath());
    return Err(msg);
  }
  FileProcessor sub(file, events, lead_time);
  return sub.Process();
}

bool FileProcessor::Err( const wxChar * msg )
{
  wxString buff(wxT("File "));
  buff << fn.GetFullPath() << wxT(", Line ") << linenum << wxT(": ") << msg;
  events.insert(DayEvent(ERROR_DAY, buff));
  return true;
}
