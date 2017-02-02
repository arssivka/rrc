/**
 *  @autor tekatod
 *  @date 1/25/17
 */
#pragma once

#include "MetaIntegralSequence.h"

namespace rrc {

    template<class T>
    class MetaPopFrontSequence;

    template<class T, template<class, T...> class S, T... Ss>
    class MetaPopFrontSequence<S<T, Ss...>> {
        public:
            using Type = MetaIntegralSequence<T>;
    };

    template<class T, template<class, T...> class S, T First, T... Ss>
    class MetaPopFrontSequence<S<T, First, Ss...>> {
        public:
            using Type = MetaIntegralSequence<T, Ss...>;
    };

}