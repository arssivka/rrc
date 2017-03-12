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
 *  @date 7/8/16
 */

#pragma once


#include <chrono>
#include "task_queue.h"

namespace rrc {
    class task_queue;

    class abstract_launcher {
    public:
        /**
         * @brief Virtual destructor of abstract launcher
         */
        virtual ~abstract_launcher() { }

        /**
         * @brief Virtual function for running the launcher
         * @return Status code of program state: 0 if succeed
         */
        virtual int run() = 0;

        virtual bool step() = 0;

        /**
         * @brief Stops the execution of launcher
         */
        virtual void stop() = 0;

        virtual void enqueue_user_task(task_queue::task_type task) = 0;

        virtual void enqueue_user_task_at(std::chrono::steady_clock::time_point tp, task_queue::task_type task) = 0;

        virtual void enqueue_user_task_for(std::chrono::steady_clock::duration duration, task_queue::task_type task) = 0;

        virtual void enqueue_sync_task(task_queue::task_type task) = 0;

        virtual void enqueue_sync_task_at(std::chrono::steady_clock::time_point tp, task_queue::task_type task) = 0;

        virtual void enqueue_sync_task_for(std::chrono::steady_clock::duration duration, task_queue::task_type task) = 0;

        virtual void enqueue_finalize_task(task_queue::task_type task) = 0;

        virtual bool is_multithreading() const = 0;

        virtual void finalize() = 0;

    };

}


