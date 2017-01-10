/**
 *  @autor arssivka
 *  @date 12/13/16
 */

#pragma once


#include <type_traits>
#include <cstddef>
#include <array>
#include "MetaFunctions.h"

namespace rrc {
    namespace meta {
        template<class T, T... Vals>
        struct ArrayGenerator {
            static constexpr size_t size = sizeof...(Vals);
            static constexpr std::array<T, sizeof...(Vals)> data{Vals...};
        };


        template<class T, T... Vals>
        struct PackedArrayGenerator {
            static_assert(std::is_integral<T>::value, "Generator can create arrays of integral types only");
            using PackedGenerator = Packer<ArrayGenerator<T>, meta::IntegralSequence<T, Vals...>>;
            static constexpr size_t size = PackedGenerator::size;
            constexpr static std::array<T, size> data = PackedGenerator::data;
        };
    }
}


