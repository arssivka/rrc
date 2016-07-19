/**
 *  @autor arssivka
 *  @date 7/19/16
 */

#pragma once


#include "MessageListener.h"
#include "MessageSender.h"

namespace rrc {
    class MessageStuff {
    public:
        MessageStuff();

        MessageStuff(MessageListener* listener, MessageSender* sender);

        MessageListener* getListener() const;

        void setListener(MessageListener* listener);

        MessageSender* getSender() const;

        void setSender(MessageSender* sender);

    private:
        MessageListener* mListener;
        MessageSender* mSender;

    };
}