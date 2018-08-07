// Copyright 2018 Johan Paulsson
// This file is part of the Water C++ Library. It is licensed under the MIT License.
// See the license.txt file in this distribution or https://watercpp.com/license.txt
//\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_
#include "base.hpp"
namespace me {

struct test_test_1 {
	bool operator()() {
		//trace() << "test_test_1";
		bool a = true; // avoid warning C4127: conditional expression is constant
		___water_test(a);
		return false;
		}
	};

int test_test_2() {
	//trace() << "test_test_2";
	bool a = true;
	___water_test(a);
	return 0;
	}

namespace {
	auto x = add(
		test_test_1{},
		test_test_2,
		[] {
			//trace() << "test_test_3";
			bool a = true;
			___water_test(a);
			}
		);
	}
}
