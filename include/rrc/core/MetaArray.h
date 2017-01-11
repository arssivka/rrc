/**
 *  @autor arssivka
 *  @date 11/28/16
 */

#pragma once


#include <cstdint>
#include <array>
#include "MetaFunctions.h"

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

    template <class C, class... T> struct TypeToId {};
    template <class C> struct TypeToId<C, bool> : meta::IntegralSequence<C, TypeId::BOOL_ID> {};
    template <class C> struct TypeToId<C, int8_t> : meta::IntegralSequence<C, TypeId::INT8_ID> {};
    template <class C> struct TypeToId<C, int16_t> : meta::IntegralSequence<C, TypeId::INT16_ID> {};
    template <class C> struct TypeToId<C, int32_t> : meta::IntegralSequence<C, TypeId::INT32_ID> {};
    template <class C> struct TypeToId<C, int64_t> : meta::IntegralSequence<C, TypeId::INT64_ID> {};
    template <class C> struct TypeToId<C, float> : meta::IntegralSequence<C, TypeId::FLOAT_ID> {};
    template <class C> struct TypeToId<C, double> : meta::IntegralSequence<C, TypeId::DOUBLE_ID> {};
    template <class C, template <class...> class List, class... Ts>
    struct TypeToId<C, List<Ts...>>
            : meta::AppendSequence<meta::IntegralSequence<C, TypeId::STRUCTURE_ID>, TypeToId<C, Ts>...> {};

    namespace detail {
        template<class List> struct TypeConverterImplementation;

        template<template<class...> class List, class... Ts>
        struct TypeConverterImplementation<List<Ts...>> {
            using Type = meta::AppendSequence<TypeToId<int8_t, Ts>...>;
        };
    }
    template <class List>
    using TypeConverter = typename detail::TypeConverterImplementation<List>::Type;

    namespace detail {
        template<class T>
        struct CleanTypeImplementation {
            static_assert(std::is_fundamental<T>::value, "Type is not a fundamental type");
            using Type = typename std::remove_cv<T>::type;
        };
        template<>
        struct CleanTypeImplementation<void> {
        };
        template<template<class> class C, class T>
        struct CleanTypeImplementation<C<T>> {
            using Type = typename CleanTypeImplementation<T>::Type;
        };
        template<template<class, class, class...> class C, class K, class T, class... O>
        struct CleanTypeImplementation<C<K, T, O...>> {
            using Type = typename CleanTypeImplementation<typename std::remove_cv<T>::type>::Type;
        };
        template<template<class, size_t> class C, class T, size_t S>
        struct CleanTypeImplementation<C<T, S>> {
            using Type = typename CleanTypeImplementation<typename std::remove_cv<T>::type>::Type;
        };
    }
    template<class T> using CleanType = typename detail::CleanTypeImplementation<typename std::remove_cv<T>::type>::Type;


    template <class G, class... Types> struct MetaArray;
    template <class T, template <class, T...> class G, class... Types, T... Values>
    struct MetaArray<G<T, Values...>, Types...> {
        template <class K>
        using Converter = TypeToId<T, CleanType<K>>;
        using ValuesSequence = meta::IntegralSequence<T, Values...>;
        using Sequence = meta::AppendSequence<ValuesSequence, meta::IntegralSequence<T, Converter<Types>::value...>>;
        using Generator = meta::RenameSequence<Sequence, G<T>>;
        constexpr static size_t size = Generator::size;
        constexpr static std::array<T, size> data = Generator::data;
    };
}
