/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


#include <tuple>

namespace rrc {
    namespace detail {
        template<class T>
        class MetaBackImplementation;
        template<template<class...> class S, class... Ss>
        class MetaBackImplementation<S<Ss...>> {
        public:
            using Type = typename std::tuple_element<sizeof...(Ss) - 1, std::tuple<Ss...>>::type;
        };
    }
    /**
     * @brief Gets the las element of the specified list
     * Exmample of using: Back<List<int, float, bool>>
     * @tparam T List to get element from
     */
    template<class T> using MetaBack = typename detail::MetaBackImplementation<T>::Type;
}