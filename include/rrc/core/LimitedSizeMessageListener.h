/**
 *  @autor arssivka
 *  @date 9/23/16
 */

#pragma once


#include "AbstractMessageListener.h"

namespace rrc {
    template <size_t Size>
    class LimitedSizeMessageListener : public AbstractMessageListener {
    public:
        LimitedSizeMessageListener(TypeId typeId)
                : AbstractMessageListener(typeId), mEmpty(true), mTailPosition(0), mHeadPosition(0) {
            static_assert(Size > 0, "Container with zero length isn't good idea.");
        }

        virtual void enqueueMessage(MessagePtr msg) override {
            if (this->getTypeId() != msg->getTypeId()) {
                return;
            }
            mMessagesContainer[mTailPosition] = std::move(msg);
            mTailPosition = (mTailPosition + 1) % Size;
            if (!mEmpty && mTailPosition == (mHeadPosition + 1) % Size) {
                mHeadPosition = (mHeadPosition + 1) % Size;
            }
            mEmpty = false;
        }

        virtual MessagePtr tryDequeueMessage() override {
            if (mEmpty) {
                return nullptr;
            }
            MessagePtr message = std::move(mMessagesContainer[mHeadPosition]);
            mHeadPosition = (mHeadPosition + 1) % Size;
            if (mHeadPosition == mTailPosition) {
                mEmpty = true;
            }
            return message;
        }

        static constexpr size_t getContainerSize() {
            return Size;
        }

    private:
        bool mEmpty;
        size_t mTailPosition;
        size_t mHeadPosition;
        MessagePtr mMessagesContainer[Size];
    };


    template <size_t Size>
    using LimitedSizeMessageListenerPtr = std::shared_ptr<LimitedSizeMessageListener<Size>>;
}


