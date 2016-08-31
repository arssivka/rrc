/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#pragma once


#include "RootNode.h"
#include "Node.h"

namespace rrc {
    class LauncherBase {
    public:
        virtual ~LauncherBase() { }

        virtual int run() = 0;

        virtual void stop() = 0;

        virtual void setRootNode(RootNode::Ptr node) = 0;

        virtual void addNode(Node::Ptr node) = 0;

        virtual void removeNode(Node::Ptr node) = 0;
    };

    typedef LauncherBase Launcher;
}


