/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


namespace rrc {
    namespace meta {
        namespace detail {
            template<class L>
            class PopFrontImplementation;
            template<template<class...> class L, class... U, class T>
            class PopFrontImplementation<L<T, U...>> {
            public:
                using Type = L<U...>;
            };
        }
        /**
         * @brief Pops the front element from the list.
         * Example of using: PopFront<List<float, int>>
         * @tparam L List to pop element from.
         */
        template<class L> using PopFront = typename detail::PopFrontImplementation<L>::Type;
    }
}