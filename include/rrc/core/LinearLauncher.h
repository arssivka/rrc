/**
 *  @autor arssivka
 *  @date 8/26/16
 */

#pragma once


#include <forward_list>
#include "AbstractLauncher.h"
#include "Node.h"

namespace rrc {
    /**
     * @brief This launcher implimentation uses only one thread to run all the nodes.
     */
    class LinearLauncher : public AbstractLauncher {
    public:
        /**
         * @brief Default constructor of Linear Launcher
         */
        LinearLauncher();

        /**
         * @brief Linear Launcher destructor
         */
        virtual ~LinearLauncher() override;

        /**
        * @brief Virtual function for running the launcher
        * @return Status code of pragram state: 0 if succeed
        */
        virtual int run() override;

        /**
        * @brief Virtual function for running one step of launcher execution
        * @return True if succeed, otherwise false
        */
        virtual bool step() override;

        /**
         * @brief Stops the execution of launcher
         */
        virtual void stop() override;

        /**
        * @brief Registers node
        * @param node Pointer to node instance
        */
        virtual void addNode(std::shared_ptr<Node> node) override;

        /**
         * @brief Removes the node from the list
         * @param node Pointer to node instance
         */
        virtual void removeNode(std::shared_ptr<Node> node) override;

        virtual void addSyncQueue(std::shared_ptr<AbstractTaskQueueAdapter> queue) override;

        virtual void removeSyncQueue(std::shared_ptr<AbstractTaskQueueAdapter> queue) override;

    private:
        bool mFinished;
        std::forward_list<std::shared_ptr<Node>> mNodesList;
        std::forward_list<std::shared_ptr<AbstractTaskQueueAdapter>> mQueuesList;
    };
}


