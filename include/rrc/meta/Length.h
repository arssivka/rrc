/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


#include <cstddef>
#include <type_traits>

namespace rrc {
    namespace meta {
        template<class... T> using Length = typename std::integral_constant<size_t, sizeof...(T)>;
    }
}