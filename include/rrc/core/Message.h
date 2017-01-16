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
        template <class R, class S> struct PrepareSerializerImplementation {};
        template <template <class...> class R, class... Rs, template <class...> class S, class... Ss, class First, class Second>
        struct PrepareSerializerImplementation<R<Rs...>, S<First, Second, Ss...>> {
            static constexpr bool isSame = std::is_same<First, Second>::value
                                  && std::is_same<typename Serializer<First>::SizeCategory, typename Serializer<Second>::SizeCategory>::value;
            static constexpr bool isDynamic = std::is_same<typename Serializer<First>::SizeCategory, DynamicSizeTag>::value;

            using Type = meta::If<isSame && !isDynamic,
                                  typename PrepareSerializerImplementation<R<Rs...>, S<First, Ss...>>::Type,
                                  typename PrepareSerializerImplementation<R<Rs..., Serializer<First>>, S<Second, Ss...>>::Type>;
        };

        template <template <class...> class R, class... Rs, template <class...> class S, class First>
        struct PrepareSerializerImplementation<R<Rs...>, S<First>> {
            using Type = R<Rs..., Serializer<First>>;
        };

        template <template <class...> class R, class... Rs, template <class...> class S>
        struct PrepareSerializerImplementation<R<Rs...>, S<>> {
            using Type = R<Rs...>;
        };

        template <class... Ts>
        using PrepareSerializers = typename PrepareSerializerImplementation<meta::List<>, meta::List<Ts...>>::Type;

        template <class... Ss>
        using GetValueTypes = typename meta::Append<typename Ss::ValueTypes...>;

        template <class... Ts>
        using MetaData = meta::RenameSequence<meta::Packer<TypeConverter<meta::Transform<GetValueTypes, PrepareSerializers<meta::Decay<Ts>...>>>>, meta::ArrayGenerator<int8_t>>;



    private:
        ConstCharPointer mMetaData;
        int_fast8_t mMetaDataSize;
    };
}


