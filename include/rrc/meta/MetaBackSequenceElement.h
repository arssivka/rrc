/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


#include <type_traits>
#include "MetaIf.h"

namespace rrc {
    /**
     * @brief Gets the last element of the specified sequence
     * Example of using: BackSequenceElement<IntegralSequence<short, 1, 2, 3>>
     * @tparam T Sequence to get element from
     */
    template<class T>
    class MetaBackSequenceElement;

    template<class T, template<class, T...> class S, T First, T... Ss>
    class MetaBackSequenceElement<S<T, First, Ss...>>
            : public MetaIf<
                    sizeof...(Ss) == 0, std::integral_constant<T, First>, MetaBackSequenceElement<S<T, Ss...>>> {
    };
}