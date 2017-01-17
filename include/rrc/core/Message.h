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
        Message(Ts&&... ts) {
            static_assert(MetaData<Ts...>::size < 256, "Meta array size should not exceed 256");
            mMetaData = (ConstCharPointer) &MetaData<Ts...>::data[0];
            mMetaDataSize = (int_fast8_t) MetaData<Ts...>::size;
        }

        // TODO: I don't like this getters
        const char* getMetaData() const {
            return mMetaData;
        }

        int_fast8_t getMetaDataSize() const {
            return mMetaDataSize;
        }

    private:
        template <class... Ss>
        using GetValueTypes = typename meta::Append<typename Ss::ValueTypes...>;

        template <class... Ts>
        using MetaData = meta::Packer<meta::ArrayGenerator<int8_t>, TypeConverter<meta::Transform<GetValueTypes, meta::List<Serializer<meta::Decay<Ts>>...>>>>;



    private:
        ConstCharPointer mMetaData;
        int_fast8_t mMetaDataSize;
    };
}


