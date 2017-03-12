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
 *  @date 10/31/16
 */

#pragma once

#include "task_queue.h"
#include <concurrentqueue.h>

namespace rrc {
    class lockfree_task_queue : public task_queue {
    public:
        virtual void enqueue(task_type task) override {
            m_queue.enqueue(std::move(task));
        }

        virtual bool try_exec() override {
            task_type task;
            if (m_queue.try_dequeue(task)) {
                task();
                return true;
            }
            return false;

        }

        virtual bool try_dequeue(task_type& task) override {
            return m_queue.try_dequeue(task);
        }

        virtual void clean() override {
            task_type task;
            while (m_queue.try_dequeue(task));
        }

    private:
        moodycamel::ConcurrentQueue<task_type> m_queue;
    };
}