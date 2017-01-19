/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


#include <cstddef>
#include <type_traits>
#include "rrc/meta.h"

namespace rrc {
    // TODO: Test it!
    template <class T>
    class ArrayReference {
    public:
        ArrayReference()
                : mArrayPointer(nullptr), mSize(0) {}
        
        ArrayReference(const ArrayReference<T>& other) = default;

        ArrayReference(ArrayReference<T>&& other) = default;

        ~ArrayReference() = default;

        template <class A>
        ArrayReference(A* array, std::size_t size) {
            mArrayPointer = array;
            mSize = size;
        }

        ArrayReference& operator=(const ArrayReference& other) = default;

        ArrayReference& operator=( ArrayReference&& other) = default;

        bool isInitialized() const noexcept {
            return mArrayPointer == nullptr;
        }

        template <class A>
        bool operator==(A* array) const {
            return mArrayPointer == array;
        }

        T& operator[](std::size_t index) {
            return mArrayPointer[index];
        }

        const T& operator[](std::size_t index) const {
            return mArrayPointer[index];
        }

        std::size_t getSize() const {
            return mSize;
        }

        T* getArrayPointer() {
            return mArrayPointer;
        }

        const T* getArrayPointer() const {
            return mArrayPointer;
        }

        // Iterators
        T* begin() noexcept { return this->getArrayPointer(); }

        const T* begin() const noexcept { return this->getArrayPointer(); }

        T* end() noexcept { return this->getArrayPointer() + this->getSize(); }

        const T* end() const noexcept { return this->getArrayPointer() + this->getSize(); }

        std::reverse_iterator<T*> rbegin() noexcept { return std::reverse_iterator<T*>(this->end()); }

        std::reverse_iterator<const T*> rbegin() const noexcept { return std::reverse_iterator<const T*>(this->end()); }

        std::reverse_iterator<T*> rend() noexcept { return std::reverse_iterator<T*>(begin()); }

        std::reverse_iterator<const T*> rend() const noexcept { return std::reverse_iterator<const T*>(begin()); }

        const T* cbegin() const noexcept { return this->getArrayPointer(); }

        const T* cend() const noexcept { return this->getArrayPointer() + this->getSize(); }

        std::reverse_iterator<const T*> crbegin() const noexcept { return this->end(); }

        std::reverse_iterator<const T*> crend() const noexcept { return this->begin(); }

    private:


    private:
        T* mArrayPointer;
        std::size_t mSize;

    };
}