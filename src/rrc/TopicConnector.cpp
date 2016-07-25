/**
 *  @autor arssivka
 *  @date 7/20/16
 */


#include <rrc/TopicConnector.h>


rrc::TopicConnector::TopicConnector(const pb::Descriptor& descriptor)
        : mDescriptor(&descriptor) { }


const pb::Descriptor& rrc::TopicConnector::getDescriptor() const {
    return *mDescriptor;
}


void rrc::TopicConnector::setDescriptor(const pb::Descriptor& descriptor) {
    mDescriptor = &descriptor;
}


bool rrc::TopicConnector::checkDescriptor(const pb::Descriptor& descriptor) {
    // TODO type checking is probably good idea
    return true;
}


bool rrc::TopicConnector::addListener(MessageListener::SPtr listener) {
    mListenersList.pushFront(std::move(listener));
    return true;
}


bool rrc::TopicConnector::detachListener(const MessageListener::SPtr listener) {
    bool deleted = false;
    mListenersList.removeIf([&](MessageListener::SPtr other) -> bool {
        bool toDelete = (other == listener);
        deleted |= toDelete;
        return toDelete;
    });
    return deleted;
}


bool rrc::TopicConnector::addSender(MessageSender::SPtr sender) {
    using namespace std::placeholders;
    sender->setCallback(std::bind(&TopicConnector::sendMessage, this, _1, _2, _3));
    mSendersList.pushFront(sender);
    return true;
}


bool rrc::TopicConnector::detachSender(MessageSender::SPtr sender) {
    bool deleted = false;
    mSendersList.removeIf([&](MessageSender::SPtr other) -> bool {
        bool toDelete = other == sender;
        deleted |= toDelete;
        return toDelete;
    });
    if (deleted) sender->disconnect();
    return deleted;
}


bool rrc::TopicConnector::sendMessage(const ID& id, Message<pb::Message> message, bool directCall) {
    mListenersList.applyWhile([&](MessageListener::SPtr listener) -> bool {
        listener->onMessage(id, message, directCall);
        return false;
    });
    return true;
}