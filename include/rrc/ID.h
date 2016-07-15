/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#pragma once


#include <string>
#include <atomic>

namespace rrc {
    class ID {
    public:
        static unsigned getCounter();

        ID(const ID& other) = default;

        ID(ID&& other) = default;

        ID(const std::string& name);

        const std::string& getName() const;

        void setName(const std::string& name);

        unsigned int getCode() const;

        void setCode(unsigned code);

        bool initialized() const;

        bool operator==(const ID& other) const;

        bool operator!=(const ID& other) const;

        bool operator==(const std::string& name) const;

        bool operator!=(const std::string& other) const;

        bool operator==(unsigned code) const;

        bool operator!=(unsigned code) const;

        operator std::string() const;

        operator unsigned() const;

    private:
        static std::atomic<unsigned> sCounter = {0};

        std::string mName;
        unsigned mCode;
    };
}



