/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#pragma once


#include <memory>
#include "NonCopyable.h"
#include "EngineWrapper.h"

namespace rrc {
    /**
     * @brief Abstract class for creating nodes - modules of the system. Each module holds it's own functioanlity.
     * In the terms of the system, node - is atomic. Executaion of it's entry is guaranteed.
     */
    class Node : public Pointer<Node>, private NonCopyable {
    public:
        /**
         * @brief Virtual function for ruuning the node functionality
         */
        virtual void entry() = 0;

        /**
         * @brief Virtual destructor of AbstractNode
         */
        virtual ~Node();


    protected:
        Node(EngineWrapper engineWrapper);

        EngineWrapper getEngineWrapper() const;

    private:
        EngineWrapper mEngineWrapper;
    };
}


