/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


#include <type_traits>

namespace rrc {
    namespace meta {
        template <class T>
        using Decay = typename std::decay<T>::type;
    }
}