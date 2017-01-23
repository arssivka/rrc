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
        class StructureTypeQuantityGeneratorImplementation {
        public:
            using Type = rrc::meta::IntegralSequence<size_t>;
        };

        template <template <class...> class List, class... Ts>
        class StructureTypeQuantityGeneratorImplementation<List<Ts...>> {
        public:
            using Type = meta::If<
                    (rrc::meta::Length<Ts...>::value > 1),
                    rrc::meta::AppendSequence<
                            rrc::meta::IntegralSequence<size_t, meta::Length<Ts...>::value>,
                            typename StructureTypeQuantityGeneratorImplementation<Ts>::Type...
                    >,
                    typename StructureTypeQuantityGeneratorImplementation<
                            rrc::meta::Front<rrc::meta::List<Ts...>>
                    >::Type
            >;

        };
        template<class T, class Alloc>
        class StructureTypeQuantityGeneratorImplementation<std::vector<T, Alloc>>
                : public StructureTypeQuantityGeneratorImplementation<rrc::meta::List<rrc::meta::Decay<T>>> {};

        template<class T, class Alloc>
        class StructureTypeQuantityGeneratorImplementation<std::deque<T, Alloc>>
                : public StructureTypeQuantityGeneratorImplementation<rrc::meta::List<rrc::meta::Decay<T>>> {};

        template<class T, class Alloc>
        class StructureTypeQuantityGeneratorImplementation<std::list<T, Alloc>>
                : public StructureTypeQuantityGeneratorImplementation<rrc::meta::List<rrc::meta::Decay<T>>> {};

        template<class T, class Alloc>
        class StructureTypeQuantityGeneratorImplementation<std::forward_list<T, Alloc>>
                : public StructureTypeQuantityGeneratorImplementation<rrc::meta::List<rrc::meta::Decay<T>>> {};

        template<class T, class Compare, class Alloc>
        class StructureTypeQuantityGeneratorImplementation<std::set<T, Compare, Alloc>>
                : public StructureTypeQuantityGeneratorImplementation<rrc::meta::List<rrc::meta::Decay<T>>> {};

        template<class T, class Compare, class Alloc>
        class StructureTypeQuantityGeneratorImplementation<std::multiset<T, Compare, Alloc>>
                : public StructureTypeQuantityGeneratorImplementation<rrc::meta::List<rrc::meta::Decay<T>>> {};

        template<class Key, class T, class Compare, class Alloc>
        class StructureTypeQuantityGeneratorImplementation<std::map<Key, T, Compare, Alloc>>
                : public StructureTypeQuantityGeneratorImplementation<rrc::meta::List<std::pair<rrc::meta::Decay<Key>, rrc::meta::Decay<T>>>> {};

        template<class Key, class T, class Compare, class Alloc>
        class StructureTypeQuantityGeneratorImplementation<std::multimap<Key, T, Compare, Alloc>>
                : public StructureTypeQuantityGeneratorImplementation<rrc::meta::List<std::pair<rrc::meta::Decay<Key>, rrc::meta::Decay<T>>>> {};

        template<class T, class Hash, class Pred, class Alloc>
        class StructureTypeQuantityGeneratorImplementation<std::unordered_set<T, Hash, Pred, Alloc>>
                : public StructureTypeQuantityGeneratorImplementation<rrc::meta::List<std::pair<rrc::meta::Decay<T>, rrc::meta::Decay<Hash>>>> {};

        template<class T, class Hash, class Pred, class Alloc>
        class StructureTypeQuantityGeneratorImplementation<std::unordered_multiset<T, Hash, Pred, Alloc>>
                : public StructureTypeQuantityGeneratorImplementation<rrc::meta::List<std::pair<rrc::meta::Decay<T>, rrc::meta::Decay<Hash>>>> {};

        template<class Key, class T, class Hash, class Pred, class Alloc>
        class StructureTypeQuantityGeneratorImplementation<std::unordered_map<Key, T, Hash, Pred, Alloc>>
                : public StructureTypeQuantityGeneratorImplementation<rrc::meta::List<std::pair<rrc::meta::Decay<Key>, rrc::meta::Decay<T>>>> {};

        template<class Key, class T, class Hash, class Pred, class Alloc>
        class StructureTypeQuantityGeneratorImplementation<std::unordered_multimap<Key, T, Hash, Pred, Alloc>>
                : public StructureTypeQuantityGeneratorImplementation<rrc::meta::List<std::pair<rrc::meta::Decay<Key>, rrc::meta::Decay<T>>>> {};

        template<class T, class Traits, class Alloc>
        class StructureTypeQuantityGeneratorImplementation<std::basic_string<T, Traits, Alloc>>
                : public StructureTypeQuantityGeneratorImplementation<rrc::meta::List<rrc::meta::Decay<T>>> {};

        template<class T, class K>
        class StructureTypeQuantityGeneratorImplementation<std::pair<T, K>>
                : public StructureTypeQuantityGeneratorImplementation<rrc::meta::List<T, K>> {};

        template<class... Ts>
        class StructureTypeQuantityGeneratorImplementation<std::tuple<Ts...>>
            : public StructureTypeQuantityGeneratorImplementation<rrc::meta::List<Ts...>> {};
    }

    template <class L>
    using StructureTypeQuantityGenerator = typename detail::StructureTypeQuantityGeneratorImplementation<L>::Type;
}