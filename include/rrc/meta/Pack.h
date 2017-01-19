/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


#include <type_traits>

namespace rrc {
    namespace meta {
        /**
         * @brief Packs to values into one
         * Example of using: Pack<int, 1, 2>
         * @tparam T Type of the values to pack
         * @tparam First First value to pack
         * @tparam Second Second value to pack
         */
        template <class T, T First, T Second>
        class Pack : public std::integral_constant<T, (First << sizeof(T) * 4) | (Second & ((T)-1 >> sizeof(T) * 4))> { };
    }
}