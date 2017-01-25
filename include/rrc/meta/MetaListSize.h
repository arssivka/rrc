/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


#include "MetaLength.h"
#include "MetaRename.h"

namespace rrc {
    template<class L> using MetaListSize = MetaRename<L, MetaLength>;
}