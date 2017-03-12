/**
 *  @autor arssivka
 *  @date 2/24/17
 */
#include "include/rrc/task_scheduler.h"

void rrc::task_scheduler::enqueue(task_type task) {
    m_task_queue.enqueue(std::move(task));
}

void rrc::task_scheduler::enqueue(std::chrono::steady_clock::time_point tp,
                                  task_type task) {
    if (tp <= std::chrono::steady_clock::now()) {
        m_task_queue.enqueue(std::move(task));
    } else {
        m_task_queue.enqueue([this, tp, task_cap = std::move(task)]() mutable {
            if (tp <= std::chrono::steady_clock::now()) {
                task_cap();
                return;
            }
            m_pending_tasks_queue.push({tp, std::move(task_cap)});
        });
    }
}

bool rrc::task_scheduler::try_dequeue(task_type& task) {
    std::pair<std::chrono::steady_clock::time_point, task_type> scheduled_task;
    if (m_pending_tasks_queue.try_dequeue_if(scheduled_task,
                                                [](const pending_task_type& task) {
                                                    auto& tp = task.first;
                                                    return tp <= std::chrono::steady_clock::now();
                                                })) {
        task = std::move(scheduled_task.second);
        return true;
    }
    return m_task_queue.try_dequeue(task);
}

