/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


namespace rrc {
    namespace detail {
        template<class L>
        class MetaClearListImplementation;
        template<template<class...> class L, class... U>
        class MetaClearListImplementation<L<U...>> {
        public:
            using Type = L<>;
        };
    }
    /**
     * @brief Deletes all the elements from list.
     * Example of using: Clear<List<int,int,int,int>>
     * @tparam L List to clear.
     */
    template<class L> using MetaClearList = typename detail::MetaClearListImplementation<L>::Type;
}