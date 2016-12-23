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

    namespace detail {
        template<class C, C ID>
        struct TypeToIdImpl { constexpr static C value = ID; };
    }
    template <class C, class T> struct TypeConverter : detail::TypeToIdImpl<C, TypeId::UNKNOWN_ID> { using Type = T; };
    template <class C> struct TypeConverter<C, bool> : detail::TypeToIdImpl<C, TypeId::BOOL_ID> {};
    template <class C> struct TypeConverter<C, int8_t> : detail::TypeToIdImpl<C, TypeId::INT8_ID> {};
    template <class C> struct TypeConverter<C, int16_t> : detail::TypeToIdImpl<C, TypeId::INT16_ID> {};
    template <class C> struct TypeConverter<C, int32_t> : detail::TypeToIdImpl<C, TypeId::INT32_ID> {};
    template <class C> struct TypeConverter<C, int64_t> : detail::TypeToIdImpl<C, TypeId::INT64_ID> {};
    template <class C> struct TypeConverter<C, float> : detail::TypeToIdImpl<C, TypeId::FLOAT_ID> {};
    template <class C> struct TypeConverter<C, double> : detail::TypeToIdImpl<C, TypeId::DOUBLE_ID> {};
    template <class C> struct TypeConverter<C, Message> : detail::TypeToIdImpl<C, TypeId::STRUCTURE_ID> {};

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
        using Converter = TypeConverter<T, CleanType<K>>;
        using ValuesSequence = meta::IntegralSequence<T, Values...>;
        using Sequence = meta::AppendSequence<ValuesSequence, meta::IntegralSequence<T, Converter<Types>::value...>>;
        using Generator = meta::RenameSequence<Sequence, G<T>>;
        constexpr static size_t size = Generator::size;
        constexpr static std::array<T, size> data = Generator::data;
    };
}
