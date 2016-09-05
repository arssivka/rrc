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

        MessageSender(RootNodePtr rootNode, const std::string& topicName);

        void sendMessage(MessagePtr message);


        const std::string& getTopicName() const;


        void setTopicName(const std::string& topicName);


        RootNodePtr getRootNode() const;


        void setRootNode(RootNodePtr rootNode);


    private:
        RootNodePtr mRootNode;
        std::string mTopicName;
    };
}


