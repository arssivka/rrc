/**
 * Copyright 2016 Arseniy Ivin <arssivka@yandex.ru>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *  @autor arssivka
 *  @date 3/16/17
 */

#include <rrc/topic_holder.h>


rrc::topic_holder::topic_holder() {
    m_topic_hash.max_load_factor(0.8);
}


void rrc::topic_holder::add_topic_listener(const std::string& topic_key,
                                           rrc::topic_callback callback,
                                           const rrc::result_callback& result) {
    bool topic_created = false;
    auto it = m_topic_hash.find(topic_key);
    if (it == m_topic_hash.end()) {
        it = m_topic_hash.emplace(topic_key, topic()).first;
        topic_created = true;
    }
    auto& topic = it->second;
    bool listener_added = topic.add_listener(std::move(callback), result);
    if (topic_created) {
        if (listener_added) {
            m_key_notifier.notify(RESULT_CODE_KEY_ADDED, topic_key);
        } else {
            m_topic_hash.erase(it);
        }
    }
}


void rrc::topic_holder::remove_topic_listener(const std::string& topic_key,
                                              const rrc::topic_callback& callback,
                                              const rrc::result_callback& result) {
    auto it = m_topic_hash.find(topic_key);
    if (it != m_topic_hash.end()) {
        auto& topic = it->second;
        topic.remove_listener(callback, result);
        if (topic.listeners_count() == 0) {
            m_topic_hash.erase(it);
            m_key_notifier.notify(RESULT_CODE_KEY_REMOVED, topic_key);
        }
    } else if (result) {
        result(RESULT_CODE_FAIL);
    }

}


void rrc::topic_holder::send_message(const std::string& topic_key,
                                     const rrc::shared_buffer& msg) {
    auto it = m_topic_hash.find(topic_key);
    if (it != m_topic_hash.end()) {
        auto& topic = it->second;
        topic.send_message(msg);
    }
}


void rrc::topic_holder::add_key_listener(key_callback callback,
                                         bool get_exits_keys,
                                         const result_callback& result) {
    if (m_key_notifier.add_listener(std::move(callback), result) && get_exits_keys) {
        this->send_keys(callback, RESULT_CODE_KEY_ADDED);
    }
}


void rrc::topic_holder::remove_key_listener(const rrc::key_callback& callback,
                                            const rrc::result_callback& result) {
    m_key_notifier.remove_listener(callback, result);
}


void rrc::topic_holder::send_keys(const rrc::key_callback& callback, rrc::result_code code) const {
    for (auto&& hash_pair : m_topic_hash) {
        callback(code, hash_pair.first);
    }
}


size_t rrc::topic_holder::listeners_count(const std::string& topic_key) const {
    auto it = m_topic_hash.find(topic_key);
    if (it != m_topic_hash.end()) {
        return it->second.listeners_count();
    }
    return 0;
}
