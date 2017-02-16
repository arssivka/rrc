/**
 *  @autor arssivka
 *  @date 2/9/17
 */

#pragma once

#include "Property.h"
#include <unordered_map>
#include <ostream>
#include <vector>

namespace rrc {
    class Table {
    public:
        typedef std::string Key;

        Table() = default;

        Table(const Table&) = default;

        Table(Table&&) = default;

        Table& operator=(const Table&) = default;

        Table& operator=(Table&&) = default;

        friend std::ostream& operator<<(std::ostream& os, const rrc::Table& table);

        const Property& operator[](const Key& index) const;

        Property& operator[](const Key& index);

        const Property& get(const Key& index, Property defaultValue = Property()) const;

        bool tryGet(const Key& index, Property& output);

        bool erase(const Key& index);

        void set(const Key& index, const Property value);

        void set(const Key& index, Property&& value);

        bool isEmpty() const;

        size_t getSize() const;

        std::vector<Key> getNames() const;

        bool operator==(const Table& rhs) const;

        bool operator!=(const Table& rhs) const;

        bool operator>(const Table& rhs) const;

        bool operator<(const Table& rhs) const;

        bool operator<=(const Table& rhs) const;

        bool operator>=(const Table& rhs) const;

        auto begin() noexcept;

        auto end() noexcept;

        const auto begin() const noexcept;

        const auto end() const noexcept;

        const auto cbegin() const noexcept;

        const auto cend() const noexcept;

    private:
        std::unordered_map<Key, Property> mHash;
    };
}

