/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#include "include/rrc/ID.h"


rrc::ID::ID(const std::string& name) : mName(name), mCode(sCounter++) {}


const std::string& rrc::ID::getName() const {
    return mName;
}


void rrc::ID::setName(const std::string& name) {
    mName = name;
}


unsigned int rrc::ID::getCode() const {
    return mCode;
}


void rrc::ID::setCode(unsigned code) {
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
    return mName != name;
}


bool rrc::ID::operator==(unsigned code) const {
    return mCode == code;
}


bool rrc::ID::operator!=(unsigned code) const {
    return mCode != code;
}


rrc::ID::operator std::string() const {
    return mName;
}


rrc::ID::operator unsigned() const {
    return mCode;
}


unsigned static rrc::ID::getCounter() {
    return sCounter;
}