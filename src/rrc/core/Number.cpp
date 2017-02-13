/**
 *  @autor arssivka
 *  @date 2/9/17
 */

#include <rrc/core/Number.h>


rrc::Number::Number(double value)
        : mValue(value) {}


double rrc::Number::get() const {
    return mValue;
}


void rrc::Number::set(double value) {
    mValue = value;
}


bool rrc::Number::operator==(const rrc::Number& rhs) const {
    return mValue == rhs.mValue;
}


bool rrc::Number::operator!=(const rrc::Number& rhs) const {
    return !(rhs == *this);
}


bool rrc::Number::operator<(const rrc::Number& rhs) const {
    return mValue < rhs.mValue;
}


bool rrc::Number::operator>(const rrc::Number& rhs) const {
    return rhs < *this;
}


bool rrc::Number::operator<=(const rrc::Number& rhs) const {
    return !(rhs < *this);
}


bool rrc::Number::operator>=(const rrc::Number& rhs) const {
    return !(*this < rhs);
}


rrc::Number::operator double() {
    return mValue;
}


namespace rrc {
    std::ostream& operator<<(std::ostream& os, const rrc::Number& number) {
        os << number.mValue;
        return os;
    }
}
