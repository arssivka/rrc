/**
 *  @autor arssivka
 *  @date 9/23/16
 */

#include <rrc/core/TaskHub.h>


rrc::TaskHub::~TaskHub() { }


bool rrc::TaskHub::enqueueTask(std::shared_ptr<rrc::Buffer> message) {
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


rrc::TaskHub::TaskHub(std::weak_ptr<AbstracrTaskQueueAdapter> taskQueue, rrc::TaskHub::Callback&& callback)
        : mTaskQueuePtr(std::move(taskQueue)), mCallback(std::move(callback)) {}


rrc::TaskHub::TaskHub(std::weak_ptr<AbstracrTaskQueueAdapter> taskQueue, const rrc::TaskHub::Callback& callback)
        : mTaskQueuePtr(taskQueue), mCallback(callback) {}


bool rrc::TaskHub::isOrphan() const {
    return mTaskQueuePtr.use_count() == 0;
}
