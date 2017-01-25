/**
 *  @autor arssivka
 *  @date 1/20/17
 */

#pragma once


#include <rrc/meta.h>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <array>
#include <forward_list>
#include <deque>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>

namespace rrc {
    namespace detail {
        template <class L>
        class StructureTypeQuantitySequenceImplementation {
        public:
            using Type = rrc::MetaIntegralSequence<size_t>;
        };

        template <template <class...> class List, class... Ts>
        class StructureTypeQuantitySequenceImplementation<List<Ts...>> {
        public:
            using Type = rrc::MetaIf<
                    (rrc::MetaLength<Ts...>::value > 1),
                    rrc::MetaAppendSequence<
                            rrc::MetaIntegralSequence<size_t, MetaLength<Ts...>::value>,
                            typename StructureTypeQuantitySequenceImplementation<Ts>::Type...
                    >,
                    typename StructureTypeQuantitySequenceImplementation<
                            rrc::MetaFront<rrc::MetaList<Ts...>>
                    >::Type
            >;

        };
        template<class T, class Alloc>
        class StructureTypeQuantitySequenceImplementation<std::vector<T, Alloc>>
                : public StructureTypeQuantitySequenceImplementation<rrc::MetaList<rrc::MetaDecay<T>>> {};

        template<class T, class Alloc>
        class StructureTypeQuantitySequenceImplementation<std::deque<T, Alloc>>
                : public StructureTypeQuantitySequenceImplementation<rrc::MetaList<rrc::MetaDecay<T>>> {};

        template<class T, class Alloc>
        class StructureTypeQuantitySequenceImplementation<std::list<T, Alloc>>
                : public StructureTypeQuantitySequenceImplementation<rrc::MetaList<rrc::MetaDecay<T>>> {};

        template<class T, class Alloc>
        class StructureTypeQuantitySequenceImplementation<std::forward_list<T, Alloc>>
                : public StructureTypeQuantitySequenceImplementation<rrc::MetaList<rrc::MetaDecay<T>>> {};

        template<class T, class Compare, class Alloc>
        class StructureTypeQuantitySequenceImplementation<std::set<T, Compare, Alloc>>
                : public StructureTypeQuantitySequenceImplementation<rrc::MetaList<rrc::MetaDecay<T>>> {};

        template<class T, class Compare, class Alloc>
        class StructureTypeQuantitySequenceImplementation<std::multiset<T, Compare, Alloc>>
                : public StructureTypeQuantitySequenceImplementation<rrc::MetaList<rrc::MetaDecay<T>>> {};

        template<class Key, class T, class Compare, class Alloc>
        class StructureTypeQuantitySequenceImplementation<std::map<Key, T, Compare, Alloc>>
                : public StructureTypeQuantitySequenceImplementation<rrc::MetaList<std::pair<rrc::MetaDecay<Key>, rrc::MetaDecay<T>>>> {};

        template<class Key, class T, class Compare, class Alloc>
        class StructureTypeQuantitySequenceImplementation<std::multimap<Key, T, Compare, Alloc>>
                : public StructureTypeQuantitySequenceImplementation<rrc::MetaList<std::pair<rrc::MetaDecay<Key>, rrc::MetaDecay<T>>>> {};

        template<class T, class Hash, class Pred, class Alloc>
        class StructureTypeQuantitySequenceImplementation<std::unordered_set<T, Hash, Pred, Alloc>>
                : public StructureTypeQuantitySequenceImplementation<rrc::MetaList<std::pair<rrc::MetaDecay<T>, rrc::MetaDecay<Hash>>>> {};

        template<class T, class Hash, class Pred, class Alloc>
        class StructureTypeQuantitySequenceImplementation<std::unordered_multiset<T, Hash, Pred, Alloc>>
                : public StructureTypeQuantitySequenceImplementation<rrc::MetaList<std::pair<rrc::MetaDecay<T>, rrc::MetaDecay<Hash>>>> {};

        template<class Key, class T, class Hash, class Pred, class Alloc>
        class StructureTypeQuantitySequenceImplementation<std::unordered_map<Key, T, Hash, Pred, Alloc>>
                : public StructureTypeQuantitySequenceImplementation<rrc::MetaList<std::pair<rrc::MetaDecay<Key>, rrc::MetaDecay<T>>>> {};

        template<class Key, class T, class Hash, class Pred, class Alloc>
        class StructureTypeQuantitySequenceImplementation<std::unordered_multimap<Key, T, Hash, Pred, Alloc>>
                : public StructureTypeQuantitySequenceImplementation<rrc::MetaList<std::pair<rrc::MetaDecay<Key>, rrc::MetaDecay<T>>>> {};

        template<class T, class Traits, class Alloc>
        class StructureTypeQuantitySequenceImplementation<std::basic_string<T, Traits, Alloc>>
                : public StructureTypeQuantitySequenceImplementation<rrc::MetaList<rrc::MetaDecay<T>>> {};

        template<class T, class K>
        class StructureTypeQuantitySequenceImplementation<std::pair<T, K>>
                : public StructureTypeQuantitySequenceImplementation<rrc::MetaList<T, K>> {};

        template<class... Ts>
        class StructureTypeQuantitySequenceImplementation<std::tuple<Ts...>>
            : public StructureTypeQuantitySequenceImplementation<rrc::MetaList<Ts...>> {};
    }

    template <class L>
    using StructureTypeQuantitySequence = typename detail::StructureTypeQuantitySequenceImplementation<L>::Type;
}