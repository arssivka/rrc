/**
 *  @autor arssivka
 *  @date 7/18/16
 */

#pragma once


#include <google/protobuf/message.h>
#include "Message.h"
#include "ID.h"

namespace {
    namespace pb = google::protobuf;
}

namespace rrc {
    class MessageSender {
    public:
        typedef std::shared_ptr<MessageSender> SPtr;

        MessageSender(ID id) : mId(id) {
            this->reset();
        }

        bool send(Message<pb::Message> msg) {
            return mCallback(mId, msg, mDirectCallEnabled);
        }

        void setDescriptor(const pb::Descriptor& descriptor) {
            mDescriptor = &descriptor;
        }

        const pb::Descriptor& getDescriptor() const {
            return *mDescriptor;
        }

        template <class Func>
        void setCallback(Func&& callback) {
            mCallback = std::forward<Func>(callback);
        }

        void disconnect() {
            this->reset();
        }

        const ID& getId() const {
            return mId;
        }

        void setId(const ID& id) {
            mId = id;
        }

        bool isDirectCallEnabled() const {
            return mDirectCallEnabled.load(std::memory_order_consume);
        }

        void setDirectCallEnabled(bool directCallEnabled) {
            mDirectCallEnabled.store(directCallEnabled, std::memory_order_release);
        }

        bool isDisabled() const {
            return mDisabled.load(std::memory_order_consume);
        }

        void setDisabled(bool disabled) {
            mDisabled.store(mDisabled, std::memory_order_release);
        }

    private:
        void reset();

    private:
        const pb::Descriptor* mDescriptor;
        std::atomic<bool> mDirectCallEnabled;
        std::atomic<bool> mDisabled;
        ID mId;
        std::function<bool(ID, Message<pb::Message>, bool)> mCallback;
    };
}


