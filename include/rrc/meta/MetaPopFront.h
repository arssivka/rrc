/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


namespace rrc {
    namespace detail {
        template<class L>
        class MetaPopFrontImplementation;

        template<template<class...> class L, class... U, class T>
        class MetaPopFrontImplementation<L<T, U...>> {
        public:
            using Type = L<U...>;
        };
    }
    /**
     * @brief Pops the front element from the list.
     * Example of using: PopFront<List<float, int>>
     * @tparam L List to pop element from.
     */
    template<class L> using MetaPopFront = typename detail::MetaPopFrontImplementation<L>::Type;
}