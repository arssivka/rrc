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


#include "service_holder.h"
#include "mechanism.h"

namespace rrc {
    class service_mechanism : protected mechanism<service_holder, 2> {
    public:
        enum {
            SERVICE_CHANGES_PRIORITY,
            SERVICE_CALL_PRIORITY
        };

        service_mechanism(abstract_launcher& launcher)
                : mechanism(launcher) {}

        void add_service(std::string key, service_callback callback) {
            mechanism::template enqueue_task<SERVICE_CHANGES_PRIORITY>(
                    &base_type::add_service,
                    std::move(key),
                    std::move(callback)
            );
        }

        void remove_service(service_callback callback) {
            mechanism::template enqueue_task<SERVICE_CHANGES_PRIORITY>(
                    &base_type::remove_service,
                    std::move(callback)
            );
        }

        void call(const std::string& key, shared_buffer input, service_result_callback listener) {
            mechanism::template enqueue_task<SERVICE_CALL_PRIORITY>(
                    &base_type::call,
                    std::move(key),
                    std::move(input),
                    std::move(listener)
            );
        }

        std::vector<std::string> keys() const {
            return mechanism::call(std::mem_fn(&service_holder::keys));
        }
    };
}


