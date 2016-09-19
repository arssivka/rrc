/**
 *  @autor arssivka
 *  @date 8/25/16
 */

#pragma once

#include <chrono>
#include "AbstractNode.h"
#include "Advertiser.h"
#include "Subscriber.h"

namespace rrc {
    class RootNode;
    typedef std::shared_ptr<RootNode> RootNodePtr;

    class Node : public AbstractNode {
    public:
        /**
         * @brief Default contructor of node
         */
        Node();

        /**
         * @brief Returns duration of the node - recomendation for launcher how often run this node
         * @return Duration of type steady_clock::duration
         */
        std::chrono::steady_clock::duration getMinDuration() const;

        /**
         * Sets duration of the node - recomendation for launcher how often run this node
         * @param minDuration Desired duration of type steady_clock::duration
         */
        void setMinDuration(const std::chrono::steady_clock::duration& minDuration);

        /**
         * @brief Creates advertiser with parameter T
         * @param topicName name of the topic to advrtise
         * @return Advertiser with parameter = T
         */
        template <class T>
        inline Advertiser<T> createAdvertiser(const std::string& topicName) const {
            return Advertiser<T>(mRootNode, topicName);
        }

        /**
         * @brief Creates subscriber with parameter T
         * @param topicName Name of the to subscibe
         * @return Subscriber with parameter = T
         */
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


