/**
 *  @autor arssivka
 *  @date 9/5/16
 */

#pragma once


#include <google/protobuf/message_lite.h>
#include "MessageFactoryBase.h"

namespace {
    namespace pb = google::protobuf;
}

namespace rrc {
    template <class T>
    class MessageFactory : public MessageFactoryBase {
    public:
        virtual std::unique_ptr<pb::MessageLite> createMessage() override {
            return std::make_unique<T>();
        }
    };
}


