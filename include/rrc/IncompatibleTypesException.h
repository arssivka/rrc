/**
 *  @autor arssivka
 *  @date 8/31/16
 */

#pragma once


#include <string>
#include "MetaTable.h"

namespace rrc {
    class IncompatibleTypesException : public std::exception {
    public:
        IncompatibleTypesException();

        IncompatibleTypesException(TypeId firstType, TypeId secondType);

        virtual ~IncompatibleTypesException() override;

        virtual const char* what() const override;

    private:
        std::string mErrorString;
    };
}


