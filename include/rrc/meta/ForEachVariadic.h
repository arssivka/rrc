/**
 *  @autor arssivka
 *  @date 1/25/17
 */

#pragma once


#include <bits/forward_list.h>

namespace rrc {
    template <class F, class... Ts>
    void forEachVariadic(F&& f, Ts&&... vars) {
        auto l = { f(std::forward<Ts>(vars))... };
    }
}