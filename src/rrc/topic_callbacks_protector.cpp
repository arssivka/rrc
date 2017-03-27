/**
 *  @autor tekatod
 *  @date 3/27/17
 */
#include "include/rrc/topic_callbacks_protector.h"

rrc::topic_callbacks_protector::topic_callbacks_protector(rrc::core& core) : m_core(core) { }

void rrc::topic_callbacks_protector::insert(std::pair<std::string, rrc::topic_callback>&& named_callback) {
    m_callbacks.emplace(named_callback);
}

void rrc::topic_callbacks_protector::remove_listeners(std::string& name) {
    for(auto it = m_callbacks.begin(); it != m_callbacks.end();) {
        if(it->first == name) {
            it = m_callbacks.erase(it);
        }
        ++it;
    }
}

void rrc::topic_callbacks_protector::remove_listener(const rrc::topic_callback& listener) {
    for(auto it = m_callbacks.begin(); it != m_callbacks.end();) {
        if(it->second == listener) {
            it = m_callbacks.erase(it);
        }
        ++it;
    }
}

void rrc::topic_callbacks_protector::insert_and_register(std::pair<std::string, rrc::topic_callback> &&named_callback,
                                                         rrc::result_callback result) {
    m_callbacks.emplace(named_callback);
    m_core.topics().add_topic_listener(named_callback.first, named_callback.second, result);
}

void rrc::topic_callbacks_protector::remove_and_unregister(std::string &name, rrc::result_callback result) {
    for(auto it = m_callbacks.begin(); it != m_callbacks.end();) {
        if(it->first == name) {
            m_core.topics().remove_topic_listener(it->first, it->second, result);
            it = m_callbacks.erase(it);
        }
        ++it;
    }
}

void rrc::topic_callbacks_protector::remove_and_unregister_all(rrc::result_callback result) {
    for(auto it = m_callbacks.begin(); it != m_callbacks.end();) {
        m_core.topics().remove_topic_listener(it->first, it->second, result);
        it = m_callbacks.erase(it);
    }
}
