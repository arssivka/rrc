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
    class TopicListener {
    public:
        virtual void onMessage(Message<pb::Message>::Ptr msg) = 0;
    };
}