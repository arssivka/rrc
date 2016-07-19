/**
 *  @autor arssivka
 *  @date 7/13/16
 */

#pragma once


#include <google/protobuf/descriptor.h>
#include "MessageListener.h"
#include "ID.h"
#include "MessageSender.h"

namespace {
    namespace pb = google::protobuf;
}

namespace rrc {
    class TopicConnector {
        TopicConnector(const pb::Descriptor& descriptor);

        bool checkDescriptor(const pb::Descriptor& descriptor);

        bool addListener(const ID& id, MessageListener* listener,
                         const pb::Descriptor& descriptor, bool directCallEnabled);

        bool detachListener(const MessageListener* listener);

        bool addSender(MessageSender* sender);

        bool detachSender(const MessageSender* sender);

    };
}