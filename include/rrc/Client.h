/**
 *  @autor arssivka
 *  @date 7/13/16
 */

#pragma once


#include "ID.h"
#include "Responce.h"
#include "Scheduler.h"

namespace rrc {
    template <class RequestType, class ResponceType>
    class Client {
    public:
        Client(const ID& id, const std::string& service, Scheduler& scheduler);


        bool isAutoReconnect() const {
            return mAutoReconnect;
        }


        void setAutoReconnect(bool autoReconnect) {
            mAutoReconnect = autoReconnect;
        }


        bool isConnected() const;

        bool reconnect();

        Responce<ResponceType> query(Message<RequestType>::Ptr request);

    private:
        bool mAutoReconnect;
    };
}


