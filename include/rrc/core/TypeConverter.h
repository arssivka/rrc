/**
 *  @autor arssivka
 *  @date 11/28/16
 */

#pragma once


#include <cstdint>
#include <array>
#include "rrc/meta.h"
#include <vector>
#include <list>
#include <cstdint>
#include <numeric>
#include <array>
#include <forward_list>
#include <deque>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>

namespace rrc {
    enum TypeId {
        UNKNOWN_ID = 0,
        INT8_ID = 1,
        INT16_ID = 2,
        INT32_ID = 3,
        INT64_ID = 4,
        FLOAT_ID = 5,
        DOUBLE_ID = 6,
        STRUCTURE_ID = 7,
        INT8_ARRAY_ID = 8,
        INT16_ARRAY_ID = 9,
        INT32_ARRAY_ID = 10,
        INT64_ARRAY_ID = 11,
        FLOAT_ARRAY_ID = 12,
        DOUBLE_ARRAY_ID = 13,
        STRUCTURE_ARRAY_ID = 14,
        COUNT_IDS = 15
    };

    template <class T, T... Vals>
    struct TypeIdSequence {
        using Type = MetaIntegralSequence<T, Vals...>;
    };
    template <class C, class... T> struct ConvertTypeToIdTraits;
    template <class C, class... T>
    using ConvertTypeToId = typename ConvertTypeToIdTraits<C, T...>::Type;
    template <class C> struct ConvertTypeToIdTraits<C, bool> : TypeIdSequence<C, TypeId::INT8_ID> {};
    template <class C> struct ConvertTypeToIdTraits<C, int8_t> : TypeIdSequence<C, TypeId::INT8_ID> {};
    template <class C> struct ConvertTypeToIdTraits<C, int16_t> : TypeIdSequence<C, TypeId::INT16_ID> {};
    template <class C> struct ConvertTypeToIdTraits<C, int32_t> : TypeIdSequence<C, TypeId::INT32_ID> {};
    template <class C> struct ConvertTypeToIdTraits<C, int64_t> : TypeIdSequence<C, TypeId::INT64_ID> {};
    template <class C> struct ConvertTypeToIdTraits<C, float> : TypeIdSequence<C, TypeId::FLOAT_ID> {};
    template <class C> struct ConvertTypeToIdTraits<C, double> : TypeIdSequence<C, TypeId::DOUBLE_ID> {};

    template <class C, class T> struct ConvertContainerTypeToArrayId;
    template <class C> struct ConvertContainerTypeToArrayId<C, bool> : TypeIdSequence<C, TypeId::INT8_ARRAY_ID> {};
    template <class C> struct ConvertContainerTypeToArrayId<C, int8_t> : TypeIdSequence<C, TypeId::INT8_ARRAY_ID> {};
    template <class C> struct ConvertContainerTypeToArrayId<C, int16_t> : TypeIdSequence<C, TypeId::INT16_ARRAY_ID> {};
    template <class C> struct ConvertContainerTypeToArrayId<C, int32_t> : TypeIdSequence<C, TypeId::INT32_ARRAY_ID> {};
    template <class C> struct ConvertContainerTypeToArrayId<C, int64_t> : TypeIdSequence<C, TypeId::INT64_ARRAY_ID> {};
    template <class C> struct ConvertContainerTypeToArrayId<C, float> : TypeIdSequence<C, TypeId::FLOAT_ARRAY_ID> {};
    template <class C> struct ConvertContainerTypeToArrayId<C, double> : TypeIdSequence<C, TypeId::DOUBLE_ARRAY_ID> {};

    template <class C, template<class...> class L, class... Ts> struct ConvertContainerTypeToArrayId<C, L<Ts...>> {
        using Type = MetaIf<MetaLength<Ts...>::value == 1,
                              MetaAppendSequence<ConvertTypeToId<C, MetaDecay<Ts>>...>,
                              MetaAppendSequence<TypeIdSequence<C, TypeId::STRUCTURE_ARRAY_ID>, ConvertTypeToId<C, MetaDecay<Ts>>...>>;
    };

    template <class C, class T, size_t N> struct ConvertTypeToIdTraits<C, T[N]> : ConvertContainerTypeToArrayId<C, MetaDecay<T>> {};
    template<class C, class T, class Alloc>
    struct ConvertTypeToIdTraits<C, std::vector<T, Alloc>>
            : ConvertContainerTypeToArrayId<C, MetaDecay<T>> {};

    template<class C, class T, class Alloc>
    struct ConvertTypeToIdTraits<C, std::deque<T, Alloc>>
            : ConvertContainerTypeToArrayId<C, MetaDecay<T>> {};

    template<class C, class T, class Alloc>
    struct ConvertTypeToIdTraits<C,std::list<T, Alloc>>
            : ConvertContainerTypeToArrayId<C, MetaDecay<T>> {};

    template<class C, class T, class Alloc>
    struct ConvertTypeToIdTraits<C, std::forward_list<T, Alloc>>
            : ConvertContainerTypeToArrayId<C, MetaDecay<T>> {};

    template<class C, class T, class Compare, class Alloc>
    struct ConvertTypeToIdTraits<C, std::set<T, Compare, Alloc>>
            : ConvertContainerTypeToArrayId<C, MetaDecay<T>> {};

    template<class C, class T, class Compare, class Alloc>
    struct ConvertTypeToIdTraits<C, std::multiset<T, Compare, Alloc>>
            : ConvertContainerTypeToArrayId<C, MetaDecay<T>> {};

    template<class C, class Key, class T, class Compare, class Alloc>
    struct ConvertTypeToIdTraits<C, std::map<Key, T, Compare, Alloc>>
            : ConvertContainerTypeToArrayId<C, std::pair<MetaDecay<Key>, MetaDecay<T>>> {};

    template<class C, class Key, class T, class Compare, class Alloc>
    struct ConvertTypeToIdTraits<C, std::multimap<Key, T, Compare, Alloc>>
            : ConvertContainerTypeToArrayId<C, std::pair<MetaDecay<Key>, MetaDecay<T>>> {};

    template<class C, class T, class Hash, class Pred, class Alloc>
    struct ConvertTypeToIdTraits<C, std::unordered_set<T, Hash, Pred, Alloc>>
            : ConvertContainerTypeToArrayId<C, std::pair<MetaDecay<T>, MetaDecay<Hash>>> {};

    template<class C, class T, class Hash, class Pred, class Alloc>
    struct ConvertTypeToIdTraits<C, std::unordered_multiset<T, Hash, Pred, Alloc>>
            : ConvertContainerTypeToArrayId<C, std::pair<MetaDecay<T>, MetaDecay<Hash>>> {};

    template<class C, class Key, class T, class Hash, class Pred, class Alloc>
    struct ConvertTypeToIdTraits<C, std::unordered_map<Key, T, Hash, Pred, Alloc>>
            : ConvertContainerTypeToArrayId<C, std::pair<MetaDecay<Key>, MetaDecay<T>>> {};

    template<class C, class Key, class T, class Hash, class Pred, class Alloc>
    struct ConvertTypeToIdTraits<C, std::unordered_multimap<Key, T, Hash, Pred, Alloc>>
            : ConvertContainerTypeToArrayId<C, std::pair<MetaDecay<Key>, MetaDecay<T>>> {};

    template<class C, class T, class Traits, class Alloc>
    struct ConvertTypeToIdTraits<C, std::basic_string<T, Traits, Alloc>>
            : ConvertContainerTypeToArrayId<C, MetaDecay<T>> {};

    template<class C, class T, class K>
    struct ConvertTypeToIdTraits<C, std::pair<T, K>>
            : ConvertTypeToIdTraits<C, MetaList<ConvertTypeToIdTraits<T>, ConvertTypeToIdTraits<K>>> {};

    template<class C, class... Ts>
    struct ConvertTypeToIdTraits<C, std::tuple<Ts...>>
            : ConvertTypeToIdTraits<C, MetaList<ConvertTypeToIdTraits<Ts>...>> {};

    template <class C, template <class...> class List, class... Ts>
    struct ConvertTypeToIdTraits<C, List<Ts...>> {
        using Type = MetaIf<MetaLength<Ts...>::value == 1,
        MetaAppendSequence<typename ConvertTypeToIdTraits<C, MetaDecay<Ts>>::Type...>,
        MetaAppendSequence<TypeIdSequence<C, TypeId::STRUCTURE_ID>, typename ConvertTypeToIdTraits<C, MetaDecay<Ts>>::Type...>>;
    };


    namespace detail {
        template<class List> struct TypeConverterImplementation;

        template<template<class...> class List, class... Ts>
        struct TypeConverterImplementation<List<Ts...>> {
            using Type = MetaAppendSequence<ConvertTypeToId<uint8_t, Ts>...>;
        };
    }
    template <class List>
    using TypeConverter = typename detail::TypeConverterImplementation<List>::Type;
}
