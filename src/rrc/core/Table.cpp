/**
 *  @autor arssivka
 *  @date 2/9/17
 */

#include <rrc/core/Table.h>


namespace rrc {
    std::ostream& operator<<(std::ostream& os, const rrc::Table& table) {
        auto& hash = table.mHash;
        auto it = hash.begin();
        if (it != hash.end()) {
            os << '[' << it->first << ": " << it->second;
            while (it != hash.end()) {
                os << ',' << it->first << ": " << it->second;
                ++it;
            }
            os << ']';
        }
        return os;
    }


    const Property& Table::operator[](const Table::Key& index) const {
        return mHash.at(index);
    }


    Property& Table::operator[](const Table::Key& index) {
        return mHash.at(index);
    }


    const Property& Table::get(const Table::Key& index, Property defaultValue) const {
        auto found = mHash.find(index);
        return (found != mHash.end())
               ? found->second
               : defaultValue;
    }


    bool Table::tryGet(const Table::Key& index, Property& output) {
        auto found = mHash.find(index);
        if (found == mHash.end()) return false;
        output = found->second;
        return true;
    }


    bool Table::erase(const Table::Key& index) {
        auto found = mHash.find(index);
        if (found == mHash.end()) return false;
        mHash.erase(found);
        return true;
    }


    void Table::set(const Table::Key& index, const Property value) {
        mHash[index] = value;
    }


    void Table::set(const Table::Key& index, Property&& value) {
        mHash[index] = std::move(value);
    }


    bool Table::isEmpty() const {
        return mHash.empty();
    }


    size_t Table::getSize() const {
        return mHash.size();
    }


    std::vector<Table::Key> Table::getNames() const {
        std::vector<Key> names;
        names.reserve(mHash.size());
        for (auto&& keyPair : mHash) {
            auto& name = keyPair.first;
            names.push_back(name);
        }
        return names;
    }


    auto Table::begin() noexcept { return mHash.begin(); }


    auto Table::end() noexcept { return mHash.end(); }


    const auto Table::begin() const noexcept { return mHash.begin(); }


    const auto Table::end() const noexcept { return mHash.end(); }


    const auto Table::cbegin() const noexcept { return mHash.cbegin(); }


    const auto Table::cend() const noexcept { return mHash.cend(); }
}
