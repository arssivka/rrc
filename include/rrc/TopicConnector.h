/**
 *  @autor arssivka
 *  @date 7/13/16
 */

#pragma once


#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#include "MessageListener.h"
#include "ID.h"
#include "MessageSender.h"
#include "TSList.h"

namespace {
    namespace pb = google::protobuf;
}

namespace rrc {
    class TopicConnector : private NonCopyable {
    public:
        TopicConnector() = default;

        TopicConnector(const pb::Descriptor& descriptor);


        const pb::Descriptor& getDescriptor() const;


        void setDescriptor(const pb::Descriptor& descriptor);


        bool checkDescriptor(const pb::Descriptor& descriptor);

        bool addListener(MessageListener::SPtr listener);

        bool detachListener(const MessageListener::SPtr listener);

        bool addSender(MessageSender::SPtr sender);

        bool detachSender(MessageSender::SPtr sender);

    private:
        bool sendMessage(const ID& id, Message<pb::Message> message, bool directCall);

    private:
        typedef TSList<MessageSender> SendersList;
        typedef TSList<MessageListener> ListenersList;

        const pb::Descriptor* mDescriptor;
        SendersList mSendersList;
        ListenersList mListenersList;

    };
}