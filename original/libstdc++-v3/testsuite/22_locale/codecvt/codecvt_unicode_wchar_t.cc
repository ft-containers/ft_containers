// Copyright (C) 2020-2023 Free Software Foundation, Inc.
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

// { dg-do run { target c++11 } }

#include "codecvt_unicode.h"

#include <codecvt>

using namespace std;

void
test_utf8_utf32_codecvts ()
{
#if __SIZEOF_WCHAR_T__ == 4
  auto cvt_ptr = to_unique_ptr (new codecvt_utf8<wchar_t> ());
  test_utf8_utf32_codecvts (*cvt_ptr);
#endif
}

void
test_utf8_utf16_codecvts ()
{
#if __SIZEOF_WCHAR_T__ >= 2
  auto cvt_ptr = to_unique_ptr (new codecvt_utf8_utf16<wchar_t> ());
  test_utf8_utf16_cvts (*cvt_ptr);
#endif
}

void
test_utf8_ucs2_codecvts ()
{
#if __SIZEOF_WCHAR_T__ == 2
  auto cvt_ptr = to_unique_ptr (new codecvt_utf8<wchar_t> ());
  test_utf8_ucs2_cvts (*cvt_ptr);
#endif
}

int
main ()
{
  test_utf8_utf32_codecvts ();
  test_utf8_utf16_codecvts ();
  test_utf8_ucs2_codecvts ();
}
