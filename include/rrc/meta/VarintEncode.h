/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once

#include <cstdint>
#include "AppendSequence.h"
#include "IntegralSequence.h"
#include "If.h"
#include "IterationTags.h"

namespace rrc {
    namespace meta {
        namespace detail {
            // TODO: Documentation and tests
            template <class T, T Value, class Tag>
            class VarintEncodeImplementation {
            public:
                using Type = meta::AppendSequence<
                        meta::If<(Value > 127),
                                meta::IntegralSequence<uint8_t, ((Value & 127) | 128)>,
                                meta::IntegralSequence<uint8_t, (Value & 127)>>,
                        typename VarintEncodeImplementation<T, (Value >> 7), IterationTraits<(Value >> 7)>>::Type>;
            };

            template <class T, T Value>
            class VarintEncodeImplementation<T, Value, rrc::meta::FinalIterationTag> {
            public:
                using Type = meta::IntegralSequence<uint8_t>;
            };
        }
        template <class T, T Value>
        using VarintEncode = typename detail::VarintEncodeImplementation<T, Value, IterationTraits<Value>>::Type;
    }
}