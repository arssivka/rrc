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

#include "rrc/shared_library.h"


#if defined(RRC_UNIX)

rrc::shared_library::shared_library(const std::string& filename)
        : m_handle_ptr(dlopen(filename.c_str(), RTLD_LAZY)) {}


void rrc::shared_library::open(const std::string& filename) {
    this->close();
    m_handle_ptr = dlopen(filename.c_str(), RTLD_LAZY);
}


void rrc::shared_library::close() {
    if (m_handle_ptr != nullptr) dlclose(m_handle_ptr);
}

#endif


bool rrc::shared_library::loaded() const noexcept {
    return m_handle_ptr != nullptr;
}

rrc::shared_library::operator bool() const noexcept {
    return this->loaded();
}


rrc::shared_library::~shared_library() {
    this->close();
}
