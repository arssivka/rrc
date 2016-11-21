/**
 *  @autor arssivka
 *  @date 7/13/16
 */

#pragma once


#include <queue>
#include "AbstractMessageListener.h"

namespace {
    namespace pb = google::protobuf;
}

namespace rrc {
    class QueueMessageListener : public AbstractMessageListener {
    public:
        // TODO Comment
        QueueMessageListener(TypeId typeId);

        /**
         * @brief Adds message to queue
         * @param msg Pointer to desired message
         */
        virtual void enqueueMessage(Message::Ptr msg) override;

        /**
         * @brief Tries to dequeue message from queue
         * @return Pointer to message
         */
        virtual Message::Ptr tryDequeueMessage() override;

    private:
        std::queue<Message::Ptr> mMessagesQueue;

    };
}