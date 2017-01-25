/**
 *  @autor arssivka
 *  @date 1/25/17
 */

#pragma once


#include "rrc/meta.h"
#include "Serializer.h"
#include "TypeConverter.h"
#include "StructureTypeQuantityGenerator.h"
#include "ArrayReference.h"

namespace rrc {
    class TypesIdentifiersArray
            : public ArrayReference<const uint8_t> {
    private:
        template<class... Ss>
        using GetValueTypes = MetaAppend<typename Ss::ValueTypes...>;

        template<class... Ts>
        using TypesList = MetaTransform<GetValueTypes, MetaList<Serializer<MetaDecay<Ts>>...>>;

        template<class... Ts>
        using IdentifiersSequence = TypeConverter<TypesList<Ts...>>;

        template<class... Ts>
        using MetaTypesData = MetaPacker<IdentifiersSequence<Ts...>>;

        template<class... Ts>
        using StructureTypeQuantitySequence = StructureTypeQuantitySequence<TypesList<Ts...>>;

        template<class... Ts>
        using EncodedStructureTypeQuantitySequence = MetaRenameSequence<
                StructureTypeQuantitySequence<Ts...>,
                detail::MetaVarintEncodeSequenceImplementation<size_t>
        >;

        //TODO:: Comment what's below and test StructureTypeQuantity. Use of implementation is ugly.
        template<class... Ts>
        using MetaData = MetaAppendSequence<
                MetaArrayGenerator<uint8_t>,
                MetaVarintEncode<size_t, MetaSequenceSize<IdentifiersSequence<Ts...>>::value>,
                MetaTypesData<Ts...>,
                typename EncodedStructureTypeQuantitySequence<Ts>::Type...
        >;

    public:
        template<class... Ts>
        TypesIdentifiersArray(Ts...)
                : ArrayReference<const uint8_t>{&MetaData<Ts...>::data[0], MetaData<Ts...>::size} {}

    };
}