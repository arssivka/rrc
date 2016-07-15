/**
 *  @autor arssivka
 *  @date 7/13/16
 */

#pragma once


#include "ID.h"
#include "Message.h"
#include "NonCopyable.h"
#include "Scheduler.h"

namespace rrc {
    template <class Request, class Responce>
    class Service : private NonCopyable {
        typedef Request Request;
        typedef Responce Responce;

        Service(const ID& id, const std::string& name, Scheduler& scheduler);

        template <class Func>
        void setCallback(Func&& callback);

        Responce<Responce> call(Message<Request>::Ptr data);
    };
}


