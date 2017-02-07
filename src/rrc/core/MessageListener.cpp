/**
 *  @autor arssivka
 *  @date 9/23/16
 */

#include <rrc/core/MessageListener.h>


rrc::MessageListener::~MessageListener() { }


bool rrc::MessageListener::sendMessage(std::shared_ptr<rrc::Buffer> message) {
    auto queue = mTaskQueue.lock();
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


rrc::MessageListener::MessageListener(std::shared_ptr<AbstracrTaskQueueAdapter> taskQueue, rrc::MessageListener::Callback&& callback)
        : mTaskQueue(std::move(taskQueue)), mCallback(std::move(callback)) {}


rrc::MessageListener::MessageListener(std::shared_ptr<AbstracrTaskQueueAdapter> taskQueue, const rrc::MessageListener::Callback& callback)
        : mTaskQueue(taskQueue), mCallback(callback) {}


bool rrc::MessageListener::isOrphan() const {
    return mTaskQueue.use_count() == 0;
}
