/**
 *  @autor tekatod
 *  @date 10/7/16
 */
#include "rrc/core/PropertyDictionary.h"

rrc::PropertyDictionary::PropertyDictionary(rrc::CopyOnWrite<std::map<std::string, rrc::Property>> dictionary) {
    this->setDictionary(dictionary);
}

void rrc::PropertyDictionary::setDictionary(rrc::CopyOnWrite<std::map<std::string, rrc::Property>> dictionary) {
    mDictionary = dictionary;
}

rrc::Property rrc::PropertyDictionary::getProperty(const std::string &key) {
    auto property = mDictionary->find(key);
    if(property != mDictionary->end()) {
        return property->second;
    }
    return rrc::Property();
}

bool rrc::PropertyDictionary::contains(const std::string key) const {
    return !(mDictionary->find(key) == mDictionary->end());
}


