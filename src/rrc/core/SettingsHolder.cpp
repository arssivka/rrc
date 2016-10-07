/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#include <rrc/core/SettingsHolder.h>

bool rrc::SettingsHolder::empty() const {
    return mDictionaries.empty();
}

bool rrc::SettingsHolder::isDictionaryEmpty(const std::string &dictionaryKey) const {
    auto dictionary = mDictionaries.find(dictionaryKey);
    if(dictionary != mDictionaries.end()) {
        return dictionary->second.empty();
    }
    return true;
}

bool rrc::SettingsHolder::isDictionaryHasListeners(const std::string &dictionaryKey) const {
    auto dictionary = mDictionaries.find(dictionaryKey);
    if(dictionary != mDictionaries.end()) {
        return dictionary->second.hasListeners();
    }
    return false;
}

bool rrc::SettingsHolder::isDictionaryContainsProperty(const std::string &dictionaryKey,
                                                          const std::string &propertyKey) const {
    auto dictionary = mDictionaries.find(dictionaryKey);
    if(dictionary != mDictionaries.end()) {
        return dictionary->second.contains(propertyKey);
    }
    return false;
}

std::vector<std::string> rrc::SettingsHolder::getKeys() const {
    std::vector<std::string> keys;
    for(auto&& dictionary : mDictionaries) {
        keys.push_back(dictionary.first);
    }
    return std::move(keys);
}

std::vector<std::string> rrc::SettingsHolder::getDictionaryKeys(const std::string& dictionaryKey) const {
    auto dictionary = mDictionaries.find(dictionaryKey);
    if(dictionary != mDictionaries.end()) {
        return std::move(dictionary->second.getKeys());
    }
    return std::vector<std::string>();
}

void rrc::SettingsHolder::removeProperty(const std::string &dictionaryKey, const std::string &propertyKey) {
    auto dictionary = mDictionaries.find(dictionaryKey);
    if(dictionary != mDictionaries.end()) {
        dictionary->second.removeProperty(propertyKey);
    }
}

void rrc::SettingsHolder::addListener(const std::string &dictionaryKey, rrc::AbstractPropertyListenerPtr listener) {
    auto dictionary = mDictionaries.find(dictionaryKey);
    if(dictionary != mDictionaries.end()) {
        dictionary->second.addListener(listener);
    }
}

void rrc::SettingsHolder::removeListener(const std::string &dictionaryKey, rrc::AbstractPropertyListenerPtr listener) {
    auto dictionary = mDictionaries.find(dictionaryKey);
    if(dictionary != mDictionaries.end()) {
        dictionary->second.removeListener(listener);
    }
}

bool rrc::SettingsHolder::hasDictionary(const std::string& dictionaryKey) const {
    return !(mDictionaries.find(dictionaryKey) == mDictionaries.end());
}

void rrc::SettingsHolder::removeDictionary(const std::string &dictionaryKey) {
    mDictionaries.erase(dictionaryKey);
}

void rrc::SettingsHolder::PropertyContainer::removeProperty(const std::string &key) {
    auto to_erase = mPropertyDictionary->find(key);
    if(to_erase != mPropertyDictionary->end()) {
        mPropertyDictionary->erase(to_erase);
    }
}

void rrc::SettingsHolder::PropertyContainer::addListener(rrc::AbstractPropertyListenerPtr listener) {
    mListeners.push_front(listener);
    listener->setDictionary(mPropertyDictionary);
}

void rrc::SettingsHolder::PropertyContainer::removeListener(rrc::AbstractPropertyListenerPtr listener) {
    mListeners.remove(listener);
}

bool rrc::SettingsHolder::PropertyContainer::contains(const std::string &key) const {
    return !(mPropertyDictionary->find(key) == mPropertyDictionary->end());
}

bool rrc::SettingsHolder::PropertyContainer::empty() const {
    return mPropertyDictionary->empty();
}

bool rrc::SettingsHolder::PropertyContainer::hasListeners() const {
    return  !mListeners.empty();
}

std::vector<std::string> rrc::SettingsHolder::PropertyContainer::getKeys() const {
    std::vector<std::string> mKeySet;
    for (auto property = mPropertyDictionary->begin(); property != mPropertyDictionary->end(); ++property) {
        mKeySet.push_back(property->first);
    }
    return std::move(mKeySet);
}