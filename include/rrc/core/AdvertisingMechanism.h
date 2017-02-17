/**
 *  @autor arssivka
 *  @date 11/5/16
 */

#pragma once


#include <vector>
#include "TaskHub.h"
#include "Buffer.h"
#include "TopicHolder.h"
#include "AbstractTaskQueueAdapter.h"
#include "QueueAdapterFactory.h"

namespace rrc {
    class AdvertisingMechanism : private NonCopyable {
    public:
        typedef std::string Name;

        AdvertisingMechanism(std::shared_ptr<AbstractTaskQueueAdapter> syncQueue,
                                     QueueAdapterFactory <Task> taskQueueFactory);

        /**
         * @brief Send a message
         * @param topicName Name of the topic for the message
         * @param message Pointer to the message, that needs to be sent
         */
        template <class K>
        void sendMessage(K&& topicName, std::shared_ptr<Buffer> message) {
            auto& topicHolderRef = mTopicHolder;
            mMessagesQueue->enqueue([&topicHolderRef, topicNameCap = std::forward<K>(topicName),
                                        messageCap = std::move(message)]() mutable {
                topicHolderRef.sendMessage(topicNameCap, std::move(messageCap));
            });
        }

        /**
         * @brief Registers listener
         * @param topicName Name of the topic for the listener
         * @param listener Pointer to the listener that needs to be registered
         */
        template <class K>
        void addListener(K&& topicName, std::shared_ptr<TaskHub<Buffer>> listener) {
            auto& topicHolderRef = mTopicHolder;
            mListenersQueue->enqueue([&topicHolderRef, topicNameCap = std::forward<K>(topicName),
                                             listenerCap = std::move(listener)]() mutable {
                topicHolderRef.addListener(topicNameCap, std::move(listenerCap));
            });
        }

        // TODO Tests and docs
        template <class K>
        void removeListener(K&& topicName, const std::weak_ptr<TaskHub<Buffer>> listener) {
            auto& topicHolderRef = mTopicHolder;
            mListenersQueue->enqueue([&topicHolderRef, topicNameCap = std::forward<K>(topicName),
                                             listenerCap = std::move(listener)]() mutable {
                topicHolderRef.removeListener(topicNameCap, std::move(listenerCap));
            });
        }

        /**
         * @brief Returns set of avaliable topic names
         * @return Set of topic names
         */
        std::vector<Name> getNames() const;

    private:
        void enqueueUpdate();

        void applyQueues();

    private:
        TopicHolder<Name> mTopicHolder;
        std::shared_ptr<AbstractTaskQueueAdapter> mSyncQueue;
        std::unique_ptr<AbstractTaskQueueAdapter> mListenersQueue;
        std::unique_ptr<AbstractTaskQueueAdapter> mMessagesQueue;
        std::atomic_flag mChangesEnqueuedFlag;
    };
}


