/**
 *  @autor arssivka
 *  @date 11/5/16
 */

#pragma once


#include <vector>
#include "Mechanism.h"
#include "AbstractMessageListener.h"
#include "AbstractMessageFilter.h"
#include "Message.h"
#include "TopicHolder.h"
#include "rrc/meta.h"
#include "TaskQueueWrapper.h"

namespace rrc {
    class AdvertisingMechanism : public Mechanism {
    public:
        AdvertisingMechanism(TaskQueueWrapper syncQueue, TopicHolder<std::string>::Ptr topicHolder);

        /**
         * @brief Send a message
         * @param topicName Name of the topic for the message
         * @param message Pointer to the message, that needs to be sent
         */
        void sendMessage(const std::string& topicName, Message::Ptr message);

        /**
         * @brief Registers listener
         * @param topicName Name of the topic for the listener
         * @param listener Pointer to the listener that needs to be registered
         */
        void addListener(const std::string& topicName, AbstractMessageListener::Ptr listener);

        /**
         * @bried Unregisters listener
         * @param topicName Name of the topic for the listener
         * @param listener Pointer to the listener that needs to be unregistered
         */
        void removeListener(const std::string& topicName, AbstractMessageListener::Ptr listener);

        /**
         * @brief Returns set of avaliable topic names
         * @return Set of topic names
         */
        auto getTopicNames() const;

        /**
         * @brief Removes topic with the specified name from TopicHolder
         * @param topicName Name of the topic to remove
         */
        void removeTopic(const std::string& topicName);

        /**
         * @brief Sets flag for auto removing of the topic with the specified name
         * @param topicName Name of the topic to set flag in it
         * @param flag Value for the flag to be set
         */
        void setTopicAutoRemoveFlag(const std::string& topicName, bool flag);

        /**
         * @brief Sets the filter for the topic with the specified name
         * @param topicName Name of the needed topic
         * @param filter Filter to apply
         */
        void setTopicMessageFilter(const std::string& topicName, AbstractMessageFilter::Ptr filter);

    private:
        TopicHolder<std::string>::Ptr mTopicHolder;
        TaskQueueWrapper mSyncQueue;
    };
}


