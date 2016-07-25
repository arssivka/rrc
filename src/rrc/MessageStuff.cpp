/**
 *  @autor arssivka
 *  @date 7/19/16
 */

#include <rrc/MessageStuff.h>


rrc::MessageStuff::MessageStuff() : mListener(nullptr), mSender(nullptr) { }


rrc::MessageStuff::MessageStuff(MessageListener::SPtr listener, MessageSender::SPtr sender)
        : mListener(listener), mSender(sender) { }


MessageListener::SPtr rrc::MessageStuff::getListener() const {
    return mListener;
}


void rrc::MessageStuff::setListener(MessageListener::SPtr listener) {
    mListener = listener;
}


MessageSender::SPtr rrc::MessageStuff::getSender() const {
    return mSender;
}


void rrc::MessageStuff::setSender(MessageSender::SPtr sender) {
    mSender = sender;
}


const pb::Descriptor& rrc::MessageStuff::getSenderDescriptor() const {
    return mSender->getDescriptor();
}


const pb::Descriptor& rrc::MessageStuff::getListenerDescriptor() const {
    return mListener->getDescriptor();
}