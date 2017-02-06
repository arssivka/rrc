/**
 *  @autor arssivka
 *  @date 11/2/16
 */

#pragma once


#include <type_traits>
#include "include/rrc/meta.h"
#include "AdvertisingMechanism.h"

namespace rrc {
    class MechanismsHolder {
    public:
        // TODO: Docs and tests
        MechanismsHolder(TaskQueueWrapper queue);

        AdvertisingMechanism& getAdvertisingMechanism();

        const AdvertisingMechanism& getAdvertisingMechanism() const;


    private:
        AdvertisingMechanism mAdvertisingMechanism;

    };
}