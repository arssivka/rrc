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
#include "topic.h"

namespace rrc {
    /**
     * @brief Class that contains all the topics and grants access to them.
     */
    template <class K>
    class topic_holder {
    public:
        using key_type = K;
        using message_type = topic::message_type;
        using subscriber_type = topic::subscriber_type;

        /**
         * @brief Constructor of billboard. Sets the default max load factor 0.8
         */
        topic_holder() {
            // TODO Check it!
            m_topic_hash.max_load_factor(0.8);
        }

        /**
         * @brief Register message listener
         * @param topicName Name of the topic
         * @param subscriber_ptr Pointer to listener to register
         */
        void add_listener(const key_type& key,
                          std::shared_ptr<subscriber_type> subscriber_ptr) {
            auto found = m_topic_hash.find(key);
            if (found == m_topic_hash.end()) {
                found = m_topic_hash.emplace(key, topic()).first;
            }
            auto& topic = found->second;
            topic.add_listener(std::move(subscriber_ptr));
        }

        // TODO: Docs
        void remove_listener(const key_type& key,
                             std::shared_ptr<subscriber_type> subscriber_ptr) {
            auto iterator = m_topic_hash.find(key);
            if (iterator != m_topic_hash.end()) {
                auto& topic = iterator->second;
                topic.remove_listener(subscriber_ptr);
            }
        }

        /**
         * @brief Sends the message
         * @param topicName Name of the topic
         * @param message Pointer to message that needs to be sent
         */
        void send_message(const key_type& key, message_type message) {
            auto found = m_topic_hash.find(key);
            if (found != m_topic_hash.end()) {
                auto& topic = found->second;
                topic.send_message(std::move(message));
            }
        }

        /**
         * @brief Returns set of the keys of registered topics
         * @return Vector of the topics's keys
         */
        std::vector<key_type> keys() const {
            std::vector<K> keys;
            keys.reserve(m_topic_hash.size());
            for (auto&& topic : m_topic_hash) {
                keys.push_back(topic.first);
            }
            return keys;
        }


    private:
        std::unordered_map<key_type, topic> m_topic_hash;

    };
}


