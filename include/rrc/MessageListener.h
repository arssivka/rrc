/**
 *  @autor arssivka
 *  @date 7/13/16
 */

#pragma once


#include <atomic>
#include <concurrentqueue.h>
#include "Message.h"

namespace {
    namespace pb = google::protobuf;
}

namespace rrc {
    class MessageListener {
    public:
        typedef std::shared_ptr<MessageListener> Ptr;

        MessageListener(TypeId typeId);

        void enqueueMessage(Message::Ptr msg);

        Message::Ptr tryDequeueMessage();

        TypeId getTypeId() const;

    private:
        TypeId mTypeId;
        moodycamel::ConcurrentQueue<Message::Ptr> mMessagesQueue;

    };
}