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
        MessageStuff();

        MessageStuff(MessageListener* listener, MessageSender* sender);

        MessageListener* getListener() const;

        void setListener(MessageListener* listener);

        MessageSender* getSender() const;

        void setSender(MessageSender* sender);

        const pb::Descriptor& getSenderDescriptor() const;

        const pb::Descriptor& getListenerDescriptor() const;

    private:
        MessageListener* mListener;
        MessageSender* mSender;

    };
}