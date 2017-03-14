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
#include "task_scheduler.h"

namespace rrc {
    /**
     * @brief This launcher implimentation uses only one thread to run all the nodes.
     */
    class lockfree_launcher : public abstract_launcher {
    public:
        /**
         * @brief Default constructor of Linear Launcher
         */
        lockfree_launcher(std::chrono::steady_clock::duration sleep_duration = std::chrono::milliseconds(1))
                : m_finished(true),
                  m_sleep_duration(sleep_duration) {}
        /**
         * @brief Linear Launcher destructor
         */
        virtual ~lockfree_launcher() override;

        /**
        * @brief Virtual function for running the launcher
        * @return Status code of pragram state: 0 if succeed
        */
        virtual int run() override;

        /**
        * @brief Virtual function for running one step of launcher execution
        * @return True if succeed, otherwise false
        */
        virtual bool step() override;

        /**
         * @brief Stops the execution of launcher
         */
        virtual void stop() override;

        virtual void finalize() override;

        virtual void enqueue_user_task(task_queue::task_type task) override;

        virtual void enqueue_user_task_at(std::chrono::steady_clock::time_point tp,
                                          task_queue::task_type task) override;

        virtual void enqueue_user_task_for(std::chrono::steady_clock::duration duration,
                                           task_queue::task_type task) override;

        virtual void enqueue_sync_task(task_queue::task_type task) override;

        virtual void enqueue_sync_task_at(std::chrono::steady_clock::time_point tp,
                                          task_queue::task_type task) override;

        virtual void enqueue_sync_task_for(std::chrono::steady_clock::duration duration,
                                           task_queue::task_type task) override;

        virtual void enqueue_finalize_task(task_queue::task_type task) override;

        virtual bool is_multithreading() const override;

    private:
        bool exec_current_tasks(task_scheduler& scheduler);

    private:
        std::atomic<bool> m_finished;
        std::chrono::steady_clock::duration m_sleep_duration;
        lockfree_task_queue m_finalize_queue;
        task_scheduler m_user_scheduler;
        task_scheduler m_sync_scheduler;

    };
}


