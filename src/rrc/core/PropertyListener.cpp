/**
 *  @autor tekatod
 *  @date 9/26/16
 */

#include <rrc/core/PropertyListener.h>


rrc::Property rrc::PropertyListener::getProperty(const std::string& key) {
    return mPropertyDictionary.getProperty(key);
}

rrc::PropertyDictionary rrc::PropertyListener::getDictionary() {
    return mPropertyDictionary;
}

void rrc::PropertyListener::setDictionary(PropertyDictionary dictionary) {
    mPropertyDictionary = dictionary;
}

bool rrc::PropertyListener::contains(const std::string& key) {
    return mPropertyDictionary.contains(key);
}
