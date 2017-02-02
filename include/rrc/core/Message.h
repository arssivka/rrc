/**
 *  @autor arssivka
 *  @date 12/19/16
 */

#pragma once


#include <vector>
#include <cstddef>
#include <cstdint>

namespace rrc {
    // TODO: Tests and docs
    class Message {
    public:
        Message(const uint8_t* bufferPtr, const size_t size);

        const std::vector<uint8_t>& getBinaryVector() const;

        bool isEmpty() const;

    private:
        std::vector<uint8_t> mBinaryVector;

    };
}


