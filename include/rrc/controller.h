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
#include "connector.h"
#include "shared_library.h"
#include "executor.h"
#include "node.h"

namespace rrc {
    class controller {
    public:
        void read_config(const std::string& filename) {

        }

        void start() {
            m_started = true;
            for (auto&& node_ptr : m_nodes) {
                node_ptr->on_init();
            }

            for (auto&& executor_ptr : m_executors) {
                executor_ptr->start();
            }
        }

        void stop() {
            for (auto&& executor_ptr : m_executors) {
                executor_ptr->stop();
            }
            m_executors.clear();

            for (auto&& node_ptr : m_nodes) {
                node_ptr->on_finish();
            }

            m_nodes.clear();
            m_libs.clear();
            m_started = false;
        }

        bool load_node(const std::string& node_name,
                       const std::string& filename) {
            if (m_started) return false;
            m_libs.emplace_front(filename);
            if (!m_libs.front()) {
                m_libs.pop_front();
                return false;
            }

            std::function<rrc::node*()> factory;
            factory = m_libs.front().get_symbol<rrc::node*()>(rrc::MODULE_ENTRY);
            if (!factory) {
                m_libs.pop_front();
                return false;
            }

            m_nodes.emplace_front(factory());
        }

        bool connect_sender(const std::string& node_name,
                            const std::string& sender_name,
                            const std::string& topic_name) {
            if (m_started) return false;
            m_connector.connect_sender(node_name, sender_name, topic_name);
            return true;
        }

        bool connect_receiver(const std::string& node_name,
                            const std::string& receiver_name,
                            const std::string& topic_name) {
            if (m_started) return false;
            m_connector.connect_receiver(node_name, receiver_name, topic_name);
            return true;
        }

        bool create_executor(const std::string& name,
                             size_t num_of_threads = 1,
                             std::chrono::steady_clock::duration loop_min_dur = std::chrono::seconds(0)) {
            if (m_started) return false;
            m_executors.push_front(std::make_unique<executor>(num_of_threads, loop_min_dur));
            m_connector.add_executor(name, m_executors.front().get());
        }

        bool attach_node(const std::string& node_name, const std::string exec_name) {
            if (m_started) return false;
            m_connector.attach_node(node_name, exec_name);
        }

    private:
        bool m_started;
        connector m_connector;
        std::forward_list<shared_library> m_libs;
        std::forward_list<std::unique_ptr<node>> m_nodes;
        std::forward_list<std::unique_ptr<executor>> m_executors;
    };
}


