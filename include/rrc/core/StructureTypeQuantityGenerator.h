/**
 *  @autor arssivka
 *  @date 1/20/17
 */

#pragma once


#include <rrc/meta.h>

namespace rrc {
    namespace detail {
        template <class L>
        class StructureTypeQuantityGeneratorImplementation {
            using Type = rrc::meta::IntegralSequence<size_t>;
        };

        template <template<class...> class L, class... Ts>
        class StructureTypeQuantityGeneratorImplementation<L<Ts...>> {
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
    }

    template <class L>
    using StructureTypeQuantityGenerator = typename detail::StructureTypeQuantityGeneratorImplementation<L>::Type;
}