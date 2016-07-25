/**
 *  @autor arssivka
 *  @date 7/13/16
 */

#pragma once


#include "ID.h"
#include "Message.h"
#include "NonCopyable.h"
#include "Scheduler.h"
#include "Response.h"

namespace rrc {
    template <class Req, class Res>
    class Service : private NonCopyable {
        typedef Req Request;
        typedef Res Response;

        Service(const ID& id, const std::string& name, Scheduler& scheduler);

        template <class Func>
        void setCallback(Func&& callback);

        rrc::Response<Response> call(Message<Request> data);
    };
}


