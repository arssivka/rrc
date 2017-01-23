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
    namespace meta {
        template<class T, T... Vals>
        struct ArrayGenerator {
            static constexpr size_t size = sizeof...(Vals);
            static const std::array<T, sizeof...(Vals)> data;
        };

        template<class T, T... Vals>
        const std::array<T, sizeof...(Vals)> ArrayGenerator<T, Vals...>::data{Vals...};
    }
}


