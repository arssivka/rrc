/**
 *  @autor arssivka
 *  @date 8/31/16
 */

#include <rrc/IncompatibleTypesException.h>
#include <rrc/MetaTable.h>
#include <sstream>


rrc::IncompatibleTypesException::IncompatibleTypesException()
        : mErrorString("Types are incompatible") { }


rrc::IncompatibleTypesException::IncompatibleTypesException(TypeId firstType, TypeId secondType) {
    std::stringstream stringstream;
    stringstream << "Types are incompatible: " << firstType << " " << secondType;
    mErrorString = stringstream.str();
}


rrc::IncompatibleTypesException::~IncompatibleTypesException() {

}


const char* rrc::IncompatibleTypesException::what() const {
    return mErrorString.c_str();
}
