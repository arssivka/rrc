/**
 * @author arssivka
 * @date 9/30/16
 */

#pragma once


#include "Message.h"

namespace rrc {
    class AbstractMessageFilter {
    public:
        virtual bool accept(MessagePtr message) = 0;

        virtual ~AbstractMessageFilter() { }

    };

    typedef std::shared_ptr<AbstractMessageFilter> AbstractMessageFilterPtr;
}


