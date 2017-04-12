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

#include <boost/algorithm/string.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "rrc/controller.h"


const std::regex rrc::controller::NAME_REGEX("[a-zA-Z_]([a-zA-Z0-9_])*");


bool rrc::controller::read_config(const std::string& filename) {
    using namespace boost::property_tree;

    if (m_started) return false;

    std::ifstream in(filename);
    if (!in) return false;

    ptree prop;
    if (boost::iends_with(filename, ".json")) {
        json_parser::read_json(in, prop);
    } else if (boost::iends_with(filename, ".xml")) {
        xml_parser::read_xml(in, prop);
    } else if (boost::iends_with(filename, ".ini")) {
        ini_parser::read_ini(in, prop);
    } else {
        return false;
    }

    return this->apply_properties(prop);
}


void rrc::controller::start() {
    m_started = true;
    for (auto&& node_ptr : m_nodes) {
        node_ptr->on_init();
    }

    for (auto&& executor_ptr : m_executors) {
        executor_ptr->start();
    }
}


void rrc::controller::stop() {
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


bool rrc::controller::load_node(const std::string& node_name,
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


bool rrc::controller::connect_sender(const std::string& node_name,
                                     const std::string& sender_name,
                                     const std::string& topic_name) {
    if (m_started) return false;
    m_connector.connect_sender(node_name, sender_name, topic_name);
    return true;
}


bool rrc::controller::connect_receiver(const std::string& node_name,
                                       const std::string& receiver_name,
                                       const std::string& topic_name) {
    if (m_started) return false;
    m_connector.connect_receiver(node_name, receiver_name, topic_name);
    return true;
}


bool
rrc::controller::create_executor(const std::string& name,
                                 size_t num_of_threads,
                                 std::chrono::steady_clock::duration loop_min_dur) {
    if (m_started) return false;
    m_executors.push_front(std::make_unique<executor>(num_of_threads, loop_min_dur));
    m_connector.add_executor(name, m_executors.front().get());
}


bool rrc::controller::attach_node(const std::string& node_name,
                                  const std::string exec_name) {
    if (m_started) return false;
    m_connector.attach_node(node_name, exec_name);
}


bool rrc::controller::is_name_valid(const std::string& name) {
    return std::regex_match(name, NAME_REGEX);
}


bool rrc::controller::apply_properties(const boost::property_tree::ptree& prop) {
    auto prop_nodes_opt = prop.get_child_optional("nodes");
    auto prop_threads_opt = prop.get_child_optional("threads");
    bool result = true;
    if (prop_nodes_opt) {
        result &= this->apply_node_properties(prop_nodes_opt.get());
    }
    if (prop_threads_opt) {
        result &= this->apply_thread_properties(prop_threads_opt.get());
    }
    return result;
}


bool rrc::controller::apply_thread_properties(const boost::property_tree::ptree& prop) {

}


bool rrc::controller::apply_node_properties(const boost::property_tree::ptree& prop) {
    using namespace boost::property_tree;

    for (auto&& prop_node : prop) {
        std::string name = prop_node.first;
        std::string lib_file = prop_node.second.get<std::string>("library", "");
        std::function<rrc::node*(int, char**)> factory;

        if (!this->is_name_valid(name)) {
            continue;
        }

//        if (node_dict.find(name) != node_dict.end()) {
////            std::cerr << "Node name already exists: " << name << std::endl;
//            fail = true;
//            continue;
//        }

        rrc::shared_library lib(lib_file);
        factory = lib.get_symbol<rrc::node*(int, char**)>(rrc::MODULE_ENTRY);

//        if (!factory) {
//            std::cerr << "Can't load library: \"" << lib_file << "\"" << std::endl;
//            fail = true;
//            continue;
//        }
//
//        libs.push_front(std::move(lib));
//
//
//        std::unique_ptr<rrc::node> node_ptr(factory(argc, argv));
//        if (node_ptr == nullptr) {
//            std::cerr << "Can't create node: " << name << std::endl;
//            fail = true;
//            continue;
//        }
//
//        auto prop_inputs = prop_node.second.get_child_optional("inputs");
//        auto prop_outputs = prop_node.second.get_child_optional("outputs");
//
//        if (prop_inputs) {
//            for (auto&& prop_input : prop_inputs.get()) {
//                std::string input_name = prop_input.first;
//                std::string topic_name = prop_input.second.data();
//                if (!check_name(input_name) || ! check_name(topic_name)) {
//                    std::cerr << "Invalid connection in " << name << "topic: "
//                              << input_name << " -> " << topic_name << std::endl;
//                    fail = true;
//                    continue;
//                }
//
//                auto receiver_ptr = node_ptr->find_receiver(input_name);
//                if (receiver_ptr == nullptr) {
//                    std::cerr << "Can't find " << input_name << " input in " << name << " node" << std::endl;
//                    fail = true;
//                    continue;
//                }
//                inputs_dict.insert({std::move(input_name), receiver_ptr});
//            }
//        }
//
//        if (prop_outputs) {
//            for (auto&& prop_output : prop_outputs.get()) {
//                std::string output_name = prop_output.first;
//                std::string topic_name = prop_output.second.data();
//                if (!check_name(output_name) || !check_name(topic_name)) {
//                    std::cerr << "Invalid connection in " << name << "topic: "
//                              << topic_name << " -> " << output_name << std::endl;
//                    fail = true;
//                    continue;
//                }
//
//                auto receiver_ptr = node_ptr->find_receiver(output_name);
//                if (receiver_ptr == nullptr) {
//                    std::cerr << "Can't find " << output_name << " output in " << name << " node" << std::endl;
//                    fail = true;
//                    continue;
//                }
//                inputs_dict.insert({std::move(output_name), receiver_ptr});
//            }
//        }
//
//
//        node_dict.insert({std::move(name), node_ptr.get()});
//        nodes.push_front(std::move(node_ptr));
    }
}
