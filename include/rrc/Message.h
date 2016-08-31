/**
 *  @autor arssivka
 *  @date 7/11/16
 */

#pragma once


#include <memory>
#include <chrono>
#include <google/protobuf/message_lite.h>
#include "NonCopyable.h"
#include "MetaTable.h"

namespace {
    namespace pb = google::protobuf;
}

namespace rrc {
    class Message : private NonCopyable {
    public:
        typedef std::shared_ptr<Message> Ptr;

        Message(TypeId typeId,
                std::chrono::steady_clock::time_point timestamp,
                std::unique_ptr<pb::MessageLite> data)
                : mTypeId(typeId), mTimestamp(timestamp), mDataPtr(std::move(data)) { }


        const pb::MessageLite* operator->() const {
            return mDataPtr.get();
        }

        const pb::MessageLite* getData() const {
            return mDataPtr.get();
        }

        operator const pb::MessageLite*() const {
            return mDataPtr.get();
        }

        std::chrono::steady_clock::time_point getTimestamp() const noexcept {
            return mTimestamp;
        }

        TypeId getTypeId() const noexcept {
            return mTypeId;
        }

    private:
        TypeId mTypeId;
        std::chrono::steady_clock::time_point mTimestamp;
        std::unique_ptr<pb::MessageLite> mDataPtr;

    };
}


