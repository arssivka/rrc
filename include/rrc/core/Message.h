/**
 *  @autor arssivka
 *  @date 12/19/16
 */

#pragma once


#include "CopyOnWrite.h"
#include "MetaFunctions.h"
#include "Serializer.h"
#include "MetaArray.h"

namespace rrc {
    class Message {
    public:
        template <class... Ts>
        Message(Ts&& ts) {
            using TypesList = meta::Append<Serializer<Ts>::ValueTypes...>
//            using PackedList = meta::Concatenator<TypesList>;
//            using MetaArray = meta::Rename<TypesList, >
            static_assert(meta::Size<TypesList>::value > 256, "Meta array size should not exceed 256");
        }

    private:
        ConstCharPointer mMetaArray;
        size_t mMetaArraySize;
    };
}


