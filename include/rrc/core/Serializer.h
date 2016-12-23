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
    template<class T>
    class Serializer {
    public:
        using Type = std::remove_cv<T>;
        static_assert(std::is_fundamental<Type>::value);

        static size_t serialize(const Type& data, char* buffer) {
            *(T*) buffer = data;
            return size(data);
        };

        static size_t size(const Type& data) noexcept {
            return 1;
        }
    };


    template<class T>
    struct ContainerSerializer {
        using Type = T;

        static size_t serialize(const T& data, char* buffer) {
            size_t acc = 0;
            for (auto&& item : data) {
                size_t wrote = rrc::Serializer<decltype(item)>::serialize(item, buffer + acc);
                acc += wrote;
            }
            return acc;
        };

        size_t size(const T& data) noexcept {
            return data.size();
        }

    };

    template<class T, size_t N>
    struct Serializer<std::array<T, N>>
            : public ContainerSerializer<std::array<T, N>> {};

    template<class T, class Alloc>
    struct Serializer<std::vector<T, Alloc>>
            : public ContainerSerializer<std::vector<T, Alloc>> {};

    template<class T, class Alloc>
    struct Serializer<std::deque<T, Alloc>>
            : public ContainerSerializer<std::deque<T, Alloc>> {};

    template<class T, class Alloc>
    struct Serializer<std::list<T, Alloc>>
            : public ContainerSerializer<std::list<T, Alloc>> {};

    template<class T, class Alloc>
    struct Serializer<std::forward_list<T, Alloc>>
            : public ContainerSerializer<std::forward_list<T, Alloc>> {};

    template<class T, class Compare, class Alloc>
    struct Serializer<std::set<T, Compare, Alloc>>
            : public ContainerSerializer<std::set<T, Compare, Alloc>> {};

    template<class T, class Compare, class Alloc>
    struct Serializer<std::multiset<T, Compare, Alloc>>
            : public ContainerSerializer<std::multiset<T, Compare, Alloc>> {};

    template<class Key, class T, class Compare, class Alloc>
    struct Serializer<std::map<Key, T, Compare, Alloc>>
            : public ContainerSerializer<std::map<Key, T, Compare, Alloc>> {};

    template<class Key, class T, class Compare, class Alloc>
    struct Serializer<std::multimap<Key, T, Compare, Alloc>>
            : public ContainerSerializer<std::multimap<Key, T, Compare, Alloc>> {};

    template<class T, class Hash, class Pred, class Alloc>
    struct Serializer<std::unordered_set<T, Hash, Pred, Alloc>>
            : public ContainerSerializer<std::unordered_set<T, Hash, Pred, Alloc>> {};

    template<class T, class Hash, class Pred, class Alloc>
    struct Serializer<std::unordered_multiset<T, Hash, Pred, Alloc>>
            : public ContainerSerializer<std::unordered_multiset<T, Hash, Pred, Alloc>> {};

    template<class Key, class T, class Hash, class Pred, class Alloc>
    struct Serializer<std::unordered_map<Key, T, Hash, Pred, Alloc>>
            : public ContainerSerializer<std::unordered_map<Key, T, Hash, Pred, Alloc>> {};

    template<class Key, class T, class Hash, class Pred, class Alloc>
    struct Serializer<std::unordered_multimap<Key, T, Hash, Pred, Alloc>>
            : public ContainerSerializer<std::unordered_multimap<Key, T, Hash, Pred, Alloc>> {};

    template<class T, class K>
    struct Serializer<std::pair<T, K>> {
        using Type = T;

        static size_t serialize(const std::pair<T, K>& data, char* buffer) {
            size_t acc = 0;
            acc += Serializer<T>::serialize(data.first, buffer + acc);
            acc += Serializer<T>::serialize(data.second, buffer + acc);
            return acc;
        };

        size_t size(const std::pair<T, K>& data) noexcept {
            return 2;
        }
    };

    template<class... Ts>
    struct Serializer<std::tuple<Ts...>> {
        static size_t serialize(const std::tuple<Ts...>& data, char* buffer) {
            size_t acc = 0;
            for (size_t i = 0; i < sizeof...(Ts); ++i) {
                using Arg = typename std::tuple_element<i, std::tuple<Ts...>>::type;
                acc += Serializer<Arg>::serialize(std::get<i>(data), buffer + acc);
            }
            return acc;
        };

        size_t size(const std::tuple<Ts...>& data) noexcept {
            return sizeof...(Ts);
        }

    };

}
