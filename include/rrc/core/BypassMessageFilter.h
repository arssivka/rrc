/**
 * @author arssivka
 * @date 9/30/16
 */

#pragma once


#include "AbstractMessageFilter.h"

namespace rrc {
    /**
     * @brief Message filter that accepts all messages
     */
    class BypassMessageFilter : public AbstractMessageFilter {
    public:
        /**
         * @brief Virtual method for accepting the message
         * @param message Pointer to message to accept
         * @return True
         */
        virtual bool accept(Message::Ptr message) override;
    };
}


