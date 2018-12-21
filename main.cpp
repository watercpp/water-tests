// Copyright 2018 Johan Paulsson
// This file is part of the Water C++ Library. It is licensed under the MIT License.
// See the license.txt file in this distribution or https://watercpp.com/license.txt
//\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_
#include "me/base.hpp"

char const *const test_args[] = {
	"application",
	"--threads",
	"-12"
	};

int main(int argc, char **argv) {
	auto
		b = static_cast<char const*const*>(argv),
		e = b + (b && argc > 0 ? argc : 0);
	//b = test_args;
	//e = test_args + sizeof(test_args) / sizeof(test_args[0]);
	return !me::run(b, e);
	}
