/**
 *  @autor arssivka
 *  @date 12/19/16
 */

#pragma once


#include "CopyOnWrite.h"
#include "rrc/meta.h"
#include "Serializer.h"
#include "TypeConverter.h"
#include "ArrayReference.h"
#include "StructureTypeQuantityGenerator.h"

namespace rrc {
    class Message {
    public:
        template <class... Ts>
        Message(Ts&&... ts) {
            mMetaData = ArrayReference<const uint8_t>(&MetaData<Ts...>::data[0], MetaData<Ts...>::size);
        }

        const ArrayReference<const uint8_t>& getMetaData() const noexcept {
            return mMetaData;
        }

    private:
        template <class... Ss>
        using GetValueTypes = typename meta::Append<typename Ss::ValueTypes...>;

        template <class... Ts>
        using TypesList = meta::Transform<GetValueTypes, meta::List<Serializer<meta::Decay<Ts>>...>>;

        template <class... Ts>
        using IdentifiersSequence = TypeConverter<TypesList<Ts...>>;

        template <class... Ts>
        using MetaTypesData = meta::Packer<IdentifiersSequence<Ts...>>;


        template <class... Ts>
        using StructureTypeQuantitySequence = StructureTypeQuantityGenerator<TypesList<Ts...>>;

        //TODO:: Comment what's below and test StructureTypeQuantity. Use of implementation is ugly.
        template <class... Ts>
        using EncodedStructureTypeQuantitySequence = meta::RenameSequence<
                StructureTypeQuantitySequence<Ts...>,
                meta::detail::VarintEncodeSequenceImplementation<size_t>
        >;

        template <class... Ts>
        using MetaData = meta::AppendSequence<
                meta::ArrayGenerator<uint8_t>,
                MetaTypesData<Ts...>,
                typename EncodedStructureTypeQuantitySequence<Ts>::Type...
        >;

    private:
        ArrayReference<const uint8_t> mMetaData;

    };
}


