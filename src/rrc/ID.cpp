/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#include <rrc/ID.h>


rrc::ID::ID(const std::string& name) : mName(name), mCode(sCounter++) {}


const std::string& rrc::ID::getName() const {
    return mName;
}


void rrc::ID::setName(const std::string& name) {
    mName = name;
}


rrc::ID::Counter rrc::ID::getCode() const {
    return mCode;
}


void rrc::ID::setCode(Counter code) {
    mCode = code;
}


bool rrc::ID::initialized() const {
    return mCode != 0;
}


bool rrc::ID::operator==(const ID& other) const {
    return mCode == other.mCode;
}


bool rrc::ID::operator!=(const ID& other) const {
    return mCode != other.mCode;
}


bool rrc::ID::operator==(const std::string& name) const {
    return mName == name;
}


bool rrc::ID::operator!=(const std::string& other) const {
    return mName != other;
}


bool rrc::ID::operator==(Counter code) const {
    return mCode == code;
}


bool rrc::ID::operator!=(Counter code) const {
    return mCode != code;
}


rrc::ID::operator std::string() const {
    return mName;
}


rrc::ID::operator Counter() const {
    return mCode;
}


rrc::ID::Counter rrc::ID::getCounter() {
    return sCounter;
}

std::ostream& std::operator<<(std::ostream& os, const rrc::ID& id) {
    os << "#" << id.getCode() << ":" << id.getName();
    return os;
}
