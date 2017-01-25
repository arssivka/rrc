/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once

#include "MetaList.h"

namespace rrc {
    namespace detail {
        template<class... L>
        class MetaAppendImplementation;

        template<>
        class MetaAppendImplementation<> {
        public:
            using Type = rrc::MetaList<>;
        };

        template<template<class...> class L, class... T>
        class MetaAppendImplementation<L<T...>> {
        public:
            using Type = L<T...>;
        };

        template<template<class...> class L1, class... T1,
                template<class...> class L2, class... T2, class... Lr>
        class MetaAppendImplementation<L1<T1...>, L2<T2...>, Lr...> {
        public:
            using Type = typename MetaAppendImplementation<L1<T1..., T2...>, Lr...>::Type;
        };
    }
    /**
     * @brief Adds elemetns to the end of the list
     * Example of using: Append<List<float>, List<int, int>, List<int, int, int>>
     * @tparam L - First parameter must be a list to add elements to it. Other parameters are elements to add
     */
    template<class... L> using MetaAppend = typename detail::MetaAppendImplementation<L...>::Type;
}