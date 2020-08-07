// Copyright 2018 Johan Paulsson
// This file is part of the Water C++ Library. It is licensed under the MIT License.
// See the license.txt file in this distribution or https://watercpp.com/license.txt
//\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_
#include "base.hpp"
#include <water/json/examples/basic.hpp>
#include <water/json/examples/reading_from_text.hpp>
#include <water/json/examples/writing_to_text.hpp>
#include <water/json/examples/indenting.hpp>
#include <water/json/examples/node_tree_1.hpp>
#include <water/json/examples/node_tree_2.hpp>
#include <water/json/examples/values.hpp>
#include <water/json/examples/creating_nodes_1.hpp>
#include <water/json/examples/creating_nodes_2.hpp>
namespace me {
namespace {
    auto x = add([]{
        namespace examples = water::json::examples;
        water::vector<char> text;
        
        text = examples::basic::example();
        ___water_test(!text.empty());
        
        ___water_test(examples::reading_from_text::basic1());
        ___water_test(examples::reading_from_text::basic2());
        ___water_test(examples::reading_from_text::parse_in_place());
        ___water_test(examples::reading_from_text::pedantic_error_checking());
        ___water_test(examples::writing_to_text::basic());
        ___water_test(examples::writing_to_text::escape_all_and_measure_size());
        ___water_test(examples::indenting::basic());
        ___water_test(examples::indenting::indent_nodes());
        ___water_test(examples::indenting::loop_and_minify());
        ___water_test(examples::node_tree_1::example());
        
        text = examples::node_tree_2::loop();
        ___water_test(!text.empty());
    
        ___water_test(examples::values::example());
        
        text = examples::creating_nodes_1::example();
        ___water_test(!text.empty());
        
        text = examples::creating_nodes_2::example();
        ___water_test(!text.empty());
    });
}
}
