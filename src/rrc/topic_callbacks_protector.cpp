/**
 *  @autor tekatod
 *  @date 3/27/17
 */
#include "include/rrc/topic_callbacks_protector.h"

rrc::topic_callbacks_protector::topic_callbacks_protector(rrc::core& core) : m_core(core) { }

void rrc::topic_callbacks_protector::insert(std::string topic_key,
                                            rrc::topic_callback callback) {
    m_callbacks.emplace(std::move(topic_key),
                        std::move(callback));
}

void rrc::topic_callbacks_protector::remove_listeners(std::string& name) {
    for(auto it = m_callbacks.begin(); it != m_callbacks.end(); ++it) {
        if(it->first == name) {
            it = m_callbacks.erase(it);
        }
    }
}

void rrc::topic_callbacks_protector::remove_listener(const rrc::topic_callback& listener) {
    for(auto it = m_callbacks.begin(); it != m_callbacks.end(); ++it) {
        if(it->second == listener) {
            it = m_callbacks.erase(it);
        }
    }
}

void rrc::topic_callbacks_protector::insert_and_register(std::string topic_key,
                                                         rrc::topic_callback callback,
                                                         rrc::result_callback result) {
    m_callbacks.emplace(topic_key, callback);
    m_core.topics().add_topic_listener(std::move(topic_key),
                                       std::move(callback),
                                       result);
}

void rrc::topic_callbacks_protector::remove_and_unregister(const std::string& name,
                                                           rrc::result_callback result) {
    for(auto it = m_callbacks.begin(); it != m_callbacks.end(); ++it) {
        if(it->first == name) {
            m_core.topics().remove_topic_listener(it->first, it->second, result);
            it = m_callbacks.erase(it);
        }
    }
}

void rrc::topic_callbacks_protector::remove_and_unregister_all(rrc::result_callback result) {
    for(auto it = m_callbacks.begin(); it != m_callbacks.end(); ++it) {
        m_core.topics().remove_topic_listener(it->first, it->second, result);
    }
    m_callbacks.clear();
}
