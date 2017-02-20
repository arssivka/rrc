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


#include "exec.h"
#include "settings_holder.h"
#include "queue_adapter_factory.h"
#include <atomic>

namespace rrc {
    class settings_mechanism {
    public:
        using key_type = std::string;
        using listener_type = settings_holder<key_type>::listener_type;

        settings_mechanism(std::shared_ptr<abstract_queue_adapter<task>> sync_queue,
                           queue_adapter_factory<task>& task_queue_factory);

        bool try_get_property(const key_type& key, property& output) const;

        void set_property(key_type key, property prop);

        void add_listener(key_type key, std::shared_ptr<listener_type> listener_ptr);

        void remove_listener(key_type key, std::shared_ptr<listener_type> listener_ptr);

        std::vector<key_type> keys() const;


    private:
        void enqueue_update();

        void apply_queues();


    private:
        settings_holder<key_type> m_settings_holder;
        std::shared_ptr<abstract_queue_adapter<task>> m_sync_queue;
        std::unique_ptr<abstract_queue_adapter<task>> m_properties_queue;
        std::unique_ptr<abstract_queue_adapter<task>> m_listeners_queue;
        std::atomic_flag m_changes_enqueued_flag;
    };
}


