/**
 *  @autor arssivka
 *  @date 12/13/16
 */

#pragma once


#include <type_traits>
#include <cstddef>
#include <array>
#include "rrc/meta.h"

namespace rrc {
    template<class T, T... Vals>
    struct MetaArrayGenerator {
        static constexpr size_t size = sizeof...(Vals);
        static const std::array<T, sizeof...(Vals)> data;
    };

    template<class T, T... Vals>
    const std::array<T, sizeof...(Vals)> MetaArrayGenerator<T, Vals...>::data{Vals...};
}


