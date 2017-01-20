/**
 *  @autor tekatod
 *  @date 1/20/17
 */
#pragma once

#include <cstddef>

namespace rrc {
    namespace meta {
        class IterationTag {
        };

        class FinalIterationTag : public IterationTag {
        };
        namespace detail {
            template<size_t N>
            class IterationTraitsImplementation {
            public:
                using Tag = IterationTag;
            };

            template<>
            class IterationTraitsImplementation<0> {
            public:
                using Tag = FinalIterationTag;
            };
        }
        template <size_t N>
        using IterationTraits = typename detail::IterationTraitsImplementation<N>::Tag;
    }
}
