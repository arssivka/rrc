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
 *  @date 3/1/17
 */
#pragma once


#include <queue>
#include <mutex>

namespace rrc {
    template <class T, class Container = std::vector<T>,
            class Compare = std::less<typename Container::value_type>>
    class concurrent_priority_queue {
    public:
        typedef T value_type;
        typedef Container container_type;
        typedef typename container_type::reference reference;
        typedef typename container_type::const_reference const_reference;

        bool try_dequeue(reference& value) {
            std::unique_lock<std::mutex> lock(m_priority_queue_mut);
            if (m_priority_queue.empty()) {
                return false;
            }
            value = std::move(m_priority_queue.top());
            m_priority_queue.pop();
            return true;
        }

        bool try_dequeue_if(reference& value,
                            std::function<bool(const_reference)> pred) {
            std::unique_lock<std::mutex> lock(m_priority_queue_mut);
            if (m_priority_queue.empty() || !pred(m_priority_queue.top())) {
                return false;
            }
            value = std::move(m_priority_queue.top());
            m_priority_queue.pop();
            return true;
        }

        void push(const_reference value) {
            std::unique_lock<std::mutex> lock(m_priority_queue_mut);
            m_priority_queue.push(value);
        }

        void push(value_type&& value) {
            std::unique_lock<std::mutex> lock(m_priority_queue_mut);
            m_priority_queue.emplace(value);
        }

        bool empty() {
            std::unique_lock<std::mutex> lock(m_priority_queue_mut);
            return m_priority_queue.empty();
        }

        void clean() {
            std::unique_lock<std::mutex> lock(m_priority_queue_mut);
            while (!m_priority_queue.empty()) m_priority_queue.pop();
        }

    private:
        std::priority_queue<value_type, container_type, Compare> m_priority_queue;
        std::mutex m_priority_queue_mut;
    };
}