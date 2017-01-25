/**
 *  @autor arssivka
 *  @date 1/25/17
 */

#pragma once


#include <cstddef>
#include "MetaIntegralSequence.h"

namespace rrc {
    namespace detail {
        template<class T, size_t N, T... Ts>
        struct MetaGenerateSequenceImplementation {
            static_assert(N > 0, "Can't generate sequence with negative length");
            using Type = typename MetaGenerateSequenceImplementation<T, N - 1, N - 1, Ts...>::Type;
        };

        template<class T, T... Ts>
        struct MetaGenerateSequenceImplementation<T, 0, Ts...> {
            using Type = MetaIntegralSequence<T, Ts...>;
        };
    }

    // TODO: Documentation and tests
    template <class T, size_t N>
    using MetaGenerateSequence = typename detail::MetaGenerateSequenceImplementation<T, N>::Type;
}