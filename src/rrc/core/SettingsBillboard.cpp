/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#include <rrc/core/SettingsBillboard.h>

bool rrc::SettingsBillboard::empty() const {
    return mDictionaries.empty();
}

bool rrc::SettingsBillboard::isDictionaryEmpty(const std::string &dictionaryKey) const {
    auto dictionary = mDictionaries.find(dictionaryKey);
    if(dictionary != mDictionaries.end()) {
        return dictionary->second.empty();
    }
    return true;
}

bool rrc::SettingsBillboard::isDictionaryHasListeners(const std::string &dictionaryKey) const {
    auto dictionary = mDictionaries.find(dictionaryKey);
    if(dictionary != mDictionaries.end()) {
        return dictionary->second.hasListeners();
    }
    return false;
}

bool rrc::SettingsBillboard::isDictionaryContainsProperty(const std::string &dictionaryKey,
                                                          const std::string &propertyKey) const {
    auto dictionary = mDictionaries.find(dictionaryKey);
    if(dictionary != mDictionaries.end()) {
        return dictionary->second.contains(propertyKey);
    }
    return false;
}

std::vector<std::string> rrc::SettingsBillboard::getKeys() const {
    std::vector<std::string> keys;
    for(auto&& dictionary : mDictionaries) {
        keys.push_back(dictionary.first);
    }
    return std::move(keys);
}

std::vector<std::string> rrc::SettingsBillboard::getDictionaryKeys(const std::string& dictionaryKey) const {
    auto dictionary = mDictionaries.find(dictionaryKey);
    if(dictionary != mDictionaries.end()) {
        return std::move(dictionary->second.getKeys());
    }
    return std::vector<std::string>();
}

void rrc::SettingsBillboard::removeProperty(const std::string &dictionaryKey, const std::string &propertyKey) {
    auto dictionary = mDictionaries.find(dictionaryKey);
    if(dictionary != mDictionaries.end()) {
        dictionary->second.removeProperty(propertyKey);
    }
}

void rrc::SettingsBillboard::addListener(const std::string &dictionaryKey, rrc::AbstractPropertyListenerPtr listener) {
    auto dictionary = mDictionaries.find(dictionaryKey);
    if(dictionary != mDictionaries.end()) {
        dictionary->second.addListener(listener);
    }
}

void rrc::SettingsBillboard::removeListener(const std::string &dictionaryKey, rrc::AbstractPropertyListenerPtr listener) {
    auto dictionary = mDictionaries.find(dictionaryKey);
    if(dictionary != mDictionaries.end()) {
        dictionary->second.removeListener(listener);
    }
}

bool rrc::SettingsBillboard::hasDictionary(const std::string& dictionaryKey) const {
    return !(mDictionaries.find(dictionaryKey) == mDictionaries.end());
}

void rrc::SettingsBillboard::removeDictionary(const std::string &dictionaryKey) {
    mDictionaries.erase(dictionaryKey);
}

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

std::vector<std::string> rrc::SettingsBillboard::PropertyDictionary::getKeys() const {
    std::vector<std::string> mKeySet;
    for (auto property = mPropertyDictionary->begin(); property != mPropertyDictionary->end(); ++property) {
        mKeySet.push_back(property->first);
    }
    return std::move(mKeySet);
}