/**
 *  @autor arssivka
 *  @date 8/29/16
 */

#pragma once


#include <string>
#include <stdexcept>
#include "MetaTable.h"

namespace rrc {
    /**
     * @brief Exception thrown when type of message is not registered in Meta Table
     */
    class UnregisteredTypeException : public std::runtime_error {
    public:
        UnregisteredTypeException(TypeId typeId = MetaTable::UNKNOWN_TYPE_ID);

        TypeId getTypeId() const;

    private:
        TypeId mTypeId;
    };
}


