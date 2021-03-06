// 2004-08-29  Paolo Carlini  <pcarlini@suse.de>

// Copyright (C) 2004 Free Software Foundation
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 2, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING.  If not, write to the Free
// Software Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307,
// USA.

// 22.2.5.1.1 time_get members

#include <locale>
#include <sstream>
#include <testsuite_hooks.h>

// Allow for one leap-second (two if !_GLIBCXX_USE_C99).
void test01()
{
  using namespace std;
  bool test __attribute__((unused)) = true;

  typedef istreambuf_iterator<wchar_t> iterator_type;

  // basic construction and sanity checks.
  locale loc_c = locale::classic();

  // create an istream-derived object, cache the time_get facet
  iterator_type end;
  wistringstream iss;
  iss.imbue(loc_c);
  const time_get<wchar_t>& tim_get =
    use_facet<time_get<wchar_t> >(iss.getloc()); 

  const ios_base::iostate good = ios_base::goodbit;
  ios_base::iostate errorstate = good;

  // create "C" time objects
  const tm time_bday = { 60, 0, 12, 4, 3, 71, 0, 93, 0 };

  iss.str(L"12:00:60 ");
  iterator_type is_it01(iss);
  tm time01;
  errorstate = good;
  tim_get.get_time(is_it01, end, iss, errorstate, &time01);
  VERIFY( time01.tm_sec == time_bday.tm_sec );
  VERIFY( errorstate == ios_base::goodbit );
}

int main()
{
  test01();
  return 0;
}
