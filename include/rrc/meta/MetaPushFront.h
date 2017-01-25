/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


namespace rrc {
    namespace detail {
        template<class L, class T>
        class MetaPushFrontImplementation;

        template<template<class...> class L, class... U, class... T>
        class MetaPushFrontImplementation<L<U...>, T...> {
        public:
            using Type = L<T..., U...>;
        };
    }
    /**
     * @brief Adds an element to the front of the List.
     * Example of using: PushFront<List<float>, int>
     * @tparam L List for adding the element.
     * @tparam T Element to add.
     */
    template<class L, class T> using MetaPushFront = typename detail::MetaPushFrontImplementation<L, T>::Type;
}