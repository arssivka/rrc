/**
 *  @autor arssivka
 *  @date 2/2/17
 */

#include <rrc/core/Buffer.h>
#include <cstring>
#include <algorithm>
#include <iterator>


rrc::Buffer::Buffer(const uint8_t* bufferPtr, const size_t size) {
    if (size > 0) {
        mSize = size;
        mBufferPtr = std::unique_ptr<uint8_t>(new uint8_t[size]);
        memcpy(mBufferPtr.get(), bufferPtr, size);
    } else {
        mBufferPtr = nullptr;
        mSize = 0;
    }
}

rrc::Buffer::Buffer(const Buffer& other) {
    mSize = other.mSize;
    mBufferPtr = std::unique_ptr<uint8_t>(new uint8_t[mSize]);
    memcpy(mBufferPtr.get(), other.getBufferPointer(), mSize);
}


bool rrc::Buffer::isEmpty() const {
    return mBufferPtr == nullptr;
}


const size_t rrc::Buffer::getSize() const {
    return mSize;
}


const uint8_t* rrc::Buffer::getBufferPointer() const {
    return mBufferPtr.get();
}


bool rrc::Buffer::operator==(const rrc::Buffer& rhs) const {
    return mSize == rhs.mSize && ((mBufferPtr == rhs.mBufferPtr) ||
            (0 == memcmp(mBufferPtr.get(), rhs.mBufferPtr.get(), std::min(mSize, rhs.mSize))));
}


bool rrc::Buffer::operator!=(const rrc::Buffer& rhs) const {
    return !(rhs == *this);
}


std::ostream& operator<<(std::ostream& os, const rrc::Buffer& buffer) {
    std::ostream_iterator<uint8_t> it(os);
    std::copy(buffer.begin(), buffer.end(), it);
    return os;
}


const uint8_t* rrc::Buffer::begin() const noexcept { return this->getBufferPointer(); }


const uint8_t* rrc::Buffer::end() const noexcept { return this->getBufferPointer() + this->getSize(); }


std::reverse_iterator<const uint8_t*> rrc::Buffer::rbegin() const noexcept {
    return std::reverse_iterator<const uint8_t*>(this->end());
}


std::reverse_iterator<const uint8_t*> rrc::Buffer::rend() const noexcept {
    return std::reverse_iterator<const uint8_t*>(this->begin());
}


const uint8_t* rrc::Buffer::cbegin() const noexcept { return this->begin(); }


const uint8_t* rrc::Buffer::cend() const noexcept { return this->end(); }


std::reverse_iterator<const uint8_t*> rrc::Buffer::crbegin() const noexcept {
    return this->rend();
}


std::reverse_iterator<const uint8_t*> rrc::Buffer::crend() const noexcept {
    return this->rbegin();
}
