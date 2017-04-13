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

#pragma once


#include <string>
#include <unordered_map>
#include "shared_library.h"

namespace rrc {
    class node;
    
    class node_factory {
    public:
        node_factory() = default;

        node_factory(const node_factory&) = delete;

        node_factory& operator=(const node_factory&) = delete;

        bool load(const std::string& filename);
        
        bool unload(const std::string& filename) noexcept;
        
        rrc::node* create(const std::string& filename, const std::string& symbol, const std::string& property_file);

    private:
        std::unordered_map<std::string, shared_library> m_libs_hash;

    };
}


