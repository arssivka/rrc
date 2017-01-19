/**
 *  @autor arssivka
 *  @date 11/2/16
 */

#pragma once


#include <type_traits>
#include "include/rrc/meta.h"
#include "Engine.h"

namespace rrc {
    class EngineWrapper : public Pointer<EngineWrapper> {
    public:
        EngineWrapper(Engine::Ptr engine);

        auto findMechanisms(const std::string& mechanismName) const;


    private:
        Engine::Ptr mEngine;

    };
}