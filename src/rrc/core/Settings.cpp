/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#include <rrc/core/Settings.h>

rrc::Settings::Settings() {
    mListenerContainers.max_load_factor(0.8);
}

//template <class T>
//void rrc::Settings::addOrUpdateProperty(const std::string &key, T property) {
//    auto container = mListenerContainers.find(key);
//    if(container != mListenerContainers.end()) {
//        container->second.updateProperty(Property(property));
//    } else {
//        mListenerContainers.insert({key, PropertyListenerContainer(Property(property))});
//    }
//}

void rrc::Settings::removeProperty(const std::string &key) {
    auto to_erase = mListenerContainers.find(key);
    if(to_erase != mListenerContainers.end()) {
        mListenerContainers.erase(to_erase);
    }
}

void rrc::Settings::addListener(const std::string &key, AbstractPropertyListenerPtr listener) {
    auto container = mListenerContainers.find(key);
    if(container != mListenerContainers.end()) {
        container->second.addListener(listener);
    }
}

void rrc::Settings::removeListener(const std::string &key, AbstractPropertyListenerPtr listener) {
    auto container = mListenerContainers.find(key);
    if(container != mListenerContainers.end()) {
        container->second.removeListener(listener);
    }
}

bool rrc::Settings::contains(const std::string &key) const {
    return !(mListenerContainers.find(key) == mListenerContainers.end());
}

bool rrc::Settings::empty() const {
    return mListenerContainers.empty();
}

bool rrc::Settings::hasListeners(const std::string &key) const {
    auto container = mListenerContainers.find(key);
    if(container != mListenerContainers.end()) {
        return container->second.hasListeners();
    }
    return false;
}

std::set<std::string> rrc::Settings::getKeys() const {
    std::set<std::string> mKeySet;
    for (auto&& container : mListenerContainers) {
        mKeySet.insert(container.first);
    }
    return mKeySet;
}

rrc::Settings::PropertyListenerContainer::PropertyListenerContainer(Property property)
        : mProperty(property) { }

void rrc::Settings::PropertyListenerContainer::addListener(AbstractPropertyListenerPtr listener) {
    listener->setProperty(mProperty);
    mListenerList.emplace_front(listener);
}

void rrc::Settings::PropertyListenerContainer::removeListener(AbstractPropertyListenerPtr listener) {
    mListenerList.remove(listener);
}

bool rrc::Settings::PropertyListenerContainer::hasListeners() const {
    return !mListenerList.empty();
}

void rrc::Settings::PropertyListenerContainer::updateProperty(Property property) {
    mProperty = property;
    for(auto&& listener : mListenerList) {
        listener->setProperty(property);
    }
}