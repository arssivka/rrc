/**
 *  @autor arssivka
 *  @date 8/26/16
 */

#pragma once


#include "AbstractLauncher.h"

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
        * @brief Sets the root node
        * @param node Pointer to root node instance
        */
        virtual void setRootNode(RootNodePtr node) override;

        /**
        * @brief Registers node
        * @param node Pointer to node instance
        */
        virtual void addNode(NodePtr node) override;

        /**
         * @brief Removes the node from the list
         * @param node Pointer to node instance
         */
        virtual void removeNode(NodePtr node) override;

    private:
        struct NodeContainer {
            NodeContainer(NodePtr node);

            NodePtr node;
            std::chrono::steady_clock::time_point timestamp;
        };

    private:
        bool mFinished;
        RootNodePtr mRootNode;
        std::forward_list<NodeContainer> mNodesList;
    };
}


