// Copyright 2018-2023 Johan Paulsson
// This file is part of the Water C++ Library. It is licensed under the MIT License.
// See the license.txt file in this distribution or https://watercpp.com/license.txt
//\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_
#ifndef ME_BASE_HPP
#define ME_BASE_HPP

#if defined(DEBUG) || defined(_DEBUG)
    #define WATER_DEBUG
#endif

//#define WATER_NO_STD
//#define WATER_NO_WINDOWS_H
//#define WATER_USE_WATER_THREADS

#define WATER_TEST_FAILED(file, line, function, code) \
    ::me::trace_test_failed(file, line, function, code); \
    ___water_breakpoint(); \
    ::water::throw_if< ::me::exception>(); // aborts if exceptions are disabled

#ifdef WATER_TESTS_INCLUDE
    #include WATER_TESTS_INCLUDE
#endif

#include <water/water.hpp>
#include <water/test.hpp>
#include <water/trace.hpp>
#include <water/throw_if.hpp>
//#include <water/tests/mess.hpp>
#include "function.hpp"
namespace me {

void trace_test_failed(char const* file, unsigned line, char const* function, char const* code);

using water::trace;
using water::size_t;
using water::ptrdiff_t;

struct exception{};

// add is used at program startup, before main

void add(function&&);

struct add_return {};

inline add_return add() {
    return {};
}

template<typename function_, typename ...list_>
add_return add(function_&& a, list_&&... list) {
    add(function{static_cast<function_&&>(a)});
    add(static_cast<list_&&>(list)...);
    return {};
}

// solo is used instead of add to run just the soloed tests, ignoring those added with plain add

void solo(function&&);

inline add_return solo() {
    return {};
}

template<typename function_, typename ...list_>
[[deprecated("change solo to add to run all tests!")]]
add_return solo(function_&& a, list_&&... list) {
    solo(function{static_cast<function_&&>(a)});
    solo(static_cast<list_&&>(list)...);
    return {};
}

// run runs everything added to add

bool run(unsigned thread_count = 0);

}
#endif
