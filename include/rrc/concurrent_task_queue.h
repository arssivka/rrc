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


#include <queue>
#include <mutex>
#include "task_queue.h"

namespace rrc {
    class concurrent_task_queue : public task_queue {
    public:
        virtual void enqueue(task_type value) override {
            std::unique_lock<std::mutex> lock(m_queue_mutex);
            m_queue.emplace(std::move(value));
        }

        virtual bool try_exec() override {
            task_type task;
            std::unique_lock<std::mutex> lock(m_queue_mutex);
            if (!this->try_dequeue(task)) return false;
            task();
            return true;
        }

        virtual bool try_dequeue(task_type& task) override {
            std::unique_lock<std::mutex> lock(m_queue_mutex);
            if (m_queue.empty())
                return false;
            task = std::move(m_queue.front());
            m_queue.pop();
            return true;
        }

        virtual void clean() override {
            std::unique_lock<std::mutex> lock(m_queue_mutex);
            while (!m_queue.empty()) m_queue.pop();
        }

    private:
        std::queue<task_type> m_queue;
        std::mutex m_queue_mutex;

    };
}