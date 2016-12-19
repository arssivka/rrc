/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#pragma once


#include "NonCopyable.h"
#include "Pointer.h"

namespace rrc {
    /**
     * @brief Abstract class for creating nodes - modules of the system. Each module holds it's own functioanlity.
     * In the terms of the system, node - is atomic. Executaion of it's entry is guaranteed.
     */
    class AbstractNode : public Pointer<AbstractNode>, private NonCopyable {
    public:
        /**
         * @brief Virtual function for ruuning the node functionality
         */
        virtual void entry() = 0;

        /**
         * @brief Virtual destructor of AbstractNode
         */
        virtual ~AbstractNode();
    };
}


