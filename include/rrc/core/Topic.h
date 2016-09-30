/**
 *  @autor arssivka
 *  @date 8/24/16
 */

#pragma once


#include <forward_list>
#include "AbstractMessageListener.h"
#include "NonCopyable.h"
#include "AbstractMessageFilter.h"

namespace {
    namespace pb = google::protobuf;
}

namespace rrc {
    /**
     * @brief All messages come to topics. Topic is a special place for holding specific messages. Nodes can subscribe to tpoics to get messages they need.
     */
    class Topic {
    public:
        /**
         * @brief Default constructor of Topic
         */
        Topic();

        /**
         * @brief Register message listener
         * @param listener Pointer to listener to register
         */
        void addListener(AbstractMessageListenerPtr listener);

        /**
         * @brief Unregisters specified listener
         * @param listener Pointer to listener that needs to be unregistred
         */
        void removeListener(AbstractMessageListenerPtr listener);

        /**
         * @brief Sends the message
         * @param message Pointer to message that needs to be sent
         */
        void sendMessage(MessagePtr message);

        /**
         * @brief Checks if this topic has listeners
         * @return True if topic has lesteners, otherwise false
         */
        bool hasListeners() const;

        bool isAutoRemoveEnabled() const;

        void setAutoRemoveEnabled(bool autoRemoveEnabled);

        bool isMessageFilterEnabled() const;

        void setMessageFilterEnabled(bool filterEnabled);

        AbstractMessageFilterPtr getMessageFilter() const;

        void setMessageFilter(AbstractMessageFilterPtr messageFilter);

    private:
        AbstractMessageFilterPtr mMessageFilter;
        std::forward_list<AbstractMessageListenerPtr> mListenersList;
        bool mAutoRemoveEnabled;
        bool mMessageFilterEnabled;

    };

    typedef std::shared_ptr<Topic> TopicPtr;
}


