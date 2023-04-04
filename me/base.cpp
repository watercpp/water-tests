// Copyright 2018-2023 Johan Paulsson
// This file is part of the Water C++ Library. It is licensed under the MIT License.
// See the license.txt file in this distribution or https://watercpp.com/license.txt
//\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_
#include "base.hpp"
#include <water/atomic.hpp>
#include <water/numbers/read.hpp>
#include <water/threads/thread.hpp>
#include <water/vector.hpp>
namespace me {


unsigned constexpr thread_count_default = 8;


void trace_test_failed(char const* file, unsigned line, char const* function, char const* code) {
    trace << "___water_test failed " << water::xtr::size<1024> << file << ':' << line << ' ' << function << ' ' << code;
}


class function_list {
    
    water::vector<function> my;
    bool mysolo = false;
    water::atomic<size_t> myat{};
    
    public:
    
        void add(function&& f) {
            if(!mysolo)
                my.emplace_back(static_cast<function&&>(f));
        }
        
        void solo(function&& f) {
            if(!mysolo)
                my.clear();
            mysolo = true;
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
        
        bool solo() const {
            return mysolo;
        }

};
static function_list functions;


void add(function&& f) {
    return functions.add(static_cast<function&&>(f));
}

void solo(function&& f) {
    return functions.solo(static_cast<function&&>(f));
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
        thread_count = thread_count_default;
    if(thread_count > functions.size())
        thread_count = static_cast<unsigned>(functions.size());
    if(thread_count <= 1)
        run();
    else {
        water::vector<water::threads::join_t> threads;
        unsigned at = 0;
        while(water::threads::run(run, *threads.push_back({})) && ++at != thread_count)
            ;
        if(!at) {
            trace << "error: could not start any threads";
            return false;
        }
        while(at)
            join(threads[--at]);
    }
    if(run.error()) {
        trace << "failed :(";
        return false;
    }
    trace << "success :)";
    if(functions.solo())
        trace << "solo mode! all tests did not run!";
    return true;
}


}
