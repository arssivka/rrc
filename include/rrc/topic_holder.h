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
 *  @date 8/24/16
 */

#pragma once


#include <unordered_map>
#include <set>
#include <memory>
#include <vector>
#include "topic.h"

namespace rrc {
    /**
     * @brief Class that contains all the topics and grants access to them.
     */
    template <class K, class M>
    class topic_holder {
    public:
        typedef K topic_key_type;
        typedef M message_type;
        typedef typename topic<message_type>::callback_type callback_type;

        topic_holder() {
            // TODO Check it!
            m_topic_hash.max_load_factor(0.8);
        }

        void add_listener(const topic_key_type& topic_key, callback_type callback_ptr) {
            auto it = m_topic_hash.find(topic_key);
            if (it == m_topic_hash.end()) {
                it = m_topic_hash.emplace(topic_key, topic<message_type>()).first;
            }
            auto& topic = it->second;
            topic.add_listener(std::move(callback_ptr));
        }

        // TODO: Docs
        void remove_listener(const topic_key_type& key, callback_type callback) {
            auto it = m_topic_hash.find(key);
            if (it != m_topic_hash.end()) {
                auto& topic = it->second;
                topic.remove_listener(callback);
                if (!topic.has_listeners()) {
                    m_topic_hash.erase(it);
                }
            }
        }

        void send_message(const topic_key_type& key, const message_type& message) {
            auto it = m_topic_hash.find(key);
            if (it != m_topic_hash.end()) {
                auto& topic = it->second;
                topic.send_message(message);
            }
        }

        /**
         * @brief Returns set of the keys of registered topics
         * @return Vector of the topics's keys
         */
        std::vector<topic_key_type> keys() const {
            std::vector<K> keys;
            keys.reserve(m_topic_hash.size());
            for (auto&& topic : m_topic_hash) {
                keys.push_back(topic.first);
            }
            return keys;
        }


    private:
        std::unordered_map<topic_key_type, topic<message_type>> m_topic_hash;

    };
}


