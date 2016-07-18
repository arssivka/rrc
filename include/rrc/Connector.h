/**
 *  @autor arssivka
 *  @date 7/13/16
 */

#pragma once


#include <google/protobuf/descriptor.h>
#include "MessageListener.h"

namespace {
    namespace pb = google::protobuf;
}

namespace rrc {
    class Connector {
        Connector(const pb::Descriptor& descriptor);

        bool checkDescriptor(const pb::Descriptor& descriptor);

        bool addListener(MessageListener* listener, const pb::Descriptor& descriptor);

        bool detachListener(MessageListener* listener);

    };
}