/**
 *  @autor arssivka
 *  @date 2/7/17
 */

#pragma once


#include "Service.h"
#include "ServiceHolder.h"

namespace rrc {
    class ServiceMechanism {
    public:
        typedef std::string Name;

        ServiceMechanism(std::shared_ptr<AbstractTaskQueueAdapter> syncQueue);

        void addService(const Name& name, std::shared_ptr<Service> service);

        void removeService(const Name& name, const std::weak_ptr<Service> service);

        void call(const Name& name, std::shared_ptr<TaskHub<Buffer>> resultHub, std::shared_ptr<Buffer> input);

        std::vector<Name> getNames() const;

    private:
        std::shared_ptr<AbstractTaskQueueAdapter> mSyncQueue;
        ServiceHolder<Name> mServiceHolder;
    };
}


