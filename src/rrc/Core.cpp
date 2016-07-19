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


bool rrc::Core::addTopicListener(const ID& id, const Key& topic, MessageListener* listener, bool directCallEnabled) {
    auto connector = TopicConnector(listener->getDescriptor());
    TopicsContainer::SPtr tptr = mTopics.get(topic, std::move(connector));
    return tptr->addListener(id, listener, directCallEnabled);
}


bool rrc::Core::detachTopicListener(const Key& topic, const MessageListener* listener) {
    TopicsContainer::SPtr tptr = mTopics.get(topic);
    if (tptr != nullptr) {
        return tptr->detachListener(listener);
    }
    return false;
}


bool rrc::Core::addTopicSender(const Key& topic, MessageSender* sender) {
    auto connector = TopicConnector(sender->getDescriptor());
    TopicsContainer::SPtr tptr = mTopics.get(topic, std::move(connector));
    return tptr->addSender(sender);
}


bool rrc::Core::detachTopicSender(const Key& topic, const MessageSender* sender) {
    TopicsContainer::SPtr tptr = mTopics.get(topic);
    return tptr->detachSender(sender);
}


bool rrc::Core::setServiceStuff(const ID& id, const Key& service, MessageStuff* stuff, bool directCallEnabled) {
    auto connector = ServiceConnector(stuff->getListenerDescriptor(),
                                      stuff->getListenerDescriptor());
    ServicesContainer::SPtr sptr = mServices.get(service, std::move(connector));
    return sptr->setServiceStuff(id, stuff, directCallEnabled);
}


bool rrc::Core::detachServiceStuff(const Key& service, const MessageStuff* stuff) {
    ServicesContainer::SPtr sptr = mServices.get(service);
    if (sptr != nullptr) {
        return sptr->detachServiceStuff(stuff);
    }
    return false;
}


bool rrc::Core::addClientStuff(const ID& id, const Key& service, MessageStuff* stuff) {
    auto connector = ServiceConnector(stuff->getListenerDescriptor(),
                                      stuff->getListenerDescriptor());
    ServicesContainer::SPtr sptr = mServices.get(service, std::move(connector));
    return sptr->addClientStuff(id, stuff);
}


bool rrc::Core::detachClientStuff(const Key& service, const MessageStuff* stuff) {
    ServicesContainer::SPtr sptr = mServices.get(service);
    if (sptr != nullptr) {
        return sptr->detachClientStuff(stuff);
    }
    return false;
}


void rrc::Core::setDirectCallEnabled(bool state) {
    mDirectCallEnabled = state;
}


bool rrc::Core::isDirectCallEnabled() const {
    return  mDirectCallEnabled;
}