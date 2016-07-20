/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#include "include/rrc/Core.h"
#include "VersionDefines.h"


std::string static constexpr rrc::Core::getVersion() {
    return std::string(RRC_VERSION);
}


std::vector<std::string>& rrc::Core::getArs() const {
    return mArgs;
}


Settings* rrc::Core::getSettings() {
    return &mSettings;
}

Core* rrc::Core::instance() {
    return sInstance;
}


bool rrc::Core::addTopicListener(const ID& id, const Key& topic, MessageListener::SPtr listener) {
    auto connector = TopicConnector(listener->getDescriptor());
    TopicsContainer::SPtr tptr = mTopics.get(topic);
    return tptr->addListener(id, listener);
}


bool rrc::Core::detachTopicListener(const Key& topic, const MessageListener::SPtr listener) {
    TopicsContainer::SPtr tptr = mTopics.get(topic);
    if (tptr != nullptr) {
        return tptr->detachListener(listener);
    }
    return false;
}


bool rrc::Core::addTopicSender(const ID& id, const Key& topic, MessageSender::SPtr sender) {
    auto connector = TopicConnector(sender->getDescriptor());
    TopicsContainer::SPtr tptr = mTopics.get(topic);
    return tptr->addSender(id, sender);
}


bool rrc::Core::detachTopicSender(const Key& topic, const MessageSender::SPtr sender) {
    TopicsContainer::SPtr tptr = mTopics.get(topic);
    return tptr->detachSender(sender);
}


bool rrc::Core::setServiceStuff(const ID& id, const Key& service, MessageStuff::SPtr stuff) {
    ServicesContainer::SPtr sptr = mServices.get(service);
    return sptr->setServiceStuff(id, stuff);
}


bool rrc::Core::detachServiceStuff(const Key& service, const MessageStuff::SPtr stuff) {
    ServicesContainer::SPtr sptr = mServices.get(service);
    if (sptr != nullptr) {
        return sptr->detachServiceStuff(stuff);
    }
    return false;
}


bool rrc::Core::addClientStuff(const ID& id, const Key& service, MessageStuff::SPtr stuff) {
    auto connector = ServiceConnector(stuff->getListenerDescriptor(),
                                      stuff->getListenerDescriptor());
    ServicesContainer::SPtr sptr = mServices.get(service);
    return sptr->addClientStuff(id, stuff);
}


bool rrc::Core::detachClientStuff(const Key& service, const MessageStuff::SPtr stuff) {
    ServicesContainer::SPtr sptr = mServices.get(service);
    if (sptr != nullptr) {
        return sptr->detachClientStuff(stuff);
    }
    return false;
}


TaskQueue::SPtr rrc::Core::getTaskQueue(const ID& id) const {
    return TaskQueueContainer.get(id);
}


bool rrc::Core::deleteTaskQueue(const ID& id) {
    auto queue = this->getTaskQueue(id);
    queue->disable();
    mTasks.remove(id);
}