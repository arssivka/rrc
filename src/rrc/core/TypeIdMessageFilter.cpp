/**
 * @author arssivka
 * @date 9/30/16
 */

#include <rrc/core/TypeIdMessageFilter.h>


rrc::TypeIdMessageFilter::TypeIdMessageFilter(rrc::TypeId typeId)
        : mTypeId(typeId) {}


bool rrc::TypeIdMessageFilter::accept(rrc::Message::Ptr message) {
    return    message != nullptr
           && message->getTypeId() == mTypeId;
}


rrc::TypeId rrc::TypeIdMessageFilter::getTypeId() const {
    return mTypeId;
}


void rrc::TypeIdMessageFilter::setTypeId(rrc::TypeId typeId) {
    mTypeId = typeId;
}
