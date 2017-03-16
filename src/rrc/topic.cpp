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
 *  @date 3/16/17
 */

#include <rrc/topic.h>


void rrc::topic::add_listener(rrc::topic_callback callback, const rrc::result_callback& result) {
    m_listeners_hash.emplace(std::move(callback));
    if (result) result(status::success);
}


void rrc::topic::remove_listener(rrc::topic_callback callback, const rrc::result_callback& result) {
    auto it = m_listeners_hash.find(callback);
    status stat = status::fail;
    if (it != m_listeners_hash.end()) {
        m_listeners_hash.erase(it);
        stat = status::success;
    }
    if (result) result(stat);
}


void rrc::topic::send_message(const rrc::shared_buffer& msg) {
    for (auto&& listener : m_listeners_hash) {
        listener(msg);
    }
}


bool rrc::topic::has_listeners() const {
    return !m_listeners_hash.empty();
}
