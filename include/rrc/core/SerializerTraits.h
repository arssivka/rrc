/**
 *  @autor arssivka
 *  @date 12/19/16
 */

#pragma once


#include "MetaFunctions.h"
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

namespace rrc {
    struct SizeTag {};

    struct FixedSizeTag
            : public SizeTag {};

    struct DynamicSizeTag
            : public SizeTag {};

    template<class T>
    struct SerializerTraits {
        using SizeCategory = FixedSizeTag;
        using ValueTypes = meta::List<T>
    };

    template<class T, size_t N>
    struct SerializerTraits<std::array<T, N>> {
        using SizeCategory = DynamicSizeTag;
        using ValueTypes = SerializerTraits<T>::ValueTypes;
    };

    template<class T, class Alloc>
    struct SerializerTraits<std::vector<T, Alloc>> {
        using SizeCategory = DynamicSizeTag;
        using ValueTypes = SerializerTraits<T>::ValueTypes;
    };

    template<class T, class Alloc>
    struct SerializerTraits<std::deque<T, Alloc>> {
        using SizeCategory = DynamicSizeTag;
        using ValueTypes = SerializerTraits<T>::ValueTypes;
    };

    template<class T, class Alloc>
    struct SerializerTraits<std::list<T, Alloc>> {
        using SizeCategory = DynamicSizeTag;
        using ValueTypes = SerializerTraits<T>::ValueTypes;
    };

    template<class T, class Alloc>
    struct SerializerTraits<std::forward_list<T, Alloc>> {
        using SizeCategory = DynamicSizeTag;
        using ValueTypes = SerializerTraits<T>::ValueTypes;
    };

    template<class T, class Compare, class Alloc>
    struct SerializerTraits<std::set<T, Compare, Alloc>> {
        using SizeCategory = DynamicSizeTag;
        using ValueTypes = SerializerTraits<T>::ValueTypes;
    };

    template<class T, class Compare, class Alloc>
    struct SerializerTraits<std::multiset<T, Compare, Alloc>> {
        using SizeCategory = DynamicSizeTag;
        using ValueTypes = SerializerTraits<T>::ValueTypes;
    };

    template<class Key, class T, class Compare, class Alloc>
    struct SerializerTraits<std::map<Key, T, Compare, Alloc>> {
        using SizeCategory = DynamicSizeTag;
        using ValueTypes = SerializerTraits<std::pair<Key, T>>::ValueTypes;
    };

    template<class Key, class T, class Compare, class Alloc>
    struct SerializerTraits<std::multimap<Key, T, Compare, Alloc>> {
        using SizeCategory = DynamicSizeTag;
        using ValueTypes = SerializerTraits<std::pair<Key, T>>::ValueTypes;
    };

    template<class T, class Hash, class Pred, class Alloc>
    struct SerializerTraits<std::unordered_set<T, Hash, Pred, Alloc>> {
        using SizeCategory = DynamicSizeTag;
        using ValueTypes = SerializerTraits<T>::ValueTypes;
    };

    template<class T, class Hash, class Pred, class Alloc>
    struct SerializerTraits<std::unordered_multiset<T, Hash, Pred, Alloc>> {
        using SizeCategory = DynamicSizeTag;
        using ValueTypes = SerializerTraits<T>::ValueTypes;
    };

    template<class Key, class T, class Hash, class Pred, class Alloc>
    struct SerializerTraits<std::unordered_map<Key, T, Hash, Pred, Alloc>> {
        using SizeCategory = DynamicSizeTag;
        using ValueTypes = SerializerTraits<std::pair<Key, T>>::ValueTypes;
    };

    template<class Key, class T, class Hash, class Pred, class Alloc>
    struct SerializerTraits<std::unordered_multimap<Key, T, Hash, Pred, Alloc>> {
        using SizeCategory = DynamicSizeTag;
        using ValueTypes = SerializerTraits<std::pair<Key, T>>::ValueTypes;
    };

    template <class T, class K>
    struct SerializerTraits<std::pair<T, K>> {
        using SizeCategory = FixedSizeTag;
        using ValueTypes = meta::Append<SerializerTraits<T>::ValueTypes, SerializerTraits<K>::ValueTypes>
    };

    template<class... Ts>
    struct SerializerTraits<std::tuple<Ts...>> {
        using SizeCategory = FixedSizeTag;
        using ValueTypes = meta::Append<SerializerTraits<Ts>::ValueTypes...>;
    };
}