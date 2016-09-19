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
        /**
         * @brief Constructor of message
         * @param typeId Type id of the message
         * @param timestamp Time  stamp of type chrono::steady_clock::time_point
         * @param data Data to store in message of type protobuf::MessageLite
         */
        Message(TypeId typeId,
                std::chrono::steady_clock::time_point timestamp,
                std::unique_ptr<pb::MessageLite> data)
                : mTypeId(typeId), mTimestamp(timestamp), mDataPtr(std::move(data)) { }

        /**
         * @brief Operator -> override
         * @return Const pointer to protobuf::MessageLite
         */
        const pb::MessageLite* operator->() const {
            return mDataPtr.get();
        }

        /**
         * @brief Returns pointer to message
         * @return Const to pointer to protobuf::MessageLite
         */
        const pb::MessageLite* getData() const {
            return mDataPtr.get();
        }

        operator const pb::MessageLite*() const {
            return mDataPtr.get();
        }

        /**
         * @brief Returns time stamp of the message
         * @return Time stamp of type chrono::steady_clock::time_point
         */
        std::chrono::steady_clock::time_point getTimestamp() const noexcept {
            return mTimestamp;
        }

        /**
         * @brief Returns type id og the message.
         * @return Type id
         */
        TypeId getTypeId() const noexcept {
            return mTypeId;
        }

    private:
        TypeId mTypeId;
        std::chrono::steady_clock::time_point mTimestamp;
        std::unique_ptr<pb::MessageLite> mDataPtr;

    };

    typedef std::shared_ptr<Message> MessagePtr;
}


