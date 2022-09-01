// Copyright 2018-2022 Johan Paulsson
// This file is part of the Water C++ Library. It is licensed under the MIT License.
// See the license.txt file in this distribution or https://watercpp.com/license.txt
//\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_
#include "base.hpp"
#include <water/atomic.hpp>
#include <water/numbers/read.hpp>
#include <water/threads/thread.hpp>
#include <water/vector.hpp>
#include "cstring.hpp"
namespace me {

class function_list {
    
    water::vector<function> my;
    water::atomic<size_t> myat{};
    
    public:
    
        void add(function&& f) {
            my.emplace_back(static_cast<function&&>(f));
        }
        
        function const* next() {
            size_t a = myat.load(water::memory_order_relaxed);
            while(!myat.compare_exchange_weak(a, a < my.size() ? a + 1 : a))
                ;
            return a < my.size() ? my.begin() + a : 0;
        }
        
        size_t size() const {
            return my.size();
        }

};
static function_list functions;


void add(function&& f) {
    return functions.add(static_cast<function&&>(f));
}

class run_functions {
    
    water::atomic<bool> myerror{};
    
    public:
        
        void operator()() {
            while(auto function = functions.next()) {
                #ifdef WATER_NO_EXCEPTIONS
                (*function)();
                #else
                try {
                    (*function)();
                }
                catch(exception&) {
                    myerror.store(true);
                }
                #endif
            }
        }
        
        bool error() {
            return myerror.load();
        }
};

bool run(unsigned thread_count) {
    run_functions run;
    if(!thread_count)
        thread_count = 8;
    if(thread_count > functions.size())
        thread_count = static_cast<unsigned>(functions.size());
    if(!thread_count)
        run();
    else {
        water::vector<water::threads::join_t> threads;
        unsigned at = 0;
        while(water::threads::run(run, *threads.push_back({})) && ++at != thread_count)
            ;
        if(!at) {
            trace() << "error: could not start any threads";
            return false;
        }
        while(at)
            join(threads[--at]);
    }
    if(run.error()) {
        trace() << "failed :(";
        return false;
    }
    trace() << "success :)";
    return true;
}

bool run(char const*const* b, char const*const* e) {
    // --threads 123
    unsigned thread_count = 0;
    if(e - b == 3 && cstring(b[1]) == cstring("--threads")) {
        cstring number(b[2]);
        water::numbers::read<unsigned> read{water::numbers::settings{}.base(10)};
        auto end = read(number.begin(), number.end());
        thread_count = read;
        if(end != number.end() || read.any_problem() || !thread_count) {
            trace() << "error: cannot understand the number of threads";
            return false;
        }
    }
    else if(e - b != 1) {
        trace() << "error: command line arguments can be --threads 8 or nothing";
        return false;
    }
    return run(thread_count);
}

}
