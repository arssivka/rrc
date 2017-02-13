/**
 *  @autor arssivka
 *  @date 9/23/16
 */

#pragma once


#include <memory>
#include "Buffer.h"
#include "AbstracrTaskQueueAdapter.h"

namespace rrc {
    class TaskHub {
    public:
        typedef std::function<void(const Buffer&)> Callback;

        // TODO Tests and docs
        TaskHub(std::weak_ptr<AbstracrTaskQueueAdapter> taskQueue, Callback&& callback);

        TaskHub(std::weak_ptr<AbstracrTaskQueueAdapter> taskQueue, const Callback& callback);

        bool isOrphan() const;

        /**
         * @brief Adds message to queue
         * @param message Pointer to desired message
         */
        bool enqueueTask(std::shared_ptr<Buffer> message);

        /**
         * @brief Virtual destructor of AbstractMessageListener
         */
        ~TaskHub();

    private:
        std::weak_ptr<AbstracrTaskQueueAdapter> mTaskQueuePtr;
        std::function<void(const Buffer&)> mCallback;

    };
}