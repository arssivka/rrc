/**
 *  @autor arssivka
 *  @date 12/19/16
 */

#pragma once


#include "CopyOnWrite.h"
#include "rrc/meta.h"
#include "Serializer.h"
#include "MetaArray.h"
#include "ArrayReference.h"

namespace rrc {
    class Message {
    public:
        template <class... Ts>
        Message(Ts&&... ts) {
            mMetaData = ArrayReference<const int8_t>(&MetaData<Ts...>::data[0], MetaData<Ts...>::size);
        }

        const ArrayReference<const int8_t>& getMetaData() const noexcept {
            return mMetaData;
        }

    private:
        template <class... Ss>
        using GetValueTypes = typename meta::Append<typename Ss::ValueTypes...>;

        template <class... Ts>
        using MetaData = meta::Packer<meta::ArrayGenerator<int8_t>, TypeConverter<meta::Transform<GetValueTypes, meta::List<Serializer<meta::Decay<Ts>>...>>>>;

    private:
        ArrayReference<const int8_t> mMetaData;

    };
}


