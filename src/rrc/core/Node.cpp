/**
 *  @autor arssivka
 *  @date 11/21/16
 */

#include <rrc/core/Node.h>

rrc::Node::~Node() { }


rrc::Node::Node(std::shared_ptr<AbstracrTaskQueueAdapter> taskQueue, rrc::MechanismsHolder& mechanismsHolder)
        : mTaskQueue(std::move(taskQueue)), mMechanismsHolder(mechanismsHolder) {}


void rrc::Node::sendMessage(const std::string& topic, std::shared_ptr<rrc::Buffer> message) {
    auto& mechanism = mMechanismsHolder.getAdvertisingMechanism();
    mechanism.sendMessage(topic, message);
}


const std::weak_ptr<rrc::MessageListener> rrc::Node::subscribe(const std::string& topicName,
                                                               MessageListener::Callback&& callback) {
    auto& mechanism = mMechanismsHolder.getAdvertisingMechanism();
    auto listener = std::make_shared<MessageListener>(mTaskQueue, std::move(callback));
    mechanism.addListener(topicName, listener);
    return listener;
}


void rrc::Node::entry() {
    mTaskQueue->execAll();
}


void rrc::Node::unsubscribe(const std::string& topicName, const std::weak_ptr<rrc::MessageListener> listener) {
    auto& mechanism = mMechanismsHolder.getAdvertisingMechanism();
    mechanism.removeListener(topicName, listener);
}
