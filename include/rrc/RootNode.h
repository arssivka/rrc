/**
 *  @autor arssivka
 *  @date 8/25/16
 */

#pragma once


#include <concurrentqueue.h>
#include "NodeBase.h"
#include "Message.h"
#include "MessageListener.h"
#include "Billboard.h"
#include "TaskQueue.h"
#include "MetaTable.h"

namespace rrc {
    class Node;
    typedef std::shared_ptr<Node> NodePtr;
    class LauncherBase;

    class RootNode : public NodeBase {
    public:
        typedef std::string Key;

    public:
        RootNode(LauncherBase* launcher, const MetaTable* metaTable);

        virtual void entry() override;

        void sendMessage(const Key& topicName, MessagePtr message);

        void addNode(NodePtr node);

        void removeNode(NodePtr node);

        void addListener(const Key& topic, MessageListenerPtr listener);

        void removeListener(const Key& topicName, MessageListenerPtr listener);

        void stop();

        template <class T>
        TypeId getTypeId() {
            return mMetaTable->getTypeId<T>();
        }

    private:
        LauncherBase* mLauncher;
        const MetaTable* mMetaTable;
        Billboard<Key> mBillboard;

        TaskQueue mNodesListPendingChanges;
        TaskQueue mListenersPendingListChanges;
        TaskQueue mSentMessages;
    };

    typedef std::shared_ptr<RootNode> RootNodePtr;
}


