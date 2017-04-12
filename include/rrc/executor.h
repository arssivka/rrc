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
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @autor arssivka
 *  @date 4/9/17
 */

#pragma once

#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>
#include "thread_group.h"

namespace rrc {
    class node;

    class executor {
    public:

        executor(size_t num_of_threads,
                      std::chrono::steady_clock::duration loop_min_dur = std::chrono::seconds(0));

        void add_node(node* node_ptr);

        void start() {
            {
                std::lock_guard<std::mutex> lock(m_mut);
                m_stop_flag = false;
            }
            m_node_cv.notify_all();
        }

        void stop() {
            {
                std::lock_guard<std::mutex> lock(m_mut);
                m_stop_flag = true;
            }
        }

        executor(const executor&) = delete;

        executor& operator=(const executor&) = delete;

        ~executor();

    private:
        std::mutex m_mut;
        std::condition_variable m_node_cv;
        std::queue<node*> m_node_queue;
        thread_group m_workers;
        std::chrono::steady_clock::duration m_loop_min_duration;
        bool m_finished_flag;
        bool m_stop_flag;
    };
}


