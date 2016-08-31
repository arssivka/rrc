/**
 *  @autor arssivka
 *  @date 8/24/16
 */

#include "include/rrc/Topic.h"


rrc::Topic::Topic(TypeId tid)
        : mTypeId(tid) { }


bool rrc::Topic::addListener(rrc::MessageListener::Ptr listener) {
    if (!this->checkCapability(listener->getTypeId())) {
        return false;
    } else {
        mListenersList.push_front(std::move(listener));
        return true;
    }
}


void rrc::Topic::removeListener(rrc::MessageListener::Ptr listener) {
    mListenersList.remove(listener);
}


void rrc::Topic::sendMessage(Message::Ptr message) {
    for (auto&& listener : mListenersList) {
        listener->enqueueMessage(message);
    }
}


rrc::TypeId rrc::Topic::getTypeId() const noexcept {
    return mTypeId;
}


bool rrc::Topic::checkCapability(TypeId typeId) const noexcept {
    return mTypeId == typeId;
}


bool rrc::Topic::empty() const {
    return mListenersList.empty();
}
