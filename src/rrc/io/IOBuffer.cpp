/**
 *  @autor Nikita Somenkov
 *  @date 08/10/2016
 */
#include "rrc/io/IOBuffer.h"

#include <cstring>

rrc::IOBuffer::IOBuffer() : mData(nullptr), mSize(0) {

}

rrc::IOBuffer::IOBuffer(const rrc::IOBuffer &other) :
        IOBuffer(other.data(), other.size()) { }

rrc::IOBuffer::IOBuffer(const char *data, size_t size) : mSize(size) {
    this->copyBuffer(data);
}

rrc::IOBuffer::IOBuffer(size_t size) : mSize(size), mData(new char[size]) {

}

rrc::IOBuffer &rrc::IOBuffer::operator=(const rrc::IOBuffer &other) {
    if (mData != nullptr)
        delete [] mData;
    mSize = other.size();
    this->copyBuffer(other.data());
    return *this;
}

size_t rrc::IOBuffer::size() const {
    return mSize;
}

char * rrc::IOBuffer::data() {
    return mData;
}

const char * rrc::IOBuffer::data() const {
    return mData;
}

void rrc::IOBuffer::copyBuffer(const char *buffer) {
    mData = new char[mSize];
    ::memcpy(mData, buffer, mSize);
}

rrc::IOBuffer::~IOBuffer() {
    delete [] mData;
}
