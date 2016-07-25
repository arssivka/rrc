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
            mCallback(mId, msg, mDirectCallEnabled);
        }

        void setDescriptor(const pb::Descriptor& descriptor) {
            mDescriptor = &descriptor;
        }

        const pb::Descriptor& getDescriptor() const {
            return *mDescriptor;
        }

        template <class Func>
        void setCallback(Func&& callback) {
            mCallback = std::forward(callback);
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
            return mDirectCallEnabled;
        }

        void setDirectCallEnabled(bool directCallEnabled) {
            mDirectCallEnabled = directCallEnabled;
        }


    private:
        void reset() {
            mCallback = [](Message<pb::Message> msg) { };
        }

    private:
        const pb::Descriptor* mDescriptor;
        bool mDirectCallEnabled;
        ID mId;
        std::function<void(ID, Message<pb::Message>, bool)> mCallback;
    };
}


