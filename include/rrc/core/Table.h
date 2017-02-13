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

        inline const Property& operator[](const Key& index) const;

        inline Property& operator[](const Key& index);

        const Property& get(const Key& index, Property defaultValue = Property()) const;

        bool tryGet(const Key& index, Property& output);

        inline bool erase(const Key& index);

        inline void set(const Key& index, const Property value);

        inline void set(const Key& index, Property&& value);

        inline bool isEmpty() const;

        inline size_t getSize() const;

        std::vector<Key> getNames() const;

        inline auto begin() noexcept;

        inline auto end() noexcept;

        inline const auto begin() const noexcept;

        inline const auto end() const noexcept;

        inline const auto cbegin() const noexcept;

        inline const auto cend() const noexcept;

    private:
        std::unordered_map<Key, Property> mHash;
    };
}

