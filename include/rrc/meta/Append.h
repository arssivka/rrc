/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once

#include "List.h"

namespace rrc {
    namespace meta {
        namespace detail {
            template<class... L>
            class AppendImplementation;
            template<>
            class AppendImplementation<> {
            public:
                using Type = List<>;
            };
            template<template<class...> class L, class... T>
            class AppendImplementation<L<T...>> {
            public:
                using Type = L<T...>;
            };
            template<template<class...> class L1, class... T1,
                    template<class...> class L2, class... T2, class... Lr>
            class AppendImplementation<L1<T1...>, L2<T2...>, Lr...> {
            public:
                using Type = typename AppendImplementation<L1<T1..., T2...>, Lr...>::Type;
            };
        }
        /**
         * @brief Adds elemetns to the end of the list
         * Example of using: Append<List<float>, List<int, int>, List<int, int, int>>
         * @tparam L - First parameter must be a list to add elements to it. Other parameters are elements to add
         */
        template<class... L> using Append = typename detail::AppendImplementation<L...>::Type;
    }
}