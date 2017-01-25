/**
 *  @autor arssivka
 *  @date 1/25/17
 */

#pragma once


#include <tuple>
#include "MetaIntegralSequence.h"
#include "MetaGenerateSequence.h"

namespace rrc {
    namespace detail {
        template<class T, class F, size_t... Ts>
        void ForEachTupleImplementation(T&& t, F&& f, MetaIntegralSequence<size_t, Ts...>) {
            auto l = { (f(std::get<Ts>(t)), 0)... };
        }
    }

    // TODO: Documentation and tests
    template<class C, class T, class... Ts, class F>
    void ForEachTuple(C&& t, F&& f) {
        detail::ForEachTupleImplementation(std::forward<C>(t), std::forward<F&&>(f), MetaGenerateSequence<size_t, sizeof...(Ts)>());
    }
}