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
 *  @date 3/31/17
 */

#pragma once


#include <atomic>
#include "abstract_launcher.h"

namespace rrc {
    class enqueue_once {
    public:
        enqueue_once(abstract_launcher& launcher);

        template <class Func, class... Args>
        bool enqueue(Func&& func, Args&&... args) {
            if (!m_enqueued_flag.test_and_set(std::memory_order_acquire)) {
                m_func = std::bind(std::forward<Func>(func), std::forward<Args>(args)...);
                m_launcher.enqueue_task(std::bind(&enqueue_once::exec, this));
                return true;
            }
            return false;
        }


    private:
        void exec();


    private:
        abstract_launcher& m_launcher;
        std::atomic_flag m_enqueued_flag;
        std::function<void()> m_func;
    };
}


