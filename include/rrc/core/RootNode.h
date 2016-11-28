/**
 *  @autor arssivka
 *  @date 8/25/16
 */

#pragma once


#include <concurrentqueue.h>
#include "AbstractNode.h"
#include "Message.h"
#include "AbstractMessageListener.h"
#include "TopicHolder.h"
#include "TaskQueue.h"
#include "MetaTable.h"
#include "SettingsHolder.h"

namespace rrc {
    class Node;
    typedef std::shared_ptr<Node> NodePtr;
    class AbstractLauncher;
    /**
     * @brief The main node. It's responsible for syncronisation bentween nodes.
     */
    class RootNode : public AbstractNode {
    public:
        typedef std::string TopicName;

    public:

        /**
         * @brief Constructor of Root Node
         * @param launcher reference to Launcher Base instance
         * @param metaTable reference to Meta TAble instance
         */
        RootNode(AbstractLauncher& launcher, MetaTable& metaTable, SettingsHolder& settingsHolder);

        /**
         * @brief Runs the synchronization algorhythm
         */
        virtual void entry() override;

        /**
         * @brief Send a message
         * @param topicName Name of the topic for the message
         * @param message Pointer to the message, that needs to be sent
         */
        void sendMessage(const TopicName& topicName, MessagePtr message);

        /**
         * @brief Registers node for the synchronization
         * @param node Pointer to the node, that nees to be registered
         */
        void addNode(NodePtr node);

        /**
         * @brief Unregisters node
         * @param node Pointer to the node that needs to be unregistered
         */
        void removeNode(NodePtr node);

        /**
         * @brief Registers listener
         * @param topicName Name of the topic for the listener
         * @param listener Pointer to the listener that needs to be registered
         */
        void addListener(const TopicName& topicName, AbstractMessageListenerPtr listener);

        /**
         * @bried Unregisters listener
         * @param topicName Name of the topic for the listener
         * @param listener Pointer to the listener that needs to be unregistered
         */
        void removeListener(const TopicName& topicName, AbstractMessageListenerPtr listener);

        /**
         * @brief Stops the node from execution
         */
        void stop();

        /**
         * @brief Returns type id for the specified tamplate parameter
         * @return Type id if found, otherwise UNKNOWN_TYPE_ID
         */
        template <class T>
        TypeId getTypeId() {
            return mMetaTable->getTypeId<T>();
        }

        /**
         * @brief Returns set of avaliable topic names
         * @return Set of topic names
         */
        std::vector<TopicName> getTopicNames() const {
            return mTopicHolder.getTopicNames();
        }

        /**
         * @brief Removes topic with the specified name from TopicHolder
         * @param topicName Name of the topic to remove
         */
        void removeTopic(const TopicName& topicName);

        /**
         * @brief Sets flag for auto removing of the topic with the specified name
         * @param topicName Name of the topic to set flag in it
         * @param flag Value for the flag to be set
         */
        void setTopicAutoRemoveFlag(const TopicName& topicName, bool flag);

        /**
         * @brief Sets the filter for the topic with the specified name
         * @param topicName Name of the needed topic
         * @param filter Filter to apply
         */
        void setTopicMessageFilter(const TopicName& topicName, AbstractMessageFilterPtr filter);

        /**
         * @brief Registers property listener for the dictionary with the specified name
         * @param dictionaryName Name of the dictionary for the listener
         * @param listener Pointer to listener taht needs to be registered
         */
        void addSettingsListener(const std::string& dictionaryName, AbstractPropertyListenerPtr listener);

        /**
         * @brief Unregisters property listener for the dictionary with the specified name
         * @param dictionaryName Name of the dictionary for the listener
         * @param listener Pointer to listener taht needs to be unregistered
         */
        void removeSettingsListener(const std::string& dictionaryName, AbstractPropertyListenerPtr listener);

    private:
        AbstractLauncher* mLauncher;
        const MetaTable* mMetaTable;
        SettingsHolder* mSettingsHolder;
        TopicHolder<TopicName> mTopicHolder;

        TaskQueue mNodesListPendingChanges;
        TaskQueue mListenersPendingListChanges;
        TaskQueue mSentMessages;
        TaskQueue mSettingsListenersPendingChanges;
    };

    typedef std::shared_ptr<RootNode> RootNodePtr;
}


