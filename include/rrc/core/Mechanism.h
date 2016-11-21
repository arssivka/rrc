/**
 *  @autor arssivka
 *  @date 10/31/16
 */

#pragma once


#include "NonCopyable.h"
#include "Pointer.h"
#include "MechanismVersion.h"

namespace rrc {
    using VersionNumber = unsigned int;

    class Mechanism : public Pointer<Mechanism>, private NonCopyable {
    public:
        const VersionNumber getVersionNumber() const {
            return mVersion.getVersion();
        }
        const std::string& getName() const {
            return mVersion.getName();
        }


        const MechanismVersion& getVersion() const {
            return mVersion;
        }


        virtual ~Mechanism() { }


    protected:
        Mechanism(const std::string& name, VersionNumber versionNumber)
                : mVersion(name, versionNumber) { };


    private:
        MechanismVersion mVersion;
    };
}