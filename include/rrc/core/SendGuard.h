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

        /**
         * @brief Constructor of Send Guard
         * @param rootNode Pointer to Root Node
         * @param topicName Name of the topic to gaurd message for
         * @param typeId Id of type of the message. Default value is UNKNOWN_TYPE_ID and there will be try to set automatically
         */
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

        /**
         * @brief Move constructor of Send Guard
         * @param other Reference to instance of Send Guard to move data from
         */
        SendGuard(SendGuard&& other)
                : mTopicName(std::move(other.mTopicName)),
                  mRootNode(std::move(other.mRootNode)),
                  mTimestamp(other.mTimestamp),
                  mTypeId(other.mTypeId),
                  mData(std::move(other.mData)) { }

        /**
         * @brief Sends message
         * @return True if succeceed, otherwise false
         */
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

        /**
         * @brief Operator -> override
         * @return Const pointer to message
         */
        const T* operator->() const {
            return mData.get();
        }

        /**
         * @brief Operator -> override
         * @return Pointer to message
         */
        T* operator->() {
            return mData.get();
        }

        /**
         * @brief Checks if message already sent
         * @return True if sent otherwise false
         */
        bool isSent() const noexcept {
            return mData == nullptr;
        }

        /**
         * @brief Returns timestamp of the message
         * @return Timestamp of type std::chrono::steady_clock::time_point
         */
        const std::chrono::steady_clock::time_point& getTimestamp() const {
            return mTimestamp;
        }

        /**
         * @brief Sets the timestamp of the message
         * @param timePoint Desired time point of type std::chrono::steady_clock::time_point
         */
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


