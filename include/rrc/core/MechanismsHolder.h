/**
 *  @autor arssivka
 *  @date 11/2/16
 */

#pragma once


#include <type_traits>
#include "AdvertisingMechanism.h"

namespace rrc {
    class MechanismsHolder {
    public:
        // TODO: Docs and tests
        MechanismsHolder(std::shared_ptr<TaskQueueAdapter> queue);

        AdvertisingMechanism& getAdvetisingMechanism();

        const AdvertisingMechanism& getAdvetisingMechanism() const;


    private:
        AdvertisingMechanism mAdvertisingMechanism;

    };
}