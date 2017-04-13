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

#include <algorithm>
#include "rrc/connector.h"
#include "rrc/topic.h"
#include "rrc/node.h"
#include "rrc/sender.h"
#include "rrc/executor.h"


rrc::connector::connector() {}


std::vector<rrc::communication_connection> rrc::connector::apply_communication_connections() {
    std::unordered_map<std::string, topic> topics;
    std::vector<communication_connection> failed_connections;

    for (auto&& connection : m_input_connections) {
        auto& node_name = connection.second.first;
        auto& receiver_name = connection.second.second;
        auto& topic_name = connection.first;

        auto node_it = m_node_hash.find(node_name);
        if (node_it == m_node_hash.end()) continue;
        node* node_ptr = node_it->second;

        receiver* receiver_ptr = node_ptr->find_receiver(receiver_name);
        if (receiver_ptr == nullptr) {
            auto range = m_output_connections.equal_range(topic_name);
            std::for_each(range.first, range.second, [&](const auto& pair) {
                failed_connections.emplace_back(
                        pair.second.first,
                        pair.second.second,
                        node_name,
                        receiver_name
                );
            });
            continue;
        }

        auto topic_it = topics.find(topic_name);
        if (topic_it == topics.end()) {
            topic_it = topics.emplace(topic_name, topic()).first;
        }

        topic_it->second.add_receiver(receiver_ptr);
    }

    for (auto&& connection : m_output_connections) {
        auto& node_name = connection.second.first;
        auto& sender_name = connection.second.second;
        auto& topic_name = connection.first;

        auto node_it = m_node_hash.find(node_name);
        if (node_it == m_node_hash.end()) continue;
        node* node_ptr = node_it->second;

        sender* sender_ptr = node_ptr->find_sender(sender_name);
        if (sender_ptr == nullptr) {
            auto range = m_input_connections.equal_range(topic_name);
            std::for_each(range.first, range.second, [&](const auto& pair) {
                failed_connections.emplace_back(
                        node_name,
                        sender_name,
                        pair.second.first,
                        pair.second.second
                );
            });
            continue;
        }

        auto topic_it = topics.find(topic_name);
        if (topic_it == topics.end()) {
            topic_it = topics.emplace(topic_name, topic()).first;
        }

        topic_it->second.add_sender(sender_ptr);
    }

    for (auto&& connection : m_connections) {
        auto& src_node_name = std::get<0>(connection);
        auto& sender_name = std::get<1>(connection);
        auto& dst_node_name = std::get<2>(connection);
        auto& receiver_name = std::get<3>(connection);

        auto node_it = m_node_hash.find(src_node_name);
        if (node_it == m_node_hash.end()) {
            communication_connection conn = {
                    src_node_name,
                    sender_name,
                    dst_node_name,
                    receiver_name
            };

            failed_connections.emplace_back(

            );
            continue;
        }
        node* src_node_ptr = node_it->second;

        node_it = m_node_hash.find(dst_node_name);
        if (node_it == m_node_hash.end()) {
            failed_connections.emplace_back(
                    src_node_name,
                    sender_name,
                    dst_node_name,
                    receiver_name
            );
            continue;
        }
        node* dst_node_ptr = node_it->second;

        sender* sender_ptr = src_node_ptr->find_sender(sender_name);
        if (sender_ptr == nullptr) {
            failed_connections.emplace_back(
                    src_node_name,
                    sender_name,
                    dst_node_name,
                    receiver_name
            );
            continue;
        }

        receiver* receiver_ptr = dst_node_ptr->find_receiver(receiver_name);
        if (receiver_ptr == nullptr) {
            failed_connections.emplace_back(
                    src_node_name,
                    sender_name,
                    dst_node_name,
                    receiver_name
            );
            continue;
        }

        if (!sender_ptr->has_receiver(receiver_ptr))
            sender_ptr->add_receiver(receiver_ptr);
    }

    for (auto&& topic_pair : topics) {
        topic_pair.second.connect();
    }

    return failed_connections;
}


std::vector<rrc::execution_connection> rrc::connector::apply_execution_connections() {
    std::vector<execution_connection> failed_connections;
    for (auto&& connection : m_executor_connections) {
        auto& node_name = connection.first;
        auto& exec_name = connection.second;

        auto node_it = m_node_hash.find(node_name);
        auto exec_it = m_executor_hash.find(exec_name);
        if (node_it == m_node_hash.end() ||
            exec_it == m_executor_hash.end()) {
            failed_connections.emplace_back(node_name, exec_name);
            continue;
        }

        exec_it->second->add_node(node_it->second);
    }
}


bool rrc::connector::add_node(const std::string& name,
                              rrc::node* node_ptr) {
    if (m_node_hash.find(name) == m_node_hash.end()) {
        m_node_hash.insert({name, node_ptr});
        return true;
    }
    return false;
}


void rrc::connector::connect_sender(const std::string& node_name,
                                    const std::string& sender_name,
                                    const std::string& topic_name) {
    m_output_connections.emplace(node_name, std::make_pair(sender_name, topic_name));
}


void rrc::connector::connect_receiver(const std::string& node_name,
                                      const std::string& receiver_name,
                                      const std::string& topic_name) {

    m_input_connections.emplace(node_name, std::make_pair(receiver_name, topic_name));
}


void rrc::connector::direct_connect(const std::string& src_node_name,
                                    const std::string& sender_name,
                                    const std::string& dst_node_name,
                                    const std::string& receiver_name) {
    m_connections.emplace(src_node_name, sender_name, dst_node_name, receiver_name);
}


void rrc::connector::attach_node(const std::string& node_name,
                                 const std::string& exec_name) {
    m_executor_connections.emplace(node_name, exec_name);
}


bool rrc::connector::add_executor(const std::string& name, rrc::executor* exec_ptr) {
    if (m_executor_hash.find(name) == m_executor_hash.end()) {
        m_executor_hash.emplace(name, exec_ptr);
        return true;
    }
    return false;
}


bool rrc::connector::remove_node(const std::string& name) {
    auto it = m_node_hash.find(name);
    if (it == m_node_hash.end()) return false;
    m_node_hash.erase(it);
    return true;
}


bool rrc::connector::remove_executor(const std::string& name) {
    auto it = m_executor_hash.find(name);
    if (it == m_executor_hash.end()) return false;
    m_executor_hash.erase(it);
    return true;
}


void rrc::connector::clear_nodes() noexcept {
    m_node_hash.clear();
}


void rrc::connector::clear_executors() noexcept {
    m_executor_hash.clear();
}


void rrc::connector::clear_connections() noexcept {
    m_output_connections.clear();
    m_input_connections.clear();
    m_connections.clear();
    m_executor_connections.clear();
}


void rrc::connector::clear() noexcept {
    this->clear_nodes();
    this->clear_executors();
    this->clear_connections();
}
