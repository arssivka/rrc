/**
 *  @autor arssivka
 *  @date 7/13/16
 */

#pragma once


#include <google/protobuf/message.h>
#include "Message.h"

namespace rrc {
    class TopicListener {
    public:
        virtual void onMessage(Message<google::protobuf::Message>::Ptr msg) = 0;
    };
}