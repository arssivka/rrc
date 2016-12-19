/**
 *  @autor arssivka
 *  @date 12/19/16
 */

#pragma once


#include <cstddef>
#include <type_traits>
#include <vector>
#include <list>
#include <cstdint>
#include <numeric>
#include <array>
#include <forward_list>
#include <deque>
#include "SerializerTraits.h"

namespace rrc {
    template <class T>
    class Serializer {
    public:
        using Type = std::remove_cv<T>;
        static_assert(std::is_fundamental<Type>::value);

        static size_t serialize(const Type& data, char* buffer) {
            *(T*) buffer = data;
            return size(data);
        };

        static size_t size(const Type& data) noexcept {
            return sizeof(data);
        }
    };



    template <class T>
    class SequenceSerializer {
    public:
        using Type = T;

        static size_t serialize(const T& data, char* buffer) {
            size_t acc = 0;
            for (auto&& item : data) {
                size_t wrote = rrc::Serializer<decltype(item)>::serialize(item, buffer + acc);
                acc += wrote;
            }
            return acc;
        };

        size_t size(T& data) noexcept {
            return sizeImplementation(data, SerializerTraits<T>::Size);
        }

    private:
        inline size_t sizeImplementation<std::true_type>(T& data, FixedSizeTag) {
            return data.size() * sizeof(T::value_type);
        }

        inline size_t sizeImplementation(T& data, DynamicSizeTag) {
            return std::accumulate(std::begin(data), std::end(data), (size_t) 0,
                                   [](size_t acc, const T::value_type& value) -> size_t {
                return acc + Serializer<T::value_type>::size(value);
            });
        }
    };

    template <class T, size_t N> class Serializer<std::array<T, N>> : SequenceSerializer<std::array<T, N>> {};
    template <class T> class Serializer<std::vector<T>> : SequenceSerializer<std::vector<T>> {};
    template <class T> class Serializer<std::deque<T>> : SequenceSerializer<std::deque<T>> {};
    template <class T> class Serializer<std::forward_list<T>> : SequenceSerializer<std::forward_list<T>> {};
    template <class T> class Serializer<std::list<T>> : SequenceSerializer<std::list<T>> {};

}
