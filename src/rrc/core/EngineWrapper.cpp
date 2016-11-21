/**
 *  @autor arssivka
 *  @date 11/2/16
 */

#include <rrc/core/EngineWrapper.h>

rrc::EngineWrapper::EngineWrapper(rrc::Engine::Ptr engine)
        : mEngine(std::move(engine)) {}


auto rrc::EngineWrapper::findMechanisms(const std::string& mechanismName) const {
    return mEngine->findMechanisms(mechanismName);
}

