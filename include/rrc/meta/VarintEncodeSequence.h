/**
 *  @autor arssivka
 *  @date 1/20/17
 */

#pragma once


#include "IntegralSequence.h"
#include "VarintEncode.h"

namespace rrc {
    namespace meta {
        namespace detail {
            template <class T, T... Ts>
            class VarintEncodeSequenceImplementation {
            public:
                using Type = rrc::meta::If<(sizeof...(Ts) != 0),
                        rrc::meta::AppendSequence<rrc::meta::VarintEncode<T, Ts>...>,
                        rrc::meta::IntegralSequence<uint8_t>>;
            };

            template <class T>
            class VarintEncodeSequenceImplementation<T> {
            public:
                using Type = rrc::meta::IntegralSequence<uint8_t>;
            };
        }

        template <class T, T... Ts>
        using VarintEncodeSequence = typename detail::VarintEncodeSequenceImplementation<T, Ts...>::Type;
    }
}