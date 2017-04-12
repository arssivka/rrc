/**
 *  @autor arssivka
 *  @date 4/9/17
 */

#include "rrc/executor.h"
#include "rrc/node.h"

rrc::executor::executor(size_t num_of_threads,
                                  std::chrono::steady_clock::duration loop_min_dur)
        : m_workers(num_of_threads),
          m_loop_min_duration(loop_min_dur),
          m_finished_flag(false),
          m_stop_flag(true) {
    using namespace std::chrono;

    num_of_threads = m_workers.size();
    for (size_t i = 0; i < num_of_threads; ++i) {
        m_workers.add_thread(std::thread([this, i] {
            steady_clock::time_point tp = steady_clock::now();
            std::unique_lock<std::mutex> lock(m_mut);
            while (true) {
                m_node_cv.wait(lock, [this] {
                    return (!m_stop_flag && !m_node_queue.empty()) || m_finished_flag;
                });
                if (m_finished_flag) return;
                node* cur_node = m_node_queue.front();
                auto now = steady_clock::now();
                auto next_tp = tp + m_loop_min_duration;
                m_node_queue.pop();
                lock.unlock();
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
        }));
    }
}

void rrc::executor::add_node(rrc::node* node_ptr) {
    if (node_ptr == nullptr) return;
    {
        std::lock_guard<std::mutex> lock(m_mut);
        m_node_queue.push(node_ptr);
    }
    m_node_cv.notify_one();
}

rrc::executor::~executor() {
    {
        std::lock_guard<std::mutex> lock(m_mut);
        m_finished_flag = true;
    }
    m_node_cv.notify_all();
    m_workers.join_all();
}
