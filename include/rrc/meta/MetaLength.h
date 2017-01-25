/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


#include <cstddef>
#include <type_traits>

namespace rrc {
    template<class... T> using MetaLength = typename std::integral_constant<size_t, sizeof...(T)>;
}