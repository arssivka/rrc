/**
 *  @autor arssivka
 *  @date 4/8/17
 */

#include <algorithm>
#include "rrc/sender.h"
#include "rrc/receiver.h"

void rrc::sender::add_receiver(rrc::receiver* rec_ptr) {
    if (rec_ptr == nullptr) return;
    m_receivers_vector.push_back(rec_ptr);
}

void rrc::sender::remove_receiver(rrc::receiver* rec_ptr) {
    auto iter = std::find(m_receivers_vector.begin(), m_receivers_vector.end(), rec_ptr);
    if (iter != m_receivers_vector.end()) m_receivers_vector.erase(iter);
}

void rrc::sender::send(const std::string& str) {
    this->send((const uint8_t*) str.c_str(), str.size());
}

void rrc::sender::send(const uint8_t* buff, size_t size) {
    for (receiver* rec : m_receivers_vector) rec->receive(buff, size);
}

size_t rrc::sender::receivers_count() const noexcept {
    return m_receivers_vector.size();
}

bool rrc::sender:: connected() const noexcept {
    return !m_receivers_vector.empty();
}


bool rrc::sender::has_receiver(const receiver* receiver_ptr) const noexcept {
    auto it = std::find(m_receivers_vector.begin(), m_receivers_vector.end(), receiver_ptr);
    return it != m_receivers_vector.end();
}


void rrc::sender::disconnect_all() {
    m_receivers_vector.clear();
}
