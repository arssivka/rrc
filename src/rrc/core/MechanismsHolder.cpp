/**
 *  @autor arssivka
 *  @date 11/2/16
 */

#include <rrc/core/MechanismsHolder.h>


rrc::MechanismsHolder::MechanismsHolder(std::shared_ptr<rrc::AbstractTaskQueueAdapter> queue,
                                        QueueAdapterFactory<Task> queueAdapterFactory)
        : mAdvertisingMechanism(queue, queueAdapterFactory),
          mServiceMechanism(queue, queueAdapterFactory),
          mSettingsMechanism(queue, queueAdapterFactory) {}


rrc::AdvertisingMechanism& rrc::MechanismsHolder::getAdvertisingMechanism() {
    return mAdvertisingMechanism;
}

rrc::ServiceMechanism& rrc::MechanismsHolder::getServiceMechanism() {
    return mServiceMechanism;
}


rrc::SettingsMechanism& rrc::MechanismsHolder::getSettingsMechanism() {
    return mSettingsMechanism;
}


const rrc::AdvertisingMechanism& rrc::MechanismsHolder::getAdvertisingMechanism() const {
    return mAdvertisingMechanism;
}


const rrc::ServiceMechanism& rrc::MechanismsHolder::getServiceMechanism() const {
    return mServiceMechanism;
}


const rrc::SettingsMechanism& rrc::MechanismsHolder::getSettingsMechanism() const {
    return mSettingsMechanism;
}
