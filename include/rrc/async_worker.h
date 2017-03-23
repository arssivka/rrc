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
 *  @date 3/16/17
 */
#pragma once


#include <queue>
#include <functional>
#include <condition_variable>
#include <thread>
#include "non_copyable.h"

namespace rrc {
    template <class T>
    class async_worker
            : private non_copyable {
    public:
        async_worker()
                : m_finished(true) {}

        async_worker(async_worker&&) = default;

        async_worker(std::function<void(T&)> callback)
                : m_finished(false) {
            this->start_thread();
        }

        async_worker& operator=(async_worker&& rhs) {
            m_worker = std::move(rhs.m_worker);
            m_queue = std::move(rhs.m_queue);
            m_finished = std::move(rhs.m_finished);

        }

        async_worker& operator=(std::function<void(T&)> callback) {
            this->stop_thread();
            this->start_thread(callback);
        }

        void push(const T& data) {
            {
                std::lock_guard<std::mutex> lock(m_queue_mut);
                if (m_finished)
                    throw std::runtime_error("enqueue on stopped async_worker");
                m_queue.push(data);
            }
            m_queue_cv.notify_one();
        }

        void push(T&& data) {
            {
                std::lock_guard<std::mutex> lock(m_queue_mut);
                if (m_finished)
                    throw std::runtime_error("enqueue on stopped async_worker");
                m_queue.push(std::move(data));
            }
            m_queue_cv.notify_one();
        }

        ~async_worker() {
            this->stop_thread();
        }


    private:
        void start_thread(std::function<void(T&)> callback) {
            m_finished = false;
            m_worker = std::thread([this, callback_cap = std::move(callback)] {
                T data;
                while (this->wait_for_data(data)) {
                    callback_cap(data);
                }
            });
        }

        void stop_thread() {
            bool finished = false;
            {
                std::lock_guard<std::mutex> lock(m_queue_mut);
                finished = m_finished;
                m_finished = true;
            }
            if (!finished) {
                m_queue_cv.notify_one();
                m_worker.join();
            }
        }

        bool wait_for_data(T& data) {
            std::unique_lock<std::mutex> lock(m_queue_mut);
            m_queue_cv.wait(lock, [this] { return !m_queue.empty() || m_finished; });
            if (m_finished && m_queue.empty()) return false;
            data = std::move(m_queue.front());
            m_queue.pop();
            return true;
        }


    private:
        std::thread m_worker;
        std::condition_variable m_queue_cv;
        std::mutex m_queue_mut;
        std::queue<T> m_queue;
        bool m_finished;
    };
}

