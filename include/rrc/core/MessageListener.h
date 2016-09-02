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
        MessageListener(TypeId typeId);

        void enqueueMessage(MessagePtr msg);

        MessagePtr tryDequeueMessage();

        TypeId getTypeId() const;

    private:
        TypeId mTypeId;
        moodycamel::ConcurrentQueue<MessagePtr> mMessagesQueue;

    };

    typedef std::shared_ptr<MessageListener> MessageListenerPtr;
}