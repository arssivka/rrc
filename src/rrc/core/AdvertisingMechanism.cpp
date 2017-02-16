/**
 *  @autor arssivka
 *  @date 11/5/16
 */

#include <rrc/core/AdvertisingMechanism.h>
#include <rrc/core/TaskCapture.h>


std::vector<std::string> rrc::AdvertisingMechanism::getNames() const {
    return mTopicHolder.getNames();
}


rrc::AdvertisingMechanism::AdvertisingMechanism(std::shared_ptr<AbstractTaskQueueAdapter> syncQueue)
        : mSyncQueue(std::move(syncQueue)) {}


void rrc::AdvertisingMechanism::sendMessage(const AdvertisingMechanism::Name& topicName,
                                            std::shared_ptr<rrc::Buffer> message) {
    auto& topicHolderRef = mTopicHolder;
    mSyncQueue->enqueue([&topicHolderRef, topicName, messageCap = std::move(message)]() mutable {
        topicHolderRef.sendMessage(topicName, std::move(messageCap));
    });
}


void rrc::AdvertisingMechanism::addListener(const AdvertisingMechanism::Name& topicName,
                                            std::shared_ptr<rrc::TaskHub<Buffer>> listener) {
    auto& topicHolderRef = mTopicHolder;
    mSyncQueue->enqueue([&topicHolderRef, topicName, listenerCap = std::move(listener)]() mutable {
        topicHolderRef.addListener(topicName, std::move(listenerCap));
    });
}


void
rrc::AdvertisingMechanism::removeListener(const AdvertisingMechanism::Name& topicName,
                                          const std::weak_ptr<TaskHub<Buffer>> listener) {
    auto& topicHolderRef = mTopicHolder;
    mSyncQueue->enqueue([&topicHolderRef, topicName, listenerCap = std::move(listener)]() mutable {
        topicHolderRef.removeListener(topicName, std::move(listenerCap));
    });
}


