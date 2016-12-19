/**
 *  @autor arssivka
 *  @date 12/13/16
 */

#pragma once


#include <algorithm>
#include <string>
#include <memory>

namespace rrc {
    template <class CharType>
    class Buffer {
    public:
        Buffer(std::initializer_list<CharType> initializerList)
                : mString(std::make_shared<const std::basic_string<CharType>>(initializerList)),
                  mBegin(0), mEnd(mString->size())  {}

        Buffer(const std::basic_string<CharType>& string)
                : mString(std::make_shared<const std::basic_string<CharType>>(string)),
                  mBegin(0), mEnd(string.size()) {}

        Buffer(std::basic_string<CharType>&& string)
                : mString(std::make_shared<const std::basic_string<CharType>>(std::move(string))),
                  mBegin(0), mEnd(mString->size()) {}

        Buffer(std::shared_ptr<const std::basic_string<CharType>> string)
                : mString(std::move(string)), mBegin(0), mEnd(mString->size()) {}

        Buffer(const Buffer& other) = default;

        Buffer(Buffer&& other) = default;

        Buffer getSubbuffer(size_t beginOffset, size_t endOffset = 0) const {
            Buffer buffer{*this};
            buffer.mBegin += beginOffset;
            buffer.mEnd -= endOffset;
            if (   buffer.mBegin > buffer.mEnd
                   || buffer.mBegin >= mString->size()
                   || buffer.mEnd > mString->size())
                throw std::out_of_range("Can't create subbufer: invalid offsets");
            return buffer;
        }

        auto begin() noexcept  -> decltype(mString->begin()) {
            auto iterator = mString->begin();
            std::advance(iterator, mBegin);
            return iterator;
        }

        auto end() noexcept -> decltype(mString->end()) {
            auto iterator = mString->begin();
            std::advance(iterator, mEnd);
            return iterator;
        }

        auto cbegin() const noexcept -> decltype(mString->cbegin()) {
            auto iterator = mString->cbegin();
            std::advance(iterator, mBegin);
            return iterator;
        }

        auto cend() const noexcept -> decltype(mString->cend()) {
            auto iterator = mString->cbegin();
            std::advance(iterator, mEnd);
            return iterator;
        }

        auto rbegin() noexcept -> decltype(mString->rbegin()) {
            auto iterator = mString->rbegin();
            const size_t offset = mString->size() - mEnd;
            std::advance(iterator, offset);
            return iterator;
        }

        auto rend() noexcept -> decltype(mString->rend()) {
            auto iterator = mString->rbegin();
            const size_t offset = mString->size() - mBegin;
            std::advance(iterator, offset);
            return iterator;
        }

        auto crbegin() const noexcept -> decltype(mString->crbegin()) {
            auto iterator = mString->crbegin();
            const size_t offset = mString->size() - mEnd;
            std::advance(iterator, offset);
            return iterator;
        }

        auto crend() const noexcept -> decltype(mString->crend()) {
            auto iterator = mString->crbegin();
            const size_t offset = mString->size() - mBegin;
            std::advance(iterator, offset);
            return iterator;
        }

        void trim(char symbol = ' ') noexcept {
            while (mString->at(mBegin) == symbol && mBegin < mEnd) ++mBegin;
            while (mString->at(mEnd - 1) == symbol && mBegin < mEnd) --mEnd;
        }

        void cut() {
            if (mBegin == 0 && mEnd == mString->size()) return;
            mString = std::make_shared<const std::basic_string<CharType>>(mString->substr(mBegin, mEnd));
            mEnd -= mBegin;
            mBegin = 0;
        }

        Buffer operator+(const Buffer& rhs) {
            Buffer first{*this};
            Buffer second{rhs};
            first.cut();
            second.cut();
            return Buffer{*first.mString += *second.mString};
        }

        CharType operator[](size_t index) const {
            index = mBegin + index;
            return mString->at(index);
        }

        CharType& operator[](size_t index) {
            index = mBegin + index;
            return mString->at(index);
        }

        bool isEmpty() const noexcept {
            return mEnd == mBegin;
        }

        size_t getSize() const noexcept {
            return mEnd - mBegin;
        }

    private:
        std::shared_ptr<const std::basic_string<CharType>> mString;
        size_t mBegin;
        size_t mEnd;
    };
}

