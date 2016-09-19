/**
 *  @autor arssivka
 *  @date 8/31/16
 */

#pragma once


#include <string>
#include "MetaTable.h"

namespace rrc {
    /**
     * @brief Exception thrown when types of messages are missmaching
     */
    class IncompatibleTypesException : public std::runtime_error {
    public:
        IncompatibleTypesException(TypeId firstType = MetaTable::UNKNOWN_TYPE_ID,
                                   TypeId secondType = MetaTable::UNKNOWN_TYPE_ID);

        TypeId getFirstTypeId() const;

        TypeId getSeconTypeId() const;

    private:
        TypeId mFirstTypeId;
        TypeId mSeconTypeId;
    };
}

