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

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>
#include <memory>
#include <forward_list>
#include <rrc/node_factory.h>
#include <rrc/executor.h>
#include <rrc/connector.h>
#include <rrc/sender.h>
#include <rrc/receiver.h>
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


bool is_name_valid(const std::string& name) {
    return std::regex_match(name, std::regex("[a-zA-Z_]([a-zA-Z0-9_])*"));
}


int main(int argc, char** argv) {
    namespace pt = boost::property_tree;
    namespace po = boost::program_options;

    int d_level;
    std::vector<std::string> config_files;

    rrc::node_factory factory;

    po::options_description desc("Allowed options:");
    desc.add_options()
            ("help,h", "show this text")
            ("debug,d", "set debug level (0-3)")
            ("config,c", po::value<std::vector<std::string>>(&config_files), "configuration files")
            ("cmd", "enable command line");
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return EXIT_SUCCESS;
    }

    pt::ptree prop;
    bool fail = false;
    bool cmd = vm.count("cmd") > 0;

    if (!config_files.empty()) {
        for (auto&& file : config_files) {
            boost::trim(file);
            std::ifstream in(file);
            if (!in) {
                fail = true;
                std::cout << "ERROR: Can't open " << file << " config file!" << std::endl;
                in.close();
                continue;
            }
            try {
                if (boost::iends_with(file, ".json")) {
                    pt::read_json(in, prop);
                } else if (boost::iends_with(file, ".xml")) {
                    pt::read_xml(in, prop);
                } else {
                    fail = true;
                    std::cout << "ERROR: Unknown format of " << file << " file!" << std::endl;
                }
            } catch (pt::file_parser_error& e) {
                fail = true;
                std::cout << "ERROR: Error occurs during parsing " << file << " file"
                          << " in " << e.line() << " line: " << e.message() << std::endl;
            }
            in.close();
        }
    } else if (cmd) {
        std::cout << "ERROR: Config files don't specified!" << std::endl;
        fail = true;
    }

    if (fail) {
        std::cout << desc << std::endl;
        return EXIT_FAILURE;
    }

    for (auto&& prop_entry : prop) {
        const std::string& type = prop_entry.first;
    }

    return 0;
}