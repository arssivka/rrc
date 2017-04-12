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
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @autor arssivka
 *  @date 4/9/17
 */

#pragma once


#include <thread>
#include <vector>

namespace rrc {
    class thread_group {
    public:
        thread_group(size_t reserve = 1);

        template <class Func>
        void create_thread(Func&& func) {
            m_threads.emplace_back(std::forward<Func>(func));
        }

        void add_thread(std::thread&& thread);

        bool joinable() const noexcept;

        void join_all();

        size_t size() const noexcept;

        void reserve(size_t size);

        size_t capacity() const noexcept;

    private:
        std::vector<std::thread> m_threads;
    };
}


