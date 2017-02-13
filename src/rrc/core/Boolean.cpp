/**
 *  @autor arssivka
 *  @date 2/9/17
 */

#include <rrc/core/Boolean.h>


rrc::Boolean::Boolean(bool value)
        : mValue(value) {}


bool rrc::Boolean::get() const {
    return mValue;
}


void rrc::Boolean::set(bool value) {
    mValue = value;
}


bool rrc::Boolean::operator==(const rrc::Boolean& rhs) const {
    return mValue == rhs.mValue;
}


bool rrc::Boolean::operator!=(const rrc::Boolean& rhs) const {
    return !(rhs == *this);
}


namespace rrc {
    std::ostream& operator<<(std::ostream& os, const rrc::Boolean& boolean) {
        os << (boolean.get() ? "True" : "False");
        return os;
    }
}


rrc::Boolean::operator bool() const {
    return mValue;
}
