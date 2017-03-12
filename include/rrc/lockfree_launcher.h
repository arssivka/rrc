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

#pragma once


#include <forward_list>
#include <condition_variable>
#include "abstract_launcher.h"
#include "node.h"
#include "task_scheduler.h"
#include "barrier.h"

namespace rrc {
    namespace {
        using namespace std::chrono_literals;
    }

    /**
     * @brief This launcher implimentation uses only one thread to run all the nodes.
     */
    class lockfree_launcher : public abstract_launcher {
    public:
        /**
         * @brief Default constructor of Linear Launcher
         */
        lockfree_launcher(std::chrono::steady_clock::duration sleep_duration = 1ms)
                : m_finished(true),
                  m_sleep_duration(sleep_duration) {}

        /**
         * @brief Linear Launcher destructor
         */
        virtual ~lockfree_launcher() override {}

        /**
        * @brief Virtual function for running the launcher
        * @return Status code of pragram state: 0 if succeed
        */
        virtual int run() override {
            m_finished.store(false, std::memory_order_release);
            while (!m_finished.load(std::memory_order_acquire)) {
                if (!this->step()) {
                    std::this_thread::sleep_for(m_sleep_duration);
                }
            }
            this->finalize();
            return EXIT_SUCCESS;
        }

        /**
        * @brief Virtual function for running one step of launcher execution
        * @return True if succeed, otherwise false
        */
        virtual bool step() override {
            task_scheduler::task_type task;
            bool executed = false;
            executed |= this->exec_current_tasks(m_sync_scheduler);
            executed |= this->exec_current_tasks(m_user_scheduler);
            return executed;
        }

        /**
         * @brief Stops the execution of launcher
         */
        virtual void stop() override {
            m_finished.store(true, std::memory_order_release);
        }

        virtual void finalize() override {
            m_finalize_queue.exec_all();
        }

        virtual void enqueue_user_task(task_queue::task_type task) override {
            m_user_scheduler.enqueue(std::move(task));
        }

        virtual void enqueue_user_task_at(std::chrono::steady_clock::time_point tp,
                                          task_queue::task_type task) override {
            m_user_scheduler.enqueue(tp, std::move(task));
        }

        virtual void enqueue_user_task_for(std::chrono::steady_clock::duration duration,
                                           task_queue::task_type task) override {
            m_user_scheduler.enqueue(std::chrono::steady_clock::now() + duration, std::move(task));
        }

        virtual void enqueue_sync_task(task_queue::task_type task) override {
            m_sync_scheduler.enqueue(std::move(task));
        }

        virtual void enqueue_sync_task_at(std::chrono::steady_clock::time_point tp,
                                          task_queue::task_type task) override {
            m_sync_scheduler.enqueue(tp, std::move(task));
        }

        virtual void enqueue_sync_task_for(std::chrono::steady_clock::duration duration,
                                           task_queue::task_type task) override {
            m_sync_scheduler.enqueue(std::chrono::steady_clock::now() + duration, std::move(task));
        }

        virtual void enqueue_finalize_task(task_queue::task_type task) override {
            m_finalize_queue.enqueue(std::move(task));
        }

        virtual bool is_multithreading() const override {
            return false;
        }

    private:
        bool exec_current_tasks(task_scheduler& scheduler) {
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

    private:
        std::atomic<bool> m_finished;
        std::chrono::steady_clock::duration m_sleep_duration;
        lockfree_task_queue m_finalize_queue;
        task_scheduler m_user_scheduler;
        task_scheduler m_sync_scheduler;

    };
}


