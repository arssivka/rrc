/**
 *  @autor arssivka
 *  @date 7/13/16
 */

#pragma once


#include <google/protobuf/message.h>
#include "Message.h"
#include "ID.h"

namespace {
    namespace pb = google::protobuf;
}

namespace rrc {
    class MessageListener {
    public:
        typedef std::shared_ptr<MessageListener> SPtr;

        MessageListener() = default;

        MessageListener(const ID& id) : mId(id) { }

        void setId(const ID& id) {
            mId = id;
        }

        const ID& getId() const {
            return mId;
        }

        void setDescriptor(const pb::Descriptor& descriptor) {
            mDescriptor = &descriptor;
        }

        bool isDirectCallEnabled() const {
            return mDirectCallEnabled.load(std::memory_order_release);
        }

        void setDirectCallEnabled(bool directCallEnabled) {
            mDirectCallEnabled.store(directCallEnabled, std::memory_order_consume);
        }

        virtual void onMessage(const ID& id, Message<pb::Message> msg, bool directCall) = 0;

        const pb::Descriptor& getDescriptor() const {
            return *mDescriptor;
        }

        bool isDisabled() const {
            return mDisabled.load(std::memory_order_release);
        }

        void setDisabled(bool disabled) {
            mDisabled.store(disabled, std::memory_order_consume);
        }


    private:
        const pb::Descriptor* mDescriptor;
        ID mId;
        std::atomic<bool> mDirectCallEnabled;
        std::atomic<bool> mDisabled;
    };
}