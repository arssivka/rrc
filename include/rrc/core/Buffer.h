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

        const uint8_t* begin() const noexcept;

        const uint8_t* end() const noexcept;

        std::reverse_iterator<const uint8_t*> rbegin() const noexcept;

        std::reverse_iterator<const uint8_t*> rend() const noexcept;

        const uint8_t* cbegin() const noexcept;

        const uint8_t* cend() const noexcept;

        std::reverse_iterator<const uint8_t*> crbegin() const noexcept;

        std::reverse_iterator<const uint8_t*> crend() const noexcept;

        friend std::ostream& operator<<(std::ostream& os, const Buffer& buffer);

    private:
        std::unique_ptr<uint8_t> mBufferPtr;
        size_t mSize;

    };
}


