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
 *  @date 2/15/17
 */

#pragma once


#include <unordered_map>
#include <vector>
#include "task_packer.h"
#include "property.h"

namespace rrc {
    template <class K>
    class settings_holder {
    public:
        using key_type = K;
        using listener_type = task_packer<property>;

        settings_holder() = default;

        void remove_table(const key_type& key) {
            auto found = m_properties_hash.find(key);
            if (found != m_properties_hash.end()) {
                m_properties_hash.erase(found);
                this->notify(key, property());
            }
        }

        bool try_get_property(const key_type& key, property& output) const {
            auto found = m_properties_hash.find(key);
            if (found == m_properties_hash.end()) {
                return false;
            }
            output = found->second;
            return true;
        }

        void set_property(const key_type& key, property prop) {
            m_properties_hash.emplace(key, prop);
            this->notify(key, prop);
        }

        bool contains(const key_type& key) const {
            auto found = m_properties_hash.find(key);
            return found != m_properties_hash.end();
        }

        std::vector<key_type> keys() const {
            std::vector<key_type> names;
            names.reserve(m_properties_hash.size());
            for (auto&& prop : m_properties_hash) {
                names.push_back(prop.first);
            }
            return names;
        }

        void add_listener(const key_type& key, std::shared_ptr<listener_type> listener_ptr) {
            m_listeners_hash.emplace(key, std::move(listener_ptr));
        }

        void remove_listener(const key_type& key, std::shared_ptr<listener_type> lisneter_ptr) {
            auto range = m_listeners_hash.equal_range(key);
            auto it = range.first;
            while (it != range.second) {
                if (it->second != lisneter_ptr) {
                    ++it;
                } else {
                    m_listeners_hash.erase(it);
                }
            }
        }


    private:
        void notify(const key_type& key, const property& prop) {
            auto range = m_listeners_hash.equal_range(key);
            auto it = range.first;
            while (it != range.second) {
                auto& listener_ptr = it->second;
                if (listener_ptr->enqueue_task(prop)) {
                    ++it;
                } else {
                    m_listeners_hash.erase(it);
                }
            }
        }

    private:
        std::unordered_map<key_type, property> m_properties_hash;
        std::unordered_multimap<key_type, std::shared_ptr<listener_type>> m_listeners_hash;
    };
}


