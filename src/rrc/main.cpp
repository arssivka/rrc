#include <memory>
#include <forward_list>
#include <boost/property_tree/json_parser.hpp>
#include <rrc/node.h>
#include <rrc/shared_library.h>
#include <rrc/executor.h>
#include <iostream>
#include <map>
#include <regex>


bool read_config(std::string filename, boost::property_tree::ptree& prop) {
    std::ifstream in(filename);
    if (!in) {
        return false;
    };
    boost::property_tree::read_json(in, prop);
    in.close();
    return true;
}

bool check_name(const std::string& name) {
    return std::regex_match(name, std::regex("[a-zA-Z_]([a-zA-Z0-9_])*"));
}


int main(int argc, char** argv) {
    using namespace boost::property_tree;

    std::forward_list<std::unique_ptr<rrc::node>> nodes;
    std::forward_list<rrc::shared_library> libs;
    std::forward_list<rrc::executor> launchers;


    {
        ptree prop;
        if (!read_config((argc > 1) ? argv[2] : "config.json", prop)) {
            std::cerr << "Can't read config file" << std::endl;
            return 1;
        }

        auto prop_nodes = prop.get_child_optional("nodes");
        auto prop_threads = prop.get_child_optional("threads");

        std::map<std::string, rrc::node*> node_dict;
        std::multimap<std::string, rrc::sender*> output_dict;
        std::multimap<std::string, rrc::receiver*> inputs_dict;

        bool fail = false;
        for (auto&& prop_node : prop_nodes.get()) {
            std::string name = prop_node.first;
            std::string lib_file = prop_node.second.get<std::string>("library", "");
            std::function<rrc::node*(int, char**)> factory;

            if (!check_name(name)) {
                std::cerr << "Incorrent node name: " << name << std::endl;
                fail = true;
                continue;
            }

            if (node_dict.find(name) != node_dict.end()) {
                std::cerr << "Node name already exists: " << name << std::endl;
                fail = true;
                continue;
            }

            rrc::shared_library lib(lib_file);
            factory = lib.get_symbol<rrc::node*(int, char**)>(rrc::MODULE_ENTRY);

            if (!factory) {
                std::cerr << "Can't load library: \"" << lib_file << "\"" << std::endl;
                fail = true;
                continue;
            }

            libs.push_front(std::move(lib));


            std::unique_ptr<rrc::node> node_ptr(factory(argc, argv));
            if (node_ptr == nullptr) {
                std::cerr << "Can't create node: " << name << std::endl;
                fail = true;
                continue;
            }

            auto prop_inputs = prop_node.second.get_child_optional("inputs");
            auto prop_outputs = prop_node.second.get_child_optional("outputs");

            if (prop_inputs) {
                for (auto&& prop_input : prop_inputs.get()) {
                    std::string input_name = prop_input.first;
                    std::string topic_name = prop_input.second.data();
                    if (!check_name(input_name) || ! check_name(topic_name)) {
                        std::cerr << "Invalid connection in " << name << "topic: "
                                  << input_name << " -> " << topic_name << std::endl;
                        fail = true;
                        continue;
                    }

                    auto receiver_ptr = node_ptr->find_receiver(input_name);
                    if (receiver_ptr == nullptr) {
                        std::cerr << "Can't find " << input_name << " input in " << name << " node" << std::endl;
                        fail = true;
                        continue;
                    }
                    inputs_dict.insert({std::move(input_name), receiver_ptr});
                }
            }

            if (prop_outputs) {
                for (auto&& prop_output : prop_outputs.get()) {
                    std::string output_name = prop_output.first;
                    std::string topic_name = prop_output.second.data();
                    if (!check_name(output_name) || !check_name(topic_name)) {
                        std::cerr << "Invalid connection in " << name << "topic: "
                                  << topic_name << " -> " << output_name << std::endl;
                        fail = true;
                        continue;
                    }

                    auto receiver_ptr = node_ptr->find_receiver(output_name);
                    if (receiver_ptr == nullptr) {
                        std::cerr << "Can't find " << output_name << " output in " << name << " node" << std::endl;
                        fail = true;
                        continue;
                    }
                    inputs_dict.insert({std::move(output_name), receiver_ptr});
                }
            }


            node_dict.insert({std::move(name), node_ptr.get()});
            nodes.push_front(std::move(node_ptr));
        }

    }
    return 0;
}