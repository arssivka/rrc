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
#include "service.h"

namespace rrc {
    template<class K>
    class service_holder {
    public:
        using key_type = K;
        using message_type = service::message_type;
        using listener_type = service::listener_type;
        using callback_type = service::callback_type;

        service_holder() {
            // TODO: Test it
            m_service_hash.max_load_factor(0.8);
        }

        void add_service(const key_type& key, std::shared_ptr<service> service_ptr) {
            m_service_hash.insert({key, std::move(service_ptr)});
        }

        void remove_service(const key_type& key, std::shared_ptr<service> service_ptr) {
            auto range = m_service_hash.equal_range(key);
            auto it = range.first;
            while (it != range.second) {
                if (it->second == service_ptr) {
                    m_service_hash.erase(it);
                } else {
                    ++it;
                }
            }
        }

        void call(const key_type& name, std::shared_ptr<listener_type> listener_ptr, message_type input) {
            auto range = m_service_hash.equal_range(name);
            auto it = range.first;
            while (it != range.second) {
                auto& service_ptr = it->second;
                if (service_ptr->call(listener_ptr, input)) {
                    ++it;
                } else {
                    m_service_hash.erase(it);
                }
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
        std::unordered_multimap<K, std::shared_ptr<service>> m_service_hash;
    };
}


