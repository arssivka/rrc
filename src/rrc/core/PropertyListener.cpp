/**
 *  @autor tekatod
 *  @date 9/26/16
 */

#include <rrc/core/PropertyListener.h>


rrc::Property rrc::PropertyListener::getProperty(const std::string& propertyName) {
    return mPropertyDictionary.getProperty(propertyName);
}


rrc::PropertyDictionary rrc::PropertyListener::getDictionary() {
    return mPropertyDictionary;
}


void rrc::PropertyListener::setDictionary(PropertyDictionary dictionary) {
    mPropertyDictionary = dictionary;
}


bool rrc::PropertyListener::isContainsName(const std::string &propertyName) {
    return mPropertyDictionary.isContainsName(propertyName);
}
