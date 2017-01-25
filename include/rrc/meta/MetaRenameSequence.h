/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


namespace rrc {
        namespace detail {
            template<class A, class B>
            class MetaRenameSequenceImplementation;

            template<class T, template<class, T...> class A,
                    template<class, T...> class B, T... V>
            class MetaRenameSequenceImplementation<A<T, V...>, B<T>> {
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
        template<class A, class B> using MetaRenameSequence = typename detail::MetaRenameSequenceImplementation<A, B>::Type;
}