// Copyright 2018 Johan Paulsson
// This file is part of the Water C++ Library. It is licensed under the MIT License.
// See the license.txt file in this distribution or https://watercpp.com/license.txt
//\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_
#ifndef ME_FUNCTION_HPP
#define ME_FUNCTION_HPP
#include "base.hpp"
#include <water/allocator.hpp>
#include <water/swap.hpp>
#include <water/later.hpp>
#include <water/new_here.hpp>
#include <water/types/types.hpp>
namespace me {

class function {

    void *my = 0;
    void (*mydestroy)(void*) = 0;
    void (*mycall)(void*) = 0;

    public:
    
        function() = default;

        function(function const&) = delete;

        function& operator=(function const&) = delete;

        ~function() {
            if(my)
                (*mydestroy)(my);
        }
        
        function(function&& a) :
            my{a.my},
            mydestroy{a.mydestroy},
            mycall{a.mycall}
        {
            a.my = 0;
        }
        
        template<typename function_> explicit function(function_&& a) {
            using no_reference = water::types::no_reference<function_>;
            // change reference to function into pointer
            using type = typename water::types::ifel_type<
                water::types::is_function<no_reference>,
                water::types::to_pointer<no_reference>,
                no_reference
            >::result;
            auto p = water::allocator{}.template allocate<type>();
            auto free = water::later([p]{ water::allocator{}.template free<type>(p); });
            my = new(water::here(p)) type{a};
            mydestroy = &function::template destroy<type>;
            mycall = &function::template call<type>;
            free.dont();
        }
        
        function& operator=(function&& a) {
            swap(a);
            return *this;
        }
        
        void swap(function& a) {
            water::swap_from_swap(my, a.my);
            water::swap_from_swap(mydestroy, a.mydestroy);
            water::swap_from_swap(mycall, a.mycall);
        }
        
        void operator()() const {
            if(my) (*mycall)(my);
        }
        
    private:
    
        template<typename function_> static void destroy(void *pointer) {
            auto a = static_cast<function_*>(pointer);
            a->~function_();
            water::allocator{}.template free<function_>(a);
        }
        
        template<typename function_> static void call(void *pointer) {
            (*static_cast<function_*>(pointer))();
        }
};

inline void swap(function& a, function& b) {
    a.swap(b);
}

}
#endif
