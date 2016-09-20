/**
 *  @autor arssivka
 *  @date 8/25/16
 */

#pragma once


#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <typeinfo>
#include <algorithm>
#include <typeindex>
#include <google/protobuf/message_lite.h>
#include "MessageFactory.h"

namespace {
    namespace pb = google::protobuf;
}

namespace rrc {
    typedef unsigned int TypeId;
    /**
     * @brief Table which contains types of the messages and allows to register new types and delete existing.
     */
    class MetaTable {
    public:
        static const TypeId UNKNOWN_TYPE_ID;

        MetaTable() = default;

        /**
         * @brief Retunrs type id for the specified template parameter
         * @return Type id if found, otherwise UNKNOWN_TYPE_ID
         */
        template <class T>
        TypeId getTypeId() const {
            using Type = typename std::remove_reference<T>::type;
            static_assert(std::is_base_of<pb::MessageLite, Type>::value,
                          "Type must be derived from google::protobuf::MessageLite");
            std::type_index typeIndex = typeid(Type);
            auto found = mTypeInfoHash.find(typeIndex);
            return (found != mTypeInfoHash.end()) ? found->second : UNKNOWN_TYPE_ID;
        }

        /**
         * @brief Regesters type id for the specified tamplate parameter
         * @param tid Type id, that nedds to be registered
         * @return True if succed, otherwise false
         */
        template <class T>
        bool registerTypeId(TypeId tid) {
            using Type = typename std::remove_reference<T>::type;
            static_assert(std::is_base_of<pb::MessageLite, Type>::value,
                          "Type must be derived from google::protobuf::MessageLite");
            if (this->isIdReserved(tid)) return false;
            std::type_index typeIndex = typeid(T);
            mMessageFactoryHash.insert({tid, std::make_unique<MessageFactory<T>>()});
            mTypeInfoHash.insert({typeIndex, tid});
            return true;
        }

        /**
         * @brief Returns pointer to Message Factory for the specified type id
         * @param typeId Type id to get Message FactorY for the needed type
         * @return Pointer to Message Factory
         */
        AbstractMessageFactoryPtr getMessageFactory(TypeId typeId);

        /**
         * @brief Unregister type by specified type id
         * @param typeId Type id of the type that needs to be unregistered
         * @return True if succed, otherwise false
         */
        bool freeTypeId(TypeId typeId);

        /**
         * @brief Tells if id already reserved
         * @param tid Type id to check if reserved
         * @return True if reserved, otherwise false
         */
        bool isIdReserved(TypeId tid);

    private:
        std::unordered_map<std::type_index, TypeId> mTypeInfoHash;
        std::unordered_map<TypeId, AbstractMessageFactoryPtr> mMessageFactoryHash;

    };
}


