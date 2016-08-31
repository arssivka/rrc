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

namespace {
    namespace pb = google::protobuf;
}

namespace rrc {
    typedef unsigned int TypeId;

    class MetaTable {
    public:
        static const TypeId UNKNOWN_TYPE_ID = std::numeric_limits<TypeId>::max();

        MetaTable() = default;

        template <class T>
        TypeId getTypeId() const {
            std::type_index typeIndex = typeid(T);
            auto found = mTypeInfoHash.find(typeIndex);
            return (found != mTypeInfoHash.end()) ? found->second : UNKNOWN_TYPE_ID;
        }

        size_t getTypeSizeById(TypeId tid) const {
            auto found = mReservedIds.find(tid);
            if (found != mReservedIds.end()) {
                return found->second;
            }
            return 0;
        }

        template <class T>
        bool registerTypeId(TypeId tid) {
            using Type = typename std::remove_reference<T>::type;
            static_assert(std::is_base_of<pb::MessageLite, Type>::value,
                          "Type must be derived from google::protobuf::MessageLite");
            if (this->isIdReserved(tid)) return false;
            std::type_index typeIndex = typeid(T);
            size_t size = sizeof(T);
            mReservedIds.insert({tid, size});
            mTypeInfoHash.insert({typeIndex, tid});
            return true;
        }

        bool freeTypeId(TypeId typeId);

        bool isIdReserved(TypeId tid);

    private:
        std::unordered_map<std::type_index, TypeId> mTypeInfoHash;
        std::unordered_map<TypeId, size_t> mReservedIds;

    };
}


