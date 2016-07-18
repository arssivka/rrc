/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#pragma once


#include "ID.h"
#include "Message.h"
#include "Scheduler.h"

namespace rrc {
    template <typename MessageType>
    class Advertiser {
    public:
        Advertiser(const ID& moduleid, const std::string& topic, Scheduler& scheduler);

        bool isConnected() const;

        void send(Message<MessageType> msg, bool updateTimestamp = true);
    private:
    };
}


