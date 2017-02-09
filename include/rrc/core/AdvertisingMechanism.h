/**
 *  @autor arssivka
 *  @date 11/5/16
 */

#pragma once


#include <vector>
#include "TaskHub.h"
#include "Buffer.h"
#include "TopicHolder.h"
#include "AbstracrTaskQueueAdapter.h"

namespace rrc {
    class AdvertisingMechanism : private NonCopyable {
    public:
        typedef std::string Name;

        AdvertisingMechanism(std::shared_ptr<AbstracrTaskQueueAdapter> syncQueue);

        /**
         * @brief Send a message
         * @param topicName Name of the topic for the message
         * @param message Pointer to the message, that needs to be sent
         */
        void sendMessage(const Name& topicName, std::shared_ptr<Buffer> message);

        /**
         * @brief Registers listener
         * @param topicName Name of the topic for the listener
         * @param listener Pointer to the listener that needs to be registered
         */
        void addListener(const Name& topicName, std::shared_ptr<TaskHub> listener);

        // TODO Tests and docs
        void removeListener(const Name& topicName, const std::weak_ptr<TaskHub> listener);

        /**
         * @brief Returns set of avaliable topic names
         * @return Set of topic names
         */
        std::vector<Name> getNames() const;

    private:
        TopicHolder<Name> mTopicHolder;
        std::shared_ptr<AbstracrTaskQueueAdapter> mSyncQueue;
    };
}


