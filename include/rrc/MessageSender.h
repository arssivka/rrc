/**
 *  @autor arssivka
 *  @date 7/18/16
 */

#pragma once


#include <google/protobuf/message.h>
#include "Message.h"
#include "RootNode.h"

namespace {
    namespace pb = google::protobuf;
}

namespace rrc {
    class MessageSender {
    public:
        typedef std::shared_ptr<MessageSender> Ptr;

        MessageSender(RootNode::Ptr rootNode, const std::string& topicName);

        void sendMessage(Message::Ptr message);


        const std::string& getTopicName() const;


        void setTopicName(const std::string& topicName);


        RootNode::Ptr getRootNode() const;


        void setRootNode(RootNode::Ptr rootNode);


    private:
        RootNode::Ptr mRootNode;
        std::string mTopicName;
    };
}


