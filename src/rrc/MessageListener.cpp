/**
 *  @autor arssivka
 *  @date 7/25/16
 */

#include <rrc/MessageListener.h>


rrc::MessageListener::MessageListener(rrc::TypeId typeId)
        : mTypeId(typeId) { }


void rrc::MessageListener::enqueueMessage(rrc::Message::Ptr msg) {
    if (msg->getTypeId() == mTypeId) {
        mMessagesQueue.enqueue(std::move(msg));
    }
}


rrc::Message::Ptr rrc::MessageListener::tryDequeueMessage() {
    Message::Ptr message;
    if (mMessagesQueue.try_dequeue(message)) {
        return message;
    } else {
        return nullptr;
    }
}


rrc::TypeId rrc::MessageListener::getTypeId() const {
    return mTypeId;
}
