/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#include "include/rrc/Settings.h"

rrc::Settings::Settings(unsigned num) : mSettings(num) { }


rrc::Settings::Settings() {}


void rrc::Settings::set(const std::string& key, rrc::Property&& data) {
    mSettings.set(key, std::move(data));
}


void rrc::Settings::remove(const std::string& key) {
    mSettings.remove(key);
}


rrc::Property rrc::Settings::get(const std::string& key) const {
    return mSettings.get(key);
}


bool rrc::Settings::contains(const std::string& key) const {
    return mSettings.contains(key);
}
