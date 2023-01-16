// { dg-do run }
// { dg-additional-options "-pthread" { target pthread } }
// { dg-require-effective-target c++11 }
// { dg-require-gthreads "" }

// Copyright (C) 2009-2022 Free Software Foundation, Inc.
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


#include <thread>
#include <system_error>
#include <testsuite_hooks.h>

bool f_was_called = false;

void f()
{
  f_was_called = true;
}

// thread non-variadic cons, c++ function
// thread join
// thread join postcondition function called correctly
// no errors
void test06()
{
  try
  {
    std::thread t(f);
    t.join();
    VERIFY( f_was_called );
  }
  catch (const std::system_error&)
  {
    VERIFY( false );
  }
  catch (...)
  {
    VERIFY( false );
  }
}

int main()
{
  test06();
  return 0;
}
