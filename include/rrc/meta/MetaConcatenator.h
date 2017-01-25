/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


#include "MetaBack.h"
#include "MetaLength.h"
#include "MetaIf.h"

namespace rrc {
    namespace detail {
        template<bool I, class... Ts>
        class MetaConcatenatorImplementation;

        template<template<class...> class R,
                template<class...> class S, class... Rs, class First, class... Ss, class... Os>
        class MetaConcatenatorImplementation<false, R<Rs...>, S<First, Ss...>, Os...> {
        public:
            using Type = typename rrc::MetaIf<std::is_same<First, MetaBack<R<Rs...>>>::value,
                    typename MetaConcatenatorImplementation<false, R<Rs...>, S<Ss...>, Os...>::Type,
                    typename MetaConcatenatorImplementation<false, R<Rs..., First>, S<Ss...>, Os...>::Type>;
        };

        template<template<class...> class R, class... Ss,
                template<class...> class S, class First, class... Os>
        class MetaConcatenatorImplementation<false, R<>, S<First, Ss...>, Os...> {
        public:
            using Type = typename MetaConcatenatorImplementation<false, R<First>, S<Ss...>, Os...>::Type;

        };

        template<template<class...> class R,
                template<class...> class S, class... Rs, class... Os>
        class MetaConcatenatorImplementation<false, R<Rs...>, S<>, Os...> {
        public:
            using Type = typename rrc::MetaIf<MetaLength<Os...>::value == 0,
                    R<Rs...>,
                    typename MetaConcatenatorImplementation<false, R<Rs...>, Os...>::Type>;
        };

        template<template<class...> class R, class... Rs>
        class MetaConcatenatorImplementation<false, R<Rs...>> {
        public:
            using Type = R<Rs...>;
        };

        template<template<class...> class R, class... Ts, class... Os>
        class MetaConcatenatorImplementation<true, R<Ts...>, Os...> {
        public:
            using Type = typename MetaConcatenatorImplementation<false, R<>, R<Ts...>, Os...>::Type;
        };
    }
    /**
     * @brief Unites a bunch of lists into one. Also transforms successively repeated types in the lists into one
     * Example of using: Concatenator<List<int, bool>, List<>, List<bool, bool, double>>
     * @tparam Ts - Bunch of lists to unite
     */
    template<class... Ts>
    using MetaConcatenator = typename detail::MetaConcatenatorImplementation<true, Ts...>::Type;
}