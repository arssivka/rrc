/**
 *  @autor arssivka
 *  @date 7/13/16
 */

#pragma once


#include <google/protobuf/message.h>
#include "Message.h"

namespace {
    namespace pb = google::protobuf;
}

namespace rrc {
    class MessageListener {
    public:
        typedef std::shared_ptr<MessageListener> SPtr;

        void setId(const ID& id) {
            mId = id;
        }

        const ID& getId() const {
            return mId;
        }

        void setDescriptor(const google::protobuf::Descriptor& descriptor) {
            mDescriptor = &descriptor;
        }

        bool isDirectCallEnabled() const {
            return mDirectCallEnabled;
        }

        void setDirectCallEnabled(bool directCallEnabled) {
            mDirectCallEnabled = directCallEnabled;
        }

        virtual void onMessage(const ID& id, Message<pb::Message> msg, bool directCall) = 0;

        const pb::Descriptor& getDescriptor() const {
            return *mDescriptor;
        }

    private:
        const pb::Descriptor* mDescriptor;
        ID mId;
        bool mDirectCallEnabled;
    };
}