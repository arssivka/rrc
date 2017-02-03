/**
 *  @autor arssivka
 *  @date 11/5/16
 */

#pragma once


#include <vector>
#include "MessageListener.h"
#include "Message.h"
#include "TopicHolder.h"
#include "TaskQueueWrapper.h"

namespace rrc {
    class AdvertisingMechanism : private NonCopyable {
    public:
        AdvertisingMechanism(TaskQueueWrapper syncQueue);

        /**
         * @brief Send a message
         * @param topicName Name of the topic for the message
         * @param message Pointer to the message, that needs to be sent
         */
        void sendMessage(const std::string& topicName, std::shared_ptr<Message> message);

        /**
         * @brief Registers listener
         * @param topicName Name of the topic for the listener
         * @param listener Pointer to the listener that needs to be registered
         */
        void addListener(const std::string& topicName, std::shared_ptr<MessageListener> listener);

        /**
         * @brief Returns set of avaliable topic names
         * @return Set of topic names
         */
        std::vector<std::string> getTopicNames() const;

        /**
         * @brief Removes topic with the specified name from TopicHolder
         * @param topicName Name of the topic to remove
         */
        void removeTopic(const std::string& topicName);

    private:
        TopicHolder<std::string> mTopicHolder;
        TaskQueueWrapper mSyncQueue;
    };
}


