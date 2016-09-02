/**
 *  @autor arssivka
 *  @date 8/25/16
 */

#include <include/rrc/core/Node.h>


std::chrono::steady_clock::duration rrc::Node::getMinDuration() const {
    return mMinDuration;
}


void rrc::Node::setMinDuration(const std::chrono::steady_clock::duration& minDuration) {
    mMinDuration = minDuration;
}


rrc::Node::Node(rrc::RootNodePtr rootNode) : mRootNode(rootNode) { }


rrc::RootNodePtr rrc::Node::getRootNode() const {
    return mRootNode;
}
