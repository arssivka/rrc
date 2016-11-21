/**
 *  @autor arssivka
 *  @date 10/31/16
 */

#pragma once


#include <unordered_map>
#include <vector>
#include "Mechanism.h"

namespace rrc {
    class Engine : public Pointer<Engine> {
    public:
        void addMechanism(Mechanism::Ptr mechanism);

        void removeMechanism(Mechanism::Ptr mechanism);

        std::vector<Mechanism::Ptr> findMechanisms(const std::string& mechanismName);

    private:
        std::unordered_multimap<std::string, Mechanism::Ptr> mMechanismHash;

    };
}


