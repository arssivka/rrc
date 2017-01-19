/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


namespace rrc {
    namespace meta {
        namespace detail {
            template<class L>
            class ClearImplementation;
            template<template<class...> class L, class... U>
            class ClearImplementation<L<U...>> {
            public:
                using Type = L<>;
            };
        }
        /**
         * @brief Deletes all the elements from list.
         * Example of using: Clear<List<int,int,int,int>>
         * @tparam L List to clear.
         */
        template<class L> using Clear = typename detail::ClearImplementation<L>::Type;
    }
}