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
 *  @date 3/21/17
 */

#include <rrc/shared_buffer_pool.h>


rrc::shared_buffer_pool::shared_buffer_pool(size_t max_obj_count)
        : m_max_obj_count(max_obj_count) {}


rrc::shared_buffer rrc::shared_buffer_pool::create(size_t size) {
    if (size == 0) return shared_buffer();
    auto it = m_buffer_map.upper_bound(size);
    if (it != m_buffer_map.end()) {
        shared_buffer buff = std::move(it->second);
        m_buffer_map.erase(it);
        return buff;
    }
    return shared_buffer(size);
}


void rrc::shared_buffer_pool::remove(rrc::shared_buffer buff) {
    if (buff == nullptr) return;
    if (m_max_obj_count == 0 ||
        (m_buffer_map.size() >= m_max_obj_count &&
         buff.size() > m_buffer_map.begin()->first)) {
        m_buffer_map.emplace(buff.size(), std::move(buff));
    }

    if (m_max_obj_count != 0) {
        while (m_buffer_map.size() > m_max_obj_count) {
            m_buffer_map.erase(m_buffer_map.begin());
        }
    }
}


size_t rrc::shared_buffer_pool::max_objects_count() const {
    return m_max_obj_count;
}


void rrc::shared_buffer_pool::set_max_objects_count(size_t max_objects_count) {
    if (max_objects_count == 0) {
        m_max_obj_count = 0;
        return;
    }
    long diff = m_max_obj_count - max_objects_count;
    while (diff > 0) {
        m_buffer_map.erase(m_buffer_map.begin());
        --diff;
    }
    m_max_obj_count = max_objects_count;
}
