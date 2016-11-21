/**
 *  @autor arssivka
 *  @date 10/31/16
 */

#include <rrc/core/Engine.h>
#include <algorithm>


void rrc::Engine::addMechanism(rrc::Mechanism::Ptr mechanism) {
    auto found = mMechanismHash.find(mechanism->getName());
    if (found == mMechanismHash.end()) {
        mMechanismHash.insert({mechanism->getName(), std::move(mechanism)});
    }
}


void rrc::Engine::removeMechanism(rrc::Mechanism::Ptr mechanism) {
    auto found = mMechanismHash.find(mechanism->getName());
    if (found != mMechanismHash.end()) {
        mMechanismHash.erase(found);
    }
}


std::vector<rrc::Mechanism::Ptr> rrc::Engine::findMechanisms(const std::string& mechanismName) {
    auto found = mMechanismHash.equal_range(mechanismName);
    std::vector<rrc::Mechanism::Ptr> result;
    std::for_each(found.first, found.second, [&result](auto hashPair) {
        result.push_back(hashPair.second);
    });
    return result;
}
