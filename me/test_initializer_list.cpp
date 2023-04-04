// Copyright 2023 Johan Paulsson
// This file is part of the Water C++ Library. It is licensed under the MIT License.
// See the license.txt file in this distribution or https://watercpp.com/license.txt
//\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_
#include "base.hpp"
// skip this for intel "classic" compiler
#if !defined(__INTEL_COMPILER) && !defined(__ICC) && !defined(__ICL)
#include <water/tests/no_initializer_list.hpp>
namespace me {
namespace {
    auto x = add(
        water::tests::no_initializer_list_all
    );
}
}
#endif
