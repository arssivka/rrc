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
 *  @date 2/24/17
 */
#include <rrc/task_scheduler.h>

void rrc::task_scheduler::enqueue(task_type task) {
    m_task_queue.enqueue(std::move(task));
}

void rrc::task_scheduler::enqueue(std::chrono::steady_clock::time_point tp,
                                  task_type task) {
    if (tp <= std::chrono::steady_clock::now()) {
        m_task_queue.enqueue(std::move(task));
    } else {
        m_task_queue.enqueue([this, tp, task_cap = std::move(task)]() mutable {
            if (tp <= std::chrono::steady_clock::now()) {
                task_cap();
                return;
            }
            m_pending_tasks_queue.push({tp, std::move(task_cap)});
        });
    }
}

bool rrc::task_scheduler::try_dequeue(task_type& task) {
    std::pair<std::chrono::steady_clock::time_point, task_type> scheduled_task;
    if (m_pending_tasks_queue.try_dequeue_if(scheduled_task,
                                                [](const pending_task_type& task) {
                                                    auto& tp = task.first;
                                                    return tp <= std::chrono::steady_clock::now();
                                                })) {
        task = std::move(scheduled_task.second);
        return true;
    }
    return m_task_queue.try_dequeue(task);
}

