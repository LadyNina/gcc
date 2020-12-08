// { dg-options "-std=gnu++17" }
// { dg-do run }

// Copyright (C) 2013-2018 Free Software Foundation, Inc.
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

#include <testsuite_hooks.h>
#include "../../../../../include/std/pmroptional"

struct tracker
{
  tracker(int value) : value(value) { ++count; }
  ~tracker() { --count; }

  tracker(tracker const& other) : value(other.value) { ++count; }
  tracker(tracker&& other) : value(other.value)
  {
    other.value = -1;
    ++count;
  }

  tracker& operator=(tracker const&) = default;
  tracker& operator=(tracker&&) = default;

  int value;

  static int count;

  typedef std::pmr::polymorphic_allocator<void> allocator_type;

  tracker(std::allocator_arg_t,allocator_type, int x)
   : tracker(x){}
  tracker(std::allocator_arg_t,allocator_type, const tracker& other)
     : tracker(other){}
  tracker(std::allocator_arg_t,allocator_type, tracker&& other)
       : tracker(std::move(other)){}

};

int tracker::count = 0;

struct exception { };

struct throwing_copy
{
  throwing_copy() = default;
  throwing_copy(throwing_copy const&) { throw exception {}; }
};

int main()
{
  // [20.5.4.1] Constructors

  {
    std::pmr::optional<long> o;
    auto copy = o;
    VERIFY( !copy );
    VERIFY( !o );
  }

  {
    const long val = 0x1234ABCD;
    std::pmr::optional<long> o { std::in_place, val};
    auto copy = o;
    VERIFY( copy );
    VERIFY( *copy == val );
    VERIFY( o && o == val );
  }

  {
    std::pmr::optional<tracker> o;
    auto copy = o;
    VERIFY( !copy );
    VERIFY( tracker::count == 0 );
    VERIFY( !o );
  }

  {
    std::pmr::optional<tracker> o { std::in_place, 333 };
    auto copy = o;
    VERIFY( copy );
    VERIFY( copy->value == 333 );
    VERIFY( tracker::count == 2 );
    VERIFY( o && o->value == 333 );
  }

  enum outcome { nothrow, caught, bad_catch };

  {
    outcome result = nothrow;
    std::pmr::optional<throwing_copy> o;

    try
    {
      auto copy = o;
    }
    catch(exception const&)
    { result = caught; }
    catch(...)
    { result = bad_catch; }

    VERIFY( result == nothrow );
  }

  {
    outcome result = nothrow;
    std::pmr::optional<throwing_copy> o { std::in_place };

    try
    {
      auto copy = o;
    }
    catch(exception const&)
    { result = caught; }
    catch(...)
    { result = bad_catch; }

    VERIFY( result == caught );
  }

  {
      std::optional<tracker> o;
      std::pmr::optional<tracker> copy = o;
      VERIFY( !copy );
      VERIFY( !o );
  }
  VERIFY( tracker::count == 0 );
}
