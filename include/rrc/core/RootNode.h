/**
 *  @autor arssivka
 *  @date 8/25/16
 */

#pragma once


#include <concurrentqueue.h>
#include "AbstractNode.h"
#include "Message.h"
#include "AbstractMessageListener.h"
#include "Billboard.h"
#include "TaskQueue.h"
#include "MetaTable.h"

namespace rrc {
    class Node;
    typedef std::shared_ptr<Node> NodePtr;
    class AbstractLauncher;
    /**
     * @brief The main node. It's responsible for syncronisation bentween nodes.
     */
    class RootNode : public AbstractNode {
    public:
        typedef std::string Key;

    public:

        /**
         * @brief Constructor of Root Node
         * @param launcher reference to Launcher Base instance
         * @param metaTable reference to Meta TAble instance
         */
        RootNode(AbstractLauncher& launcher, MetaTable& metaTable);

        /**
         * @brief Runs the synchronization algorhythm
         */
        virtual void entry() override;

        /**
         * @brief Send a message
         * @param topicName Name of the topic for the message
         * @param message Pointer to the message, that needs to be sent
         */
        void sendMessage(const Key& topicName, MessagePtr message);

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
        void addListener(const Key& topicName, AbstractMessageListenerPtr listener);

        /**
         * @bried Unregisters listener
         * @param topicName Name of the topic for the listener
         * @param listener Pointer to the listener that needs to be unregistered
         */
        void removeListener(const Key& topicName, AbstractMessageListenerPtr listener);

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
        std::vector<Key> getTopicNames() const {
            return mBillboard.getKeys();
        }

        void removeTopic(const Key& topicName);

        void setTopicAutoRemoveFlag(const Key& topicName, bool);

        void setTopicMessageFilter(const Key& topicName, AbstractMessageFilterPtr filter);

    private:
        AbstractLauncher* mLauncher;
        const MetaTable* mMetaTable;
        Billboard<Key> mBillboard;

        TaskQueue mNodesListPendingChanges;
        TaskQueue mListenersPendingListChanges;
        TaskQueue mSentMessages;
    };

    typedef std::shared_ptr<RootNode> RootNodePtr;
}


