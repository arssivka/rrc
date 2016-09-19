/**
 *  @autor arssivka
 *  @date 8/31/16
 */

#pragma once


#include "Message.h"
#include "IncompatibleTypesException.h"

namespace {
    namespace pb = google::protobuf;
}

namespace rrc {
    template <class T>
    class ReceiveGuard {
    public:
        /**
         * @brief Constructor of Receieve Guard.
         * @param message Message to guard.
         * @param typeId Type id of the message. UNKNOWN_TYPE_ID if not set.
         */
        ReceiveGuard(MessagePtr message, TypeId typeId = MetaTable::UNKNOWN_TYPE_ID) {
            static_assert(std::is_base_of<pb::MessageLite, T>::value,
                          "Template EXPEparameter of ReceiveGuard must be an instance of google::protobuf::MessageLite");
            if (message != nullptr
                    && typeId != MetaTable::UNKNOWN_TYPE_ID
                    && typeId != message->getTypeId()) {
                throw IncompatibleTypesException(typeId, message->getTypeId());
            }
            mMessage = std::move(message);
        }

        /**
         * @brief Returns type id og the message.
         * @return Type id
         */
        TypeId getTypeId() const {
            return mMessage->getTypeId();
        }

        /**
         * @brief Returns time stamp of the message
         * @return Time stamp of type chrono::steady_clock::time_point
         */
        std::chrono::steady_clock::time_point getTimestamp() const {
            return mMessage->getTimestamp();
        }

        /**
         * @brief Operator -> override
         * @return Const pointer to message
         */
        const T* operator->() const {
            return (const T*) mMessage->getData();
        }

        /**
         * @brief Retunrs pointer to message
         * @return Const pointer to message
         */
        const T* getData() const {
            return (const T*) mMessage->getData();
        }

        operator const T*() const {
            return (const T*) mMessage->getData();
        }

        /**
         * @brief Checks if message is not empty
         * @return True if message's empty, otherwise false
         */
        bool isMessageSet() const {
            return mMessage != nullptr;
        }

    private:
        MessagePtr mMessage;
    };
}


