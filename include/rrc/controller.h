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


#include <functional>
#include <memory>
#include <regex>
#include <boost/property_tree/ptree.hpp>
#include "connector.h"
#include "shared_library.h"
#include "executor.h"
#include "node.h"

namespace rrc {
    class controller {
    public:
        bool read_config(const std::string& filename);

        void start();

        void stop();

        bool load_node(const std::string& node_name,
                       const std::string& filename);

        bool connect_sender(const std::string& node_name,
                            const std::string& sender_name,
                            const std::string& topic_name);

        bool connect_receiver(const std::string& node_name,
                            const std::string& receiver_name,
                            const std::string& topic_name);

        bool create_executor(const std::string& name,
                             size_t num_of_threads = 1,
                             std::chrono::steady_clock::duration loop_min_dur = std::chrono::seconds(0));

        bool attach_node(const std::string& node_name,
                         const std::string exec_name);

    private:
        static bool is_name_valid(const std::string& name);

        bool apply_properties(const boost::property_tree::ptree& prop);

        bool apply_thread_properties(const boost::property_tree::ptree& prop);

        bool apply_node_properties(const boost::property_tree::ptree& prop);

    private:
        static const std::regex NAME_REGEX;

        bool m_started;
        connector m_connector;
        std::forward_list<shared_library> m_libs;
        std::forward_list<std::unique_ptr<node>> m_nodes;
        std::forward_list<std::unique_ptr<executor>> m_executors;
    };
}


