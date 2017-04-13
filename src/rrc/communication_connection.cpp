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

#include "rrc/communication_connection.h"


rrc::communication_connection::communication_connection(const std::string& src_node,
                                                        const std::string& sender,
                                                        const std::string& dst_node,
                                                        const std::string& receiver)
        : m_src_node(src_node), m_sender(sender), m_dst_node(dst_node), m_receiver(receiver) {}


const std::string& rrc::communication_connection::src_node() const {
    return m_src_node;
}


void rrc::communication_connection::set_src_node(const std::string& src_node) {
    m_src_node = src_node;
}


const std::string& rrc::communication_connection::sender() const {
    return m_sender;
}


void rrc::communication_connection::set_sender(const std::string& sender) {
    m_sender = sender;
}


const std::string& rrc::communication_connection::dst_node() const {
    return m_dst_node;
}


void rrc::communication_connection::set_dst_node(const std::string& dst_node) {
    m_dst_node = dst_node;
}


const std::string& rrc::communication_connection::receiver() const {
    return m_receiver;
}


void rrc::communication_connection::set_receiver(const std::string& receiver) {
    m_receiver = receiver;
}

