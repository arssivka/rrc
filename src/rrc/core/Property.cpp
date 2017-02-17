/**
 *  @autor tekatod
 *  @date 7/15/16
 */
#include <ostream>
#include <rrc/core/Property.h>
#include <rrc/core/Array.h>
#include <rrc/core/Table.h>
#include <mapbox/variant_io.hpp>


rrc::Property::Property(const rrc::String& string) {
    mValue->set<String>(string);
}


rrc::Property::Property(rrc::String&& string) {
    mValue->set<String>(std::move(string));
}


rrc::Property::Property(const rrc::Number& number) {
    mValue->set<Number>(number);
}


rrc::Property::Property(const rrc::Boolean& boolean) {
    mValue->set<Boolean>(boolean);
}


rrc::Property::Property(const rrc::Array& array) {
    mValue->set<mapbox::util::recursive_wrapper<Array>>(mapbox::util::recursive_wrapper<Array>(array));
}


rrc::Property::Property(rrc::Array&& array) {
    mValue->set<mapbox::util::recursive_wrapper<Array>>(mapbox::util::recursive_wrapper<Array>(std::move(array)));
}


rrc::Property::Property(const rrc::Table& table) {
    mValue->set<Table>(table);
}


rrc::Property::Property(rrc::Table&& table) {
    mValue->set<Table>(std::move(table));
}


rrc::PropertyType rrc::Property::getType() const {
    switch (mValue->which()) {
        case Value::which<Nil>(): return PropertyType::Nil;
        case Value::which<Boolean>() : return PropertyType::Boolean;
        case Value::which<Number>() : return PropertyType::Number;
        case Value::which<String>() : return PropertyType::String;
        case Value::which<mapbox::util::recursive_wrapper<Array>>() : return PropertyType::Array;
        case Value::which<mapbox::util::recursive_wrapper<Table>>() : return PropertyType::Table;
        default: return PropertyType::Unknown;
    }
}


bool rrc::Property::tryGetNumber(rrc::Number& outputNumber) const {
    if (this->isNumber()) {
        outputNumber = mValue->get_unchecked<Number>();
        return true;
    }
    return false;
}


bool rrc::Property::tryGetBoolean(rrc::Boolean& outputBoolean) const {
    if (this->isBoolean()) {
        outputBoolean = mValue->get_unchecked<Boolean>();
        return true;
    }
    return false;
}


bool rrc::Property::tryGetString(rrc::String& outputString) const {
    if (this->isString()) {
        outputString = mValue->get_unchecked<String>();
        return true;
    }
    return false;
}


bool rrc::Property::tryGetArray(rrc::Array& outputArray) const {
    if (this->isArray()) {
        outputArray = mValue->get_unchecked<mapbox::util::recursive_wrapper<Array>>();
        return true;
    }
    return false;
}


bool rrc::Property::tryGetTable(rrc::Table& outputTable) const {
    if (this->isTable()) {
        outputTable = mValue->get_unchecked<mapbox::util::recursive_wrapper<Table>>();
        return true;
    }
    return false;
}


void rrc::Property::setNil() {
    mValue->set<Nil>(Nil());
}


void rrc::Property::setBoolean(rrc::Boolean&& boolean) {
    mValue->set<Boolean>(std::move(boolean));
}


void rrc::Property::setNumber(rrc::Number&& number) {
    mValue->set<Number>(std::move(number));
}


void rrc::Property::setString(rrc::String&& string) {
    mValue->set<String>(std::move(string));
}


void rrc::Property::setArray(rrc::Array&& array) {
    mValue->set<Array>(std::move(array));
}


void rrc::Property::setTable(rrc::Table&& table) {
    mValue->set<Table>(std::move(table));
}

void rrc::Property::setBoolean(const rrc::Boolean& boolean) {
    mValue->set<Boolean>(boolean);
}


void rrc::Property::setNumber(const rrc::Number& number) {
    mValue->set<Number>(number);
}


void rrc::Property::setString(const rrc::String& string) {
    mValue->set<String>(string);
}


void rrc::Property::setArray(const rrc::Array& array) {
    mValue->set<Array>(array);
}


void rrc::Property::setTable(const rrc::Table& table) {
    mValue->set<Table>(table);
}

bool rrc::Property::isValid() const {
    return mValue->valid();
}


bool rrc::Property::isNil() const {
    return !mValue->valid() || mValue->is<Nil>();
}


bool rrc::Property::isBoolean() const {
    return mValue->is<Boolean>();
}


bool rrc::Property::isNumber() const {
    return mValue->is<Number>();
}


bool rrc::Property::isString() const {
    return mValue->is<String>();
}


bool rrc::Property::isArray() const {
    return mValue->is<Array>();
}


bool rrc::Property::isTable() const {
    return mValue->is<Table>();
}


namespace rrc {
    std::ostream& operator<<(std::ostream& os, const rrc::Property& property) {
        os << *property.mValue;
        return os;
    }
}


rrc::Property::Property(rrc::Number&& number) {
    mValue->set<Number>(std::move(number));
}


rrc::Property::Property(rrc::Boolean&& boolean) {
    mValue->set<Boolean>(std::move(boolean));
}


rrc::Property::Property() {
    mValue->set<Nil>(Nil());
}


bool rrc::Property::operator<(const rrc::Property& rhs) const {
    return *mValue < *(rhs.mValue);
}


bool rrc::Property::operator>(const rrc::Property& rhs) const {
    return rhs < *this;
}


bool rrc::Property::operator<=(const rrc::Property& rhs) const {
    return !(rhs < *this);
}


bool rrc::Property::operator>=(const rrc::Property& rhs) const {
    return !(*this < rhs);
}


bool rrc::Property::operator==(const rrc::Property& rhs) const {
    return *mValue == *rhs.mValue;
}


bool rrc::Property::operator!=(const rrc::Property& rhs) const {
    return !(rhs == *this);
}
