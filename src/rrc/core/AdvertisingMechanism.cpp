/**
 *  @autor arssivka
 *  @date 11/5/16
 */

#include <rrc/core/AdvertisingMechanism.h>


std::vector<std::string> rrc::AdvertisingMechanism::getTopicNames() const {
    return mTopicHolder.getTopicNames();
}


rrc::AdvertisingMechanism::AdvertisingMechanism(TaskQueueWrapper syncQueue)
        : mSyncQueue(syncQueue) {}


void rrc::AdvertisingMechanism::sendMessage(const std::string& topicName, std::shared_ptr<rrc::Message> message) {
    auto& topicHolder = mTopicHolder;
    mSyncQueue.enqueue([&topicHolder, topicName, message]() {
        std::shared_ptr<Topic> topic = topicHolder.getTopic(topicName);
        if (topic != nullptr) {
            topic->sendMessage(message);
        }
    });
}


void rrc::AdvertisingMechanism::addListener(const std::string& topicName,
                                            std::shared_ptr<rrc::MessageListener> listener) {
    auto& topicHolder = mTopicHolder;
    mSyncQueue.enqueue([&topicHolder, topicName, listener]() {
        std::shared_ptr<Topic> topic = topicHolder.getTopic(topicName);
        if (topic == nullptr) {
            topicHolder.createTopic(topicName);
            topic = topicHolder.getTopic(topicName);
        }
        topic->addListener(listener);

    });
}


void rrc::AdvertisingMechanism::removeTopic(const std::string& topicName) {
    auto& topicHolder = mTopicHolder;
    mSyncQueue.enqueue([&topicHolder, topicName]() {
        topicHolder.removeTopic(topicName);
    });
}


