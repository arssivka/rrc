/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


#include <type_traits>

namespace rrc {
    template<bool Condition, class TrueType, class FalseType>
    using MetaIf = typename std::conditional<Condition, TrueType, FalseType>::type;
}