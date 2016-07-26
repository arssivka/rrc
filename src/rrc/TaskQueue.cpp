/**
 *  @autor arssivka
 *  @date 7/20/16
 */

#include <rrc/TaskQueue.h>


void rrc::TaskQueue::execOnce() {
    if (this->isDisabled()) return;
    TSFunctionQueue::SPtr task = mTaskQueue.pop();
    if (task != nullptr) {
        auto& func = *task;
        func();
    }
}


void rrc::TaskQueue::execAll() {
    if (this->isDisabled()) return;
    TSFunctionQueue::SPtr task;
    while ((task = mTaskQueue.pop()) != nullptr) {
        auto& func = *task;
        func();
    }
}


void rrc::TaskQueue::disable() {
    mDisabled.store(true, std::memory_order_release);
}


bool rrc::TaskQueue::isDisabled() const {
    return mDisabled.load(std::memory_order_acquire);
}