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
 *  @date 4/11/17
 */

#include "rrc/topic.h"
#include "rrc/receiver.h"
#include "rrc/sender.h"


void rrc::topic::add_sender(rrc::sender* sender_ptr) {
    m_senders.push_front(sender_ptr);
}


void rrc::topic::add_receiver(rrc::receiver* receiver_ptr) {
    m_receivers.push_front(receiver_ptr);
}


void rrc::topic::reset() {
    m_senders.clear();
    m_receivers.clear();
}


void rrc::topic::connect() {
    if (!m_senders.empty() && !m_receivers.empty()) {
        for (auto&& sender_ptr : m_senders) {
            for (auto&& receiver_ptr : m_receivers) {
                if (!sender_ptr->has_receiver(receiver_ptr)) {
                    sender_ptr->add_receiver(receiver_ptr);
                }
            }
        }
    }

    m_senders.clear();
    m_receivers.clear();
}
