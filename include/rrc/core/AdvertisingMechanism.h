/**
 *  @autor arssivka
 *  @date 11/5/16
 */

#pragma once


#include <vector>
#include "MessageListener.h"
#include "Buffer.h"
#include "TopicHolder.h"
#include "AbstracrTaskQueueAdapter.h"

namespace rrc {
    class AdvertisingMechanism : private NonCopyable {
    public:
        AdvertisingMechanism(std::shared_ptr<AbstracrTaskQueueAdapter> syncQueue);

        /**
         * @brief Send a message
         * @param topicName Name of the topic for the message
         * @param message Pointer to the message, that needs to be sent
         */
        void sendMessage(const std::string& topicName, std::shared_ptr<Buffer> message);

        /**
         * @brief Registers listener
         * @param topicName Name of the topic for the listener
         * @param listener Pointer to the listener that needs to be registered
         */
        void addListener(const std::string& topicName, std::shared_ptr<MessageListener> listener);

        // TODO Tests and docs
        void removeListener(const std::string& topicName, const std::weak_ptr<MessageListener> listener);

        /**
         * @brief Returns set of avaliable topic names
         * @return Set of topic names
         */
        std::vector<std::string> getTopicNames() const;

    private:
        TopicHolder<std::string> mTopicHolder;
        std::shared_ptr<AbstracrTaskQueueAdapter> mSyncQueue;
    };
}


