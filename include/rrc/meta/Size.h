/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


#include "Length.h"
#include "Rename.h"

namespace rrc {
    namespace meta {
        template<class L> using Size = Rename<L, Length>;
    }
}