/**
 *  @autor arssivka
 *  @date 11/5/16
 */

#pragma once


#include "Mechanism.h"
#include "AbstractLauncher.h"

namespace rrc {
    class NodeMechanism : public Mechanism {
    public:

        NodeMechanism(TaskQueueWrapper syncQueue, AbstractLauncher::Ptr launcher);


        /**
         * @brief Registers node for the synchronization
         * @param node Pointer to the node, that nees to be registered
         */
        void addNode(Node::Ptr node);


        /**
         * @brief Unregisters node
         * @param node Pointer to the node that needs to be unregistered
         */
        void removeNode(Node::Ptr node);


        /**
        * @brief Stops the node from execution
        */
        void stop();


    private:
        TaskQueueWrapper mSyncQueue;
        AbstractLauncher::Ptr mLauncher;
    };
}


