/**
 *  @autor arssivka
 *  @date 9/23/16
 */

#pragma once

#include <rrc/core/AbstractMessageListener.h>


rrc::AbstractMessageListener::AbstractMessageListener(rrc::TypeId typeId)
        : mTypeId(typeId) { }


rrc::TypeId rrc::AbstractMessageListener::getTypeId() const {
    return mTypeId;
}
