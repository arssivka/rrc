/**
 *  @autor arssivka
 *  @date 11/2/16
 */

#include <rrc/core/MechanismsHolder.h>


rrc::MechanismsHolder::MechanismsHolder(rrc::TaskQueueWrapper queue)
        : mAdvertisingMechanism(std::move(queue)) {}


rrc::AdvertisingMechanism& rrc::MechanismsHolder::getAdvertisingMechanism() {
    return mAdvertisingMechanism;
}


const rrc::AdvertisingMechanism& rrc::MechanismsHolder::getAdvertisingMechanism() const {
    return mAdvertisingMechanism;
}
