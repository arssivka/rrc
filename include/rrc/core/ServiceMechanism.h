/**
 *  @autor arssivka
 *  @date 2/7/17
 */

#pragma once


#include "Service.h"
#include "ServiceHolder.h"
#include "QueueAdapterFactory.h"

namespace rrc {
    class ServiceMechanism {
    public:
        typedef std::string Name;

        ServiceMechanism(std::shared_ptr<AbstractTaskQueueAdapter> syncQueue,
                         QueueAdapterFactory <Task> taskQueueFactory);

        template <class K>
        void addService(K&& name, std::shared_ptr<Service> service) {
            auto& serviceHolderRef = mServiceHolder;
            mServicesQueue->enqueue(
                    [&serviceHolderRef, nameCap = std::forward<K>(name),
                            serviceCap = std::move(service)]() mutable {
                        serviceHolderRef.removeService(nameCap, std::move(serviceCap));
                    });
            this->enqueueUpdate();
        }

        template <class K>
        void removeService(K&& name, const std::weak_ptr<Service> service) {
            auto& serviceHolderRef = mServiceHolder;
            mServicesQueue->enqueue(
                    [&serviceHolderRef, nameCap = std::forward<K>(name), service]() mutable {
                        serviceHolderRef.removeService(nameCap, service);
                    });
            this->enqueueUpdate();
        }

        template <class K>
        void call(K&& name, std::shared_ptr<TaskHub<Buffer>> resultHub,
                  std::shared_ptr<Buffer> input) {
            auto& serviceHolderRef = mServiceHolder;
            mCallsQueue->enqueue(
                    [&serviceHolderRef, nameCap = std::forward<K>(name),
                            resultHubCap = std::move(resultHub),
                            inputCap = std::move(input)]() mutable {
                        serviceHolderRef.call(nameCap, std::move(resultHubCap), std::move(inputCap));
                    });
            this->enqueueUpdate();
        }

        std::vector<Name> getNames() const;

    private:
        void enqueueUpdate();

        void applyQueues();

    private:
        ServiceHolder<Name> mServiceHolder;
        std::shared_ptr<AbstractTaskQueueAdapter> mSyncQueue;
        std::unique_ptr<AbstractTaskQueueAdapter> mServicesQueue;
        std::unique_ptr<AbstractTaskQueueAdapter> mCallsQueue;
        std::atomic_flag mChangesEnqueuedFlag;
    };
}


