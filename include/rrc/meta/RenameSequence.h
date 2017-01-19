/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


namespace rrc {
    namespace meta {
        namespace detail {
            template<class A, class B>
            class RenameSequenceImplementation;

            template<class T, template<class, T...> class A,
                    template<class, T...> class B, T... V>
            class RenameSequenceImplementation<A<T, V...>, B<T>> {
            public:
                using Type = B<T, V...>;
            };
        }
        /**
         * @brief Transforms sequence to a container
         * Example of using: RenameSequence<IntegralSequence<int, 1, 2, 3>, ArrayGenerator<int>>
         * @tparam A Sequence to rename
         * @tparam B Needed type of resulting container
         */
        template<class A, class B> using RenameSequence = typename detail::RenameSequenceImplementation<A, B>::Type;
    }
}