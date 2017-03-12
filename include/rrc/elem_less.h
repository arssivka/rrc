/**
 *  @autor arssivka
 *  @date 3/9/17
 */
#pragma once

#include <cstddef>
#include <utility>

namespace rrc {
    template <class T, size_t N>
    class elem_less {
    public:
        typedef T first_argument_type;
        typedef T second_argument_type;
        typedef bool result_type;

        bool operator() (const T& x, const T& y) const {return std::get<N>(x) < std::get<N>(y);}
    };
}