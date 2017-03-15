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
#include <condition_variable>
#include "task_queue.h"

namespace rrc {
    class concurrent_task_queue : public task_queue {
    public:
        concurrent_task_queue()
                : m_destroyed(false) {}

        virtual void enqueue(task_type value) override {
            {
                std::unique_lock<std::mutex> lock(m_data_mutex);
                m_data_queue.emplace(std::move(value));
            }
            m_data_cv.notify_one();
        }

        virtual bool try_exec() override {
            task_type task;
            if (!this->try_dequeue(task)) return false;
            task();
            return true;
        }

        virtual bool try_dequeue(task_type& task) override {
            std::lock_guard<std::mutex> lock(m_data_mutex);
            if (m_data_queue.empty())
                return false;
            task = std::move(m_data_queue.front());
            m_data_queue.pop();
            return true;
        }

        virtual void clean() override {
            std::lock_guard<std::mutex> lock(m_data_mutex);
            while (!m_data_queue.empty()) m_data_queue.pop();
        }

        bool wait_for_task(task_type& task) {
            std::unique_lock<std::mutex> lock(m_data_mutex);
            m_data_cv.wait(lock, [this]() -> bool {
                return m_destroyed || !m_data_queue.empty();
            });
            if (m_data_queue.empty() || m_destroyed)
                return false;
            task = std::move(m_data_queue.front());
            m_data_queue.pop();
        }

        virtual ~concurrent_task_queue() override {
            {
                std::lock_guard<std::mutex> lock(m_data_mutex);
                m_destroyed = true;
            }
            m_data_cv.notify_all();
        }

    private:
        bool m_destroyed;
        std::queue<task_type> m_data_queue;
        std::condition_variable m_data_cv;
        std::mutex m_data_mutex;

    };
}