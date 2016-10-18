/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#include <rrc/core/SettingsHolder.h>


bool rrc::SettingsHolder::isEmpty() const {
    return mDictionaries.empty();
}


bool rrc::SettingsHolder::isDictionaryHasListeners(const std::string& dictionaryName) const {
    auto dictionary = mDictionaries.find(dictionaryName);
    if(dictionary != mDictionaries.end()) {
        return dictionary->second.hasListeners();
    }
    return false;
}


std::vector<std::string> rrc::SettingsHolder::getNames() const {
    std::vector<std::string> names;
    names.reserve(mDictionaries.size());
    for(auto&& dictionary : mDictionaries) {
        names.push_back(dictionary.first);
    }
    return std::move(names);
}


void rrc::SettingsHolder::removeProperty(const std::string& dictionaryName, const std::string& propertyName) {
    auto dictionary = mDictionaries.find(dictionaryName);
    if(dictionary != mDictionaries.end()) {
        dictionary->second.removeProperty(propertyName);
    }
}


void rrc::SettingsHolder::addListener(const std::string& dictionaryName, rrc::AbstractPropertyListenerPtr listener) {
    auto dictionary = mDictionaries.find(dictionaryName);
    if(dictionary != mDictionaries.end()) {
        dictionary->second.addListener(listener);
    }
}


void rrc::SettingsHolder::removeListener(const std::string& dictionaryName, rrc::AbstractPropertyListenerPtr listener) {
    auto dictionary = mDictionaries.find(dictionaryName);
    if(dictionary != mDictionaries.end()) {
        dictionary->second.removeListener(listener);
    }
}


bool rrc::SettingsHolder::hasDictionary(const std::string& dictionaryName) const {
    return !(mDictionaries.find(dictionaryName) == mDictionaries.end());
}


void rrc::SettingsHolder::removeDictionary(const std::string& dictionaryName) {
    mDictionaries.erase(dictionaryName);
}


void rrc::SettingsHolder::PropertyContainer::removeProperty(const std::string& propertyName) {
    mPropertyDictionary.removeProperty(propertyName);
    for (auto&& listener : mListeners) {
        listener->setDictionary(PropertyDictionary(mPropertyDictionary));
    }
}


void rrc::SettingsHolder::PropertyContainer::addListener(rrc::AbstractPropertyListenerPtr listener) {
    mListeners.push_front(listener);
    listener->setDictionary(mPropertyDictionary);
}


void rrc::SettingsHolder::PropertyContainer::removeListener(rrc::AbstractPropertyListenerPtr listener) {
    mListeners.remove(listener);
}


bool rrc::SettingsHolder::PropertyContainer::hasListeners() const {
    return  !mListeners.empty();
}


std::vector<std::string> rrc::SettingsHolder::PropertyContainer::getNames() const {
    return mPropertyDictionary.getNames();
}
