/**
 *  @autor arssivka
 *  @date 4/11/17
 */

#include "rrc/connector.h"
#include "rrc/topic.h"
#include "rrc/node.h"
#include "rrc/sender.h"
#include "rrc/executor.h"


rrc::connector::connector() {}


void rrc::connector::finish() {
    std::unordered_map<std::string, topic> topics;
    for (auto&& connection : m_input_connections) {
        auto& node_name = std::get<0>(connection);
        auto& receiver_name = std::get<1>(connection);
        auto& topic_name = std::get<2>(connection);

        auto node_it = m_node_hash.find(node_name);
        if (node_it == m_node_hash.end()) continue;
        node* node_ptr = node_it->second;

        receiver* receiver_ptr = node_ptr->find_receiver(receiver_name);
        if (receiver_ptr == nullptr) continue;

        auto topic_it = topics.find(topic_name);
        if (topic_it == topics.end()) {
            topic_it = topics.emplace(topic_name, topic()).first;
        }

        topic_it->second.add_receiver(receiver_ptr);
    }

    for (auto&& connection : m_output_connections) {
        auto& node_name = std::get<0>(connection);
        auto& sender_name = std::get<1>(connection);
        auto& topic_name = std::get<2>(connection);

        auto node_it = m_node_hash.find(node_name);
        if (node_it == m_node_hash.end()) continue;
        node* node_ptr = node_it->second;

        sender* sender_ptr = node_ptr->find_sender(sender_name);
        if (sender_ptr == nullptr) continue;

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
        if (node_it == m_node_hash.end()) continue;
        node* src_node_ptr = node_it->second;

        node_it = m_node_hash.find(dst_node_name);
        if (node_it == m_node_hash.end()) continue;
        node* dst_node_ptr = node_it->second;

        sender* sender_ptr = src_node_ptr->find_sender(sender_name);
        if (sender_ptr == nullptr) continue;

        receiver* receiver_ptr = dst_node_ptr->find_receiver(receiver_name);
        if (receiver_ptr == nullptr) continue;

        if (!sender_ptr->has_receiver(receiver_ptr))
            sender_ptr->add_receiver(receiver_ptr);
    }

    for (auto&& topic_pair : topics) {
        topic_pair.second.connect();
    }

    for (auto&& connection : m_executor_connections) {
        auto& node_name = std::get<0>(connection);
        auto& exec_name = std::get<1>(connection);

        auto node_it = m_node_hash.find(node_name);
        if (node_it == m_node_hash.end()) continue;

        auto exec_it = m_executor_hash.find(exec_name);
        if (exec_it == m_executor_hash.end()) continue;

        exec_it->second->add_node(node_it->second);
    }

    m_node_hash.clear();
    m_input_connections.clear();
    m_output_connections.clear();
    m_executor_connections.clear();
}


rrc::connector& rrc::connector::add_node(const std::string& name, rrc::node* node_ptr) {
    if (m_node_hash.find(name) == m_node_hash.end()) {
        m_node_hash.insert({name, node_ptr});
    }
    return *this;
}


rrc::connector& rrc::connector::connect_sender(const std::string& node_name, const std::string& sender_name,
                                               const std::string& topic_name) {

    m_output_connections.emplace_front(node_name, sender_name, topic_name);
    return *this;
}


rrc::connector& rrc::connector::connect_receiver(const std::string& node_name, const std::string& receiver_name,
                                                 const std::string& topic_name) {

    m_input_connections.emplace_front(node_name, receiver_name, topic_name);
    return *this;
}


rrc::connector& rrc::connector::connect(const std::string& src_node_name, const std::string& sender_name,
                                        const std::string& dst_node_name, const std::string& receiver_name) {
    m_connections.emplace_front(src_node_name, sender_name, dst_node_name, receiver_name);
    return *this;
}

rrc::connector& rrc::connector::attach_node(const std::string& node_name,
                                            const std::string& exec_name) {
    m_executor_connections.emplace_front(node_name, exec_name);
    return *this;
}

rrc::connector& rrc::connector::add_executor(const std::string& name, rrc::executor* exec_ptr) {
    if (m_executor_hash.find(name) == m_executor_hash.end()) {
        m_executor_hash.emplace(name, exec_ptr);
    }
    return *this;
}
