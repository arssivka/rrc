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
 *  @date 3/16/17
 */

#include <rrc/service_mechanism.h>


rrc::service_mechanism::service_mechanism(rrc::abstract_launcher& launcher)
        : mechanism(launcher) {}


void rrc::service_mechanism::add_service(std::string key,
                                         rrc::service_callback callback,
                                         rrc::result_callback result) {
    mechanism::template enqueue_task<CHANGE_SERVICES_PRIORITY>(
            &base_type::add_service,
            std::move(key),
            std::move(callback),
            std::move(result)
    );
}


void rrc::service_mechanism::remove_service(rrc::service_callback callback,
                                            rrc::result_callback result) {
    mechanism::template enqueue_task<CHANGE_SERVICES_PRIORITY>(
            &base_type::remove_service,
            std::move(callback),
            std::move(result)
    );
}


void rrc::service_mechanism::call(const std::string& key,
                                  rrc::shared_buffer input,
                                  rrc::service_result_callback listener) {
    mechanism::template enqueue_task<SERVICE_CALL_PRIORITY>(
            &base_type::call,
            std::move(key),
            std::move(input),
            std::move(listener)
    );
}


void rrc::service_mechanism::add_key_listener(key_callback callback, bool get_exists_keys, result_callback result) {
    mechanism::template enqueue_task<CHANGE_KEY_LISTENERS_PRIORITY>(
            std::mem_fn(&base_type::add_key_listener),
            std::move(callback),
            get_exists_keys,
            std::move(result)
    );
}

void rrc::service_mechanism::remove_key_listener(key_callback callback, rrc::result_callback result) {
    mechanism::template enqueue_task<CHANGE_KEY_LISTENERS_PRIORITY>(
            std::mem_fn(&base_type::remove_key_listener),
            std::move(callback),
            std::move(result)
    );
}
