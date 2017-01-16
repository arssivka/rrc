/**
 *  @autor arssivka
 *  @date 11/28/16
 */

#pragma once


#include <cstdint>
#include <array>
#include "MetaFunctions.h"
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
    class Message;

    enum TypeId {
        UNKNOWN_ID,
        BOOL_ID,
        INT8_ID,
        INT16_ID,
        INT32_ID,
        INT64_ID,
        FLOAT_ID,
        DOUBLE_ID,
        STRUCTURE_ID,
        COUNT_IDS
    };

    namespace detail {
        template <class T, T... Vals>
        struct TypeIdSequence {
            using Type = meta::IntegralSequence<T, Vals...>;
        };
        template <class C, class... T> struct ConvertTypeToIdImplementation {};
        template <class C> struct ConvertTypeToIdImplementation<C, bool> : TypeIdSequence<C, TypeId::BOOL_ID> {};
        template <class C> struct ConvertTypeToIdImplementation<C, int8_t> : TypeIdSequence<C, TypeId::INT8_ID> {};
        template <class C> struct ConvertTypeToIdImplementation<C, int16_t> : TypeIdSequence<C, TypeId::INT16_ID> {};
        template <class C> struct ConvertTypeToIdImplementation<C, int32_t> : TypeIdSequence<C, TypeId::INT32_ID> {};
        template <class C> struct ConvertTypeToIdImplementation<C, int64_t> : TypeIdSequence<C, TypeId::INT64_ID> {};
        template <class C> struct ConvertTypeToIdImplementation<C, float> : TypeIdSequence<C, TypeId::FLOAT_ID> {};
        template <class C> struct ConvertTypeToIdImplementation<C, double> : TypeIdSequence<C, TypeId::DOUBLE_ID> {};
        template <class C, template <class...> class List, class... Ts>
        struct ConvertTypeToIdImplementation<C, List<Ts...>> {
            using Type = meta::If<meta::Length<Ts...>::value == 1,
            meta::AppendSequence<typename ConvertTypeToIdImplementation<C, meta::Decay<Ts>>::Type...>,
            meta::AppendSequence<TypeIdSequence<C, TypeId::STRUCTURE_ID>, typename ConvertTypeToIdImplementation<C, meta::Decay<Ts>>::Type...>>;
        };
    }
    template <class C, class... T>
    using ConvertTypeToId = typename detail::ConvertTypeToIdImplementation<C, T...>::Type;


    namespace detail {
        template<class List> struct TypeConverterImplementation;

        template<template<class...> class List, class... Ts>
        struct TypeConverterImplementation<List<Ts...>> {
            using Type = meta::AppendSequence<ConvertTypeToId<int8_t, Ts>...>;
        };
    }
    template <class List>
    using TypeConverter = typename detail::TypeConverterImplementation<List>::Type;

    namespace detail {


        //TODO: VECTOR ON NIFIGA NE DINAMIC, A CLEAN TYPE OCHISHAET OT VECTORA
        template<class T>
        struct CleanTypeImplementation {
            static_assert(std::is_fundamental<T>::value, "Type is not a fundamental type");
            using Type = rrc::meta::Decay<T>;
        };
        template<>
        struct CleanTypeImplementation<void> {
        };

        template<class T, class Alloc>
        struct CleanTypeImplementation<std::vector<T, Alloc>>
                : CleanTypeImplementation<rrc::meta::Decay<T>> {};

        template<class T, class Alloc>
        struct CleanTypeImplementation<std::deque<T, Alloc>>
                : CleanTypeImplementation<rrc::meta::Decay<T>> {};

        template<class T, class Alloc>
        struct CleanTypeImplementation<std::list<T, Alloc>>
                : CleanTypeImplementation<rrc::meta::Decay<T>> {};

        template<class T, class Alloc>
        struct CleanTypeImplementation<std::forward_list<T, Alloc>>
                : CleanTypeImplementation<rrc::meta::Decay<T>> {};

        template<class T, class Compare, class Alloc>
        struct CleanTypeImplementation<std::set<T, Compare, Alloc>>
                : CleanTypeImplementation<rrc::meta::Decay<T>> {};

        template<class T, class Compare, class Alloc>
        struct CleanTypeImplementation<std::multiset<T, Compare, Alloc>>
                : CleanTypeImplementation<rrc::meta::Decay<T>> {};

        template<class Key, class T, class Compare, class Alloc>
        struct CleanTypeImplementation<std::map<Key, T, Compare, Alloc>>
                : CleanTypeImplementation<std::pair<Key, T>> {};

        template<class Key, class T, class Compare, class Alloc>
        struct CleanTypeImplementation<std::multimap<Key, T, Compare, Alloc>>
                : CleanTypeImplementation<std::pair<Key, T>> {};

        template<class T, class Hash, class Pred, class Alloc>
        struct CleanTypeImplementation<std::unordered_set<T, Hash, Pred, Alloc>>
                : CleanTypeImplementation<std::pair<T, Hash>> {};

        template<class T, class Hash, class Pred, class Alloc>
        struct CleanTypeImplementation<std::unordered_multiset<T, Hash, Pred, Alloc>>
                : CleanTypeImplementation<std::pair<T, Hash>> {};

        template<class Key, class T, class Hash, class Pred, class Alloc>
        struct CleanTypeImplementation<std::unordered_map<Key, T, Hash, Pred, Alloc>>
                : CleanTypeImplementation<std::pair<Key, T>> {};

        template<class Key, class T, class Hash, class Pred, class Alloc>
        struct CleanTypeImplementation<std::unordered_multimap<Key, T, Hash, Pred, Alloc>>
                : CleanTypeImplementation<std::pair<Key, T>> {};

        template<class T, class Traits, class Alloc>
        struct CleanTypeImplementation<std::basic_string<T, Traits, Alloc>>
                : CleanTypeImplementation<rrc::meta::Decay<T>> {};

        template<class T, class K>
        struct CleanTypeImplementation<std::pair<T, K>> {
            using Type = std::pair<CleanTypeImplementation<T>, CleanTypeImplementation<K>>;
        };

        template<class... Ts>
        struct CleanTypeImplementation<std::tuple<Ts...>> {
            using Type = std::tuple<CleanTypeImplementation<Ts>...>;
        };
    }
    template<class T> using CleanType = typename detail::CleanTypeImplementation<T>::Type;


//    template <class G, class... Types> struct MetaArray;
//    template <class T, template <class, T...> class G, class... Types, T... Values>
//    struct MetaArray<G<T, Values...>, Types...> {
//        template <class K>
//        using Converter = TypeToId<T, CleanType<K>>;
//        using ValuesSequence = meta::IntegralSequence<T, Values...>;
//        using Sequence = meta::AppendSequence<ValuesSequence, meta::IntegralSequence<T, Converter<Types>::value...>>;
//        using Generator = meta::RenameSequence<Sequence, G<T>>;
//        constexpr static size_t size = Generator::size;
//        constexpr static std::array<T, size> data = Generator::data;
//    };
}
