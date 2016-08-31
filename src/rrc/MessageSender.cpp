/**
 *  @autor arssivka
 *  @date 7/18/16
 */

#include "include/rrc/MessageSender.h"


rrc::MessageSender::MessageSender(rrc::RootNode::Ptr rootNode, const std::string& topicName)
        : mRootNode(std::move(rootNode)), mTopicName(topicName) { }


void rrc::MessageSender::sendMessage(rrc::Message::Ptr message) {
    mRootNode->sendMessage(mTopicName, std::move(message));
}


const std::string& rrc::MessageSender::getTopicName() const {
    return mTopicName;
}


void rrc::MessageSender::setTopicName(const std::string& topicName) {
    mTopicName = topicName;
}


rrc::RootNode::Ptr rrc::MessageSender::getRootNode() const {
    return mRootNode;
}


void rrc::MessageSender::setRootNode(rrc::RootNode::Ptr rootNode) {
    mRootNode = std::move(rootNode);
}
