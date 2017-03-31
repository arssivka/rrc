/**
 *  @autor arssivka
 *  @date 3/31/17
 */

#pragma once


#include <concurrentqueue.h>
#include "abstract_launcher.h"

namespace rrc {
    template <size_t N>
    class node {
    public:
        constexpr static size_t queues_count = N;

        node(abstract_launcher& launcher, size_t max_iter_count = 64)
                : m_launcher(launcher),
                  m_changes_enqueued_flag(ATOMIC_FLAG_INIT),
                  m_max_iter_count(max_iter_count) {}


    protected:
        template <class... Args>
        inline void enqueue_task(size_t queue_num,
                                 const std::function<void()>& task,
                                 Args&&... args) {
            m_local_queues[queue_num].enqueue(
                    std::move(task),
                    std::forward<Args>(args)...
            );
            this->enqueue_changes();
        };

        template <class Func, class... Args>
        inline void enqueue_task_at(std::chrono::steady_clock::time_point tp,
                             Func&& func, Args... args) {
            m_launcher.enqueue_task_at(tp, std::bind(std::forward<Func>, std::forward<Args>(args)...));
        };

        template <class Func, class... Args>
        inline void enqueue_task_for(std::chrono::steady_clock::duration duration,
                              Func&& func, Args... args) {
            m_launcher.enqueue_task_for(duration, std::bind(std::forward<Func>, std::forward<Args>(args)...));
        };

        inline void enqueue_changes() {
            if (m_changes_enqueued_flag.test_and_set(std::memory_order_acquire)) {
                m_launcher.enqueue_task([this] {
                    this->apply_changes();
                });
            }
        }

        void apply_changes() {
            m_changes_enqueued_flag.clear(std::memory_order_release);
            bool need_enqueue = false;
            std::function<void()> task;
            for (auto&& queue : m_local_queues) {
                bool finished = false;
                for (size_t i = 0; i < m_max_iter_count; ++i) {
                    if (!queue.try_dequeue(task)) {
                        finished = true;
                        break;
                    } else {
                        task();
                    }
                }
                if (!finished) {
                    need_enqueue = true;
                }
            }
            if (need_enqueue) {
                this->enqueue_changes();
            }
        }

        inline size_t max_iter_count() const noexcept {
            return m_max_iter_count;
        }

        inline void set_max_iter_count(size_t max_iter_count) noexcept {
            m_max_iter_count = max_iter_count;
        }

    private:
        typedef moodycamel::ConcurrentQueue<std::function<void()>> queue_type;

        abstract_launcher& m_launcher;
        std::array<queue_type, queues_count> m_local_queues;
        std::atomic_flag m_changes_enqueued_flag;
        size_t m_max_iter_count;

    };
}