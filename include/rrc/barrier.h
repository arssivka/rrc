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
 *  @date 2/28/17
 */
#pragma once


#include <condition_variable>
#include <atomic>
#include "non_copyable.h"

namespace rrc {
    template <class M>
    class barrier : private non_copyable {
    public:
        typedef M mutex_type;

        barrier(unsigned int n)
                : m_num_of_threads(n), m_threads_waiting(0), m_waiting_flag(false) {
        }

        void wait() {
            if (m_threads_waiting.fetch_add(1) >= m_num_of_threads - 1) {
                {
                    std::unique_lock<mutex_type> lock(m_mutex);
                    m_waiting_flag = true;
                }
                m_wait_cv.notify_all();
                m_threads_waiting.store(0);
            } else {
                std::unique_lock<mutex_type> lock(m_mutex);
                m_wait_cv.wait(lock, [this] { return !m_waiting_flag; });
            }
        }

    private:
        const unsigned int m_num_of_threads;
        std::atomic<unsigned int> m_threads_waiting;
        bool m_waiting_flag;
        std::condition_variable m_wait_cv;
        mutex_type m_mutex;
    };
}
