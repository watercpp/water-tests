// Copyright 2018 Johan Paulsson
// This file is part of the Water C++ Library. It is licensed under the MIT License.
// See the license.txt file in this distribution or https://watercpp.com/license.txt
//\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_
#ifndef ME_CSTRING_HPP
#define ME_CSTRING_HPP
namespace me {

class cstring {
	char const
		*mybegin = 0,
		*myend = 0;
	public:
		cstring() = default;
		explicit cstring(char const *a) :
			mybegin{a},
			myend{a}
			{
			if(myend && *myend)
				while(*++myend)
					;
			}
		char const* begin() const {
			return mybegin;
			}
		char const* end() const {
			return myend;
			}
	};

inline bool operator==(cstring a, cstring b) {
	if(a.end() - a.begin() != b.end() - b.begin())
		return false;
	auto
		ai = a.begin(),
		bi = b.begin();
	while(ai != a.end() && *ai == *bi++)
		++ai;
	return ai == a.end();
	}

inline bool operator!=(cstring a, cstring b) {
	return !(a == b);
	}

}
#endif
