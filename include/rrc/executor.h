/**
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


