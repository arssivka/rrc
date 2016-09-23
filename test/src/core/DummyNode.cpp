/**
 *  @autor arssivka
 *  @date 9/2/16
 */

#include <Message.pb.h>
#include "include/DummyNode.h"


DummyNode::DummyNode(rrc::RootNodePtr rootNode, const std::string& topicName)
        : Node(rootNode), mRootNode(rootNode), mTopicName(topicName) {
    this->resetCounter();
    rrc::TypeId typeId = rootNode->getTypeId<testmessages::TestMessage>();
    mListener = std::make_shared<rrc::QueueMessageListener>(typeId);
    mRootNode->addListener(mTopicName, mListener);
}


void DummyNode::incrementCounter() {
    ++mCounter;
    if (mCounter == 5) {
        mRootNode->stop();
    }
}


void DummyNode::resetCounter() {
    mCounter = 0;
}


rrc::MessagePtr DummyNode::tryGetMessage() {
    return mListener->tryDequeueMessage();
}


DummyNode::~DummyNode() {
    mRootNode->removeListener(mTopicName, mListener);
}
