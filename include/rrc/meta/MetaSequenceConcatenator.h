/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


#include "MetaBackSequenceElement.h"
#include "MetaLength.h"

namespace rrc {
    namespace detail {
        template<bool I, class... Ts>
        class MetaSequenceConcatenatorImplementation;

        template<class T, template<class, T...> class R,
                template<class, T...> class S, T... Rs, T First, T... Ss, class... Os>
        class MetaSequenceConcatenatorImplementation<false, R<T, Rs...>, S<T, First, Ss...>, Os...> {
        public:
            using Type = typename rrc::MetaIf<First == MetaBackSequenceElement<R<T, Rs...>>::value,
                    typename MetaSequenceConcatenatorImplementation<false, R<T, Rs...>, S<T, Ss...>, Os...>::Type,
                    typename MetaSequenceConcatenatorImplementation<false, R<T, Rs..., First>, S<T, Ss...>, Os...>::Type>;
        };

        template<class T, template<class, T...> class R, T... Ss,
                template<class, T...> class S, T First, class... Os>
        class MetaSequenceConcatenatorImplementation<false, R<T>, S<T, First, Ss...>, Os...> {
        public:
            using Type = typename MetaSequenceConcatenatorImplementation<false, R<T, First>, S<T, Ss...>, Os...>::Type;

        };

        template<class T, template<class, T...> class R,
                template<class, T...> class S, T... Rs, class... Os>
        class MetaSequenceConcatenatorImplementation<false, R<T, Rs...>, S<T>, Os...> {
        public:
            using Type = typename rrc::MetaIf<MetaLength<Os...>::value == 0,
                    R<T, Rs...>,
                    typename MetaSequenceConcatenatorImplementation<false, R<T, Rs...>, Os...>::Type>;
        };

        template<class T, template<class, T...> class R, T... Rs>
        class MetaSequenceConcatenatorImplementation<false, R<T, Rs...>> {
        public:
            using Type = R<T, Rs...>;
        };

        template<class T, template<class, T...> class R, T... Ts, class... Os>
        class MetaSequenceConcatenatorImplementation<true, R<T, Ts...>, Os...> {
        public:
            using Type = typename MetaSequenceConcatenatorImplementation<false, R<T>, R<T, Ts...>, Os...>::Type;
        };
    }
    /**
     * @brief Unites a bunch of sequences into one. Also transforms successively repeated numbers in the sequences into one
     * Example of using: SequenceConcatenator<IntegralSequence<short, 1, 2, 2, 3>, IntegralSequence<short, 4, 5, 5, 5>,
     * IntegralSequence<short, 6, 6, 6>>
     * @tparam Ts - Bunch of sequences to unite
     */
    template<class... Ts>
    using MetaSequenceConcatenator = typename detail::MetaSequenceConcatenatorImplementation<true, Ts...>::Type;
}