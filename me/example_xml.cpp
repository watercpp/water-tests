// Copyright 2018-2022 Johan Paulsson
// This file is part of the Water C++ Library. It is licensed under the MIT License.
// See the license.txt file in this distribution or https://watercpp.com/license.txt
//\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_
#include "base.hpp"
#include <water/xml/examples/basic.hpp>
#include <water/xml/examples/iterators.hpp>
#include <water/xml/examples/reading_from_text.hpp>
#include <water/xml/examples/writing_to_text.hpp>
namespace me {
namespace {
    auto x = add([]{
        namespace examples = water::xml::examples;
        water::vector<char> text;
        
        text = examples::basic::example();
        ___water_test(!text.empty());
        
        ___water_test(examples::iterators::iterator_ranges());
        ___water_test(examples::iterators::plain_iterators());
        
        ___water_test(examples::reading_from_text::basic1());
        ___water_test(examples::reading_from_text::basic2());
        ___water_test(examples::reading_from_text::parse_in_place());
        ___water_test(examples::writing_to_text::example1());
        ___water_test(examples::writing_to_text::example2());
        
    });
}
}
