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


    }
    return 0;
}