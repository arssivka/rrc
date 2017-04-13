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
 *  @date 4/13/17
 */

#include <functional>
#include "rrc/node_factory.h"


bool rrc::node_factory::load(const std::string& filename) {
    if (m_libs_hash.find(filename) != m_libs_hash.end()) return false;
    shared_library lib(filename);
    if (!lib) return false;
    m_libs_hash.emplace(filename, std::move(lib));
    return true;
}



rrc::node* rrc::node_factory::create(const std::string& filename,
                                     const std::string& function,
                                     const std::string& property_file) {
    auto it = m_libs_hash.find(filename);
    if (it == m_libs_hash.end()) {
        shared_library lib(filename);
        if (!lib) return nullptr;
        it = m_libs_hash.emplace(filename, std::move(lib)).first;
    }
    auto& lib = it->second;
    std::function<rrc::node*(const std::string&)> factory_method = lib.get_symbol<rrc::node*(const std::string&)>(function);
    if (!factory_method) return nullptr;
    return factory_method(property_file);
}


bool rrc::node_factory::unload(const std::string& filename) noexcept {
    auto it = m_libs_hash.find(filename);
    if (it == m_libs_hash.end()) return false;
    m_libs_hash.erase(it);
    return true;
}
