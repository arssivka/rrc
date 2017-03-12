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
 *  @date 2/24/17
 */
#pragma once


#include <functional>

namespace rrc {
    class task_queue {
    public:
        typedef std::function<void()> task_type;

        virtual void enqueue(task_type task) = 0;

        virtual bool try_exec() = 0;

        virtual bool try_dequeue(task_type& task) = 0;

        void exec_all()  {
            while (this->try_exec());
        }

        virtual void clean() = 0;

        virtual ~task_queue() {}
    };
}
