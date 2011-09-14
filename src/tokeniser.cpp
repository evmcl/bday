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

#include "tokeniser.h"

namespace // (local)
{
  static const wxString EMPTY;

  inline bool isWhitespace( wxChar ch )
  {
    switch ( ch )
    {
    case wxT(' '):
    case wxT('\t'):
    case wxT('\r'):
    case wxT('\n'):
      return true;
    default:
      return false;
    }
  }
}

Tokeniser::Tokeniser( const wxString & str ) :
  str(str), start(0), end(0)
{
  FindNextToken();
}

bool Tokeniser::FindNextToken()
{
  const size_t len = str.length();

  // Increment start pointer until we find the next non-whitespace char
  // (or hit the end of the string).
  for ( start = end; start < len; ++start )
    if ( !isWhitespace(str[start]) )
      break;

  // Increment end pointer until we find the next whitespace char
  // (or hit the end of the string).
  for ( end = start; end < len; ++end )
    if ( isWhitespace(str[end]) )
      break;
  return HasMoreTokens();
}

wxString Tokeniser::GetNextToken()
{
  wxString ret(PeekNextToken());
  FindNextToken();
  return ret;
}

wxString Tokeniser::PeekNextToken()
{
  if ( HasMoreTokens() )
    return str.Mid(start, end - start);
  return EMPTY;
}

wxString Tokeniser::GetRemainingString()
{
  if ( HasMoreTokens() )
    return str.Mid(start);
  return EMPTY;
}
