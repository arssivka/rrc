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
 *  @date 2/26/17
 */
#pragma once


#include <vector>
#include <chrono>
#include <iostream>
#include "abstract_launcher.h"

namespace rrc {
    class core_base {
    public:
        core_base(abstract_launcher& launcher, int argc, char** argv);

        const std::vector<std::string>& args() const noexcept;

        template <class Func, class... Args>
        void enqueue_task(Func&& func, Args... args) {
            m_launcher.enqueue_task(std::bind(std::forward<Func>, std::forward<Args>(args)...));
        };

        template <class Func, class... Args>
        void enqueue_task_at(std::chrono::steady_clock::time_point tp,
                             Func&& func, Args... args) {
            m_launcher.enqueue_task_at(tp, std::bind(std::forward<Func>, std::forward<Args>(args)...));
        };

        template <class Func, class... Args>
        void enqueue_task_for(std::chrono::steady_clock::duration duration,
                              Func&& func, Args... args) {
            m_launcher.enqueue_task_for(duration, std::bind(std::forward<Func>, std::forward<Args>(args)...));
        };

        void stop();

    private:
        abstract_launcher& m_launcher;
        std::vector<std::string> m_args;

    };
}