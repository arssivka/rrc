/**
 *  @autor arssivka
 *  @date 8/29/16
 */

#include "include/rrc/UnregisteredTypeException.h"


rrc::UnregisteredTypeException::UnregisteredTypeException(TypeId typeId)
        : std::runtime_error("Type was not registered in metatable"), mTypeId(typeId) { }

rrc::TypeId rrc::UnregisteredTypeException::getTypeId() const {
    return mTypeId;
}
