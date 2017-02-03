/**
 *  @autor arssivka
 *  @date 9/23/16
 */

#include <rrc/core/MessageListener.h>


rrc::MessageListener::~MessageListener() { }


bool rrc::MessageListener::sendMessage(std::shared_ptr<rrc::Message> message) {
    if (!mTaskQueue.isOrphan()) {
        auto& callback = mCallback;
        mTaskQueue.enqueue([callback, message]() {
            callback(*message);
        });
        return true;
    } else {
        return false;
    }
}


rrc::MessageListener::MessageListener(rrc::TaskQueueWrapper taskQueue, rrc::MessageListener::Callback&& callback)
        : mTaskQueue(taskQueue), mCallback(std::move(callback)) {}


rrc::MessageListener::MessageListener(rrc::TaskQueueWrapper taskQueue, const rrc::MessageListener::Callback& callback)
        : mTaskQueue(taskQueue), mCallback(callback) {}
