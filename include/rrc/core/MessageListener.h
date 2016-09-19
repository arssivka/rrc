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
        /**
         * @brief Constructor of Message Listener
         * @param typeId Type id of messages to listen
         */
        MessageListener(TypeId typeId);

        /**
         * @brief Adds message to queue
         * @param msg Pointer to desired message
         */
        void enqueueMessage(MessagePtr msg);

        /**
         * @brief Tries to dequeue message from queue
         * @return Pointer to message
         */
        MessagePtr tryDequeueMessage();

        /**
         * @brief Returns type id of messages that of this message listener
         * @return
         */
        TypeId getTypeId() const;

    private:
        TypeId mTypeId;
        moodycamel::ConcurrentQueue<MessagePtr> mMessagesQueue;

    };

    typedef std::shared_ptr<MessageListener> MessageListenerPtr;
}