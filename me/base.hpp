// Copyright 2018 Johan Paulsson
// This file is part of the Water C++ Library. It is licensed under the MIT License.
// See the license.txt file in this distribution or https://watercpp.com/license.txt
//\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_
#ifndef ME_BASE_HPP
#define ME_BASE_HPP
#if defined(DEBUG) || defined(_DEBUG)
    #define WATER_DEBUG
#endif
#define WATER_TEST_FAILED(file, line, function, code) \
    ::water::trace() << "___water_test failed " << file << ':' << line << ' ' << function << ' ' << code; \
    ___water_breakpoint(); \
    ::water::throw_if< ::me::exception>(); // aborts if exceptions are disabled
#include <water/water.hpp>
#include <water/test.hpp>
#include <water/trace.hpp>
#include <water/throw_if.hpp>
//#include <water/tests/mess.hpp>
#include "function.hpp"
namespace me {

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

template<typename function_, typename ...list_> add_return add(function_&& a, list_&&... list) {
    add(function{static_cast<function_&&>(a)});
    add(static_cast<list_&&>(list)...);
    return {};
}

// run runs everything added to add

bool run(unsigned thread_count = 0);
bool run(char const*const* begin, char const*const* end);

}
#endif
