/**
 *  @autor arssivka
 *  @date 8/29/16
 */

#pragma once


#include "Message.h"
#include "RootNode.h"
#include "UnregisteredTypeException.h"

namespace rrc {
    template <class T>
    class SendGuard : private NonCopyable {
    public:
        SendGuard(RootNodePtr rootNode, const std::string& topicName, TypeId typeId = MetaTable::UNKNOWN_TYPE_ID)
                : mTopicName(topicName), mRootNode(rootNode) {
            mTypeId = (typeId == MetaTable::UNKNOWN_TYPE_ID)
                      ? mRootNode->getTypeId<T>()
                      : typeId;
            if (mTypeId == MetaTable::UNKNOWN_TYPE_ID) {
                throw rrc::UnregisteredTypeException();
            }
            mData.reset(new T);
        }

        SendGuard(SendGuard&& other)
                : mTopicName(std::move(other.mTopicName)),
                  mRootNode(std::move(other.mRootNode)),
                  mTimestamp(other.mTimestamp),
                  mTypeId(other.mTypeId),
                  mData(std::move(other.mData)) { }

        bool send() {
            if (this->isSent()) {
                return false;
            }
            // Set current time if timestamp wasn't set
            auto timestamp = mTimestamp;
            if (timestamp == std::chrono::steady_clock::time_point()) {
                timestamp = std::chrono::steady_clock::now();
            }
            MessagePtr message = std::make_shared<Message>(mTypeId, timestamp, std::move(mData));
            mRootNode->sendMessage(mTopicName, std::move(message));
            return true;
        }

        const T* operator->() const {
            return mData.get();
        }

        T* operator->() {
            return mData.get();
        }

        bool isSent() const noexcept {
            return mData == nullptr;
        }

        const std::chrono::steady_clock::time_point& getTimestamp() const {
            return mTimestamp;
        }


        void setTimestamp(const std::chrono::steady_clock::time_point& timePoint) {
            mTimestamp = timePoint;
        }


    private:
        std::string mTopicName;
        RootNodePtr mRootNode;
        std::chrono::steady_clock::time_point mTimestamp;
        TypeId mTypeId;
        std::unique_ptr<T> mData;
    };
}


