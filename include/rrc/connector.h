/**
 *  @autor arssivka
 *  @date 4/11/17
 */

#pragma once


#include <string>
#include <unordered_map>
#include <forward_list>

namespace rrc {
    class node;
    class executor;

    class connector {
    public:
        connector();

        void finish();

        connector& add_node(const std::string& name, node* node_ptr);

        connector& add_executor(const std::string& name, executor* exec_ptr);

        connector& connect_sender(const std::string& node_name,
                                  const std::string& sender_name,
                                  const std::string& topic_name);

        connector& connect_receiver(const std::string& node_name,
                                    const std::string& receiver_name,
                                    const std::string& topic_name);

        connector& connect(const std::string& src_node_name,
                           const std::string& sender_name,
                           const std::string& dst_node_name,
                           const std::string& receiver_name);

        connector& attach_node(const std::string& node_name,
                               const std::string& exec_name);

    private:
        std::unordered_map<std::string, node*> m_node_hash;
        std::unordered_map<std::string, executor*> m_executor_hash;
        std::forward_list<std::tuple<std::string, std::string, std::string>> m_output_connections;
        std::forward_list<std::tuple<std::string, std::string, std::string>> m_input_connections;
        std::forward_list<std::tuple<std::string, std::string, std::string, std::string>> m_connections;
        std::forward_list<std::tuple<std::string, std::string>> m_executor_connections;
    };
}


