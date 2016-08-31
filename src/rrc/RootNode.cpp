/**
 *  @autor arssivka
 *  @date 8/25/16
 */

#include <rrc/LauncherBase.h>
#include <rrc/RootNode.h>


rrc::RootNode::RootNode(rrc::LauncherBase* launcher, const rrc::MetaTable* metaTable)
        : mLauncher(launcher), mMetaTable(metaTable) { }


void rrc::RootNode::entry() {
    mNodesListPendingChanges.execAll();
    mListenersPendingListChanges.execAll();
    mSentMessages.execAll();
}


void rrc::RootNode::sendMessage(const rrc::RootNode::Key& topicName, rrc::MessagePtr message) {
    mSentMessages.enqueue([this, topicName, message]() {
        TopicPtr t = mBillboard.getTopic(topicName);
        if (t != nullptr) {
            t->sendMessage(message);
        }
    });
}


void rrc::RootNode::addNode(rrc::NodePtr node) {
    mNodesListPendingChanges.enqueue([this, node]() {
        mLauncher->addNode(node);
    });
}


void rrc::RootNode::removeNode(rrc::NodePtr node) {
    mNodesListPendingChanges.enqueue([this, node]() {
        mLauncher->removeNode(node);
    });
}


void rrc::RootNode::addListener(const rrc::RootNode::Key& topic, rrc::MessageListenerPtr listener) {
    mListenersPendingListChanges.enqueue([this, topic, listener]() {
        TopicPtr t = mBillboard.getTopic(topic);
        if (t == nullptr) {
            mBillboard.createTopic(topic, listener->getTypeId());
            t = mBillboard.getTopic(topic);
        }
        t->addListener(listener);
    });
}


void rrc::RootNode::removeListener(const rrc::RootNode::Key& topicName, rrc::MessageListenerPtr listener) {
    TopicPtr t = mBillboard.getTopic(topicName);
    if (t != nullptr) {
        t->removeListener(listener);
        if (t->empty()) {
            mBillboard.removeTopic(topicName);
        }
    }
}


void rrc::RootNode::stop() {
    mLauncher->stop();
}
