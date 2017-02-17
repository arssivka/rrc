/**
 *  @autor arssivka
 *  @date 11/2/16
 */

#pragma once


#include <type_traits>
#include "AdvertisingMechanism.h"
#include "ServiceMechanism.h"
#include "SettingsMechanism.h"

namespace rrc {
    class MechanismsHolder {
    public:
        // TODO: Docs and tests
        MechanismsHolder(std::shared_ptr<AbstractTaskQueueAdapter> queue,
                         QueueAdapterFactory<Task> queueAdapterFactory);

        AdvertisingMechanism& getAdvertisingMechanism();

        ServiceMechanism& getServiceMechanism();

        SettingsMechanism& getSettingsMechanism();

        const AdvertisingMechanism& getAdvertisingMechanism() const;

        const ServiceMechanism& getServiceMechanism() const;

        const SettingsMechanism& getSettingsMechanism() const;

    private:
        AdvertisingMechanism mAdvertisingMechanism;
        ServiceMechanism mServiceMechanism;
        SettingsMechanism mSettingsMechanism;

    };
}