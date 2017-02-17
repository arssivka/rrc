/**
 *  @autor arssivka
 *  @date 2/9/17
 */

#pragma once


#include <vector>
#include <cstddef>
#include "Property.h"

namespace rrc {
    class Array {
    public:
        Array() = default;

        Array(const Array&) = default;

        Array(Array&&) = default;

        Array(std::initializer_list<Property> initializerList);

        Array(size_t n, Property&& p);

        Array(size_t n, const Property& p);

        Array& operator=(const Array&) = default;

        Array& operator=(Array&&) = default;

        Property& operator[](size_t index);

        const Property& operator[](size_t index) const;
        
        Property get(size_t index, Property defaultValue = Property()) const;
        
        bool tryGet(size_t index, Property& output) const;
        
        bool erase(size_t index);

        void set(size_t index, const Property& value);

        void set(size_t index, Property&& value);

        void reserve(size_t size);

        void resize(size_t size);

        void push(const Property& value);

        void push(Property&& value);

        Property pop();
        
        bool isEmpty() const noexcept;
        
        size_t getSize() const noexcept;

        bool operator==(const Array& rhs) const;

        bool operator!=(const Array& rhs) const;

        bool operator>(const Array& rhs) const;

        bool operator<(const Array& rhs) const;

        bool operator<=(const Array& rhs) const;

        bool operator>=(const Array& rhs) const;

        auto begin() noexcept;

        auto end() noexcept;

        auto rbegin() noexcept;

        auto rend() noexcept;

        const auto begin() const noexcept;

        const auto end() const noexcept;

        const auto rbegin() const noexcept;

        const auto rend() const noexcept;

        const auto cbegin() const noexcept;

        const auto cend() const noexcept;

        const auto crbegin() const noexcept;

        const auto crend() const noexcept;


    private:
        std::vector<Property> mVector;
    };
}


