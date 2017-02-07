/**
 *  @autor arssivka
 *  @date 11/5/16
 */

#pragma once


#include "AbstractLauncher.h"

namespace rrc {
    class NodeMechanism {
    public:

        NodeMechanism(std::shared_ptr<TaskQueueAdapter> syncQueue, AbstractLauncher& launcher);


        /**
         * @brief Registers node for the synchronization
         * @param node Pointer to the node, that nees to be registered
         */
        void addNode(std::shared_ptr<Node> node);


        /**
         * @brief Unregisters node
         * @param node Pointer to the node that needs to be unregistered
         */
        void removeNode(std::shared_ptr<Node> node);


        /**
        * @brief Stops the node from execution
        */
        void stop();


    private:
        std::shared_ptr<TaskQueueAdapter> mSyncQueue;
        AbstractLauncher& mLauncher;
    };
}


