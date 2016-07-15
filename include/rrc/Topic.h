/**
 *  @autor arssivka
 *  @date 7/13/16
 */

#pragma once


#include <google/protobuf/descriptor.h>
#include "TopicListener.h"

namespace {
    namespace pb = google::protobuf;
}

namespace rrc {
    class Topic {
        Topic(const pb::Descriptor& descriptor);

        bool checkDescriptor(const pb::Descriptor& descriptor);

        bool addListener(TopicListener* listener, const pb::Descriptor& descriptor);

        bool detachListener(TopicListener* listener);

    };
}