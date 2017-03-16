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
#include "service_status.h"
#include "shared_function.h"

namespace rrc {
    template<class K, class M>
    class service_holder {
    public:
        typedef K key_type;
        typedef M message_type;
        typedef shared_function<void(service_status, const message_type&)> listener_type;
        typedef shared_function<service_status(const message_type&, message_type&)> callback_type;

        service_holder() {
            m_service_hash.max_load_factor(0.8);
        }

        void add_service(const key_type& key, callback_type callback) {
            m_service_hash.emplace(key, std::move(callback));
        }

        void remove_service(const callback_type& callback) {
            auto it = std::find_if(m_service_hash.begin(), m_service_hash.end(),
                                [&callback](const auto& pair) {
                return pair.second == callback;
            });
            m_service_hash.erase(it);
        }

        void call(const key_type& key, message_type input, listener_type listener) {
            auto it = m_service_hash.find(key);
            if (it != m_service_hash.end()) {
                auto& callback = it->second;
                message_type output;
                service_status result = callback(std::move(input), output);
                listener(result, output);
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
        std::unordered_map<K, callback_type> m_service_hash;
    };
}


