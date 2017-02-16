/**
 *  @autor arssivka
 *  @date 8/24/16
 */

#include <rrc/core/Topic.h>


void rrc::Topic::addListener(std::shared_ptr<rrc::TaskHub<Buffer>> listener) {
    mListenersList.push_front(std::move(listener));
}


void rrc::Topic::removeListener(std::weak_ptr<rrc::TaskHub<Buffer>> listener) {
    auto lock = listener.lock();
    if (lock != nullptr) {
        mListenersList.remove(lock);
    }
}


void rrc::Topic::sendMessage(std::shared_ptr<Buffer> message) {
    for (auto it = mListenersList.begin(); it != mListenersList.end(); ++it) {
        auto& listener = *it;
        bool sent = listener->enqueueTask(message);
        if (!sent) {
            mListenersList.erase(it);
        }
    }
}


bool rrc::Topic::hasListeners() const {
    return !mListenersList.empty();
}


