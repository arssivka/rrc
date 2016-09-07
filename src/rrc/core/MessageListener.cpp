/**
 *  @autor arssivka
 *  @date 7/25/16
 */

#include <rrc/core/MessageListener.h>


rrc::MessageListener::MessageListener(rrc::TypeId typeId)
        : mTypeId(typeId) { }


void rrc::MessageListener::enqueueMessage(rrc::MessagePtr msg) {
    if (msg->getTypeId() == mTypeId) {
        mMessagesQueue.enqueue(std::move(msg));
    }
}


rrc::MessagePtr rrc::MessageListener::tryDequeueMessage() {
    MessagePtr message;
    if (mMessagesQueue.try_dequeue(message)) {
        return message;
    } else {
        return nullptr;
    }
}


rrc::TypeId rrc::MessageListener::getTypeId() const {
    return mTypeId;
}
