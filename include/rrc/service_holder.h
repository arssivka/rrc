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
 *  @date 2/7/17
 */

#pragma once


#include <unordered_map>
#include <algorithm>

namespace rrc {
    template<class K, class M>
    class service_holder {
    public:
        typedef K key_type;
        typedef M message_type;
        typedef std::function<void(message_type)> listener_type;
        typedef std::function<void(message_type, const listener_type&)> callback_type;

        service_holder() {
            // TODO: Test it
            m_service_hash.max_load_factor(0.8);
        }

        void add_service(const key_type& key, std::shared_ptr<callback_type> callback_ptr) {
            m_service_hash.emplace(key, std::move(callback_ptr));
        }

        void remove_service(std::shared_ptr<callback_type> callback_ptr) {
            auto it = std::find_if(m_service_hash.begin(), m_service_hash.end(),
                                [callback_ptr_cap = std::move(callback_ptr)](const auto& pair) {
                return pair->second == callback_ptr_cap;
            });
            m_service_hash.erase(it);
        }

        void call(const key_type& key, message_type input, const listener_type& listener) {
            auto it = m_service_hash.find(key);
            if (it != m_service_hash.end()) {
                auto& callback = *it;
                callback(std::move(input), listener);
            }
        }

        std::vector<K> keys() const {
            std::vector<K> keys;
            keys.reserve(m_service_hash.size());
            for (auto&& keyPair : m_service_hash) {
                keys.push_back(keyPair.first);
            }
            return keys;
        }

    private:
        std::unordered_map<K, std::shared_ptr<callback_type>> m_service_hash;
    };
}


