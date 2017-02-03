/**
 *  @autor arssivka
 *  @date 11/5/16
 */

#include "rrc/core/NodeMechanism.h"


rrc::NodeMechanism::NodeMechanism(rrc::TaskQueueWrapper syncQueue, rrc::AbstractLauncher& launcher)
        : mSyncQueue(std::move(syncQueue)), mLauncher(launcher) { }


void rrc::NodeMechanism::addNode(std::shared_ptr<rrc::AbstractNode> node) {
    // TODO: Move to enclosure
    auto& launcher = mLauncher;
    mSyncQueue.enqueue([&launcher, node]() {
        launcher.addNode(node);
    });
}


void rrc::NodeMechanism::removeNode(std::shared_ptr<rrc::AbstractNode> node) {
    // TODO: Move to enclosure
    auto& launcher = mLauncher;
    mSyncQueue.enqueue([&launcher, node]() {
        launcher.removeNode(node);
    });
}


void rrc::NodeMechanism::stop() {
    mLauncher.stop();
}
