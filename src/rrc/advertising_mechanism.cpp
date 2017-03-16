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

#include <rrc/advertising_mechanism.h>


rrc::advertising_mechanism::advertising_mechanism(rrc::abstract_launcher& launcher)
        : mechanism(launcher) {}


void rrc::advertising_mechanism::send_message(std::string topic_key, rrc::shared_buffer message) {
    mechanism::template enqueue_task<SEND_MESSAGE_PRIORITY>(
            &base_type::send_message,
            std::move(topic_key),
            std::move(message)
    );
}


void rrc::advertising_mechanism::add_listener(std::string topic_key, rrc::topic_callback callback,
                                              rrc::result_callback result) {
    mechanism::template enqueue_task<CHANGE_LISTENERS_PRIORITY>(
            &base_type::add_listener,
            std::move(topic_key),
            std::move(callback),
            std::move(result)
    );
}


void rrc::advertising_mechanism::remove_listener(std::string topic_key, rrc::topic_callback callback,
                                                 rrc::result_callback result) {
    mechanism::template enqueue_task<CHANGE_LISTENERS_PRIORITY>(
            &base_type::remove_listener,
            std::move(topic_key),
            std::move(callback),
            std::move(result)
    );
}


std::vector<std::string> rrc::advertising_mechanism::keys() const {
    return mechanism::call(mem_fn(&base_type::keys));
}
