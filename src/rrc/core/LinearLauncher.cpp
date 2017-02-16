/**
 *  @autor arssivka
 *  @date 8/26/16
 */

#include <rrc/core/LinearLauncher.h>
#include <stdlib.h>


rrc::LinearLauncher::LinearLauncher()
        : mFinished(false) { }


rrc::LinearLauncher::~LinearLauncher() { }


int rrc::LinearLauncher::run() {
    // TODO: Optimize memory model
    mFinished = false;
    while (this->step());
    return EXIT_SUCCESS;
}


void rrc::LinearLauncher::stop() {
    // TODO: Optimize memory model
    mFinished = true;
}


void rrc::LinearLauncher::addNode(std::shared_ptr<rrc::Node> node) {
    mNodesList.emplace_front(std::move(node));
}


void rrc::LinearLauncher::removeNode(std::shared_ptr<rrc::Node> node) {
    mNodesList.remove(node);
}


bool rrc::LinearLauncher::step() {
    // TODO: Optimize memory model
    if (mFinished) return false;
    for (auto&& queue : mQueuesList) queue->execAll();
    for (auto&& node : mNodesList) node->entry();
    return true;
}


void rrc::LinearLauncher::addSyncQueue(std::shared_ptr<AbstractTaskQueueAdapter> queue) {
    mQueuesList.emplace_front(std::move(queue));
}


void rrc::LinearLauncher::removeSyncQueue(std::shared_ptr<AbstractTaskQueueAdapter> queue) {
    mQueuesList.remove(std::move(queue));
}
