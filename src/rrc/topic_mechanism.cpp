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

#include <rrc/topic_mechanism.h>


rrc::topic_mechanism::topic_mechanism(rrc::abstract_launcher& launcher)
        : mechanism(launcher) {}


void rrc::topic_mechanism::send_message(std::string topic_key, rrc::shared_buffer message) {
    mechanism::template enqueue_task<SEND_MESSAGE_PRIORITY>(
            std::mem_fn(&base_type::send_message),
            std::move(topic_key),
            std::move(message)
    );
}


void rrc::topic_mechanism::add_topic_listener(std::string topic_key, rrc::topic_callback callback,
                                              rrc::result_callback result) {
    mechanism::template enqueue_task<CHANGE_TOPIC_LISTENERS_PRIORITY>(
            std::mem_fn(&base_type::add_topic_listener),
            std::move(topic_key),
            std::move(callback),
            std::move(result)
    );
}


void rrc::topic_mechanism::remove_topic_listener(std::string topic_key, rrc::topic_callback callback,
                                                 rrc::result_callback result) {
    mechanism::template enqueue_task<CHANGE_TOPIC_LISTENERS_PRIORITY>(
            std::mem_fn(&base_type::remove_topic_listener),
            std::move(topic_key),
            std::move(callback),
            std::move(result)
    );
}


void rrc::topic_mechanism::add_key_listener(key_callback callback, bool get_exists_keys, result_callback result) {
    mechanism::template enqueue_task<CHANGE_KEY_LISTENERS_PRIORITY>(
            std::mem_fn(&base_type::add_key_listener),
            std::move(callback),
            get_exists_keys,
            std::move(result)
    );
}

void rrc::topic_mechanism::remove_key_listener(rrc::key_callback callback, rrc::result_callback result) {
    mechanism::template enqueue_task<CHANGE_KEY_LISTENERS_PRIORITY>(
            std::mem_fn(&base_type::remove_key_listener),
            std::move(callback),
            std::move(result)
    );
}


size_t rrc::topic_mechanism::listeners_count(const std::string& topic_key) const {
    return mechanism::call(std::mem_fn(&base_type::listeners_count), std::ref(topic_key));
}
