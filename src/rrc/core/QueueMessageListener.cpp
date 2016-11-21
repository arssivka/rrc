/**
 *  @autor arssivka
 *  @date 7/25/16
 */

#include <rrc/core/QueueMessageListener.h>


rrc::QueueMessageListener::QueueMessageListener(rrc::TypeId typeId)
        : AbstractMessageListener(typeId) {  }


void rrc::QueueMessageListener::enqueueMessage(rrc::Message::Ptr msg) {
    if (msg->getTypeId() == this->getTypeId()) {
        mMessagesQueue.emplace(std::move(msg));
    }
}


rrc::Message::Ptr rrc::QueueMessageListener::tryDequeueMessage() {
    Message::Ptr message;
    if (!mMessagesQueue.empty()) {
        message = std::move(mMessagesQueue.front());
        mMessagesQueue.pop();
        return message;
    } else {
        return nullptr;
    }
}


