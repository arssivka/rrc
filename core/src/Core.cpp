/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#include "Core.h"
#include "VersionDefines.h"


std::string static constexpr rrc::Core::getVersion() {
    return std::string(RRC_VERSION);
}


std::vector<std::string>& rrc::Core::getArs() const {
    return mArgs;
}


Settings* rrc::Core::getSettings() {
    return &mSettings;
}

Core* rrc::Core::instance() {
    return sInstance;
}