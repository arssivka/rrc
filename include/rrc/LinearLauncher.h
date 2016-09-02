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

        virtual bool step() override;

        virtual void stop() override;

        virtual void setRootNode(RootNodePtr node) override;

        virtual void addNode(NodePtr node) override;

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


