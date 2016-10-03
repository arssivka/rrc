/**
 * @author arssivka
 * @date 9/30/16
 */

#pragma once


#include "AbstractMessageFilter.h"

namespace rrc {
    /**
     * @brief This message filter sets the callback to check the message
     */
    class CallbackMessageFilter : public AbstractMessageFilter {
    public:
        /**
         * @brief Constructor of CallbackMessageFilter
         * @param callback Const reference to callback function object for checking the message
         */
        CallbackMessageFilter(const std::function<bool(MessagePtr)>& callback);

        /**
         * @brief Constrcutor of CallbackMessageFilter
         * @param callback R-value refernce callback function object for checking the message
         */
        CallbackMessageFilter(std::function<bool(MessagePtr)>&& callback);

        /**
         * @brief Virtual method for checking the message validity
         * @param message Pointer to message that needs to be checked
         * @return True if message accpeted, otherwise false.
         */
        virtual bool accept(MessagePtr message) override;

    private:
        std::function<bool(MessagePtr)> mCallback;
    };
}


