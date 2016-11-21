/**
 *  @autor arssivka
 *  @date 11/15/16
 */

#pragma once


#include <string>

namespace rrc {
    class MechanismVersion {
    public:
        MechanismVersion(const std::string& name, unsigned int version);

        const std::string& getName() const noexcept;

        unsigned int getVersion() const noexcept;

    private:
        std::string mName;
        unsigned int mVersion;
    };
}


