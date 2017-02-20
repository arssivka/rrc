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

#include <rrc/core/service_mechanism.h>


rrc::service_mechanism::service_mechanism(std::shared_ptr<abstract_queue_adapter<task>> sync_queue,
                                        queue_adapter_factory<task>& task_queue_factory)
        : m_sync_queue{std::move(sync_queue)},
          m_services_queue{task_queue_factory.create()},
          m_calls_queue{task_queue_factory.create()} {}


std::vector<rrc::service_mechanism::key_type> rrc::service_mechanism::keys() const {
    return m_service_holder.keys();
}

void rrc::service_mechanism::enqueue_update() {
    if (m_changes_enqueued_flag.test_and_set(std::memory_order_acquire)) {
        m_sync_queue->enqueue([this]() {
            this->apply_queues();
        });
    }
}

void rrc::service_mechanism::apply_queues() {
    exec_all(m_services_queue);
    exec_all(m_calls_queue);
    m_changes_enqueued_flag.clear(std::memory_order_release);
}


void
rrc::service_mechanism::add_service(rrc::service_mechanism::key_type key, std::shared_ptr<rrc::service> service_ptr) {
    m_services_queue->enqueue(
            [this, key_cap = std::move(key),
                    service_ptr_cap = std::move(service_ptr)]() mutable {
                m_service_holder.remove_service(key_cap, std::move(service_ptr_cap));
            });
    this->enqueue_update();
}


void rrc::service_mechanism::remove_service(rrc::service_mechanism::key_type key,
                                            const std::shared_ptr<rrc::service> service_ptr) {
    m_services_queue->enqueue(
            [this, key_cap = std::move(key),
                    service_ptr_cap = std::move(service_ptr)]() mutable {
                m_service_holder.remove_service(key_cap, std::move(service_ptr_cap));
            });
    this->enqueue_update();
}


void rrc::service_mechanism::call(rrc::service_mechanism::key_type key,
                                  std::shared_ptr<rrc::service_mechanism::listener_type> listener_ptr,
                                  rrc::service_mechanism::message_type input) {
    m_calls_queue->enqueue(
            [this, key_cap = std::move(key),
                    listener_ptr_cap = std::move(listener_ptr),
                    input_cap = std::move(input)]() mutable {
                m_service_holder.call(key_cap, std::move(listener_ptr_cap), std::move(input_cap));
            });
    this->enqueue_update();
}
