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

#include <algorithm>
#include "rrc/thread_group.h"

rrc::thread_group::thread_group(size_t reserve) {
    if (reserve == 0) reserve = 1;
    m_threads.reserve(reserve);
}

void rrc::thread_group::add_thread(std::thread&& thread) {
    m_threads.push_back(std::move(thread));
}

void rrc::thread_group::join_all() {
    for (auto&& thread : m_threads) {
        if (thread.joinable()) thread.join();
    }
}

size_t rrc::thread_group::size() const noexcept {
    return m_threads.size();
}


bool rrc::thread_group::joinable() const noexcept {
    for (auto&& thread : m_threads) {
        if (thread.joinable()) return true;
    }
    return false;
}


void rrc::thread_group::reserve(size_t size) {
    m_threads.reserve(size);
}


size_t rrc::thread_group::capacity() const noexcept {
    return m_threads.capacity();
}
