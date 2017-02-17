/**
 *  @autor arssivka
 *  @date 11/5/16
 */

#include <rrc/core/AdvertisingMechanism.h>


rrc::AdvertisingMechanism::AdvertisingMechanism(std::shared_ptr<AbstractTaskQueueAdapter> syncQueue,
                                                QueueAdapterFactory<Task> taskQueueFactory)
        : mSyncQueue(std::move(syncQueue)),
          mListenersQueue((AbstractTaskQueueAdapter*) taskQueueFactory.createUniquePointer().release()),
          mMessagesQueue((AbstractTaskQueueAdapter*) taskQueueFactory.createUniquePointer().release()) {}


std::vector<std::string> rrc::AdvertisingMechanism::getNames() const {
    return mTopicHolder.getNames();
}

void rrc::AdvertisingMechanism::enqueueUpdate() {
    if (mChangesEnqueuedFlag.test_and_set(std::memory_order_acquire)) {
        mSyncQueue->enqueue([this]() {
            this->applyQueues();
        });
    }
}

void rrc::AdvertisingMechanism::applyQueues() {
    mListenersQueue->execAll();
    mMessagesQueue->execAll();
    mChangesEnqueuedFlag.clear(std::memory_order_release);
}


