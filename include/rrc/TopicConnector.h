/**
 *  @autor arssivka
 *  @date 7/13/16
 */

#pragma once


#include <google/protobuf/descriptor.h>
#include "MessageListener.h"
#include "ID.h"
#include "MessageSender.h"

namespace rrc {
    class TopicConnector {
    public:
        TopicConnector(const pb::Descriptor& descriptor);

        bool checkDescriptor(const pb::Descriptor& descriptor);

        bool addListener(const ID& id, MessageListener* listener, bool directCallEnabled);

        bool detachListener(const MessageListener* listener);

        bool addSender(MessageSender* sender);

        bool detachSender(const MessageSender* sender);

    };
}