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

        /**
         * @brief Constructot of Message Sender
         * @param rootNode Pointer to root node
         * @param topicName Name of the topic to connect
         */
        MessageSender(RootNodePtr rootNode, const std::string& topicName);

        /**
         * @brief Sends the message to topic
         * @param message Pointer to messages
         */
        void sendMessage(MessagePtr message);

        /**
         * @brief Returns topic name
         * @return Topic name of typr std::string
         */
        const std::string& getTopicName() const;

        /**
         * @brief Sets the name of the topic to connect
         * @param topicName
         */
        void setTopicName(const std::string& topicName);

        /**
         * @brief Returns pointer to the root node instance
         * @return
         */
        RootNodePtr getRootNode() const;

        /**
         * @brief Sets the root node
         * @param rootNode Pointer to the root node instance
         */
        void setRootNode(RootNodePtr rootNode);


    private:
        RootNodePtr mRootNode;
        std::string mTopicName;
    };
}


