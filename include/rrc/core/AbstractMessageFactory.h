/**
 *  @autor arssivka
 *  @date 9/5/16
 */

#pragma once


#include <google/protobuf/message_lite.h>
#include <memory>
#include "Pointer.h"

namespace {
    namespace pb = google::protobuf;
}

namespace rrc {
    class AbstractMessageFactory : public Pointer<AbstractMessageFactory> {
    public:
        /**
         * @brief Virtual function for creating the message
         * @return  Unique pointer to protobuf::MessageLite
         */
        virtual std::unique_ptr<pb::MessageLite> createMessage() = 0;

        /**
         * @brief Virtual destructor of Abstract Message Factory
         */
        virtual ~AbstractMessageFactory() { }

    };
}