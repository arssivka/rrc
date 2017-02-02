/**
 *  @autor tekatod
 *  @date 1/27/17
 */
#pragma once

#include <type_traits>

namespace rrc {

    template<class T>
    class MetaFrontSequenceElement;

    template<class T, template<class, T...> class S, T First, T... Ss>
    class MetaFrontSequenceElement<S<T, First, Ss...>> : public std::integral_constant<T, First> { };

}