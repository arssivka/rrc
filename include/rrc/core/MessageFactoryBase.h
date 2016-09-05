/**
 *  @autor arssivka
 *  @date 9/5/16
 */

#pragma once


#include <google/protobuf/message_lite.h>
#include <memory>

namespace {
    namespace pb = google::protobuf;
}

namespace rrc {
    class MessageFactoryBase {
    public:
        virtual std::unique_ptr<pb::MessageLite> createMessage() = 0;

        virtual ~MessageFactoryBase() { }

    };

    typedef std::shared_ptr<MessageFactoryBase> MessageFactoryPtr;
}