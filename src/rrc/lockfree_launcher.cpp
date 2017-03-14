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
 *  @date 8/26/16
 */

#include <rrc/lockfree_launcher.h>





rrc::lockfree_launcher::~lockfree_launcher() {}


int rrc::lockfree_launcher::run() {
    m_finished.store(false, std::memory_order_release);
    while (!m_finished.load(std::memory_order_acquire)) {
        if (!this->step()) {
            std::this_thread::sleep_for(m_sleep_duration);
        }
    }
    this->finalize();
    return EXIT_SUCCESS;
}


bool rrc::lockfree_launcher::step() {
    task_scheduler::task_type task;
    bool executed = false;
    executed |= this->exec_current_tasks(m_sync_scheduler);
    executed |= this->exec_current_tasks(m_user_scheduler);
    return executed;
}


void rrc::lockfree_launcher::stop() {
    m_finished.store(true, std::memory_order_release);
}


void rrc::lockfree_launcher::finalize() {
    m_finalize_queue.exec_all();
}


void rrc::lockfree_launcher::enqueue_user_task(rrc::task_queue::task_type task) {
    m_user_scheduler.enqueue(std::move(task));
}


void rrc::lockfree_launcher::enqueue_user_task_at(std::chrono::steady_clock::time_point tp,
                                             rrc::task_queue::task_type task) {
    m_user_scheduler.enqueue(tp, std::move(task));
}


void rrc::lockfree_launcher::enqueue_user_task_for(std::chrono::steady_clock::duration duration,
                                                   rrc::task_queue::task_type task) {
    m_user_scheduler.enqueue(std::chrono::steady_clock::now() + duration, std::move(task));
}


void rrc::lockfree_launcher::enqueue_sync_task(rrc::task_queue::task_type task) {
    m_sync_scheduler.enqueue(std::move(task));
}


void rrc::lockfree_launcher::enqueue_sync_task_at(std::chrono::steady_clock::time_point tp,
                                                  rrc::task_queue::task_type task) {
    m_sync_scheduler.enqueue(tp, std::move(task));
}


void rrc::lockfree_launcher::enqueue_sync_task_for(std::chrono::steady_clock::duration duration,
                                                   rrc::task_queue::task_type task) {
    m_sync_scheduler.enqueue(std::chrono::steady_clock::now() + duration, std::move(task));
}


void rrc::lockfree_launcher::enqueue_finalize_task(rrc::task_queue::task_type task) {
    m_finalize_queue.enqueue(std::move(task));
}


bool rrc::lockfree_launcher::is_multithreading() const {
    return false;
}


bool rrc::lockfree_launcher::exec_current_tasks(rrc::task_scheduler& scheduler) {
    task_scheduler::task_type task;
    bool finished_flag = false;
    bool executed = false;
    auto flag_setter = [&finished_flag] {
        finished_flag = true;
    };
    scheduler.enqueue(flag_setter);
    while (true) {
        bool result = scheduler.try_dequeue(task);
        task();
        if (!finished_flag && result) {
            executed = true;
        } else {
            return executed;
        }
    }
}
