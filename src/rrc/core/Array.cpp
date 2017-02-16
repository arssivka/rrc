/**
 *  @autor arssivka
 *  @date 2/9/17
 */

#include <rrc/core/Array.h>
#include <rrc/core/Property.h>


rrc::Property& rrc::Array::operator[](size_t index) { return mVector[index]; }


const rrc::Property& rrc::Array::operator[](size_t index) const {
    return mVector[index];
}


rrc::Property rrc::Array::get(size_t index, rrc::Property defaultValue) const {
    if (index >= mVector.size()) return defaultValue;
    return mVector[index];
}


bool rrc::Array::tryGet(size_t index, rrc::Property& output) const {
    if (index >= mVector.size()) return false;
    output = mVector[index];
    return true;
}


bool rrc::Array::erase(size_t index) {
    if (index >= mVector.size()) return false;
    auto it = mVector.begin();
    std::advance(it, index);
    mVector.erase(it);
    return true;
}


void rrc::Array::set(size_t index, const rrc::Property& value) {
    mVector[index] = value;
}


void rrc::Array::set(size_t index, rrc::Property&& value) {
    mVector[index] = std::move(value);
}


void rrc::Array::reserve(size_t size) {
    mVector.reserve(size);
}


void rrc::Array::push(const rrc::Property& value) {
    mVector.emplace_back(value);
}


void rrc::Array::push(rrc::Property&& value) {
    mVector.emplace_back(std::move(value));
}


rrc::Property rrc::Array::pop() {
    Property last = std::move(mVector.back());
    mVector.pop_back();
    return last;
}


bool rrc::Array::isEmpty() const noexcept {
    return mVector.empty();
}


size_t rrc::Array::getSize() const noexcept {
    return mVector.size();
}

bool rrc::Array::operator==(const rrc::Array& rhs) const {
    return mVector == rhs.mVector;
}

bool rrc::Array::operator!=(const rrc::Array& rhs) const {
    return mVector != rhs.mVector;
}

bool rrc::Array::operator>(const rrc::Array& rhs) const {
    return mVector > rhs.mVector;
}

bool rrc::Array::operator<(const rrc::Array& rhs) const {
    return mVector < rhs.mVector;
}

bool rrc::Array::operator<=(const rrc::Array& rhs) const {
    return mVector <= rhs.mVector;
}

bool rrc::Array::operator>=(const rrc::Array& rhs) const {
    return mVector >= rhs.mVector;
}

auto rrc::Array::begin() noexcept { return mVector.begin(); }


auto rrc::Array::end() noexcept { return mVector.end(); }


auto rrc::Array::rbegin() noexcept { return mVector.rbegin(); }


auto rrc::Array::rend() noexcept { return mVector.rend(); }


const auto rrc::Array::begin() const noexcept { return mVector.begin(); }


const auto rrc::Array::end() const noexcept { return mVector.end(); }


const auto rrc::Array::rbegin() const noexcept { return mVector.rbegin(); }


const auto rrc::Array::rend() const noexcept { return mVector.rend(); }


const auto rrc::Array::cbegin() const noexcept { return mVector.cbegin(); }


const auto rrc::Array::cend() const noexcept { return mVector.cend(); }


const auto rrc::Array::crbegin() const noexcept { return mVector.crbegin(); }


const auto rrc::Array::crend() const noexcept { return mVector.crend(); }


void rrc::Array::resize(size_t size) {
    mVector.resize(size);
}
