/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


#include <cstddef>
#include <type_traits>
#include "rrc/meta.h"

namespace rrc {
    /**
     * @brief Wrapper around reference to array.
     * @tparam T Array type
     */
    template <class T>
    class ArrayReference {
    public:
        /**
         * @brief Default constructor. Sets inner pointer to nullptr, size to 0
         */
        ArrayReference()
                : mArrayPointer(nullptr), mSize(0) {}

        /**
         * @brief Default copy constructor
         * @param other Reference to instance to copy from
         */
        ArrayReference(const ArrayReference<T>& other) = default;

        /**
         * @brief Default move constructor
         * @param other RValue reference to instance to move from
         */
        ArrayReference(ArrayReference<T>&& other) = default;

        /**
         * @brief Default destructor
         */
        ~ArrayReference() = default;

        /**
         * @brief Constructor of ArrayReference
         * @tparam A Type of array
         * @param array Pointer to array
         * @param size Size of array
         */
        template <class A>
        ArrayReference(A* array, std::size_t size) {
            mArrayPointer = array;
            mSize = size;
        }

        ArrayReference& operator=(const ArrayReference& other) = default;

        ArrayReference& operator=( ArrayReference&& other) = default;

        /**
         * @brief Checks if this instance was initialized by array
         * @return True if was initialized, otherwise false
         */
        bool isInitialized() const noexcept {
            return mArrayPointer != nullptr;
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

        /**
         * @brief Returns size of the array
         * @return Size of type size_t
         */
        std::size_t getSize() const {
            return mSize;
        }

        /**
         * @brief Returns pointer to an array this instance holds pointer to
         * @return Pointer to an array of type T*
         */
        T* getArrayPointer() {
            return mArrayPointer;
        }

        /**
         * @brief Returns const pointer to an array this instance holds pointer to
         * @return Const pointer to an array of type T*
         */
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
        T* mArrayPointer;
        std::size_t mSize;

    };
}