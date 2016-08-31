/**
 *  @autor arssivka
 *  @date 8/25/16
 */

#include "include/rrc/Node.h"


std::chrono::steady_clock::duration rrc::Node::getMinDuration() const {
    return mMinDuration;
}


void rrc::Node::setMinDuration(const std::chrono::steady_clock::duration& minDuration) {
    mMinDuration = minDuration;
}


rrc::Node::Node(rrc::RootNode::Ptr rootNode) : mRootNode(rootNode) { }


rrc::RootNode::Ptr rrc::Node::getRootNode() const {
    return mRootNode;
}
