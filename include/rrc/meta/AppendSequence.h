/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


namespace rrc {
    namespace meta {
        namespace detail {
            template<class... S>
            class AppendSequenceImplementation;
            template<class T, template<class, T...> class S, T... V>
            class AppendSequenceImplementation<S<T, V...>> {
            public:
                using Type = S<T, V...>;
            };
            template<class T, template<class, T...> class S1, T... V1,
                    template<class, T...> class S2, T... V2, class... Lr>
            class AppendSequenceImplementation<S1<T, V1...>, S2<T, V2...>, Lr...> {
            public:
                using Type = typename AppendSequenceImplementation<S1<T, V1..., V2...>, Lr...>::Type;
            };
        }
        /**
         * @brief Adds elements to the end of the sequence
         * Example of using: AppendSequence <IntegralSequence<int, 1, 2, 3>, IntegralSequence<int, 4, 5, 6>, IntegralSequence<int, 7, 8, 9>>
         * @tparam S First parameter must be a sequence to add elements to it. Other parameters are elements to add
         */
        template<class... S> using AppendSequence = typename detail::AppendSequenceImplementation<S...>::Type;
    }
}