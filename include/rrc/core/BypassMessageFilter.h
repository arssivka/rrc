/**
 * @author arssivka
 * @date 9/30/16
 */

#pragma once


#include "AbstractMessageFilter.h"

namespace rrc {
    class BypassMessageFilter : public AbstractMessageFilter {
    public:
        virtual bool accept(MessagePtr message) override;
    };
}


