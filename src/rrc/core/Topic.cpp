/**
 *  @autor arssivka
 *  @date 8/24/16
 */

#include <rrc/core/Topic.h>
#include <rrc/core/BypassMessageFilter.h>


rrc::Topic::Topic()
        : mMessageFilter(std::make_shared<BypassMessageFilter>()), mAutoRemoveEnabled(true),
          mMessageFilterEnabled(true) { }


void rrc::Topic::addListener(rrc::AbstractMessageListener::Ptr listener) {
    mListenersList.push_front(std::move(listener));
}


void rrc::Topic::removeListener(rrc::AbstractMessageListener::Ptr listener) {
    mListenersList.remove(listener);
}


void rrc::Topic::sendMessage(Message::Ptr message) {
    if (mMessageFilter->accept(message)) {
        for (auto&& listener : mListenersList) {
            listener->enqueueMessage(message);
        }
    }
}


bool rrc::Topic::hasListeners() const {
    return !mListenersList.empty();
}


bool rrc::Topic::isAutoRemoveEnabled() const {
    return mAutoRemoveEnabled;
}


void rrc::Topic::setAutoRemoveEnabled(bool autoRemoveEnabled) {
    mAutoRemoveEnabled = autoRemoveEnabled;
}


bool rrc::Topic::isMessageFilterEnabled() const {
    return mMessageFilterEnabled;
}


void rrc::Topic::setMessageFilterEnabled(bool filterEnabled) {
    mMessageFilterEnabled = filterEnabled;
}


rrc::AbstractMessageFilter::Ptr rrc::Topic::getMessageFilter() const {
    return mMessageFilter;
}


void rrc::Topic::setMessageFilter(AbstractMessageFilter::Ptr messageFilter) {
    mMessageFilter = messageFilter;
}
