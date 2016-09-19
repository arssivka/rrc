/**
 *  @autor arssivka
 *  @date 9/5/16
 */

#pragma once


#include <google/protobuf/message_lite.h>
#include "AbstractMessageFactory.h"

namespace {
    namespace pb = google::protobuf;
}

namespace rrc {
    template <class T>
    class MessageFactory : public AbstractMessageFactory {
    public:
        /**
         * @brief Creates message inherited from protobuf::MessageLite
         * @return Unique pointer to created message
         */
        virtual std::unique_ptr<pb::MessageLite> createMessage() override {
            return std::make_unique<T>();
        }
    };
}


