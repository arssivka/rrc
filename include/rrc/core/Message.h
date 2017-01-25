/**
 *  @autor arssivka
 *  @date 12/19/16
 */

#pragma once


#include "CopyOnWrite.h"
#include "rrc/meta.h"
#include "TypesIdentifiersArray.h"

namespace rrc {
    class Message {
    public:
        template <class... Ts>
        Message(Ts&&... ts)
                : mMetaData{ts...} {}

        const ArrayReference<const uint8_t>& getMetaData() const noexcept {
            return mMetaData;
        }

    private:
        TypesIdentifiersArray mMetaData;
    };
}


