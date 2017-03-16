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
    class topic_holder {
    public:
        topic_holder() {
            // TODO Check it!
            m_topic_hash.max_load_factor(0.8);
        }

        void add_listener(const std::string& topic_key,
                          topic_callback callback,
                          const result_callback& result = result_callback()) {
            auto it = m_topic_hash.find(topic_key);
            if (it == m_topic_hash.end()) {
                it = m_topic_hash.emplace(topic_key, topic()).first;
            }
            auto& topic = it->second;
            topic.add_listener(std::move(callback), result);
        }

        // TODO: Docs
        void remove_listener(const std::string& topic_key,
                             const topic_callback& callback,
                             const result_callback& result = result_callback()) {
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

        void send_message(const std::string& topic_key, const shared_buffer& msg) {
            auto it = m_topic_hash.find(topic_key);
            if (it != m_topic_hash.end()) {
                auto& topic = it->second;
                topic.send_message(msg);
            }
        }

        /**
         * @brief Returns set of the keys of registered topics
         * @return Vector of the topics's keys
         */
        std::vector<std::string> keys() const {
            std::vector<std::string> keys;
            keys.reserve(m_topic_hash.size());
            for (auto&& topic : m_topic_hash) {
                keys.push_back(topic.first);
            }
            return keys;
        }


    private:
        std::unordered_map<std::string, topic> m_topic_hash;

    };
}


