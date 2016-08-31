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
#include "LauncherBase.h"

namespace rrc {
    class RootNode : public NodeBase {
    public:
        typedef std::shared_ptr<RootNode> Ptr;
        typedef std::string Key;

    public:
        RootNode(LauncherBase* launcher, const MetaTable* metaTable);

        virtual void entry() override;

        void sendMessage(const Key& topicName, Message::Ptr message);

        void addNode(Node::Ptr node);

        void removeNode(Node::Ptr node);

        void addListener(const Key& topic, MessageListener::Ptr listener);

        void removeListener(const Key& topicName, MessageListener::Ptr listener);

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
}


