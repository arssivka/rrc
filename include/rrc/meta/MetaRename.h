/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


namespace rrc {
    namespace detail {
        template<class A, template<class...> class B>
        class MetaRenameImplementation;

        template<template<class...> class A, class... T,
                template<class...> class B>
        class MetaRenameImplementation<A<T...>, B> {
        public:
            using Type = B<T...>;
        };
    }
    /**
     * @brief Renames class A to class B.
     * It can rename any variadic class template into any other and also non-variadic.
     * Example of using: Rename<std::vector<int>, std::list>
     * @tparam A Source class to rename
     * @tparam B Destination class
     */
    template<class A, template<class...> class B> using MetaRename = typename detail::MetaRenameImplementation<A, B>::Type;
}