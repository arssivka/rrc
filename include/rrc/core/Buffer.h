/**
 *  @autor arssivka
 *  @date 12/19/16
 */

#pragma once


#include <vector>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>

namespace rrc {
    // TODO: Tests and docs
    class Buffer {
    public:
        Buffer(const uint8_t* bufferPtr, const size_t size);

        Buffer(Buffer&& other) = default;

        Buffer(const Buffer& other);

        const uint8_t* getBufferPointer() const;

        const size_t getSize() const;

        bool isEmpty() const;

        bool operator==(const Buffer& rhs) const;

        bool operator!=(const Buffer& rhs) const;

        Buffer& operator=(const Buffer& other);

        Buffer& operator=(Buffer&& other) = default;

        const uint8_t* begin() const noexcept { return this->getBufferPointer(); }

        const uint8_t* end() const noexcept { return this->getBufferPointer() + this->getSize(); }

        std::reverse_iterator<const uint8_t*> rbegin() const noexcept {
            return std::reverse_iterator<const uint8_t*>(this->end());
        }

        std::reverse_iterator<const uint8_t*> rend() const noexcept {
            return std::reverse_iterator<const uint8_t*>(this->begin());
        }

        const uint8_t* cbegin() const noexcept { return this->begin(); }

        const uint8_t* cend() const noexcept { return this->end(); }

        std::reverse_iterator<const uint8_t*> crbegin() const noexcept {
            return this->rend();
        }

        std::reverse_iterator<const uint8_t*> crend() const noexcept {
            return this->rbegin();
        }

        friend std::ostream& operator<<(std::ostream& os, const Buffer& buffer);

    private:
        std::unique_ptr<uint8_t> mBufferPtr;
        size_t mSize;

    };
}


