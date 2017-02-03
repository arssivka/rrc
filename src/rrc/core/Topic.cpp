/**
 *  @autor arssivka
 *  @date 8/24/16
 */

#include <rrc/core/Topic.h>


void rrc::Topic::addListener(std::weak_ptr<rrc::MessageListener> listener) {
    mListenersList.push_front(std::move(listener));
}

void rrc::Topic::sendMessage(std::shared_ptr<Message> message) {
    for (auto it = mListenersList.begin(); it != mListenersList.end(); ++it) {
        auto listener = it->lock();
        bool sent = false;
        if (listener != nullptr) {
            sent = listener->sendMessage(message);
        }
        if (!sent) {
            mListenersList.erase(it);
        }
    }
}


bool rrc::Topic::hasListeners() const {
    return !mListenersList.empty();
}


