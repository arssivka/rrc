/**
 *  @autor arssivka
 *  @date 9/23/16
 */

#pragma once


#include <memory>
#include "Message.h"
#include "TypeConverter.h"
#include "TaskQueueWrapper.h"

namespace rrc {
    class MessageListener {
    public:
        typedef std::function<void(const Message&)> Callback;

        // TODO Tests and docs
        MessageListener(TaskQueueWrapper taskQueue, Callback&& callback);

        MessageListener(TaskQueueWrapper taskQueue, const Callback& callback);

        /**
         * @brief Adds message to queue
         * @param message Pointer to desired message
         */
        bool sendMessage(std::shared_ptr<Message> message);

        /**
         * @brief Virtual destructor of AbstractMessageListener
         */
        ~MessageListener();

    private:
        TaskQueueWrapper mTaskQueue;
        std::function<void(const Message&)> mCallback;

    };
}