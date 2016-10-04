/**
 * @author arssivka
 * @date 9/30/16
 */

#include "include/rrc/core/CallbackMessageFilter.h"


rrc::CallbackMessageFilter::CallbackMessageFilter(const std::function<bool(MessagePtr)>& callback)
        : mCallback(callback) {}


rrc::CallbackMessageFilter::CallbackMessageFilter(std::function<bool(MessagePtr)>&& callback)
        : mCallback(std::move(callback)) { }


bool rrc::CallbackMessageFilter::accept(rrc::MessagePtr message) {
    return mCallback(message);
}
