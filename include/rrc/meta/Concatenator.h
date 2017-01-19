/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


#include "Back.h"
#include "Length.h"
#include "If.h"

namespace rrc {
    namespace meta {
        namespace detail {
            template<bool I, class... Ts>
            class ConcatenatorImplementation;
            template<template<class...> class R, template<class...> class S, class... Rs, class First, class... Ss, class... Os>
            class ConcatenatorImplementation<false, R<Rs...>, S<First, Ss...>, Os...> {
            public:
                using Type = typename rrc::meta::If<std::is_same<First, rrc::meta::Back<R<Rs...>>>::value,
                        typename ConcatenatorImplementation<false, R<Rs...>, S<Ss...>, Os...>::Type,
                        typename ConcatenatorImplementation<false, R<Rs..., First>, S<Ss...>, Os...>::Type>;
            };
            template<template<class...> class R, class... Ss,
                    template<class...> class S, class First, class... Os>
            class ConcatenatorImplementation<false, R<>, S<First, Ss...>, Os...> {
            public:
                using Type = typename ConcatenatorImplementation<false, R<First>, S<Ss...>, Os...>::Type;

            };
            template<template<class...> class R, template<class...> class S, class... Rs, class... Os>
            class ConcatenatorImplementation<false, R<Rs...>, S<>, Os...> {
            public:
                using Type = typename rrc::meta::If<Length<Os...>::value == 0,
                        R<Rs...>,
                        typename ConcatenatorImplementation<false, R<Rs...>, Os...>::Type>;
            };
            template<template<class...> class R, class... Rs>
            class ConcatenatorImplementation<false, R<Rs...>> {
            public:
                using Type = R<Rs...>;
            };
            template<template<class...> class R, class... Ts, class... Os>
            class ConcatenatorImplementation<true, R<Ts...>, Os...> {
            public:
                using Type = typename ConcatenatorImplementation<false, R<>, R<Ts...>, Os...>::Type;
            };
        }
        /**
         * @brief Unites a bunch of lists into one. Also transforms successively repeated types in the lists into one
         * Example of using: Concatenator<List<int, bool>, List<>, List<bool, bool, double>>
         * @tparam Ts - Bunch of lists to unite
         */
        template <class... Ts>
        using Concatenator = typename detail::ConcatenatorImplementation<true, Ts...>::Type;
    }
}