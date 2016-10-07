/**
 *  @autor tekatod
 *  @date 10/7/16
 */
#include "rrc/core/PropertyDictionary.h"


rrc::Property rrc::PropertyDictionary::getProperty(const std::string& propertyName) {
    auto property = mDictionary->find(propertyName);
    if(property != mDictionary->end()) {
        return property->second;
    }
    return rrc::Property();
}


bool rrc::PropertyDictionary::isContains(const std::string& propertyName) const {
    return !(mDictionary->find(propertyName) == mDictionary->end());
}


bool rrc::PropertyDictionary::isEmpty() const {
    return mDictionary->empty();
}


std::vector<std::string> rrc::PropertyDictionary::getNames() const {
    std::vector<std::string> names;
    names.reserve(mDictionary->size());
    for(auto property = mDictionary->begin(); property != mDictionary->end(); ++property) {
        names.push_back(property->first);
    }
    return std::move(names);
}


void rrc::PropertyDictionary::removeProperty(const std::string& propertyName) {
    auto toErase = mDictionary->find(propertyName);
    if(toErase != mDictionary->end()) {
        mDictionary->erase(toErase);
    }
}

