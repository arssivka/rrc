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
 *  @date 4/10/17
 */

#pragma once


#include <string>

#if defined(__linux__) || \
        defined(__linux)   || \
        defined(linux)     || \
        defined(__APPLE__)
    #define RRC_EXPORT
    #define RRC_UNIX
#elif defined(_WIN32)
    #define RRC_EXPORT __declspec(dllexport)
    #define RRC_WIN32
#else
    #warning "Unknown target platform"
#endif

namespace rrc {
    const std::string MODULE_ENTRY("rrcmain");
}


