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

        Array& operator=(const Array&) = default;

        Array& operator=(Array&&) = default;

        inline Property& operator[](size_t index);

        inline const Property& operator[](size_t index) const;
        
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

        inline auto begin() noexcept;

        inline auto end() noexcept;

        inline auto rbegin() noexcept;

        inline auto rend() noexcept;

        inline const auto begin() const noexcept;

        inline const auto end() const noexcept;

        inline const auto rbegin() const noexcept;

        inline const auto rend() const noexcept;

        inline const auto cbegin() const noexcept;

        inline const auto cend() const noexcept;

        inline const auto crbegin() const noexcept;

        inline const auto crend() const noexcept;


    private:
        std::vector<Property> mVector;
    };
}


