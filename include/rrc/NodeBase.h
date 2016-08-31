/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#pragma once


#include <memory>
#include "NonCopyable.h"

namespace rrc {
    class NodeBase : private NonCopyable {
    public:
        virtual void entry() = 0;

    };

    typedef std::shared_ptr<NodeBase> NodeBasePtr;
}


