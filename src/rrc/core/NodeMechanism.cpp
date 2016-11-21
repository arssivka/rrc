/**
 *  @autor arssivka
 *  @date 11/5/16
 */

#include "rrc/core/NodeMechanism.h"


rrc::NodeMechanism::NodeMechanism(rrc::TaskQueueWrapper syncQueue, rrc::Pointer<rrc::AbstractLauncher>::Ptr launcher)
        : Mechanism("rrc.nodes", 0), mSyncQueue(std::move(syncQueue)), mLauncher(std::move(launcher)) { }


void rrc::NodeMechanism::addNode(rrc::Pointer<rrc::Node>::Ptr node) {
    // TODO: Move to enclosure
    auto launcher = mLauncher;
    mSyncQueue.enqueue([launcher, node]() {
        launcher->addNode(node);
    });
}


void rrc::NodeMechanism::removeNode(rrc::Pointer<rrc::Node>::Ptr node) {
    // TODO: Move to enclosure
    auto launcher = mLauncher;
    mSyncQueue.enqueue([launcher, node]() {
        launcher->removeNode(node);
    });
}


void rrc::NodeMechanism::stop() {
    mLauncher->stop();
}
