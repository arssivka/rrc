/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#include <rrc/core/SettingsBillboard.h>

void rrc::SettingsBillboard::PropertyDictionary::removeProperty(const std::string &key) {
    auto to_erase = mPropertyDictionary->find(key);
    if(to_erase != mPropertyDictionary->end()) {
        mPropertyDictionary->erase(to_erase);
    }
}

void rrc::SettingsBillboard::PropertyDictionary::addListener(rrc::AbstractPropertyListenerPtr listener) {
    mListeners.push_front(listener);
    listener->setDictionary(mPropertyDictionary);
}

void rrc::SettingsBillboard::PropertyDictionary::removeListener(rrc::AbstractPropertyListenerPtr listener) {
    mListeners.remove(listener);
}

bool rrc::SettingsBillboard::PropertyDictionary::contains(const std::string &key) const {
    return !(mPropertyDictionary->find(key) == mPropertyDictionary->end());
}

bool rrc::SettingsBillboard::PropertyDictionary::empty() const {
    return mPropertyDictionary->empty();
}

bool rrc::SettingsBillboard::PropertyDictionary::hasListeners() const {
    return  !mListeners.empty();
}

std::set<std::string> rrc::SettingsBillboard::PropertyDictionary::getKeys() const {
    std::set<std::string> mKeySet;
    for (std::map<std::string, rrc::Property>::iterator it = mPropertyDictionary->begin(); it != mPropertyDictionary->end(); ++it) {
        mKeySet.insert(it->first);
    }
    return mKeySet;
}