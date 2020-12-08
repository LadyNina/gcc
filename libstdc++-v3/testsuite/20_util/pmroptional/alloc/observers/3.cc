// { dg-options "-std=gnu++20" }
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

struct value_type
{
  typedef std::pmr::polymorphic_allocator<void> allocator_type;

  value_type(std::allocator_arg_t,allocator_type)
  : value_type(){}


  value_type(std::allocator_arg_t,allocator_type, int i)
  : value_type(i){}

  value_type(std::allocator_arg_t,allocator_type, value_type const& other)
    : value_type(other){}

  value_type(){};

  value_type(int _i) : i(_i){};

  value_type(value_type const& other): i(other.i)
      {};

  value_type& operator=(value_type const& other)
  {
    i = other.i;
    return *this;
  }
  int i = 0;
};

int main()
{
  {
    std::pmr::optional<value_type> o { value_type { 51 } };
    VERIFY( o.value().i == 51 );
    VERIFY( o.value().i == (*o).i );
    VERIFY( &o.value().i == &(*o).i );
  }

  {
    enum outcome_type { nothrow, caught, bad_catch };

    outcome_type outcome {};
    std::pmr::optional<value_type> o = std::nullopt;
    bool called = false;
    auto const eat = [&called](int) { called = true; };

    try
    {
      eat(o.value().i);
    }
    catch(std::bad_optional_access const&)
    { outcome = caught; }
    catch(...)
    { outcome = bad_catch; }

    VERIFY( outcome == caught );
    VERIFY( !called );
  }
}
