/**
 *  @autor arssivka
 *  @date 7/18/16
 */

#pragma once


#include "ID.h"
#include "MessageStuff.h"
#include "NonCopyable.h"

namespace {
    namespace pb = google::protobuf;
}

namespace rrc {
    class ServiceConnector : private NonCopyable {
    public:
        ServiceConnector() = default;

        ServiceConnector(const pb::Descriptor& paramDscr,
                         const pb::Descriptor& resultDscr)
                : mParamDescr(&paramDscr), mResultDescr(&resultDscr) { }


        const pb::Descriptor& getParamDescriptor() const {
            return *mParamDescr;
        }


        void setParamDescriptor(const google::protobuf::Descriptor& paramDescr) {
            mParamDescr = &paramDescr;
        }


        const google::protobuf::Descriptor& getResultDescriptor() const {
            return *mResultDescr;
        }


        void setResultDescriptor(const pb::Descriptor& resultDescr) {
            mResultDescr = &resultDescr;
        }

        bool checkDescriptors(const pb::Descriptor& paramDscr,
                                    const pb::Descriptor& resultDscr) {
            // TODO type checking is probably good idea
            return true;
        }


        bool setServiceStuff(const ID& id, MessageStuff::SPtr stuff);

        bool detachServiceStuff(const MessageStuff::SPtr stuff);

        bool addClientStuff(const ID& id, MessageStuff::SPtr stuff);

        bool detachClientStuff(const MessageStuff::SPtr stuff);

    private:
        const pb::Descriptor* mParamDescr;
        const pb::Descriptor* mResultDescr;
    };
}


