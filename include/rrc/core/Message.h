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
            static_assert(MetaData<Ts>::size > 256, "Meta array size should not exceed 256");
            mMetaData = MetaData<Ts>::data;
            mMetaDataSize = (int_fast8_t) MetaData<Ts>::size;
        }

        // TODO: I don't like this getters
        const char* getMetaData() const {
            return mMetaData;
        }

        int_fast8_t getMetaDataSize() const {
            return mMetaDataSize;
        }

    private:
        template <class R, class S> struct _PrepareSerializer {};
        template <template <class...> class R, class... Rs, template <class...> class S, class... Ss, class First, class Second>
        struct _PrepareSerializer<R<Rs>, S<First, Second, Ss>> {
            static constexpr bool isSame =    std::is_same<First, Second>::value
                                  && std::is_same<Serializer<First>::SizeCategory, Serializer<Second>::SizeCategory>::value;
            static constexpr bool isDynamic = std::is_same<Serializer<First>::SizeCategory, DynamicSizeTag>::value;

            using Type = meta::If<isSame && !isDynamic,
                                  _PrepareSerializer<R<Rs, Serializer<First>>, S<Ss>>::Type,
                                  _PrepareSerializer<R<Rs, Serializer<First>>, S<Second, Ss>>::Type>;
        };

        template <template <class...> class R, class... Rs, template <class...> class S, class First>
        struct _PrepareSerializer<R<Rs>, S<First>> {
            using Type = R<Rs, Serializer<First>>;
        };

        template <template <class...> class R, class... Rs, template <class...> class S>
        struct _PrepareSerializer<R<Rs>, S<>> {
            using Type = R<Rs>;
        };

        template <class... Ts>
        using PrepareSerializers = typename _PrepareSerializer<meta::List<>, meta::Back<Ts>>::Type;

        template <class... Ss>
        using GetValueTypes = typename meta::Append<Ss::ValueTypes...>;

        template <class... Ts>
        using MetaData = meta::RenameSequence<TypeConverter<meta::Transform<GetValueTypes, PrepareSerializers<Ts>>>, rrc::MetaArray<int8_t>>;



    private:
        ConstCharPointer mMetaData;
        int_fast8_t mMetaDataSize;
    };
}


