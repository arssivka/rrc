/**
 *  @autor arssivka
 *  @date 11/5/16
 */

#include <rrc/core/AdvertisingMechanism.h>


auto rrc::AdvertisingMechanism::getTopicNames() const {
    return mTopicHolder->getTopicNames();
}


rrc::AdvertisingMechanism::AdvertisingMechanism(rrc::TaskQueueWrapper syncQueue,
                                                rrc::TopicHolder<std::string>::Ptr topicHolder)
        : Mechanism("rrc.advertising", 0), mTopicHolder(std::move(topicHolder)), mSyncQueue(syncQueue) {}


void rrc::AdvertisingMechanism::sendMessage(const std::string& topicName, rrc::Pointer<rrc::Message>::Ptr message) {
    auto topicHolder = mTopicHolder;
    mSyncQueue.enqueue([topicHolder, topicName, message]() {
        Topic::Ptr topic = topicHolder->getTopic(topicName);
        if (topic != nullptr) {
            topic->sendMessage(message);
        }
    });
}


void rrc::AdvertisingMechanism::addListener(const std::string& topicName,
                                            rrc::Pointer<rrc::AbstractMessageListener>::Ptr listener) {
    auto topicHolder = mTopicHolder;
    mSyncQueue.enqueue([topicHolder, topicName, listener]() {
        Topic::Ptr topic = topicHolder->getTopic(topicName);
        if (topic != nullptr) {
            topic->removeListener(listener);
            if (topic->isAutoRemoveEnabled() && !topic->hasListeners()) {
                topicHolder->removeTopic(topicName);
            }
        }
    });
}


void rrc::AdvertisingMechanism::removeListener(const std::string& topicName,
                                               rrc::Pointer<rrc::AbstractMessageListener>::Ptr listener) {
    auto topicHolder = mTopicHolder;
    mSyncQueue.enqueue([topicHolder, topicName, listener]() {
        Topic::Ptr topic = topicHolder->getTopic(topicName);
        if (topic != nullptr) {
            topic->removeListener(listener);
            if (!topic->hasListeners()) {
                topicHolder->removeTopic(topicName);
            }
        }
    });
}


void rrc::AdvertisingMechanism::removeTopic(const std::string& topicName) {
    auto topicHolder = mTopicHolder;
    mSyncQueue.enqueue([topicHolder, topicName]() {
        Topic::Ptr topic = topicHolder->getTopic(topicName);
        if (topic != nullptr) {
            topicHolder->removeTopic(topicName);
        }
    });
}


void rrc::AdvertisingMechanism::setTopicAutoRemoveFlag(const std::string& topicName, bool flag) {
    auto topicHolder = mTopicHolder;
    mSyncQueue.enqueue([topicHolder, topicName, flag]() {
        Topic::Ptr topic = topicHolder->getTopic(topicName);
        if (topic == nullptr) {
            if (flag) {
                topicHolder->createTopic(topicName);
                topic = topicHolder->getTopic(topicName);
                topic->setAutoRemoveEnabled(true);
            }
        } else {
            if (!flag && !topic->hasListeners() ) {
                topicHolder->removeTopic(topicName);
            } else {
                topic->setAutoRemoveEnabled(false);
            }
        }
    });
}


void rrc::AdvertisingMechanism::setTopicMessageFilter(const std::string& topicName,
                                                      rrc::Pointer<rrc::AbstractMessageFilter>::Ptr filter) {
    auto topicHolder = mTopicHolder;
    mSyncQueue.enqueue([this, topicName, filter{std::move(filter)}]() {
        Topic::Ptr topic = mTopicHolder->getTopic(topicName);
        if (topic == nullptr) {
            mTopicHolder->createTopic(topicName);
            topic = mTopicHolder->getTopic(topicName);
            topic->setAutoRemoveEnabled(false);
            topic->setMessageFilter(filter);
        } else {
            topic->setMessageFilter(filter);
        }
    });
}

