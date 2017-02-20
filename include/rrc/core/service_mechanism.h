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


#include <vector>
#include "service.h"
#include "service_holder.h"
#include "queue_adapter_factory.h"

namespace rrc {
    class service_mechanism {
    public:
        using key_type = std::string;
        using message_type = service_holder<key_type>::message_type;
        using listener_type = service_holder<key_type>::listener_type;
        using callback_type = service_holder<key_type>::callback_type;

        service_mechanism(std::shared_ptr<abstract_queue_adapter<task>> sync_queue,
                          queue_adapter_factory<task>& task_queue_factory);

        void add_service(key_type key, std::shared_ptr<service> service_ptr);

        void remove_service(key_type key, const std::shared_ptr<service> service_ptr);

        void call(key_type key, std::shared_ptr<listener_type> listener_ptr, message_type input);

        std::vector<key_type> keys() const;

    private:
        void enqueue_update();

        void apply_queues();

    private:
        service_holder<key_type> m_service_holder;
        std::shared_ptr<abstract_queue_adapter<task>> m_sync_queue;
        std::unique_ptr<abstract_queue_adapter<task>> m_services_queue;
        std::unique_ptr<abstract_queue_adapter<task>> m_calls_queue;
        std::atomic_flag m_changes_enqueued_flag;
    };
}


