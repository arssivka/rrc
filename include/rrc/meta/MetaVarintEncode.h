/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once

#include <cstdint>
#include "MetaAppendSequence.h"
#include "MetaIntegralSequence.h"
#include "MetaIf.h"
#include "IterationTags.h"

namespace rrc {
    namespace detail {
        // TODO: Documentation and tests
        template<class T, T Value, class Tag>
        class MetaVarintEncodeImplementation {
        public:
            using Type = rrc::MetaAppendSequence<
                    rrc::MetaIf < (Value > 127),
                    rrc::MetaIntegralSequence<uint8_t, ((Value & 127) | 128)>,
                    rrc::MetaIntegralSequence<uint8_t, (Value & 127)>>,
            typename MetaVarintEncodeImplementation<T, (Value >> 7), IterationTraits<(Value >> 7)>>::Type>;
        };

        template<class T, T Value>
        class MetaVarintEncodeImplementation<T, Value, FinalIterationTag> {
        public:
            using Type = MetaIntegralSequence<uint8_t>;
        };
    }
    template<class T, T Value>
    using MetaVarintEncode = typename detail::MetaVarintEncodeImplementation<T, Value, IterationTraits < Value>>::Type;
}