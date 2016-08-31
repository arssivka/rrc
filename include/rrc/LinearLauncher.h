/**
 *  @autor arssivka
 *  @date 8/26/16
 */

#pragma once


#include "LauncherBase.h"

namespace rrc {
    class LinearLauncher : public LauncherBase {
    public:
        LinearLauncher();

        virtual ~LinearLauncher() override;

        virtual int run() override;

        virtual void stop() override;

        virtual void setRootNode(RootNode::Ptr node) override;

        virtual void addNode(Node::Ptr node) override;

        virtual void removeNode(Node::Ptr node) override;

    private:
        struct NodeContainer {
            NodeContainer(Node::Ptr node);

            Node::Ptr node;
            std::chrono::steady_clock::time_point timestamp;
        };

    private:
        bool mFinished;
        RootNode::Ptr mRootNode;
        std::forward_list<NodeContainer> mNodesList;
    };
}


