/**
 *  @autor arssivka
 *  @date 2/7/17
 */

#include "include/rrc/core/ServiceMechanism.h"


rrc::ServiceMechanism::ServiceMechanism(std::shared_ptr<rrc::AbstracrTaskQueueAdapter> syncQueue)
        : mSyncQueue(std::move(syncQueue)) {}


void rrc::ServiceMechanism::addService(const rrc::ServiceMechanism::Name& name, std::shared_ptr<rrc::Service> service) {
    auto& serviceHolderRef = mServiceHolder;
    mSyncQueue->enqueue(
            [&serviceHolderRef, name, serviceCap = std::move(service)]() mutable {
                serviceHolderRef.removeService(name, std::move(serviceCap));
            });
}


void
rrc::ServiceMechanism::removeService(const rrc::ServiceMechanism::Name& name, const std::weak_ptr<rrc::Service> service) {
    auto& serviceHolderRef = mServiceHolder;
    mSyncQueue->enqueue(
            [&serviceHolderRef, name, service]() mutable {
                serviceHolderRef.removeService(name, service);
            });
}


void rrc::ServiceMechanism::call(const rrc::ServiceMechanism::Name& name, std::shared_ptr<rrc::TaskHub> resultHub,
                                 std::shared_ptr<rrc::Buffer> input) {
    auto& serviceHolderRef = mServiceHolder;
    mSyncQueue->enqueue(
            [&serviceHolderRef, name, resultHubCap = std::move(resultHub),
                    inputCap = std::move(input)]() mutable {
                serviceHolderRef.call(name, std::move(resultHubCap), std::move(inputCap));
            });
}


std::vector<rrc::ServiceMechanism::Name> rrc::ServiceMechanism::getNames() const {
    return mServiceHolder.getNames();
}
