// Copyright 2023 Johan Paulsson
// This file is part of the Water C++ Library. It is licensed under the MIT License.
// See the license.txt file in this distribution or https://watercpp.com/license.txt
//\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_
#include "base.hpp"
#include <water/tests/begin_end.hpp>
#include <water/tests/size_from.hpp> // not begin_end but kind of related
namespace me {
namespace {
    auto x = add(
        water::tests::begin_end_all
    );
}
}
