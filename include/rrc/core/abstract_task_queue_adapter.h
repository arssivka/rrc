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
 *  @date 7/20/16
 */

#pragma once


#include <atomic>
#include "abstract_queue_adapter.h"
#include "defines.h"

namespace rrc {
    class abstract_task_queue_adapter : public abstract_queue_adapter<task> {
    public:
        /**
         * @brief Enques function object with it's args
         * @param func function object
         * @param args Arguments for the function object
         */
         template <class Func, class... Args>
        void enqueue_task(Func&& func, Args... args) {
            this->enqueue(std::bind(std::forward<Func>(func),
                                         std::forward<Args>(args)...));
        }

        /**
         * @brief Executes one Task from queue
         * @return True if succeed otherwise false
         */
        bool exec_once();

        /**
         * @brief Executes all Tasks from queue
         */
        void exec_all();
    };
}


