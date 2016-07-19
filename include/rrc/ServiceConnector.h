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
        ServiceConnector() = default;

        bool setServiceStuff(const ID& id, MessageStuff* stuff, bool directCallEnabled);

        bool detachServiceStuff(const MessageStuff* stuff);

        bool addClientStuff(const ID& id, MessageStuff* stuff);

        bool detachClient(const MessageStuff* stuff);

    private:

    };
}


