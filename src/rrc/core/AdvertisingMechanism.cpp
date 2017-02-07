/**
 *  @autor arssivka
 *  @date 11/5/16
 */

#include <rrc/core/AdvertisingMechanism.h>
#include <include/rrc/core/TaskCapture.h>


std::vector<std::string> rrc::AdvertisingMechanism::getTopicNames() const {
    return mTopicHolder.getTopicNames();
}


rrc::AdvertisingMechanism::AdvertisingMechanism(std::shared_ptr<TaskQueueAdapter> syncQueue)
        : mSyncQueue(std::move(syncQueue)) {}


void rrc::AdvertisingMechanism::sendMessage(const std::string& topicName, std::shared_ptr<rrc::Buffer> message) {
    auto& topicHolder = mTopicHolder;
    mSyncQueue->enqueue([&topicHolder, topicName, capturedMessage = std::move(message)]() mutable {
        topicHolder.sendMessage(topicName, std::move(capturedMessage));
    });
}


void rrc::AdvertisingMechanism::addListener(const std::string& topicName,
                                            std::shared_ptr<rrc::MessageListener> listener) {
    auto& topicHolder = mTopicHolder;
    mSyncQueue->enqueue([&topicHolder, topicName, capturedListener = std::move(listener)]() mutable {
        topicHolder.addListener(topicName, std::move(capturedListener));
    });
}


void
rrc::AdvertisingMechanism::removeListener(const std::string& topicName, const std::weak_ptr<MessageListener> listener) {
    auto& topicHolder = mTopicHolder;
    mSyncQueue->enqueue([&topicHolder, topicName, capturedListener = std::move(listener)]() mutable {
        topicHolder.removeListener(topicName, std::move(capturedListener));
    });
}


