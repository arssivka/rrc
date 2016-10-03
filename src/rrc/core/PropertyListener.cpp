/**
 *  @autor tekatod
 *  @date 9/26/16
 */

#include <rrc/core/PropertyListener.h>


rrc::Property rrc::PropertyListener::getProperty(std::string key) {
    auto property = mPropertyDictionary->find(key);
    if(property != mPropertyDictionary->end()) {
        return property->second;
    }
    return nullptr;
}

rrc::CopyOnWrite<std::map<std::string, rrc::Property>> rrc::PropertyListener::getDictionary() {
    return mPropertyDictionary;
}

void rrc::PropertyListener::setDictionary(CopyOnWrite<std::map<std::string, Property>> dictionary) {
    mPropertyDictionary = dictionary;
}