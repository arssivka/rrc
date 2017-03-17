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
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *  @autor arssivka
 *  @date 2/7/17
 */

#pragma once


#include <vector>
#include <unordered_map>
#include "callback_defines.h"
#include "key_listener.h"

namespace rrc {
    class service_holder {
    public:
        service_holder();

        void add_service(const std::string& key,
                         service_callback callback,
                         const result_callback& result = result_callback());

        void remove_service(const service_callback& callback,
                            const result_callback& result = result_callback());

        void add_key_listener(key_callback callback, const result_callback& result = result_callback());

        void remove_key_listener(const key_callback& callback, const result_callback& result = result_callback());

        void call(const std::string& key, const shared_buffer input, service_result_callback listener);

        std::vector<std::string> keys() const;

    private:
        std::unordered_map<std::string, service_callback> m_service_hash;
        key_listener m_key_listener;
    };
}


