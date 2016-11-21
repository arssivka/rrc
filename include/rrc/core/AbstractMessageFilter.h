/**
 * @author arssivka
 * @date 9/30/16
 */

#pragma once


#include "Message.h"

namespace rrc {
    /**
     * @brief Abstract class for creating the message filters which will accept or deny certain messages
     */
    class AbstractMessageFilter : public Pointer<AbstractMessageFilter> {
    public:
        /**
         * @brief Virtual method for checking the message validity
         * @param message Pointer to message that needs to be checked
         * @return True if message accpeted, otherwise false.
         */
        virtual bool accept(Message::Ptr message) = 0;

        /**
         * @brief Virtual destruuctor of message filter
         */
        virtual ~AbstractMessageFilter() { }

    };
}


