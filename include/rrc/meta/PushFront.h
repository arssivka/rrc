/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


namespace rrc {
    namespace meta {
        namespace detail {
            template<class L, class T>
            class PushFrontImplementation;
            template<template<class...> class L, class... U, class... T>
            class PushFrontImplementation<L<U...>, T...> {
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
        template<class L, class T> using PushFront = typename detail::PushFrontImplementation<L, T>::Type;
    }
}