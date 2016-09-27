/**
 *  @autor arssivka
 *  @date 9/23/16
 */

#include <rrc/core/AbstractMessageListener.h>


rrc::AbstractMessageListener::AbstractMessageListener(rrc::TypeId typeId)
        : mTypeId(typeId) { }


rrc::TypeId rrc::AbstractMessageListener::getTypeId() const {
    return mTypeId;
}
