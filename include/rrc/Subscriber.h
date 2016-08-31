/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#pragma once


#include "LauncherBase.h"
#include "Message.h"
#include "NonCopyable.h"
#include "MessageListener.h"
#include "TaskQueue.h"
#include "UnregisteredTypeException.h"
#include "ReceiveGuard.h"

namespace {
    namespace pb = google::protobuf;
}

namespace rrc {
    template <typename T>
    class Subscriber : private NonCopyable {
    public:
        Subscriber(RootNode::Ptr rootNode, const std::string& topicName) {
            TypeId typeId = rootNode->getTypeId<T>();
            if (typeId == MetaTable::UNKNOWN_TYPE_ID) {
                throw UnregisteredTypeException();
            }
            mConnected = false;
            mRootNode = rootNode;
            mTopicName = topicName;
            mListener = std::make_shared<MessageListener>(typeId);

            this->connect();
        }

        ~Subscriber() {
            this->disconnect();
        }

        ReceiveGuard<T> tryGetMessage() {
            return ReceiveGuard<T>(mListener->tryDequeueMessage());
        }

        void disconnect() const {
            if (mConnected) {
                mRootNode->removeListener(mTopicName, mListener);
            }
        }


        void connect() {
            if (!mConnected) {
                mRootNode->addListener(mTopicName, mListener);
            }
        }


    private:
        bool mConnected;
        RootNode::Ptr mRootNode;
        std::string mTopicName;
        MessageListener::Ptr mListener;
    };
}
