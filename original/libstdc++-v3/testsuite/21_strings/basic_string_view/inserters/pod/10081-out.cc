// { dg-do run { target c++17 } }

// Copyright (C) 2013-2022 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING3.  If not see
// <http://www.gnu.org/licenses/>.

// class basic_istream::sentry

#include <string_view>
#include <ostream>
#include <sstream>
#include <locale>
#include <typeinfo>
#include <testsuite_hooks.h>
#include <testsuite_character.h>

void
test01()
{
  using namespace std;

  using __gnu_test::pod_ushort;
  typedef basic_string_view<pod_ushort> 	string_type;
  typedef basic_stringbuf<pod_ushort> 	stringbuf_type;
  typedef basic_ostream<pod_ushort> 	ostream_type;

  string_type str;
  stringbuf_type strbuf01;
  ostream_type stream(&strbuf01);

  try
    {
      stream << str;
    }
  catch (std::bad_cast& obj)
    {
      // Ok, throws bad_cast because locale has no ctype facet.
    }
  catch (...)
    {
      VERIFY( false );
    }

  const std::locale loc(std::locale::classic(), new std::ctype<pod_ushort>);
  stream.imbue(loc);
  try
    {
      stream << str;
    }
  catch (...)
    {
      VERIFY( false );
    }
}

int
main()
{
  test01();

  return 0;
}
