/**
 *  @autor arssivka
 *  @date 1/25/17
 */

#pragma once


#include <type_traits>
#include <cstddef>

namespace rrc {
    template <class Seq>
    class MetaSequenceSize;

    template <class T, template <class, T...> class Seq, T... Ts>
    class MetaSequenceSize<Seq<T, Ts...>>
            : public std::integral_constant<size_t, sizeof...(Ts)> {};
}