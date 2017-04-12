/**
 *  @autor arssivka
 *  @date 4/11/17
 */

#include "rrc/topic.h"
#include "rrc/receiver.h"
#include "rrc/sender.h"


void rrc::topic::add_sender(rrc::sender* sender_ptr) {
    m_senders.push_front(sender_ptr);
}


void rrc::topic::add_receiver(rrc::receiver* receiver_ptr) {
    m_receivers.push_front(receiver_ptr);
}


void rrc::topic::reset() {
    m_senders.clear();
    m_receivers.clear();
}


void rrc::topic::connect() {
    if (!m_senders.empty() && !m_receivers.empty()) {
        for (auto&& sender_ptr : m_senders) {
            for (auto&& receiver_ptr : m_receivers) {
                if (!sender_ptr->has_receiver(receiver_ptr)) {
                    sender_ptr->add_receiver(receiver_ptr);
                }
            }
        }
    }

    m_senders.clear();
    m_receivers.clear();
}
