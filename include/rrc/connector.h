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

#pragma once


#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <set>
#include "communication_connection.h"
#include "execution_connection.h"

namespace rrc {
    class node;
    class executor;

    class connector {
    public:
        connector();

        std::vector<communication_connection> apply_communication_connections();

        std::vector<execution_connection> apply_execution_connections();

        bool add_node(const std::string& name,
                      node* node_ptr);

        bool remove_node(const std::string& name);

        bool add_executor(const std::string& name,
                          executor* exec_ptr);

        bool remove_executor(const std::string& name);

        void clear_nodes() noexcept;

        void clear_executors() noexcept;

        void connect_sender(const std::string& node_name,
                            const std::string& sender_name,
                            const std::string& topic_name);

        void connect_receiver(const std::string& node_name,
                              const std::string& receiver_name,
                              const std::string& topic_name);

        void direct_connect(const std::string& src_node_name,
                            const std::string& sender_name,
                            const std::string& dst_node_name,
                            const std::string& receiver_name);

        void attach_node(const std::string& node_name,
                         const std::string& exec_name);

        void clear_connections() noexcept;

        void clear() noexcept;

    private:
        std::unordered_map<std::string, node*> m_node_hash;
        std::unordered_map<std::string, executor*> m_executor_hash;
        std::multimap<std::string, std::pair<std::string, std::string>> m_output_connections;
        std::multimap<std::string, std::pair<std::string, std::string>> m_input_connections;
        std::set<std::tuple<std::string, std::string, std::string, std::string>> m_connections;
        std::map<std::string, std::string> m_executor_connections;
    };
}


