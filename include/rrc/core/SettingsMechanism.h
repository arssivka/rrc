/**
 *  @autor arssivka
 *  @date 2/15/17
 */

#pragma once


#include "Table.h"
#include "AbstractTaskQueueAdapter.h"
#include "SettingsHolder.h"
#include "QueueAdapterFactory.h"
#include <atomic>

namespace rrc {
    class SettingsMechanism {
    public:
        typedef std::string Key;
        typedef SettingsHolder<Key> Holder;

        SettingsMechanism(std::shared_ptr<AbstractTaskQueueAdapter> syncQueue,
                          QueueAdapterFactory<Task> taskQueueFactory);

        Table getTable(const Key& name) const;

        template <class K, class T>
        void setTable(K&& name, T&& table) {
            auto& settingsHolderRef = mSettingsHolder;
            mTablesQueue->enqueue([&settingsHolderRef, nameCap{ std::forward<K>(name) },
                                          tableCap{ std::forward<T>(table) }]() mutable {
                settingsHolderRef.setTable(std::move(nameCap), std::move(tableCap));
            });
            this->enqueueUpdate();
        }

        template <class K>
        void addListener(K&& name, std::shared_ptr<Holder::Listener> listener) {
            auto& settingsHolderRef = mSettingsHolder;
            mTablesQueue->enqueue([&settingsHolderRef, nameCap{ std::forward<K>(name) },
                                          listenerCap{ std::move(listener) }]() mutable {
                settingsHolderRef.addListener(std::move(nameCap), std::move(listenerCap));
            });
            this->enqueueUpdate();
        }

        template <class K>
        void removeListener(K&& name, std::weak_ptr<Holder::Listener> listener) {
            auto& settingsHolderRef = mSettingsHolder;
            mTablesQueue->enqueue([&settingsHolderRef, listener, nameCap{ std::forward<K>(name) }]() mutable {
                settingsHolderRef.removeListener(std::move(nameCap), listener);
            });
            this->enqueueUpdate();
        }

        std::vector<Key> getNames() const;


    private:
        void enqueueUpdate();

        void applyQueues();


    private:
        Holder mSettingsHolder;
        std::shared_ptr<AbstractTaskQueueAdapter> mSyncQueue;
        std::unique_ptr<AbstractTaskQueueAdapter> mTablesQueue;
        std::unique_ptr<AbstractTaskQueueAdapter> mListenersQueue;
        std::atomic_flag mChangesEnqueuedFlag;
    };
}


