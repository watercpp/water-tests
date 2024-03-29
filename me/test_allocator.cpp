// Copyright 2018-2023 Johan Paulsson
// This file is part of the Water C++ Library. It is licensed under the MIT License.
// See the license.txt file in this distribution or https://watercpp.com/license.txt
//\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_
#include "base.hpp"
#include <water/tests/allocator.hpp>
#include <water/tests/std_allocator.hpp>
namespace me {
namespace {
    auto x = add(
        water::tests::allocator_all,
        water::tests::std_allocator_all
    );
}
}
