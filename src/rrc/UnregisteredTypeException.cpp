/**
 *  @autor arssivka
 *  @date 8/29/16
 */

#include "include/rrc/UnregisteredTypeException.h"


rrc::UnregisteredTypeException::UnregisteredTypeException()
        : mErrorString("Type was not registered in metatable") { }


rrc::UnregisteredTypeException::UnregisteredTypeException(const std::string& typeName)
        : mErrorString("Type was not registered in metatable: " + typeName) { }


rrc::UnregisteredTypeException::~UnregisteredTypeException() {

}


const char* rrc::UnregisteredTypeException::what() const {
    return mErrorString.c_str();
}
