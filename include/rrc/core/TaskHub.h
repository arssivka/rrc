/**
 *  @autor arssivka
 *  @date 9/23/16
 */

#pragma once


#include <memory>
#include "Buffer.h"
#include "AbstractTaskQueueAdapter.h"

namespace rrc {
    template <class T>
    class TaskHub {
    public:
        typedef std::function<void(const T&)> Callback;

        // TODO Tests and docs
        TaskHub(std::weak_ptr<AbstractTaskQueueAdapter> taskQueue, Callback&& callback)
                : mTaskQueuePtr(std::move(taskQueue)), mCallback(std::move(callback)) {}

        TaskHub(std::weak_ptr<AbstractTaskQueueAdapter> taskQueue, const Callback& callback)
                : mTaskQueuePtr(taskQueue), mCallback(callback) {}

        bool isOrphan() const {
            return mTaskQueuePtr.use_count() == 0;
        }

        /**
         * @brief Adds message to queue
         * @param message Pointer to desired message
         */
        bool enqueueTask(std::shared_ptr<T> message) {
            auto queue = mTaskQueuePtr.lock();
            if (queue != nullptr) {
                auto& callback = mCallback;
                queue->enqueue([callback, message]() {
                    callback(*message);
                });
                return true;
            } else {
                return false;
            }
        }

        /**
         * @brief Virtual destructor of AbstractMessageListener
         */
        ~TaskHub() {}

    private:
        std::weak_ptr<AbstractTaskQueueAdapter> mTaskQueuePtr;
        std::function<void(const T&)> mCallback;

    };
}