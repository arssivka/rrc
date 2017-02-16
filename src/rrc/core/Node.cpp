/**
 *  @autor arssivka
 *  @date 11/21/16
 */

#include <rrc/core/Node.h>

rrc::Node::~Node() { }


rrc::Node::Node(std::shared_ptr<AbstractTaskQueueAdapter> taskQueue, rrc::MechanismsHolder& mechanismsHolder)
        : mTaskQueue(std::move(taskQueue)), mMechanismsHolder(mechanismsHolder) {}


void rrc::Node::sendMessage(const std::string& topic, std::shared_ptr<rrc::Buffer> message) {
    auto& mechanism = mMechanismsHolder.getAdvertisingMechanism();
    mechanism.sendMessage(topic, message);
}


const std::weak_ptr<rrc::TaskHub<rrc::Buffer>> rrc::Node::subscribe(const std::string& topicName,
                                                               TaskHub<Buffer>::Callback&& callback) {
    auto& mechanism = mMechanismsHolder.getAdvertisingMechanism();
    auto listener = std::make_shared<TaskHub<Buffer>>(mTaskQueue, std::move(callback));
    mechanism.addListener(topicName, listener);
    return listener;
}


void rrc::Node::entry() {
    mTaskQueue->execAll();
}


void rrc::Node::unsubscribe(const std::string& topicName, const std::weak_ptr<rrc::TaskHub<Buffer>> listener) {
    auto& mechanism = mMechanismsHolder.getAdvertisingMechanism();
    mechanism.removeListener(topicName, listener);
}
