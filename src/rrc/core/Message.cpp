/**
 *  @autor arssivka
 *  @date 2/2/17
 */

#include <rrc/core/Message.h>


rrc::Message::Message(const uint8_t* bufferPtr, const size_t size) {
    if (size > 0) {
        auto begin = bufferPtr;
        auto end = bufferPtr + size;
        mBinaryVector.assign(begin, end);
    }
}


const std::vector<uint8_t>& rrc::Message::getBinaryVector() const {
    return mBinaryVector;
}


bool rrc::Message::isEmpty() const {
    return mBinaryVector.empty();
}
