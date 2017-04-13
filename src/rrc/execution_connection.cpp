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
 *  @date 4/13/17
 */

#include "rrc/execution_connection.h"


rrc::execution_connection::execution_connection(const std::string& node, const std::string& worker)
        : m_node(node), m_worker(worker) {}


const std::string& rrc::execution_connection::node() const {
    return m_node;
}


void rrc::execution_connection::set_node(const std::string& node) {
    m_node = node;
}


const std::string& rrc::execution_connection::worker() const {
    return m_worker;
}


void rrc::execution_connection::set_worker(const std::string& worker) {
    m_worker = worker;
}
