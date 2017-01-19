/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


#include <type_traits>
#include "If.h"

namespace rrc {
    namespace meta {
        /**
         * @brief Gets the last element of the specified sequence
         * Example of using: BackSequenceElement<IntegralSequence<short, 1, 2, 3>>
         * @tparam T Sequence to get element from
         */
        template<class T>
        class BackSequenceElement;
        template<class T, template<class, T...> class S, T First, T... Ss>
        class BackSequenceElement<S<T, First, Ss...>>
                : public rrc::meta::If<sizeof...(Ss) == 0, std::integral_constant<T, First>, BackSequenceElement<S<T, Ss...>>> { };
    }
}