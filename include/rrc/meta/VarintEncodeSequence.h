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
            template <class S>
            class VarintEncodeSequence;

            template <class T, template <class, T...> class S, T... Ts>
            class VarintEncodeSequence<rrc::meta::IntegralSequence<T, Ts...>> {
            public:
                using Type = rrc::meta::AppendSequence<rrc::meta::VarintEncode<T, Ts>...>;
            };
        }

        template <class S>
        using VarintEncode = typename detail::VarintEncodeImplementation<S>::Type;
    }
}