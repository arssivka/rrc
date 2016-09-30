/**
 * @author arssivka
 * @date 9/30/16
 */

#pragma once


#include "AbstractMessageFilter.h"

namespace rrc {
    class CallbackMessageFilter : public AbstractMessageFilter {
    public:
        CallbackMessageFilter(const std::function<bool(MessagePtr)>& callback);

        CallbackMessageFilter(std::function<bool(MessagePtr)>&& callback);

        virtual bool accept(MessagePtr message) override;

    private:
        std::function<bool(MessagePtr)> mCallback;
    };
}


