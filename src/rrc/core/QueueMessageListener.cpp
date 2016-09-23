/**
 *  @autor arssivka
 *  @date 7/25/16
 */

#include <rrc/core/QueueMessageListener.h>


rrc::QueueMessageListener::QueueMessageListener(rrc::TypeId typeId)
        : AbstractMessageListener(typeId) {  }


void rrc::QueueMessageListener::enqueueMessage(rrc::MessagePtr msg) {
    if (msg->getTypeId() == this->getTypeId()) {
        mMessagesQueue.emplace(std::move(msg));
    }
}


rrc::MessagePtr rrc::QueueMessageListener::tryDequeueMessage() {
    MessagePtr message;
    if (!mMessagesQueue.empty()) {
        message = std::move(mMessagesQueue.front());
        mMessagesQueue.pop();
        return message;
    } else {
        return nullptr;
    }
}


