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
    // TODO Check it!
    m_topic_hash.max_load_factor(0.8);
}


void rrc::topic_holder::add_listener(const std::string& topic_key, rrc::topic_callback callback,
                                     const rrc::result_callback& result) {
    auto it = m_topic_hash.find(topic_key);
    if (it == m_topic_hash.end()) {
        it = m_topic_hash.emplace(topic_key, topic()).first;
    }
    auto& topic = it->second;
    topic.add_listener(std::move(callback), result);
}


void rrc::topic_holder::remove_listener(const std::string& topic_key, const rrc::topic_callback& callback,
                                        const rrc::result_callback& result) {
    auto it = m_topic_hash.find(topic_key);
    if (it != m_topic_hash.end()) {
        auto& topic = it->second;
        topic.remove_listener(callback, result);
        if (!topic.has_listeners()) {
            m_topic_hash.erase(it);
        }
    } else {
        result(status::fail);
    }

}


void rrc::topic_holder::send_message(const std::string& topic_key, const rrc::shared_buffer& msg) {
    auto it = m_topic_hash.find(topic_key);
    if (it != m_topic_hash.end()) {
        auto& topic = it->second;
        topic.send_message(msg);
    }
}


std::vector<std::string> rrc::topic_holder::keys() const {
    std::vector<std::string> keys;
    keys.reserve(m_topic_hash.size());
    for (auto&& topic : m_topic_hash) {
        keys.push_back(topic.first);
    }
    return keys;
}
