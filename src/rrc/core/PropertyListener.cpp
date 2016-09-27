/**
 *  @autor tekatod
 *  @date 9/26/16
 */

#include <rrc/core/PropertyListener.h>

void rrc::PropertyListener::setProperty(rrc::Property property) {
    mProperty = property;
}

rrc::Property rrc::PropertyListener::getProperty() {
    return mProperty;
}