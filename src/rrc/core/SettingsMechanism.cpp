/**
 *  @autor arssivka
 *  @date 2/15/17
 */

#include <rrc/core/SettingsMechanism.h>

rrc::SettingsMechanism::SettingsMechanism(std::shared_ptr<rrc::AbstractTaskQueueAdapter> syncQueue,
                                          rrc::QueueAdapterFactory<rrc::Task> taskQueueFactory)
        : mSyncQueue(std::move(syncQueue)),
          mTablesQueue((AbstractTaskQueueAdapter*) taskQueueFactory.createUniquePointer().release()),
          mListenersQueue((AbstractTaskQueueAdapter*) taskQueueFactory.createUniquePointer().release()),
          mChangesEnqueuedFlag(ATOMIC_FLAG_INIT) {}

rrc::Table rrc::SettingsMechanism::getTable(const rrc::SettingsMechanism::Key& name) const {
    return mSettingsHolder.getTable(name);
}

std::vector<rrc::SettingsMechanism::Key> rrc::SettingsMechanism::getNames() const {
    return mSettingsHolder.getNames();
}

void rrc::SettingsMechanism::enqueueUpdate() {
    if (mChangesEnqueuedFlag.test_and_set(std::memory_order_acquire)) {
        mSyncQueue->enqueue([this]() {
            this->applyQueues();
        });
    }
}

void rrc::SettingsMechanism::applyQueues() {
    mListenersQueue->execAll();
    mTablesQueue->execAll();
    mChangesEnqueuedFlag.clear(std::memory_order_release);
}
