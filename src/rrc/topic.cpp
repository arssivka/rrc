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


bool rrc::topic::add_listener(rrc::topic_callback callback, const rrc::result_callback& result) {
    if (m_notifier.add_listener(std::move(callback), result)) {
        m_listeners_count.fetch_add(1);
        return true;
    }
    return false;
}


bool rrc::topic::remove_listener(rrc::topic_callback callback, const rrc::result_callback& result) {
    if (m_notifier.remove_listener(std::move(callback), result)) {
        m_listeners_count.fetch_sub(1);
        return true;
    }
    return false;
}


void rrc::topic::send_message(const rrc::shared_buffer& msg) {
    m_notifier.notify(msg);
}


size_t rrc::topic::listeners_count() const {
    return m_listeners_count.load(std::memory_order_acquire);
}

rrc::topic::topic()
        : m_listeners_count(0) {}

rrc::topic::topic(const rrc::topic& rhs)
        : m_notifier(rhs.m_notifier), m_listeners_count(m_notifier.size()) {}

rrc::topic::topic(rrc::topic&& rhs)
        : m_notifier(std::move(rhs.m_notifier)), m_listeners_count(m_notifier.size()) {}
