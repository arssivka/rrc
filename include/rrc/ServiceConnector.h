/**
 *  @autor arssivka
 *  @date 7/18/16
 */

#pragma once


#include "ID.h"
#include "MessageStuff.h"

namespace rrc {
    class ServiceConnector {
    public:
        ServiceConnector(const pb::Descriptor& paramDscr,
                         const pb::Descriptor& resultDscr);

        bool setServiceStuff(const ID& id, MessageStuff* stuff, bool directCallEnabled);

        bool detachServiceStuff(const MessageStuff* stuff);

        bool addClientStuff(const ID& id, MessageStuff* stuff);

        bool detachClientStuff(const MessageStuff* stuff);

    private:

    };
}


