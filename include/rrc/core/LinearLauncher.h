/**
 *  @autor arssivka
 *  @date 8/26/16
 */

#pragma once


#include <forward_list>
#include "AbstractLauncher.h"
#include "AbstractNode.h"

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
        virtual void addNode(AbstractNode::Ptr node) override;

        /**
         * @brief Removes the node from the list
         * @param node Pointer to node instance
         */
        virtual void removeNode(AbstractNode::Ptr node) override;

        virtual void addSyncQueue(TaskQueueWrapper queue) override;

        virtual void removeSyncQueue(TaskQueueWrapper queue) override;

    private:
        bool mFinished;
        std::forward_list<AbstractNode::Ptr> mNodesList;
        std::forward_list<TaskQueueWrapper> mQueuesList;
    };
}


