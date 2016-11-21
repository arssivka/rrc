/**
 *  @autor arssivka
 *  @date 11/15/16
 */

#include "rrc/core/MechanismVersion.h"


rrc::MechanismVersion::MechanismVersion(const std::string& name, unsigned int version)
        : mName(name), mVersion(version) {}


const std::string& rrc::MechanismVersion::getName() const noexcept {
    return mName;
}


unsigned int rrc::MechanismVersion::getVersion() const noexcept {
    return mVersion;
}
