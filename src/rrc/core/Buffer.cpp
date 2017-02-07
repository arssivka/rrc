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
    uint8_t* bufferPtr = new uint8_t[mSize];
    for(size_t i = 0; i < mSize; ++i) {
        bufferPtr[i] = other.getBufferPointer()[i];
    }
    mBufferPtr = std::unique_ptr<uint8_t>(new uint8_t[mSize]);
    memcpy(mBufferPtr.get(), bufferPtr, mSize);
    delete[] bufferPtr;
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
