/**
 *  @autor arssivka
 *  @date 1/23/17
 */

#pragma once


#include <memory>
#include "rrc/meta.h"
#include "ArrayReference.h"

namespace rrc {
    class TypeSizesArray : public ArrayReference<size_t> {
    private:


    public:
        template <class... Ts>
        TypeSizesArray(Ts&&... values) {

        }

    private:
        std::unique_ptr<size_t> mMemory;

    };
}