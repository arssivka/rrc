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
 *  @date 4/8/17
 */

#pragma once


#include <cstdint>
#include <cstddef>
#include <functional>

namespace rrc {
    class receiver {
    public:
        using functor = std::function<void(const uint8_t*, size_t)>;

        receiver(functor&& fn);

        receiver(const receiver&) = delete;

        receiver& operator=(const receiver&) = delete;

        void receive(const uint8_t* buff, size_t size);

    private:
        std::function<void(const uint8_t*, size_t)> m_functor;

    };
}

