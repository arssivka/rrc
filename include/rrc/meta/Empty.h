/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


namespace rrc {
    namespace meta {
        namespace detail {
            template<class L>
            class EmptyImplementation;
            template<template<class...> class L, class... U>
            class EmptyImplementation<L<U...>> {
            public:
                constexpr static bool value = sizeof...(U) == 0;
            };
        }
        /**
         * @brief Checks if the specified list is empty or not
         * Example of using: Empty<List<int, int, int, int>>::value
         * @tparam L List to check.
         */
        template<class L> using Empty = detail::EmptyImplementation<L>;
    }
}