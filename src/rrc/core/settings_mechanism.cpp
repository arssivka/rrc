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

#include <rrc/core/settings_mechanism.h>

rrc::settings_mechanism::settings_mechanism(std::shared_ptr<rrc::abstract_queue_adapter<task>> sync_queue,
                                            rrc::queue_adapter_factory<rrc::task>& task_queue_factory)
        : m_sync_queue(std::move(sync_queue)),
          m_properties_queue(task_queue_factory.create()),
          m_listeners_queue(task_queue_factory.create()),
          m_changes_enqueued_flag(ATOMIC_FLAG_INIT) {}

bool rrc::settings_mechanism::try_get_property(const rrc::settings_mechanism::key_type& key,
                                               property& output) const {
    return m_settings_holder.try_get_property(key, output);
}

std::vector<rrc::settings_mechanism::key_type> rrc::settings_mechanism::keys() const {
    return m_settings_holder.keys();
}

void rrc::settings_mechanism::enqueue_update() {
    if (m_changes_enqueued_flag.test_and_set(std::memory_order_acquire)) {
        m_sync_queue->enqueue([this]() {
            this->apply_queues();
        });
    }
}

void rrc::settings_mechanism::apply_queues() {
    exec_all(m_listeners_queue);
    exec_all(m_properties_queue);
    m_changes_enqueued_flag.clear(std::memory_order_release);
}


void rrc::settings_mechanism::set_property(rrc::settings_mechanism::key_type key, rrc::property prop) {
    m_properties_queue->enqueue([this, key_cap = std::move(key),
                                        prop_cap = std::move(prop)]() mutable {
        m_settings_holder.set_property(key_cap, std::move(prop_cap));
    });
    this->enqueue_update();
}


void rrc::settings_mechanism::add_listener(rrc::settings_mechanism::key_type key,
                                           std::shared_ptr<rrc::settings_mechanism::listener_type> listener_ptr) {
    m_listeners_queue->enqueue([this, key_cap = std::move(key),
                                       listener_ptr_cap = std::move(listener_ptr)]() mutable {
        m_settings_holder.add_listener(key_cap, std::move(listener_ptr_cap));
    });
    this->enqueue_update();
}


void rrc::settings_mechanism::remove_listener(rrc::settings_mechanism::key_type key,
                                              std::shared_ptr<rrc::settings_mechanism::listener_type> listener_ptr) {
    m_listeners_queue->enqueue([this, key_cap = std::move(key),
                                       listener_ptr_cap = std::move(listener_ptr)]() mutable {
        m_settings_holder.remove_listener(key_cap, std::move(listener_ptr_cap));
    });
    this->enqueue_update();
}
