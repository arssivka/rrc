/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#pragma once


#include <string>
#include <atomic>
#include <ostream>

namespace rrc {
    class ID {
    public:
        typedef unsigned int Counter;

        static Counter getCounter();

        ID(const ID& other) = default;

        ID(ID&& other) = default;

        ID(const std::string& name);

        const std::string& getName() const;

        void setName(const std::string& name);

        Counter getCode() const;

        void setCode(unsigned code);

        bool initialized() const;

        bool operator==(const ID& other) const;

        bool operator!=(const ID& other) const;

        bool operator==(const std::string& name) const;

        bool operator!=(const std::string& other) const;

        bool operator==(Counter code) const;

        bool operator!=(Counter code) const;

        operator std::string() const;

        operator Counter() const;

    private:
        static std::atomic<Counter> sCounter = {0};

        std::string mName;
        Counter mCode;
    };

    std::ostream &rrc::operator<<(std::ostream &os, const ID &id) {
        os << "#" << id.getCode() << ":" << id.getName();
        return os;
    }
}

namespace std {
    template <>
    struct hash<rrc::ID> {
        std::size_t operator()(const rrc::ID& id) const {
            return hash<decltype(id.getCode())>()(id.getCode());
        }
    };
}



