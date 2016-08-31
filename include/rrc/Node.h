/**
 *  @autor arssivka
 *  @date 8/25/16
 */

#pragma once

#include <chrono>
#include "RootNode.h"

namespace rrc {
    class Node : public NodeBase {
    public:
        typedef std::shared_ptr<Node> Ptr;

    public:
        std::chrono::steady_clock::duration getMinDuration() const;

        void setMinDuration(const std::chrono::steady_clock::duration& minDuration);

    protected:
        Node(RootNode::Ptr rootNode);

        RootNode::Ptr getRootNode() const;

    private:
        RootNode::Ptr mRootNode;
        std::chrono::steady_clock::duration mMinDuration;
    };
}


