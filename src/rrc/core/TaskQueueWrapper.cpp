/**
 *  @autor arssivka
 *  @date 7/20/16
 */

#include <rrc/core/TaskQueueWrapper.h>


rrc::TaskQueueWrapper::TaskQueueWrapper(std::shared_ptr<rrc::AbstractQueueAdapter<Task>> queueAdapter)
        : mQueueAdapter(std::move(queueAdapter)) {}


rrc::TaskQueueWrapper::TaskQueueWrapper(rrc::TaskQueueWrapper&& other)
        : mQueueAdapter(std::move(other.mQueueAdapter)) {}


bool rrc::TaskQueueWrapper::tryDequeue(rrc::Task& task) {
    return mQueueAdapter->tryDequeue(task);
}


bool rrc::TaskQueueWrapper::execOnce() {
    Task task;
    if (mQueueAdapter->tryDequeue(task)) {
        task();
        return true;
    }
    return false;
}


void rrc::TaskQueueWrapper::execAll() {
    Task task;
    while (mQueueAdapter->tryDequeue(task)) {
        task();
    }
}


bool rrc::TaskQueueWrapper::operator==(const rrc::TaskQueueWrapper& rhs) const {
    return mQueueAdapter == rhs.mQueueAdapter;
}


bool rrc::TaskQueueWrapper::operator!=(const rrc::TaskQueueWrapper& rhs) const {
    return !(rhs == *this);
}


void rrc::TaskQueueWrapper::enqueue(const rrc::Task& task) {
    mQueueAdapter->enqueue(task);
}


void rrc::TaskQueueWrapper::enqueue(rrc::Task&& task) {
    mQueueAdapter->enqueue(std::move(task));
}


bool rrc::TaskQueueWrapper::isOrphan() const {
    return mQueueAdapter.unique();
}
