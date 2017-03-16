/**
 *  @autor arssivka
 *  @date 3/16/17
 */

#include <rrc/topic.h>


void rrc::topic::add_listener(rrc::topic_callback callback, const rrc::result_callback& result) {
    m_listeners_hash.emplace(std::move(callback));
    if (result) result(status::success);
}


void rrc::topic::remove_listener(rrc::topic_callback callback, const rrc::result_callback& result) {
    auto it = m_listeners_hash.find(callback);
    status stat = status::fail;
    if (it != m_listeners_hash.end()) {
        m_listeners_hash.erase(it);
        stat = status::success;
    }
    if (result) result(stat);
}


void rrc::topic::send_message(const rrc::shared_buffer& msg) {
    for (auto&& listener : m_listeners_hash) {
        listener(msg);
    }
}


bool rrc::topic::has_listeners() const {
    return !m_listeners_hash.empty();
}
