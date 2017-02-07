/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#pragma once


#include "Node.h"
#include "AbstractQueueAdapter.h"
#include "TaskQueueAdapter.h"

namespace rrc {
    /**
     * @brief Abstract class for creating launchers. Lauуncher is needed to run all the nodes and functionality of the whole system.
     */
    class AbstractLauncher {
    public:
        /**
         * @brief Virtual destructor of Abstract Launcher
         */
        virtual ~AbstractLauncher() { }

        /**
         * @brief Virtual function for running the launcher
         * @return Status code of pragram state: 0 if succeed
         */
        virtual int run() = 0;

        /**
         * @brief Virtual function for running one step of launcher execution
         * @return True if succeed, otherwise false
         */
        virtual bool step() = 0;

        /**
         * @brief Stops the execution of launcher
         */
        virtual void stop() = 0;

        /**
         * @brief Registers node
         * @param node Pointer to node instance
         */
        virtual void addNode(std::shared_ptr<Node> node) = 0;

        /**
         * @brief Removes the node from the list
         * @param node Pointer to node instance
         */
        virtual void removeNode(std::shared_ptr<Node> node) = 0;

        // TODO: Docs and tests
        virtual void addSyncQueue(std::shared_ptr<TaskQueueAdapter> queue) = 0;

        virtual void removeSyncQueue(std::shared_ptr<TaskQueueAdapter> queue) = 0;
    };

}


