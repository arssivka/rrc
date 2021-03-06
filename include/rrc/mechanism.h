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
#pragma once


#include "non_copyable.h"
#include "abstract_launcher.h"
#include "lockfree_task_queue.h"
#include <type_traits>

namespace rrc {
    template<class T, size_t N>
    class mechanism : private non_copyable {
    protected:
        static constexpr size_t queues_count = N;
        typedef std::function<void()> task_type;
        typedef moodycamel::ConcurrentQueue<task_type> task_queue_type;
        typedef T base_type;

        template<class... Args>
        mechanism(abstract_launcher& launcher, Args&& ... args)
                : m_base(std::forward<Args>(args)...),
                  m_launcher(launcher),
                  m_changes_enqueued_flag(ATOMIC_FLAG_INIT),
                  m_exec_vector(64) {}

        template<size_t I, class Func, class... Args>
        inline void enqueue_task(Func&& func, Args&& ... args) {
            static_assert(I < queues_count, "Incorrect queue index");
            m_local_queues[I].enqueue(
                    std::bind(std::forward<Func>(func), &m_base, std::forward<Args>(args)...)
            );
            this->enqueue_changes();
        };

        template<class Func, class... Args>
        inline auto call(Func&& func, Args&& ... args)
                -> typename std::result_of<Func(base_type*, Args...)>::type {
            return func(&m_base, std::forward<Args>(args)...);
        };

        template<class Func, class... Args>
        inline auto call(Func&& func, Args&& ... args) const
                -> typename std::result_of<Func(base_type*, Args...)>::type {
            return func(&m_base, std::forward<Args>(args)...);
        };

        inline void enqueue_changes() {
            if (m_changes_enqueued_flag.test_and_set(std::memory_order_acquire)) {
                m_launcher.enqueue_sync_task([this] {
                    this->apply_changes();
                });
            }
        }

        void apply_changes() {
            m_changes_enqueued_flag.clear(std::memory_order_release);
            bool need_enqueue = false;
            size_t dequeued;
            for (auto&& queue : m_local_queues) {
                dequeued = queue.try_dequeue_bulk(m_exec_vector.begin(),
                                                  m_exec_vector.size());
                for (size_t i = 0; i < dequeued; ++i) {
                    m_exec_vector[i]();
                }

                if (dequeued == m_exec_vector.size()) {
                    need_enqueue = true;
                }
            }
            if (need_enqueue) {
                this->enqueue_changes();
            }
        }

    private:
        base_type m_base;
        abstract_launcher& m_launcher;
        std::atomic_flag m_changes_enqueued_flag;
        std::array<task_queue_type, queues_count> m_local_queues;
        std::vector<task_type> m_exec_vector;
    };
}