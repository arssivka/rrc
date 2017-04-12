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
 *  @date 4/8/17
 */

#include "rrc/node.h"
#include "rrc/sender.h"


void rrc::node::add_sender(const std::string& key, rrc::sender* sender_ptr) {
    m_senders_hash.emplace(std::make_pair(key, sender_ptr));
}


void rrc::node::add_receiver(const std::string& key, rrc::receiver* receiver_ptr) {
    m_receivers_hash.insert(std::make_pair(key, receiver_ptr));
}


rrc::sender* rrc::node::find_sender(const std::string& key) const noexcept {
    auto iter = m_senders_hash.find(key);
    if (iter != m_senders_hash.end()) return iter->second;
    return nullptr;
}


rrc::receiver* rrc::node::find_receiver(const std::string& key) const noexcept {
    auto iter = m_receivers_hash.find(key);
    if (iter != m_receivers_hash.end()) return iter->second;
    return nullptr;
}


void rrc::node::on_init() {}


void rrc::node::on_start() {}


void rrc::node::on_finish() {}


void rrc::node::on_process() {}


rrc::node::~node() {}
