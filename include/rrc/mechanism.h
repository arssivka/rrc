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
#include "concurrent_task_queue.h"
#include <type_traits>

namespace rrc {
    template<class T, class Q, size_t N>
    class mechanism : private non_copyable {
    protected:
        static constexpr size_t queues_count = N;
        typedef T base_type;
        typedef Q queue_type;

        template<class... Args>
        mechanism(abstract_launcher& launcher, Args&& ... args)
                : m_base(std::forward<Args>(args)...),
                  m_launcher(launcher),
                  m_changes_enqueued_flag(ATOMIC_FLAG_INIT) {}

        template<size_t I, class Func, class... Args>
        inline void enqueue_task(size_t num_local_queue, Func&& func, Args&& ... args) {
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

//        template<class Func, class... Args>
//        inline void exec(Func&& func, Args&& ... args) const {
//            func(&m_base, std::forward<Args>(args)...);
//        };
//
//        template<class Func, class... Args>
//        inline void exec(Func&& func, Args&& ... args) {
//            func(&m_base, std::forward<Args>(args)...);
//        };

        inline void enqueue_changes() {
            if (m_changes_enqueued_flag.test_and_set(std::memory_order_acquire)) {
                m_launcher.enqueue_sync_task([this] {
                    this->apply_changes();
                });
            }
        }

        void apply_changes() {
            m_changes_enqueued_flag.clear(std::memory_order_release);
            for (auto&& queue : m_local_queues) {
                bool flag = false;
                queue.enque([&flag] {
                    flag = true;
                });
                while (!flag && queue.try_exec());
            }
        }

    private:
        base_type m_base;
        abstract_launcher& m_launcher;
        std::atomic_flag m_changes_enqueued_flag;
        std::array<queue_type, queues_count> m_local_queues;
    };
}