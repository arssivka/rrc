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
 *  @date 11/5/16
 */

#include <rrc/core/advertising_mechanism.h>
#include <rrc/core/exec.h>


using namespace rrc;

advertising_mechanism::advertising_mechanism(std::shared_ptr<abstract_queue_adapter<task>> sync_queue,
                                                  queue_adapter_factory<task>& task_queue_factory)
        : m_sync_queue(sync_queue),
          m_listeners_queue((abstract_queue_adapter<task>*) task_queue_factory.create_unique_pointer().release()),
          m_messages_queue((abstract_queue_adapter<task>*) task_queue_factory.create_unique_pointer().release()) {}


std::vector<std::string> advertising_mechanism::keys() const {
    return m_topic_holder.keys();
}

void advertising_mechanism::enqueue_update() {
    if (m_changes_enqueued_flag.test_and_set(std::memory_order_acquire)) {
        m_sync_queue->enqueue([this]() {
            this->apply_queues();
        });
    }
}

void advertising_mechanism::apply_queues() {
    exec_all(m_listeners_queue);
    exec_all(m_messages_queue);
    m_changes_enqueued_flag.clear(std::memory_order_release);
}


void advertising_mechanism::send_message(advertising_mechanism::key_type key, advertising_mechanism::message message) {
    m_messages_queue->enqueue([this, key_cap = std::move(key),
                                      message_cap = std::move(message)]() mutable {
        m_topic_holder.send_message(key_cap, std::move(message_cap));
    });
    this->enqueue_update();
}


void advertising_mechanism::add_listener(advertising_mechanism::key_type key,
                                         std::shared_ptr<advertising_mechanism::subscriber> listener_ptr) {
    m_listeners_queue->enqueue([this, key_cap = std::move(key),
                                       listener_ptr_cap = std::move(listener_ptr)]() mutable {
        m_topic_holder.add_listener(key_cap, std::move(listener_ptr_cap));
    });
    this->enqueue_update();
}


void advertising_mechanism::remove_listener(advertising_mechanism::key_type key,
                                            const std::shared_ptr<advertising_mechanism::subscriber> listener_ptr) {
    m_listeners_queue->enqueue([this, key_cap = std::move(key),
                                       listener_ptr_cap = std::move(listener_ptr)]() mutable {
        m_topic_holder.remove_listener(key_cap, std::move(listener_ptr_cap));
    });
    this->enqueue_update();
}


