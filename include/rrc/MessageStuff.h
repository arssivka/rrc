/**
 *  @autor arssivka
 *  @date 7/19/16
 */

#pragma once


#include "MessageListener.h"
#include "MessageSender.h"

namespace {
    namespace pb = google::protobuf;
}

namespace rrc {
    class MessageStuff {
    public:
        typedef std::shared_ptr<MessageStuff> SPtr;

        MessageStuff();

        MessageStuff(MessageListener::SPtr listener, MessageSender::SPtr sender);

        MessageListener::SPtr getListener() const;

        void setListener(MessageListener::SPtr listener);

        MessageSender::SPtr getSender() const;

        void setSender(MessageSender::SPtr sender);

        const pb::Descriptor& getSenderDescriptor() const;

        const pb::Descriptor& getListenerDescriptor() const;

    private:
        MessageListener::SPtr mListener;
        MessageSender::SPtr mSender;

    };
}