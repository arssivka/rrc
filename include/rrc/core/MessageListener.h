/**
 *  @autor arssivka
 *  @date 9/23/16
 */

#pragma once


#include <memory>
#include "Buffer.h"
#include "TaskQueueAdapter.h"

namespace rrc {
    class MessageListener {
    public:
        typedef std::function<void(const Buffer&)> Callback;

        // TODO Tests and docs
        MessageListener(std::shared_ptr<TaskQueueAdapter> taskQueue, Callback&& callback);

        MessageListener(std::shared_ptr<TaskQueueAdapter> taskQueue, const Callback& callback);

        bool isOrphan() const;

        /**
         * @brief Adds message to queue
         * @param message Pointer to desired message
         */
        bool sendMessage(std::shared_ptr<Buffer> message);

        /**
         * @brief Virtual destructor of AbstractMessageListener
         */
        ~MessageListener();

    private:
        std::weak_ptr<TaskQueueAdapter> mTaskQueue;
        std::function<void(const Buffer&)> mCallback;

    };
}