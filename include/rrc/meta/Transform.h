/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


namespace rrc {
    namespace meta {
        namespace detail {
            template<template<class...> class F, class L>
            class TransformImplementation;

            template<template<class...> class F,
                    template<class...> class L, class... T>
            class TransformImplementation<F, L<T...>> {
            public:
                using Type = L<F<T>...>;
            };
        }
        /**
         * @brief Takes a functuian and aplies to each element of the list
         * Example of using:
         * template <class A>
         * using AddPointer = typename std::add_pointer<A>::type;
         * Transform<AddPointer , List<int, int, int>>
         * @tparam F Function which must be apllied to elements in the list
         * @tparam L List of the elements to transform
         */
        template<template<class...> class F, class L> using Transform = typename detail::TransformImplementation<F, L>::Type;
    }
}