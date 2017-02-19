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


#include "abstract_task_queue_adapter.h"
#include "settings_holder.h"
#include "queue_adapter_factory.h"
#include <atomic>

namespace rrc {
    class settings_mechanism {
    public:
        using key_type = std::string;
        using listener_type = settings_holder<key_type>::listener_type;

        settings_mechanism(std::shared_ptr<abstract_task_queue_adapter> sync_queue,
                           queue_adapter_factory<task>& task_queue_factory);

        bool try_get_property(const key_type& key, property& output) const;

        void set_property(key_type key, property prop) {
            m_properties_queue->enqueue([this, key_cap = std::move(key),
                                                prop_cap = std::move(prop)]() mutable {
                m_settings_holder.set_property(key_cap, std::move(prop_cap));
            });
            this->enqueue_update();
        }

        void add_listener(key_type key, std::shared_ptr<listener_type> listener_ptr) {
            m_listeners_queue->enqueue([this, key_cap = std::move(key),
                                               listener_ptr_cap = std::move(listener_ptr)]() mutable {
                m_settings_holder.add_listener(key_cap, std::move(listener_ptr_cap));
            });
            this->enqueue_update();
        }

        void remove_listener(key_type key, std::shared_ptr<listener_type> listener_ptr) {
            m_listeners_queue->enqueue([this, key_cap = std::move(key),
                                               listener_ptr_cap = std::move(listener_ptr)]() mutable {
                m_settings_holder.remove_listener(key_cap, std::move(listener_ptr_cap));
            });
            this->enqueue_update();
        }

        std::vector<key_type> keys() const;


    private:
        void enqueue_update();

        void apply_queues();


    private:
        settings_holder<key_type> m_settings_holder;
        std::shared_ptr<abstract_task_queue_adapter> m_sync_queue;
        std::unique_ptr<abstract_task_queue_adapter> m_properties_queue;
        std::unique_ptr<abstract_task_queue_adapter> m_listeners_queue;
        std::atomic_flag m_changes_enqueued_flag;
    };
}


