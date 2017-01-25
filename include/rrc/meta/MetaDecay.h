/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


#include <type_traits>

namespace rrc {
    template <class T>
    using MetaDecay = typename std::decay<T>::type;
}