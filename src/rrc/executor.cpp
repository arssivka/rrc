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

#include "rrc/executor.h"
#include "rrc/node.h"

rrc::executor::executor(size_t num_of_threads,
                        std::chrono::steady_clock::duration loop_min_dur)
        : m_workers(num_of_threads),
          m_num_of_threads(num_of_threads != 0 ? num_of_threads : 1),
          m_start_flag(false),
          m_loop_min_dur(loop_min_dur) {}


void rrc::executor::add_node(rrc::node* node_ptr) {
    if (node_ptr != nullptr) {
        std::lock_guard<std::mutex> lock(m_mut);
        m_node_queue.push(node_ptr);
    } else {
        return;
    }
    m_node_cv.notify_one();
}


rrc::executor::~executor() {
    this->stop();
}


void rrc::executor::start() {
    using namespace std::chrono;

    if (m_start_flag) return;
    m_start_flag = true;

    for (size_t i = 0; i < m_num_of_threads; ++i) {
        m_workers.create_thread([this] {
            steady_clock::time_point tp = steady_clock::now();
            std::unique_lock<std::mutex> lock(m_mut);
            while (true) {
                m_node_cv.wait(lock, [this] {
                    return !m_start_flag || !m_node_queue.empty();
                });
                if (!m_start_flag) return;
                node* cur_node = m_node_queue.front();
                m_node_queue.pop();
                auto next_tp = tp + m_loop_min_dur;
                lock.unlock();
                auto now = steady_clock::now();
                cur_node->on_process();
                if (now >= next_tp) {
                    tp = now;
                } else {
                    tp = next_tp;
                    std::this_thread::sleep_until(next_tp);
                }
                lock.lock();
                m_node_queue.push(cur_node);
            }
        });
    }
}


void rrc::executor::stop() {
    if (m_start_flag) {
        {
            std::lock_guard<std::mutex> lock(m_mut);
            m_start_flag = false;
        }
        m_workers.join_all();
    }
}


size_t rrc::executor::num_of_threads() const {
    return m_num_of_threads;
}


void rrc::executor::set_num_of_threads(size_t num_of_threads) {
    if (num_of_threads == 0) num_of_threads = 1;
    if (num_of_threads != m_num_of_threads) {
        bool reset = m_start_flag;
        this->stop();
        m_num_of_threads = num_of_threads;
        if (reset) this->start();
    }
}


bool rrc::executor::started() const {
    return m_start_flag;
}


const std::chrono::steady_clock::duration& rrc::executor::loop_min_duration() const {
    return m_loop_min_dur;
}


void rrc::executor::set_loop_min_duration(const std::chrono::steady_clock::duration& loop_min_dur) {
    std::lock_guard<std::mutex> lock(m_mut);
    m_loop_min_dur = loop_min_dur;
}


bool rrc::executor::clean_nodes() {
    if (m_start_flag) return false;
    // TODO Change allocator
    m_node_queue = std::queue<node*>();
    return true;
}
