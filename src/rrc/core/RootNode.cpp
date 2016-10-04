/**
 *  @autor arssivka
 *  @date 8/25/16
 */

#include <rrc/core/AbstractLauncher.h>
#include <rrc/core/RootNode.h>
#include "AbstractMessageListener.cpp"


rrc::RootNode::RootNode(AbstractLauncher &launcher, MetaTable &metaTable)
        : mLauncher(&launcher), mMetaTable(&metaTable) { }


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


void rrc::RootNode::addListener(const rrc::RootNode::Key& topicName, AbstractMessageListenerPtr listener) {
    mListenersPendingListChanges.enqueue([this, topicName, listener]() {
        TopicPtr t = mBillboard.getTopic(topicName);
        if (t == nullptr) {
            mBillboard.createTopic(topicName);
            t = mBillboard.getTopic(topicName);
        }
        t->addListener(listener);
    });
}


void rrc::RootNode::removeListener(const rrc::RootNode::Key& topicName, AbstractMessageListenerPtr listener) {
    mListenersPendingListChanges.enqueue([this, topicName, listener]() {
        TopicPtr t = mBillboard.getTopic(topicName);
        if (t != nullptr) {
            t->removeListener(listener);
            if (t->isAutoRemoveEnabled() && !t->hasListeners()) {
                mBillboard.removeTopic(topicName);
            }
        }
    });
}

void rrc::RootNode::removeTopic(const rrc::RootNode::Key& topicName) {
    mListenersPendingListChanges.enqueue([this, topicName]() {
        TopicPtr t = mBillboard.getTopic(topicName);
        if (t != nullptr) {
            mBillboard.removeTopic(topicName);
        }
    });
}

void rrc::RootNode::setTopicAutoRemoveFlag(const rrc::RootNode::Key& topicName, bool flag) {
    mListenersPendingListChanges.enqueue([this, topicName, flag]() {
        TopicPtr t = mBillboard.getTopic(topicName);
        if (t == nullptr) {
            if (flag) {
                mBillboard.createTopic(topicName);
                t = mBillboard.getTopic(topicName);
                t->setAutoRemoveEnabled(true);
            }
        } else {
            if (!flag && !t->hasListeners() ) {
                mBillboard.removeTopic(topicName);
            } else {
                t->setAutoRemoveEnabled(false);
            }
        }
    });
}

void rrc::RootNode::setTopicMessageFilter(const rrc::RootNode::Key& topicName, rrc::AbstractMessageFilterPtr filter) {
    mListenersPendingListChanges.enqueue([this, topicName, filter{std::move(filter)}]() {
        TopicPtr t = mBillboard.getTopic(topicName);
        if (t == nullptr) {
            mBillboard.createTopic(topicName);
            t = mBillboard.getTopic(topicName);
            t->setAutoRemoveEnabled(false);
            t->setMessageFilter(filter);
        } else {
            t->setMessageFilter(filter);
        }
    });
}


void rrc::RootNode::stop() {
    mLauncher->stop();
}
