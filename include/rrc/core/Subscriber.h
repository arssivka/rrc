/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#pragma once


#include "AbstractLauncher.h"
#include "Message.h"
#include "NonCopyable.h"
#include "QueueMessageListener.h"
#include "TaskQueueWrapper.h"
#include "UnregisteredTypeException.h"
#include "ReceiveGuard.h"
#include "QueueMessageListener.h"
#include "LimitedSizeMessageListener.h"

namespace {
    namespace pb = google::protobuf;
}

namespace rrc {
    /**
     * @brief This class allows to subsribe to topic and get messages from it.
     */
    template <typename MessageType, typename ListenerType>
    class Subscriber : private NonCopyable {
    public:

        /**
         * @brief Constructor of subscriber
         * @param rootNode Pointer to root node
         * @param topicName Name of the topic to subscribe
         */
        Subscriber(RootNodePtr rootNode, const std::string& topicName) {
            static_assert(std::is_base_of<AbstractMessageListener, ListenerType>::value,
                          "ListenerType template parameter must be derived from rrc::AbstractMessageListener");
            TypeId typeId = rootNode->getTypeId<MessageType>();
            if (typeId == MetaTable::UNKNOWN_TYPE_ID) {
                throw UnregisteredTypeException();
            }
            mConnected = false;
            mRootNode = rootNode;
            mTopicName = topicName;
            mListener = std::make_shared<ListenerType>(typeId);

            this->connect();
        }

        /**
         * @brief Move constructor for Subscriber
         * @param other Reference to instance of Sunscriber to move from
         */
        Subscriber(Subscriber&& other)
                : mConnected(std::move(other.mConnected)), mRootNode(std::move(other.mRootNode)),
                  mTopicName(std::move(other.mTopicName)), mListener(std::move(other.mListener)) { }

        ~Subscriber() {
            this->disconnect();
        }

        /**
         * @brief Trys to get message
         * @return Recieve Guard with message of type T
         */
        ReceiveGuard<MessageType> tryGetMessage() {
            return ReceiveGuard<MessageType>(mListener->tryDequeueMessage());
        }

        // TODO Getter with bool result
        /**
         * @brief Removes listener of this subscriber from the root node
         */
        void disconnect() const {
            if (mConnected) {
                mRootNode->removeListener(mTopicName, mListener);
            }
        }


        /**
         * @brief Adds listener of this subscriber to the root node
         */
        void connect() {
            if (!mConnected) {
                mRootNode->addListener(mTopicName, mListener);
            }
        }


    private:
        bool mConnected;
        RootNodePtr mRootNode;
        std::string mTopicName;
        AbstractMessageListenerPtr mListener;
    };

    // TODO Comment it
    template <class MessageType>
    using QueueSubscriber = Subscriber<MessageType, QueueMessageListener>;

    template <class MessageType, size_t Size>
    using LimitedSizeSubscriber = Subscriber<MessageType, LimitedSizeMessageListener<Size>>;
}
