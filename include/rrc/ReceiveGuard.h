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
        ReceiveGuard(Message::Ptr message, TypeId typeId = MetaTable::UNKNOWN_TYPE_ID) {
            static_assert(std::is_base_of<pb::MessageLite, T>::value,
                          "Template parameter of ReceiveGuard must be an instance of google::protobuf::MessageLite");
            if (message != nullptr
                    && typeId != MetaTable::UNKNOWN_TYPE_ID
                    && typeId != message->getTypeId()) {
                throw IncompatibleTypesException(typeId, message->getTypeId());
            }
            mMessage = std::move(message);
        }

        TypeId getTypeId() const {
            return mMessage->getTypeId();
        }

        std::chrono::steady_clock::time_point getTimestamp() const {
            return mMessage->getTimestamp();
        }

        const T* operator->() const {
            return (const T*) mMessage->getData();
        }

        const T* getData() const {
            return (const T*) mMessage->getData();
        }

        operator const T*() const {
            return (const T*) mMessage->getData();
        }

        bool isMessageSet() const {
            return mMessage != nullptr;
        }

    private:
        Message::Ptr mMessage;
    };
}


