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
    class Topic : public Pointer<Topic> {
    public:
        /**
         * @brief Default constructor of Topic
         */
        Topic();

        /**
         * @brief Register message listener
         * @param listener Pointer to listener to register
         */
        void addListener(AbstractMessageListener::Ptr listener);

        /**
         * @brief Unregisters specified listener
         * @param listener Pointer to listener that needs to be unregistred
         */
        void removeListener(AbstractMessageListener::Ptr listener);

        /**
         * @brief Sends the message
         * @param message Pointer to message that needs to be sent
         */
        void sendMessage(Message::Ptr message);

        /**
         * @brief Checks if this topic has listeners
         * @return True if topic has lesteners, otherwise false
         */
        bool hasListeners() const;

        /**
         * @brief Checks if auto remove flag is set
         * @return True if set, otherwise false
         */
        bool isAutoRemoveEnabled() const;

        /**
         * @brief Sets flag of auto removing
         * @param autoRemoveEnabled Value to set to the flag
         */
        void setAutoRemoveEnabled(bool autoRemoveEnabled);

        /**
         * @brief Checks if message filter is enabled
         * @return True if enabled, otherwise false
         */
        bool isMessageFilterEnabled() const;

        /**
         * @brief Enables or disables message filter
         * @param filterEnabled Pass true if the filter is needed otherwise false
         */
        void setMessageFilterEnabled(bool filterEnabled);

        /**
         * @brief Returns message filter apllied to this topic
         * @return Pointer to message filter
         */
        AbstractMessageFilter::Ptr getMessageFilter() const;

        /**
         * @brief Sets message filter to this topic
         * @param messageFilter Pointer to needed message filter
         */
        void setMessageFilter(AbstractMessageFilter::Ptr messageFilter);

    private:
        AbstractMessageFilter::Ptr mMessageFilter;
        std::forward_list<AbstractMessageListener::Ptr> mListenersList;
        bool mAutoRemoveEnabled;
        bool mMessageFilterEnabled;

    };
}


