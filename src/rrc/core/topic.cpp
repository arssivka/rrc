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
 *  @date 8/24/16
 */

#include <rrc/core/topic.h>
#include <algorithm>


void rrc::topic::add_listener(std::shared_ptr<rrc::topic::subscriber_type> listener_ptr) {
    m_listeners_list.push_front(std::move(listener_ptr));
}

void rrc::topic::remove_listener(std::shared_ptr<rrc::topic::subscriber_type> listener_ptr) {
    m_listeners_list.remove(listener_ptr);
}

void rrc::topic::send_message(rrc::topic::message_type message) {
    m_listeners_list.erase(std::remove_if(m_listeners_list.begin(), m_listeners_list.end(),
                           [message_cap = std::move(message)]
                                   (std::shared_ptr<subscriber_type>& listener_ptr) mutable {
        return !listener_ptr->enqueue_task(std::move(message_cap));
    }), m_listeners_list.end());
}

bool rrc::topic::has_listeners() const {
    return !m_listeners_list.empty();
}