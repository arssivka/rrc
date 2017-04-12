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

#include "defines.h"
#include <string>

#if defined(RRC_UNIX)
    #include <dlfcn.h>
#endif

namespace rrc {
    class shared_library {
    public:
        shared_library(const std::string& filename);

        ~shared_library();

        bool loaded() const noexcept;


        shared_library(shared_library&&) = default;

        shared_library& operator=(shared_library&&) = default;

        // Non copyable
        shared_library(const shared_library&) = delete;

        shared_library& operator=(const shared_library&) = delete;

        operator bool() const noexcept;

#if defined(RRC_UNIX)
    public:
        template <class T>
        T* get_symbol(const std::string& sym) const noexcept {
            if (m_handle_ptr == nullptr) return nullptr;
            T* ptr = (T*) dlsym(m_handle_ptr, sym.c_str());
            return ptr;
        }


    private:
        void* m_handle_ptr;
#endif
    };
}


