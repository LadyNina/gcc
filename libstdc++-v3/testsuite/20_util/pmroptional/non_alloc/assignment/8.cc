// { dg-options "-std=gnu++17" }
// { dg-do compile }

// Copyright (C) 2018 Free Software Foundation, Inc.
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

struct X
{
  ~X();
};

struct Y
{
  Y& operator=(const Y&) = default;
  Y& operator=(Y&&);
  Y(const Y&) = default;
  Y(Y&&) = default;
};

struct Z
{
  Z& operator=(const Z&);
  Z& operator=(Z&&) = default;
  Z(const Z&) = default;
};

struct Y2
{
  Y2& operator=(const Y2&) = default;
  Y2& operator=(Y2&&);
};

struct Z2
{
  Z2& operator=(const Z2&);
  Z2& operator=(Z2&&) = default;
};

static_assert(std::is_trivially_copy_assignable_v<std::pmr::optional<int>>);
static_assert(std::is_trivially_move_assignable_v<std::pmr::optional<int>>);
static_assert(!std::is_trivially_copy_assignable_v<std::pmr::optional<X>>);
static_assert(!std::is_trivially_move_assignable_v<std::pmr::optional<X>>);
static_assert(std::is_trivially_copy_assignable_v<std::pmr::optional<Y>>);
static_assert(!std::is_trivially_move_assignable_v<std::pmr::optional<Y>>);
static_assert(!std::is_trivially_copy_assignable_v<std::pmr::optional<Z>>);
static_assert(std::is_trivially_move_assignable_v<std::pmr::optional<Z>>);
static_assert(std::is_trivially_copy_assignable_v<Y2>);
static_assert(!std::is_trivially_move_assignable_v<Y2>);
static_assert(!std::is_trivially_copy_assignable_v<std::pmr::optional<Y2>>);
static_assert(!std::is_trivially_move_assignable_v<std::pmr::optional<Y2>>);
static_assert(!std::is_trivially_copy_assignable_v<Z2>);
static_assert(std::is_trivially_move_assignable_v<Z2>);
static_assert(!std::is_trivially_copy_assignable_v<std::pmr::optional<Z2>>);
static_assert(!std::is_trivially_move_assignable_v<std::pmr::optional<Z2>>);


struct S {
  S(const S&&) = delete;
  S& operator=(const S&) = default;
};
static_assert(std::is_trivially_copy_assignable_v<S>);

union U {
  char dummy;
  S s;
};
static_assert(std::is_trivially_copy_assignable_v<U>);

static_assert(!std::is_trivially_copy_assignable_v<std::pmr::optional<S>>);
static_assert(!std::is_copy_assignable_v<std::pmr::optional<S>>);

struct S2 {
  S2(S2&&) = delete;
  S2& operator=(const S2&) = default;
};
static_assert(std::is_trivially_move_assignable_v<S2>);

union U2 {
  char dummy;
  S2 s;
};
static_assert(std::is_trivially_move_assignable_v<U2>);

static_assert(!std::is_trivially_move_assignable_v<std::pmr::optional<S2>>);
static_assert(!std::is_move_assignable_v<std::pmr::optional<S2>>);
