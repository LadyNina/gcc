// { dg-options "-std=gnu++20" }
// { dg-do compile }

// Copyright (C) 2016-2018 Free Software Foundation, Inc.
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

#include "../../../../../include/std/pmroptional"

// Swappable.
struct A { };

static_assert( std::is_nothrow_swappable_v<A> );
// TODO : no except not implemented yet
//static_assert( std::is_nothrow_swappable_v<std::pmr::optional<A>> );

// Swappable, but might throw.
struct B { };
void swap(B&, B&) noexcept(false);

static_assert( std::is_swappable_v<std::pmr::optional<B>> );

// TODO : no except not implemented yet
//static_assert( !std::is_nothrow_swappable_v<std::pmr::optional<B>> );

// Not swappable, and optional<C> not swappable via the generic std::swap.
struct C { };
void swap(C&, C&) = delete;

static_assert( !std::is_swappable_v<std::pmr::optional<C>> );

// Not swappable, and optional<D> not swappable via the generic std::swap.
struct D { D(D&&) = delete; };

static_assert( !std::is_swappable_v<std::pmr::optional<D>> );
