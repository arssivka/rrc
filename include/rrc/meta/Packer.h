/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


#include "If.h"
#include "Length.h"
#include "Pack.h"

namespace rrc {
    namespace meta {
        namespace detail {
            template<bool I, class... Ss>
            class PackerImplementation;
            template<class T, template<class, T...> class R,
                    template<class, T...> class V, T... Result, T First, T Second, T... Values, class... Ss>
            class PackerImplementation<false, R<T, Result...>, V<T, First, Second, Values...>, Ss...> {
            public:
                using Type = typename PackerImplementation<false, R<T, Result...,
                        Pack<T, First, Second>::value>, V<T, Values...>, Ss...>::Type;
            };
            template<class T, template<class, T...> class R,
                    template<class, T...> class V, T... Result, T Last, class... Ss>
            class PackerImplementation<false, R<T, Result...>, V<T, Last>, Ss...> {
            public:
                using Type = R<T, Result..., Pack<T, 0, Last>::value>;
            };
            template<class T, template<class, T...> class R,
                    template<class, T...> class V, T... Result, class... Ss>
            class PackerImplementation<false, R<T, Result...>, V<T>, Ss...> {
            public:
                using Type = meta::If<meta::Length<Ss...>::value == 0, R<T, Result...>,
                        typename PackerImplementation<false, R<T, Result...>, Ss...>::Type>;
            };
            template<class T, template<class, T...> class R, T... Rs>
            class PackerImplementation<false, R<T, Rs...>> {
            public:
                using Type = R<T, Rs...>;
            };
            template<class T, template<class, T...> class R, T... Ts, class... Os>
            class PackerImplementation<true, R<T, Ts...>, Os...> {
            public:
                using Type = typename PackerImplementation<false, R<T>, R<T, Ts...>, Os...>::Type;
            };
        }
        /**
         * @brief Packs the values from IntegralSequence pair by pair into an array. If there is no pair for value,
         * it just stays at it is.
         * Example of using: Packer<ArrayGenerator<short>, IntegralSequence<short, 1, 2, 3>>
         * @tparam Values First parameter is an ArrayGenerator, second is an IntegralSequence with the values to pack
         */
        template <class... Values>
        using Packer = typename detail::PackerImplementation<true, Values...>::Type;
    }
}