/**
 *  @autor arssivka
 *  @date 7/13/16
 */

#pragma once


#include <google/protobuf/descriptor.h>
#include "TopicListener.h"

namespace rrc {
    class Topic {
        Topic(const google::protobuf::Descriptor& descriptor);

        bool checkDescriptor(const google::protobuf::Descriptor& descriptor);

        bool addListener(TopicListener* listener, const google::protobuf::Descriptor& descriptor);

        bool detachListener(TopicListener* listener);

    };
}