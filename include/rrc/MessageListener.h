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
        virtual void onMessage(Message<pb::Message> msg) = 0;
    };
}