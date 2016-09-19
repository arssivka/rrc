/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#pragma once


#include <memory>
#include "NonCopyable.h"

namespace rrc {
    class AbstractNode : private NonCopyable {
    public:
        /**
         * @brief Virtual function for ruuning the node functionality
         */
        virtual void entry() = 0;

    };

    typedef std::shared_ptr<AbstractNode> AbstractNodePtr;
}


