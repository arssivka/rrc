/**
 *  @autor arssivka
 *  @date 1/20/17
 */

#pragma once


#include "MetaIntegralSequence.h"
#include "MetaVarintEncode.h"

namespace rrc {
    namespace detail {
        template<class T, T... Ts>
        class MetaVarintEncodeSequenceImplementation {
        public:
            using Type = MetaIf<(sizeof...(Ts) != 0),
                    MetaAppendSequence<MetaVarintEncode<T, Ts>...>,
                    MetaIntegralSequence<uint8_t>>;
        };

        template<class T>
        class MetaVarintEncodeSequenceImplementation<T> {
        public:
            using Type = MetaIntegralSequence<uint8_t>;
        };
    }

    template<class T, T... Ts>
    using MetaVarintEncodeSequence = typename detail::MetaVarintEncodeSequenceImplementation<T, Ts...>::Type;
}