/**
 * @author arssivka
 * @date 9/30/16
 */

#pragma once


#include "AbstractMessageFilter.h"

namespace rrc {
    /**
     * @brief This message filter doesn't accept any message
     */
    class RejectMessageFilter : public AbstractMessageFilter {
    public:

        /**
         * @brief Virtual method for not accepting messages
         * @param message Pointer to message to not accept
         * @return False
         */
        virtual bool accept(Message::Ptr message) override;
    };
}


