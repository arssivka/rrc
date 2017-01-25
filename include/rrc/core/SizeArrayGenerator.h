/**
 *  @autor arssivka
 *  @date 1/23/17
 */

#pragma once


#include "MetaGenerators.h"

namespace rrc {
    class SizeArrayGenerator  {
    public:
        template <class... Ts>
        SizeArrayGenerator(Ts&&... values) {

        }

    private:


    };
}