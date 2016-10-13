/**
 *  @autor nikitas
 *  @date 10/13/16
 */

#include "rrc/io/IOError.h"


rrc::IOError::IOError() : mError(false), std::runtime_error("IOError: not error") {

}

rrc::IOError::IOError(const rrc::IOError &other)
        : mError(other.mError),
          std::runtime_error(static_cast<const std::runtime_error&>(other)) { }

rrc::IOError::IOError(bool error, const std::string &msg) :
        mError(error), std::runtime_error("IOError: " + msg) { }

rrc::IOError::operator bool() const {
    return mError;
}

