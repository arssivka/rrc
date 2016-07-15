/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#include <algorithm>
#include "include/rrc/Node.h"

void rrc::Node::attachNode(Node::Ptr node) {
    mChildren.push_back(std::move(node));
    if (node)
        node->mParent = this;
}


Node::Ptr rrc::Node::detachNode(Node* node) {
    auto found = std::find(mChildren.begin(), mChildren.end(), node);
    if (found != nullptr) {
        Node::Ptr child = std::move(*found);
        mChildren.erase(found);
        return child;
    } else {
        return nullptr;
    }
}


Node* rrc::Node::findChild(const std::string& name) const {
    auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](const Node::Ptr& node) {
        return node->getID() == name;
    });
    return (found != mChildren.end())
           ? found->get()
           : nullptr;
}


Node* rrc::Node::findChild(const ID& id) const {
    auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](const Node::Ptr& node) {
        return node->getID() == id;
    });
    return (found != mChildren.end())
           ? found->get()
           : nullptr;
}


const ID& rrc::Node::getID() const {
    return mID;
}


Node* rrc::Node::getParent() const {
    return mParent;
}


const std::vector<Ptr>& rrc::Node::getChildren() const {
    return mChildren;
}


rrc::Node::Node(const std::string& name) : mID(name) {}