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

#include <rrc/core/service.h>


rrc::service::service(std::weak_ptr<rrc::abstract_task_queue_adapter> task_queue, rrc::service::callback_type callback)
        : m_task_queue_ptr(std::move(task_queue)), m_callback(std::move(callback)) {}


bool rrc::service::call(std::shared_ptr<listener_type> listener_ptr, message_type input) {
    auto task_queue = m_task_queue_ptr.lock();
    if (task_queue != nullptr) {
        task_queue->enqueue(
                [this, listener_ptr_cap = std::move(listener_ptr), input_cap = std::move(input)]() mutable {
                    auto result = m_callback(std::move(input_cap));
                    listener_ptr_cap->enqueue_task(result);
                });
        return true;
    } else {
        return false;
    }
}

bool rrc::service::is_orphan() const {
    return m_task_queue_ptr.use_count() == 0;
}
