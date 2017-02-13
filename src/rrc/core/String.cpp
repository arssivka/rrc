/**
 *  @autor arssivka
 *  @date 2/9/17
 */

#include <rrc/core/String.h>


rrc::String::String(const std::string& string)
        : mString(string) {}


rrc::String::String(std::string&& string)
        : mString(std::move(string)) {}


rrc::String::String(const std::string& string, size_t position, size_t length)
        : mString(string, position, length) {}


rrc::String::String(const char* cstring)
        : mString(cstring) {}


rrc::String::String(size_t n, char c)
        : mString(n, c) {}


rrc::String::String(std::initializer_list<char> initializerList)
        : mString(initializerList) {}


const std::string& rrc::String::get() const {
    return mString;
}


void rrc::String::set(const std::string& string) {
    mString = string;
}


bool rrc::String::operator==(const rrc::String& rhs) const {
    return mString == rhs.mString;
}


bool rrc::String::operator!=(const rrc::String& rhs) const {
    return !(rhs == *this);
}


std::ostream& operator<<(std::ostream& os, const rrc::String& string) {
    os << string.get();
    return os;
}


rrc::String::operator const std::string&() {
    return mString;
}


size_t rrc::String::getSize() const {
    return mString.size();
}


bool rrc::String::isEmpty() const {
    return mString.empty();
}


const char& rrc::String::operator[](size_t index) { return mString[index]; }


const auto rrc::String::begin() const noexcept { return mString.begin(); }


const auto rrc::String::end() const noexcept { return mString.end(); }


const auto rrc::String::rbegin() const noexcept { return mString.rbegin(); }


const auto rrc::String::rend() const noexcept { return mString.rend(); }


const auto rrc::String::cbegin() const noexcept { return mString.cbegin(); }


const auto rrc::String::cend() const noexcept { return mString.cend(); }


const auto rrc::String::crbegin() const noexcept { return mString.crbegin(); }


const auto rrc::String::crend() const noexcept { return mString.crend(); }
