/**
 *  @autor arssivka
 *  @date 8/25/16
 */

#pragma once

#include <chrono>
#include "NodeBase.h"
#include "Advertiser.h"
#include "Subscriber.h"

namespace rrc {
    class RootNode;
    typedef std::shared_ptr<RootNode> RootNodePtr;

    class Node : public NodeBase {
    public:
        Node();

        std::chrono::steady_clock::duration getMinDuration() const;

        void setMinDuration(const std::chrono::steady_clock::duration& minDuration);

        template <class T>
        inline Advertiser<T> createAdvertiser(const std::string& topicName) const {
            return Advertiser<T>(mRootNode, topicName);
        }

        template <class T>
        inline Subscriber<T> createSubscriber(const std::string& topicName) {
            return Subscriber<T>(mRootNode, topicName);
        }

    protected:
        Node(RootNodePtr rootNode);

        RootNodePtr getRootNode() const;

    private:
        RootNodePtr mRootNode;
        std::chrono::steady_clock::duration mMinDuration;
    };

    typedef std::shared_ptr<Node> NodePtr;
}


