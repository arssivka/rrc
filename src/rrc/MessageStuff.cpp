/**
 *  @autor arssivka
 *  @date 7/19/16
 */

#include <rrc/MessageStuff.h>


rrc::MessageStuff::MessageStuff() : mListener(nullptr), mSender(nullptr) { }


rrc::MessageStuff::MessageStuff(MessageListener* listener, MessageSender* sender)
        : mListener(listener), mSender(sender) { }


MessageListener* rrc::MessageStuff::getListener() const {
    return mListener;
}


void rrc::MessageStuff::setListener(MessageListener* listener) {
    mListener = listener;
}


MessageSender* rrc::MessageStuff::getSender() const {
    return mSender;
}


void rrc::MessageStuff::setSender(MessageSender* sender) {
    mSender = sender;
}