/**
 *  @autor arssivka
 *  @date 11/2/16
 */

#include <rrc/core/MechanismsHolder.h>


rrc::MechanismsHolder::MechanismsHolder(std::shared_ptr<rrc::TaskQueueAdapter> queue)
        : mAdvertisingMechanism(std::move(queue)) {}


rrc::AdvertisingMechanism& rrc::MechanismsHolder::getAdvetisingMechanism() {
    return mAdvertisingMechanism;
}


const rrc::AdvertisingMechanism& rrc::MechanismsHolder::getAdvetisingMechanism() const {
    return mAdvertisingMechanism;
}
