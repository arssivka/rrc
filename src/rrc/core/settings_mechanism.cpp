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

rrc::settings_mechanism::settings_mechanism(std::shared_ptr<rrc::abstract_task_queue_adapter> sync_queue,
                                            rrc::queue_adapter_factory<rrc::task>& task_queue_factory)
        : m_sync_queue(std::move(sync_queue)),
          m_properties_queue((abstract_task_queue_adapter*) task_queue_factory.create_unique_pointer().release()),
          m_listeners_queue((abstract_task_queue_adapter*) task_queue_factory.create_unique_pointer().release()),
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
    m_listeners_queue->exec_all();
    m_properties_queue->exec_all();
    m_changes_enqueued_flag.clear(std::memory_order_release);
}
