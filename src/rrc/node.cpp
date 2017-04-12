/**
 *  @autor arssivka
 *  @date 4/8/17
 */

#include "rrc/node.h"
#include "rrc/sender.h"


void rrc::node::add_sender(const std::string& key, rrc::sender* sender_ptr) {
    m_senders_hash.emplace(std::make_pair(key, sender_ptr));
}


void rrc::node::add_receiver(const std::string& key, rrc::receiver* receiver_ptr) {
    m_receivers_hash.insert(std::make_pair(key, receiver_ptr));
}


rrc::sender* rrc::node::find_sender(const std::string& key) const noexcept {
    auto iter = m_senders_hash.find(key);
    if (iter != m_senders_hash.end()) return iter->second;
    return nullptr;
}


rrc::receiver* rrc::node::find_receiver(const std::string& key) const noexcept {
    auto iter = m_receivers_hash.find(key);
    if (iter != m_receivers_hash.end()) return iter->second;
    return nullptr;
}


void rrc::node::on_init() {}


void rrc::node::on_start() {}


void rrc::node::on_finish() {}


void rrc::node::on_process() {}


rrc::node::~node() {}
