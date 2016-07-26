/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#include <algorithm>
#include <rrc/Node.h>

void rrc::Node::attachNode(Node::UPtr node) {
    mChildren.push_back(std::move(node));
    if (node)
        node->mParent = this;
}


rrc::Node::UPtr rrc::Node::detachNode(Node* node) {
    auto found = std::find_if(mChildren.begin(), mChildren.end(), [=](UPtr& ptr) -> bool {
        return ptr.get() == node;
    });
    if (found != mChildren.end()) {
        Node::UPtr child = std::move(*found);
        mChildren.erase(found);
        return child;
    } else {
        return nullptr;
    }
}


rrc::Node* rrc::Node::findChild(const std::string& name) const {
    auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](const Node::UPtr& node) {
        return node->getID() == name;
    });
    return (found != mChildren.end())
           ? found->get()
           : nullptr;
}


rrc::Node* rrc::Node::findChild(const ID& id) const {
    auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](const Node::UPtr& node) {
        return node->getID() == id;
    });
    return (found != mChildren.end())
           ? found->get()
           : nullptr;
}


const rrc::ID& rrc::Node::getID() const {
    return mID;
}


rrc::Node* rrc::Node::getParent() const {
    return mParent;
}


const std::vector<rrc::Node::UPtr>& rrc::Node::getChildren() const {
    return mChildren;
}


rrc::Node::Node(const std::string& name)
        : mID(name) {
    auto core = Core::instance();
    core->setEntryForID(mID,[this]() {
        this->entry();
    });
}

void rrc::Node::entry() {
    this->pollEvents();
}

void rrc::Node::pollEvent() {
    mTaskQueue->execOnce();
}

void rrc::Node::pollEvents() {
    mTaskQueue->execAll();
}
