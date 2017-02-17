/**
 *  @autor arssivka
 *  @date 2/7/17
 */

#include <rrc/core/ServiceMechanism.h>


rrc::ServiceMechanism::ServiceMechanism(std::shared_ptr<AbstractTaskQueueAdapter> syncQueue,
                                        QueueAdapterFactory <Task> taskQueueFactory)
        : mSyncQueue(std::move(syncQueue)),
          mServicesQueue((AbstractTaskQueueAdapter*) taskQueueFactory.createUniquePointer().release()),
          mCallsQueue((AbstractTaskQueueAdapter*) taskQueueFactory.createUniquePointer().release()) {}


std::vector<rrc::ServiceMechanism::Name> rrc::ServiceMechanism::getNames() const {
    return mServiceHolder.getNames();
}

void rrc::ServiceMechanism::enqueueUpdate() {
    if (mChangesEnqueuedFlag.test_and_set(std::memory_order_acquire)) {
        mSyncQueue->enqueue([this]() {
            this->applyQueues();
        });
    }
}

void rrc::ServiceMechanism::applyQueues() {
    mServicesQueue->execAll();
    mCallsQueue->execAll();
    mChangesEnqueuedFlag.clear(std::memory_order_release);
}
