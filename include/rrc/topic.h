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


#include <unordered_set>

namespace rrc {
    /**
     * @brief All messages come to topics. Topic is a special place for holding specific messages. Nodes can subscribe to tpoics to get messages they need.
     */

    template <class M>
    class topic {
    public:
        typedef M message_type;
        typedef std::function<void(const message_type&)> callback_type;

        /**
         * @brief Register message callback
         * @param callback_ptr Pointer to callback to register
         */
        void add_listener(std::shared_ptr<callback_type> callback_ptr) {
            m_listeners_hash.emplace(std::move(callback_ptr));
        }

        // TODO: Docs
        void remove_listener(std::shared_ptr<callback_type> callback_ptr) {
            auto it = m_listeners_hash.find(callback_ptr);
            if (it != m_listeners_hash.end()) {
                m_listeners_hash.erase(it);
            }
        }

        /**
         * @brief Sends the message
         * @param message Pointer to message that needs to be sent
         */
        void send_message(message_type message) {
            for (auto&& listener_ptr : m_listeners_hash) {
                auto& listener = *listener_ptr;
                listener(message);
            }
        }

        /**
         * @brief Checks if this topic has listeners
         * @return True if topic has lesteners, otherwise false
         */
        bool has_listeners() const {
            return !m_listeners_hash.empty();
        }

    private:
        std::unordered_set<std::shared_ptr<callback_type>> m_listeners_hash;
    };
}


